#include "include.h"
int url_parser(char *url, char *hostname, char *urlfile, int *port)
{
	char *tmp;
	char *port_index;
	url += 7;
	tmp = NULL;
	tmp = strstr(url,"/");
	memcpy(hostname,url,tmp-url);
	if(strstr(hostname,":") != NULL)
	{
		port_index = NULL;
		port_index = strstr(hostname,":");
		port_index+=1;
		*port = atoi(port_index);
	}
	else
		*port = 80;
	memcpy(urlfile,tmp,strlen(tmp));
	memset(hostname,0,128);
	if(strstr(url,":") != NULL)
	{
		tmp = strstr(url,":");
		memcpy(hostname,url,tmp-url);
	}
	else
		memcpy(hostname,url,tmp-url);
	return 0;
}
int tcp_client(char *hostname,int port)
{
	int sockfd,ret;
	struct sockaddr_in server;
	struct hostent *tmp;

	sockfd = socket(AF_INET,SOCK_STREAM,0);


	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port   = htons(port);

	tmp = gethostbyname(hostname);
	if(tmp == NULL)
		{	
			return -1;
		}
	memcpy(&server.sin_addr,(struct in_addr *)tmp->h_addr,4);
	
	ret = connect(sockfd,(struct sockaddr *)&server,sizeof(server));
	if(ret < 0)
		{
			return -1;
		}
	
	printf("connect to %s success!\n",hostname);

	return sockfd;
}
int send_http_request(int sockfd,char *hostname,int port,char *filename)
{
	char *send_request_char = (char *)malloc(256);
	memset(send_request_char,0,256);
	sprintf(send_request_char,"GET %s HTTP/1.1\r\nHost: %s:%d\r\nConnection: Close\r\n\r\n",filename,hostname,port);
	printf("send_request_char:%s",send_request_char);
	send(sockfd,send_request_char,strlen(send_request_char),0);
	printf("send ok\n");
	return 0;
}
int recv_http_request(int sockfd)
{
	char buf[10240];
	memset(buf,0,10240);
	char *index = NULL;
	int down_fd;
	int ret = recv(sockfd,buf,10240,0);
	if(ret < 0) return -1;
	index = strstr(buf,"\r\n\r\n");
	if(index)
	{
		printf("recv is:\n%s",buf);
	}
	char *p = buf;
	p+=9;
	int num = atoi(p);
	if(num!=200) 
	{
		shutdown(sockfd,SHUT_RDWR);
		close(sockfd);
		return -1;
	}
	num = index-buf+4;
	printf("num:%d\n",num);
	down_fd = open("/bin/gateway_bak",O_RDWR|O_CREAT|O_TRUNC,0777);
	printf("downloading >>>>>\n");
	write(down_fd,buf+num,ret-num);
	while(ret)
	{
		memset(buf,0,10240);
		ret = recv(sockfd,buf,10240,0);
		if(ret<0)
		{
			shutdown(sockfd,SHUT_RDWR);
			close(sockfd);
			close(down_fd);
			remove("/bin/gateway_bak");
			return -1;
		}
		write(down_fd,buf,ret);
	}
	shutdown(sockfd,SHUT_RDWR);
	close(sockfd);
	fsync(down_fd);
	close(down_fd);
	return 0;
}
void down_file(cJSON *root)
{
	int ret_value;
	int my_sockfd;
	cJSON *url_data = cJSON_GetObjectItem(root,"data");
	cJSON *url = cJSON_GetObjectItem(url_data,"http");
	//char url[] = "http://47.106.229.214:8091/file/gateway";

	char hostname[128];
	memset(hostname,0,128);
	char urlfile[256];
	memset(urlfile,0,256);
	int port;
	url_parser(url->valuestring,hostname,urlfile,&port);
	printf("hostname:%s\n",hostname);
	printf("urlfile:%s\n",urlfile);
	printf("port:%d\n",port);
	my_sockfd = tcp_client(hostname,port);
	if(my_sockfd==-1)
	{
		printf("socket failed \n");
		return ;
	}
	send_http_request(my_sockfd,hostname,port,urlfile);
	ret_value = recv_http_request(my_sockfd);
	if(ret_value==0)
	{
		printf("download file success\n");
		pthread_mutex_lock(&mutex_down_file);
		remove("/bin/gateway");
		system("mv /bin/gateway_bak /bin/gateway");
		system("chmod +x /bin/gateway");
		pthread_mutex_unlock(&mutex_down_file);
		kill_gateway();
	}
	else
	{
		printf("download file failed\n");
		return ;
	}
}
