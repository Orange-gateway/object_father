#include "include.h"

/*  tcp初始化函数   */
int client_init(void)
{
	int ret = 1;
	
	cd = -1;
	struct sockaddr_in ser_addr;
	
	memset((void*)&ser_addr,0,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	
	//inet_aton("47.106.229.214",&ser_addr.sin_addr);//将点分式ip地址 转换为2进制 
	//inet_aton("192.168.77.131",&ser_addr.sin_addr);//将点分式ip地址 转换为2进制 
	
	struct hostent *tmp;
	tmp = gethostbyname("smart.zgjuzi.com");
	
	if(tmp == NULL)
		return -1;
		
	memcpy(&ser_addr.sin_addr,(struct in_addr *)tmp->h_addr,4);

	cd = socket(AF_INET,SOCK_STREAM,0);
	if(cd == -1)
		return -1;
	ret = connect(cd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
	if( ret == 0)
	{	
		printf("connect success  cd = %d\n",cd);
		struct timeval timeout = {1,0}; 
		setsockopt(cd,SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(struct timeval));
		return 0;
	}
	else
	{
		printf("connet fault  cd = %d\n",cd);
		NET_FLAG = 0;
		return -1;
	}
}

void tcp_server_init(void)
{
	int sockfd, num_d,client_sockfd = -1,flag_break,sin_size=0,len=0,arr_len=0,data_len=0,max_fd;
	fd_set inset,tmp_inset;
	uint8_t r_buff[1024];//串口接收缓冲区
	uint8_t rc_buff[10240];//中间转换缓冲区
	//char send_ip[16] = {0};
	struct sockaddr_in server_sockaddr, client_sockaddr;
	memset((void *)&server_sockaddr,0,sizeof(server_sockaddr));
	memset((void *)&client_sockaddr,0,sizeof(client_sockaddr));
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{ 
		perror("socket"); 
		exit(1); 
	} 
	server_sockaddr.sin_family = AF_INET; 
	server_sockaddr.sin_port = htons(8888);
	//get_local_ip("eth0", send_ip);
	inet_aton("192.168.77.1",&server_sockaddr.sin_addr);//将点分式ip地址 转换为2进制 
	memset(&(server_sockaddr.sin_zero),0,8);
	int i = 1;/* 允许重复使用本地地址与套接字进行绑定*/ 
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
	if (bind(sockfd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1) 
	{ 
		perror("bind"); 
		exit(1); 
	}
	if(listen(sockfd,25)== -1)
	{ 
		perror("listen"); 
		exit(1);
	}
	printf("listening.........%d\n",sockfd);
	max_fd = sockfd+1;
	FD_ZERO(&inset); 
	FD_SET(sockfd, &inset);
	sin_size=sizeof(struct sockaddr_in);
	memset(rc_buff,0,10240);
	struct timeval timeout = {0,100000}; 
	while(1)
	{
		tmp_inset = inset;
		memset(r_buff, 0, 1024);
		printf("select qian\n");
		if (select(max_fd,&tmp_inset,NULL, NULL, NULL) > 0) //选择文件描述符的动作，如果有动作就不阻塞 否则一直阻塞在那.
		{	printf("max_fd : %d\n",max_fd);
			for (num_d = 3; num_d < max_fd; num_d++)
			{
				if (FD_ISSET(num_d, &tmp_inset) > 0)
				{
					if (num_d == sockfd)
					{
						client_sockfd = -1;
						if (( client_sockfd = accept(sockfd,(struct sockaddr *)&client_sockaddr,(socklen_t *)&sin_size))== -1) 
						{
 	 						perror("accept");
							exit(1);
						}
						else 
						{
							printf("client_fd is %d coming\n",client_sockfd); 
							FD_SET(client_sockfd,&inset);
							//memset(buf_mac,0,13);
							//getpeermac(client_sockfd,buf_mac);
							//net_fd_zt(client_sockfd,buf_mac,inset);
							setsockopt(client_sockfd,SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(struct timeval));
							if(client_sockfd >= max_fd) max_fd=1+client_sockfd;
						}
					}
					else
					{
						len=recv(num_d,r_buff,1024,0);//接收
						
						if(len>0)
						{
							for(i=0;i<len;i++)
							{
								rc_buff[arr_len]=r_buff[i];
								arr_len+=1;
							}
							while(1)
							{
								if(arr_len > 15)
								{
									flag_break = 0;
									for(i=0;i<arr_len;i++)
									{	
										if((rc_buff[i]==0x5A)&&(rc_buff[i+1]==0xA5))
										{
											if(i>0)
											{
												delete_len_from_arr(rc_buff,i,&arr_len);
											}
											if(arr_len > 15)
											{
												data_len = rc_buff[13]*256+rc_buff[14]+15;
												
												if(arr_len >= data_len)
												{
													uint8_t *my_u_data = NULL;
													my_u_data =(uint8_t*)malloc(data_len);//解析数据接收缓冲区
													memset(my_u_data,0,data_len);
													printf("US_receive (%d): ",num_d);
													for(i=0;i<data_len;i++)
													{
														my_u_data[i]=rc_buff[i];
														printf("%.2x ",my_u_data[i]);
													}
													printf("\n");
													up_resend(my_u_data);//更新重发列表
													if( my_u_data[10] == 0xf1)
													{
														send_to_son_hart_jump(num_d);
														free(my_u_data);
														my_u_data = NULL;
													}
													else if( my_u_data[10] == 0xf4)
													{
														char *pthread_mac = (char *)malloc(13);
														memset(pthread_mac,0,13);
														hex_to_str(my_u_data+15,pthread_mac,6);
														pthread_mac[12] = '\0';
														net_fd_zt(client_sockfd,pthread_mac,&inset);
														pth_creat_my(get_status,pthread_mac);
														free(my_u_data);
														my_u_data = NULL;
													}
													else
														pth_creat_my(pthread_v_send,my_u_data);
													
													delete_len_from_arr(rc_buff,data_len,&arr_len);
												}
												else
													flag_break = 1;
											}
											break;
										}
										else if(i==arr_len-1)
											flag_break = 1;
									}
									if(flag_break) break;
								}
								else
									break;
							}
						}
						else
						{
							printf("%d is gone\n",num_d);
							//kill_gateway();
							up_net_fd(num_d);
							close(num_d); 
							FD_CLR(num_d, &inset);//diaoxian
						}
						
					}
				}
			}
		}
	}
}

/*增加更新子网关网络状态*/
void net_fd_zt(int net_fd,char *mac,fd_set *inset)
{
	NET_F *p = NULL,*q = NULL;
	p  = q = net_head;
	
	if(p == NULL)
	{
		net_d = (NET_F *)malloc(sizeof(NET_F));
		memset(net_d,0,sizeof(NET_F));
		net_d->flag = 1;
		net_d->fd_net = net_fd;
		memset(net_d->mac,0,13);
		memcpy(net_d->mac,mac,13);
		net_head = net_z = net_d;
		net_d->next = NULL;
		printf("net_d->fd_net:%d mac : %s\n",net_d->fd_net,net_d->mac);
		return ;
	}
	else
	{
		while( p )
		{
			if(strcmp(p->mac,mac)==0)
			{
				p->flag = 1;
				if(p->fd_net != net_fd)
				{
					int close_fd = p->fd_net;
					p->fd_net = net_fd;
					if( !find_net_fd_repeat(close_fd) )
					{
						close(close_fd);
						printf("close is %d  new is %d\n",close_fd,net_fd);
						up_net_fd(close_fd);
						FD_CLR(close_fd,inset);
					}
				}
				return;
			}
			else if(p->next == NULL)
			{
				net_d = (NET_F *)malloc(sizeof(NET_F));
				memset(net_d,0,sizeof(NET_F));
				net_d->flag = 1;
				net_d->fd_net = net_fd;
				memset(net_d->mac,0,13);
				memcpy(net_d->mac,mac,13);
				p->next = net_d;
				net_d->next = NULL;
				printf("null : net_d->fd_net:%d mac : %s\n",net_d->fd_net,net_d->mac);
				return ;
			}
			p = p->next;
		}
	}
}

void up_net_fd(int net_fd)
{
	NET_F *p = NULL;
	p = net_head;
	while( p )
	{
		if(p->fd_net == net_fd)
		{
			p->flag = 0;
			return;
		}
		p = p->next;
	}
}

int find_net_fd_repeat(int num_fd)
{
	NET_F *p = NULL;
	p = net_head;
	while( p )
	{
		if( p->fd_net == num_fd )
			return 1;
		else if( p->next == NULL)
			return 0;
		p = p->next;
	}
	return 0;
}

void getpeermac( int sockfd, char *buf )
{
	struct arpreq arpreq;
	struct sockaddr_in dstadd_in;
	socklen_t  len = sizeof( struct sockaddr_in );
	memset( &arpreq, 0, sizeof( struct arpreq ));
	memset( &dstadd_in, 0, sizeof( struct sockaddr_in ));
	if( getpeername( sockfd, (struct sockaddr*)&dstadd_in, &len ) < 0 )
		printf("getpeername error\n");  
	else
	{
		memcpy( &arpreq.arp_pa, &dstadd_in, sizeof( struct sockaddr_in ));
		memcpy(arpreq.arp_dev, "br-lan",6);
		arpreq.arp_pa.sa_family = AF_INET;
		arpreq.arp_ha.sa_family = AF_UNSPEC;
		if( ioctl( sockfd, SIOCGARP, &arpreq ) < 0 )
			printf("ioctl error\n");
		else
		{
			unsigned char* ptr = (unsigned char *)arpreq.arp_ha.sa_data;
			sprintf(buf, "%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
			printf("buf: %s\n",buf);
		}
	}
	return ;
} 
void send_to_son_hart_jump(int send_net)
{
	cJSON *heart_root = cJSON_CreateObject();
	cJSON_AddStringToObject(heart_root,"api","heart_jump-heart_jump");
	char *send_char = cJSON_PrintUnformatted(heart_root);
	int my_len = strlen(send_char);
	char *my_send_char = (char *)malloc(my_len+2);
	memset(my_send_char,0,my_len+2);
	memcpy(my_send_char,send_char,my_len);
	strcat(my_send_char,"\n\0");
	send(send_net,my_send_char,my_len+1,0);
	cJSON_Delete(heart_root);
	heart_root = NULL;
	free(send_char);
	send_char = NULL;
	free(my_send_char);
	my_send_char = NULL;
}
