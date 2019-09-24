#include "include.h"
void handler(int s)
{
	if(s == SIGBUS)
	{
		system("rm /bin/gateway");
		system("killall gateway");
	}
}
int main(int argc,char* argv[])
{
	umask(0);
	signal(SIGBUS, handler);
	memset(gw_version,0,9);
	memcpy(gw_version,"20190726",strlen("20190726"));
	printf("gateway_version:%s\n",gw_version);
	memset(zigbee_channel,0,2);
	memset(zigbee_id,0,5);
	memset(my_gw_mac,0,13);
	get_mac(my_gw_mac);
	onekey_or_study_flag=2;
	resend_head = resend_z = resend_d = NULL;
	human_head = human_z = human_d = NULL;
	net_head = net_z = net_d = NULL;
	sign_mac_head = sign_mac_z = sign_mac_d = NULL;
	int ret_usart,ret0,ret1,ret2,ret3,ret4,ret5,ret6,ret7/*,ret8*/;          //接受返回值，用于判断
	identify_flag = 0;
	go_net_flag = 0;
	NET_FLAG = 0;
	device_flag = 0;
	down_gw_flag = 0;
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init_func();
	fd = usart_open(fd,argv[1]);
	do
	{
		ret_usart = usart_init(fd,115200,0,8,'n',1);
	}while(ret_usart == -1 || fd == -1);
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction( SIGPIPE, &sa, 0 );
	file_init_common();
	pthread_t id_usart,id_heart_jump,id_resend,id_timer,id_human_body,id_gateway_heart,id_tcp_server/*,id_udp_send*/;
	ret0 = pthread_create(&id_usart,NULL,(void*)pthread_usart_receive,NULL);
	if(ret0 < 0)
	{	
		printf("id_usart create fault\n");
		return -1;
	}
	read_channel();
	ret1 = pthread_create(&id_client,NULL,(void*)pthread_client_receive,NULL);
	if(ret1 < 0)
	{
		printf("id_client create fault\n");
		return -1;
	}
	ret3 = pthread_create(&id_timer,NULL,(void*)my_timer,NULL);
	if(ret3 < 0)
	{
		printf("id_timer create fault\n");
	}
	
	ret4 = pthread_create(&id_resend,NULL,(void*)re_send,NULL);
	if(ret4 < 0)
	{
		printf("id_resend create fault\n");
	}
	char *pthread_mac = (char *)malloc(13);
	memset(pthread_mac,0,13);
	memcpy(pthread_mac,my_gw_mac,13);
	pth_creat_my(get_status,pthread_mac);
	ret5 = pthread_create(&id_human_body,NULL,(void*)human_check,NULL);
	if(ret5 < 0)
	{
		printf("id_human_body create fault\n");
	}
	ret6 = pthread_create(&id_tcp_server,NULL,(void*)tcp_server_init,NULL);
	if(ret6 < 0)
	{
			printf("id_tcp_server create fault\n");
	}
	ret7 = pthread_create(&id_gateway_heart,NULL,(void*)gateway_send_heart_jump,NULL);
	if(ret7 < 0)
	{
		printf("id_gateway_heart create fault\n");
	}
/*	ret8 = pthread_create(&id_udp_send,NULL,(void*)pthread_udp_send,NULL);*/      /*创建广播线程*/
/*	if(ret8 < 0)*/
/*	{*/
/*		printf("id_udp_send create fault\n");*/
/*	}*/
	client_init();
	ret2 = pthread_create(&id_heart_jump,NULL,(void*)heart_jump,NULL);
	if(ret2 < 0)
	{
		printf("id_heart_jump create fault\n");
	}
	pthread_join(id_usart,NULL);/*线程等待*/
	pthread_join(id_client,NULL);
	pthread_join(id_heart_jump,NULL);
	pthread_join(id_timer,NULL);
	pthread_join(id_resend,NULL);
	pthread_join(id_human_body,NULL);
	close(fd);
	close(cd);
	return 0;
}


