#include "include.h"
void cmd_mix(char *mac,char *port,char *cmd,uint8_t *final_cmd)//发送至串口合成命令(普通设备控制)
{
	int len = strlen(cmd);
	len = len/2;
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"45");
	strcat(send_cmd,port);
	strcat(send_cmd,"00");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (len>>8)&0xff;
	final_cmd[14] = len & 0xff;
	str_to_hex(final_cmd+15,cmd,len);
}
void cmd_mix_47(char *mac,char *port,char *cmd,uint8_t *final_cmd)//发送至串口合成命令(普通设备控制)离线语音控制控制
{
	int len = strlen(cmd);
	len = len/2;
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"45");
	strcat(send_cmd,port);
	strcat(send_cmd,"47");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (len>>8)&0xff;
	final_cmd[14] = len & 0xff;
	str_to_hex(final_cmd+15,cmd,len);
}
void cmd_mix_scene(char *mac,char *port,char *cmd,uint8_t *final_cmd)//发送至串口合成命令(普通设备控制)
{
	int len = strlen(cmd);
	len = len/2;
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"45");
	strcat(send_cmd,port);
	strcat(send_cmd,"45");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (len>>8)&0xff;
	final_cmd[14] = len & 0xff;
	str_to_hex(final_cmd+15,cmd,len);
}
void cmd_mix_get_signal(char *mac,char *cmd,uint8_t *final_cmd)//获取信号质量合成指令
{
	int len = strlen(cmd);
	len = len/2;
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"60");
	strcat(send_cmd,"00");
	strcat(send_cmd,"00");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (len>>8)&0xff;
	final_cmd[14] = len & 0xff;
	str_to_hex(final_cmd+15,cmd,len);
}
void cmd_mix_get_stastus1(char *mac,char *port,char *cmd,uint8_t *final_cmd)//状态命令合成1
{
	int len = strlen(cmd);
	len = len/2;
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"15");
	strcat(send_cmd,port);
	strcat(send_cmd,"00");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (len>>8)&0xff;
	final_cmd[14] = len & 0xff;
	str_to_hex(final_cmd+15,cmd,len);
}

void cmd_delete_mix(char *mac,char *cmd,uint8_t *final_cmd)//移除设备合成指令
{
	int len = strlen(cmd);
	len = len/2;
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"55");
	strcat(send_cmd,"0000");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (len>>8)&0xff;
	final_cmd[14] = len & 0xff;
	str_to_hex(final_cmd+15,cmd,len);
}

void cmd_request_describ_mix(char *mac,char *cmd,uint8_t *final_cmd)//获取设备描述符指令
{
	int len = strlen(cmd);
	len = len/2;
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"40");
	strcat(send_cmd,"0000");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (len>>8)&0xff;
	final_cmd[14] = len & 0xff;
	str_to_hex(final_cmd+15,cmd,len);
}
void cmd_mix_kt(char *lid,char *cmd,char *kt_code,char *mac,char *id,int len,uint8_t *final_cmd)//发送至串口合成命令(kt)
{
	int num;
	char *send_cmd = NULL;
	send_cmd = (char *)malloc(len+1);
	memset(send_cmd,0,len+1);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"500100");
	num = (len-30)/2;
	uint8_t my_lid[2];
	memset(my_lid,0,2);
	my_lid[0] = (num>>8)&0xff;
	my_lid[1] = num & 0xff;
	hex_to_str(my_lid,send_cmd+26,2);
	num =atoi(lid);
	my_lid[0] = (num>>8)&0xff;
	my_lid[1] = num & 0xff;
	hex_to_str(my_lid,send_cmd+30,2);
	strcat(send_cmd,cmd);
	strcat(send_cmd,kt_code);
	uint8_t my_id[4];
	memset(my_id,0,4);
	num =atoi(id);
	int i;
	for(i=0;i<4;i++)
		my_id[i] = (num >> (3-i)*8)&0xff;
	num = strlen(send_cmd);
	hex_to_str(my_id,send_cmd+num,4);
	str_to_hex(final_cmd,send_cmd,len/2);
	free(send_cmd);
	send_cmd = NULL;
}
void cmd_mix_fkt(char *fkt_code,char *mac,int len,uint8_t *final_cmd)//发送至串口合成命令(fkt)
{
	int num;
	char *send_cmd = NULL;
	send_cmd = (char *)malloc(len+1);
	memset(send_cmd,0,len+1);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"510100");
	num = (len-30)/2;
	uint8_t my_lid[2];
	memset(my_lid,0,2);
	my_lid[0] = (num>>8)&0xff;
	my_lid[1] = num & 0xff;
	hex_to_str(my_lid,send_cmd+26,2);
	strcat(send_cmd,fkt_code);
	str_to_hex(final_cmd,send_cmd,len/2);
	free(send_cmd);
	send_cmd = NULL;
}
void cmd_hw_study_or_complish(char *mac,uint8_t *final_cmd,int flag)//发送至串口红外学习命令合成
{
	char send_cmd[27];
	memset(send_cmd,0,27);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"520100");
	str_to_hex(final_cmd,send_cmd,13);
	final_cmd[13] = (2>>8)&0xff;
	final_cmd[14] = 2 & 0xff;
	final_cmd[15] = 0x52;
	if(flag)
	final_cmd[16] = 0x01;
	else 
	final_cmd[16] = 0x02;
}

void cmd_mix_lock(char *mac,char *port,char *cmd,uint8_t *final_cmd)//发送至串口合成命令(开锁控制指令)
{
	char send_cmd[51];
	memset(send_cmd,0,51);
	memcpy(send_cmd,"5AA5",4);
	strcat(send_cmd,mac);
	strcat(send_cmd,"90");
	strcat(send_cmd,port);
	strcat(send_cmd,"00000aaa550200000000000000");
	memcpy(send_cmd+38,cmd+4,2);
	printf("send locek : (%d)%s\n",(int)strlen(send_cmd),send_cmd);
	str_to_hex(final_cmd,send_cmd,25);
}

void gw_mac_bind_dev_mac(char *u_data_str)//绑定子网关mac
{
	char *gw_mac_str = NULL;
	gw_mac_str = (char*)malloc(13);//son_gw_mac地址
	memset(gw_mac_str,0,13);
	memcpy(gw_mac_str,u_data_str+30,12);
	gw_mac_str[12]='\0';

	char *dev_mac_str = NULL;
	dev_mac_str = (char *)malloc(17);//dev_mac地址
	memset(dev_mac_str,0,17);
	memcpy(dev_mac_str,u_data_str+4,16);
	dev_mac_str[16] = '\0';
	
	pthread_mutex_lock(&mutex_gw_dev_mac);
	cJSON *gw_mac_dev = cJSON_Parse(gw_dev_mac_list);
	if(gw_mac_dev != NULL)
	{
		if(gw_mac_dev->child == NULL)
			cJSON_AddStringToObject(gw_mac_dev,dev_mac_str,gw_mac_str);
		else
		{
			cJSON *while_find = gw_mac_dev->child;
			while(while_find != NULL)
			{
				if(strcmp(dev_mac_str,while_find->string)==0)
				{
					cJSON *Get_Bind_Mac = cJSON_GetObjectItem(gw_mac_dev,dev_mac_str);
					if(strcmp(Get_Bind_Mac->valuestring,gw_mac_str))
					{
						cJSON_DeleteItemFromObject(gw_mac_dev,dev_mac_str);
						cJSON_AddStringToObject(gw_mac_dev,dev_mac_str,gw_mac_str);
					}
					break;
				}
				while_find = while_find->next;
				if(while_find==NULL)
					cJSON_AddStringToObject(gw_mac_dev,dev_mac_str,gw_mac_str);
			}
		}
	}
	char *send_char = cJSON_PrintUnformatted(gw_mac_dev);
	memset(gw_dev_mac_list,0,10240);
	memcpy(gw_dev_mac_list,send_char,strlen(send_char));
	int gw_mac_dev_fd = open("/root/gw_bin_dev.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(gw_mac_dev_fd,send_char,strlen(send_char));
	fsync(gw_mac_dev_fd);
	close(gw_mac_dev_fd);
	pthread_mutex_unlock(&mutex_gw_dev_mac);
	
	free(gw_mac_str);
	gw_mac_str = NULL;
	free(dev_mac_str);
	dev_mac_str = NULL;
	cJSON_Delete(gw_mac_dev);
	gw_mac_dev = NULL;
	free(send_char);
	send_char = NULL;
}

void gw_bind_self_mac(char *data_str)//绑定主网关mac
{
	char *dev_mac_str = NULL;
	dev_mac_str = (char*)malloc(17);//mac地址
	memset(dev_mac_str,0,17);
	memcpy(dev_mac_str,data_str+4,16);
	dev_mac_str[16]='\0';
	
	pthread_mutex_lock(&mutex_gw_dev_mac);
	cJSON *gw_mac_dev = cJSON_Parse(gw_dev_mac_list);
	if(gw_mac_dev != NULL)
	{
		if(gw_mac_dev->child == NULL)
			cJSON_AddStringToObject(gw_mac_dev,dev_mac_str,my_gw_mac);
		else
		{
			cJSON *while_find = gw_mac_dev->child;
			while(while_find != NULL)
			{
				if(strcmp(dev_mac_str,while_find->string)==0)
				{
					cJSON *Get_Bind_Mac = cJSON_GetObjectItem(gw_mac_dev,dev_mac_str);
					if(strcmp(Get_Bind_Mac->valuestring,my_gw_mac))
					{
						cJSON_DeleteItemFromObject(gw_mac_dev,dev_mac_str);
						cJSON_AddStringToObject(gw_mac_dev,dev_mac_str,my_gw_mac);
					}
					break;
				}
				while_find = while_find->next;
				if(while_find==NULL)
					cJSON_AddStringToObject(gw_mac_dev,dev_mac_str,my_gw_mac);
			}
		}
	}
	char *send_char = cJSON_PrintUnformatted(gw_mac_dev);
	memset(gw_dev_mac_list,0,10240);
	memcpy(gw_dev_mac_list,send_char,strlen(send_char));
	int gw_mac_dev_fd = open("/root/gw_bin_dev.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(gw_mac_dev_fd,send_char,strlen(send_char));
	fsync(gw_mac_dev_fd);
	close(gw_mac_dev_fd);
	pthread_mutex_unlock(&mutex_gw_dev_mac);
	
	free(dev_mac_str);
	dev_mac_str = NULL;
	free(send_char);
	send_char = NULL;
	cJSON_Delete(gw_mac_dev);
	gw_mac_dev = NULL;
}
void delete_gw_bind_mac(char *del_mac)
{
	pthread_mutex_lock(&mutex_gw_dev_mac);
	cJSON *gw_mac_dev = cJSON_Parse(gw_dev_mac_list);
	if(gw_mac_dev != NULL)
	{
		if(gw_mac_dev->child != NULL)
		{
			cJSON *while_find = gw_mac_dev->child;
			while(while_find != NULL)
			{
				if(strcmp(del_mac,while_find->string)==0)
				{
					cJSON_DeleteItemFromObject(gw_mac_dev,del_mac);
					break;
				}
				while_find = while_find->next;
			}
		}
	}
	char *send_char = cJSON_PrintUnformatted(gw_mac_dev);
	memset(gw_dev_mac_list,0,10240);
	memcpy(gw_dev_mac_list,send_char,strlen(send_char));
	int gw_mac_dev_fd = open("/root/gw_bin_dev.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(gw_mac_dev_fd,send_char,strlen(send_char));
	fsync(gw_mac_dev_fd);
	close(gw_mac_dev_fd);
	pthread_mutex_unlock(&mutex_gw_dev_mac);
	cJSON_Delete(gw_mac_dev);
	gw_mac_dev = NULL;
	free(send_char);
	send_char = NULL;
}

void update_gw_bind_mac(void)
{
	typedef struct sign_dev_mac
	{
		cJSON *mac;
		struct sign_dev_mac *next;
	}SIG;
	
	SIG *sig_head,*sig_z,*sig_d,*p;
	sig_head=sig_z=sig_d=p=NULL;
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	if(dev_list_data != NULL && dev_list_data->child != NULL)
	{
		cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
		cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
		int	data_l =  cJSON_GetArraySize(my_dev_list_list);
		cJSON *data_arr_jx = NULL;
		cJSON *tem_mac = NULL;
		int i;
		for(i=0;i<data_l;i++)
		{
			data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
			tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
			if(sig_head==NULL)
			{
				sig_d = (SIG *)malloc(sizeof(SIG));
				memset(sig_d,0,sizeof(SIG));
				sig_d->mac = tem_mac;
				sig_head = sig_z = sig_d;
				sig_d->next = NULL;
			}
			else
			{
				p=sig_head;
				while(p != NULL)
				{
					if(strcmp(tem_mac->valuestring,p->mac->valuestring)==0)
						break;
					p = p->next;
					if(p==NULL)
					{
						sig_d = (SIG *)malloc(sizeof(SIG));
						memset(sig_d,0,sizeof(SIG));
						sig_d->mac = tem_mac;
						sig_z->next = sig_d;
						sig_d->next = NULL;
						sig_z = sig_d;
					}
				}
			}
		}
		if(data_l != 0)
		{
			cJSON *gw_mac_dev = cJSON_Parse(gw_dev_mac_list);
			if(gw_mac_dev != NULL)
			{
				cJSON *while_find = gw_mac_dev->child;
				while(while_find != NULL)
				{
					p = sig_head;
					if( p != NULL)
					{
						while(p != NULL)
						{
							if(strcmp(while_find->string,p->mac->valuestring) == 0)
								break;
							p = p->next;
							if(p == NULL)
								cJSON_DeleteItemFromObject(gw_mac_dev,while_find->string);
						}
					}
					else
					{
						int gw_mac_dev_fd = open("/root/gw_bin_dev.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
						write(gw_mac_dev_fd,"{}",2);
						fsync(gw_mac_dev_fd);
						close(gw_mac_dev_fd);
						memset(gw_dev_mac_list,0,10240);
						memcpy(gw_dev_mac_list,"{}",2);
					}
					while_find = while_find->next;
				}
			}
			char *send_char = cJSON_PrintUnformatted(gw_mac_dev);
			memset(gw_dev_mac_list,0,10240);
			memcpy(gw_dev_mac_list,send_char,strlen(send_char));
			int gw_mac_dev_fd = open("/root/gw_bin_dev.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
			write(gw_mac_dev_fd,send_char,strlen(send_char));
			fsync(gw_mac_dev_fd);
			close(gw_mac_dev_fd);
			free(send_char);
			send_char = NULL;
			cJSON_Delete(gw_mac_dev);
			gw_mac_dev = NULL;
		}
		else
		{
			int gw_mac_dev_fd = open("/root/gw_bin_dev.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
			write(gw_mac_dev_fd,"{}",2);
			fsync(gw_mac_dev_fd);
			close(gw_mac_dev_fd);
			memset(gw_dev_mac_list,0,10240);
			memcpy(gw_dev_mac_list,"{}",2);
		}
	}
	else
	{
		int gw_mac_dev_fd = open("/root/gw_bin_dev.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
		write(gw_mac_dev_fd,"{}",2);
		fsync(gw_mac_dev_fd);
		close(gw_mac_dev_fd);
		memset(gw_dev_mac_list,0,10240);
		memcpy(gw_dev_mac_list,"{}",2);
	}
	cJSON_Delete(dev_list_data);
	dev_list_data = NULL;
	
	while(sig_head != NULL)
	{
		p = sig_head;
		sig_head = sig_head->next;
		free(p);
		p = NULL;
	}
}
/***********************************************************************************************************/

void dev_com_con(cJSON *root)//无内存泄露问题
{
	int kg;
	cJSON *str_data = NULL;
	str_data = cJSON_GetObjectItem(root,"data");// cmc data 层
	cJSON *dev_type_this = NULL;
	dev_type_this = cJSON_GetObjectItem(str_data,"dev_type");//chufashebeileixing
	cJSON *dev_id_this = NULL;
	dev_id_this = cJSON_GetObjectItem(str_data,"dev_id");
	cJSON *dev_list_data = NULL;
	pthread_mutex_lock(&mutex_sl);
	dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child !=NULL)
		{
			cJSON *my_dev_list_data = NULL;
			cJSON *my_dev_list_list = NULL;
			my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr = NULL;
			cJSON *data_for = NULL;
			int i;
			for(i=0;i<data_l;i++)
			{
				data_arr = cJSON_GetArrayItem(my_dev_list_list,i);
				data_for = cJSON_GetObjectItem(data_arr,"dev_id");
				if(strcmp(data_for->valuestring,dev_id_this->valuestring)==0)//找设备id
				{
					cJSON *data_mac = cJSON_GetObjectItem(data_arr,"mac");
					cJSON *data_port = cJSON_GetObjectItem(data_arr,"dev_port");
					cJSON *data_cmd = cJSON_GetObjectItem(str_data,"dev_cmd");
					cJSON *data_dev_cmd = cJSON_GetObjectItem(data_cmd,"cmd");//命令
					int flag_kg=2;
					int len_of_cmd = strlen(data_dev_cmd->valuestring);
					len_of_cmd = len_of_cmd/2;
					if(strcmp(dev_type_this->valuestring,"0D0101")==0) len_of_cmd = 10;
					uint8_t *final_cmd = NULL;
					final_cmd = malloc(15+len_of_cmd);
					memset(final_cmd,0,15+len_of_cmd);
					if(strcmp(dev_type_this->valuestring,"0D0101")==0)
					{
						cmd_mix_lock(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
					}
					else if(strcmp(dev_type_this->valuestring,"010101")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"010102")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"010103")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"010501")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"010104")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"010201")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"010301")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(data_dev_cmd->valuestring[6]=='0' && data_dev_cmd->valuestring[7]=='0')
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"010601")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else if(strcmp(data_dev_cmd->valuestring,"01")==0)
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"040101")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else if(strcmp(data_dev_cmd->valuestring,"01")==0)
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"040102")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else if(strcmp(data_dev_cmd->valuestring,"01")==0)
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"040201")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(strcmp(data_dev_cmd->valuestring,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"040301")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
						if(data_dev_cmd->valuestring[0]=='0' && data_dev_cmd->valuestring[1]=='0')
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(dev_type_this->valuestring,"080301")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
					}
					else if(strcmp(dev_type_this->valuestring,"080401")==0)
					{
						cmd_mix(data_mac->valuestring,data_port->valuestring,data_dev_cmd->valuestring,final_cmd);
						resend_zt(15+len_of_cmd,final_cmd,dev_id_this->valuestring,dev_type_this->valuestring);
						find_mac_and_send(data_mac->valuestring,final_cmd,15+len_of_cmd);
					}
					free(final_cmd);
					final_cmd = NULL;
					if(flag_kg !=2)
					{
						pthread_mutex_lock(&mutex_bl);
						cJSON *multi_bind_data = cJSON_Parse(multi_bind);//遍历多联绑定列表
						pthread_mutex_unlock(&mutex_bl);
						if(multi_bind_data != NULL)
						{
							if(multi_bind_data->child != NULL)
							{
								cJSON *my_multi_bind_data = cJSON_GetObjectItem(multi_bind_data,"data");
								cJSON *my_multi_bind_list = cJSON_GetObjectItem(my_multi_bind_data,"bind_mx_list");
								int	multi_bind_len =  cJSON_GetArraySize(my_multi_bind_list);
								int j=0;
								cJSON *multi_bind_for = NULL;
								cJSON *multi_bind_dev_id = NULL;
								for(j=0;j<multi_bind_len;j++)
								{
									multi_bind_for = cJSON_GetArrayItem(my_multi_bind_list,j);
									multi_bind_dev_id = cJSON_GetObjectItem(multi_bind_for,"dev_id");
									if(strcmp(multi_bind_dev_id->valuestring,data_for->valuestring)==0)//找到设备id
									{
										cJSON *multi_bind_bind_ourid = cJSON_GetObjectItem(multi_bind_for,"bind_id");//共有的绑定id
										int k,m;
										cJSON *multi_bind_bind_id=NULL;
										cJSON *bind_devid=NULL;
										for(k=0;k<multi_bind_len;k++)
										{
											multi_bind_for = cJSON_GetArrayItem(my_multi_bind_list,k);
											multi_bind_bind_id = cJSON_GetObjectItem(multi_bind_for,"bind_id");
											if(strcmp(multi_bind_bind_id->valuestring,multi_bind_bind_ourid->valuestring)==0)//对比bind_id
											{
												bind_devid = cJSON_GetObjectItem(multi_bind_for,"dev_id");
												pthread_mutex_lock(&mutex_sl);
												cJSON *dev_list_dev = cJSON_Parse(device_list);//遍历设备列表
												pthread_mutex_unlock(&mutex_sl);
												if(dev_list_dev != NULL)
												{
													if(dev_list_dev->child != NULL)
													{
														cJSON *dev_list_data_for = cJSON_GetObjectItem(dev_list_dev,"data");
														cJSON *dev_list_list_for = cJSON_GetObjectItem(dev_list_data_for,"dev_list");
														data_l =  cJSON_GetArraySize(dev_list_list_for);
														cJSON *data_arr_for = NULL;
														cJSON *data_mac_for = NULL;
														cJSON *data_port_for = NULL;
														cJSON *data_type_for = NULL;
														cJSON *data_id = NULL;
														for(m=0;m<data_l;m++)
														{
															data_arr_for = cJSON_GetArrayItem(dev_list_list_for,m);
															data_id = cJSON_GetObjectItem(data_arr_for,"dev_id");
															if(strcmp(bind_devid->valuestring,data_for->valuestring)==0)//跳过执行设备
																break;
															else if(strcmp(data_id->valuestring,bind_devid->valuestring)==0)
															{
																data_mac_for = cJSON_GetObjectItem(data_arr_for,"mac");
																data_port_for = cJSON_GetObjectItem(data_arr_for,"dev_port");
																data_type_for = cJSON_GetObjectItem(data_arr_for,"dev_type");
																kg=0;
																if(strcmp(data_type_for->valuestring,"010101")==0)
																	kg=1;
																else if(strcmp(data_type_for->valuestring,"010102")==0)
																	kg=1;
																else if(strcmp(data_type_for->valuestring,"010103")==0)
																	kg=1;
																else if(strcmp(data_type_for->valuestring,"010104")==0)
																	kg=1;
																
																else if(strcmp(data_type_for->valuestring,"010501")==0)
																	kg=1;
																else if(strcmp(data_type_for->valuestring,"010601")==0)
																	kg=1;
																else if(strcmp(data_type_for->valuestring,"040101")==0)
																	kg=1;
																else if(strcmp(data_type_for->valuestring,"040102")==0)
																	kg=1;	
																if(kg==1)//开关类
																{
																	uint8_t *multi_bind_final_cmd = NULL;
																	multi_bind_final_cmd = (uint8_t *)malloc(16);
																	memset(multi_bind_final_cmd,0,16);
																	if(flag_kg==1)
																		cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"01",multi_bind_final_cmd);
																	else if(flag_kg==0)
																		cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"00",multi_bind_final_cmd);
																	resend_zt(16,multi_bind_final_cmd,data_id->valuestring,data_type_for->valuestring);
																	find_mac_and_send(data_mac_for->valuestring,multi_bind_final_cmd,16);
																	free(multi_bind_final_cmd);
																	multi_bind_final_cmd=NULL;
																}
																else if(strcmp(data_type_for->valuestring,"010201")==0)//调光灯
																{
																	uint8_t *multi_bind_final_cmd = NULL;
																	multi_bind_final_cmd = (uint8_t *)malloc(16);
																	memset(multi_bind_final_cmd,0,16);
																	if(flag_kg==1)
																		cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"ff",multi_bind_final_cmd);
																	else if(flag_kg==0)
																		cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"00",multi_bind_final_cmd);
																	resend_zt(16,multi_bind_final_cmd,data_id->valuestring,data_type_for->valuestring);
																	find_mac_and_send(data_mac_for->valuestring,multi_bind_final_cmd,16);
																	free(multi_bind_final_cmd);
																	multi_bind_final_cmd = NULL;
																}
																else if(strcmp(data_type_for->valuestring,"010301")==0)//RGB
																{
																	uint8_t *multi_bind_final_cmd = NULL;
																	multi_bind_final_cmd = (uint8_t *)malloc(19);
																	memset(multi_bind_final_cmd,0,19);
																	pthread_mutex_lock(&mutex_zl);
																	cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
																	pthread_mutex_unlock(&mutex_zl);
																	if(device_state_list_data != NULL)
																	{
																		if(device_state_list_data->child != NULL)
																		{
																			cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
																			cJSON *while_device_state_list_data = my_device_state_list_data->child;
																			if(while_device_state_list_data==NULL)
																			{
																				if(flag_kg == 1)
																				cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"ffffffff",multi_bind_final_cmd);
																				else if(flag_kg == 0)
																				cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"00000000",multi_bind_final_cmd);
																			}
																			else
																			{
																				while(while_device_state_list_data != NULL)
																				{
																					if(strcmp(while_device_state_list_data->string,data_id->valuestring)==0)
																					{
																						cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,data_id->valuestring);
																						cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
																						if(flag_kg == 1)//触发源开
																						{
																							if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
																							{
																								my_dev_state->valuestring[6]='f';
																								my_dev_state->valuestring[7]='f';
																							}
																						}
																						else if(flag_kg == 0)
																						{
																							my_dev_state->valuestring[6]='0';
																							my_dev_state->valuestring[7]='0';
																						}
																						cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,my_dev_state->valuestring,multi_bind_final_cmd);
																						break;
																					}
																					while_device_state_list_data = while_device_state_list_data->next;
																					if(while_device_state_list_data==NULL)
																					{
																						if(flag_kg == 1)
																						cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"ffffffff",multi_bind_final_cmd);
																						else if(flag_kg == 0)
																						cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"00000000",multi_bind_final_cmd);
																					}
																				}
																			}
																		}
																	}
																	
																	if(multi_bind_final_cmd[0] != multi_bind_final_cmd[1])
																	{
																		resend_zt(19,multi_bind_final_cmd,data_id->valuestring,data_type_for->valuestring);
																		find_mac_and_send(data_mac_for->valuestring,multi_bind_final_cmd,19);
																	}
																	cJSON_Delete(device_state_list_data);
																	device_state_list_data=NULL;
																	free(multi_bind_final_cmd);
																	multi_bind_final_cmd = NULL;
																}
																else if(strcmp(data_type_for->valuestring,"040201")==0)//百分比窗帘
																{
																	uint8_t *multi_bind_final_cmd = NULL;
																	multi_bind_final_cmd = (uint8_t *)malloc(16);
																	memset(multi_bind_final_cmd,0,16);
																	if(flag_kg==1)//触发源开
																	cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"64",multi_bind_final_cmd);
																	else if(flag_kg==0)
																	cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"00",multi_bind_final_cmd);
																	resend_zt(16,multi_bind_final_cmd,data_id->valuestring,data_type_for->valuestring);
																	find_mac_and_send(data_mac_for->valuestring,multi_bind_final_cmd,16);
																	free(multi_bind_final_cmd);
																	multi_bind_final_cmd = NULL;
																}
																else if(strcmp(data_type_for->valuestring,"040301")==0)//百叶窗帘
																{
																	uint8_t *multi_bind_final_cmd = NULL;
																	multi_bind_final_cmd = (uint8_t *)malloc(17);
																	memset(multi_bind_final_cmd,0,17);
																	if(flag_kg==1)//触发源开
																	cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"6464",multi_bind_final_cmd);
																	else if(flag_kg==0)
																	cmd_mix(data_mac_for->valuestring,data_port_for->valuestring,"0000",multi_bind_final_cmd);
																	resend_zt(17,multi_bind_final_cmd,data_id->valuestring,data_type_for->valuestring);
																	find_mac_and_send(data_mac_for->valuestring,multi_bind_final_cmd,17);
																	free(multi_bind_final_cmd);
																	multi_bind_final_cmd=NULL;
																}
																usleep(200000);
																break;
															}
														}
													}
												}
												cJSON_Delete(dev_list_dev);
												dev_list_dev=NULL;
											}
										}
										break;
									}
								}
							}
						}
						cJSON_Delete(multi_bind_data);
						multi_bind_data= NULL;
					}
					break;
				}
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
}
void dev_room_con(cJSON *root)//无内存泄露问题
{
	cJSON *room_cmd_data = cJSON_GetObjectItem(root,"data");//data 层
	cJSON *room_cmd_cmd = cJSON_GetObjectItem(room_cmd_data,"cmd");//取出命令
	cJSON *room_dev_id_list = cJSON_GetObjectItem(room_cmd_data,"dev_id_list");//get id
	int id_num = cJSON_GetArraySize(room_dev_id_list);
	int id_i,data_l,i,kg;
	cJSON *id_for = NULL;
	cJSON *my_dev_list_data = NULL;
	cJSON *my_dev_list_list = NULL;
	cJSON *data_arr = NULL;
	cJSON *data_id = NULL;
	cJSON *data_mac = NULL;
	cJSON *data_port= NULL;
	cJSON *data_type = NULL;
	for(id_i=0;id_i<id_num;id_i++)
	{
		id_for = cJSON_GetArrayItem(room_dev_id_list,id_i);
		pthread_mutex_lock(&mutex_sl);
		cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
		pthread_mutex_unlock(&mutex_sl);
		if(dev_list_data != NULL)
		{
			if(dev_list_data->child !=NULL)
			{
				my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
				my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
				data_l =  cJSON_GetArraySize(my_dev_list_list);
				for(i=0;i<data_l;i++)
				{
					data_arr = cJSON_GetArrayItem(my_dev_list_list,i);
					data_id = cJSON_GetObjectItem(data_arr,"dev_id");
					if(strcmp(data_id->valuestring,id_for->valuestring)==0)
					{
						data_mac = cJSON_GetObjectItem(data_arr,"mac");
						data_port = cJSON_GetObjectItem(data_arr,"dev_port");
						data_type = cJSON_GetObjectItem(data_arr,"dev_type");
						kg=0;
						if(strcmp(data_type->valuestring,"010101")==0)
							kg=1;
						else if(strcmp(data_type->valuestring,"010102")==0)
							kg=1;
						else if(strcmp(data_type->valuestring,"010103")==0)
							kg=1;
						else if(strcmp(data_type->valuestring,"010104")==0)
							kg=1;
						else if(strcmp(data_type->valuestring,"040101")==0)
							kg=1;
						else if(strcmp(data_type->valuestring,"010501")==0)
							kg=1;
						else if(strcmp(data_type->valuestring,"010601")==0)
							kg=1;
						else if(strcmp(data_type->valuestring,"040102")==0)
							kg=1;
						if(strcmp(room_cmd_cmd->valuestring,"1")==0)//全开
						{
							if(kg==1)//开关类型
							{
								uint8_t *final_cmd_of_switch = NULL;
								final_cmd_of_switch = (uint8_t *)malloc(16);
								memset(final_cmd_of_switch,0,16);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"01",final_cmd_of_switch);
								resend_zt(16,final_cmd_of_switch,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_switch,16);
								free(final_cmd_of_switch);
								final_cmd_of_switch = NULL;
								usleep(500000);
							}
							else if(strcmp(data_type->valuestring,"010201")==0)//调光灯
							{
								uint8_t *final_cmd_of_tgd = NULL;
								final_cmd_of_tgd = (uint8_t *)malloc(16);
								memset(final_cmd_of_tgd,0,16);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"ff",final_cmd_of_tgd);
								resend_zt(16,final_cmd_of_tgd,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_tgd,16);
								free(final_cmd_of_tgd);
								final_cmd_of_tgd = NULL;
								usleep(200000);
							}
							else if(strcmp(data_type->valuestring,"010301")==0)//RGB
							{
								uint8_t *final_cmd_of_rgb = NULL;
								final_cmd_of_rgb = (uint8_t *)malloc(19);
								memset(final_cmd_of_rgb,0,19);
								pthread_mutex_lock(&mutex_zl);
								cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
								pthread_mutex_unlock(&mutex_zl);
								if(device_state_list_data != NULL)
								{
									if(device_state_list_data->child != NULL)
									{
										cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
										cJSON *while_device_state_list_data = my_device_state_list_data->child;
										if(while_device_state_list_data==NULL)
										{
											cmd_mix(data_mac->valuestring,data_port->valuestring,"ffffffff",final_cmd_of_rgb);
										}
										else
										{
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(while_device_state_list_data->string,data_id->valuestring)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,data_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
													{
														my_dev_state->valuestring[6]='f';
														my_dev_state->valuestring[7]='f';
														cmd_mix(data_mac->valuestring,data_port->valuestring,my_dev_state->valuestring,final_cmd_of_rgb);
													}
													else
													cmd_mix(data_mac->valuestring,data_port->valuestring,my_dev_state->valuestring,final_cmd_of_rgb);
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
												if(while_device_state_list_data==NULL)
												cmd_mix(data_mac->valuestring,data_port->valuestring,"ffffffff",final_cmd_of_rgb);
											}
										}
									}
								}
								if(final_cmd_of_rgb[0] != final_cmd_of_rgb[1])
								{
									resend_zt(19,final_cmd_of_rgb,data_id->valuestring,data_type->valuestring);
									find_mac_and_send(data_mac->valuestring,final_cmd_of_rgb,19);
								}
								cJSON_Delete(device_state_list_data);
								device_state_list_data=NULL;
								free(final_cmd_of_rgb);
								final_cmd_of_rgb = NULL;
								usleep(200000);
							}
							else if(strcmp(data_type->valuestring,"040201")==0)//百分比窗帘
							{
								uint8_t *final_cmd_of_percen_cl = NULL;
								final_cmd_of_percen_cl = (uint8_t *)malloc(16);
								memset(final_cmd_of_percen_cl,0,16);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"64",final_cmd_of_percen_cl);
								resend_zt(16,final_cmd_of_percen_cl,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_percen_cl,16);
								free(final_cmd_of_percen_cl);
								final_cmd_of_percen_cl = NULL;
								usleep(200000);
							}
							else if(strcmp(data_type->valuestring,"040301")==0)//百叶窗窗帘
							{
								uint8_t *final_cmd_of_blind_cl = NULL;
								final_cmd_of_blind_cl = (uint8_t *)malloc(17);
								memset(final_cmd_of_blind_cl,0,17);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"6464",final_cmd_of_blind_cl);
								resend_zt(17,final_cmd_of_blind_cl,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_blind_cl,17);
								free(final_cmd_of_blind_cl);
								final_cmd_of_blind_cl = NULL;
								usleep(200000);
							}
						}
						if(strcmp(room_cmd_cmd->valuestring,"0")==0)//全关
						{
							if(kg==1)//墙壁开关类型
							{
								uint8_t *final_cmd_of_switch = NULL;
								final_cmd_of_switch = (uint8_t *)malloc(16);
								memset(final_cmd_of_switch,0,16);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"00",final_cmd_of_switch);
								resend_zt(16,final_cmd_of_switch,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_switch,16);
								free(final_cmd_of_switch);
								final_cmd_of_switch = NULL;
								usleep(500000);
							}
							else if(strcmp(data_type->valuestring,"010201")==0)//调光灯
							{
								uint8_t *final_cmd_of_tgd = NULL;
								final_cmd_of_tgd = (uint8_t *)malloc(16);
								memset(final_cmd_of_tgd,0,16);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"00",final_cmd_of_tgd);
								resend_zt(16,final_cmd_of_tgd,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_tgd,16);
								free(final_cmd_of_tgd);
								final_cmd_of_tgd = NULL;
								usleep(200000);
							}
							else if(strcmp(data_type->valuestring,"010301")==0)//RGB
							{
								uint8_t *final_cmd_of_rgb = NULL;
								final_cmd_of_rgb = (uint8_t *)malloc(19);
								memset(final_cmd_of_rgb,0,19);
								pthread_mutex_lock(&mutex_zl);
								cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
								pthread_mutex_unlock(&mutex_zl);
								if(device_state_list_data != NULL)
								{
									if(device_state_list_data->child != NULL)
									{
										cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
										cJSON *while_device_state_list_data = my_device_state_list_data->child;
										if(while_device_state_list_data==NULL)
										{
											cmd_mix(data_mac->valuestring,data_port->valuestring,"00000000",final_cmd_of_rgb);
										}
										else
										{
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(while_device_state_list_data->string,data_id->valuestring)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,data_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
													{
														cmd_mix(data_mac->valuestring,data_port->valuestring,my_dev_state->valuestring,final_cmd_of_rgb);
													}
													else
													{
														my_dev_state->valuestring[6]='0';
														my_dev_state->valuestring[7]='0';
														cmd_mix(data_mac->valuestring,data_port->valuestring,my_dev_state->valuestring,final_cmd_of_rgb);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
												if(while_device_state_list_data==NULL)
												cmd_mix(data_mac->valuestring,data_port->valuestring,"00000000",final_cmd_of_rgb);
											}
										}
									}
								}
								if(final_cmd_of_rgb[0] != final_cmd_of_rgb[1])
								{
									resend_zt(19,final_cmd_of_rgb,data_id->valuestring,data_type->valuestring);
									find_mac_and_send(data_mac->valuestring,final_cmd_of_rgb,19);
								}
								cJSON_Delete(device_state_list_data);
								device_state_list_data=NULL;
								free(final_cmd_of_rgb);
								final_cmd_of_rgb = NULL;
								usleep(200000);
							}
							else if(strcmp(data_type->valuestring,"040201")==0)//百分比窗帘
							{
								uint8_t *final_cmd_of_percen_cl = NULL;
								final_cmd_of_percen_cl = (uint8_t *)malloc(16);
								memset(final_cmd_of_percen_cl,0,16);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"00",final_cmd_of_percen_cl);
								resend_zt(16,final_cmd_of_percen_cl,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_percen_cl,16);
								free(final_cmd_of_percen_cl);
								final_cmd_of_percen_cl = NULL;
								usleep(200000);
							}
							else if(strcmp(data_type->valuestring,"040301")==0)//百叶窗窗帘
							{
								uint8_t *final_cmd_of_blind_cl = NULL;
								final_cmd_of_blind_cl = (uint8_t *)malloc(17);
								memset(final_cmd_of_blind_cl,0,17);
								cmd_mix(data_mac->valuestring,data_port->valuestring,"0000",final_cmd_of_blind_cl);
								resend_zt(17,final_cmd_of_blind_cl,data_id->valuestring,data_type->valuestring);
								find_mac_and_send(data_mac->valuestring,final_cmd_of_blind_cl,17);
								free(final_cmd_of_blind_cl);
								final_cmd_of_blind_cl = NULL;
								usleep(200000);
							}
						}
						break;
					}
				}
			}
		}
		cJSON_Delete(dev_list_data);
		dev_list_data=NULL;
	}
}
void voice_open(cJSON *data_arr_jx,char *Voice_CMD)
{
	int class = 0;
	cJSON *tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
	cJSON *tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
	cJSON *tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
	cJSON *tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
	if(!strcmp(tem_type->valuestring,"010101"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010102"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010103"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010104"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010201"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010501"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010601"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040101"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040102"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040201"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040301"))//二字节命令为2
	class=2;
	else if(!strcmp(tem_type->valuestring,"010301"))//四字节命令为3
	class=3;
	else if(!strcmp(tem_type->valuestring,"050101"))//空调为4
	class=4;
	else if(!strcmp(tem_type->valuestring,"050201"))//电视遥控器
	class=5;
	else if(!strcmp(tem_type->valuestring,"050202"))
	class=5;
	else if(!strcmp(tem_type->valuestring,"050203"))
	class=5;
	else if(!strcmp(tem_type->valuestring,"050204"))
	class=5;
	else if(!strcmp(tem_type->valuestring,"050205"))
	class=5;
	else if(!strcmp(tem_type->valuestring,"080401"))//中央空调
	class=6;
	else if(!strcmp(tem_type->valuestring,"080301"))//温控器
	class=7;
	if(class==1)
	{
		uint8_t final_cmd[16];
		memset(final_cmd,0,16);
		if(!strcmp(tem_type->valuestring,"010201"))//tgd
		{
			uint8_t num_str = judge_number(Voice_CMD);
			if( num_str == 255 )
				cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff",final_cmd);
			else
			{
				num_str = num_str*25.5/10;
				if(num_str >= 255)
				cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff",final_cmd);
				else
				{
					char cmd_str[3];
					memset(cmd_str,0,3);
					hex_to_str(&num_str,cmd_str,1);
					cmd_str[2]='\0';
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,cmd_str,final_cmd);
				}
			}
		}
		else if(!strcmp(tem_type->valuestring,"040201"))//bfbcl
		{
			uint8_t num_str = judge_number(Voice_CMD);
			if( num_str == 255 )
				cmd_mix(tem_mac->valuestring,tem_port->valuestring,"64",final_cmd);
			else
			{
				char cmd_str[3];
				memset(cmd_str,0,3);
				hex_to_str(&num_str,cmd_str,1);
				cmd_str[2]='\0';
				cmd_mix(tem_mac->valuestring,tem_port->valuestring,cmd_str,final_cmd);
			}
		}
		else
		cmd_mix(tem_mac->valuestring,tem_port->valuestring,"01",final_cmd);
		resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
		find_mac_and_send(tem_mac->valuestring,final_cmd,16);
		usleep(200000);
	}
	else if(class==2)
	{
		uint8_t final_cmd[17];
		memset(final_cmd,0,17);
		cmd_mix(tem_mac->valuestring,tem_port->valuestring,"6464",final_cmd);
		resend_zt(17,final_cmd,tem_id->valuestring,tem_type->valuestring);
		find_mac_and_send(tem_mac->valuestring,final_cmd,17);
		usleep(200000);
	}
	else if(class==3)
	{
		uint8_t final_cmd[19];
		memset(final_cmd,0,19);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					if(strstr(Voice_CMD,"红色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff0000ff",final_cmd);
					else if(strstr(Voice_CMD,"橙色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff7d00ff",final_cmd);
					else if(strstr(Voice_CMD,"黄色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffff00ff",final_cmd);
					else if(strstr(Voice_CMD,"绿色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ff00ff",final_cmd);
					else if(strstr(Voice_CMD,"青色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ffffff",final_cmd);
					else if(strstr(Voice_CMD,"蓝色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0000ffff",final_cmd);
					else if(strstr(Voice_CMD,"紫色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff00ffff",final_cmd);
					else if(strstr(Voice_CMD,"黑色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000000ff",final_cmd);
					else
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffffffff",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
							{
								my_dev_state->valuestring[6]='f';
								my_dev_state->valuestring[7]='f';
								if(strstr(Voice_CMD,"红色"))
								memcpy(my_dev_state->valuestring,"ff0000",6);
								else if(strstr(Voice_CMD,"橙色"))
								memcpy(my_dev_state->valuestring,"ff7d00",6);
								else if(strstr(Voice_CMD,"黄色"))
								memcpy(my_dev_state->valuestring,"ffff00",6);
								else if(strstr(Voice_CMD,"绿色"))
								memcpy(my_dev_state->valuestring,"00ff00",6);
								else if(strstr(Voice_CMD,"青色"))
								memcpy(my_dev_state->valuestring,"00ffff",6);
								else if(strstr(Voice_CMD,"蓝色"))
								memcpy(my_dev_state->valuestring,"0000ff",6);
								else if(strstr(Voice_CMD,"紫色"))
								memcpy(my_dev_state->valuestring,"ff00ff",6);
								else if(strstr(Voice_CMD,"黑色"))
								memcpy(my_dev_state->valuestring,"000000",6);
								cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							}
							else
							{
								if(strstr(Voice_CMD,"红色"))
								memcpy(my_dev_state->valuestring,"ff0000",6);
								else if(strstr(Voice_CMD,"橙色"))
								memcpy(my_dev_state->valuestring,"ff7d00",6);
								else if(strstr(Voice_CMD,"黄色"))
								memcpy(my_dev_state->valuestring,"ffff00",6);
								else if(strstr(Voice_CMD,"绿色"))
								memcpy(my_dev_state->valuestring,"00ff00",6);
								else if(strstr(Voice_CMD,"青色"))
								memcpy(my_dev_state->valuestring,"00ffff",6);
								else if(strstr(Voice_CMD,"蓝色"))
								memcpy(my_dev_state->valuestring,"0000ff",6);
								else if(strstr(Voice_CMD,"紫色"))
								memcpy(my_dev_state->valuestring,"ff00ff",6);
								else if(strstr(Voice_CMD,"黑色"))
								memcpy(my_dev_state->valuestring,"000000",6);
								cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							}
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							if(strstr(Voice_CMD,"红色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff0000ff",final_cmd);
							else if(strstr(Voice_CMD,"橙色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff7d00ff",final_cmd);
							else if(strstr(Voice_CMD,"黄色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffff00ff",final_cmd);
							else if(strstr(Voice_CMD,"绿色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ff00ff",final_cmd);
							else if(strstr(Voice_CMD,"青色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ffffff",final_cmd);
							else if(strstr(Voice_CMD,"蓝色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0000ffff",final_cmd);
							else if(strstr(Voice_CMD,"紫色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff00ffff",final_cmd);
							else if(strstr(Voice_CMD,"黑色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000000ff",final_cmd);
							else
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffffffff",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(19,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,19);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
		usleep(200000);
	}
	else if(class==4)
	{
		cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
		int str_len = strlen(tem_lid->valuestring);
		if(str_len)
		{
			pthread_mutex_lock(&mutex_code);
			cJSON *code_id_root = cJSON_Parse(code_id);
			pthread_mutex_unlock(&mutex_code);
			if(code_id_root != NULL)
			{
				if(code_id_root->child != NULL)
				{
					cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
					if(kt_root != NULL)
					{
						cJSON *kt_while = kt_root->child;
						if(kt_while==NULL && NET_FLAG)
						{
							cJSON *hw_request_root = cJSON_CreateObject();
							cJSON_AddStringToObject(hw_request_root,"co","orange");
							cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
							cJSON *hw_request_data = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
							cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
							cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
							cJSON *hw_request_cmd = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
							cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201010102");
							char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
							int my_len = strlen(hw_request_char);
							char *my_send_char = (char *)malloc(my_len+2);
							memset(my_send_char,0,my_len+2);
							memcpy(my_send_char,hw_request_char,my_len);
							strcat(my_send_char,"\n\0");
							send(cd,my_send_char,my_len+1,0);
							cJSON_Delete(hw_request_root);
							hw_request_root = NULL;
							free(hw_request_char);
							hw_request_char = NULL;
							free(my_send_char);
							my_send_char=NULL;
						}
						else
						{
							while(kt_while != NULL)
							{
								if(strcmp(kt_while->string,tem_lid->valuestring)==0)
								{
									cJSON *my_hw_lid = cJSON_GetObjectItem(kt_root,tem_lid->valuestring);
									cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"code");
									str_len = strlen(my_code->valuestring)+56;
									uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
									memset(final_cmd,0,str_len/2);
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											if(while_device_state_list_data==NULL)
											cmd_mix_kt(tem_lid->valuestring,"1a010201010102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
											else
											{
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
													{
														cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														my_dev_state->valuestring[8] = '0';
														my_dev_state->valuestring[9] = '1';
														cmd_mix_kt(tem_lid->valuestring,my_dev_state->valuestring,my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
														break;
													}
													while_device_state_list_data=while_device_state_list_data->next;
													if(while_device_state_list_data==NULL)
													cmd_mix_kt(tem_lid->valuestring,"1a010201010102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
												}
											}
										}
									}
									find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
									cJSON_Delete(device_state_list_data);
									device_state_list_data=NULL;
									free(final_cmd);
									final_cmd = NULL;
									usleep(200000);
									break;
								}
								kt_while = kt_while->next;
								if(kt_while==NULL && NET_FLAG)
								{
									cJSON *hw_request_root = cJSON_CreateObject();
									cJSON_AddStringToObject(hw_request_root,"co","orange");
									cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
									cJSON *hw_request_data = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
									cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
									cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
									cJSON *hw_request_cmd = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
									cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201010102");
									char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
									int my_len = strlen(hw_request_char);
									char *my_send_char = (char *)malloc(my_len+2);
									memset(my_send_char,0,my_len+2);
									memcpy(my_send_char,hw_request_char,my_len);
									strcat(my_send_char,"\n\0");
									send(cd,my_send_char,my_len+1,0);
									cJSON_Delete(hw_request_root);
									hw_request_root = NULL;
									free(hw_request_char);
									hw_request_char = NULL;
									free(my_send_char);
									my_send_char=NULL;
								}
							}
						}
					}
				}
			}
			cJSON_Delete(code_id_root);
			code_id_root=NULL;
		}
	}
	else if(class==5)
	{
		cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
		int str_len = strlen(tem_lid->valuestring);
		if(str_len)
		{
			pthread_mutex_lock(&mutex_code);
			cJSON *code_id_root = cJSON_Parse(code_id);
			pthread_mutex_unlock(&mutex_code);
			if(code_id_root != NULL)
			{
				if(code_id_root->child != NULL)
				{
					cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
					if(fkt_root!=NULL)
					{
						cJSON *fkt_while = fkt_root->child;
						if(fkt_while==NULL && NET_FLAG)
						{
							cJSON *hw_request_root = cJSON_CreateObject();
							cJSON_AddStringToObject(hw_request_root,"co","orange");
							cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
							cJSON *hw_request_data = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
							cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
							cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
							cJSON *hw_request_cmd = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
							cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
							char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
							int my_len = strlen(hw_request_char);
							char *my_send_char = (char *)malloc(my_len+2);
							memset(my_send_char,0,my_len+2);
							memcpy(my_send_char,hw_request_char,my_len);
							strcat(my_send_char,"\n\0");
							send(cd,my_send_char,my_len+1,0);
							cJSON_Delete(hw_request_root);
							hw_request_root = NULL;
							free(hw_request_char);
							hw_request_char = NULL;
							free(my_send_char);
							my_send_char=NULL;
						}
						else
						{
							while(fkt_while != NULL)
							{
								if(strcmp(fkt_while->string,tem_lid->valuestring)==0)//先找码库id
								{
									cJSON *my_hw_lid = cJSON_GetObjectItem(fkt_root,tem_lid->valuestring);
									cJSON *my_hw_lid_while = my_hw_lid->child;
									while(my_hw_lid_while != NULL)
									{
										if(strcmp(my_hw_lid_while->string,"on_off")==0)//再找键值
										{
											cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"on_off");
											int str_len = strlen(my_code->valuestring)+30;
											uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
											memset(final_cmd,0,str_len/2);
											cmd_mix_fkt(my_code->valuestring,tem_mac->valuestring,str_len,final_cmd);
											find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
											free(final_cmd);
											final_cmd=NULL;
											break;
										}
										my_hw_lid_while = my_hw_lid_while->next;
										if(my_hw_lid_while == NULL && NET_FLAG)
										{
											cJSON *hw_request_root = cJSON_CreateObject();
											cJSON_AddStringToObject(hw_request_root,"co","orange");
											cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
											cJSON *hw_request_data = cJSON_CreateObject();
											cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
											cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
											cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
											cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
											cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
											cJSON *hw_request_cmd = cJSON_CreateObject();
											cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
											cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
											char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
											int my_len = strlen(hw_request_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,hw_request_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											cJSON_Delete(hw_request_root);
											hw_request_root = NULL;
											free(hw_request_char);
											hw_request_char = NULL;
											free(my_send_char);
											my_send_char=NULL;
										}
									}
									break;
								}
								fkt_while = fkt_while->next;
								if(fkt_while==NULL && NET_FLAG)
								{
									cJSON *hw_request_root = cJSON_CreateObject();
									cJSON_AddStringToObject(hw_request_root,"co","orange");
									cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
									cJSON *hw_request_data = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
									cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
									cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
									cJSON *hw_request_cmd = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
									cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
									char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
									int my_len = strlen(hw_request_char);
									char *my_send_char = (char *)malloc(my_len+2);
									memset(my_send_char,0,my_len+2);
									memcpy(my_send_char,hw_request_char,my_len);
									strcat(my_send_char,"\n\0");
									send(cd,my_send_char,my_len+1,0);
									cJSON_Delete(hw_request_root);
									hw_request_root = NULL;
									free(hw_request_char);
									hw_request_char = NULL;
									free(my_send_char);
									my_send_char=NULL;
								}
							}
						}
					}
				}
			}
			cJSON_Delete(code_id_root);
			code_id_root=NULL;
		}
	}
	else if(class == 6)
	{
		uint8_t final_cmd[25];
		memset(final_cmd,0,25);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000100010003001a0000",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							my_dev_state->valuestring[3] = '1';
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000100010003001a0000",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(25,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,25);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
	}
	else if(class == 7)
	{
		uint8_t final_cmd[20];
		memset(final_cmd,0,20);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0101011a00",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							my_dev_state->valuestring[1] = '1';
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0101011a00",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(20,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,20);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
	}
}
void voice_close(cJSON *data_arr_jx)
{
	int class=0;
	cJSON *tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
	cJSON *tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
	cJSON *tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
	cJSON *tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
	if(!strcmp(tem_type->valuestring,"010101"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010102"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010103"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010104"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010201"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010501"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"010601"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040101"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040102"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040201"))//一字节命令为1
	class=1;
	else if(!strcmp(tem_type->valuestring,"040301"))//bycl
	class=2;
	else if(!strcmp(tem_type->valuestring,"010301"))//rgb
	class=3;
	else if(!strcmp(tem_type->valuestring,"050101"))//kt
	class=4;
	else if(!strcmp(tem_type->valuestring,"050201"))//电视遥控器
	class=5;
	else if(!strcmp(tem_type->valuestring,"050202"))//
	class=5;
	else if(!strcmp(tem_type->valuestring,"050203"))//
	class=5;
	else if(!strcmp(tem_type->valuestring,"050204"))//
	class=5;
	else if(!strcmp(tem_type->valuestring,"050205"))//
	class=5;
	else if(!strcmp(tem_type->valuestring,"080401"))//中央空调
	class=6;
	else if(!strcmp(tem_type->valuestring,"080301"))//温控器
	class=7;
	if(class == 2)//bycl
	{
		uint8_t final_cmd[17];
		memset(final_cmd,0,17);
		cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0000",final_cmd);
		resend_zt(17,final_cmd,tem_id->valuestring,tem_type->valuestring);
		find_mac_and_send(tem_mac->valuestring,final_cmd,17);
		usleep(200000);
	}
	else if(class == 3)//rgb
	{
		uint8_t final_cmd[19];
		memset(final_cmd,0,19);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00000000",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							else
							{
								my_dev_state->valuestring[6]='0';
								my_dev_state->valuestring[7]='0';
								cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							}
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00000000",final_cmd);
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(19,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,19);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
		usleep(200000);
	}
	else if(class == 4)//空调
	{
		cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
		int str_len = strlen(tem_lid->valuestring);
		if(str_len)
		{
			pthread_mutex_lock(&mutex_code);
			cJSON *code_id_root = cJSON_Parse(code_id);
			pthread_mutex_unlock(&mutex_code);
			if(code_id_root != NULL)
			{
				if(code_id_root->child != NULL)
				{
					cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
					if(kt_root != NULL)
					{
						cJSON *kt_while = kt_root->child;
						if(kt_while==NULL && NET_FLAG)
						{
							cJSON *hw_request_root = cJSON_CreateObject();
							cJSON_AddStringToObject(hw_request_root,"co","orange");
							cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
							cJSON *hw_request_data = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
							cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
							cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
							cJSON *hw_request_cmd = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
							cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201000102");
							char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
							int my_len = strlen(hw_request_char);
							char *my_send_char = (char *)malloc(my_len+2);
							memset(my_send_char,0,my_len+2);
							memcpy(my_send_char,hw_request_char,my_len);
							strcat(my_send_char,"\n\0");
							send(cd,my_send_char,my_len+1,0);
							cJSON_Delete(hw_request_root);
							hw_request_root = NULL;
							free(hw_request_char);
							hw_request_char = NULL;
							free(my_send_char);
							my_send_char=NULL;
						}
						else
						{
							while(kt_while != NULL)
							{
								if(strcmp(kt_while->string,tem_lid->valuestring)==0)
								{
									cJSON *my_hw_lid = cJSON_GetObjectItem(kt_root,tem_lid->valuestring);
									cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"code");
									int str_len = strlen(my_code->valuestring)+56;
									uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
									memset(final_cmd,0,str_len/2);
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											if(while_device_state_list_data==NULL)
											cmd_mix_kt(tem_lid->valuestring,"1a010201000102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
											else
											{
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
													{
														cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														my_dev_state->valuestring[8] = '0';
														my_dev_state->valuestring[9] = '0';
														cmd_mix_kt(tem_lid->valuestring,my_dev_state->valuestring,my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
														break;
													}
													while_device_state_list_data=while_device_state_list_data->next;
													if(while_device_state_list_data==NULL)
													cmd_mix_kt(tem_lid->valuestring,"1a010201000102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
												}
											}
										}
									}
									find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
									cJSON_Delete(device_state_list_data);
									device_state_list_data=NULL;
									free(final_cmd);
									final_cmd = NULL;
									usleep(200000);
									break;
								}
								kt_while = kt_while->next;
								if(kt_while==NULL && NET_FLAG)
								{
									cJSON *hw_request_root = cJSON_CreateObject();
									cJSON_AddStringToObject(hw_request_root,"co","orange");
									cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
									cJSON *hw_request_data = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
									cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
									cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
									cJSON *hw_request_cmd = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
									cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201000102");
									char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
									int my_len = strlen(hw_request_char);
									char *my_send_char = (char *)malloc(my_len+2);
									memset(my_send_char,0,my_len+2);
									memcpy(my_send_char,hw_request_char,my_len);
									strcat(my_send_char,"\n\0");
									send(cd,my_send_char,my_len+1,0);
									cJSON_Delete(hw_request_root);
									hw_request_root = NULL;
									free(hw_request_char);
									hw_request_char = NULL;
									free(my_send_char);
									my_send_char=NULL;
								}
							}
						}
					}
				}
			}
			cJSON_Delete(code_id_root);
			code_id_root=NULL;
		}
	}
	else if(class == 5)//电视
	{
		cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
		int str_len = strlen(tem_lid->valuestring);
		if(str_len)
		{
			pthread_mutex_lock(&mutex_code);
			cJSON *code_id_root = cJSON_Parse(code_id);
			pthread_mutex_unlock(&mutex_code);
			if(code_id_root != NULL)
			{
				if(code_id_root->child != NULL)
				{
					cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
					if(fkt_root!=NULL)
					{
						cJSON *fkt_while = fkt_root->child;
						if(fkt_while==NULL && NET_FLAG)
						{
							cJSON *hw_request_root = cJSON_CreateObject();
							cJSON_AddStringToObject(hw_request_root,"co","orange");
							cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
							cJSON *hw_request_data = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
							cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
							cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
							cJSON *hw_request_cmd = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
							cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
							char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
							int my_len = strlen(hw_request_char);
							char *my_send_char = (char *)malloc(my_len+2);
							memset(my_send_char,0,my_len+2);
							memcpy(my_send_char,hw_request_char,my_len);
							strcat(my_send_char,"\n\0");
							send(cd,my_send_char,my_len+1,0);
							cJSON_Delete(hw_request_root);
							hw_request_root = NULL;
							free(hw_request_char);
							hw_request_char = NULL;
							free(my_send_char);
							my_send_char=NULL;
						}
						else
						{
							while(fkt_while != NULL)
							{
								if(strcmp(fkt_while->string,tem_lid->valuestring)==0)//先找码库id
								{
									cJSON *my_hw_lid = cJSON_GetObjectItem(fkt_root,tem_lid->valuestring);
									cJSON *my_hw_lid_while = my_hw_lid->child;
									while(my_hw_lid_while != NULL)
									{
										if(strcmp(my_hw_lid_while->string,"on_off")==0)//再找键值
										{
											cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"on_off");
											int str_len = strlen(my_code->valuestring)+30;
											uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
											memset(final_cmd,0,str_len/2);
											cmd_mix_fkt(my_code->valuestring,tem_mac->valuestring,str_len,final_cmd);
											find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
											free(final_cmd);
											final_cmd=NULL;
											break;
										}
										my_hw_lid_while = my_hw_lid_while->next;
										if(my_hw_lid_while == NULL && NET_FLAG)
										{
											cJSON *hw_request_root = cJSON_CreateObject();
											cJSON_AddStringToObject(hw_request_root,"co","orange");
											cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
											cJSON *hw_request_data = cJSON_CreateObject();
											cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
											cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
											cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
											cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
											cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
											cJSON *hw_request_cmd = cJSON_CreateObject();
											cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
											cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
											char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
											int my_len = strlen(hw_request_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,hw_request_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											cJSON_Delete(hw_request_root);
											hw_request_root = NULL;
											free(hw_request_char);
											hw_request_char = NULL;
											free(my_send_char);
											my_send_char=NULL;
										}
									}
									break;
								}
								fkt_while = fkt_while->next;
								if(fkt_while==NULL && NET_FLAG)
								{
									cJSON *hw_request_root = cJSON_CreateObject();
									cJSON_AddStringToObject(hw_request_root,"co","orange");
									cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
									cJSON *hw_request_data = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
									cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
									cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
									cJSON *hw_request_cmd = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
									cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
									char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
									int my_len = strlen(hw_request_char);
									char *my_send_char = (char *)malloc(my_len+2);
									memset(my_send_char,0,my_len+2);
									memcpy(my_send_char,hw_request_char,my_len);
									strcat(my_send_char,"\n\0");
									send(cd,my_send_char,my_len+1,0);
									cJSON_Delete(hw_request_root);
									hw_request_root = NULL;
									free(hw_request_char);
									hw_request_char = NULL;
									free(my_send_char);
									my_send_char=NULL;
								}
							}
						}
					}
				}
			}
			cJSON_Delete(code_id_root);
			code_id_root=NULL;
		}
	}
	else if(class == 6)
	{
		uint8_t final_cmd[25];
		memset(final_cmd,0,25);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000000010003001a0000",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							my_dev_state->valuestring[3] = '0';
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000000010003001a0000",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(25,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,25);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
	}
	else if(class == 7)
	{
		uint8_t final_cmd[20];
		memset(final_cmd,0,20);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0001011a00",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							my_dev_state->valuestring[1] = '0';
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0001011a00",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(20,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,20);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
	}
	else if(class==1)
	{
		uint8_t final_cmd[16];
		memset(final_cmd,0,16);
		cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
		resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
		find_mac_and_send(tem_mac->valuestring,final_cmd,16);
		usleep(200000);
	}
}
void voice_judge(cJSON *data_arr_jx,char *Voice_CMD)
{
	cJSON *tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
	cJSON *tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
	cJSON *tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
	cJSON *tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
	if(!strcmp(tem_type->valuestring,"010201"))
	{
		uint8_t final_cmd[16];
		memset(final_cmd,0,16);
		uint8_t num_str = judge_number(Voice_CMD);
		if( num_str == 255 )
			cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff",final_cmd);
		else
		{
			num_str = num_str*25.5/10;
			if(num_str >= 255)
			cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff",final_cmd);
			else
			{
				char cmd_str[3];
				memset(cmd_str,0,3);
				hex_to_str(&num_str,cmd_str,1);
				cmd_str[2]='\0';
				cmd_mix(tem_mac->valuestring,tem_port->valuestring,cmd_str,final_cmd);
			}
		}
		resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
		find_mac_and_send(tem_mac->valuestring,final_cmd,16);
		usleep(200000);
	}
	else if(!strcmp(tem_type->valuestring,"040201"))//bfbcl
	{
		uint8_t final_cmd[16];
		memset(final_cmd,0,16);
		uint8_t num_str = judge_number(Voice_CMD);
		if( num_str == 255 )
			cmd_mix(tem_mac->valuestring,tem_port->valuestring,"64",final_cmd);
		else
		{
			char cmd_str[3];
			memset(cmd_str,0,3);
			hex_to_str(&num_str,cmd_str,1);
			cmd_str[2]='\0';
			cmd_mix(tem_mac->valuestring,tem_port->valuestring,cmd_str,final_cmd);
		}
		resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
		find_mac_and_send(tem_mac->valuestring,final_cmd,16);
		usleep(200000);
	}
	else if(!strcmp(tem_type->valuestring,"010301"))//rgb
	{
		uint8_t final_cmd[19];
		memset(final_cmd,0,19);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					if(strstr(Voice_CMD,"红色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff0000ff",final_cmd);
					else if(strstr(Voice_CMD,"橙色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff7d00ff",final_cmd);
					else if(strstr(Voice_CMD,"黄色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffff00ff",final_cmd);
					else if(strstr(Voice_CMD,"绿色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ff00ff",final_cmd);
					else if(strstr(Voice_CMD,"青色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ffffff",final_cmd);
					else if(strstr(Voice_CMD,"蓝色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0000ffff",final_cmd);
					else if(strstr(Voice_CMD,"紫色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff00ffff",final_cmd);
					else if(strstr(Voice_CMD,"黑色"))
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000000ff",final_cmd);
					else
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffffffff",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
							{
								my_dev_state->valuestring[6]='f';
								my_dev_state->valuestring[7]='f';
								if(strstr(Voice_CMD,"红色"))
								memcpy(my_dev_state->valuestring,"ff0000",6);
								else if(strstr(Voice_CMD,"橙色"))
								memcpy(my_dev_state->valuestring,"ff7d00",6);
								else if(strstr(Voice_CMD,"黄色"))
								memcpy(my_dev_state->valuestring,"ffff00",6);
								else if(strstr(Voice_CMD,"绿色"))
								memcpy(my_dev_state->valuestring,"00ff00",6);
								else if(strstr(Voice_CMD,"青色"))
								memcpy(my_dev_state->valuestring,"00ffff",6);
								else if(strstr(Voice_CMD,"蓝色"))
								memcpy(my_dev_state->valuestring,"0000ff",6);
								else if(strstr(Voice_CMD,"紫色"))
								memcpy(my_dev_state->valuestring,"ff00ff",6);
								else if(strstr(Voice_CMD,"黑色"))
								memcpy(my_dev_state->valuestring,"000000",6);
								cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							}
							else
							{
								if(strstr(Voice_CMD,"红色"))
								memcpy(my_dev_state->valuestring,"ff0000",6);
								else if(strstr(Voice_CMD,"橙色"))
								memcpy(my_dev_state->valuestring,"ff7d00",6);
								else if(strstr(Voice_CMD,"黄色"))
								memcpy(my_dev_state->valuestring,"ffff00",6);
								else if(strstr(Voice_CMD,"绿色"))
								memcpy(my_dev_state->valuestring,"00ff00",6);
								else if(strstr(Voice_CMD,"青色"))
								memcpy(my_dev_state->valuestring,"00ffff",6);
								else if(strstr(Voice_CMD,"蓝色"))
								memcpy(my_dev_state->valuestring,"0000ff",6);
								else if(strstr(Voice_CMD,"紫色"))
								memcpy(my_dev_state->valuestring,"ff00ff",6);
								else if(strstr(Voice_CMD,"黑色"))
								memcpy(my_dev_state->valuestring,"000000",6);
								cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							}
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							if(strstr(Voice_CMD,"红色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff0000ff",final_cmd);
							else if(strstr(Voice_CMD,"橙色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff7d00ff",final_cmd);
							else if(strstr(Voice_CMD,"黄色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffff00ff",final_cmd);
							else if(strstr(Voice_CMD,"绿色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ff00ff",final_cmd);
							else if(strstr(Voice_CMD,"青色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"00ffffff",final_cmd);
							else if(strstr(Voice_CMD,"蓝色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0000ffff",final_cmd);
							else if(strstr(Voice_CMD,"紫色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ff00ffff",final_cmd);
							else if(strstr(Voice_CMD,"黑色"))
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000000ff",final_cmd);
							else
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"ffffffff",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(19,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,19);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
		usleep(200000);
	}
	else if(!strcmp(tem_type->valuestring,"080401"))//中央空调
	{
		uint8_t final_cmd[25];
		memset(final_cmd,0,25);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000100010003001a0000",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							if(strstr(Voice_CMD,"度"))
							{
								uint8_t temperature = judge_number_kt(Voice_CMD);
								if(temperature >=16 && temperature <=30)
								hex_to_str(&temperature,my_dev_state->valuestring+14,1);
							}
							else if(strstr(Voice_CMD,"自动模式"))
								memcpy(my_dev_state->valuestring+6,"00",2);
							else if(strstr(Voice_CMD,"制冷模式"))
								memcpy(my_dev_state->valuestring+6,"01",2);
							else if(strstr(Voice_CMD,"制热模式"))
								memcpy(my_dev_state->valuestring+6,"02",2);
							else if(strstr(Voice_CMD,"除湿模式"))
								memcpy(my_dev_state->valuestring+6,"03",2);
							else if(strstr(Voice_CMD,"送风模式"))
								memcpy(my_dev_state->valuestring+6,"04",2);
							else if(strstr(Voice_CMD,"低"))
								memcpy(my_dev_state->valuestring+10,"01",2);
							else if(strstr(Voice_CMD,"中"))
								memcpy(my_dev_state->valuestring+10,"02",2);
							else if(strstr(Voice_CMD,"高"))
								memcpy(my_dev_state->valuestring+10,"03",2);
							else if(strstr(Voice_CMD,"自动风"))
								memcpy(my_dev_state->valuestring+10,"00",2);
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"000100010003001a0000",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(25,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,25);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
	}
	else if(!strcmp(tem_type->valuestring,"080301"))//温控器
	{
		uint8_t final_cmd[20];
		memset(final_cmd,0,20);
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		pthread_mutex_unlock(&mutex_zl);
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				if(while_device_state_list_data==NULL)
				{
					cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0101011a00",final_cmd);
				}
				else
				{
					while(while_device_state_list_data != NULL)
					{
						if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
						{
							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
							if(strstr(Voice_CMD,"度"))
							{
								uint8_t temperature = judge_number_kt(Voice_CMD);
								if(temperature >=5 && temperature <=35)
								hex_to_str(&temperature,my_dev_state->valuestring+6,1);
							}
							else if(strstr(Voice_CMD,"自动模式"))
								memcpy(my_dev_state->valuestring+2,"00",2);
							else if(strstr(Voice_CMD,"制冷模式"))
								memcpy(my_dev_state->valuestring+2,"01",2);
							else if(strstr(Voice_CMD,"制热模式"))
								memcpy(my_dev_state->valuestring+2,"02",2);
							else if(strstr(Voice_CMD,"除湿模式"))
								memcpy(my_dev_state->valuestring+2,"03",2);
							else if(strstr(Voice_CMD,"送风模式"))
								memcpy(my_dev_state->valuestring+2,"04",2);
							else if(strstr(Voice_CMD,"低"))
								memcpy(my_dev_state->valuestring+4,"01",2);
							else if(strstr(Voice_CMD,"中"))
								memcpy(my_dev_state->valuestring+4,"02",2);
							else if(strstr(Voice_CMD,"高"))
								memcpy(my_dev_state->valuestring+4,"03",2);
							else if(strstr(Voice_CMD,"自动风"))
								memcpy(my_dev_state->valuestring+4,"00",2);
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
							break;
						}
						while_device_state_list_data = while_device_state_list_data->next;
						if(while_device_state_list_data==NULL)
						{
							cmd_mix(tem_mac->valuestring,tem_port->valuestring,"0101011a00",final_cmd);
						}
					}
				}
			}
		}
		if(final_cmd[0] != final_cmd[1])
		{
			resend_zt(20,final_cmd,tem_id->valuestring,tem_type->valuestring);
			find_mac_and_send(tem_mac->valuestring,final_cmd,20);
		}
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
	}
	else if(!strcmp(tem_type->valuestring,"050101"))//kt
	{
		cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
		int str_len = strlen(tem_lid->valuestring);
		if(str_len)
		{
			pthread_mutex_lock(&mutex_code);
			cJSON *code_id_root = cJSON_Parse(code_id);
			pthread_mutex_unlock(&mutex_code);
			if(code_id_root != NULL)
			{
				if(code_id_root->child != NULL)
				{
					cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
					if(kt_root != NULL)
					{
						cJSON *kt_while = kt_root->child;
						if(kt_while==NULL && NET_FLAG)
						{
							cJSON *hw_request_root = cJSON_CreateObject();
							cJSON_AddStringToObject(hw_request_root,"co","orange");
							cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
							cJSON *hw_request_data = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
							cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
							cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
							cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
							cJSON *hw_request_cmd = cJSON_CreateObject();
							cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
							cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201010102");//默认模式
							char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
							int my_len = strlen(hw_request_char);
							char *my_send_char = (char *)malloc(my_len+2);
							memset(my_send_char,0,my_len+2);
							memcpy(my_send_char,hw_request_char,my_len);
							strcat(my_send_char,"\n\0");
							send(cd,my_send_char,my_len+1,0);
							cJSON_Delete(hw_request_root);
							hw_request_root = NULL;
							free(hw_request_char);
							hw_request_char = NULL;
							free(my_send_char);
							my_send_char=NULL;
						}
						else
						{
							while(kt_while != NULL)
							{
								if(strcmp(kt_while->string,tem_lid->valuestring)==0)
								{
									cJSON *my_hw_lid = cJSON_GetObjectItem(kt_root,tem_lid->valuestring);
									cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"code");
									str_len = strlen(my_code->valuestring)+56;
									uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
									memset(final_cmd,0,str_len/2);
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											if(while_device_state_list_data==NULL)
											cmd_mix_kt(tem_lid->valuestring,"1a010201010102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
											else
											{
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
													{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														if(strstr(Voice_CMD,"度"))
														{
															uint8_t temperature1,temperature2;
															str_to_hex(&temperature1,my_dev_state->valuestring,1);
															temperature2 = judge_number_kt(Voice_CMD);
															if(temperature2 >= 16 && temperature2 <= 30)
															{
																if(temperature1 > temperature2)
																{
																	my_dev_state->valuestring[10]='0';
																	my_dev_state->valuestring[11]='7';
																	hex_to_str(&temperature2,my_dev_state->valuestring,1);
																}
																else if(temperature1 < temperature2)
																{
																	my_dev_state->valuestring[10]='0';
																	my_dev_state->valuestring[11]='6';
																	hex_to_str(&temperature2,my_dev_state->valuestring,1);
																}
															}
														}
														else if(strstr(Voice_CMD,"自动模式"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='2';
															my_dev_state->valuestring[12]='0';
															my_dev_state->valuestring[13]='1';
														}
														else if(strstr(Voice_CMD,"制冷模式"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='2';
															my_dev_state->valuestring[12]='0';
															my_dev_state->valuestring[13]='2';
														}
														else if(strstr(Voice_CMD,"除湿模式"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='2';
															my_dev_state->valuestring[12]='0';
															my_dev_state->valuestring[13]='3';
														}
														else if(strstr(Voice_CMD,"送风模式"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='2';
															my_dev_state->valuestring[12]='0';
															my_dev_state->valuestring[13]='4';
														}
														else if(strstr(Voice_CMD,"制热模式"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='2';
															my_dev_state->valuestring[12]='0';
															my_dev_state->valuestring[13]='5';
														}
														else if(strstr(Voice_CMD,"低"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='3';
															my_dev_state->valuestring[2]='0';
															my_dev_state->valuestring[3]='2';
														}
														else if(strstr(Voice_CMD,"中"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='3';
															my_dev_state->valuestring[2]='0';
															my_dev_state->valuestring[3]='3';
														}
														else if(strstr(Voice_CMD,"高"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='3';
															my_dev_state->valuestring[2]='0';
															my_dev_state->valuestring[3]='4';
														}
														else if(strstr(Voice_CMD,"自动风"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='3';
															my_dev_state->valuestring[2]='0';
															my_dev_state->valuestring[3]='1';
														}
														else if(strstr(Voice_CMD,"上下扫风"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='4';
															my_dev_state->valuestring[4]='0';
														
															if(my_dev_state->valuestring[5] == '1')
																my_dev_state->valuestring[5] = '2';
															else if(my_dev_state->valuestring[5] == '2')
																my_dev_state->valuestring[5] = '1';
															else
																my_dev_state->valuestring[5] = '2';
														}
														else if(strstr(Voice_CMD,"左右扫风"))
														{
															my_dev_state->valuestring[10]='0';
															my_dev_state->valuestring[11]='5';
															my_dev_state->valuestring[6]='0';
															my_dev_state->valuestring[6] = '0';
															if(my_dev_state->valuestring[7] == '0')
																my_dev_state->valuestring[7] = '1';
															else
																my_dev_state->valuestring[7] = '0';
														}
														cmd_mix_kt(tem_lid->valuestring,my_dev_state->valuestring,my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
														break;
													}
													while_device_state_list_data=while_device_state_list_data->next;
													if(while_device_state_list_data==NULL)
													cmd_mix_kt(tem_lid->valuestring,"1a010201010102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
												}
											}
										}
									}
									find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
									cJSON_Delete(device_state_list_data);
									device_state_list_data=NULL;
									free(final_cmd);
									final_cmd = NULL;
									usleep(200000);
									break;
								}
								kt_while = kt_while->next;
								if(kt_while==NULL && NET_FLAG)
								{
									cJSON *hw_request_root = cJSON_CreateObject();
									cJSON_AddStringToObject(hw_request_root,"co","orange");
									cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
									cJSON *hw_request_data = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
									cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
									cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
									cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
									cJSON *hw_request_cmd = cJSON_CreateObject();
									cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
									cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201010102");
									char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
									int my_len = strlen(hw_request_char);
									char *my_send_char = (char *)malloc(my_len+2);
									memset(my_send_char,0,my_len+2);
									memcpy(my_send_char,hw_request_char,my_len);
									strcat(my_send_char,"\n\0");
									send(cd,my_send_char,my_len+1,0);
									cJSON_Delete(hw_request_root);
									hw_request_root = NULL;
									free(hw_request_char);
									hw_request_char = NULL;
									free(my_send_char);
									my_send_char=NULL;
								}
							}
						}
					}
				}
			}
			cJSON_Delete(code_id_root);
			code_id_root=NULL;
		}
	}
}
void voice_con(cJSON *root)
{
	cJSON *voice_data = cJSON_GetObjectItem(root,"data");
	cJSON *voice_cmd = cJSON_GetObjectItem(voice_data,"cmd");
	cJSON *voice_type = cJSON_GetObjectItem(voice_data,"type");
	int flag_have;
	int run_if = 0;
/*先遍历情景*//*先遍历情景*//*先遍历情景*//*先遍历情景*//*先遍历情景*//*先遍历情景*//*先遍历情景*//*先遍历情景*//*先遍历情景*/
	pthread_mutex_lock(&mutex_scene);
	cJSON *scene_list_root = cJSON_Parse(scene_list);//遍历情景列表
	pthread_mutex_unlock(&mutex_scene);
	if(scene_list_root != NULL)
	{
		if(scene_list_root->child !=NULL)
		{
			cJSON *scene_list_data = cJSON_GetObjectItem(scene_list_root,"data");
			if(scene_list_data->child != NULL)
			{
				cJSON *scene_list_list = cJSON_GetObjectItem(scene_list_data,"scen_list");
				int scene_num = cJSON_GetArraySize(scene_list_list);
				int i,j;
				cJSON *scene_id_my = NULL;
				cJSON *scene_name = NULL;
				cJSON *scene_for = NULL;
				for(i=0;i<scene_num;i++)
				{
					scene_for = cJSON_GetArrayItem(scene_list_list,i);
					scene_name = cJSON_GetObjectItem(scene_for,"scen_name");
					if(strstr(voice_cmd->valuestring,scene_name->valuestring))
					{
						cJSON *scene_enable = cJSON_GetObjectItem(scene_for,"is_enable");
						if(strcmp(scene_enable->valuestring,"1")==0)//need run scene
						{
							scene_id_my = cJSON_GetObjectItem(scene_for,"scen_id");
							char *scene_id_pthread = (char *)malloc(strlen(scene_id_my->valuestring)+1);
							memset(scene_id_pthread,0,strlen(scene_id_my->valuestring)+1);
							memcpy(scene_id_pthread,scene_id_my->valuestring,strlen(scene_id_my->valuestring)+1);
							pth_creat_my(run_the_scene,scene_id_pthread);
							run_if = 1;
							if(NET_FLAG)
							{
								cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
								cJSON *send_root = cJSON_CreateObject();
								cJSON_AddStringToObject(send_root,"co","orange");
								cJSON_AddStringToObject(send_root,"api","gw_up_msg");
								cJSON *data_scene = cJSON_CreateObject();
								cJSON_AddItemToObject(send_root,"data",data_scene);
								cJSON_AddStringToObject(data_scene,"id",scene_id_my->valuestring);
								cJSON_AddStringToObject(data_scene,"msg_type","0203");
								if(strcmp(push->valuestring,"1")==0)
									cJSON_AddStringToObject(data_scene,"is_push","1");
								else
									cJSON_AddStringToObject(data_scene,"is_push","0");
								char *send_char = cJSON_PrintUnformatted(send_root);
								int my_len = strlen(send_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,send_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								free(send_char);
								send_char=NULL;
								free(my_send_char);
								my_send_char=NULL;
								cJSON_Delete(send_root);
								send_root=NULL;
							}
						}
						break;
					}
					else if(i==(scene_num-1))
					{
						cJSON *key_voice = NULL;
						cJSON *voice_for = NULL;
						int num_voice=0,k;
						for(j=0;j<scene_num;j++)
						{
							scene_for = cJSON_GetArrayItem(scene_list_list,j);
							key_voice = cJSON_GetObjectItem(scene_for,"keyword");
							num_voice = cJSON_GetArraySize(key_voice);
							for(k=0;k<num_voice;k++)
							{
								voice_for = cJSON_GetArrayItem(key_voice,k);
								if(strstr(voice_cmd->valuestring,voice_for->valuestring))
								{
									cJSON *scene_enable = cJSON_GetObjectItem(scene_for,"is_enable");
									if(strcmp(scene_enable->valuestring,"1")==0)//need run scene
									{
										scene_id_my = cJSON_GetObjectItem(scene_for,"scen_id");
										char *scene_id_pthread = (char *)malloc(strlen(scene_id_my->valuestring)+1);
										memset(scene_id_pthread,0,strlen(scene_id_my->valuestring)+1);
										memcpy(scene_id_pthread,scene_id_my->valuestring,strlen(scene_id_my->valuestring)+1);
										pth_creat_my(run_the_scene,scene_id_pthread);
										run_if = 1;
										if(NET_FLAG)
										{
											cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
											cJSON *send_root = cJSON_CreateObject();
											cJSON_AddStringToObject(send_root,"co","orange");
											cJSON_AddStringToObject(send_root,"api","gw_up_msg");
											cJSON *data_scene = cJSON_CreateObject();
											cJSON_AddItemToObject(send_root,"data",data_scene);
											cJSON_AddStringToObject(data_scene,"id",scene_id_my->valuestring);
											cJSON_AddStringToObject(data_scene,"msg_type","0203");
											if(strcmp(push->valuestring,"1")==0)
												cJSON_AddStringToObject(data_scene,"is_push","1");
											else
												cJSON_AddStringToObject(data_scene,"is_push","0");
											char *send_char = cJSON_PrintUnformatted(send_root);
											int my_len = strlen(send_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,send_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											free(send_char);
											send_char=NULL;
											free(my_send_char);
											my_send_char=NULL;
											cJSON_Delete(send_root);
											send_root=NULL;
										}
									}
									j = scene_num;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	cJSON_Delete(scene_list_root);
	scene_list_root=NULL;
/*再遍历安防*//*再遍历安防*//*再遍历安防*//*再遍历安防*//*再遍历安防*//*再遍历安防*//*再遍历安防*//*再遍历安防*/	
	if(run_if==0)
	{
		int flag_af=0;
		char af_str[5];
		memset(af_str,0,5);
		if(strstr(voice_cmd->valuestring,"在家布防") || strstr(voice_cmd->valuestring,"在家不妨"))
		{
			strcat(af_str,"0101");
			flag_af=1;
		}
		else if(strstr(voice_cmd->valuestring,"离家布防") || strstr(voice_cmd->valuestring,"离家不妨"))
		{
			strcat(af_str,"0102");
			flag_af=1;
		}
		else if(strstr(voice_cmd->valuestring,"撤防") || strstr(voice_cmd->valuestring,"侧房"))
		{
			strcat(af_str,"0103");
			flag_af=1;
		}
		if(flag_af==1)
		{
			run_if = 2;
			pthread_mutex_lock(&mutex_qj);
			if(strcmp(af_str,qj_model))
			{
				memset(qj_model,0,5);
				memcpy(qj_model,af_str,strlen(af_str));
				int qj_model_fd = open("/root/qj_model.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
				write(qj_model_fd,qj_model,strlen(qj_model));
				fsync(qj_model_fd);
				close(qj_model_fd);
				pthread_mutex_unlock(&mutex_qj);
				int i,j;
				pthread_mutex_lock(&mutex_af);
				cJSON *secure_list = cJSON_Parse(secure_set_list);//遍历af列表
				pthread_mutex_unlock(&mutex_af);
				if(secure_list != NULL)
				{
					if(secure_list->child != NULL)
					{
						cJSON *my_model_data = cJSON_GetObjectItem(secure_list,"data");
						cJSON *my_model = cJSON_GetObjectItem(my_model_data,"model_set_list");
						cJSON *switch_model = cJSON_GetObjectItem(my_model,af_str);
						int m_l = cJSON_GetArraySize(switch_model);
						cJSON *secure_arr_jx = NULL;
						cJSON *secure_id = NULL;
						cJSON *secure_type = NULL;
						cJSON *secure_state = NULL;
						for(i=0;i<m_l;i++)
						{
							secure_arr_jx = cJSON_GetArrayItem(switch_model,i);
							secure_id = cJSON_GetObjectItem(secure_arr_jx,"dev_id");
							secure_type = cJSON_GetObjectItem(secure_arr_jx,"dev_type");
							secure_state = cJSON_GetObjectItem(secure_arr_jx,"dev_state");
							if(NET_FLAG)
							{
								cJSON *secure_root = cJSON_CreateObject();
								cJSON *secure_root_data = cJSON_CreateObject();
								cJSON *secure_root_state = cJSON_CreateObject();
								cJSON_AddNumberToObject(secure_root,"retcode",0);
								cJSON_AddStringToObject(secure_root,"message","success");
								cJSON_AddStringToObject(secure_root,"api","secuStateRes");
								cJSON_AddItemToObject(secure_root,"data",secure_root_data);
								cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
								cJSON_AddStringToObject(secure_root_data,"dev_id",secure_id->valuestring);
								cJSON_AddStringToObject(secure_root_data,"dev_type",secure_type->valuestring);
								if(strcmp(secure_type->valuestring,"020101")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else if(strcmp(secure_type->valuestring,"020102")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else if(strcmp(secure_type->valuestring,"020103")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else if(strcmp(secure_type->valuestring,"020104")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else
									cJSON_AddStringToObject(secure_root_state,"dev_state",secure_state->valuestring);
								char *secure_root_char = cJSON_PrintUnformatted(secure_root);
								int my_len = strlen(secure_root_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,secure_root_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								free(secure_root_char);
								secure_root_char=NULL;
								free(my_send_char);
								my_send_char=NULL;
								cJSON_Delete(secure_root);
								secure_root=NULL;
							}
							pthread_mutex_lock(&mutex_zl);
							cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
							if(device_state_list_data != NULL)
							{
								if(device_state_list_data->child != NULL)
								{
									cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
									cJSON *while_device_state_list_data = my_device_state_list_data->child;
									if(while_device_state_list_data==NULL)
									{
										cJSON *state_root = cJSON_CreateObject();
										cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
										cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
										char *state_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,state_char,strlen(state_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,state_char,strlen(state_char));
										fsync(state_fd);
										close(state_fd);
										free(state_char);
										state_char=NULL;
									}
									else
									{
										while(while_device_state_list_data != NULL)
										{
											if(strcmp(while_device_state_list_data->string,secure_id->valuestring)==0)
											{
												cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,secure_id->valuestring);
												int num_sec = cJSON_GetArraySize(dev_state_cjson);
												cJSON *arr_for=NULL;
												flag_have=0;
												for(j=0;j<num_sec;j++)
												{
													arr_for = cJSON_GetArrayItem(dev_state_cjson,j);
													if(!strcmp(arr_for->string,"dev_state"))
													{
														flag_have=1;
														break;
													}
												}
												if(flag_have==1)
												cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
												cJSON_AddStringToObject(dev_state_cjson,"dev_state",secure_state->valuestring);
												char *state_char = cJSON_PrintUnformatted(device_state_list_data);
												memset(device_state_list,0,BUFFSIZE);
												memcpy(device_state_list,state_char,strlen(state_char));
												int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
												write(state_fd,state_char,strlen(state_char));
												fsync(state_fd);
												close(state_fd);
												free(state_char);
												state_char=NULL;
												break;
											}
											while_device_state_list_data = while_device_state_list_data->next;
											if(while_device_state_list_data==NULL)
											{
												cJSON *state_root = cJSON_CreateObject();
												cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
												cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
												char *state_char = cJSON_PrintUnformatted(device_state_list_data);
												memset(device_state_list,0,BUFFSIZE);
												memcpy(device_state_list,state_char,strlen(state_char));
												int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
												write(state_fd,state_char,strlen(state_char));
												fsync(state_fd);
												close(state_fd);
												free(state_char);
												state_char=NULL;
											}
										}
									}
								}
							}
							pthread_mutex_unlock(&mutex_zl);
							cJSON_Delete(device_state_list_data);
							device_state_list_data=NULL;
						}
					}
				}
				if(NET_FLAG)
				{
					cJSON *secure_model_now = cJSON_CreateObject();
					cJSON *secure_model_now_data = cJSON_CreateObject();
					cJSON_AddNumberToObject(secure_model_now,"retcode",0);
					cJSON_AddStringToObject(secure_model_now,"message","success");
					cJSON_AddStringToObject(secure_model_now,"api","secuModelRes");
					cJSON_AddItemToObject(secure_model_now,"data",secure_model_now_data);
					cJSON_AddStringToObject(secure_model_now_data,"model",af_str);
					char *secure_model_now_char = cJSON_PrintUnformatted(secure_model_now);
					int my_len = strlen(secure_model_now_char);
					char *my_send_char = (char *)malloc(my_len+2);
					memset(my_send_char,0,my_len+2);
					memcpy(my_send_char,secure_model_now_char,my_len);
					strcat(my_send_char,"\n\0");
					send(cd,my_send_char,my_len+1,0);
					free(secure_model_now_char);
					secure_model_now_char=NULL;
					free(my_send_char);
					my_send_char=NULL;
					cJSON_Delete(secure_model_now);
					secure_model_now=NULL;
				}
				cJSON_Delete(secure_list);
				secure_list=NULL;
			}
			else
				pthread_mutex_unlock(&mutex_qj);
		}
	}
/*再遍历普通控制*//*再遍历普通控制*//*再遍历普通控制*//*再遍历普通控制*//*再遍历普通控制*//*再遍历普通控制*//*再遍历普通控制*//*再遍历普通控制*/
	if(run_if==0)
	{
		char voice_str_in[50];
		memset(voice_str_in,0,50);
		int traver_ret = traversing_room_list(voice_cmd->valuestring,voice_str_in);
		if(strstr(voice_cmd->valuestring,"打开")||strstr(voice_cmd->valuestring,"开启")||strstr(voice_cmd->valuestring,"启动"))
		{
			int flag_voice = 1;
			pthread_mutex_lock(&mutex_sl);
			cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
			pthread_mutex_unlock(&mutex_sl);
			if(dev_list_data != NULL)
			{
				if(dev_list_data->child != NULL)
				{
					cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
					cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
					int	data_l =  cJSON_GetArraySize(my_dev_list_list);
					cJSON *data_arr_jx = NULL;
					cJSON *tem_name = NULL;
					cJSON *tem_room_id = NULL;
					int i,j;
					for(i=0;i<data_l;i++)
					{
						data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
						tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
						tem_room_id = cJSON_GetObjectItem(data_arr_jx,"room_id");
						if(traver_ret)
						{
							if(strstr(voice_cmd->valuestring,tem_name->valuestring) && !strcmp(tem_room_id->valuestring,voice_str_in))
							{
								flag_voice=0;
								run_if=3;
								voice_open(data_arr_jx,voice_cmd->valuestring);
							}
							else if(i==(data_l-1) && flag_voice == 1 )
							{
								for(j=0;j<data_l;j++)
								{
									data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,j);
									tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
									tem_room_id = cJSON_GetObjectItem(data_arr_jx,"room_id");
									char *my_str_first = NULL;
									char *my_str_second = NULL;
									char *voice_str_first = NULL;
									char *voice_str_second = NULL;
									my_str_first = tiqu(tem_name->valuestring);
									voice_str_first = tiqu(voice_cmd->valuestring);
									my_str_second = str_judge(my_str_first);
									voice_str_second = str_judge(voice_str_first);
									if(strstr(voice_str_second,my_str_second) && !strcmp(tem_room_id->valuestring,voice_str_in))
									{
										run_if=3;
										voice_open(data_arr_jx,voice_cmd->valuestring);
									}
									free(my_str_first);
									my_str_first=NULL;
									free(my_str_second);
									my_str_second=NULL;
									free(voice_str_first);
									voice_str_first=NULL;
									free(voice_str_second);
									voice_str_second=NULL;
								}
							}
						}
						else
						{
							if(strstr(voice_cmd->valuestring,tem_name->valuestring))
							{
								flag_voice=0;
								run_if=3;
								voice_open(data_arr_jx,voice_cmd->valuestring);
							}
							else if(i==(data_l-1) && flag_voice == 1)
							{
								for(j=0;j<data_l;j++)
								{
									data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,j);
									tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
									char *my_str_first = NULL;
									char *my_str_second = NULL;
									char *voice_str_first = NULL;
									char *voice_str_second = NULL;
									my_str_first = tiqu(tem_name->valuestring);
									voice_str_first = tiqu(voice_cmd->valuestring);
									my_str_second = str_judge(my_str_first);
									voice_str_second = str_judge(voice_str_first);
									if(strstr(voice_str_second,my_str_second))
									{
										run_if=3;
										voice_open(data_arr_jx,voice_cmd->valuestring);
									}
									free(my_str_first);
									my_str_first=NULL;
									free(my_str_second);
									my_str_second=NULL;
									free(voice_str_first);
									voice_str_first=NULL;
									free(voice_str_second);
									voice_str_second=NULL;
								}
							}
						}
					}
				}
			}
			cJSON_Delete(dev_list_data);
			dev_list_data=NULL;
		}//
		else if(strstr(voice_cmd->valuestring,"关闭")||strstr(voice_cmd->valuestring,"关掉")||strstr(voice_cmd->valuestring,"关上"))
		{
			int flag_voice = 1;
			pthread_mutex_lock(&mutex_sl);
			cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
			pthread_mutex_unlock(&mutex_sl);
			if(dev_list_data != NULL)
			{
				if(dev_list_data->child != NULL)
				{
					cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
					cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
					int	data_l =  cJSON_GetArraySize(my_dev_list_list);
					cJSON *data_arr_jx = NULL;
					cJSON *tem_name = NULL;
					cJSON *tem_room_id = NULL;
					int i,j;
					for(i=0;i<data_l;i++)
					{
						data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
						tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
						tem_room_id = cJSON_GetObjectItem(data_arr_jx,"room_id");
						if(traver_ret)
						{
							if(strstr(voice_cmd->valuestring,tem_name->valuestring) && !strcmp(tem_room_id->valuestring,voice_str_in))
							{
								flag_voice=0;
								run_if=3;
								voice_close(data_arr_jx);
							}
							else if(i==(data_l-1) && flag_voice == 1)
							{
								for(j=0;j<data_l;j++)
								{
									data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,j);
									tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
									tem_room_id = cJSON_GetObjectItem(data_arr_jx,"room_id");
									char *my_str_first = NULL;
									char *my_str_second = NULL;
									char *voice_str_first = NULL;
									char *voice_str_second = NULL;
									my_str_first = tiqu(tem_name->valuestring);
									voice_str_first = tiqu(voice_cmd->valuestring);
									my_str_second = str_judge(my_str_first);
									voice_str_second = str_judge(voice_str_first);
									if(strstr(voice_str_second,my_str_second) && !strcmp(tem_room_id->valuestring,voice_str_in))
									{
										run_if=3;
										voice_close(data_arr_jx);
									}
									free(my_str_first);
									my_str_first=NULL;
									free(my_str_second);
									my_str_second=NULL;
									free(voice_str_first);
									voice_str_first=NULL;
									free(voice_str_second);
									voice_str_second=NULL;
								}
							}
						}
						else
						{
							if(strstr(voice_cmd->valuestring,tem_name->valuestring))
							{
								flag_voice=0;
								run_if=3;
								voice_close(data_arr_jx);
							}
							else if(i==(data_l-1) && flag_voice == 1)
							{
								for(j=0;j<data_l;j++)
								{
									data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,j);
									tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
									char *my_str_first = NULL;
									char *my_str_second = NULL;
									char *voice_str_first = NULL;
									char *voice_str_second = NULL;
									my_str_first = tiqu(tem_name->valuestring);
									voice_str_first = tiqu(voice_cmd->valuestring);
									my_str_second = str_judge(my_str_first);
									voice_str_second = str_judge(voice_str_first);
									if(strstr(voice_str_second,my_str_second))
									{
										run_if=3;
										voice_close(data_arr_jx);
									}
									free(my_str_first);
									my_str_first=NULL;
									free(my_str_second);
									my_str_second=NULL;
									free(voice_str_first);
									voice_str_first=NULL;
									free(voice_str_second);
									voice_str_second=NULL;
								}
							}
						}
					}
				}
			}
			cJSON_Delete(dev_list_data);
			dev_list_data=NULL;
		}//
		else if(strstr(voice_cmd->valuestring,"调到")||strstr(voice_cmd->valuestring,"调整到")||strstr(voice_cmd->valuestring,"调为")||strstr(voice_cmd->valuestring,"调成")||strstr(voice_cmd->valuestring,"变成"))
		{
			int flag_voice = 1;
			pthread_mutex_lock(&mutex_sl);
			cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
			pthread_mutex_unlock(&mutex_sl);
			if(dev_list_data != NULL)
			{
				if(dev_list_data->child != NULL)
				{
					cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
					cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
					int	data_l =  cJSON_GetArraySize(my_dev_list_list);
					cJSON *data_arr_jx = NULL;
					cJSON *tem_name = NULL;
					cJSON *tem_room_id = NULL;
					int i,j;
					for(i=0;i<data_l;i++)
					{
						data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
						tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
						tem_room_id = cJSON_GetObjectItem(data_arr_jx,"room_id");
						if(traver_ret)
						{
							if(strstr(voice_cmd->valuestring,tem_name->valuestring) && !strcmp(tem_room_id->valuestring,voice_str_in))
							{
								flag_voice=0;
								run_if=3;
								voice_judge(data_arr_jx,voice_cmd->valuestring);
							}
							else if(i==(data_l-1) && flag_voice == 1)
							{
								for(j=0;j<data_l;j++)
								{
									data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,j);
									tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
									tem_room_id = cJSON_GetObjectItem(data_arr_jx,"room_id");
									char *my_str_first = NULL;
									char *my_str_second = NULL;
									char *voice_str_first = NULL;
									char *voice_str_second = NULL;
									my_str_first = tiqu(tem_name->valuestring);
									voice_str_first = tiqu(voice_cmd->valuestring);
									my_str_second = str_judge(my_str_first);
									voice_str_second = str_judge(voice_str_first);
									if(strstr(voice_str_second,my_str_second) && !strcmp(tem_room_id->valuestring,voice_str_in))
									{
										run_if=3;
										voice_judge(data_arr_jx,voice_cmd->valuestring);
									}
									free(my_str_first);
									my_str_first=NULL;
									free(my_str_second);
									my_str_second=NULL;
									free(voice_str_first);
									voice_str_first=NULL;
									free(voice_str_second);
									voice_str_second=NULL;
								}//for
							}
						}
						else
						{
							if(strstr(voice_cmd->valuestring,tem_name->valuestring))
							{
								flag_voice=0;
								run_if=3;
								voice_judge(data_arr_jx,voice_cmd->valuestring);
							}
							else if(i==(data_l-1) && flag_voice == 1)
							{
								for(j=0;j<data_l;j++)
								{
									data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,j);
									tem_name = cJSON_GetObjectItem(data_arr_jx,"dev_name");
									char *my_str_first = NULL;
									char *my_str_second = NULL;
									char *voice_str_first = NULL;
									char *voice_str_second = NULL;
									my_str_first = tiqu(tem_name->valuestring);
									voice_str_first = tiqu(voice_cmd->valuestring);
									my_str_second = str_judge(my_str_first);
									voice_str_second = str_judge(voice_str_first);
									if(strstr(voice_str_second,my_str_second))
									{
										run_if=3;
										voice_judge(data_arr_jx,voice_cmd->valuestring);
									}
									free(my_str_first);
									my_str_first=NULL;
									free(my_str_second);
									my_str_second=NULL;
									free(voice_str_first);
									voice_str_first=NULL;
									free(voice_str_second);
									voice_str_second=NULL;
								}//for
							}
						}
					}//for
				}
			}
			cJSON_Delete(dev_list_data);
			dev_list_data=NULL;
		}
	}
	if(run_if==0 && NET_FLAG)
	{
		cJSON *voice_ret = cJSON_CreateObject();
		cJSON *voice_data = cJSON_CreateObject();
		cJSON_AddNumberToObject(voice_ret,"retcode",130);
		cJSON_AddStringToObject(voice_ret,"message","没听清楚，能再说一遍吗？");
		cJSON_AddStringToObject(voice_ret,"api","voice_cmd");
		cJSON_AddItemToObject(voice_ret,"data",voice_data);
		cJSON_AddStringToObject(voice_data,"type",voice_type->valuestring);
		char *voice_char = cJSON_PrintUnformatted(voice_ret);
		int my_len = strlen(voice_char);
		char *my_send_char = (char *)malloc(my_len+2);
		memset(my_send_char,0,my_len+2);
		memcpy(my_send_char,voice_char,my_len);
		strcat(my_send_char,"\n\0");
		send(cd,my_send_char,my_len+1,0);
		free(voice_char);
		voice_char=NULL;
		free(my_send_char);
		my_send_char=NULL;
		cJSON_Delete(voice_ret);
		voice_ret=NULL;
	}
	else if(NET_FLAG)
	{
		cJSON *voice_ret = cJSON_CreateObject();
		cJSON *voice_data = cJSON_CreateObject();
		cJSON_AddNumberToObject(voice_ret,"retcode",0);
		cJSON_AddStringToObject(voice_ret,"message","success");
		cJSON_AddStringToObject(voice_ret,"api","voice_cmd");
		cJSON_AddItemToObject(voice_ret,"data",voice_data);
		cJSON_AddStringToObject(voice_data,"type",voice_type->valuestring);
		char *voice_char = cJSON_PrintUnformatted(voice_ret);
		int my_len = strlen(voice_char);
		char *my_send_char = (char *)malloc(my_len+2);
		memset(my_send_char,0,my_len+2);
		memcpy(my_send_char,voice_char,my_len);
		strcat(my_send_char,"\n\0");
		send(cd,my_send_char,my_len+1,0);
		free(voice_char);
		voice_char=NULL;
		free(my_send_char);
		my_send_char=NULL;
		cJSON_Delete(voice_ret);
		voice_ret=NULL;
	}
}
void dev_sec_con(cJSON *root)
{
	int i,flag_have;
	cJSON *secure_data = cJSON_GetObjectItem(root,"data");//data 层
	cJSON *secure_id = cJSON_GetObjectItem(secure_data,"dev_id");
	cJSON *secure_type = cJSON_GetObjectItem(secure_data,"dev_type");
	cJSON *secure_cmd = cJSON_GetObjectItem(secure_data,"dev_cmd");
	cJSON *my_cmd = cJSON_GetObjectItem(secure_cmd,"cmd");
	cJSON *secure_root = cJSON_CreateObject();
	cJSON *secure_root_data = cJSON_CreateObject();
	cJSON *secure_root_state = cJSON_CreateObject();
	cJSON_AddNumberToObject(secure_root,"retcode",0);
	cJSON_AddStringToObject(secure_root,"message","success");
	cJSON_AddStringToObject(secure_root,"api","secuStateRes");
	cJSON_AddItemToObject(secure_root,"data",secure_root_data);
	cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
	cJSON_AddStringToObject(secure_root_data,"dev_id",secure_id->valuestring);
	cJSON_AddStringToObject(secure_root_data,"dev_type",secure_type->valuestring);
	cJSON_AddStringToObject(secure_root_state,"dev_state",my_cmd->valuestring);
	char *secure_root_char = cJSON_PrintUnformatted(secure_root);
	int my_len = strlen(secure_root_char);
	char *my_send_char = (char *)malloc(my_len+2);
	memset(my_send_char,0,my_len+2);
	memcpy(my_send_char,secure_root_char,my_len);
	strcat(my_send_char,"\n\0");
	send(cd,my_send_char,my_len+1,0);
	free(my_send_char);
	my_send_char=NULL;
	free(secure_root_char);
	secure_root_char=NULL;
	cJSON_Delete(secure_root);
	secure_root=NULL;
	pthread_mutex_lock(&mutex_qj);
	if(strcmp(qj_model,"0104"))
	{
		int qj_model_fd = open("/root/qj_model.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
		write(qj_model_fd,"0104",strlen(qj_model));
		fsync(qj_model_fd);
		close(qj_model_fd);
		cJSON *secure_model_now = cJSON_CreateObject();
		cJSON *secure_model_now_data = cJSON_CreateObject();
		cJSON_AddNumberToObject(secure_model_now,"retcode",0);
		cJSON_AddStringToObject(secure_model_now,"message","success");
		cJSON_AddStringToObject(secure_model_now,"api","secuModelRes");
		cJSON_AddItemToObject(secure_model_now,"data",secure_model_now_data);
		cJSON_AddStringToObject(secure_model_now_data,"model","0104");
		char *secure_model_now_char = cJSON_PrintUnformatted(secure_model_now);
		int my_len = strlen(secure_model_now_char);
		char *my_send_char = (char *)malloc(my_len+2);
		memset(my_send_char,0,my_len+2);
		memcpy(my_send_char,secure_model_now_char,my_len);
		strcat(my_send_char,"\n\0");
		send(cd,my_send_char,my_len+1,0);
		free(secure_model_now_char);
		secure_model_now_char=NULL;
		free(my_send_char);
		my_send_char=NULL;
		cJSON_Delete(secure_model_now);
		secure_model_now=NULL;
		memset(qj_model,0,5);
		memcpy(qj_model,"0104",4);
	}
	pthread_mutex_unlock(&mutex_qj);
	pthread_mutex_lock(&mutex_zl);
	cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
	if(device_state_list_data != NULL)
	{
		if(device_state_list_data->child != NULL)
		{
			cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
			cJSON *while_device_state_list_data = my_device_state_list_data->child;
			if(while_device_state_list_data==NULL)
			{
				cJSON *state_root = cJSON_CreateObject();
				cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
				cJSON_AddStringToObject(state_root,"dev_state",my_cmd->valuestring);
				char *state_char = cJSON_PrintUnformatted(device_state_list_data);
				memset(device_state_list,0,BUFFSIZE);
				memcpy(device_state_list,state_char,strlen(state_char));
				int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
				write(state_fd,state_char,strlen(state_char));
				fsync(state_fd);
				close(state_fd);
				free(state_char);
				state_char=NULL;
			}
			else
			{
				while(while_device_state_list_data != NULL)
				{
					if(strcmp(while_device_state_list_data->string,secure_id->valuestring)==0)
					{
						cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,secure_id->valuestring);
						int num_sec = cJSON_GetArraySize(dev_state_cjson);
						cJSON *arr_for=NULL;
						flag_have=0;
						for(i=0;i<num_sec;i++)
						{
							arr_for = cJSON_GetArrayItem(dev_state_cjson,i);
							if(!strcmp(arr_for->string,"dev_state"))
							{
								flag_have=1;
								break;
							}
						}
						if(flag_have==1)
						cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
						cJSON_AddStringToObject(dev_state_cjson,"dev_state",my_cmd->valuestring);
						char *state_char = cJSON_PrintUnformatted(device_state_list_data);
						memset(device_state_list,0,BUFFSIZE);
						memcpy(device_state_list,state_char,strlen(state_char));
						int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
						write(state_fd,state_char,strlen(state_char));
						fsync(state_fd);
						close(state_fd);
						free(state_char);
						state_char=NULL;
						break;
					}
					while_device_state_list_data = while_device_state_list_data->next;
					if(while_device_state_list_data==NULL)
					{
						cJSON *state_root = cJSON_CreateObject();
						cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
						cJSON_AddStringToObject(state_root,"dev_state",my_cmd->valuestring);
						char *state_char = cJSON_PrintUnformatted(device_state_list_data);
						memset(device_state_list,0,BUFFSIZE);
						memcpy(device_state_list,state_char,strlen(state_char));
						int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
						write(state_fd,state_char,strlen(state_char));
						fsync(state_fd);
						close(state_fd);
						free(state_char);
						state_char=NULL;
					}
				}
			}
		}
	}
	pthread_mutex_unlock(&mutex_zl);
	cJSON_Delete(device_state_list_data);
	device_state_list_data=NULL;
}
void switchSecuModel(cJSON *root)
{
	int flag_have;
	cJSON *secure_data = cJSON_GetObjectItem(root,"data");//data 层
	cJSON *secure_model = cJSON_GetObjectItem(secure_data,"model");
	pthread_mutex_lock(&mutex_qj);
	if(strcmp(secure_model->valuestring,qj_model))
	{
		memset(qj_model,0,5);
		memcpy(qj_model,secure_model->valuestring,strlen(secure_model->valuestring));
		int qj_model_fd = open("/root/qj_model.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
		write(qj_model_fd,qj_model,strlen(qj_model));
		fsync(qj_model_fd);
		close(qj_model_fd);
		pthread_mutex_unlock(&mutex_qj);
		int i,j;
		pthread_mutex_lock(&mutex_af);
		cJSON *secure_list = cJSON_Parse(secure_set_list);//遍历af列表
		pthread_mutex_unlock(&mutex_af);
		if(secure_list != NULL)
		{
			if(secure_list->child != NULL)
			{
				cJSON *my_model_data = cJSON_GetObjectItem(secure_list,"data");
				cJSON *my_model = cJSON_GetObjectItem(my_model_data,"model_set_list");
				cJSON *switch_model = cJSON_GetObjectItem(my_model,secure_model->valuestring);
				int m_l = cJSON_GetArraySize(switch_model);
				cJSON *secure_arr_jx = NULL;
				cJSON *secure_id = NULL;
				cJSON *secure_type = NULL;
				cJSON *secure_state = NULL;
				for(i=0;i<m_l;i++)
				{
					secure_arr_jx = cJSON_GetArrayItem(switch_model,i);
					secure_id = cJSON_GetObjectItem(secure_arr_jx,"dev_id");
					secure_type = cJSON_GetObjectItem(secure_arr_jx,"dev_type");
					secure_state = cJSON_GetObjectItem(secure_arr_jx,"dev_state");
					cJSON *secure_root = cJSON_CreateObject();
					cJSON *secure_root_data = cJSON_CreateObject();
					cJSON *secure_root_state = cJSON_CreateObject();
					cJSON_AddNumberToObject(secure_root,"retcode",0);
					cJSON_AddStringToObject(secure_root,"message","success");
					cJSON_AddStringToObject(secure_root,"api","secuStateRes");
					cJSON_AddItemToObject(secure_root,"data",secure_root_data);
					cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
					cJSON_AddStringToObject(secure_root_data,"dev_id",secure_id->valuestring);
					cJSON_AddStringToObject(secure_root_data,"dev_type",secure_type->valuestring);
					if(strcmp(secure_type->valuestring,"020101")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else if(strcmp(secure_type->valuestring,"020102")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else if(strcmp(secure_type->valuestring,"020103")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else if(strcmp(secure_type->valuestring,"020104")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else
						cJSON_AddStringToObject(secure_root_state,"dev_state",secure_state->valuestring);
					char *secure_root_char = cJSON_PrintUnformatted(secure_root);
					int my_len = strlen(secure_root_char);
					char *my_send_char = (char *)malloc(my_len+2);
					memset(my_send_char,0,my_len+2);
					memcpy(my_send_char,secure_root_char,my_len);
					strcat(my_send_char,"\n\0");
					send(cd,my_send_char,my_len+1,0);
					free(secure_root_char);
					secure_root_char=NULL;
					free(my_send_char);
					my_send_char=NULL;
					cJSON_Delete(secure_root);
					secure_root=NULL;
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							
							if(while_device_state_list_data==NULL)
							{
								cJSON *state_root = cJSON_CreateObject();
								cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
								cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
								char *state_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,state_char,strlen(state_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,state_char,strlen(state_char));
								fsync(state_fd);
								close(state_fd);
								free(state_char);
								state_char=NULL;
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,secure_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,secure_id->valuestring);
										int num_sec = cJSON_GetArraySize(dev_state_cjson);
										cJSON *arr_for=NULL;
										flag_have=0;
										for(j=0;j<num_sec;j++)
										{
											arr_for = cJSON_GetArrayItem(dev_state_cjson,j);
											if(!strcmp(arr_for->string,"dev_state"))
											{
												flag_have=1;
												break;
											}
										}
										if(flag_have==1)
										cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
										cJSON_AddStringToObject(dev_state_cjson,"dev_state",secure_state->valuestring);
										char *state_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,state_char,strlen(state_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,state_char,strlen(state_char));
										fsync(state_fd);
										close(state_fd);
										free(state_char);
										state_char=NULL;
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data==NULL)
									{
										cJSON *state_root = cJSON_CreateObject();
										cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
										cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
										char *state_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,state_char,strlen(state_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,state_char,strlen(state_char));
										fsync(state_fd);
										close(state_fd);
										free(state_char);
										state_char=NULL;
									}
								}
							}
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data=NULL;
				}
			}
		}
		cJSON *secure_model_now = cJSON_CreateObject();
		cJSON *secure_model_now_data = cJSON_CreateObject();
		cJSON_AddNumberToObject(secure_model_now,"retcode",0);
		cJSON_AddStringToObject(secure_model_now,"message","success");
		cJSON_AddStringToObject(secure_model_now,"api","secuModelRes");
		cJSON_AddItemToObject(secure_model_now,"data",secure_model_now_data);
		cJSON_AddStringToObject(secure_model_now_data,"model",secure_model->valuestring);
		char *secure_model_now_char = cJSON_PrintUnformatted(secure_model_now);
		int my_len = strlen(secure_model_now_char);
		char *my_send_char = (char *)malloc(my_len+2);
		memset(my_send_char,0,my_len+2);
		memcpy(my_send_char,secure_model_now_char,my_len);
		strcat(my_send_char,"\n\0");
		send(cd,my_send_char,my_len+1,0);
		free(secure_model_now_char);
		secure_model_now_char=NULL;
		free(my_send_char);
		my_send_char=NULL;
		cJSON_Delete(secure_model_now);
		secure_model_now=NULL;
		cJSON_Delete(secure_list);
		secure_list=NULL;
	}
	else
	pthread_mutex_unlock(&mutex_qj);
}
void update_secure(void)
{
	int flag_have,i,j;
	pthread_mutex_lock(&mutex_qj);
	if(strcmp(qj_model,"0104"))
	{
		char *qj_model_compare = (char *)malloc(5);
		memset(qj_model_compare,0,5);
		memcpy(qj_model_compare,qj_model,4);
		qj_model_compare[4] = '\0';
		pthread_mutex_unlock(&mutex_qj);
		pthread_mutex_lock(&mutex_af);
		cJSON *secure_list = cJSON_Parse(secure_set_list);//遍历af列表
		pthread_mutex_unlock(&mutex_af);
		if(secure_list != NULL)
		{
			if(secure_list->child != NULL)
			{
				cJSON *my_model_data = cJSON_GetObjectItem(secure_list,"data");
				cJSON *my_model = cJSON_GetObjectItem(my_model_data,"model_set_list");
				cJSON *switch_model = cJSON_GetObjectItem(my_model,qj_model_compare);
				int m_l = cJSON_GetArraySize(switch_model);
				cJSON *secure_arr_jx = NULL;
				cJSON *secure_id = NULL;
				cJSON *secure_type = NULL;
				cJSON *secure_state = NULL;
				for(i=0;i<m_l;i++)
				{
					secure_arr_jx = cJSON_GetArrayItem(switch_model,i);
					secure_id = cJSON_GetObjectItem(secure_arr_jx,"dev_id");
					secure_type = cJSON_GetObjectItem(secure_arr_jx,"dev_type");
					secure_state = cJSON_GetObjectItem(secure_arr_jx,"dev_state");
					cJSON *secure_root = cJSON_CreateObject();
					cJSON *secure_root_data = cJSON_CreateObject();
					cJSON *secure_root_state = cJSON_CreateObject();
					cJSON_AddNumberToObject(secure_root,"retcode",0);
					cJSON_AddStringToObject(secure_root,"message","success");
					cJSON_AddStringToObject(secure_root,"api","secuStateRes");
					cJSON_AddItemToObject(secure_root,"data",secure_root_data);
					cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
					cJSON_AddStringToObject(secure_root_data,"dev_id",secure_id->valuestring);
					cJSON_AddStringToObject(secure_root_data,"dev_type",secure_type->valuestring);
					if(strcmp(secure_type->valuestring,"020101")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else if(strcmp(secure_type->valuestring,"020102")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else if(strcmp(secure_type->valuestring,"020103")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else if(strcmp(secure_type->valuestring,"020104")==0)
						cJSON_AddStringToObject(secure_root_state,"dev_state","01");
					else
						cJSON_AddStringToObject(secure_root_state,"dev_state",secure_state->valuestring);
					char *secure_root_char = cJSON_PrintUnformatted(secure_root);
					int my_len = strlen(secure_root_char);
					char *my_send_char = (char *)malloc(my_len+2);
					memset(my_send_char,0,my_len+2);
					memcpy(my_send_char,secure_root_char,my_len);
					strcat(my_send_char,"\n\0");
					send(cd,my_send_char,my_len+1,0);
					free(secure_root_char);
					secure_root_char=NULL;
					free(my_send_char);
					my_send_char=NULL;
					cJSON_Delete(secure_root);
					secure_root=NULL;
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							if(while_device_state_list_data==NULL)
							{
								cJSON *state_root = cJSON_CreateObject();
								cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
								cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
								char *state_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,state_char,strlen(state_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,state_char,strlen(state_char));
								fsync(state_fd);
								close(state_fd);
								free(state_char);
								state_char=NULL;
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,secure_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,secure_id->valuestring);
										int num_sec = cJSON_GetArraySize(dev_state_cjson);
										cJSON *arr_for=NULL;
										flag_have=0;
										for(j=0;j<num_sec;j++)
										{
											arr_for = cJSON_GetArrayItem(dev_state_cjson,j);
											if(!strcmp(arr_for->string,"dev_state"))
											{
												flag_have=1;
												break;
											}
										}
										if(flag_have==1)
										cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
										cJSON_AddStringToObject(dev_state_cjson,"dev_state",secure_state->valuestring);
										char *state_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,state_char,strlen(state_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,state_char,strlen(state_char));
										fsync(state_fd);
										close(state_fd);
										free(state_char);
										state_char=NULL;
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data==NULL)
									{
										cJSON *state_root = cJSON_CreateObject();
										cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
										cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
										char *state_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,state_char,strlen(state_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,state_char,strlen(state_char));
										fsync(state_fd);
										close(state_fd);
										free(state_char);
										state_char=NULL;
									}
								}
							}
						
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data=NULL;
				}
			}
		}
		free(qj_model_compare);
		qj_model_compare = NULL;
		cJSON_Delete(secure_list);
		secure_list = NULL;
	}
	else
		pthread_mutex_unlock(&mutex_qj);
}
void hw_study_or_complish_con(cJSON *root,int flag)
{
	cJSON *hw_study_data = cJSON_GetObjectItem(root,"data");
	cJSON *hw_mac = cJSON_GetObjectItem(hw_study_data,"mac");
	uint8_t final_cmd[17];
	memset(final_cmd,0,17);
	cmd_hw_study_or_complish(hw_mac->valuestring,final_cmd,flag);
	find_mac_and_send(hw_mac->valuestring,final_cmd,17);
}
void dev_hw_con(cJSON *root)
{
	cJSON *dev_hw_data = cJSON_GetObjectItem(root,"data");
	cJSON *dev_hw_mac = cJSON_GetObjectItem(dev_hw_data,"mac");
	cJSON *dev_hw_lid = cJSON_GetObjectItem(dev_hw_data,"lid");
	cJSON *dev_hw_id = cJSON_GetObjectItem(dev_hw_data,"dev_id");
	cJSON *dev_hw_type = cJSON_GetObjectItem(dev_hw_data,"dev_type");
	cJSON *dev_hw_cmd = cJSON_GetObjectItem(dev_hw_data,"dev_cmd");
	pthread_mutex_lock(&mutex_code);
	cJSON *code_id_root = cJSON_Parse(code_id);
	pthread_mutex_unlock(&mutex_code);
	if(code_id_root != NULL)
	{
		if(code_id_root->child != NULL)
		{
			if(strcmp(dev_hw_cmd->child->string,"cmd")==0)//按照简直找
			{
				cJSON *hw_cmd = cJSON_GetObjectItem(dev_hw_cmd,"cmd");
				cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
				if(kt_root != NULL)
				{
					cJSON *kt_while = kt_root->child;
					if(kt_while==NULL)
					{
						cJSON *hw_request_root = cJSON_CreateObject();
						cJSON_AddStringToObject(hw_request_root,"co","orange");
						cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
						cJSON *hw_request_data = cJSON_CreateObject();
						cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
						cJSON_AddStringToObject(hw_request_data,"mac",dev_hw_mac->valuestring);
						cJSON_AddStringToObject(hw_request_data,"lid",dev_hw_lid->valuestring);
						cJSON_AddStringToObject(hw_request_data,"dev_id",dev_hw_id->valuestring);
						cJSON_AddStringToObject(hw_request_data,"dev_type",dev_hw_type->valuestring);
						cJSON *hw_request_cmd = cJSON_CreateObject();
						cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
						cJSON_AddStringToObject(hw_request_cmd,"cmd",hw_cmd->valuestring);
						char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
						int my_len = strlen(hw_request_char);
						char *my_send_char = (char *)malloc(my_len+2);
						memset(my_send_char,0,my_len+2);
						memcpy(my_send_char,hw_request_char,my_len);
						strcat(my_send_char,"\n\0");
						send(cd,my_send_char,my_len+1,0);
						cJSON_Delete(hw_request_root);
						hw_request_root = NULL;
						free(hw_request_char);
						hw_request_char = NULL;
						free(my_send_char);
						my_send_char=NULL;
					}
					else
					{
						while(kt_while != NULL)
						{
							if(strcmp(kt_while->string,dev_hw_lid->valuestring)==0)
							{
								cJSON *my_hw_lid = cJSON_GetObjectItem(kt_root,dev_hw_lid->valuestring);
								cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"code");
								int str_len = strlen(my_code->valuestring)+56;
								uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
								memset(final_cmd,0,str_len/2);
								cmd_mix_kt(dev_hw_lid->valuestring,hw_cmd->valuestring,my_code->valuestring,dev_hw_mac->valuestring,dev_hw_id->valuestring,str_len,final_cmd);
								find_mac_and_send(dev_hw_mac->valuestring,final_cmd,str_len/2);
								free(final_cmd);
								final_cmd = NULL;
								break;
							}
							kt_while = kt_while->next;
							if(kt_while==NULL)
							{
								cJSON *hw_request_root = cJSON_CreateObject();
								cJSON_AddStringToObject(hw_request_root,"co","orange");
								cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
								cJSON *hw_request_data = cJSON_CreateObject();
								cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
								cJSON_AddStringToObject(hw_request_data,"mac",dev_hw_mac->valuestring);
								cJSON_AddStringToObject(hw_request_data,"lid",dev_hw_lid->valuestring);
								cJSON_AddStringToObject(hw_request_data,"dev_id",dev_hw_id->valuestring);
								cJSON_AddStringToObject(hw_request_data,"dev_type",dev_hw_type->valuestring);
								cJSON *hw_request_cmd = cJSON_CreateObject();
								cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
								cJSON *hw_cmd = cJSON_GetObjectItem(dev_hw_cmd,"cmd");
								cJSON_AddStringToObject(hw_request_cmd,"cmd",hw_cmd->valuestring);
								char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
								int my_len = strlen(hw_request_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,hw_request_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								cJSON_Delete(hw_request_root);
								hw_request_root = NULL;
								free(hw_request_char);
								hw_request_char = NULL;
								free(my_send_char);
								my_send_char=NULL;
							}
						}
					}
				}
			}
			else if(strcmp(dev_hw_cmd->child->string,"key")==0)
			{
				cJSON *hw_cmd = cJSON_GetObjectItem(dev_hw_cmd,"key");
				cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
				if(fkt_root != NULL)
				{
					cJSON *fkt_while = fkt_root->child;
					if(fkt_while==NULL)
					{
						cJSON *hw_request_root = cJSON_CreateObject();
						cJSON_AddStringToObject(hw_request_root,"co","orange");
						cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
						cJSON *hw_request_data = cJSON_CreateObject();
						cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
						cJSON_AddStringToObject(hw_request_data,"mac",dev_hw_mac->valuestring);
						cJSON_AddStringToObject(hw_request_data,"lid",dev_hw_lid->valuestring);
						cJSON_AddStringToObject(hw_request_data,"dev_id",dev_hw_id->valuestring);
						cJSON_AddStringToObject(hw_request_data,"dev_type",dev_hw_type->valuestring);
						cJSON *hw_request_cmd = cJSON_CreateObject();
						cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
						cJSON_AddStringToObject(hw_request_cmd,"key",hw_cmd->valuestring);
						char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
						int my_len = strlen(hw_request_char);
						char *my_send_char = (char *)malloc(my_len+2);
						memset(my_send_char,0,my_len+2);
						memcpy(my_send_char,hw_request_char,my_len);
						strcat(my_send_char,"\n\0");
						send(cd,my_send_char,my_len+1,0);
						cJSON_Delete(hw_request_root);
						hw_request_root = NULL;
						free(hw_request_char);
						hw_request_char = NULL;
						free(my_send_char);
						my_send_char=NULL;
					}
					else
					{
						while(fkt_while != NULL)
						{
							if(strcmp(fkt_while->string,dev_hw_lid->valuestring)==0)//先找码库id
							{
								cJSON *my_hw_lid = cJSON_GetObjectItem(fkt_root,dev_hw_lid->valuestring);
								cJSON *my_hw_lid_while = my_hw_lid->child;
								while(my_hw_lid_while != NULL)
								{
									if(strcmp(my_hw_lid_while->string,hw_cmd->valuestring)==0)//再找键值
									{
										cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,hw_cmd->valuestring);
										int str_len = strlen(my_code->valuestring)+30;
										uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
										memset(final_cmd,0,str_len/2);
										cmd_mix_fkt(my_code->valuestring,dev_hw_mac->valuestring,str_len,final_cmd);
										find_mac_and_send(dev_hw_mac->valuestring,final_cmd,str_len/2);
										free(final_cmd);
										final_cmd=NULL;
										break;
									}
									my_hw_lid_while = my_hw_lid_while->next;
									if(my_hw_lid_while == NULL)
									{
										cJSON *hw_request_root = cJSON_CreateObject();
										cJSON_AddStringToObject(hw_request_root,"co","orange");
										cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
										cJSON *hw_request_data = cJSON_CreateObject();
										cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
										cJSON_AddStringToObject(hw_request_data,"mac",dev_hw_mac->valuestring);
										cJSON_AddStringToObject(hw_request_data,"lid",dev_hw_lid->valuestring);
										cJSON_AddStringToObject(hw_request_data,"dev_id",dev_hw_id->valuestring);
										cJSON_AddStringToObject(hw_request_data,"dev_type",dev_hw_type->valuestring);
										cJSON *hw_request_cmd = cJSON_CreateObject();
										cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
										cJSON_AddStringToObject(hw_request_cmd,"key",hw_cmd->valuestring);
										char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
										int my_len = strlen(hw_request_char);
										char *my_send_char = (char *)malloc(my_len+2);
										memset(my_send_char,0,my_len+2);
										memcpy(my_send_char,hw_request_char,my_len);
										strcat(my_send_char,"\n\0");
										send(cd,my_send_char,my_len+1,0);
										cJSON_Delete(hw_request_root);
										hw_request_root = NULL;
										free(hw_request_char);
										hw_request_char = NULL;
										free(my_send_char);
										my_send_char=NULL;
									}
								}
								break;
							}
							fkt_while = fkt_while->next;
							if(fkt_while==NULL)
							{
								cJSON *hw_request_root = cJSON_CreateObject();
								cJSON_AddStringToObject(hw_request_root,"co","orange");
								cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
								cJSON *hw_request_data = cJSON_CreateObject();
								cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
								cJSON_AddStringToObject(hw_request_data,"mac",dev_hw_mac->valuestring);
								cJSON_AddStringToObject(hw_request_data,"lid",dev_hw_lid->valuestring);
								cJSON_AddStringToObject(hw_request_data,"dev_id",dev_hw_id->valuestring);
								cJSON_AddStringToObject(hw_request_data,"dev_type",dev_hw_type->valuestring);
								cJSON *hw_request_cmd = cJSON_CreateObject();
								cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
								cJSON_AddStringToObject(hw_request_cmd,"key",hw_cmd->valuestring);
								char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
								int my_len = strlen(hw_request_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,hw_request_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								cJSON_Delete(hw_request_root);
								hw_request_root = NULL;
								free(hw_request_char);
								hw_request_char = NULL;
								free(my_send_char);
								my_send_char=NULL;
							}
						}
					}
				}
			}
		}
	}
	cJSON_Delete(code_id_root);
	code_id_root=NULL;
}
void up_hw_code(cJSON *root)
{
	cJSON *up_data = cJSON_GetObjectItem(root,"data");
	cJSON *up_lid = cJSON_GetObjectItem(up_data,"lid");
	pthread_mutex_lock(&mutex_code);
	cJSON *code_id_root = cJSON_Parse(code_id);
	if(code_id_root != NULL)
	{
		if(code_id_root->child != NULL)
		{
			cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
			if(kt_root != NULL)
			{
				cJSON *kt_while = kt_root->child;
				while(kt_while != NULL)
				{
					if(strcmp(kt_while->string,up_lid->valuestring)==0)
					{
						cJSON_DeleteItemFromObject(kt_root,up_lid->valuestring);
						char *code_char = cJSON_PrintUnformatted(code_id_root);
						memset(code_id,0,BUFFSIZE);
						memcpy(code_id,code_char,strlen(code_char));
						int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
						write(code_fd,code_char,strlen(code_char));
						fsync(code_fd);
						close(code_fd);
						free(code_char);
						code_char=NULL;
						break;
					}
					kt_while = kt_while->next;
				}
			}
			cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
			if(fkt_root != NULL)
			{
				cJSON *fkt_while = fkt_root->child;
				while(fkt_while != NULL)
				{
					if(strcmp(fkt_while->string,up_lid->valuestring)==0)
					{
						cJSON_DeleteItemFromObject(fkt_root,up_lid->valuestring);
						char *code_char = cJSON_PrintUnformatted(code_id_root);
						memset(code_id,0,BUFFSIZE);
						memcpy(code_id,code_char,strlen(code_char));
						int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
						write(code_fd,code_char,strlen(code_char));
						fsync(code_fd);
						close(code_fd);
						free(code_char);
						code_char=NULL;
						break;
					}
					fkt_while = fkt_while->next;
				}
			}
		}
	}
	pthread_mutex_unlock(&mutex_code);
	cJSON_Delete(code_id_root);
	code_id_root=NULL;
}
void get_new_lid_ver(cJSON *root)
{
	cJSON *up_data = cJSON_GetObjectItem(root,"data");
	int num = cJSON_GetArraySize(up_data);
	int j;
	cJSON *arr_for = NULL;
	cJSON *my_code_num = NULL;
	cJSON *my_code_ver = NULL;
	for(j=0;j<num;j++)
	{
		arr_for = cJSON_GetArrayItem(up_data,j);
		my_code_num = cJSON_GetObjectItem(arr_for,"lid");
		my_code_ver = cJSON_GetObjectItem(arr_for,"ver");
		pthread_mutex_lock(&mutex_code);
		cJSON *code_id_root = cJSON_Parse(code_id);
		if(code_id_root != NULL)
		{
			if(code_id_root->child != NULL)
			{
				cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
				if(kt_root != NULL)
				{
					cJSON *kt_while = kt_root->child;
					while(kt_while != NULL)
					{
						if(strcmp(kt_while->string,my_code_num->valuestring)==0)
						{
							cJSON *code_num_root = cJSON_GetObjectItem(kt_root,my_code_num->valuestring);
							cJSON *code_version = cJSON_GetObjectItem(code_num_root,"ver");
							if(strcmp(code_version->valuestring,my_code_ver->valuestring))
							{
								cJSON_DeleteItemFromObject(kt_root,my_code_num->valuestring);
								char *code_char = cJSON_PrintUnformatted(code_id_root);
								memset(code_id,0,BUFFSIZE);
								memcpy(code_id,code_char,strlen(code_char));
								int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(code_fd,code_char,strlen(code_char));
								fsync(code_fd);
								close(code_fd);
								free(code_char);
								code_char=NULL;
							}
							break;
						}
						kt_while = kt_while->next;
					}
				}
				cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
				if(fkt_root != NULL)
				{
					cJSON *fkt_while = fkt_root->child;
					while(fkt_while != NULL)
					{
						if(strcmp(fkt_while->string,my_code_num->valuestring)==0)
						{
							cJSON *code_num_root = cJSON_GetObjectItem(fkt_root,my_code_num->valuestring);
							cJSON *code_version = cJSON_GetObjectItem(code_num_root,"ver");
							if(strcmp(code_version->valuestring,my_code_ver->valuestring))
							{
								cJSON_DeleteItemFromObject(fkt_root,my_code_num->valuestring);
								char *code_char = cJSON_PrintUnformatted(code_id_root);
								memset(code_id,0,BUFFSIZE);
								memcpy(code_id,code_char,strlen(code_char));
								int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(code_fd,code_char,strlen(code_char));
								fsync(code_fd);
								close(code_fd);
								free(code_char);
								code_char=NULL;
							}
							break;
						}
						fkt_while = fkt_while->next;
					}
				}
			}
		}
		pthread_mutex_unlock(&mutex_code);
		cJSON_Delete(code_id_root);
		code_id_root=NULL;
	}
}
void get_hw_code_ser(cJSON *root)
{
	cJSON *get_return = cJSON_GetObjectItem(root,"retcode");
	if(get_return->valueint ==0)
	{
		cJSON *get_hw_code_data = cJSON_GetObjectItem(root,"data");
		cJSON *get_hw_mac = cJSON_GetObjectItem(get_hw_code_data,"mac");
		cJSON *get_hw_id = cJSON_GetObjectItem(get_hw_code_data,"dev_id");
		cJSON *get_hw_lid = cJSON_GetObjectItem(get_hw_code_data,"lid");
		cJSON *get_cmd = cJSON_GetObjectItem(get_hw_code_data,"dev_cmd");
		cJSON *cmd_zx = cJSON_GetObjectItem(get_cmd,get_cmd->child->string);
		cJSON *get_code = cJSON_GetObjectItem(get_hw_code_data,"code");
		cJSON *get_version = cJSON_GetObjectItem(get_hw_code_data,"ver");
		if(strcmp(get_cmd->child->string,"cmd")==0)
		{
			int str_len = strlen(get_code->valuestring)+56;
			if(str_len%2==0)
			{
				uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
				memset(final_cmd,0,str_len/2);
				cmd_mix_kt(get_hw_lid->valuestring,cmd_zx->valuestring,get_code->valuestring,get_hw_mac->valuestring,get_hw_id->valuestring,str_len,final_cmd);
				find_mac_and_send(get_hw_mac->valuestring,final_cmd,str_len/2);
				free(final_cmd);
				final_cmd=NULL;
				pthread_mutex_lock(&mutex_code);
				cJSON *code_id_root = cJSON_Parse(code_id);
				if(code_id_root != NULL)
				{
					if(code_id_root->child != NULL)
					{
						cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
						cJSON *kt_root_while = kt_root->child;
						if(kt_root_while == NULL)
						{
							cJSON *my_lid = cJSON_CreateObject();
							cJSON_AddItemToObject(kt_root,get_hw_lid->valuestring,my_lid);
							cJSON_AddStringToObject(my_lid,"code",get_code->valuestring);
							cJSON_AddStringToObject(my_lid,"ver",get_version->valuestring);
							char *code_char = cJSON_PrintUnformatted(code_id_root);
							memset(code_id,0,BUFFSIZE);
							memcpy(code_id,code_char,strlen(code_char));
							int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
							write(code_fd,code_char,strlen(code_char));
							fsync(code_fd);
							close(code_fd);
							free(code_char);
							code_char = NULL;
						}
						else
						{
							while(kt_root_while != NULL)
							{
								if(strcmp(kt_root_while->string,get_hw_lid->valuestring)==0)//找到了相同的lid
								{
									cJSON_DeleteItemFromObject(kt_root,get_hw_lid->valuestring);
									cJSON *my_lid = cJSON_CreateObject();
									cJSON_AddItemToObject(kt_root,get_hw_lid->valuestring,my_lid);
									cJSON_AddStringToObject(my_lid,"code",get_code->valuestring);
									cJSON_AddStringToObject(my_lid,"ver",get_version->valuestring);
									char *code_char = cJSON_PrintUnformatted(code_id_root);
									memset(code_id,0,BUFFSIZE);
									memcpy(code_id,code_char,strlen(code_char));
									int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
									write(code_fd,code_char,strlen(code_char));
									fsync(code_fd);
									close(code_fd);
									free(code_char);
									code_char = NULL;
									break;
								}
								kt_root_while = kt_root_while->next;
								if(kt_root_while==NULL)
								{
									cJSON *my_lid = cJSON_CreateObject();
									cJSON_AddItemToObject(kt_root,get_hw_lid->valuestring,my_lid);
									cJSON_AddStringToObject(my_lid,"code",get_code->valuestring);
									cJSON_AddStringToObject(my_lid,"ver",get_version->valuestring);
									char *code_char = cJSON_PrintUnformatted(code_id_root);
									memset(code_id,0,BUFFSIZE);
									memcpy(code_id,code_char,strlen(code_char));
									int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
									write(code_fd,code_char,strlen(code_char));
									fsync(code_fd);
									close(code_fd);
									free(code_char);
									code_char = NULL;
								}
							}
						}
					}
				}
				pthread_mutex_unlock(&mutex_code);
				cJSON_Delete(code_id_root);
				code_id_root=NULL;
			}
		}
		if(strcmp(get_cmd->child->string,"key")==0)
		{
			int str_len = strlen(get_code->valuestring)+30;
			if(str_len%2==0)
			{
				uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
				memset(final_cmd,0,str_len/2);
				cmd_mix_fkt(get_code->valuestring,get_hw_mac->valuestring,str_len,final_cmd);
				find_mac_and_send(get_hw_mac->valuestring,final_cmd,str_len/2);
				free(final_cmd);
				final_cmd=NULL;
				pthread_mutex_lock(&mutex_code);
				cJSON *code_id_root = cJSON_Parse(code_id);
				if(code_id_root != NULL)
				{
					if(code_id_root->child != NULL)
					{
						cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
						cJSON *fkt_root_while = fkt_root->child;
						if(fkt_root->child == NULL)
						{
							cJSON *my_lid = cJSON_CreateObject();
							cJSON_AddItemToObject(fkt_root,get_hw_lid->valuestring,my_lid);
							cJSON_AddStringToObject(my_lid,cmd_zx->valuestring,get_code->valuestring);
							cJSON_AddStringToObject(my_lid,"ver",get_version->valuestring);
							char *code_char = cJSON_PrintUnformatted(code_id_root);
							memset(code_id,0,BUFFSIZE);
							memcpy(code_id,code_char,strlen(code_char));
							int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
							write(code_fd,code_char,strlen(code_char));
							fsync(code_fd);
							close(code_fd);
							free(code_char);
							code_char=NULL;
						}
						else
						{
							while(fkt_root_while != NULL)
							{
								if(strcmp(fkt_root_while->string,get_hw_lid->valuestring)==0)//判断是否有lid
								{
									cJSON *lid_num = cJSON_GetObjectItem(fkt_root,get_hw_lid->valuestring);
									cJSON *lid_version = cJSON_GetObjectItem(lid_num,"ver");
									if(strcmp(lid_version->valuestring,get_version->valuestring))
									{
										cJSON_DeleteItemFromObject(fkt_root,get_hw_lid->valuestring);
										cJSON *my_lid = cJSON_CreateObject();
										cJSON_AddItemToObject(fkt_root,get_hw_lid->valuestring,my_lid);
										cJSON_AddStringToObject(my_lid,cmd_zx->valuestring,get_code->valuestring);
										cJSON_AddStringToObject(my_lid,"ver",get_version->valuestring);
										char *code_char = cJSON_PrintUnformatted(code_id_root);
										memset(code_id,0,BUFFSIZE);
										memcpy(code_id,code_char,strlen(code_char));
										int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(code_fd,code_char,strlen(code_char));
										fsync(code_fd);
										close(code_fd);
										free(code_char);
										code_char=NULL;
									}
									else
									{
										cJSON *lid_num_while = lid_num->child;
										while(lid_num_while != NULL)
										{
											if(strcmp(lid_num_while->string,cmd_zx->valuestring)==0)//判断是否有相同的key
											{
												cJSON_DeleteItemFromObject(lid_num,cmd_zx->valuestring);
												cJSON_AddStringToObject(lid_num,cmd_zx->valuestring,get_code->valuestring);
												char *code_char = cJSON_PrintUnformatted(code_id_root);
												memset(code_id,0,BUFFSIZE);
												memcpy(code_id,code_char,strlen(code_char));
												int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
												write(code_fd,code_char,strlen(code_char));
												fsync(code_fd);
												close(code_fd);
												free(code_char);
												code_char=NULL;
												break;
											}
											lid_num_while = lid_num_while->next;
											if(lid_num_while == NULL)
											{
												cJSON_AddStringToObject(lid_num,cmd_zx->valuestring,get_code->valuestring);
												char *code_char = cJSON_PrintUnformatted(code_id_root);
												memset(code_id,0,BUFFSIZE);
												memcpy(code_id,code_char,strlen(code_char));
												int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
												write(code_fd,code_char,strlen(code_char));
												fsync(code_fd);
												close(code_fd);
												free(code_char);
												code_char=NULL;
											}
										}
									}
									break;
								}
								fkt_root_while = fkt_root_while->next;
								if(fkt_root_while == NULL)
								{
									cJSON *my_lid = cJSON_CreateObject();
									cJSON_AddItemToObject(fkt_root,get_hw_lid->valuestring,my_lid);
									cJSON_AddStringToObject(my_lid,cmd_zx->valuestring,get_code->valuestring);
									cJSON_AddStringToObject(my_lid,"ver",get_version->valuestring);
									char *code_char = cJSON_PrintUnformatted(code_id_root);
									memset(code_id,0,BUFFSIZE);
									memcpy(code_id,code_char,strlen(code_char));
									int code_fd = open("/root/code.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
									write(code_fd,code_char,strlen(code_char));
									fsync(code_fd);
									close(code_fd);
									free(code_char);
									code_char=NULL; 
								}
							}
						}
					}
				}
				pthread_mutex_unlock(&mutex_code);
				cJSON_Delete(code_id_root);
				code_id_root=NULL;
			}
		}
	}
}
void down_scene_list(char *str)
{
	pthread_mutex_lock(&mutex_scene);
	int scene_list_fd = open("/root/scene_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(scene_list_fd,str,strlen(str));
	fsync(scene_list_fd);
	memset(scene_list,0,BUFFSIZE);
	memcpy(scene_list,str,strlen(str));
	close(scene_list_fd);
	pthread_mutex_unlock(&mutex_scene);
}
void down_room_list(char *str)
{
	pthread_mutex_lock(&mutex_room);
	int room_fd = open("/root/room_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(room_fd,str,strlen(str));
	fsync(room_fd);
	memset(room_list,0,10240);
	memcpy(room_list,str,strlen(str));
	close(room_fd);
	pthread_mutex_unlock(&mutex_room);
}
void down_scene_mx(char *str)
{
	pthread_mutex_lock(&mutex_scene);
	int scene_detail_fd = open("/root/scene_detail.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(scene_detail_fd,str,strlen(str));
	fsync(scene_detail_fd);
	memset(scene_detail,0,819200);
	memcpy(scene_detail,str,strlen(str));
	close(scene_detail_fd);
	pthread_mutex_unlock(&mutex_scene);
}
void down_dev_list(char *str)
{
	pthread_mutex_lock(&mutex_sl);
	int device_list_fd = open("/root/device_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	int my_len = strlen(str);
	write(device_list_fd,str,my_len);
	fsync(device_list_fd);
	memset(device_list,0,819200);
	memcpy(device_list,str,my_len);
	close(device_list_fd);
	pthread_mutex_unlock(&mutex_sl);
	up_dev_des();
}
void down_dev_state_list(char *str)
{
	pthread_mutex_lock(&mutex_zl);
	int device_state_list_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	int my_len = strlen(str);
	memset(device_state_list,0,BUFFSIZE);
	memcpy(device_state_list,str,my_len);
	write(device_state_list_fd,str,my_len);
	fsync(device_state_list_fd);
	close(device_state_list_fd);
	pthread_mutex_unlock(&mutex_zl);
}
void down_bind_list(char *str)
{
	pthread_mutex_lock(&mutex_bl);
	int multi_bind_fd = open("/root/multi_bind.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(multi_bind_fd,str,strlen(str));
	fsync(multi_bind_fd);
	memset(multi_bind,0,BUFFSIZE);
	memcpy(multi_bind,str,strlen(str));
	close(multi_bind_fd);
	pthread_mutex_unlock(&mutex_bl);
}
void down_timer_list(char *str)
{
	pthread_mutex_lock(&mutex_time);
	int timer_list_fd = open("/root/timer_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(timer_list_fd,str,strlen(str));
	fsync(timer_list_fd);
	memset(timer_list,0,BUFFSIZE);
	memcpy(timer_list,str,strlen(str));
	close(timer_list_fd);
	pthread_mutex_unlock(&mutex_time);
}
void down_sec_list(char *str)
{
	pthread_mutex_lock(&mutex_af);
	int secure_set_list_fd = open("/root/secure_set_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(secure_set_list_fd,str,strlen(str));
	fsync(secure_set_list_fd);
	memset(secure_set_list,0,BUFFSIZE);
	memcpy(secure_set_list,str,strlen(str));
	close(secure_set_list_fd);
	pthread_mutex_unlock(&mutex_af);
	update_secure();
}
void down_voice_list(char *str)
{
	pthread_mutex_lock(&mutex_voice);
	int voice_fd = open("/root/voice.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(voice_fd,str,strlen(str));
	fsync(voice_fd);
	memset(voice_list,0,BUFFSIZE);
	memcpy(voice_list,str,strlen(str));
	close(voice_fd); 
	pthread_mutex_unlock(&mutex_voice);
}
void get_identify(cJSON *root)
{
	cJSON *ret_value = cJSON_GetObjectItem(root,"retcode");
	usleep(100000);
	if(ret_value->valueint)
	kill_gateway();
	identify_flag=1;
	NET_FLAG = 1;
	file_init_net();
	cJSON *gw_identify_data=cJSON_GetObjectItem(root,"data");
	//////////////////////////////////////////////////////////////////////////////////////
	cJSON *dev_list_ver=cJSON_GetObjectItem(gw_identify_data,"dev_list_ver");
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_pase=cJSON_Parse(device_list);
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_pase->child != NULL)
	{
		cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_pase,"data");
		cJSON *my_dev_list_ver = cJSON_GetObjectItem(my_dev_list_data,"dev_ver");
		if(strcmp(dev_list_ver->valuestring,my_dev_list_ver->valuestring))
		{
			dev_list_rq();
			usleep(10000);
		}
	}
	else
	{
		dev_list_rq();
	}
	cJSON_Delete(dev_list_pase);
	dev_list_pase=NULL;
	///////////////////////////////////////////////////////////////////////////////////
	cJSON *scene_ver=cJSON_GetObjectItem(gw_identify_data,"scene_ver");
	pthread_mutex_lock(&mutex_scene);
	cJSON *scene_list_pase=cJSON_Parse(scene_list);
	pthread_mutex_unlock(&mutex_scene);
	if(scene_list_pase->child != NULL)
	{
		cJSON *scene_list_pase_data = cJSON_GetObjectItem(scene_list_pase,"data");
		cJSON *scene_list_ver = cJSON_GetObjectItem(scene_list_pase_data,"scene_ver");
		if(strcmp(scene_list_ver->valuestring,scene_ver->valuestring))
		{
			scene_list_rq();
			usleep(10000);
			scene_detail_rq();
			usleep(10000);
		}
	}
	else
	{
		scene_list_rq();
		usleep(10000);
		scene_detail_rq();
	}
	cJSON_Delete(scene_list_pase);
	scene_list_pase=NULL;
	/////////////////////////////////////////////////////////////////////////////////////
	cJSON *timer_ver=cJSON_GetObjectItem(gw_identify_data,"timer_ver");
	pthread_mutex_lock(&mutex_time);
	cJSON *timer_list_pase=cJSON_Parse(timer_list);
	pthread_mutex_unlock(&mutex_time);
	if(timer_list_pase->child != NULL)
	{
		cJSON *timer_list_pase_data = cJSON_GetObjectItem(timer_list_pase,"data");
		cJSON *timer_list_ver = cJSON_GetObjectItem(timer_list_pase_data,"timer_ver");
		if(strcmp(timer_list_ver->valuestring,timer_ver->valuestring))
		{
			timer_list_rq();
			usleep(10000);
		}
	}
	else
		timer_list_rq();
	cJSON_Delete(timer_list_pase);
	timer_list_pase=NULL;
	///////////////////////////////////////////////////////////////////////////////////////
	cJSON *bind_ver=cJSON_GetObjectItem(gw_identify_data,"bind_ver");
	pthread_mutex_lock(&mutex_bl);
	cJSON *multi_bind_pase=cJSON_Parse(multi_bind);
	pthread_mutex_unlock(&mutex_bl);
	if(multi_bind_pase->child != NULL)
	{
		cJSON *multi_bind_pase_data = cJSON_GetObjectItem(multi_bind_pase,"data");
		cJSON *multi_bind_ver = cJSON_GetObjectItem(multi_bind_pase_data,"bind_ver");
		if(strcmp(multi_bind_ver->valuestring,bind_ver->valuestring))
		{
			multi_bind_rq();
			usleep(10000);
		}
	}
	else
		multi_bind_rq();
	cJSON_Delete(multi_bind_pase);
	multi_bind_pase=NULL;
	////////////////////////////////////////////////////////////////////////////////////////////
	cJSON *model_set_ver=cJSON_GetObjectItem(gw_identify_data,"model_set_ver");
	pthread_mutex_lock(&mutex_af);
	cJSON *secure_set_list_pase=cJSON_Parse(secure_set_list);
	pthread_mutex_unlock(&mutex_af);
	if(secure_set_list_pase->child != NULL)
	{
		cJSON *secure_set_list_pase_data = cJSON_GetObjectItem(secure_set_list_pase,"data");
		cJSON *secure_set_list_ver = cJSON_GetObjectItem(secure_set_list_pase_data,"model_set_ver");
		if(strcmp(secure_set_list_ver->valuestring,model_set_ver->valuestring))
		{
			secure_set_list_rq();
			usleep(10000);
		}
	}
	else
		secure_set_list_rq();
	cJSON_Delete(secure_set_list_pase);
	secure_set_list_pase=NULL;
	//////////////////////////////////////////////////////////////////////////////////////////////////
	cJSON *voice_list_ver = cJSON_GetObjectItem(gw_identify_data,"voice_set_ver");
	pthread_mutex_lock(&mutex_voice);
	cJSON *voice_list_pase=cJSON_Parse(voice_list);
	pthread_mutex_unlock(&mutex_voice);
	if(voice_list_pase->child != NULL)
	{
		cJSON *voice_list_pase_data = cJSON_GetObjectItem(voice_list_pase,"data");
		cJSON *voice_set_list_ver = cJSON_GetObjectItem(voice_list_pase_data,"ver");
		if(strcmp(voice_set_list_ver->valuestring,voice_list_ver->valuestring))
		{
			voice_list_rq();
			usleep(10000);
		}
	}
	else
		voice_list_rq();
	cJSON_Delete(voice_list_pase);
	voice_list_pase=NULL;
	/////////////////////////////////////////////////////////////////////////////////////////////////
	cJSON *room_version = cJSON_GetObjectItem(gw_identify_data,"room_ver");
	pthread_mutex_lock(&mutex_room);
	cJSON *room_list_pase=cJSON_Parse(room_list);
	pthread_mutex_unlock(&mutex_room);
	if(room_list_pase->child != NULL)
	{
		cJSON *room_list_pase_data = cJSON_GetObjectItem(room_list_pase,"data");
		cJSON *room_list_ver = cJSON_GetObjectItem(room_list_pase_data,"room_ver");
		if(strcmp(room_version->valuestring,room_list_ver->valuestring))
		{
			room_list_rq();
			usleep(1000);
		}
	}
	else
		room_list_rq();
	cJSON_Delete(room_list_pase);
	room_list_pase=NULL;
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	cJSON *pain_id = cJSON_GetObjectItem(gw_identify_data,"pan_id");
	cJSON *channel = cJSON_GetObjectItem(gw_identify_data,"channel");
	if(pain_id->valuestring != NULL && channel->valuestring != NULL)
	{
		if(pain_id->valuestring[0] != '\0' && channel->valuestring[0] != '\0')
		{
			uint8_t set_id_channel[18] = {0x5a,0xa5,0x12,0x34,0x56,0x78,0x12,0x34,0x56,0x78,0x25,0x00,0x00,0x00,0x03,0x00,0x00,0x00};
			str_to_hex(set_id_channel+15,channel->valuestring,1);
			str_to_hex(set_id_channel+16,pain_id->valuestring,2);
			usart_send(fd,set_id_channel,18);
		}
	}
}
void let_go_to_net(cJSON *root)
{
	cJSON *dev_net_data = cJSON_GetObjectItem(root,"data");
	cJSON *dev_net_cmd = cJSON_GetObjectItem(dev_net_data,"cmd");
	if(strcmp(dev_net_cmd->valuestring,"1")==0)
	{
		uint8_t go_to_net_please[16] = {0x5a,0xa5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x01,0x00};
		usart_send(fd,go_to_net_please,16);
		send_to_son_gw_no(go_to_net_please,16);
	}
	else
	{
		uint8_t go_to_net_forbid[16] = {0x5a,0xa5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x00,0x00,0x01,0x00};
		usart_send(fd,go_to_net_forbid,16);	
		send_to_son_gw_no(go_to_net_forbid,16);
	}
}

void get_signal(void)
{
	typedef struct signal_mac
	{
		cJSON *mac;
		cJSON *dev_id;
		cJSON *dev_type;
		struct signal_mac *next;
	}SIG;
	SIG *sig_head,*sig_z,*sig_d,*p;
	sig_head=sig_z=sig_d=p=NULL;
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	uint8_t final_cmd[16];
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_type = NULL;
			cJSON *tem_id = NULL;
			int i,flag_get;
			for(i=0;i<data_l;i++)
			{
				flag_get = 0;
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
				tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
				if(strcmp(tem_type->valuestring,"010101")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"010102")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"010103")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"010104")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"010201")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"010301")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"010501")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"010601")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"040101")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"040102")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"040201")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"040301")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"080301")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"080401")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"070101")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"0C0101")==0)
					flag_get=1;
				else if(strcmp(tem_type->valuestring,"0D0101")==0)
					flag_get=1;
				if( flag_get )
				{
					if(sig_head==NULL)
					{
						sig_d = (SIG *)malloc(sizeof(SIG));
						memset(sig_d,0,sizeof(SIG));
						sig_d->mac = tem_mac;
						sig_d->dev_id = tem_id;
						sig_d->dev_type = tem_type;
						sig_head = sig_z = sig_d;
						sig_d->next = NULL;
					}
					else
					{
						p=sig_head;
						while(p != NULL)
						{
							if(strcmp(tem_mac->valuestring,p->mac->valuestring)==0)
								break;
							p = p->next;
							if(p==NULL)
							{
								sig_d = (SIG *)malloc(sizeof(SIG));
								memset(sig_d,0,sizeof(SIG));
								sig_d->mac = tem_mac;
								sig_d->dev_id = tem_id;
								sig_d->dev_type = tem_type;
								sig_z->next = sig_d;
								sig_d->next = NULL;
								sig_z = sig_d;
							}
						}
					}
				}
			}
			p = sig_head;
			while(p != NULL)
			{
				memset(final_cmd,0,16);
				cmd_mix_get_signal(p->mac->valuestring,"00",final_cmd);
				resend_zt(16,final_cmd,p->dev_id->valuestring,p->dev_type->valuestring);
				find_mac_and_send(p->mac->valuestring,final_cmd,16);
				usleep(200000);
				p = p->next;
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
	while(sig_head!=NULL)
	{
		p = sig_head;
		sig_head = sig_head->next;
		free(p);
		p=NULL;
	}
}

/*****************************************************************************************************************/
void voice_com_con_u(int i,uint8_t *u_data,char *u_data_str)
{
	char data_str[5];//命令编号
	memset(data_str,0,5);
	memcpy(data_str,u_data_str+38,4);
	data_str[4]='\0';
	char mac_str[17];//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	char port_str[3];//端口号
	memset(port_str,0,3);
	memcpy(port_str,u_data_str+22,2);
	port_str[2] = '\0';
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l_dev_list =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_port = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l_dev_list;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
				if(strcmp(tem_mac->valuestring,mac_str)==0 && strcmp(tem_port->valuestring,port_str)==0)
				{
					tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
					pthread_mutex_lock(&mutex_voice);
					cJSON *voice_list_root = cJSON_Parse(voice_list);//遍历离线语音列表
					pthread_mutex_unlock(&mutex_voice);
					if(voice_list_root != NULL)
					{
						if(voice_list_root->child != NULL)
						{
							cJSON *voice_list_data = cJSON_GetObjectItem(voice_list_root,"data");
							cJSON *my_voice_list = cJSON_GetObjectItem(voice_list_data,"list");
							if(my_voice_list != NULL)
							{
								cJSON *while_my_voice_list = my_voice_list->child;
								while(while_my_voice_list != NULL)
								{
									if(strcmp(while_my_voice_list->string,tem_id->valuestring)==0)
									{
										cJSON *voice_arr = cJSON_GetObjectItem(my_voice_list,tem_id->valuestring);
										int data_l =  cJSON_GetArraySize(voice_arr);
										cJSON *arr_jx = NULL;
										cJSON *voice_num = NULL;
										int j;
										for(j=0;j<data_l;j++)
										{
											arr_jx = cJSON_GetArrayItem(voice_arr,j);
											voice_num = cJSON_GetObjectItem(arr_jx,"voice_cmd");
											if(!strcmp(voice_num->valuestring,data_str))
											{
												cJSON *my_scene_id = cJSON_GetObjectItem(arr_jx,"dev_scen_id");
												if(u_data[18]==0x81 && u_data[19]==0x03)//情景模式
													run_scene(my_scene_id->valuestring);
												else
												{
													int k;
													for(k=0;k<data_l_dev_list;k++)
													{
														data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,k);
														tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
														tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
									 					tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
 														if(!strcmp(tem_id->valuestring,my_scene_id->valuestring))
														{
															tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
															if(!strcmp(tem_type->valuestring,"010101")||!strcmp(tem_type->valuestring,"010103")||!strcmp(tem_type->valuestring,"010104")||!strcmp(tem_type->valuestring,"010501"))//开关类
															{
																uint8_t final_cmd[16];
																memset(final_cmd,0,16);
																if(u_data[21]==0x01)
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"01",final_cmd);
																else
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
																resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
																find_mac_and_send(tem_mac->valuestring,final_cmd,16);
															}
															else if(!strcmp(tem_type->valuestring,"010102"))//86插座
															{
																uint8_t final_cmd[16];
																memset(final_cmd,0,16);
																if(u_data[21]==0x01)
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"01",final_cmd);
																else
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
																resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
																find_mac_and_send(tem_mac->valuestring,final_cmd,16);
															}
															else if(!strcmp(tem_type->valuestring,"010201"))//调光灯
															{
																uint8_t final_cmd[16];
																memset(final_cmd,0,16);
																if(u_data[21]==0x01)
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"ff",final_cmd);
																else
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
																resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
																find_mac_and_send(tem_mac->valuestring,final_cmd,16);
															}
															else if(!strcmp(tem_type->valuestring,"010301"))//RGB
															{
																uint8_t final_cmd[19];
																memset(final_cmd,0,19);
																pthread_mutex_lock(&mutex_zl);
																cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
																pthread_mutex_unlock(&mutex_zl);
																if(device_state_list_data != NULL)
																{
																	if(device_state_list_data->child != NULL)
																	{
																		cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
																		cJSON *while_device_state_list_data = my_device_state_list_data->child;
																		if(while_device_state_list_data==NULL)
																		{
																			if(u_data[21] == 0x01)
																			cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"ffffffff",final_cmd);
																			else if(u_data[21] == 0x00)
																			cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"00000000",final_cmd);
																		}
																		else
																		{
																			while(while_device_state_list_data != NULL)
																			{
																				if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
																				{
																					cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
																					cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
																					if(u_data[21] == 0x01)
																					{
																						if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
																						{
																							my_dev_state->valuestring[6]='f';
																							my_dev_state->valuestring[7]='f';
																						}
																					}
																					else if(u_data[21] == 0x00)
																					{
																						my_dev_state->valuestring[6]='0';
																						my_dev_state->valuestring[7]='0';
																					}
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
																					break;
																				}
																				while_device_state_list_data = while_device_state_list_data->next;
																				if(while_device_state_list_data==NULL)
																				{
																					if(u_data[21] == 0x01)
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"ffffffff",final_cmd);
																					else if(u_data[21] == 0x00)
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"00000000",final_cmd);
																				}
																			}
																		}
																	}
																}
																cJSON_Delete(device_state_list_data);
																device_state_list_data=NULL;
																if(final_cmd[0] != final_cmd[1])
																{
																	resend_zt(19,final_cmd,tem_id->valuestring,tem_type->valuestring);
																	find_mac_and_send(tem_mac->valuestring,final_cmd,19);
																}
															}
															else if(!strcmp(tem_type->valuestring,"010201")||!strcmp(tem_type->valuestring,"040101")||!strcmp(tem_type->valuestring,"040102"))//电池阀||普通窗帘||推窗器
															{
																uint8_t final_cmd[16];
																memset(final_cmd,0,16);
																if(u_data[21]==0x01)
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"01",final_cmd);
																else
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
																resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);	
																find_mac_and_send(tem_mac->valuestring,final_cmd,16);
															}
															else if(!strcmp(tem_type->valuestring,"040201"))//百分比窗帘
															{
																uint8_t final_cmd[16];
																memset(final_cmd,0,16);
																if(u_data[21]==0x01)
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"64",final_cmd);
																else
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
																resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);	
																find_mac_and_send(tem_mac->valuestring,final_cmd,16);
															}
															else if(!strcmp(tem_type->valuestring,"040301"))//百叶窗帘
															{
																uint8_t final_cmd[17];
																memset(final_cmd,0,17);
																if(u_data[21]==0x01)
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"6464",final_cmd);
																else
																cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"0000",final_cmd);
																resend_zt(17,final_cmd,tem_id->valuestring,tem_type->valuestring);	
																find_mac_and_send(tem_mac->valuestring,final_cmd,17);
															}
															else if(!strcmp(tem_type->valuestring,"080401"))//中央空调
															{
																uint8_t final_cmd[25];
																memset(final_cmd,0,25);
																pthread_mutex_lock(&mutex_zl);
																cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
																pthread_mutex_unlock(&mutex_zl);
																if(device_state_list_data != NULL)
																{
																	if(device_state_list_data->child != NULL)
																	{
																		cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
																		cJSON *while_device_state_list_data = my_device_state_list_data->child;
																		if(while_device_state_list_data==NULL)
																		{
																			if(u_data[21] == 0x01)
																			cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"000100010003001a0000",final_cmd);
																			else if(u_data[21] == 0x00)
																			cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"000000010003001a0000",final_cmd);
																		}
																		else
																		{
																			while(while_device_state_list_data != NULL)
																			{
																				if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
																				{
																					cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
																					cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
																					if(u_data[21] == 0x01)
																						my_dev_state->valuestring[3] = '1';
																					else if(u_data[21] == 0x00)
																						my_dev_state->valuestring[3] = '0';
																					else if(u_data[21] == 0x02)
																						my_dev_state->valuestring[7] = '1';
																					else if(u_data[21] == 0x03)
																						my_dev_state->valuestring[7] = '2';
																					else if(u_data[21] == 0x04)
																						my_dev_state->valuestring[7] = '3';
																					else if(u_data[21] == 0x05)
																						my_dev_state->valuestring[7] = '4';
																					else if(u_data[21] == 0x06)
																						my_dev_state->valuestring[7] = '0';
																					else if(u_data[21] == 0x09)
																						my_dev_state->valuestring[11] = '3';
																					else if(u_data[21] == 0x0a)
																						my_dev_state->valuestring[11] = '2';
																					else if(u_data[21] == 0x0b)
																						my_dev_state->valuestring[11] = '1';
																					else if(u_data[21] >= 0x0c && u_data[21] <= 0x1a)
																					{
																						uint8_t temperature = u_data[21] + 0x04;
																						hex_to_str(&temperature,my_dev_state->valuestring+14,1);
																					}
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
																					break;
																				}
																				while_device_state_list_data = while_device_state_list_data->next;
																				if(while_device_state_list_data==NULL)
																				{
																					if(u_data[21] == 0x01)
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"000100010003001a0000",final_cmd);
																					else if(u_data[21] == 0x00)
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"000000010003001a0000",final_cmd);
																				}
																			}
																		}
																	}
																}
																cJSON_Delete(device_state_list_data);
																device_state_list_data=NULL;
																if(final_cmd[0] != final_cmd[1])
																{
																	resend_zt(25,final_cmd,tem_id->valuestring,tem_type->valuestring);
																	find_mac_and_send(tem_mac->valuestring,final_cmd,25);
																}
															}
															else if(!strcmp(tem_type->valuestring,"080301"))////温控器
															{
																uint8_t final_cmd[20];
																memset(final_cmd,0,20);
																pthread_mutex_lock(&mutex_zl);
																cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
																pthread_mutex_unlock(&mutex_zl);
																if(device_state_list_data != NULL)
																{
																	if(device_state_list_data->child != NULL)
																	{
																		cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
																		cJSON *while_device_state_list_data = my_device_state_list_data->child;
																		if(while_device_state_list_data==NULL)
																		{
																			if(u_data[21] == 0x01)
																			cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"0101011a00",final_cmd);
																			else if(u_data[21] == 0x00)
																			cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"0001011a00",final_cmd);
																		}
																		else
																		{
																			while(while_device_state_list_data != NULL)
																			{
																				if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
																				{
																					cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
																					cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
																					if(u_data[21] == 0x01)
																						my_dev_state->valuestring[1] = '1';
																					else if(u_data[21] == 0x00)
																						my_dev_state->valuestring[1] = '0';
																					else if(u_data[21] == 0x02)
																						my_dev_state->valuestring[3] = '1';
																					else if(u_data[21] == 0x03)
																						my_dev_state->valuestring[3] = '2';
																					else if(u_data[21] == 0x04)
																						my_dev_state->valuestring[3] = '3';
																					else if(u_data[21] == 0x05)
																						my_dev_state->valuestring[3] = '4';
																					else if(u_data[21] == 0x06)
																						my_dev_state->valuestring[3] = '0';
																					else if(u_data[21] == 0x09)
																						my_dev_state->valuestring[5] = '3';
																					else if(u_data[21] == 0x0a)
																						my_dev_state->valuestring[5] = '2';
																					else if(u_data[21] == 0x0b)
																						my_dev_state->valuestring[5] = '1';
																					else if(u_data[21] >= 0x0c && u_data[21] <= 0x1a)
																					{
																						uint8_t temperature = u_data[21] + 0x04;
																						hex_to_str(&temperature,my_dev_state->valuestring+6,1);
																					}
																					
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
																					break;
																				}
																				while_device_state_list_data = while_device_state_list_data->next;
																				if(while_device_state_list_data==NULL)
																				{
																					if(u_data[21] == 0x01)
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"0101011a00",final_cmd);
																					else if(u_data[21] == 0x00)
																					cmd_mix_47(tem_mac->valuestring,tem_port->valuestring,"0001011a00",final_cmd);
																				}
																			}
																		}
																	}
																}
																cJSON_Delete(device_state_list_data);
																device_state_list_data=NULL;
																if(final_cmd[0] != final_cmd[1])
																{
																	resend_zt(20,final_cmd,tem_id->valuestring,tem_type->valuestring);
																	find_mac_and_send(tem_mac->valuestring,final_cmd,20);
																}
															}
															else if(!strcmp(tem_type->valuestring,"050101"))//kt
															{
																cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
																int str_len = strlen(tem_lid->valuestring);
																if(str_len)
																{
																	pthread_mutex_lock(&mutex_code);
																	cJSON *code_id_root = cJSON_Parse(code_id);
																	pthread_mutex_unlock(&mutex_code);
																	if(code_id_root != NULL)
																	{
																		if(code_id_root->child != NULL)
																		{
																			cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
																			if(kt_root != NULL)
																			{
																				cJSON *kt_while = kt_root->child;
																				if(kt_while==NULL && NET_FLAG)
																				{
																					cJSON *hw_request_root = cJSON_CreateObject();
																					cJSON_AddStringToObject(hw_request_root,"co","orange");
																					cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
																					cJSON *hw_request_data = cJSON_CreateObject();
																					cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
																					cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
																					cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
																					cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
																					cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
																					cJSON *hw_request_cmd = cJSON_CreateObject();
																					cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
																					cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201010102");
																					char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
																					int my_len = strlen(hw_request_char);
																					char *my_send_char = (char *)malloc(my_len+2);
																					memset(my_send_char,0,my_len+2);
																					memcpy(my_send_char,hw_request_char,my_len);
																					strcat(my_send_char,"\n\0");
																					send(cd,my_send_char,my_len+1,0);
																					cJSON_Delete(hw_request_root);
																					hw_request_root = NULL;
																					free(hw_request_char);
																					hw_request_char = NULL;
																					free(my_send_char);
																					my_send_char=NULL;
																				}
																				else
																				{
																					while(kt_while != NULL)
																					{
																						if(strcmp(kt_while->string,tem_lid->valuestring)==0)
																						{
																							cJSON *my_hw_lid = cJSON_GetObjectItem(kt_root,tem_lid->valuestring);
																							cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"code");
																							str_len = strlen(my_code->valuestring)+56;
																							uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
																							memset(final_cmd,0,str_len/2);
																							pthread_mutex_lock(&mutex_zl);
																							cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
																							pthread_mutex_unlock(&mutex_zl);
																							if(device_state_list_data != NULL)
																							{
																								if(device_state_list_data->child != NULL)
																								{
																									cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
																									cJSON *while_device_state_list_data = my_device_state_list_data->child;
																									if(while_device_state_list_data==NULL)
																									cmd_mix_kt(tem_lid->valuestring,"1a010201010102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
																									else
																									{
																										while(while_device_state_list_data != NULL)
																										{
																											if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
																											{
																												cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
																												cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
																												if(u_data[21]==0x01)//开
																												{
																													my_dev_state->valuestring[8] = '0';
																													my_dev_state->valuestring[9] = '1';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '1';
																												}
																												else if(u_data[21]==0x00)//关
																												{
																													my_dev_state->valuestring[8] = '0';
																													my_dev_state->valuestring[9] = '0';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '1';
																												}
																												else if(u_data[21]==0x02)//制冷模式
																												{
																													my_dev_state->valuestring[12] = '0';
																													my_dev_state->valuestring[13] = '2';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '2';
																												}
																												else if(u_data[21]==0x03)//制热模式
																												{
																													my_dev_state->valuestring[12] = '0';
																													my_dev_state->valuestring[13] = '5';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '2';
																												}
																												else if(u_data[21]==0x04)//除湿模式
																												{
																													my_dev_state->valuestring[12] = '0';
																													my_dev_state->valuestring[13] = '3';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '2';
																												}
																												else if(u_data[21]==0x05)//送风模式
																												{
																													my_dev_state->valuestring[12] = '0';
																													my_dev_state->valuestring[13] = '4';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '2';
																												}
																												else if(u_data[21]==0x06)//自动模式
																												{
																													my_dev_state->valuestring[12] = '0';
																													my_dev_state->valuestring[13] = '1';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '2';
																												}
																												else if(u_data[21]==0x07)//上下扫风
																												{
																													my_dev_state->valuestring[4] = '0';
																													if(my_dev_state->valuestring[5] == '1')
																														my_dev_state->valuestring[5] = '2';
																													else if(my_dev_state->valuestring[5] == '2')
																														my_dev_state->valuestring[5] = '1';
																													else
																														my_dev_state->valuestring[5] = '2';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '4';
																												}
																												else if(u_data[21]==0x08)//左右扫风
																												{
																													my_dev_state->valuestring[6] = '0';
																													if(my_dev_state->valuestring[7] == '0')
																														my_dev_state->valuestring[7] = '1';
																													else
																														my_dev_state->valuestring[7] = '0';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '5';
																												}
																												else if(u_data[21]==0x09)//高风
																												{
																													my_dev_state->valuestring[2] = '0';
																													my_dev_state->valuestring[3] = '4';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '3';
																												}
																												else if(u_data[21]==0x0a)//中风
																												{
																													my_dev_state->valuestring[2] = '0';
																													my_dev_state->valuestring[3] = '3';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '3';
																												}
																												else if(u_data[21]==0x0b)//低风
																												{
																													my_dev_state->valuestring[2] = '0';
																													my_dev_state->valuestring[3] = '2';
																													my_dev_state->valuestring[10] = '0';
																													my_dev_state->valuestring[11] = '3';
																												}
																												else if(u_data[21]>=0x0c && u_data[21]<=0x1a)//16~30
																												{
																													uint8_t temperature1,temperature2;
																													str_to_hex(&temperature1,my_dev_state->valuestring,1);
																													temperature2 = u_data[21]+0x04;
																													if(temperature1 > temperature2)
																													{
																														my_dev_state->valuestring[10]='0';
																														my_dev_state->valuestring[11]='7';
																														hex_to_str(&temperature2,my_dev_state->valuestring,1);
																													}
																													else if(temperature1 < temperature2)
																													{
																														my_dev_state->valuestring[10]='0';
																														my_dev_state->valuestring[11]='6';
																														hex_to_str(&temperature2,my_dev_state->valuestring,1);
																													}
																												}
																												cmd_mix_kt(tem_lid->valuestring,my_dev_state->valuestring,my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
																												break;
																											}
																											while_device_state_list_data=while_device_state_list_data->next;
																											if(while_device_state_list_data==NULL)
																											cmd_mix_kt(tem_lid->valuestring,"1a010201010102",my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
																										}
																									}
																								}
																							}
																							cJSON_Delete(device_state_list_data);
																							device_state_list_data=NULL;
																							find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
																							free(final_cmd);
																							final_cmd = NULL;
																							usleep(200000);
																							break;
																						}
																						kt_while = kt_while->next;
																						if(kt_while == NULL && NET_FLAG)
																						{
																							cJSON *hw_request_root = cJSON_CreateObject();
																							cJSON_AddStringToObject(hw_request_root,"co","orange");
																							cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
																							cJSON *hw_request_data = cJSON_CreateObject();
																							cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
																							cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
																							cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
																							cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
																							cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
																							cJSON *hw_request_cmd = cJSON_CreateObject();
																							cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
																							cJSON_AddStringToObject(hw_request_cmd,"cmd","1a010201010102");
																							char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
																							int my_len = strlen(hw_request_char);
																							char *my_send_char = (char *)malloc(my_len+2);
																							memset(my_send_char,0,my_len+2);
																							memcpy(my_send_char,hw_request_char,my_len);
																							strcat(my_send_char,"\n\0");
																							send(cd,my_send_char,my_len+1,0);
																							cJSON_Delete(hw_request_root);
																							hw_request_root = NULL;
																							free(hw_request_char);
																							hw_request_char = NULL;
																							free(my_send_char);
																							my_send_char=NULL;
																						}
																					}
																				}
																			}
																		}
																	}
																	cJSON_Delete(code_id_root);
																	code_id_root=NULL;
																}
															}
										
															else if(!strcmp(tem_type->valuestring,"050201")||!strcmp(tem_type->valuestring,"050202")||!strcmp(tem_type->valuestring,"050203")||!strcmp(tem_type->valuestring,"050204")||!strcmp(tem_type->valuestring,"050205"))//电视遥控//电视机顶盒遥控//媒体播放器//功放
															{
																cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
																int str_len = strlen(tem_lid->valuestring);
																if(str_len)
																{
																	pthread_mutex_lock(&mutex_code);
																	cJSON *code_id_root = cJSON_Parse(code_id);
																	pthread_mutex_unlock(&mutex_code);
																	if(code_id_root != NULL)
																	{
																		if(code_id_root->child != NULL)
																		{
																			cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
																			if(fkt_root != NULL)
																			{
																				cJSON *fkt_while = fkt_root->child;
																				if(fkt_while==NULL && NET_FLAG && (u_data[21]>=0x00 && u_data[21]<=0x08))
																				{
																					cJSON *hw_request_root = cJSON_CreateObject();
																					cJSON_AddStringToObject(hw_request_root,"co","orange");
																					cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
																					cJSON *hw_request_data = cJSON_CreateObject();
																					cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
																					cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
																					cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
																					cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
																					cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
																					cJSON *hw_request_cmd = cJSON_CreateObject();
																					cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
																					if(u_data[21]==0x01)
																					cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
																					else if(u_data[21]==0x00)
																					cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
																					else if(u_data[21]==0x02)
																					cJSON_AddStringToObject(hw_request_cmd,"key","ch_add");
																					else if(u_data[21]==0x03)
																					cJSON_AddStringToObject(hw_request_cmd,"key","ch_sub");
																					else if(u_data[21]==0x04)
																					cJSON_AddStringToObject(hw_request_cmd,"key","voice_add");
																					else if(u_data[21]==0x05)
																					cJSON_AddStringToObject(hw_request_cmd,"key","voice_sub");
																					else if(u_data[21]==0x06)
																					cJSON_AddStringToObject(hw_request_cmd,"key","voice_add");
																					else if(u_data[21]==0x07)
																					cJSON_AddStringToObject(hw_request_cmd,"key","voice_sub");
																					else if(u_data[21]==0x08)
																					cJSON_AddStringToObject(hw_request_cmd,"key","voice_no");
																					char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
																					int my_len = strlen(hw_request_char);
																					char *my_send_char = (char *)malloc(my_len+2);
																					memset(my_send_char,0,my_len+2);
																					memcpy(my_send_char,hw_request_char,my_len);
																					strcat(my_send_char,"\n\0");
																					send(cd,my_send_char,my_len+1,0);
																					cJSON_Delete(hw_request_root);
																					hw_request_root = NULL;
																					free(hw_request_char);
																					hw_request_char = NULL;
																					free(my_send_char);
																					my_send_char=NULL;
																				}
																				else
																				{
																					while(fkt_while != NULL)
																					{
																						if(strcmp(fkt_while->string,tem_lid->valuestring)==0)//先找码库id
																						{
																							char *tv_p = NULL;
																							if(u_data[21]==0x01) tv_p="on_off";
																							else if(u_data[21]==0x00) tv_p="on_off";
																							else if(u_data[21]==0x02) tv_p="ch_add";
																							else if(u_data[21]==0x03) tv_p="ch_sub";
																							else if(u_data[21]==0x04) tv_p="voice_add";
																							else if(u_data[21]==0x05) tv_p="voice_sub";
																							else if(u_data[21]==0x06) tv_p="voice_add";
																							else if(u_data[21]==0x07) tv_p="voice_sub";
																							else if(u_data[21]==0x08) tv_p="voice_no";
																							else break;
																							cJSON *my_hw_lid = cJSON_GetObjectItem(fkt_root,tem_lid->valuestring);
																							cJSON *my_hw_lid_while = my_hw_lid->child;
																							while(my_hw_lid_while != NULL)
																							{
																								if(strcmp(my_hw_lid_while->string,tv_p)==0)//再找键值
																								{
																									cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,my_hw_lid_while->string);
																									int str_len = strlen(my_code->valuestring)+30;
																									uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
																									memset(final_cmd,0,str_len/2);
																									cmd_mix_fkt(my_code->valuestring,tem_mac->valuestring,str_len,final_cmd);
																									find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
																									free(final_cmd);
																									final_cmd=NULL;
																									break;
																								}
																								my_hw_lid_while = my_hw_lid_while->next;
																								if(my_hw_lid_while == NULL && NET_FLAG && (u_data[21]>=0x00 && u_data[21]<=0x08))
																								{
																									cJSON *hw_request_root = cJSON_CreateObject();
																									cJSON_AddStringToObject(hw_request_root,"co","orange");
																									cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
																									cJSON *hw_request_data = cJSON_CreateObject();
																									cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
																									cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
																									cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
																									cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
																									cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
																									cJSON *hw_request_cmd = cJSON_CreateObject();
																									cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
																									if(u_data[21]==0x01)
																									cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
																									else if(u_data[21]==0x00)
																									cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
																									else if(u_data[21]==0x02)
																									cJSON_AddStringToObject(hw_request_cmd,"key","ch_add");
																									else if(u_data[21]==0x03)
																									cJSON_AddStringToObject(hw_request_cmd,"key","ch_sub");
																									else if(u_data[21]==0x04)
																									cJSON_AddStringToObject(hw_request_cmd,"key","voice_add");
																									else if(u_data[21]==0x05)
																									cJSON_AddStringToObject(hw_request_cmd,"key","voice_sub");
																									else if(u_data[21]==0x06)
																									cJSON_AddStringToObject(hw_request_cmd,"key","voice_add");
																									else if(u_data[21]==0x07)
																									cJSON_AddStringToObject(hw_request_cmd,"key","voice_sub");
																									else if(u_data[21]==0x08)
																									cJSON_AddStringToObject(hw_request_cmd,"key","voice_no");
																									char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
																									int my_len = strlen(hw_request_char);
																									char *my_send_char = (char *)malloc(my_len+2);
																									memset(my_send_char,0,my_len+2);
																									memcpy(my_send_char,hw_request_char,my_len);
																									strcat(my_send_char,"\n\0");
																									send(cd,my_send_char,my_len+1,0);
																									cJSON_Delete(hw_request_root);
																									hw_request_root = NULL;
																									free(hw_request_char);
																									hw_request_char = NULL;
																									free(my_send_char);
																									my_send_char=NULL;
																								}
																							}
																							break;
																						}
																						fkt_while = fkt_while->next;
																						if(fkt_while==NULL && NET_FLAG && (u_data[21]>=0x00 && u_data[21]<=0x08))
																						{
																							cJSON *hw_request_root = cJSON_CreateObject();
																							cJSON_AddStringToObject(hw_request_root,"co","orange");
																							cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
																							cJSON *hw_request_data = cJSON_CreateObject();
																							cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
																							cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
																							cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
																							cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
																							cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
																							cJSON *hw_request_cmd = cJSON_CreateObject();
																							cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
																							if(u_data[21]==0x01)
																							cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
																							else if(u_data[21]==0x00)
																							cJSON_AddStringToObject(hw_request_cmd,"key","on_off");
																							else if(u_data[21]==0x02)
																							cJSON_AddStringToObject(hw_request_cmd,"key","ch_add");
																							else if(u_data[21]==0x03)
																							cJSON_AddStringToObject(hw_request_cmd,"key","ch_sub");
																							else if(u_data[21]==0x04)
																							cJSON_AddStringToObject(hw_request_cmd,"key","voice_add");
																							else if(u_data[21]==0x05)
																							cJSON_AddStringToObject(hw_request_cmd,"key","voice_sub");
																							else if(u_data[21]==0x06)
																							cJSON_AddStringToObject(hw_request_cmd,"key","voice_add");
																							else if(u_data[21]==0x07)
																							cJSON_AddStringToObject(hw_request_cmd,"key","voice_sub");
																							else if(u_data[21]==0x08)
																							cJSON_AddStringToObject(hw_request_cmd,"key","voice_no");
																							char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
																							int my_len = strlen(hw_request_char);
																							char *my_send_char = (char *)malloc(my_len+2);
																							memset(my_send_char,0,my_len+2);
																							memcpy(my_send_char,hw_request_char,my_len);
																							strcat(my_send_char,"\n\0");
																							send(cd,my_send_char,my_len+1,0);
																							cJSON_Delete(hw_request_root);
																							hw_request_root = NULL;
																							free(hw_request_char);
																							hw_request_char = NULL;
																							free(my_send_char);
																							my_send_char=NULL;
																						}
																					}
																				}
																			}
																		}
																	}
																	cJSON_Delete(code_id_root);
																	code_id_root= NULL;
																}
															}
															break;
														}//
													}
												}
												break;
											}
										}
										break;
									}
									while_my_voice_list = while_my_voice_list->next;
								}
							}
						}
					}
					cJSON_Delete(voice_list_root);
					voice_list_root = NULL;
					break;
				}
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data = NULL;
}
void dev_com_con_u(int i,int u_data_len,uint8_t *u_data,char *u_data_str)
{
	int flag_kg=2;
	int kg,data_len = (u_data_len-15)*2;
	char *data_str = NULL;
	data_str= (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+30,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	char *port_str = NULL;
	port_str = (char*)malloc(3);//端口号
	memset(port_str,0,3);
	memcpy(port_str,u_data_str+22,2);
	port_str[2] = '\0';
	if(go_net_flag==1)
	{
		uint8_t *req_des_cmd = NULL;
		req_des_cmd = (uint8_t *)malloc(16);
		memset(req_des_cmd,0,16);
		cmd_request_describ_mix(mac_str,"00",req_des_cmd);
		find_mac_and_send(mac_str,req_des_cmd,16);
		free(req_des_cmd);
		req_des_cmd=NULL;
	}
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_port = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
				if(strcmp(tem_mac->valuestring,mac_str)==0 && strcmp(tem_port->valuestring,port_str)==0)
				{
					tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
					tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
					flag_kg=2;
					if(strcmp(tem_type->valuestring,"010101")==0)//qbkg
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"010102")==0)
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else if(strcmp(data_str,"01")==0)
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"010103")==0)
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"010104")==0)
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"010201")==0)
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"010301")==0)
					{
						if(data_str[6]=='0'&&data_str[7]=='0')
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"010501")==0)
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"010601")==0)
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else if(strcmp(data_str,"01")==0)
							flag_kg=1;
					}		 		
					else if(strcmp(tem_type->valuestring,"040101")==0)//ptcl
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else if(strcmp(data_str,"01")==0)
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"040201")==0)
					{
						if(strcmp(data_str,"00")==0)
							flag_kg=0;
						else if(strcmp(data_str,"01")==0)
							flag_kg=1;
					}
					else if(strcmp(tem_type->valuestring,"040301")==0)
					{
						if(data_str[0]=='0'&&data_str[1]=='0')
							flag_kg=0;
						else
							flag_kg=1;
					}	
					if(NET_FLAG && strcmp(tem_type->valuestring,"010401"))
					{
						cJSON *root_u = cJSON_CreateObject();//创建项目
						cJSON *data_object = cJSON_CreateObject();
						cJSON *cmd_dev = cJSON_CreateObject();
						cJSON_AddNumberToObject(root_u,"retcode",0);
						cJSON_AddStringToObject(root_u,"message","success");
						cJSON_AddStringToObject(root_u,"api","devStateRes");
						cJSON_AddItemToObject(root_u,"data",data_object);
						cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
						cJSON_AddStringToObject(data_object,"mac",tem_mac->valuestring);
						cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
						if(u_data[10] == 0x45 && u_data[12] == 0)
						cJSON_AddStringToObject(data_object,"control_type","1");
						else if(u_data[10] == 0x46) 
							cJSON_AddStringToObject(data_object,"control_type","2");
						else if(u_data[10] == 0x45 && u_data[12] == 0x47)
							cJSON_AddStringToObject(data_object,"control_type","3");
						else if(u_data[10] == 0x45 && u_data[12] == 0x45)
							cJSON_AddStringToObject(data_object,"control_type","4");
						cJSON_AddStringToObject(cmd_dev,"dev_state",data_str);
						cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
						char *send_char=cJSON_PrintUnformatted(root_u);
						int my_len = strlen(send_char);
						char *my_send_char = (char *)malloc(my_len+2);
						memset(my_send_char,0,my_len+2);
						memcpy(my_send_char,send_char,my_len);
						strcat(my_send_char,"\n\0");
						send(cd,my_send_char,my_len+1,0);
						free(send_char);
						send_char=NULL;
						free(my_send_char);
						my_send_char=NULL;
						cJSON_Delete(root_u);
						root_u = NULL;
					}
					if(u_data[12] != 0x45)
						run_scene_u_triger(tem_id->valuestring,data_str);
					if(u_data[10]==0x46 || u_data[12] == 0x47)
					{
						if(flag_kg !=2)
						{
							pthread_mutex_lock(&mutex_bl);
							cJSON *multi_bind_data = cJSON_Parse(multi_bind);//遍历多联绑定列表
							pthread_mutex_unlock(&mutex_bl);
							if(multi_bind_data != NULL)
							{
								if(multi_bind_data->child != NULL)
								{
									cJSON *my_multi_bind_data = cJSON_GetObjectItem(multi_bind_data,"data");
									cJSON *my_multi_bind_list = cJSON_GetObjectItem(my_multi_bind_data,"bind_mx_list");
									int	multi_bind_len =  cJSON_GetArraySize(my_multi_bind_list);
									int j=0;
									cJSON *multi_bind_for = NULL;
									cJSON *multi_bind_dev_id = NULL;
									for(j=0;j<multi_bind_len;j++)
									{
										multi_bind_for = cJSON_GetArrayItem(my_multi_bind_list,j);
										multi_bind_dev_id = cJSON_GetObjectItem(multi_bind_for,"dev_id");
										if(strcmp(multi_bind_dev_id->valuestring,tem_id->valuestring)==0)//找到设备id
										{
											cJSON *multi_bind_bind_ourid = cJSON_GetObjectItem(multi_bind_for,"bind_id");//共有的绑定id
											int k,m;
											cJSON *multi_bind_bind_id=NULL;
											cJSON *bind_devid=NULL;
											for(k=0;k<multi_bind_len;k++)
											{
												multi_bind_for = cJSON_GetArrayItem(my_multi_bind_list,k);
												multi_bind_bind_id = cJSON_GetObjectItem(multi_bind_for,"bind_id");
												if(strcmp(multi_bind_bind_id->valuestring,multi_bind_bind_ourid->valuestring)==0)//对比bind_id
												{
													bind_devid = cJSON_GetObjectItem(multi_bind_for,"dev_id");
													pthread_mutex_lock(&mutex_sl);
													cJSON *dev_list_dev = cJSON_Parse(device_list);//遍历设备列表
													pthread_mutex_unlock(&mutex_sl);
													if(dev_list_dev != NULL)
													{
														if(dev_list_dev->child != NULL)	
														{
															cJSON *dev_list_data_for = cJSON_GetObjectItem(dev_list_dev,"data");
															cJSON *dev_list_list_for = cJSON_GetObjectItem(dev_list_data_for,"dev_list");
															data_l =  cJSON_GetArraySize(dev_list_list_for);
															cJSON *data_arr_jx_for = NULL;
															cJSON *tem_id_for = NULL;
															cJSON *tem_mac_for = NULL;
															cJSON *tem_type_for = NULL;
															cJSON *tem_port_for = NULL;
															for(m=0;m<data_l;m++)
															{
																data_arr_jx_for = cJSON_GetArrayItem(dev_list_list_for,m);
																tem_id_for = cJSON_GetObjectItem(data_arr_jx_for,"dev_id");
																if(strcmp(tem_id->valuestring,bind_devid->valuestring)==0)
																	break;
																else if(strcmp(tem_id_for->valuestring,bind_devid->valuestring)==0)
																{
																	tem_mac_for = cJSON_GetObjectItem(data_arr_jx_for,"mac");
																	tem_port_for = cJSON_GetObjectItem(data_arr_jx_for,"dev_port");
																	tem_type_for = cJSON_GetObjectItem(data_arr_jx_for,"dev_type");
																	kg=0;
																	if(strcmp(tem_type_for->valuestring,"010101")==0)
																		kg=1;
																	else if(strcmp(tem_type_for->valuestring,"010102")==0)
																		kg=1;
																	else if(strcmp(tem_type_for->valuestring,"010103")==0)
																		kg=1;
																	else if(strcmp(tem_type_for->valuestring,"010104")==0)
																		kg=1;
																	else if(strcmp(tem_type_for->valuestring,"010501")==0)
																		kg=1;
																	else if(strcmp(tem_type_for->valuestring,"010601")==0)
																		kg=1;
																	else if(strcmp(tem_type_for->valuestring,"040101")==0)
																		kg=1;
																	else if(strcmp(tem_type_for->valuestring,"040102")==0)
																		kg=1;
																	if(kg==1)//类似开关类
																	{
																		uint8_t *multi_bind_final_cmd = NULL;
																		multi_bind_final_cmd = (uint8_t *)malloc(16);
																		memset(multi_bind_final_cmd,0,16);
																		if(flag_kg==1)
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"01",multi_bind_final_cmd);
																		else if(flag_kg==0)
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"00",multi_bind_final_cmd);
																		resend_zt(16,multi_bind_final_cmd,tem_id_for->valuestring,tem_type_for->valuestring);	
																		find_mac_and_send(tem_mac_for->valuestring,multi_bind_final_cmd,16);
																		free(multi_bind_final_cmd);
																		multi_bind_final_cmd=NULL;
																	}
																	else if(strcmp(tem_type_for->valuestring,"010201")==0)//tgd
																	{
																		uint8_t *multi_bind_final_cmd = NULL;
																		multi_bind_final_cmd = (uint8_t *)malloc(16);
																		memset(multi_bind_final_cmd,0,16);
																		if(flag_kg==1)//触发源开
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"ff",multi_bind_final_cmd);
																		else if(flag_kg==0)
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"00",multi_bind_final_cmd);
																		resend_zt(16,multi_bind_final_cmd,tem_id_for->valuestring,tem_type_for->valuestring);
																		find_mac_and_send(tem_mac_for->valuestring,multi_bind_final_cmd,16);
																		free(multi_bind_final_cmd);
																		multi_bind_final_cmd=NULL;
																	}
																	else if(strcmp(tem_type_for->valuestring,"010301")==0)//rgb
																	{
																		uint8_t *multi_bind_final_cmd = NULL;
																		multi_bind_final_cmd = (uint8_t *)malloc(19);
																		memset(multi_bind_final_cmd,0,19);
																		pthread_mutex_lock(&mutex_zl);
																		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
																		pthread_mutex_unlock(&mutex_zl);
																		if(device_state_list_data != NULL)
																		{
																			if(device_state_list_data->child != NULL)
																			{
																				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
																				cJSON *while_device_state_list_data = my_device_state_list_data->child;
																				if(while_device_state_list_data==NULL)
																				{
																					if(flag_kg == 1)
																					cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"ffffffff",multi_bind_final_cmd);
																					else if(flag_kg == 0)
																					cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"00000000",multi_bind_final_cmd);
																				}
																				else
																				{
																					while(while_device_state_list_data != NULL)
																					{
																						if(strcmp(while_device_state_list_data->string,tem_id_for->valuestring)==0)
																						{
																							cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id_for->valuestring);
																							cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
																							if(flag_kg == 1)
																							{
																								if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
																								{
																									my_dev_state->valuestring[6]='f';
																									my_dev_state->valuestring[7]='f';
																								}
																							}
																							else if(flag_kg == 0)
																							{
																								my_dev_state->valuestring[6]='0';
																								my_dev_state->valuestring[7]='0';
																							}
																							cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,my_dev_state->valuestring,multi_bind_final_cmd);
																							break;
																						}
																						while_device_state_list_data = while_device_state_list_data->next;
																						if(while_device_state_list_data==NULL)
																						{
																							if(flag_kg == 1)
																							cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"ffffffff",multi_bind_final_cmd);
																							else if(flag_kg == 0)
																							cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"00000000",multi_bind_final_cmd);
																						}
																					}
																				}
																			}
																		}
																		cJSON_Delete(device_state_list_data);
																		device_state_list_data=NULL;
																		if(multi_bind_final_cmd[0] != multi_bind_final_cmd[1])
																		{
																			resend_zt(19,multi_bind_final_cmd,tem_id_for->valuestring,tem_type_for->valuestring);
																			find_mac_and_send(tem_mac_for->valuestring,multi_bind_final_cmd,19);
																		}
																		free(multi_bind_final_cmd);
																		multi_bind_final_cmd = NULL;
																	}
																	else if(strcmp(tem_type_for->valuestring,"040201")==0)//bfbcl
																	{
																		uint8_t *multi_bind_final_cmd = NULL;
																		multi_bind_final_cmd = (uint8_t *)malloc(16);
																		memset(multi_bind_final_cmd,0,16);
																		if(flag_kg==1)//触发源开
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"64",multi_bind_final_cmd);
																		else if(flag_kg==0)
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"00",multi_bind_final_cmd);
																		resend_zt(16,multi_bind_final_cmd,tem_id_for->valuestring,tem_type_for->valuestring);
																		find_mac_and_send(tem_mac_for->valuestring,multi_bind_final_cmd,16);
																		free(multi_bind_final_cmd);
																		multi_bind_final_cmd = NULL;
																	}
																	else if(strcmp(tem_type_for->valuestring,"040301")==0)//bycl
																	{
																		uint8_t *multi_bind_final_cmd = NULL;
																		multi_bind_final_cmd = (uint8_t *)malloc(17);
																		memset(multi_bind_final_cmd,0,17);
																		if(flag_kg==1)//触发源开
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"6464",multi_bind_final_cmd);
																		else if(flag_kg==0)
																		cmd_mix(tem_mac_for->valuestring,tem_port_for->valuestring,"0000",multi_bind_final_cmd);
																		resend_zt(17,multi_bind_final_cmd,tem_id_for->valuestring,tem_type_for->valuestring);
																		find_mac_and_send(tem_mac_for->valuestring,multi_bind_final_cmd,17);
																		free(multi_bind_final_cmd);
																		multi_bind_final_cmd = NULL;
																	}
																	usleep(200000);
																	break;
																}
															}
														}
													}
													cJSON_Delete(dev_list_dev);
													dev_list_dev=NULL;
												}
											}
											break;
										}
									}
								}
							}
							cJSON_Delete(multi_bind_data);
							multi_bind_data = NULL;
						}
					}
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							if(while_device_state_list_data==NULL)
							{
								cJSON *my_date = cJSON_CreateObject();//创建项目
								cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
								cJSON_AddStringToObject(my_date,"dev_state",data_str);
								char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,device_state_list_char,strlen(device_state_list_char));
								fsync(state_fd);
								close(state_fd);
								free(device_state_list_char);
								device_state_list_char=NULL;
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
										int flag_have = 0,len = 0,num = 0;
										num = cJSON_GetArraySize(dev_state_cjson);
										cJSON *arr_for = NULL;
										for(len=0;len<num;len++)
										{
											arr_for = cJSON_GetArrayItem(dev_state_cjson,len);
											if(!strcmp(arr_for->string,"dev_state"))
											{
												flag_have = 1;
												break;
											}
										}
										if( flag_have )
										cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
										cJSON_AddStringToObject(dev_state_cjson,"dev_state",data_str);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char = NULL;
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data == NULL)
									{
										cJSON *dev_status = cJSON_CreateObject();
										cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,dev_status);
										cJSON_AddStringToObject(dev_status,"dev_state",data_str);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char = NULL;
										break;
									}	
								}
							}
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data=NULL;
					break;//*******
				}
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
	free(data_str);
	data_str=NULL;
	free (mac_str);
	mac_str=NULL;
	free(port_str);
	port_str= NULL;
}
void dev_com_kt_con(int i,int u_data_len,uint8_t *u_data,char *u_data_str)
{
	char *data_str = NULL;
	data_str= (char*)malloc(15);//指令cmd
	memset(data_str,0,15);
	memcpy(data_str,u_data_str+34,14);
	data_str[14]='\0';
	char *mac_id = NULL;
	mac_id = (char *)malloc(9);
	memset(mac_id,0,9);
	int id_num = 0;
	for(i=0;i<4;i++)
	id_num += u_data[31-4+i]<<(3-i)*8;
	int_to_str(id_num,mac_id); 
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
				if( strcmp(tem_id->valuestring,mac_id)==0 )
				{
					tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
					if(NET_FLAG)
					{
						cJSON *root_u = cJSON_CreateObject();//创建项目
						cJSON_AddNumberToObject(root_u,"retcode",0);
						cJSON_AddStringToObject(root_u,"message","success");
						cJSON_AddStringToObject(root_u,"api","devStateRes");
						cJSON *data_object = cJSON_CreateObject();
						cJSON_AddItemToObject(root_u,"data",data_object);
						cJSON *cmd_dev = cJSON_CreateObject();
						cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
						cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
						cJSON_AddStringToObject(cmd_dev,"dev_state",data_str);
						cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
						char *send_char=cJSON_PrintUnformatted(root_u);
						int my_len = strlen(send_char);
						char *my_send_char = (char *)malloc(my_len+2);
						memset(my_send_char,0,my_len+2);
						memcpy(my_send_char,send_char,my_len);
						strcat(my_send_char,"\n\0");
						send(cd,my_send_char,my_len+1,0);
						free(send_char);
						send_char=NULL;
						free(my_send_char);
						my_send_char=NULL;
						cJSON_Delete(root_u);
						root_u = NULL;
					}
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							if(while_device_state_list_data==NULL)
							{
								cJSON *my_date = cJSON_CreateObject();//创建项目
								cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
								cJSON_AddStringToObject(my_date,"dev_state",data_str);
								char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,device_state_list_char,strlen(device_state_list_char));
								fsync(state_fd);
								close(state_fd);
								free(device_state_list_char);
								device_state_list_char=NULL;
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
										cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
										cJSON_AddStringToObject(dev_state_cjson,"dev_state",data_str);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char=NULL;
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data==NULL)
									{
										cJSON *my_date = cJSON_CreateObject();//创建项目
										cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
										cJSON_AddStringToObject(my_date,"dev_state",data_str);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char=NULL;
									}
								}
							}
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data=NULL;
				}
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data = NULL;
	free(data_str);
	data_str = NULL;
	free(mac_id);
	mac_id=NULL;
}
void dev_lock_con(int i,int u_data_len,uint8_t *u_data,char *u_data_str)
{
	int data_len = (u_data_len-17)*2-6;
	char *data_str = (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+34,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	char *port_str = NULL;
	port_str = (char*)malloc(3);//端口号
	memset(port_str,0,3);
	memcpy(port_str,u_data_str+22,2);
	port_str[2] = '\0';
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_port = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
				if(strcmp(tem_mac->valuestring,mac_str)==0 && strcmp(tem_port->valuestring,port_str)==0)
				{
					tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
					tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
					if(NET_FLAG)
					{
						cJSON *root_u = cJSON_CreateObject();//创建项目
						cJSON *data_object = cJSON_CreateObject();
						cJSON *cmd_dev = cJSON_CreateObject();
						cJSON_AddNumberToObject(root_u,"retcode",0);
						cJSON_AddStringToObject(root_u,"message","success");
						cJSON_AddStringToObject(root_u,"api","devStateRes");
						cJSON_AddItemToObject(root_u,"data",data_object);
						cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
						cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
						cJSON_AddStringToObject(cmd_dev,"dev_state",data_str);
						cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
						char *send_char = cJSON_PrintUnformatted(root_u);
						int my_len = strlen(send_char);
						char *my_send_char = (char *)malloc(my_len+2);
						memset(my_send_char,0,my_len+2);
						memcpy(my_send_char,send_char,my_len);
						strcat(my_send_char,"\n\0");
						send(cd,my_send_char,my_len+1,0);
						cJSON_Delete(root_u);
						root_u = NULL;
						free(send_char);
						send_char = NULL;
						free(my_send_char);
						my_send_char = NULL;
					}
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							if(while_device_state_list_data==NULL)
							{
								cJSON *my_date = cJSON_CreateObject();//创建项目
								cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
								cJSON_AddStringToObject(my_date,"dev_state",data_str);
								char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,device_state_list_char,strlen(device_state_list_char));
								fsync(state_fd);
								close(state_fd);
								free(device_state_list_char);
								device_state_list_char=NULL;
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
										cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
										cJSON_AddStringToObject(dev_state_cjson,"dev_state",data_str);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char = NULL;
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data == NULL)
									{
										cJSON *my_date = cJSON_CreateObject();//创建项目
										cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
										cJSON_AddStringToObject(my_date,"dev_state",data_str);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char=NULL;
									}
								}
							}
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data=NULL;
					break;
				}
			}
		}
	}
	free(data_str);
	data_str = NULL;
	free(mac_str);
	mac_str = NULL;
	free(port_str);
	port_str = NULL;
	cJSON_Delete(dev_list_data);
	dev_list_data = NULL;
}
void hw_study_or_one_key(int u_data_len,uint8_t *u_data,char *u_data_str)
{
	if(u_data[15] != 0x52 && onekey_or_study_flag==0)
	{
		cJSON *send_root = cJSON_CreateObject();
		cJSON_AddNumberToObject(send_root,"retcode",0);
		cJSON_AddStringToObject(send_root,"message","success");
		cJSON_AddStringToObject(send_root,"api","one_key_code");
		cJSON *send_data = cJSON_CreateObject();
		cJSON_AddItemToObject(send_root,"data",send_data);
		int data_len = (u_data_len-15)*2;
		char *data_str = (char*)malloc(data_len+1);//指令cmd
		memset(data_str,0,data_len+1);
		memcpy(data_str,u_data_str+30,data_len);
		data_str[data_len]='\0';
		cJSON_AddStringToObject(send_data,"code",data_str);
		char *send_char = cJSON_PrintUnformatted(send_root);
		int my_len = strlen(send_char);
		char *my_send_char = (char *)malloc(my_len+2);
		memset(my_send_char,0,my_len+2);
		memcpy(my_send_char,send_char,my_len);
		strcat(my_send_char,"\n\0");
		send(cd,my_send_char,my_len+1,0);
		free(send_char);
		send_char=NULL;
		free(my_send_char);
		my_send_char=NULL;
		cJSON_Delete(send_root);
		send_root = NULL;
		free(data_str);
		data_str=NULL;
		onekey_or_study_flag = 2;
	}
	else if(u_data[15] != 0x52 && onekey_or_study_flag==1)
	{
		cJSON *send_root = cJSON_CreateObject();
		cJSON_AddNumberToObject(send_root,"retcode",0);
		cJSON_AddStringToObject(send_root,"message","success");
		cJSON_AddStringToObject(send_root,"api","cmd_study_hw");
		cJSON *send_data = cJSON_CreateObject();
		cJSON_AddItemToObject(send_root,"data",send_data);
		int data_len = (u_data_len-15)*2;
		char *data_str = (char*)malloc(data_len+1);//指令cmd
		memset(data_str,0,data_len+1);
		memcpy(data_str,u_data_str+30,data_len);
		data_str[data_len]='\0';
		char *mac_str = NULL;
		mac_str = (char*)malloc(17);//mac地址
		memset(mac_str,0,17);
		memcpy(mac_str,u_data_str+4,16);
		mac_str[16]='\0';
		cJSON_AddStringToObject(send_data,"code",data_str);
		cJSON_AddStringToObject(send_data,"mac",mac_str);
		char *send_char = cJSON_PrintUnformatted(send_root);
		int my_len = strlen(send_char);
		char *my_send_char = (char *)malloc(my_len+2);
		memset(my_send_char,0,my_len+2);
		memcpy(my_send_char,send_char,my_len);
		strcat(my_send_char,"\n\0");
		send(cd,my_send_char,my_len+1,0);
		free(send_char);
		send_char=NULL;
		free(my_send_char);
		my_send_char=NULL;
		free(mac_str);
		mac_str=NULL;
		cJSON_Delete(send_root);
		send_root = NULL;
		free(data_str);
		data_str=NULL;
		onekey_or_study_flag = 2;
	}
	else if(u_data[15]==0x52 && u_data[16] == 0x00)
	{
		cJSON *send_root = cJSON_CreateObject();
		cJSON_AddNumberToObject(send_root,"retcode",140);
		cJSON_AddStringToObject(send_root,"message","匹配失败,请重试");
		cJSON_AddStringToObject(send_root,"api","one_key_code");
		cJSON *send_data = cJSON_CreateObject();
		cJSON_AddItemToObject(send_root,"data",send_data);
		char *send_char = cJSON_PrintUnformatted(send_root);
		int my_len = strlen(send_char);
		char *my_send_char = (char *)malloc(my_len+2);
		memset(my_send_char,0,my_len+2);
		memcpy(my_send_char,send_char,my_len);
		strcat(my_send_char,"\n\0");
		send(cd,my_send_char,my_len+1,0);
		free(send_char);
		send_char=NULL;
		free(my_send_char);
		my_send_char=NULL;
		cJSON_Delete(send_root);
		send_root=NULL;
		onekey_or_study_flag = 2;
	}
	else if(u_data[15]==0x52 && u_data[16] == 0x01)
	onekey_or_study_flag=1;
	else if(u_data[15]==0x52 && u_data[16] == 0x02)
	onekey_or_study_flag=0;
}
void dev_online(int i,int u_data_len,char *u_data_str)
{
	int data_len = (u_data_len-15)*2;
	time_t net_now_time;
	char *data_str = NULL;
	data_str = (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+30,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			if(data_l==0)
			{
				net_now_time = time(NULL);
				if((unsigned int)difftime(net_now_time,net_record_time) >= 300 || go_net_flag==0)//超时
				{
					uint8_t *dev_net_delete = NULL;
					dev_net_delete = (uint8_t *)malloc(16);
					memset(dev_net_delete,0,16);
					cmd_delete_mix(mac_str,"00",dev_net_delete);
					usart_send(fd,dev_net_delete,16);
					free(dev_net_delete);
					dev_net_delete=NULL;
				}
				else
				{
					uint8_t *req_des_cmd = NULL;
					req_des_cmd = (uint8_t *)malloc(16);
					memset(req_des_cmd,0,16);
					cmd_request_describ_mix(mac_str,"00",req_des_cmd);
					usleep(500000);//需要老何优化
					usart_send(fd,req_des_cmd,16);
					free(req_des_cmd);
					req_des_cmd=NULL;
				}
			}
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				if(strcmp(tem_mac->valuestring,mac_str)==0)
				{
					if(strcmp(data_str,"00")==0)
					{
						break;
					}
				}
				else
				{
					if(i==(data_l-1))
					{
						net_now_time = time(NULL);
						if((unsigned int)difftime(net_now_time,net_record_time) >= 300 || go_net_flag==0)//超时
						{
							uint8_t *dev_net_delete = NULL;
							dev_net_delete = (uint8_t *)malloc(16);
							memset(dev_net_delete,0,16);
							cmd_delete_mix(mac_str,"00",dev_net_delete);
							usart_send(fd,dev_net_delete,16);
							free(dev_net_delete);
							dev_net_delete=NULL;
						}
						else
						{
							uint8_t *req_des_cmd = NULL;
							req_des_cmd = (uint8_t *)malloc(16);
							memset(req_des_cmd,0,16);
							cmd_request_describ_mix(mac_str,"00",req_des_cmd);
							usleep(500000);//需要老何优化
							usart_send(fd,req_des_cmd,16);
							free(req_des_cmd);
							req_des_cmd=NULL;
						}
					}
				}
			}
		}
	}
	free(data_str);
	data_str =NULL;
	free(mac_str);
	mac_str = NULL;
	cJSON_Delete(dev_list_data);
	dev_list_data = NULL;
}
void dev_status_u(uint8_t *u_data,int i,int u_data_len,char *u_data_str)
{
	int data_len = (u_data_len-15)*2;
	char *data_str = NULL;
	data_str= (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+30,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	char *port_str = NULL;
	port_str = (char*)malloc(3);//端口号
	memset(port_str,0,3);
	memcpy(port_str,u_data_str+22,2);
	port_str[2] = '\0';
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_port = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
				if(strcmp(tem_mac->valuestring,mac_str)==0 && strcmp(tem_port->valuestring,port_str)==0)
				{
					tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
					tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							if(while_device_state_list_data==NULL)
							{
								cJSON *my_date = cJSON_CreateObject();//创建项目
								cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
								cJSON_AddStringToObject(my_date,"dev_state",data_str);
								char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,device_state_list_char,strlen(device_state_list_char));
								fsync(state_fd);
								close(state_fd);
								free(device_state_list_char);
								device_state_list_char=NULL;
								if(NET_FLAG)
								{
									cJSON *root_state = cJSON_CreateObject();
									cJSON_AddNumberToObject(root_state,"retcode",0);
									cJSON_AddStringToObject(root_state,"message","success");
									cJSON_AddStringToObject(root_state,"api","devStateRes");
									cJSON *root_state_data = cJSON_CreateObject();
									cJSON_AddItemToObject(root_state,"data",root_state_data);
									cJSON_AddStringToObject(root_state_data,"dev_id",tem_id->valuestring);
									cJSON_AddStringToObject(root_state_data,"dev_type",tem_type->valuestring);
									cJSON *my_status = cJSON_CreateObject();
									cJSON_AddItemToObject(root_state_data,"dev_state",my_status);
									cJSON_AddStringToObject(my_status,"dev_state",data_str);
									char *send_char = cJSON_PrintUnformatted(root_state);
									int my_len = strlen(send_char);
									char *my_send_char = (char *)malloc(my_len+2);
									memset(my_send_char,0,my_len+2);
									memcpy(my_send_char,send_char,my_len);
									strcat(my_send_char,"\n\0");
									send(cd,my_send_char,my_len+1,0);
									cJSON_Delete(root_state);
									root_state=NULL;
									free(send_char);
									send_char=NULL;
									free(my_send_char);
									my_send_char=NULL;
								}
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
										cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
										if(strcmp(my_dev_state->valuestring,data_str)==0)
											break;
										else
										{
											cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
											cJSON_AddStringToObject(dev_state_cjson,"dev_state",data_str);
											char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
											memset(device_state_list,0,BUFFSIZE);
											memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
											int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
											write(state_fd,device_state_list_char,strlen(device_state_list_char));
											fsync(state_fd);
											close(state_fd);
											free(device_state_list_char);
											device_state_list_char=NULL;
											if(NET_FLAG)
											{
												cJSON *root_state = cJSON_CreateObject();
												cJSON_AddNumberToObject(root_state,"retcode",0);
												cJSON_AddStringToObject(root_state,"message","success");
												cJSON_AddStringToObject(root_state,"api","devStateRes");
												cJSON *root_state_data = cJSON_CreateObject();
												cJSON_AddItemToObject(root_state,"data",root_state_data);
												cJSON_AddStringToObject(root_state_data,"dev_id",tem_id->valuestring);
												cJSON_AddStringToObject(root_state_data,"dev_type",tem_type->valuestring);
												cJSON *my_status = cJSON_CreateObject();
												cJSON_AddItemToObject(root_state_data,"dev_state",my_status);
												cJSON_AddStringToObject(my_status,"dev_state",data_str);
												char *send_char = cJSON_PrintUnformatted(root_state);
												int my_len = strlen(send_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,send_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												cJSON_Delete(root_state);
												root_state=NULL;
												free(send_char);
												send_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
											}
										}
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data==NULL)
									{
										cJSON *my_date = cJSON_CreateObject();//创建项目
										cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
										cJSON_AddStringToObject(my_date,"dev_state",data_str);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char = NULL;
										if(NET_FLAG)
										{
											cJSON *root_state = cJSON_CreateObject();
											cJSON_AddNumberToObject(root_state,"retcode",0);
											cJSON_AddStringToObject(root_state,"message","success");
											cJSON_AddStringToObject(root_state,"api","devStateRes");
											cJSON *root_state_data = cJSON_CreateObject();
											cJSON_AddItemToObject(root_state,"data",root_state_data);
											cJSON_AddStringToObject(root_state_data,"dev_id",tem_id->valuestring);
											cJSON_AddStringToObject(root_state_data,"dev_type",tem_type->valuestring);
											cJSON *my_status = cJSON_CreateObject();
											cJSON_AddItemToObject(root_state_data,"dev_state",my_status);
											cJSON_AddStringToObject(my_status,"dev_state",data_str);
											char *send_char = cJSON_PrintUnformatted(root_state);
											int my_len = strlen(send_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,send_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											cJSON_Delete(root_state);
											root_state=NULL;
											free(send_char);
											send_char=NULL;
											free(my_send_char);
											my_send_char=NULL;
										}
									}
								}
							}
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data = NULL;
					break;
				}
			}
		}
	}
	free(data_str);
	data_str =NULL;
	free(mac_str);
	mac_str = NULL;
	free(port_str);
	port_str = NULL;
	cJSON_Delete(dev_list_data);
	dev_list_data = NULL;
}
void dev_descrip_u(int i,int u_data_len,char *u_data_str)
{
	int data_len = (u_data_len-15)*2;
	char *data_str = NULL;
	data_str = (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+30,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	cJSON *des_root = cJSON_CreateObject();
	cJSON_AddStringToObject(des_root,"co","orange");
	cJSON_AddStringToObject(des_root,"api","add_dev_request");
	cJSON *des_data = cJSON_CreateObject();
	cJSON_AddItemToObject(des_root,"data",des_data);
	cJSON_AddStringToObject(des_data,"mac",mac_str);
	cJSON_AddStringToObject(des_data,"descrip",data_str);
	char *des_root_char = cJSON_PrintUnformatted(des_root);
	int my_len = strlen(des_root_char);
	char *my_send_char = (char *)malloc(my_len+2);
	memset(my_send_char,0,my_len+2);
	memcpy(my_send_char,des_root_char,my_len);
	strcat(my_send_char,"\n\0");
	send(cd,my_send_char,my_len+1,0);
	cJSON_Delete(des_root);
	des_root=NULL;
	free(des_root_char);
	des_root_char=NULL;
	free(my_send_char);
	my_send_char=NULL;
	free(data_str);
	data_str=NULL;
	free(mac_str);
	mac_str=NULL;
}

void power_65(uint8_t *u_data,int i,int u_data_len,char *u_data_str)
{
	int data_len = (u_data_len-15)*2;
	char *data_str = NULL;
	data_str= (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+30,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	char *port_str = NULL;
	port_str = (char*)malloc(3);//端口号
	memset(port_str,0,3);
	memcpy(port_str,u_data_str+22,2);
	port_str[2] = '\0';
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
		cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
		int	data_l =  cJSON_GetArraySize(my_dev_list_list);
		if(data_l==0)
		{
			;
		}
		else
		{
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				if(strcmp(tem_mac->valuestring,mac_str)==0)
				{
					tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
					tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
					char *power_l = (char *)malloc(2);
					memset(power_l,0,2);
					get_sensor_power(u_data,power_l);
					if(power_l[0]=='1' && NET_FLAG)
					{
						cJSON *root_power = cJSON_CreateObject();
						cJSON *root_power_data = cJSON_CreateObject();
						cJSON_AddStringToObject(root_power,"co","orange");
						cJSON_AddStringToObject(root_power,"api","gw_up_msg");
						cJSON_AddStringToObject(root_power_data,"id",tem_id->valuestring);
						cJSON_AddStringToObject(root_power_data,"msg_type","0207");
						cJSON_AddItemToObject(root_power,"data",root_power_data);
						char *send_char = cJSON_PrintUnformatted(root_power);
						int my_len = strlen(send_char);
						char *my_send_char = (char *)malloc(my_len+2);
						memset(my_send_char,0,my_len+2);
						memcpy(my_send_char,send_char,my_len);
						strcat(my_send_char,"\n\0");
						send(cd,my_send_char,my_len+1,0);
						cJSON_Delete(root_power);
						root_power = NULL;
						free(send_char);
						send_char = NULL;
						free(my_send_char);
						my_send_char = NULL;
					}
					else if(power_l[0]=='0' && NET_FLAG)
					{
						cJSON *root_power = cJSON_CreateObject();
						cJSON *root_power_data = cJSON_CreateObject();
						cJSON_AddStringToObject(root_power,"co","orange");
						cJSON_AddStringToObject(root_power,"api","gw_up_msg");
						cJSON_AddStringToObject(root_power_data,"id",tem_id->valuestring);
						cJSON_AddStringToObject(root_power_data,"msg_type","0208");
						cJSON_AddItemToObject(root_power,"data",root_power_data);
						char *send_char = cJSON_PrintUnformatted(root_power);
						int my_len = strlen(send_char);
						char *my_send_char = (char *)malloc(my_len+2);
						memset(my_send_char,0,my_len+2);
						memcpy(my_send_char,send_char,my_len);
						strcat(my_send_char,"\n\0");
						send(cd,my_send_char,my_len+1,0);
						cJSON_Delete(root_power);
						root_power = NULL;
						free(send_char);
						send_char = NULL;
						free(my_send_char);
						my_send_char = NULL;
					}
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							if(while_device_state_list_data==NULL)
							{
								cJSON *my_date = cJSON_CreateObject();//创建项目
								cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
								cJSON_AddStringToObject(my_date,"power_level",power_l);
								char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,device_state_list_char,strlen(device_state_list_char));
								fsync(state_fd);
								close(state_fd);
								free(device_state_list_char);
								device_state_list_char=NULL;
								if(NET_FLAG)
								{
									cJSON *root_u = cJSON_CreateObject();//创建项目
									cJSON *data_object = cJSON_CreateObject();
									cJSON_AddNumberToObject(root_u,"retcode",0);
									cJSON_AddStringToObject(root_u,"message","success");
									cJSON_AddStringToObject(root_u,"api","devStateRes");
									cJSON_AddItemToObject(root_u,"data",data_object);
									cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
									cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
									cJSON *cmd_dev =  cJSON_Duplicate(my_date,1);
									cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
									char *send_char = cJSON_PrintUnformatted(root_u);
									int my_len = strlen(send_char);
									char *my_send_char = (char *)malloc(my_len+2);
									memset(my_send_char,0,my_len+2);
									memcpy(my_send_char,send_char,my_len);
				 					strcat(my_send_char,"\n\0");
									send(cd,my_send_char,my_len+1,0);
									free(send_char);
									send_char=NULL;
									free(my_send_char);
									my_send_char=NULL;
									cJSON_Delete(root_u);
									root_u = NULL;
								}
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
										int num = cJSON_GetArraySize(dev_state_cjson);
										int i,flag_have;
										i=0;flag_have=0;
										cJSON *arr_for = NULL;
										for(i=0;i<num;i++)
										{
											arr_for = cJSON_GetArrayItem(dev_state_cjson,i);
											if(!strcmp(arr_for->string,"power_level"))
											{
												flag_have = 1;
												break;
											}
										}
										if(flag_have==1)
										cJSON_DeleteItemFromObject(dev_state_cjson,"power_level");
										cJSON_AddStringToObject(dev_state_cjson,"power_level",power_l);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char = NULL;
										if(NET_FLAG)
										{
											cJSON *root_u = cJSON_CreateObject();//创建项目
											cJSON *data_object = cJSON_CreateObject();
											cJSON_AddNumberToObject(root_u,"retcode",0);
											cJSON_AddStringToObject(root_u,"message","success");
											cJSON_AddStringToObject(root_u,"api","devStateRes");
											cJSON_AddItemToObject(root_u,"data",data_object);
											cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
											cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
											cJSON *cmd_dev = cJSON_Duplicate(dev_state_cjson,1);
											cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
											char *send_char = cJSON_PrintUnformatted(root_u);
											int my_len = strlen(send_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,send_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											free(send_char);
											send_char=NULL;
											free(my_send_char);
											my_send_char=NULL;
											cJSON_Delete(root_u);
											root_u = NULL;
										}
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data==NULL)
									{
										cJSON *my_date = cJSON_CreateObject();//创建项目
										cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,my_date);
										cJSON_AddStringToObject(my_date,"power_level",power_l);
										char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,device_state_list_char,strlen(device_state_list_char));
										fsync(state_fd);
										close(state_fd);
										free(device_state_list_char);
										device_state_list_char=NULL;
										if(NET_FLAG)
										{
											cJSON *root_u = cJSON_CreateObject();//创建项目
											cJSON *data_object = cJSON_CreateObject();
											cJSON_AddNumberToObject(root_u,"retcode",0);
											cJSON_AddStringToObject(root_u,"message","success");
											cJSON_AddStringToObject(root_u,"api","devStateRes");
											cJSON_AddItemToObject(root_u,"data",data_object);
											cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
											cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
											cJSON *cmd_dev = cJSON_Duplicate(my_date,1);
											cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
											char *send_char = cJSON_PrintUnformatted(root_u);
											int my_len = strlen(send_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,send_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											free(send_char);
											send_char=NULL;
											free(my_send_char);
											my_send_char=NULL;
											cJSON_Delete(root_u);
											root_u = NULL;
										}
									}
								}
							}
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data=NULL;
					free(power_l);
					power_l=NULL;
				 }
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
	free(data_str);
	data_str=NULL;
	free(mac_str);
	mac_str=NULL;
	free(port_str);
	port_str=NULL;
}

void dev_sensor_81(int i,int u_data_len,char *u_data_str)//安防设备报警接口函数
{
	int num_for,j,a,data_len = (u_data_len-15)*2;
	char *data_str = NULL;
	data_str= (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+30,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	char *port_str = NULL;
	port_str = (char*)malloc(3);//端口号
	memset(port_str,0,3);
	memcpy(port_str,u_data_str+22,2);
	port_str[2] = '\0';
	if(go_net_flag==1)
	{
		uint8_t *req_des_cmd = NULL;
		req_des_cmd = (uint8_t *)malloc(16);
		memset(req_des_cmd,0,16);
		cmd_request_describ_mix(mac_str,"00",req_des_cmd);
		find_mac_and_send(mac_str,req_des_cmd,16);
		free(req_des_cmd);
		req_des_cmd=NULL;
	}
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_port = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
				if(strcmp(tem_mac->valuestring,mac_str)==0 && strcmp(tem_port->valuestring,port_str)==0)
				{
					tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
					tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
					a=0;
					if(strcmp(tem_type->valuestring,"020101")==0)
					a=1;
					else if(strcmp(tem_type->valuestring,"020102")==0)
					a=1;
					else if(strcmp(tem_type->valuestring,"020103")==0)
					a=1;
					else if(strcmp(tem_type->valuestring,"020104")==0)
					a=1;
					pthread_mutex_lock(&mutex_qj);
					if(a==1)
					{
						if(strcmp(data_str,"01")==0)
						{
							run_scene_u_triger(tem_id->valuestring,"01");
							if(NET_FLAG)
							{
								cJSON *root_bj = cJSON_CreateObject();
								cJSON *root_bj_data = cJSON_CreateObject();
								cJSON_AddStringToObject(root_bj,"co","orange");
								cJSON_AddStringToObject(root_bj,"api","success");
								cJSON_AddStringToObject(root_bj,"api","gw_up_msg");
								cJSON_AddItemToObject(root_bj,"data",root_bj_data);
								cJSON_AddStringToObject(root_bj_data,"id",tem_id->valuestring);
								cJSON_AddStringToObject(root_bj_data,"msg_type","0201");
								char *root_bj_char = cJSON_PrintUnformatted(root_bj);
								int my_len = strlen(root_bj_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,root_bj_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								free(root_bj_char);
								root_bj_char=NULL;
								free(my_send_char);
								my_send_char=NULL;
								cJSON_Delete(root_bj);
								root_bj=NULL;
							}
						}
					}
					else if(strcmp(qj_model,"0104")==0)
					{
						pthread_mutex_lock(&mutex_zl);
						cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
						pthread_mutex_unlock(&mutex_zl);
						if(device_state_list_data != NULL)
						{
							if(device_state_list_data->child != NULL)
							{
								cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
								cJSON *while_device_state_list_data = my_device_state_list_data->child;
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
										int num = cJSON_GetArraySize(dev_state_cjson);
										int l,flag_have;
										flag_have=0;
										cJSON *arr_for = NULL;
										for(l=0;l<num;l++)
										{
											arr_for = cJSON_GetArrayItem(dev_state_cjson,l);
											if(!strcmp(arr_for->string,"dev_state"))
											{
												flag_have=1;
												break;
											}
										}
										if(flag_have==0) break;
										cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
										if(strcmp(my_dev_state->valuestring,"01")==0 && strcmp(data_str,"01")==0)//布防
										{
											run_scene_u_triger(tem_id->valuestring,"01");
											if(NET_FLAG)
											{
												cJSON *root_bj = cJSON_CreateObject();
												cJSON *root_bj_data = cJSON_CreateObject();
												cJSON_AddStringToObject(root_bj,"co","orange");
												cJSON_AddStringToObject(root_bj,"api","success");
												cJSON_AddStringToObject(root_bj,"api","gw_up_msg");
												cJSON_AddItemToObject(root_bj,"data",root_bj_data);
												cJSON_AddStringToObject(root_bj_data,"id",tem_id->valuestring);
												cJSON_AddStringToObject(root_bj_data,"msg_type","0201");
												char *root_bj_char = cJSON_PrintUnformatted(root_bj);
												int my_len = strlen(root_bj_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,root_bj_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												free(root_bj_char);
												root_bj_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
												cJSON_Delete(root_bj);
												root_bj=NULL;
											}
										}
										else if(strcmp(my_dev_state->valuestring,"00")==0 && strcmp(data_str,"01")==0)//撤防
											run_scene_u_triger(tem_id->valuestring,"00");
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
								}
							}
						}
						cJSON_Delete(device_state_list_data);
						device_state_list_data=NULL;
					}
					else if(strcmp(data_str,"01")==0)
					{
						pthread_mutex_lock(&mutex_af);
						cJSON *secure_list = cJSON_Parse(secure_set_list);//遍历af列表
						pthread_mutex_unlock(&mutex_af);
						if(secure_list != NULL)
						{
							if(secure_list->child != NULL)
							{
								cJSON *my_model_data = cJSON_GetObjectItem(secure_list,"data");
								cJSON *my_model = cJSON_GetObjectItem(my_model_data,"model_set_list");
								if(strcmp(qj_model,"0101")==0)
								{
									cJSON *zjbf = cJSON_GetObjectItem(my_model,"0101");
									num_for = cJSON_GetArraySize(zjbf);
									cJSON *arr_for=NULL;
									cJSON *af_id = NULL;
									cJSON *af_state = NULL;
									for(j=0;j<num_for;j++)
									{
										arr_for = cJSON_GetArrayItem(zjbf,j);
										af_id = cJSON_GetObjectItem(arr_for,"dev_id");
										if(strcmp(af_id->valuestring,tem_id->valuestring)==0)
										{
											af_state = cJSON_GetObjectItem(arr_for,"dev_state");
											if(strcmp(af_state->valuestring,"01")==0)
											{
												run_scene_u_triger(tem_id->valuestring,"01");
												if(NET_FLAG)
												{
													cJSON *root_bj = cJSON_CreateObject();
													cJSON *root_bj_data = cJSON_CreateObject();
													cJSON_AddStringToObject(root_bj,"co","orange");
													cJSON_AddStringToObject(root_bj,"api","success");
													cJSON_AddStringToObject(root_bj,"api","gw_up_msg");
													cJSON_AddItemToObject(root_bj,"data",root_bj_data);
													cJSON_AddStringToObject(root_bj_data,"id",af_id->valuestring);
													cJSON_AddStringToObject(root_bj_data,"msg_type","0201");
													char *root_bj_char = cJSON_PrintUnformatted(root_bj);
													int my_len = strlen(root_bj_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,root_bj_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													free(root_bj_char);
													root_bj_char=NULL;
													free(my_send_char);
													my_send_char=NULL;
													cJSON_Delete(root_bj);
													root_bj=NULL;
												}
											}
											break;
										}
									}
								}
								else if(strcmp(qj_model,"0102")==0)
								{
									cJSON *ljbf = cJSON_GetObjectItem(my_model,"0102");
									num_for = cJSON_GetArraySize(ljbf);
									cJSON *arr_for=NULL;
									cJSON *af_id = NULL;
									cJSON *af_state = NULL;
									for(j=0;j<num_for;j++)
									{
										arr_for = cJSON_GetArrayItem(ljbf,j);
										af_id = cJSON_GetObjectItem(arr_for,"dev_id");
										if(strcmp(af_id->valuestring,tem_id->valuestring)==0)
										{
											af_state = cJSON_GetObjectItem(arr_for,"dev_state");
											if(strcmp(af_state->valuestring,"01")==0)
											{
												run_scene_u_triger(tem_id->valuestring,"01");
												if(NET_FLAG)
												{
													cJSON *root_bj = cJSON_CreateObject();
													cJSON *root_bj_data = cJSON_CreateObject();
													cJSON_AddStringToObject(root_bj,"co","orange");
													cJSON_AddStringToObject(root_bj,"api","success");
													cJSON_AddStringToObject(root_bj,"api","gw_up_msg");
													cJSON_AddItemToObject(root_bj,"data",root_bj_data);
													cJSON_AddStringToObject(root_bj_data,"id",af_id->valuestring);
													cJSON_AddStringToObject(root_bj_data,"msg_type","0201");
													char *root_bj_char = cJSON_PrintUnformatted(root_bj);
													int my_len = strlen(root_bj_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,root_bj_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													free(root_bj_char);
													root_bj_char=NULL;
													free(my_send_char);
													my_send_char=NULL;
													cJSON_Delete(root_bj);
													root_bj=NULL;
												}
											}
											break;
										}
									}
								}
								else if(strcmp(qj_model,"0103")==0)
								{
									cJSON *cf = cJSON_GetObjectItem(my_model,"0103");
									num_for = cJSON_GetArraySize(cf);
									cJSON *arr_for=NULL;
									cJSON *af_id = NULL;
									cJSON *af_state = NULL;
									for(j=0;j<num_for;j++)
									{
										arr_for = cJSON_GetArrayItem(cf,j);
										af_id = cJSON_GetObjectItem(arr_for,"dev_id");
										if(strcmp(af_id->valuestring,tem_id->valuestring)==0)
										{
											af_state = cJSON_GetObjectItem(arr_for,"dev_state");
											if(strcmp(af_state->valuestring,"01")==0)
											{
												run_scene_u_triger(tem_id->valuestring,"01");
												if(NET_FLAG)
												{
													cJSON *root_bj = cJSON_CreateObject();
													cJSON *root_bj_data = cJSON_CreateObject();
													cJSON_AddStringToObject(root_bj,"co","orange");
													cJSON_AddStringToObject(root_bj,"api","success");
													cJSON_AddStringToObject(root_bj,"api","gw_up_msg");
													cJSON_AddItemToObject(root_bj,"data",root_bj_data);
													cJSON_AddStringToObject(root_bj_data,"id",af_id->valuestring);
													cJSON_AddStringToObject(root_bj_data,"msg_type","0201");
													char *root_bj_char = cJSON_PrintUnformatted(root_bj);
													int my_len = strlen(root_bj_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,root_bj_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													free(root_bj_char);
													root_bj_char=NULL;
													free(my_send_char);
													my_send_char=NULL;
													cJSON_Delete(root_bj);
													root_bj=NULL;
												}
											}
											break;
										}
									}
								}
							}
						}
						cJSON_Delete(secure_list);
						secure_list=NULL;
					}
					pthread_mutex_unlock(&mutex_qj);
					break;
				}
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
	free(mac_str);
	mac_str=NULL;
	free(data_str);
	data_str=NULL;
	free(port_str);
	port_str=NULL;
}
void dev_sensor_82(uint8_t *u_data,int i,int u_data_len,char *u_data_str)//zigbee主动上报传感器类状态
{
	int flag_have,data_len = (u_data_len-15)*2;
	char *data_str = NULL;
	data_str= (char*)malloc(data_len+1);//指令cmd
	memset(data_str,0,data_len+1);
	memcpy(data_str,u_data_str+30,data_len);
	data_str[data_len]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	char *port_str = NULL;
	port_str = (char*)malloc(3);//端口号
	memset(port_str,0,3);
	memcpy(port_str,u_data_str+22,2);
	port_str[2] = '\0';
	if(go_net_flag==1)
	{
		uint8_t *req_des_cmd = NULL;
		req_des_cmd = (uint8_t *)malloc(16);
		memset(req_des_cmd,0,16);
		cmd_request_describ_mix(mac_str,"00",req_des_cmd);
		find_mac_and_send(mac_str,req_des_cmd,16);
		free(req_des_cmd);
		req_des_cmd=NULL;
	}
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			cJSON *tem_id = NULL;
			cJSON *tem_port = NULL;
			cJSON *tem_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
				if(strcmp(tem_mac->valuestring,mac_str)==0 && strcmp(tem_port->valuestring,port_str)==0)
				{
					tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
					tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
					if(strcmp(tem_type->valuestring,"060101")==0)	//Door magnet
					{
						run_scene_u_triger(tem_id->valuestring,data_str);
					}
					else if(strcmp(tem_type->valuestring,"060102")==0)	//human body
					{
						human_zt(mac_str,port_str);
						run_scene_u_triger(tem_id->valuestring,data_str);
					}
					else if(strcmp(tem_type->valuestring,"060203")==0)	//temperature sensor
					{
						char *value = (char *)malloc(10);
						memset(value,0,10);
						char *level = (char *)malloc(2);
						memset(level,0,2);
						get_sensor_value(u_data,value,level);
						run_scene_u_triger_sensor(tem_id->valuestring,value);
						free(value);
						value=NULL;
						free(level);
						level=NULL;
					}
					else if(strcmp(tem_type->valuestring,"060201")==0 || strcmp(tem_type->valuestring,"060204")==0 || strcmp(tem_type->valuestring,"060205")==0 || strcmp(tem_type->valuestring,"060206")==0)	//PM2.5 or moisture sensor or formaldehyde or TVOC
					{
						char *value = (char *)malloc(10);
						memset(value,0,10);
						char *level = (char *)malloc(2);
						memset(level,0,2);
						get_sensor_value(u_data,value,level);
						run_scene_u_triger_sensor(tem_id->valuestring,level);
						free(value);
						value=NULL;
						free(level);
						level=NULL;
					}
					pthread_mutex_lock(&mutex_zl);
					cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
					if(device_state_list_data != NULL)
					{
						if(device_state_list_data->child != NULL)
						{
							cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
							cJSON *while_device_state_list_data = my_device_state_list_data->child;
							if(while_device_state_list_data==NULL)
							{
								if(strcmp(tem_type->valuestring,"060101")==0||strcmp(tem_type->valuestring,"060102")==0)
								{
									cJSON *dev_status = cJSON_CreateObject();
									cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,dev_status);
									cJSON_AddStringToObject(dev_status,"dev_state",data_str);
									char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
									memset(device_state_list,0,BUFFSIZE);
									memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
									int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
									write(state_fd,device_state_list_char,strlen(device_state_list_char));
									fsync(state_fd);
									close(state_fd);
									free(device_state_list_char);
									device_state_list_char = NULL;
									if(NET_FLAG)
									{
										cJSON *root_v = cJSON_CreateObject();//创建项目
										cJSON *data_object = cJSON_CreateObject();
										cJSON_AddNumberToObject(root_v,"retcode",0);
										cJSON_AddStringToObject(root_v,"message","success");
										cJSON_AddStringToObject(root_v,"api","devStateRes");
										cJSON_AddItemToObject(root_v,"data",data_object);
										cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
										cJSON_AddStringToObject(data_object,"mac",tem_mac->valuestring);
										cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
										cJSON *cmd_dev = cJSON_Duplicate(dev_status,1);
										cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
										char *send_char=cJSON_PrintUnformatted(root_v);
										int my_len = strlen(send_char);
										char *my_send_char = (char *)malloc(my_len+2);
										memset(my_send_char,0,my_len+2);
										memcpy(my_send_char,send_char,my_len);
										strcat(my_send_char,"\n\0");
										send(cd,my_send_char,my_len+1,0);
										free(send_char);
										send_char=NULL;
										free(my_send_char);
										my_send_char=NULL;
										cJSON_Delete(root_v);
										root_v = NULL;
									}
								}
								else if(!strcmp(tem_type->valuestring,"060201") || !strcmp(tem_type->valuestring,"060202") || !strcmp(tem_type->valuestring,"060203") || !strcmp(tem_type->valuestring,"060204") || !strcmp(tem_type->valuestring,"060205") || !strcmp(tem_type->valuestring,"060206"))
								{
									cJSON *dev_status = cJSON_CreateObject();
									cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,dev_status);
									char *value = (char *)malloc(10);
									memset(value,0,10);
									char *level = (char *)malloc(2);
									memset(level,0,2);
									get_sensor_value(u_data,value,level);
									cJSON_AddStringToObject(dev_status,"state_data",value);
									cJSON_AddStringToObject(dev_status,"state_level",level);
									char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
									memset(device_state_list,0,BUFFSIZE);
									memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
									int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
									write(state_fd,device_state_list_char,strlen(device_state_list_char));
									fsync(state_fd);
									close(state_fd);
									free(device_state_list_char);
									device_state_list_char = NULL;
									if(NET_FLAG)
									{
										cJSON *root_v = cJSON_CreateObject();//创建项目
										cJSON *data_object = cJSON_CreateObject();
										cJSON_AddNumberToObject(root_v,"retcode",0);
										cJSON_AddStringToObject(root_v,"message","success");
										cJSON_AddStringToObject(root_v,"api","devStateRes");
										cJSON_AddItemToObject(root_v,"data",data_object);
										cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
										cJSON_AddStringToObject(data_object,"mac",tem_mac->valuestring);
										cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
										cJSON *cmd_dev = cJSON_Duplicate(dev_status,1);
										cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
										char *send_char=cJSON_PrintUnformatted(root_v);
										int my_len = strlen(send_char);
										char *my_send_char = (char *)malloc(my_len+2);
										memset(my_send_char,0,my_len+2);
										memcpy(my_send_char,send_char,my_len);
										strcat(my_send_char,"\n\0");
										send(cd,my_send_char,my_len+1,0);
										free(send_char);
										send_char=NULL;
										free(my_send_char);
										my_send_char=NULL;
										cJSON_Delete(root_v);
										root_v = NULL;
									}
									free(value);
									value=NULL;
									free(level);
									level=NULL;
								}
							}
							else
							{
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
										if(strcmp(tem_type->valuestring,"060101")==0||strcmp(tem_type->valuestring,"060102")==0)
										{
											int num = cJSON_GetArraySize(dev_state_cjson);
											int m;
											cJSON *arr_for = NULL;
											flag_have=0;
											for(m=0;m<num;m++)
											{
												arr_for = cJSON_GetArrayItem(dev_state_cjson,m);
												if(!strcmp(arr_for->string,"dev_state"))
												{
													flag_have = 1;
													break;
												}
											}
											if(flag_have == 1)
											cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
											cJSON_AddStringToObject(dev_state_cjson,"dev_state",data_str);
											char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
											memset(device_state_list,0,BUFFSIZE);
											memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
											int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
											write(state_fd,device_state_list_char,strlen(device_state_list_char));
											fsync(state_fd);
											close(state_fd);
											free(device_state_list_char);
											device_state_list_char = NULL;
											if(NET_FLAG)
											{
												cJSON *root_v = cJSON_CreateObject();//创建项目
												cJSON *data_object = cJSON_CreateObject();
										 		cJSON_AddNumberToObject(root_v,"retcode",0);
												cJSON_AddStringToObject(root_v,"message","success");
												cJSON_AddStringToObject(root_v,"api","devStateRes");
												cJSON_AddItemToObject(root_v,"data",data_object);
												cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
												cJSON_AddStringToObject(data_object,"mac",tem_mac->valuestring);
												cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
												cJSON *cmd_dev = cJSON_Duplicate(dev_state_cjson,1);
												cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
												char *send_char=cJSON_PrintUnformatted(root_v);
												int my_len = strlen(send_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,send_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												free(send_char);
												send_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
												cJSON_Delete(root_v);
												root_v = NULL;
											}
										}
										else if(!strcmp(tem_type->valuestring,"060201") || !strcmp(tem_type->valuestring,"060202") || !strcmp(tem_type->valuestring,"060203") || !strcmp(tem_type->valuestring,"060204") || !strcmp(tem_type->valuestring,"060205") || !strcmp(tem_type->valuestring,"060206"))
										{
											int num = cJSON_GetArraySize(dev_state_cjson);
											cJSON *arr_for = NULL;
											int m;
											flag_have=0;
											for(m=0;m<num;m++)
											{
												arr_for = cJSON_GetArrayItem(dev_state_cjson,m);
												if(!strcmp(arr_for->string,"state_data"))
												{
													flag_have=1;
													break;
												}
											}
											if(flag_have==1)
											{
												cJSON_DeleteItemFromObject(dev_state_cjson,"state_data");
												cJSON_DeleteItemFromObject(dev_state_cjson,"state_level");
											}
											char *value = (char *)malloc(10);
											memset(value,0,10);
											char *level = (char *)malloc(2);
											memset(level,0,2);
											get_sensor_value(u_data,value,level);
											cJSON_AddStringToObject(dev_state_cjson,"state_data",value);
											cJSON_AddStringToObject(dev_state_cjson,"state_level",level);
											char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
											memset(device_state_list,0,BUFFSIZE);
											memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
											int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
											write(state_fd,device_state_list_char,strlen(device_state_list_char));
											fsync(state_fd);
											close(state_fd);
											free(device_state_list_char);
											device_state_list_char=NULL;
											if(NET_FLAG)
											{
												cJSON *root_v = cJSON_CreateObject();//创建项目
												cJSON *data_object = cJSON_CreateObject();
												cJSON_AddNumberToObject(root_v,"retcode",0);
												cJSON_AddStringToObject(root_v,"message","success");
												cJSON_AddStringToObject(root_v,"api","devStateRes");
												cJSON_AddItemToObject(root_v,"data",data_object);
												cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
												cJSON_AddStringToObject(data_object,"mac",tem_mac->valuestring);
												cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
												cJSON *cmd_dev = cJSON_Duplicate(dev_state_cjson,1);
												cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
												char *send_char=cJSON_PrintUnformatted(root_v);
												int my_len = strlen(send_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,send_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												free(send_char);
												send_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
												cJSON_Delete(root_v);
												root_v = NULL;
											}
											free(value);
											value=NULL;
											free(level);
											level=NULL;
										}
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
									if(while_device_state_list_data == NULL)
									{
										if(strcmp(tem_type->valuestring,"060101")==0||strcmp(tem_type->valuestring,"060102")==0)
										{
											cJSON *dev_status = cJSON_CreateObject();
											cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,dev_status);
											cJSON_AddStringToObject(dev_status,"dev_state",data_str);
											char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
											memset(device_state_list,0,BUFFSIZE);
											memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
											int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
											write(state_fd,device_state_list_char,strlen(device_state_list_char));
											fsync(state_fd);
											close(state_fd);
											free(device_state_list_char);
											device_state_list_char = NULL;
											if(NET_FLAG)
											{
												cJSON *root_v = cJSON_CreateObject();//创建项目
												cJSON *data_object = cJSON_CreateObject();
												cJSON_AddNumberToObject(root_v,"retcode",0);
												cJSON_AddStringToObject(root_v,"message","success");
												cJSON_AddStringToObject(root_v,"api","devStateRes");
												cJSON_AddItemToObject(root_v,"data",data_object);
												cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
												cJSON_AddStringToObject(data_object,"mac",tem_mac->valuestring);
												cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
												cJSON *cmd_dev = cJSON_Duplicate(dev_status,1);
												cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
												char *send_char=cJSON_PrintUnformatted(root_v);
												int my_len = strlen(send_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,send_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												free(send_char);
												send_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
												cJSON_Delete(root_v);
												root_v = NULL;
											}
										}
										else if(!strcmp(tem_type->valuestring,"060201") || !strcmp(tem_type->valuestring,"060202") || !strcmp(tem_type->valuestring,"060203") || !strcmp(tem_type->valuestring,"060204") || !strcmp(tem_type->valuestring,"060205") || !strcmp(tem_type->valuestring,"060206"))
										{
											cJSON *dev_status = cJSON_CreateObject();
											cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,dev_status);
											char *value = (char *)malloc(10);
											memset(value,0,10);
											char *level = (char *)malloc(2);
											memset(level,0,2);
											get_sensor_value(u_data,value,level);
											cJSON_AddStringToObject(dev_status,"state_data",value);
											cJSON_AddStringToObject(dev_status,"state_level",level);
											char *device_state_list_char = cJSON_PrintUnformatted(device_state_list_data);
											memset(device_state_list,0,BUFFSIZE);
											memcpy(device_state_list,device_state_list_char,strlen(device_state_list_char));
											int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
											write(state_fd,device_state_list_char,strlen(device_state_list_char));
											fsync(state_fd);
											close(state_fd);
											free(device_state_list_char);
											device_state_list_char = NULL;
											if(NET_FLAG)
											{
												cJSON *root_v = cJSON_CreateObject();//创建项目
												cJSON *data_object = cJSON_CreateObject();
												cJSON_AddNumberToObject(root_v,"retcode",0);
												cJSON_AddStringToObject(root_v,"message","success");
												cJSON_AddStringToObject(root_v,"api","devStateRes");
												cJSON_AddItemToObject(root_v,"data",data_object);
												cJSON_AddStringToObject(data_object,"dev_id",tem_id->valuestring);
												cJSON_AddStringToObject(data_object,"mac",tem_mac->valuestring);
												cJSON_AddStringToObject(data_object,"dev_type",tem_type->valuestring);
												cJSON *cmd_dev = cJSON_Duplicate(dev_status,1);
												cJSON_AddItemToObject(data_object,"dev_state",cmd_dev);
												char *send_char=cJSON_PrintUnformatted(root_v);
												int my_len = strlen(send_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,send_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												free(send_char);
												send_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
												cJSON_Delete(root_v);
												root_v = NULL;
											}
											free(value);
											value=NULL;
											free(level);
											level=NULL;
										}
									}
								}
							}
						}
					}
					pthread_mutex_unlock(&mutex_zl);
					cJSON_Delete(device_state_list_data);
					device_state_list_data=NULL;
					break;
				}
			}
		}
	}
	free(data_str);
	data_str=NULL;
	free(mac_str);
	mac_str=NULL;
	free(port_str);
	port_str=NULL;
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
}
void dev_into_net(uint8_t *u_data)
{
	cJSON *net_root = cJSON_CreateObject();
	cJSON_AddNumberToObject(net_root,"retcode",0);
	cJSON_AddStringToObject(net_root,"message","success");
	cJSON_AddStringToObject(net_root,"api","dev_net_res");
	cJSON *net_data = cJSON_CreateObject();
	cJSON_AddItemToObject(net_root,"data",net_data);
	if(u_data[10] ==0x20)
	{
		cJSON_AddStringToObject(net_data,"res","1");
		net_record_time = time(NULL);
		go_net_flag=1;
	}
	else
	{
		cJSON_AddStringToObject(net_data,"res","0");
		go_net_flag=0;
	}
	char *net_root_char = cJSON_PrintUnformatted(net_root);
	int my_len = strlen(net_root_char);
	char *my_send_char = (char *)malloc(my_len+2);
	memset(my_send_char,0,my_len+2);
	memcpy(my_send_char,net_root_char,my_len);
	strcat(my_send_char,"\n\0");
	send(cd,my_send_char,my_len+1,0);
	cJSON_Delete(net_root);
	net_root=NULL;
	free(net_root_char);
	net_root_char=NULL;
	free(my_send_char);
	my_send_char=NULL;
}
void up_dev_describe(cJSON *root)//删除列表更新而更新状态列表
{
	cJSON *delete_data = cJSON_GetObjectItem(root,"data");
	if(strcmp(delete_data->child->string,"mac")==0)
	{
		cJSON *delete_mac = cJSON_GetObjectItem(delete_data,"mac");
		uint8_t *dev_net_delete = NULL;
		dev_net_delete = (uint8_t *)malloc(16);
		memset(dev_net_delete,0,16);
		cmd_delete_mix(delete_mac->valuestring,"00",dev_net_delete);
		find_mac_and_send(delete_mac->valuestring,dev_net_delete,16);
		delete_gw_bind_mac(delete_mac->valuestring);
		free(dev_net_delete);
		dev_net_delete=NULL;
		cJSON *dev_list_data = NULL;
		pthread_mutex_lock(&mutex_sl);
		dev_list_data = cJSON_Parse(device_list);
		pthread_mutex_unlock(&mutex_sl);
		if(dev_list_data != NULL)
		{
			if(dev_list_data->child !=NULL)
			{
				int i;
				cJSON *my_dev_list_data = NULL;
				cJSON *my_dev_list_list = NULL;
				my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
				my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
				int	data_l =  cJSON_GetArraySize(my_dev_list_list);
				cJSON *data_arr = NULL;
				cJSON *data_mac = NULL;
				cJSON *data_id = NULL;
				for(i=0;i<data_l;i++)
				{
					data_arr = cJSON_GetArrayItem(my_dev_list_list,i);
					data_mac = cJSON_GetObjectItem(data_arr,"mac");
					if(strcmp(delete_mac->valuestring,data_mac->valuestring)==0)
					{
						data_id = cJSON_GetObjectItem(data_arr,"dev_id");
						pthread_mutex_lock(&mutex_zl);
						cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
						if(device_state_list_data != NULL)
						{
							if(device_state_list_data->child != NULL)
							{
								cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
								cJSON *while_device_state_list_data = my_device_state_list_data->child;
								while(while_device_state_list_data != NULL)
								{
									if(strcmp(while_device_state_list_data->string,data_id->valuestring)==0)
									{
										cJSON_DeleteItemFromObject(my_device_state_list_data,data_id->valuestring);
										char *delete_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,delete_char,strlen(delete_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,delete_char,strlen(delete_char));
										fsync(state_fd);
										close(state_fd);
										free(delete_char);
										delete_char=NULL;
										break;
									}
									while_device_state_list_data = while_device_state_list_data->next;
								}
							}
						}
						pthread_mutex_unlock(&mutex_zl);
						cJSON_Delete(device_state_list_data);
						device_state_list_data=NULL;
					}
				}
			}
		}
		cJSON_Delete(dev_list_data);
		dev_list_data = NULL;
	}
	else if(strcmp(delete_data->child->string,"dev_id")==0)
	{
		cJSON *delete_id = cJSON_GetObjectItem(delete_data,"dev_id");
		pthread_mutex_lock(&mutex_zl);
		cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
		if(device_state_list_data != NULL)
		{
			if(device_state_list_data->child != NULL)
			{
				cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
				cJSON *while_device_state_list_data = my_device_state_list_data->child;
				while(while_device_state_list_data != NULL)
				{
					if(strcmp(while_device_state_list_data->string,delete_id->valuestring)==0)
					{
						cJSON_DeleteItemFromObject(my_device_state_list_data,delete_id->valuestring);
						char *delete_char = cJSON_PrintUnformatted(device_state_list_data);
						memset(device_state_list,0,BUFFSIZE);
						memcpy(device_state_list,delete_char,strlen(delete_char));
						int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
						write(state_fd,delete_char,strlen(delete_char));
						fsync(state_fd);
						close(state_fd);
						free(delete_char);
						delete_char=NULL;
						break;
					}
					while_device_state_list_data = while_device_state_list_data->next;
				}
			}
		}
		pthread_mutex_unlock(&mutex_zl);
		cJSON_Delete(device_state_list_data);
		device_state_list_data=NULL;
	}
}

void up_dev_des(void)//随着列表更新而更新状态列表
{
	cJSON *dev_list_data = NULL;
	pthread_mutex_lock(&mutex_sl);
	dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	int i,j,data_l,a,flag_have;
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child !=NULL)
		{
			cJSON *my_dev_list_data = NULL;
			cJSON *my_dev_list_list = NULL;
			my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr = NULL;
			cJSON *data_id = NULL;
			cJSON *data_mac = NULL;
			cJSON *data_port = NULL;
			cJSON *data_type = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr = cJSON_GetArrayItem(my_dev_list_list,i);
				data_id = cJSON_GetObjectItem(data_arr,"dev_id");
				data_type = cJSON_GetObjectItem(data_arr,"dev_type");
				data_mac = cJSON_GetObjectItem(data_arr,"mac");
				data_port = cJSON_GetObjectItem(data_arr,"dev_port");
				pthread_mutex_lock(&mutex_zl);
				cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
				if(device_state_list_data != NULL)
				{
					if(device_state_list_data->child != NULL)
					{
						cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
						cJSON *while_device_state_list_data = my_device_state_list_data->child;
						if(while_device_state_list_data==NULL)
						{
							a=0;
							if(strcmp(data_type->valuestring,"020101")==0)//可燃气体报警
								a=1;
							else if(strcmp(data_type->valuestring,"020102")==0)//紧急按钮报警器
								a=1;
							else if(strcmp(data_type->valuestring,"020103")==0)//一氧化碳报警器
								a=1;
							else if(strcmp(data_type->valuestring,"020104")==0)//烟雾报警器
								a=1;
							else if(strcmp(data_type->valuestring,"020201")==0)//门磁触发报警
								a=2;
							else if(strcmp(data_type->valuestring,"020202")==0)//人体红外接近报警
								a=2;
							else if(strcmp(data_type->valuestring,"020204")==0)//水浸报警器
								a=2;
							else if(strcmp(data_type->valuestring,"010101")==0)//墙壁开关
								a=3;
							else if(strcmp(data_type->valuestring,"010102")==0)//86插座	
								a=3;
							else if(strcmp(data_type->valuestring,"010103")==0)//带背光开关
								a=3;
							else if(strcmp(data_type->valuestring,"010104")==0)//语音开关
								a=3;
							else if(strcmp(data_type->valuestring,"010201")==0)//调光灯
								a=3;
							else if(strcmp(data_type->valuestring,"010301")==0)//RGB调色灯
								a=3;
							else if(strcmp(data_type->valuestring,"010501")==0)//声光报警开关
								a=3;
							else if(strcmp(data_type->valuestring,"010601")==0)//电磁阀开关
								a=3;
							else if(strcmp(data_type->valuestring,"040101")==0)//普通窗帘
								a=3;
							else if(strcmp(data_type->valuestring,"040102")==0)//推窗器
								a=3;
							else if(strcmp(data_type->valuestring,"040201")==0)//百分比窗帘
								a=3;
							else if(strcmp(data_type->valuestring,"040301")==0)//百叶窗帘
								a=3;
							else if(strcmp(data_type->valuestring,"080301")==0)//温控器面板
								a=3;
							else if(strcmp(data_type->valuestring,"080401")==0)//中央空调
								a=3;
							if(a==1 || a==2)
							{
								cJSON *secure_root = cJSON_CreateObject();
								cJSON *secure_root_data = cJSON_CreateObject();
								cJSON *secure_root_state = cJSON_CreateObject();
								cJSON_AddNumberToObject(secure_root,"retcode",0);
								cJSON_AddStringToObject(secure_root,"message","success");
								cJSON_AddStringToObject(secure_root,"api","secuStateRes");
								cJSON_AddItemToObject(secure_root,"data",secure_root_data);
								cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
								cJSON_AddStringToObject(secure_root_data,"dev_id",data_id->valuestring);
								cJSON_AddStringToObject(secure_root_data,"dev_type",data_type->valuestring);
								if(a==1)
								cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else
								cJSON_AddStringToObject(secure_root_state,"dev_state","00");
								char *secure_root_char = cJSON_PrintUnformatted(secure_root);
								int my_len = strlen(secure_root_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,secure_root_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								free(secure_root_char);
								secure_root_char=NULL;
								free(my_send_char);
								my_send_char=NULL;
								cJSON_Delete(secure_root);
								secure_root=NULL;
								cJSON *state_root = cJSON_CreateObject();
								cJSON_AddItemToObject(my_device_state_list_data,data_id->valuestring,state_root);
								if(a==1)
								cJSON_AddStringToObject(state_root,"dev_state","01");
								else
								cJSON_AddStringToObject(state_root,"dev_state","00");
								char *state_char = cJSON_PrintUnformatted(device_state_list_data);
								memset(device_state_list,0,BUFFSIZE);
								memcpy(device_state_list,state_char,strlen(state_char));
								int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
								write(state_fd,state_char,strlen(state_char));
								fsync(state_fd);
								close(state_fd);
								free(state_char);
								state_char=NULL;
							}
							else if(a==3)
							{
								uint8_t *final_cmd_stastus = (uint8_t *)malloc(16);
								memset(final_cmd_stastus,0,16);
								cmd_mix_get_stastus1(data_mac->valuestring,data_port->valuestring,"00",final_cmd_stastus);
								find_mac_and_send(data_mac->valuestring,final_cmd_stastus,16);
								free(final_cmd_stastus);
								final_cmd_stastus=NULL;
								usleep(200000);	
							}
						}
						else
						{
							while(while_device_state_list_data != NULL)
							{
								if(strcmp(while_device_state_list_data->string,data_id->valuestring)==0)
								{
									a=0;
									if(strcmp(data_type->valuestring,"020101")==0)//020101~060205都是带电量的设备，需要判断
										a=1;
									else if(strcmp(data_type->valuestring,"020102")==0)
										a=1;
									else if(strcmp(data_type->valuestring,"020103")==0)
										a=1;
									else if(strcmp(data_type->valuestring,"020104")==0)
										a=1;
									else if(strcmp(data_type->valuestring,"020201")==0)
										a=1;
									else if(strcmp(data_type->valuestring,"020202")==0)
										a=1;
									else if(strcmp(data_type->valuestring,"020204")==0)
										a=1;
									else
										break;
									if(a==1)
									{
										cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,data_id->valuestring);
										int num_sec = cJSON_GetArraySize(dev_state_cjson);
										cJSON *arr_for=NULL;
										flag_have=0;
										for(j=0;j<num_sec;j++)
										{
											arr_for = cJSON_GetArrayItem(dev_state_cjson,j);
											if(!strcmp(arr_for->string,"dev_state"))
											{
												flag_have=1;
												break;
											}
										}
										if(flag_have==1)
											break;
										else
										{
											cJSON *secure_root = cJSON_CreateObject();
											cJSON *secure_root_data = cJSON_CreateObject();
											cJSON *secure_root_state = cJSON_CreateObject();
											cJSON_AddNumberToObject(secure_root,"retcode",0);
											cJSON_AddStringToObject(secure_root,"message","success");
											cJSON_AddStringToObject(secure_root,"api","secuStateRes");
											cJSON_AddItemToObject(secure_root,"data",secure_root_data);
											cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
											cJSON_AddStringToObject(secure_root_data,"dev_id",data_id->valuestring);
											cJSON_AddStringToObject(secure_root_data,"dev_type",data_type->valuestring);
											if(!strcmp(data_type->valuestring,"020201"))
											cJSON_AddStringToObject(secure_root_state,"dev_state","00");
											else if(!strcmp(data_type->valuestring,"020202"))
											cJSON_AddStringToObject(secure_root_state,"dev_state","00");
											else if(!strcmp(data_type->valuestring,"020204"))
											cJSON_AddStringToObject(secure_root_state,"dev_state","00");
											else
											cJSON_AddStringToObject(secure_root_state,"dev_state","01");
											char *secure_root_char = cJSON_PrintUnformatted(secure_root);
											int my_len = strlen(secure_root_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,secure_root_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											free(secure_root_char);
											secure_root_char=NULL;
											free(my_send_char);
											my_send_char=NULL;
											cJSON_Delete(secure_root);
											secure_root=NULL;
											if(!strcmp(data_type->valuestring,"020201"))
											cJSON_AddStringToObject(dev_state_cjson,"dev_state","00");
											else if(!strcmp(data_type->valuestring,"020202"))
											cJSON_AddStringToObject(dev_state_cjson,"dev_state","00");
											else if(!strcmp(data_type->valuestring,"020204"))
											cJSON_AddStringToObject(dev_state_cjson,"dev_state","00");
											else
											cJSON_AddStringToObject(dev_state_cjson,"dev_state","01");
											char *state_char = cJSON_PrintUnformatted(device_state_list_data);
											memset(device_state_list,0,BUFFSIZE);
											memcpy(device_state_list,state_char,strlen(state_char));
											int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
											write(state_fd,state_char,strlen(state_char));
											fsync(state_fd);
											close(state_fd);
											free(state_char);
											state_char=NULL;
											break;
										}
									}
								}
								while_device_state_list_data = while_device_state_list_data->next;
								if(while_device_state_list_data==NULL)
								{
									a=0;
									if(strcmp(data_type->valuestring,"020101")==0)//可燃气体报警
										a=1;
									else if(strcmp(data_type->valuestring,"020102")==0)//紧急按钮报警器
										a=1;
									else if(strcmp(data_type->valuestring,"020103")==0)//一氧化碳报警器
										a=1;
									else if(strcmp(data_type->valuestring,"020104")==0)//烟雾报警器
										a=1;
									else if(strcmp(data_type->valuestring,"020201")==0)//门磁触发报警
										a=2;
									else if(strcmp(data_type->valuestring,"020202")==0)//人体红外接近报警
										a=2;
									else if(strcmp(data_type->valuestring,"020204")==0)//水浸报警器
										a=2;
									else if(strcmp(data_type->valuestring,"010101")==0)//墙壁开关
										a=3;
									else if(strcmp(data_type->valuestring,"010102")==0)//86插座	
										a=3;
									else if(strcmp(data_type->valuestring,"010103")==0)//带背光开关
										a=3;
									else if(strcmp(data_type->valuestring,"010104")==0)//语音开关
										a=3;
									else if(strcmp(data_type->valuestring,"010201")==0)//调光灯
										a=3;
									else if(strcmp(data_type->valuestring,"010301")==0)//RGB调色灯
										a=3;
									else if(strcmp(data_type->valuestring,"010501")==0)//声光报警开关
										a=3;
									else if(strcmp(data_type->valuestring,"010601")==0)//电磁阀开关
										a=3;
									else if(strcmp(data_type->valuestring,"040101")==0)//普通窗帘
										a=3;
									else if(strcmp(data_type->valuestring,"040102")==0)//推窗器
										a=3;
									else if(strcmp(data_type->valuestring,"040201")==0)//百分比窗帘
										a=3;
									else if(strcmp(data_type->valuestring,"040301")==0)//百叶窗帘
										a=3;
									else if(strcmp(data_type->valuestring,"080301")==0)//温控器面板
										a=3;
									else if(strcmp(data_type->valuestring,"080401")==0)//中央空调
										a=3;
									if(a==1 || a==2)
									{
										cJSON *secure_root = cJSON_CreateObject();
										cJSON *secure_root_data = cJSON_CreateObject();
										cJSON *secure_root_state = cJSON_CreateObject();
										cJSON_AddNumberToObject(secure_root,"retcode",0);
										cJSON_AddStringToObject(secure_root,"message","success");
										cJSON_AddStringToObject(secure_root,"api","secuStateRes");
										cJSON_AddItemToObject(secure_root,"data",secure_root_data);
										cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
										cJSON_AddStringToObject(secure_root_data,"dev_id",data_id->valuestring);
										cJSON_AddStringToObject(secure_root_data,"dev_type",data_type->valuestring);
										if(a==1)
										cJSON_AddStringToObject(secure_root_state,"dev_state","01");
										else
										cJSON_AddStringToObject(secure_root_state,"dev_state","00");
										char *secure_root_char = cJSON_PrintUnformatted(secure_root);
										int my_len = strlen(secure_root_char);
										char *my_send_char = (char *)malloc(my_len+2);
										memset(my_send_char,0,my_len+2);
										memcpy(my_send_char,secure_root_char,my_len);
										strcat(my_send_char,"\n\0");
										send(cd,my_send_char,my_len+1,0);
										free(secure_root_char);
										secure_root_char=NULL;
										free(my_send_char);
										my_send_char=NULL;
										cJSON_Delete(secure_root);
										secure_root=NULL;
										cJSON *state_root = cJSON_CreateObject();
										cJSON_AddItemToObject(my_device_state_list_data,data_id->valuestring,state_root);
										if(a==1)
										cJSON_AddStringToObject(state_root,"dev_state","01");
										else
										cJSON_AddStringToObject(state_root,"dev_state","00");
										char *state_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,state_char,strlen(state_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,state_char,strlen(state_char));
										fsync(state_fd);
										close(state_fd);
										free(state_char);
										state_char=NULL;
									}
									else if(a == 3)
									{
										uint8_t *final_cmd_stastus = (uint8_t *)malloc(16);
										memset(final_cmd_stastus,0,16);
										cmd_mix_get_stastus1(data_mac->valuestring,data_port->valuestring,"00",final_cmd_stastus);
										find_mac_and_send(data_mac->valuestring,final_cmd_stastus,16);
										free(final_cmd_stastus);
										final_cmd_stastus=NULL;
										usleep(200000);	
									}
								}
							}
						}
					}
				}
				pthread_mutex_unlock(&mutex_zl);
				cJSON_Delete(device_state_list_data);
				device_state_list_data = NULL;
			}
		}
	}
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
}
void update_state(void)
{
	typedef struct device_id
	{
		cJSON *id_dev;
		int flag;
		struct device_id *next;
	}DEV;
	DEV *dev_head,*dev_z,*dev_d,*p;
	dev_head=dev_z=dev_d=p=NULL;
	int data_l = 0,num=0;
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_id = NULL;
			int i;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
				if(dev_head==NULL)
				{
					dev_d = (DEV *)malloc(sizeof(DEV));
					dev_d->id_dev = tem_id;
					dev_d->flag = 0;
					dev_head = dev_z = dev_d;
					dev_d->next = NULL;
				}
				else
				{
					p=dev_head;
					while(p != NULL)
					{
						p = p->next;
						if(p==NULL)
						{
							dev_d = (DEV *)malloc(sizeof(DEV));
							dev_d->id_dev = tem_id;
							dev_d->flag = 0;
							dev_z->next = dev_d;
							dev_d->next = NULL;
							dev_z = dev_d;
						}
					}
				}
			}
		}
	}
	cJSON *delete_prev = NULL;
	pthread_mutex_lock(&mutex_zl);
	cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
	if(device_state_list_data != NULL)
	{
		if(device_state_list_data->child != NULL)
		{
			cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
			cJSON *while_device_state_list_data = my_device_state_list_data->child;
			while(while_device_state_list_data != NULL)
			{
				if(data_l==0)
				{
					delete_prev = while_device_state_list_data;
					while_device_state_list_data = while_device_state_list_data->next;
					cJSON_DeleteItemFromObject(my_device_state_list_data,delete_prev->string);
				}
				else
				{
					p = dev_head;
					while(p != NULL)
					{
						if(strcmp(p->id_dev->valuestring,while_device_state_list_data->string)==0 && p->flag==0)
						{
							while_device_state_list_data = while_device_state_list_data->next;
							p->flag = 1;
							num+=1;
							break;
						}
						else if(strcmp(p->id_dev->valuestring,while_device_state_list_data->string)==0 && p->flag==1)
						{
							delete_prev = while_device_state_list_data;
							while_device_state_list_data = while_device_state_list_data->next;
							cJSON_DeleteItemFromArray(my_device_state_list_data,num);
							break;
						}
						p = p->next;
						if(p==NULL)
						{
							delete_prev = while_device_state_list_data;
							while_device_state_list_data = while_device_state_list_data->next;
							cJSON_DeleteItemFromObject(my_device_state_list_data,delete_prev->string);
						}
					}
				}
			}
		}
	}
	char *delete_char = cJSON_PrintUnformatted(device_state_list_data);
	memset(device_state_list,0,BUFFSIZE);
	memcpy(device_state_list,delete_char,strlen(delete_char));
	int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
	write(state_fd,device_state_list,strlen(device_state_list));
	fsync(state_fd);
	close(state_fd);
	free(delete_char);
	delete_char=NULL;
	pthread_mutex_unlock(&mutex_zl);
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
	cJSON_Delete(device_state_list_data);
	device_state_list_data=NULL;
	while(dev_head!=NULL)
	{
		p = dev_head;
		dev_head = dev_head->next;
		free(p);
		p=NULL;
	}
}
void run_scene(char *sce_id)
{
	pthread_mutex_lock(&mutex_scene);
	cJSON *scene_list_root = cJSON_Parse(scene_list);//遍历情景列表
	pthread_mutex_unlock(&mutex_scene);
	if(scene_list_root != NULL)
	{
		if(scene_list_root->child !=NULL)
		{
			cJSON *scene_list_data = cJSON_GetObjectItem(scene_list_root,"data");
			if(scene_list_data->child != NULL)
			{
				cJSON *scene_list_list = cJSON_GetObjectItem(scene_list_data,"scen_list");
				int scene_num = cJSON_GetArraySize(scene_list_list);
				int i;
				cJSON *scene_id_my = NULL;
				cJSON *scene_for = NULL;
				for(i=0;i<scene_num;i++)
				{
					scene_for = cJSON_GetArrayItem(scene_list_list,i);
					scene_id_my = cJSON_GetObjectItem(scene_for,"scen_id");
					if(strcmp(sce_id,scene_id_my->valuestring)==0)
					{
						cJSON *scene_enable = cJSON_GetObjectItem(scene_for,"is_enable");
						if(strcmp(scene_enable->valuestring,"1")==0)//need run scene
						{
							char *scene_id_pthread = (char *)malloc(strlen(sce_id)+1);
							memset(scene_id_pthread,0,strlen(sce_id)+1);
							memcpy(scene_id_pthread,sce_id,strlen(sce_id)+1);
							pth_creat_my(run_the_scene,scene_id_pthread);
							if(NET_FLAG)
							{
								cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
								cJSON *send_root = cJSON_CreateObject();
								cJSON_AddStringToObject(send_root,"co","orange");
								cJSON_AddStringToObject(send_root,"api","gw_up_msg");
								cJSON *data_scene = cJSON_CreateObject();
								cJSON_AddItemToObject(send_root,"data",data_scene);
								cJSON_AddStringToObject(data_scene,"id",sce_id);
								cJSON_AddStringToObject(data_scene,"msg_type","0203");
								if(strcmp(push->valuestring,"1")==0)
									cJSON_AddStringToObject(data_scene,"is_push","1");
								else
									cJSON_AddStringToObject(data_scene,"is_push","0");
								char *send_char = cJSON_PrintUnformatted(send_root);
								int my_len = strlen(send_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,send_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								free(send_char);
								send_char=NULL;
								free(my_send_char);
								my_send_char=NULL;
								cJSON_Delete(send_root);
								send_root=NULL;
							}
						}
						break;//找到对应的情景Id
					}
				}
			}
		}
	}
	cJSON_Delete(scene_list_root);
	scene_list_root = NULL;
}

void run_the_scene(char *str_id)
{
	int flag_run = 1;//默认执行
	int a,return_val;
	int num_arr,flag_have;
	pthread_mutex_lock(&mutex_scene);
	cJSON *scene_detail_root = cJSON_Parse(scene_detail);//遍历情景明细
	pthread_mutex_unlock(&mutex_scene);
	if(scene_detail_root != NULL)
	{
		if(scene_detail_root->child !=NULL)
		{
			cJSON *scene_detail_data = cJSON_GetObjectItem(scene_detail_root,"data");
			if(scene_detail_data->child != NULL)
			{
				cJSON *scene_detail_list = cJSON_GetObjectItem(scene_detail_data,"scen_list");
				int i,j,condition_num,k,scene_detail_num;
				cJSON *scene_id = NULL;
				cJSON *scene_for = NULL;
				cJSON *dev_condition_list = NULL;
				cJSON *dev_id_condition = NULL;
				cJSON *condtion_for = NULL;
				cJSON *type_condition = NULL;
				cJSON *dev_state_root = NULL;
				cJSON *arr_for = NULL;
				cJSON *while_scene_list = scene_detail_list->child;
				while(while_scene_list != NULL)
				{
					if(strcmp(str_id,while_scene_list->string)==0)//find scene_id
					{
						scene_id = cJSON_GetObjectItem(scene_detail_list,str_id);
						scene_detail_num = cJSON_GetArraySize(scene_id);
						for(i=0;i<scene_detail_num;i++)
						{
							scene_for = cJSON_GetArrayItem(scene_id,i);
							flag_run=1;
							dev_condition_list = cJSON_GetObjectItem(scene_for,"dev_condition_list");
							condition_num = cJSON_GetArraySize(dev_condition_list);
							for(j=0;j<condition_num;j++)
							{
								condtion_for = cJSON_GetArrayItem(dev_condition_list,j);
								dev_id_condition = cJSON_GetObjectItem(condtion_for,"dev_id");
								pthread_mutex_lock(&mutex_zl);
								cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
								pthread_mutex_unlock(&mutex_zl);
								if(device_state_list_data != NULL)
								{
									if(device_state_list_data->child != NULL)
									{
										cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
										cJSON *while_device_state_list_data = my_device_state_list_data->child;
										while(while_device_state_list_data !=NULL)
										{
											if(strcmp(while_device_state_list_data->string,dev_id_condition->valuestring)==0)
											{
												cJSON *device_status = cJSON_GetObjectItem(my_device_state_list_data,while_device_state_list_data->string);
												type_condition = cJSON_GetObjectItem(condtion_for,"dev_type");
												dev_state_root = cJSON_GetObjectItem(condtion_for,"dev_state");
												a=0;
												if(strcmp(type_condition->valuestring,"060201")==0)
													a=1;
												else if(strcmp(type_condition->valuestring,"060202")==0)
													a=1;
												else if(strcmp(type_condition->valuestring,"060203")==0)
													a=3;
												else if(strcmp(type_condition->valuestring,"060204")==0)
													a=1;
												else if(strcmp(type_condition->valuestring,"060205")==0)
													a=1;
												else if(strcmp(type_condition->valuestring,"060206")==0)
													a=1;
												else
													a=2;
												if(a==1)
												{
													flag_have=0;
													num_arr = cJSON_GetArraySize(device_status);
													for(k=0;k<num_arr;k++)
													{
														arr_for = cJSON_GetArrayItem(device_status,k);
														if(strcmp(arr_for->string,"state_level")==0)
														{
															flag_have=1;
															break;
														}
													}
													if(flag_have==1)
													{	
														cJSON *dev_data_my = cJSON_GetObjectItem(dev_state_root,"state_level");
														cJSON *status_data = cJSON_GetObjectItem(device_status,"state_level");
														if(strcmp(dev_data_my->valuestring,status_data->valuestring)==0)
															break;
														else
														{	
															flag_run = 0;
															break;
														}
													}
													else
													{
														flag_run = 0;
														break;
													}
												}
												else if(a==2)
												{
													flag_have=0;
													num_arr = cJSON_GetArraySize(device_status);
													for(k=0;k<num_arr;k++)
													{
														arr_for = cJSON_GetArrayItem(device_status,k);
														if(strcmp(arr_for->string,"dev_state")==0)
														{
															flag_have=1;
															break;
														}
													}
													if(flag_have==1)
													{
														cJSON *dev_data_my = cJSON_GetObjectItem(dev_state_root,"dev_state");
														cJSON *status_data = cJSON_GetObjectItem(device_status,"dev_state");
														if(strcmp(status_data->valuestring,dev_data_my->valuestring)==0)
															break;
														else
														{
															flag_run = 0;
															break;
														}
													}
													else
													{
														flag_run = 0;
														break;
													}
												}
												else if(a==3)
												{
													flag_have=0;
													num_arr = cJSON_GetArraySize(device_status);
													for(k=0;k<num_arr;k++)
													{
														arr_for = cJSON_GetArrayItem(device_status,k);
														if(strcmp(arr_for->string,"state_data")==0)
														{
															flag_have=1;
															break;
														}
													}
													if(flag_have==1)
													{	
														cJSON *dev_data_my = cJSON_GetObjectItem(dev_state_root,"state_data");
														cJSON *status_data = cJSON_GetObjectItem(device_status,"state_data");
														if(dev_data_my->valuestring[0]=='-')
														{
															if(atoi(dev_data_my->valuestring+1)-atoi(status_data->valuestring) >= 0)
																break;
															else
															{
																flag_run = 0;
																break;
															}
														}
														else
														{
															if(atoi(dev_data_my->valuestring+1)-atoi(status_data->valuestring) <= 0)
																break;
															else
															{
																flag_run = 0;
																break;
															}
														}
													}
													else
													{
														flag_run = 0;
														break;
													}
												}
												else 
													break;
											}
											while_device_state_list_data = while_device_state_list_data->next;
										}
									}
								}
								cJSON_Delete(device_state_list_data);
								device_state_list_data=NULL;
								if(flag_run==0)
								break;
							}
							if(flag_run)
							{	
								return_val = 6;
								cJSON *time_delay = cJSON_GetObjectItem(scene_for,"time_delay");
								sleep(atoi(time_delay->valuestring));
								if(atoi(time_delay->valuestring)==0)
								usleep(200000);
								cJSON *allow_root = cJSON_GetObjectItem(scene_for,"allowed_time");
								int t_n = cJSON_GetArraySize(allow_root);
								if(t_n==0)
								{
									return_val = scene_time_judge(NULL,scene_for,str_id);
								}
								else
								{
									int num_for;
									cJSON *allow_for = NULL;
									for(num_for=0;num_for<t_n;num_for++)
									{
										allow_for = cJSON_GetArrayItem(allow_root,num_for);
										return_val = scene_time_judge(allow_for->valuestring,scene_for,str_id);
										if(return_val == 0 || return_val ==1)
											break;
									}
								}
								if(return_val ==1)
									break;
							}
						}
						break;
					}
					while_scene_list = while_scene_list->next;
				}
			}
		}
	}
	free(str_id);
	str_id=NULL;
	cJSON_Delete(scene_detail_root);
	scene_detail_root=NULL;
	pthread_exit((void *)0);
}

void run_scene_u_triger(char *dev_id,char *status)
{
	pthread_mutex_lock(&mutex_scene);
	cJSON *scene_list_root = cJSON_Parse(scene_list);//遍历情景列表
	pthread_mutex_unlock(&mutex_scene);
	if(scene_list_root != NULL)
	{
		if(scene_list_root->child !=NULL)
		{
			cJSON *scene_list_data = cJSON_GetObjectItem(scene_list_root,"data");
			if(scene_list_data->child != NULL)
			{
				cJSON *scene_list_list = cJSON_GetObjectItem(scene_list_data,"scen_list");
				int scene_num = cJSON_GetArraySize(scene_list_list);
				int i;
				int condition_num;
				int j;
				cJSON *dev_id_condition = NULL;
				cJSON *dev_list_condition = NULL;
				cJSON *scene_for = NULL;
				cJSON *condtion_for = NULL;
				for(i=0;i<scene_num;i++)
				{
					scene_for = cJSON_GetArrayItem(scene_list_list,i);
					dev_list_condition = cJSON_GetObjectItem(scene_for,"trigger_dev_list");
					condition_num = cJSON_GetArraySize(dev_list_condition);
					for(j=0;j<condition_num;j++)
					{
						condtion_for = cJSON_GetArrayItem(dev_list_condition,j);
						dev_id_condition = cJSON_GetObjectItem(condtion_for,"dev_id");
						if(strcmp(dev_id_condition->valuestring,dev_id)==0)//找到触发设备id
						{
							cJSON *scene_enable_is_or = cJSON_GetObjectItem(scene_for,"is_enable");
							if(strcmp(scene_enable_is_or->valuestring,"1")==0)
							{
								cJSON *dev_status_root = cJSON_GetObjectItem(condtion_for,"dev_state");
								cJSON *dev_status = cJSON_GetObjectItem(dev_status_root,"dev_state");
								if(!strcmp(dev_status->valuestring,"all"))
								{
									cJSON *allow_time = cJSON_GetObjectItem(condtion_for,"dev_time");
									int num_allow_time = cJSON_GetArraySize(allow_time);
									if(num_allow_time == 0)
									{
										cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
										char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
										memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
										memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
										pth_creat_my(run_the_scene,scene_id_pthread);
										if(NET_FLAG)
										{
											cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
											cJSON *send_root = cJSON_CreateObject();
											cJSON_AddStringToObject(send_root,"co","orange");
											cJSON_AddStringToObject(send_root,"api","gw_up_msg");
											cJSON *data_scene = cJSON_CreateObject();
											cJSON_AddItemToObject(send_root,"data",data_scene);
											cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
											cJSON_AddStringToObject(data_scene,"msg_type","0203");
											if(strcmp(push->valuestring,"1")==0)
												cJSON_AddStringToObject(data_scene,"is_push","1");
											else
												cJSON_AddStringToObject(data_scene,"is_push","0");
											char *send_char = cJSON_PrintUnformatted(send_root);
											int my_len = strlen(send_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,send_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											free(send_char);
											send_char=NULL;
											free(my_send_char);
											my_send_char=NULL;
											cJSON_Delete(send_root);
											send_root=NULL;
										}
									}
									else
									{
										int k;
										cJSON *time_for = NULL;
										for(k=0;k<num_allow_time;k++)
										{
											time_for = cJSON_GetArrayItem(allow_time,k);
											if(trigger_source_time_judge(time_for->valuestring)==0)
											{
												cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
												char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
												memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
												memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
												pth_creat_my(run_the_scene,scene_id_pthread);
												if(NET_FLAG)
												{
													cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
													cJSON *send_root = cJSON_CreateObject();
													cJSON_AddStringToObject(send_root,"co","orange");
													cJSON_AddStringToObject(send_root,"api","gw_up_msg");
													cJSON *data_scene = cJSON_CreateObject();
													cJSON_AddItemToObject(send_root,"data",data_scene);
													cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
													cJSON_AddStringToObject(data_scene,"msg_type","0203");
													if(strcmp(push->valuestring,"1")==0)
														cJSON_AddStringToObject(data_scene,"is_push","1");
													else
														cJSON_AddStringToObject(data_scene,"is_push","0");
													char *send_char = cJSON_PrintUnformatted(send_root);
													int my_len = strlen(send_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,send_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													free(send_char);
													send_char=NULL;
													free(my_send_char);
													my_send_char=NULL;
													cJSON_Delete(send_root);
													send_root=NULL;
												}
												break;
											}
										}
									}
								}
								else
								{
									char *str = NULL;
									str = strtok(dev_status->valuestring,"-");
									while(str!=NULL)
									{
										if(strcmp(str,status)==0)//执行情景
										{
											cJSON *allow_time = cJSON_GetObjectItem(condtion_for,"dev_time");
											int num_allow_time = cJSON_GetArraySize(allow_time);
											if(num_allow_time == 0)
											{
												cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
												char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
												memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
												memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
												pth_creat_my(run_the_scene,scene_id_pthread);
												if(NET_FLAG)
												{
													cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
													cJSON *send_root = cJSON_CreateObject();
													cJSON_AddStringToObject(send_root,"co","orange");
													cJSON_AddStringToObject(send_root,"api","gw_up_msg");
													cJSON *data_scene = cJSON_CreateObject();
													cJSON_AddItemToObject(send_root,"data",data_scene);
													cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
													cJSON_AddStringToObject(data_scene,"msg_type","0203");
													if(strcmp(push->valuestring,"1")==0)
														cJSON_AddStringToObject(data_scene,"is_push","1");
													else
														cJSON_AddStringToObject(data_scene,"is_push","0");
													char *send_char = cJSON_PrintUnformatted(send_root);
													int my_len = strlen(send_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,send_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													free(send_char);
													send_char=NULL;
													free(my_send_char);
													my_send_char=NULL;
													cJSON_Delete(send_root);
													send_root=NULL;
												}
											}
											else
											{
												int k;
												cJSON *time_for = NULL;
												for(k=0;k<num_allow_time;k++)
												{
													time_for = cJSON_GetArrayItem(allow_time,k);
													if(trigger_source_time_judge(time_for->valuestring)==0)
													{
														cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
														char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
														memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
														memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
														pth_creat_my(run_the_scene,scene_id_pthread);
														if(NET_FLAG)
														{
															cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
															cJSON *send_root = cJSON_CreateObject();
															cJSON_AddStringToObject(send_root,"co","orange");
															cJSON_AddStringToObject(send_root,"api","gw_up_msg");
															cJSON *data_scene = cJSON_CreateObject();
															cJSON_AddItemToObject(send_root,"data",data_scene);
															cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
															cJSON_AddStringToObject(data_scene,"msg_type","0203");
															if(strcmp(push->valuestring,"1")==0)
																cJSON_AddStringToObject(data_scene,"is_push","1");
															else
																cJSON_AddStringToObject(data_scene,"is_push","0");
															char *send_char = cJSON_PrintUnformatted(send_root);
															int my_len = strlen(send_char);
															char *my_send_char = (char *)malloc(my_len+2);
															memset(my_send_char,0,my_len+2);
															memcpy(my_send_char,send_char,my_len);
															strcat(my_send_char,"\n\0");
															send(cd,my_send_char,my_len+1,0);
															free(send_char);
															send_char=NULL;
															free(my_send_char);
															my_send_char=NULL;
															cJSON_Delete(send_root);
															send_root=NULL;
														}
														break;
													}
												}
											}
											break;
										}
										str = strtok(NULL,"-");
									}
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	cJSON_Delete(scene_list_root);
	scene_list_root=NULL;
}
void run_scene_u_triger_sensor(char *dev_id,char *status)
{
	pthread_mutex_lock(&mutex_scene);
	cJSON *scene_list_root = cJSON_Parse(scene_list);//遍历情景列表
	pthread_mutex_unlock(&mutex_scene);
	if(scene_list_root != NULL)
	{
		if(scene_list_root->child !=NULL)
		{
			cJSON *scene_list_data = cJSON_GetObjectItem(scene_list_root,"data");
			if(scene_list_data->child != NULL)
			{
				cJSON *scene_list_list = cJSON_GetObjectItem(scene_list_data,"scen_list");
				int scene_num = cJSON_GetArraySize(scene_list_list);
				int i;
				int condition_num;
				int j,flag_do;
				cJSON *dev_id_condition = NULL;
				cJSON *dev_type_condition = NULL;
				cJSON *dev_list_condition = NULL;
				cJSON *scene_for = NULL;
				cJSON *condtion_for = NULL;
				for(i=0;i<scene_num;i++)
				{
					scene_for = cJSON_GetArrayItem(scene_list_list,i);
					dev_list_condition = cJSON_GetObjectItem(scene_for,"trigger_dev_list");
					condition_num = cJSON_GetArraySize(dev_list_condition);
					for(j=0;j<condition_num;j++)
					{
						condtion_for = cJSON_GetArrayItem(dev_list_condition,j);
						dev_id_condition = cJSON_GetObjectItem(condtion_for,"dev_id");
						dev_type_condition = cJSON_GetObjectItem(condtion_for,"dev_type");
						if(strcmp(dev_id_condition->valuestring,dev_id)==0)//找到触发设备id
						{
							cJSON *scene_enable_is_or = cJSON_GetObjectItem(scene_for,"is_enable");
							if(strcmp(scene_enable_is_or->valuestring,"1")==0)
							{
								cJSON *dev_status_root = cJSON_GetObjectItem(condtion_for,"dev_state");
								if(strcmp(dev_type_condition->valuestring,"060203"))
								{
									cJSON *dev_status = cJSON_GetObjectItem(dev_status_root,"state_level");
									if(!strcmp(dev_status->valuestring,"all"))
									{
										cJSON *allow_time = cJSON_GetObjectItem(condtion_for,"dev_time");
										int num_allow_time = cJSON_GetArraySize(allow_time);
										if(num_allow_time == 0)
										{
											cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
											char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
											memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
											memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
											pth_creat_my(run_the_scene,scene_id_pthread);
											if(NET_FLAG)
											{
												cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
												cJSON *send_root = cJSON_CreateObject();
												cJSON_AddStringToObject(send_root,"co","orange");
												cJSON_AddStringToObject(send_root,"api","gw_up_msg");
												cJSON *data_scene = cJSON_CreateObject();
												cJSON_AddItemToObject(send_root,"data",data_scene);
												cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
												cJSON_AddStringToObject(data_scene,"msg_type","0203");
												if(strcmp(push->valuestring,"1")==0)
													cJSON_AddStringToObject(data_scene,"is_push","1");
												else
													cJSON_AddStringToObject(data_scene,"is_push","0");
												char *send_char = cJSON_PrintUnformatted(send_root);
												int my_len = strlen(send_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,send_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												free(send_char);
												send_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
												cJSON_Delete(send_root);
												send_root=NULL;
											}
										}
										else
										{
											int k;
											cJSON *time_for = NULL;
											for(k=0;k<num_allow_time;k++)
											{
												time_for = cJSON_GetArrayItem(allow_time,k);
												if(trigger_source_time_judge(time_for->valuestring)==0)
												{
													cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
													char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
													memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
													memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
													pth_creat_my(run_the_scene,scene_id_pthread);
													if(NET_FLAG)
													{
														cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
														cJSON *send_root = cJSON_CreateObject();
														cJSON_AddStringToObject(send_root,"co","orange");
														cJSON_AddStringToObject(send_root,"api","gw_up_msg");
														cJSON *data_scene = cJSON_CreateObject();
														cJSON_AddItemToObject(send_root,"data",data_scene);
														cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
														cJSON_AddStringToObject(data_scene,"msg_type","0203");
														if(strcmp(push->valuestring,"1")==0)
															cJSON_AddStringToObject(data_scene,"is_push","1");
														else
															cJSON_AddStringToObject(data_scene,"is_push","0");
														char *send_char = cJSON_PrintUnformatted(send_root);
														int my_len = strlen(send_char);
														char *my_send_char = (char *)malloc(my_len+2);
														memset(my_send_char,0,my_len+2);
														memcpy(my_send_char,send_char,my_len);
														strcat(my_send_char,"\n\0");
														send(cd,my_send_char,my_len+1,0);
														free(send_char);
														send_char=NULL;
														free(my_send_char);
														my_send_char=NULL;
														cJSON_Delete(send_root);
														send_root=NULL;
													}
													break;
												}
											}
										}
									}
									else
									{
										char *str = NULL;
										str = strtok(dev_status->valuestring,"-");
										while(str!=NULL)
										{
											if(strcmp(str,status)==0)//执行情景
											{
												cJSON *allow_time = cJSON_GetObjectItem(condtion_for,"dev_time");
												int num_allow_time = cJSON_GetArraySize(allow_time);
												if(num_allow_time == 0)
												{
													cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
													char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
													memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
													memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
													pth_creat_my(run_the_scene,scene_id_pthread);
													if(NET_FLAG)
													{
														cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
														cJSON *send_root = cJSON_CreateObject();
														cJSON_AddStringToObject(send_root,"co","orange");
														cJSON_AddStringToObject(send_root,"api","gw_up_msg");
														cJSON *data_scene = cJSON_CreateObject();
														cJSON_AddItemToObject(send_root,"data",data_scene);
														cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
														cJSON_AddStringToObject(data_scene,"msg_type","0203");
														if(strcmp(push->valuestring,"1")==0)
															cJSON_AddStringToObject(data_scene,"is_push","1");
														else
															cJSON_AddStringToObject(data_scene,"is_push","0");
														char *send_char = cJSON_PrintUnformatted(send_root);
														int my_len = strlen(send_char);
														char *my_send_char = (char *)malloc(my_len+2);
														memset(my_send_char,0,my_len+2);
														memcpy(my_send_char,send_char,my_len);
														strcat(my_send_char,"\n\0");
														send(cd,my_send_char,my_len+1,0);
														free(send_char);
														send_char=NULL;
														free(my_send_char);
														my_send_char=NULL;
														cJSON_Delete(send_root);
														send_root=NULL;
													}
												}
												else
												{
													int k;
													cJSON *time_for = NULL;
													for(k=0;k<num_allow_time;k++)
													{
														time_for = cJSON_GetArrayItem(allow_time,k);
														if(trigger_source_time_judge(time_for->valuestring)==0)
														{
															cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
															char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
															memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
															memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
															pth_creat_my(run_the_scene,scene_id_pthread);
															if(NET_FLAG)
															{
																cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
																cJSON *send_root = cJSON_CreateObject();
																cJSON_AddStringToObject(send_root,"co","orange");
																cJSON_AddStringToObject(send_root,"api","gw_up_msg");
																cJSON *data_scene = cJSON_CreateObject();
																cJSON_AddItemToObject(send_root,"data",data_scene);
																cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
																cJSON_AddStringToObject(data_scene,"msg_type","0203");
																if(strcmp(push->valuestring,"1")==0)
																	cJSON_AddStringToObject(data_scene,"is_push","1");
																else
																	cJSON_AddStringToObject(data_scene,"is_push","0");
																char *send_char = cJSON_PrintUnformatted(send_root);
																int my_len = strlen(send_char);
																char *my_send_char = (char *)malloc(my_len+2);
																memset(my_send_char,0,my_len+2);
																memcpy(my_send_char,send_char,my_len);
																strcat(my_send_char,"\n\0");
																send(cd,my_send_char,my_len+1,0);
																free(send_char);
																send_char=NULL;
																free(my_send_char);
																my_send_char=NULL;
																cJSON_Delete(send_root);
																send_root=NULL;
															}
															break;
														}
													}
												}
												break;
											}
											str = strtok(NULL,"-");
										}
									}
								}
								else
								{
									cJSON *dev_status = cJSON_GetObjectItem(dev_status_root,"state_data");
									if(!strcmp(dev_status->valuestring,"all"))
									{
										cJSON *allow_time = cJSON_GetObjectItem(condtion_for,"dev_time");
										int num_allow_time = cJSON_GetArraySize(allow_time);
										if(num_allow_time == 0)
										{
											cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
											char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
											memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
											memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
											pth_creat_my(run_the_scene,scene_id_pthread);
											if(NET_FLAG)
											{
												cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
												cJSON *send_root = cJSON_CreateObject();
												cJSON_AddStringToObject(send_root,"co","orange");
												cJSON_AddStringToObject(send_root,"api","gw_up_msg");
												cJSON *data_scene = cJSON_CreateObject();
												cJSON_AddItemToObject(send_root,"data",data_scene);
												cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
												cJSON_AddStringToObject(data_scene,"msg_type","0203");
												if(strcmp(push->valuestring,"1")==0)
													cJSON_AddStringToObject(data_scene,"is_push","1");
												else
													cJSON_AddStringToObject(data_scene,"is_push","0");
												char *send_char = cJSON_PrintUnformatted(send_root);
												int my_len = strlen(send_char);
												char *my_send_char = (char *)malloc(my_len+2);
												memset(my_send_char,0,my_len+2);
												memcpy(my_send_char,send_char,my_len);
												strcat(my_send_char,"\n\0");
												send(cd,my_send_char,my_len+1,0);
												free(send_char);
												send_char=NULL;
												free(my_send_char);
												my_send_char=NULL;
												cJSON_Delete(send_root);
												send_root=NULL;
											}
										}
										else
										{
											int k;
											cJSON *time_for = NULL;
											for(k=0;k<num_allow_time;k++)
											{
												time_for = cJSON_GetArrayItem(allow_time,k);
												if(trigger_source_time_judge(time_for->valuestring)==0)
												{
													cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
													char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
													memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
													memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
													pth_creat_my(run_the_scene,scene_id_pthread);
													if(NET_FLAG)
													{
														cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
														cJSON *send_root = cJSON_CreateObject();
														cJSON_AddStringToObject(send_root,"co","orange");
														cJSON_AddStringToObject(send_root,"api","gw_up_msg");
														cJSON *data_scene = cJSON_CreateObject();
														cJSON_AddItemToObject(send_root,"data",data_scene);
														cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
														cJSON_AddStringToObject(data_scene,"msg_type","0203");
														if(strcmp(push->valuestring,"1")==0)
															cJSON_AddStringToObject(data_scene,"is_push","1");
														else
															cJSON_AddStringToObject(data_scene,"is_push","0");
														char *send_char = cJSON_PrintUnformatted(send_root);
														int my_len = strlen(send_char);
														char *my_send_char = (char *)malloc(my_len+2);
														memset(my_send_char,0,my_len+2);
														memcpy(my_send_char,send_char,my_len);
														strcat(my_send_char,"\n\0");
														send(cd,my_send_char,my_len+1,0);
														free(send_char);
														send_char=NULL;
														free(my_send_char);
														my_send_char=NULL;
														cJSON_Delete(send_root);
														send_root=NULL;
													}
													break;
												}
											}
										}
									}
									else
									{
										flag_do = 0;
										if(dev_status->valuestring[0] == '-')
										{
											if(atoi(dev_status->valuestring+1)-atoi(status) >= 0)
												flag_do = 1;
										}
										else
										{
											if(atoi(dev_status->valuestring+1)-atoi(status) <= 0)
												flag_do = 1;
										}
										if(flag_do)//执行情景
										{
											cJSON *allow_time = cJSON_GetObjectItem(condtion_for,"dev_time");
											int num_allow_time = cJSON_GetArraySize(allow_time);
											if(num_allow_time == 0)
											{
												cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
												char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
												memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
												memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
												pth_creat_my(run_the_scene,scene_id_pthread);
												if(NET_FLAG)
												{
													cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
													cJSON *send_root = cJSON_CreateObject();
													cJSON_AddStringToObject(send_root,"co","orange");
													cJSON_AddStringToObject(send_root,"api","gw_up_msg");
													cJSON *data_scene = cJSON_CreateObject();
													cJSON_AddItemToObject(send_root,"data",data_scene);
													cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
													cJSON_AddStringToObject(data_scene,"msg_type","0203");
													if(strcmp(push->valuestring,"1")==0)
														cJSON_AddStringToObject(data_scene,"is_push","1");
													else
														cJSON_AddStringToObject(data_scene,"is_push","0");
													char *send_char = cJSON_PrintUnformatted(send_root);
													int my_len = strlen(send_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,send_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													free(send_char);
													send_char=NULL;
													free(my_send_char);
													my_send_char=NULL;
													cJSON_Delete(send_root);
													send_root=NULL;
												}
											}
											else
											{
												int k;
												cJSON *time_for = NULL;
												for(k=0;k<num_allow_time;k++)
												{
													time_for = cJSON_GetArrayItem(allow_time,k);
													if(trigger_source_time_judge(time_for->valuestring)==0)
													{
														cJSON *scene_id_zx = cJSON_GetObjectItem(scene_for,"scen_id");
														char *scene_id_pthread = (char *)malloc(strlen(scene_id_zx->valuestring)+1);
														memset(scene_id_pthread,0,strlen(scene_id_zx->valuestring)+1);
														memcpy(scene_id_pthread,scene_id_zx->valuestring,strlen(scene_id_zx->valuestring)+1);
														pth_creat_my(run_the_scene,scene_id_pthread);
														if(NET_FLAG)
														{
															cJSON *push = cJSON_GetObjectItem(scene_for,"is_push");
															cJSON *send_root = cJSON_CreateObject();
															cJSON_AddStringToObject(send_root,"co","orange");
															cJSON_AddStringToObject(send_root,"api","gw_up_msg");
															cJSON *data_scene = cJSON_CreateObject();
															cJSON_AddItemToObject(send_root,"data",data_scene);
															cJSON_AddStringToObject(data_scene,"id",scene_id_zx->valuestring);
															cJSON_AddStringToObject(data_scene,"msg_type","0203");
															if(strcmp(push->valuestring,"1")==0)
																cJSON_AddStringToObject(data_scene,"is_push","1");
															else
																cJSON_AddStringToObject(data_scene,"is_push","0");
															char *send_char = cJSON_PrintUnformatted(send_root);
															int my_len = strlen(send_char);
															char *my_send_char = (char *)malloc(my_len+2);
															memset(my_send_char,0,my_len+2);
															memcpy(my_send_char,send_char,my_len);
															strcat(my_send_char,"\n\0");
															send(cd,my_send_char,my_len+1,0);
															free(send_char);
															send_char=NULL;
															free(my_send_char);
															my_send_char=NULL;
															cJSON_Delete(send_root);
															send_root=NULL;
														}
														break;
													}
												}
											}
										}
									}
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	cJSON_Delete(scene_list_root);
	scene_list_root=NULL;
}

int scene_time_judge(char *my_time,cJSON *mxid,char *strid)
{
	int flag_kt=0;
	int class,num,flag_have;
	if( my_time == NULL )
		flag_kt = 1;
	else 
	{
		char *str1 = NULL;
		char *str2 = NULL;
		str1 = strtok(my_time, "-");
		str2 = strtok(NULL, "-");
		if( strcmp(str1,str2) > 0)//跨天执行
		{
			time_t nowtime;
			struct tm* nt;
			time(&nowtime);
			nt = localtime(&nowtime);
			char nowtime_str[10];
			memset(nowtime_str,0,10);
			sprintf(nowtime_str,"%02d:%02d:%02d",nt->tm_hour,nt->tm_min,nt->tm_sec);
			if(strcmp(nowtime_str,str2) > 0 && strcmp(nowtime_str,str1) < 0 )
				flag_kt = 0;
			else
				flag_kt = 1;
		}
		else if( strcmp(str1,str2) <= 0 )//无需跨天执行
		{
			time_t nowtime;
			struct tm* nt;
			time(&nowtime);
			nt = localtime(&nowtime);
			char nowtime_str[10];
			memset(nowtime_str,0,10);
			sprintf(nowtime_str,"%02d:%02d:%02d",nt->tm_hour,nt->tm_min,nt->tm_sec);
			if( strcmp(nowtime_str,str1) >= 0 && strcmp(nowtime_str,str2) <= 0)
				flag_kt = 1;
		}
	}
	if( flag_kt )//执行
	{
		cJSON *type_mx = cJSON_GetObjectItem(mxid,"mx_type");
		if(strcmp(type_mx->valuestring,"1")==0)//普通设备控制
		{
			cJSON *dev_cmd_root = cJSON_GetObjectItem(mxid,"cmd");
			cJSON *dev_id_zx = cJSON_GetObjectItem(dev_cmd_root,"dev_id");
			cJSON *cmd_root = cJSON_GetObjectItem(dev_cmd_root,"dev_cmd");
			cJSON *cmd_zx = cJSON_GetObjectItem(cmd_root,"cmd");
			pthread_mutex_lock(&mutex_sl);
			cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
			pthread_mutex_unlock(&mutex_sl);
			if(dev_list_data != NULL)
			{
				if(dev_list_data->child != NULL)
				{
					cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
					cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
					int	data_l =  cJSON_GetArraySize(my_dev_list_list);
					int k;
					cJSON *data_arr_jx = NULL;
					cJSON *tem_id = NULL;
					for(k=0;k<data_l;k++)
					{
						data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,k);
						tem_id = cJSON_GetObjectItem(data_arr_jx,"dev_id");
						if(strcmp(dev_id_zx->valuestring,tem_id->valuestring)==0)
						{
							cJSON *tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
							cJSON *tem_port = cJSON_GetObjectItem(data_arr_jx,"dev_port");
							cJSON *tem_type = cJSON_GetObjectItem(data_arr_jx,"dev_type");
							class=0;
							if(!strcmp(tem_type->valuestring,"040301"))//bycl
								class=1;
							else if(!strcmp(tem_type->valuestring,"010301"))//rgb
								class=2;
							else if(!strcmp(tem_type->valuestring,"020201"))//门磁触发报警
								class=3;
							else if(!strcmp(tem_type->valuestring,"020202"))//人体红外接近报警器
								class=3;
							else if(!strcmp(tem_type->valuestring,"020204"))//水浸报警器
								class=3;
							else if(!strcmp(tem_type->valuestring,"050101"))//kt
								class=5;
							else if(!strcmp(tem_type->valuestring,"050201"))
								class=6;
							else if(!strcmp(tem_type->valuestring,"050202"))
								class=6;
							else if(!strcmp(tem_type->valuestring,"050203"))
								class=6;
							else if(!strcmp(tem_type->valuestring,"050204"))
								class=6;
							else if(!strcmp(tem_type->valuestring,"050205"))
								class=6;
							else if(!strcmp(tem_type->valuestring,"010101"))//墙壁开关	
								class=4;
							else if(!strcmp(tem_type->valuestring,"010102"))//86插座
								class=4;
							else if(!strcmp(tem_type->valuestring,"010103"))//带背光开关
								class=4;
							else if(!strcmp(tem_type->valuestring,"010104"))//语音开关
								class=4;
							else if(!strcmp(tem_type->valuestring,"010201"))//调光灯
								class=4;
							else if(!strcmp(tem_type->valuestring,"010501"))//声光报警开关
								class=4;
							else if(!strcmp(tem_type->valuestring,"010601"))//电磁阀开关（机械手）
								class=4;
							else if(!strcmp(tem_type->valuestring,"040101"))//普通窗帘
								class=4;
							else if(!strcmp(tem_type->valuestring,"040102"))//推窗器
								class=4;
							else if(!strcmp(tem_type->valuestring,"040201"))//百分比窗帘
								class=4;
							else if(!strcmp(tem_type->valuestring,"080401"))//中央空调
								class=10;
							else if(!strcmp(tem_type->valuestring,"080301"))//温控器
							class=8;
							if(class==1)//bycl
							{
								uint8_t *final_cmd = NULL;
								final_cmd = (uint8_t *)malloc(17);
								memset(final_cmd,0,17);
								if(!strcmp(cmd_zx->valuestring,"reverse"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													if(my_dev_state->valuestring[0]=='0' && my_dev_state->valuestring[1]=='0')
													{
														my_dev_state->valuestring[0]='6';
														my_dev_state->valuestring[1]='4';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													else
													{
														my_dev_state->valuestring[0]='0';
														my_dev_state->valuestring[1]='0';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									cJSON_Delete(device_state_list_data);
									device_state_list_data= NULL;
								}
								else if(!strcmp(cmd_zx->valuestring,"add"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{	
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													uint8_t num_str;
													str_to_hex(&num_str,my_dev_state->valuestring+2,1);
													if(num_str>=0x5a)
													{
														my_dev_state->valuestring[2]='6';
														my_dev_state->valuestring[3]='4';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													else 
													{
														num_str+=0x0a;
														hex_to_str(&num_str,my_dev_state->valuestring+2,1);
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									cJSON_Delete(device_state_list_data);
									device_state_list_data= NULL;
								}
								else if(!strcmp(cmd_zx->valuestring,"sub"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													uint8_t num_str;
													str_to_hex(&num_str,my_dev_state->valuestring+2,1);
													if(num_str<=0x0a)
													{
														my_dev_state->valuestring[2]='0';
														my_dev_state->valuestring[3]='0';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													else 
													{
														num_str-=0x0a;
														hex_to_str(&num_str,my_dev_state->valuestring+2,1);;
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									cJSON_Delete(device_state_list_data);
									device_state_list_data= NULL;
								}
								else
								cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,cmd_zx->valuestring,final_cmd);
								if(final_cmd[0] != final_cmd[1])
								{
									resend_zt(17,final_cmd,tem_id->valuestring,tem_type->valuestring);
									find_mac_and_send(tem_mac->valuestring,final_cmd,17);
								}
								free(final_cmd);
								final_cmd = NULL;
							}
							else if(class==2)//rgb
							{
								uint8_t *final_cmd = NULL;
								final_cmd = (uint8_t *)malloc(19);
								memset(final_cmd,0,19);
								if(!strcmp(cmd_zx->valuestring,"reverse"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													if(my_dev_state->valuestring[6]=='0' && my_dev_state->valuestring[7]=='0')
													{
														my_dev_state->valuestring[6] = 'f';
														my_dev_state->valuestring[7] = 'f';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													else
													{
														my_dev_state->valuestring[6] = '0';
														my_dev_state->valuestring[7] = '0';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									cJSON_Delete(device_state_list_data);
									device_state_list_data=NULL;
								}
								else if(!strcmp(cmd_zx->valuestring,"add"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													uint8_t num_str;
													str_to_hex(&num_str,my_dev_state->valuestring+6,1);
													if(num_str>=0xe6)
													{
														my_dev_state->valuestring[6]='f';
														my_dev_state->valuestring[7]='f';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													else
													{
														num_str+=0x19;
														hex_to_str(&num_str,my_dev_state->valuestring+6,1);
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									cJSON_Delete(device_state_list_data);
									device_state_list_data= NULL;
								}
								else if(!strcmp(cmd_zx->valuestring,"sub"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													uint8_t num_str;
													str_to_hex(&num_str,my_dev_state->valuestring+6,1);
													if(num_str<=0x19)
													{
														my_dev_state->valuestring[6]='0';
														my_dev_state->valuestring[7]='0';
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													else 
													{
														num_str-=0x19;
														hex_to_str(&num_str,my_dev_state->valuestring+6,1);;
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									cJSON_Delete(device_state_list_data);
									device_state_list_data= NULL;
								}
								else
									cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,cmd_zx->valuestring,final_cmd);
								if(final_cmd[0] != final_cmd[1])
								{
									resend_zt(19,final_cmd,tem_id->valuestring,tem_type->valuestring);
									find_mac_and_send(tem_mac->valuestring,final_cmd,19);
								}
								free(final_cmd);
								final_cmd = NULL;
							}
							else if(class==3)
							{
								if(!strcmp(cmd_zx->valuestring,"reverse"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													num = cJSON_GetArraySize(dev_state_cjson);
													flag_have=0;
													cJSON *arr_for=NULL;
													int m;
													for(m=0;m<num;m++)
													{
														arr_for=cJSON_GetArrayItem(dev_state_cjson,m);
														if(strcmp(arr_for->string,"dev_state")==0)
														{
															flag_have=1;
															break;
														}
													}
													if(flag_have==1)
													{
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														if(!strcmp(my_dev_state->valuestring,"00"))
														{
															memset(my_dev_state->valuestring,0,strlen(my_dev_state->valuestring));
															memcpy(my_dev_state->valuestring,"01",2);
														}
														else if(!strcmp(my_dev_state->valuestring,"01"))
														{
															memset(my_dev_state->valuestring,0,strlen(my_dev_state->valuestring));
															memcpy(my_dev_state->valuestring,"00",2);
														}
														if(NET_FLAG)
														{
															cJSON *secure_root = cJSON_CreateObject();
															cJSON *secure_root_data = cJSON_CreateObject();
															cJSON *secure_root_state = cJSON_CreateObject();
															cJSON_AddNumberToObject(secure_root,"retcode",0);
															cJSON_AddStringToObject(secure_root,"message","success");
															cJSON_AddStringToObject(secure_root,"api","secuStateRes");
															cJSON_AddItemToObject(secure_root,"data",secure_root_data);
															cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
															cJSON_AddStringToObject(secure_root_data,"dev_id",tem_id->valuestring);
															cJSON_AddStringToObject(secure_root_data,"dev_type",tem_type->valuestring);
															cJSON_AddStringToObject(secure_root_state,"dev_state",my_dev_state->valuestring);
															char *secure_root_char = cJSON_PrintUnformatted(secure_root);
															int my_len = strlen(secure_root_char);
															char *my_send_char = (char *)malloc(my_len+2);
															memset(my_send_char,0,my_len+2);
															memcpy(my_send_char,secure_root_char,my_len);
															strcat(my_send_char,"\n\0");
															send(cd,my_send_char,my_len+1,0);
															free(secure_root_char);
															secure_root_char=NULL;
															free(my_send_char);
															my_send_char=NULL;
															cJSON_Delete(secure_root);
															secure_root=NULL;
														}
														pthread_mutex_lock(&mutex_qj);
														if(strcmp(qj_model,"0104"))
														{
															int qj_model_fd = open("/root/qj_model.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
															write(qj_model_fd,"0104",strlen(qj_model));
															fsync(qj_model_fd);
															close(qj_model_fd);
															if(NET_FLAG)
															{
																cJSON *secure_model_now = cJSON_CreateObject();
																cJSON *secure_model_now_data = cJSON_CreateObject();
																cJSON_AddNumberToObject(secure_model_now,"retcode",0);
																cJSON_AddStringToObject(secure_model_now,"message","success");
																cJSON_AddStringToObject(secure_model_now,"api","secuModelRes");
																cJSON_AddItemToObject(secure_model_now,"data",secure_model_now_data);
																cJSON_AddStringToObject(secure_model_now_data,"model","0104");
																char *secure_model_now_char = cJSON_PrintUnformatted(secure_model_now);
																int my_len = strlen(secure_model_now_char);
																char *my_send_char = (char *)malloc(my_len+2);
																memset(my_send_char,0,my_len+2);
																memcpy(my_send_char,secure_model_now_char,my_len);
																strcat(my_send_char,"\n\0");
																send(cd,my_send_char,my_len+1,0);
																free(secure_model_now_char);
																secure_model_now_char=NULL;
																free(my_send_char);
																my_send_char=NULL;
																cJSON_Delete(secure_model_now);
																secure_model_now=NULL;
															}
															memset(qj_model,0,5);
															memcpy(qj_model,"0104",4);
														}
														pthread_mutex_unlock(&mutex_qj);
														char *state_char = cJSON_PrintUnformatted(device_state_list_data);
														memset(device_state_list,0,BUFFSIZE);
														memcpy(device_state_list,state_char,strlen(state_char));
														int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
														write(state_fd,state_char,strlen(state_char));
														fsync(state_fd);
														close(state_fd);
														free(state_char);
														state_char=NULL;
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									pthread_mutex_unlock(&mutex_zl);
									cJSON_Delete(device_state_list_data);
									device_state_list_data=NULL;
								}
								else
								{
									if(NET_FLAG)
									{
										cJSON *secure_root = cJSON_CreateObject();
										cJSON *secure_root_data = cJSON_CreateObject();
										cJSON *secure_root_state = cJSON_CreateObject();
										cJSON_AddNumberToObject(secure_root,"retcode",0);
										cJSON_AddStringToObject(secure_root,"message","success");
										cJSON_AddStringToObject(secure_root,"api","secuStateRes");
										cJSON_AddItemToObject(secure_root,"data",secure_root_data);
										cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
										cJSON_AddStringToObject(secure_root_data,"dev_id",tem_id->valuestring);
										cJSON_AddStringToObject(secure_root_data,"dev_type",tem_type->valuestring);
										cJSON_AddStringToObject(secure_root_state,"dev_state",cmd_zx->valuestring);
										char *secure_root_char = cJSON_PrintUnformatted(secure_root);
										int my_len = strlen(secure_root_char);
										char *my_send_char = (char *)malloc(my_len+2);
										memset(my_send_char,0,my_len+2);
										memcpy(my_send_char,secure_root_char,my_len);
										strcat(my_send_char,"\n\0");
										send(cd,my_send_char,my_len+1,0);
										free(secure_root_char);
										secure_root_char=NULL;
										free(my_send_char);
										my_send_char=NULL;
										cJSON_Delete(secure_root);
										secure_root=NULL;
									}
									pthread_mutex_lock(&mutex_qj);
									if(strcmp(qj_model,"0104"))
									{
										int qj_model_fd = open("/root/qj_model.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(qj_model_fd,"0104",strlen(qj_model));
										fsync(qj_model_fd);
										close(qj_model_fd);
										if(NET_FLAG)
										{
											cJSON *secure_model_now = cJSON_CreateObject();
											cJSON *secure_model_now_data = cJSON_CreateObject();
											cJSON_AddNumberToObject(secure_model_now,"retcode",0);
											cJSON_AddStringToObject(secure_model_now,"message","success");
											cJSON_AddStringToObject(secure_model_now,"api","secuModelRes");
											cJSON_AddItemToObject(secure_model_now,"data",secure_model_now_data);
											cJSON_AddStringToObject(secure_model_now_data,"model","0104");
											char *secure_model_now_char = cJSON_PrintUnformatted(secure_model_now);
											int my_len = strlen(secure_model_now_char);
											char *my_send_char = (char *)malloc(my_len+2);
											memset(my_send_char,0,my_len+2);
											memcpy(my_send_char,secure_model_now_char,my_len);
											strcat(my_send_char,"\n\0");
											send(cd,my_send_char,my_len+1,0);
											free(secure_model_now_char);
											secure_model_now_char=NULL;
											free(my_send_char);
											my_send_char=NULL;
											cJSON_Delete(secure_model_now);
											secure_model_now=NULL;
										}
										memset(qj_model,0,5);
										memcpy(qj_model,"0104",4);
									}
									pthread_mutex_unlock(&mutex_qj);
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											if(while_device_state_list_data==NULL)
											{
												cJSON *state_root = cJSON_CreateObject();
												cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,state_root);
												cJSON_AddStringToObject(state_root,"dev_state",cmd_zx->valuestring);
												char *state_char = cJSON_PrintUnformatted(device_state_list_data);
												memset(device_state_list,0,BUFFSIZE);
												memcpy(device_state_list,state_char,strlen(state_char));
												int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
												write(state_fd,state_char,strlen(state_char));
												fsync(state_fd);
												close(state_fd);
												free(state_char);
												state_char=NULL;
											}
											else
											{
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(while_device_state_list_data->string,tem_id->valuestring)==0)
													{
														cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														num = cJSON_GetArraySize(dev_state_cjson);
														int m;
														flag_have=0;
														cJSON *arr_for=NULL;
														for(m=0;m<num;m++)
														{
															arr_for = cJSON_GetArrayItem(dev_state_cjson,m);
															if(!strcmp(arr_for->string,"dev_state"))
															{
																flag_have=1;
																break;
															}
														}
														if(flag_have==1)
														cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
														cJSON_AddStringToObject(dev_state_cjson,"dev_state",cmd_zx->valuestring);
														char *state_char = cJSON_PrintUnformatted(device_state_list_data);
														memset(device_state_list,0,BUFFSIZE);
														memcpy(device_state_list,state_char,strlen(state_char));
														int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
														write(state_fd,state_char,strlen(state_char));
														fsync(state_fd);
														close(state_fd);
														free(state_char);
														state_char=NULL;
														break;
													}
													while_device_state_list_data=while_device_state_list_data->next;
													if(while_device_state_list_data==NULL)
													{
														cJSON *state_root = cJSON_CreateObject();
														cJSON_AddItemToObject(my_device_state_list_data,tem_id->valuestring,state_root);
														cJSON_AddStringToObject(state_root,"dev_state",cmd_zx->valuestring);
														char *state_char = cJSON_PrintUnformatted(device_state_list_data);
														memset(device_state_list,0,BUFFSIZE);
														memcpy(device_state_list,state_char,strlen(state_char));
														int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
														write(state_fd,state_char,strlen(state_char));
														fsync(state_fd);
														close(state_fd);
														free(state_char);
														state_char=NULL;
													}
												}
											}
										}
									}
									pthread_mutex_unlock(&mutex_zl);
									cJSON_Delete(device_state_list_data);
									device_state_list_data=NULL;
								}
							}
							else if(class==4)
							{
								uint8_t *final_cmd = NULL;
								final_cmd = (uint8_t *)malloc(16);
								memset(final_cmd,0,16);
								if(!strcmp(cmd_zx->valuestring,"reverse"))
								{
									pthread_mutex_lock(&mutex_zl);
									cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
									pthread_mutex_unlock(&mutex_zl);
									if(device_state_list_data != NULL)
									{
										if(device_state_list_data->child != NULL)
										{
											cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
											cJSON *while_device_state_list_data = my_device_state_list_data->child;
											while(while_device_state_list_data != NULL)
											{
												if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
												{
													cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
													cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
													if(strcmp(tem_type->valuestring,"040201")==0)//bfbcl
													{
														if(strcmp(my_dev_state->valuestring,"00")==0)
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"64",final_cmd);
														else
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
													}
													else if(strcmp(tem_type->valuestring,"010201")==0)//tgd
													{
														if(strcmp(my_dev_state->valuestring,"00")==0)
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"ff",final_cmd);
														else
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
													}
													else
													{
														if(strcmp(my_dev_state->valuestring,"00")==0)
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"01",final_cmd);
														else
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
													}
													break;
												}
												while_device_state_list_data = while_device_state_list_data->next;
											}
										}
									}
									cJSON_Delete(device_state_list_data);
									device_state_list_data=NULL;
								}
								else if(!strcmp(cmd_zx->valuestring,"add"))
								{
									if(strcmp(tem_type->valuestring,"010201")==0)//tgd
									{
										pthread_mutex_lock(&mutex_zl);
										cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
										pthread_mutex_unlock(&mutex_zl);
										if(device_state_list_data != NULL)
										{
											if(device_state_list_data->child != NULL)
											{
												cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
												cJSON *while_device_state_list_data = my_device_state_list_data->child;
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
													{
														cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														uint8_t num_str;
														str_to_hex(&num_str,my_dev_state->valuestring,1);
														if(num_str>=0xe6)
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"ff",final_cmd);
														else
														{
															num_str+=0x19;
															hex_to_str(&num_str,my_dev_state->valuestring,1);
															cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
														}
														break;
													}
													while_device_state_list_data = while_device_state_list_data->next;
												}
											}
										}
										cJSON_Delete(device_state_list_data);
										device_state_list_data= NULL;
									}
									else if(strcmp(tem_type->valuestring,"040201")==0)//bfbcl
									{
										pthread_mutex_lock(&mutex_zl);
										cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
										pthread_mutex_unlock(&mutex_zl);
										if(device_state_list_data != NULL)
										{
											if(device_state_list_data->child != NULL)
											{
												cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
												cJSON *while_device_state_list_data = my_device_state_list_data->child;
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
													{
														cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														uint8_t num_str;
														str_to_hex(&num_str,my_dev_state->valuestring,1);
														if(num_str>=0x5a)
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"64",final_cmd);
														else 
														{
															num_str+=0x0a;
															hex_to_str(&num_str,my_dev_state->valuestring,1);
															cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
														}
														break;
													}
													while_device_state_list_data = while_device_state_list_data->next;
												}
											}
										}
										cJSON_Delete(device_state_list_data);
										device_state_list_data= NULL;
									}
								}
								else if(!strcmp(cmd_zx->valuestring,"sub"))
								{
									if(strcmp(tem_type->valuestring,"010201")==0)//tgd
									{
										pthread_mutex_lock(&mutex_zl);
										cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
										pthread_mutex_unlock(&mutex_zl);
										if(device_state_list_data != NULL)
										{
											if(device_state_list_data->child != NULL)
											{
												cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
												cJSON *while_device_state_list_data = my_device_state_list_data->child;
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
													{
														cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														uint8_t num_str;
														str_to_hex(&num_str,my_dev_state->valuestring,1);
														if(num_str<=0x19)
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
														else 
														{
															num_str-=0x19;
															hex_to_str(&num_str,my_dev_state->valuestring,1);
															cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
														}
														break;
													}
													while_device_state_list_data = while_device_state_list_data->next;
												}
											}
										}
										cJSON_Delete(device_state_list_data);
										device_state_list_data= NULL;
									}
									else if(strcmp(tem_type->valuestring,"040201")==0)//bfbcl
									{
										pthread_mutex_lock(&mutex_zl);
										cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
										pthread_mutex_unlock(&mutex_zl);
										if(device_state_list_data != NULL)
										{
											if(device_state_list_data->child != NULL)
											{
												cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
												cJSON *while_device_state_list_data = my_device_state_list_data->child;
												while(while_device_state_list_data != NULL)
												{
													if(strcmp(tem_id->valuestring,while_device_state_list_data->string)==0)
													{
														cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,tem_id->valuestring);
														cJSON *my_dev_state = cJSON_GetObjectItem(dev_state_cjson,"dev_state");
														uint8_t num_str;
														str_to_hex(&num_str,my_dev_state->valuestring,1);
														if(num_str<=0x0a)
														cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,"00",final_cmd);
														else
														{
															num_str-=0x0a;
															hex_to_str(&num_str,my_dev_state->valuestring,1);
															cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,my_dev_state->valuestring,final_cmd);
														}
														break;
													}
													while_device_state_list_data = while_device_state_list_data->next;
												}
											}
										}
										cJSON_Delete(device_state_list_data);
										device_state_list_data= NULL;
									}
								}
								else
									cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,cmd_zx->valuestring,final_cmd);
								if(final_cmd[0] != final_cmd[1])
								{
									resend_zt(16,final_cmd,tem_id->valuestring,tem_type->valuestring);
									find_mac_and_send(tem_mac->valuestring,final_cmd,16);
								}
								free(final_cmd);
								final_cmd = NULL;
							}
							else if(class==5)
							{
								cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
								int str_len = strlen(tem_lid->valuestring);
								if(str_len)
								{
									pthread_mutex_lock(&mutex_code);
									cJSON *code_id_root = cJSON_Parse(code_id);
									pthread_mutex_unlock(&mutex_code);
									if(code_id_root != NULL)
									{
										if(code_id_root->child != NULL)
										{
											cJSON *kt_root = cJSON_GetObjectItem(code_id_root,"kt");
											if(kt_root != NULL)
											{
												cJSON *kt_while = kt_root->child;
												if(kt_while==NULL && NET_FLAG)
												{
													cJSON *hw_request_root = cJSON_CreateObject();
													cJSON_AddStringToObject(hw_request_root,"co","orange");
													cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
													cJSON *hw_request_data = cJSON_CreateObject();
													cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
													cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
													cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
													cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
													cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
													cJSON *hw_request_cmd = cJSON_CreateObject();
													cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
													cJSON_AddStringToObject(hw_request_cmd,"cmd",cmd_zx->valuestring);
													char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
													int my_len = strlen(hw_request_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,hw_request_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													cJSON_Delete(hw_request_root);
													hw_request_root = NULL;
													free(hw_request_char);
													hw_request_char = NULL;
													free(my_send_char);
													my_send_char=NULL;
												}
												else
												{
													while(kt_while != NULL)
													{
														if(strcmp(kt_while->string,tem_lid->valuestring)==0)
														{
															cJSON *my_hw_lid = cJSON_GetObjectItem(kt_root,tem_lid->valuestring);
															cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,"code");
															str_len = strlen(my_code->valuestring)+56;
															uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
															memset(final_cmd,0,str_len/2);
															cmd_mix_kt(tem_lid->valuestring,cmd_zx->valuestring,my_code->valuestring,tem_mac->valuestring,tem_id->valuestring,str_len,final_cmd);
															find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
															free(final_cmd);
															final_cmd = NULL;
															usleep(200000);
															break;
														}
														kt_while = kt_while->next;
														if(kt_while==NULL && NET_FLAG)
														{
															cJSON *hw_request_root = cJSON_CreateObject();
															cJSON_AddStringToObject(hw_request_root,"co","orange");
															cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
															cJSON *hw_request_data = cJSON_CreateObject();
															cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
															cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
															cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
															cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
															cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
															cJSON *hw_request_cmd = cJSON_CreateObject();
															cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
															cJSON_AddStringToObject(hw_request_cmd,"cmd",cmd_zx->valuestring);
															char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
															int my_len = strlen(hw_request_char);
															char *my_send_char = (char *)malloc(my_len+2);
															memset(my_send_char,0,my_len+2);
															memcpy(my_send_char,hw_request_char,my_len);
															strcat(my_send_char,"\n\0");
															send(cd,my_send_char,my_len+1,0);
															cJSON_Delete(hw_request_root);
															hw_request_root = NULL;
															free(hw_request_char);
															hw_request_char = NULL;
															free(my_send_char);
															my_send_char=NULL;
														}
													}
												}
											}
										}
									}
									cJSON_Delete(code_id_root);
									code_id_root=NULL;
								}
							}
							else if(class==6)
							{
								cJSON *tem_lid = cJSON_GetObjectItem(data_arr_jx,"lid");
								int str_len = strlen(tem_lid->valuestring);
								if(str_len)
								{
									pthread_mutex_lock(&mutex_code);
									cJSON *code_id_root = cJSON_Parse(code_id);
									pthread_mutex_unlock(&mutex_code);
									if(code_id_root != NULL)
									{
										if(code_id_root->child != NULL)
										{
											cJSON *fkt_root = cJSON_GetObjectItem(code_id_root,"fkt");
											if(fkt_root != NULL)
											{
												cJSON *fkt_while = fkt_root->child;
												if(fkt_while==NULL && NET_FLAG)
												{
													cJSON *hw_request_root = cJSON_CreateObject();
													cJSON_AddStringToObject(hw_request_root,"co","orange");
													cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
													cJSON *hw_request_data = cJSON_CreateObject();
													cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
													cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
													cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
													cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
													cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
													cJSON *hw_request_cmd = cJSON_CreateObject();
													cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
													cJSON_AddStringToObject(hw_request_cmd,"key",cmd_zx->valuestring);
													char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
													int my_len = strlen(hw_request_char);
													char *my_send_char = (char *)malloc(my_len+2);
													memset(my_send_char,0,my_len+2);
													memcpy(my_send_char,hw_request_char,my_len);
													strcat(my_send_char,"\n\0");
													send(cd,my_send_char,my_len+1,0);
													cJSON_Delete(hw_request_root);
													hw_request_root = NULL;
													free(hw_request_char);
													hw_request_char = NULL;
													free(my_send_char);
													my_send_char=NULL;
												}
												else
												{
													while(fkt_while != NULL)
													{
														if(strcmp(fkt_while->string,tem_lid->valuestring)==0)//先找码库id
														{
															cJSON *my_hw_lid = cJSON_GetObjectItem(fkt_root,tem_lid->valuestring);
															cJSON *my_hw_lid_while = my_hw_lid->child;
															while(my_hw_lid_while != NULL)
															{
																if(strcmp(my_hw_lid_while->string,cmd_zx->valuestring)==0)//再找键值
																{
																	cJSON *my_code = cJSON_GetObjectItem(my_hw_lid,cmd_zx->valuestring);
																	int str_len = strlen(my_code->valuestring)+30;
																	uint8_t *final_cmd = (uint8_t *)malloc(str_len/2);
																	memset(final_cmd,0,str_len/2);
																	cmd_mix_fkt(my_code->valuestring,tem_mac->valuestring,str_len,final_cmd);
																	find_mac_and_send(tem_mac->valuestring,final_cmd,str_len/2);
																	free(final_cmd);
																	final_cmd=NULL;
																	break;
																}
																my_hw_lid_while = my_hw_lid_while->next;
																if(my_hw_lid_while == NULL && NET_FLAG)
																{
																	cJSON *hw_request_root = cJSON_CreateObject();
																	cJSON_AddStringToObject(hw_request_root,"co","orange");
																	cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
																	cJSON *hw_request_data = cJSON_CreateObject();
																	cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
																	cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
																	cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
																	cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
																	cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
																	cJSON *hw_request_cmd = cJSON_CreateObject();
																	cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
																	cJSON_AddStringToObject(hw_request_cmd,"key",cmd_zx->valuestring);
																	char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
																	int my_len = strlen(hw_request_char);
																	char *my_send_char = (char *)malloc(my_len+2);
																	memset(my_send_char,0,my_len+2);
																	memcpy(my_send_char,hw_request_char,my_len);
																	strcat(my_send_char,"\n\0");
																	send(cd,my_send_char,my_len+1,0);
																	cJSON_Delete(hw_request_root);
																	hw_request_root = NULL;
																	free(hw_request_char);
																	hw_request_char = NULL;
																	free(my_send_char);
																	my_send_char=NULL;
																}
															}
															break;
														}
														fkt_while = fkt_while->next;
														if(fkt_while==NULL && NET_FLAG)
														{
															cJSON *hw_request_root = cJSON_CreateObject();
															cJSON_AddStringToObject(hw_request_root,"co","orange");
															cJSON_AddStringToObject(hw_request_root,"api","get_hw_code");
															cJSON *hw_request_data = cJSON_CreateObject();
															cJSON_AddItemToObject(hw_request_root,"data",hw_request_data);
															cJSON_AddStringToObject(hw_request_data,"mac",tem_mac->valuestring);
															cJSON_AddStringToObject(hw_request_data,"lid",tem_lid->valuestring);
															cJSON_AddStringToObject(hw_request_data,"dev_id",tem_id->valuestring);
															cJSON_AddStringToObject(hw_request_data,"dev_type",tem_type->valuestring);
															cJSON *hw_request_cmd = cJSON_CreateObject();
															cJSON_AddItemToObject(hw_request_data,"dev_cmd",hw_request_cmd);
															cJSON_AddStringToObject(hw_request_cmd,"cmd",cmd_zx->valuestring);
															char *hw_request_char = cJSON_PrintUnformatted(hw_request_root);
															int my_len = strlen(hw_request_char);
															char *my_send_char = (char *)malloc(my_len+2);
															memset(my_send_char,0,my_len+2);
															memcpy(my_send_char,hw_request_char,my_len);
															strcat(my_send_char,"\n\0");
															send(cd,my_send_char,my_len+1,0);
															cJSON_Delete(hw_request_root);
															hw_request_root = NULL;
															free(hw_request_char);
															hw_request_char = NULL;
															free(my_send_char);
															my_send_char=NULL;
														}
													}
												}
											}
										}
									}
									cJSON_Delete(code_id_root);
									code_id_root=NULL;
								}
							}
							else if(class==10)
							{
								uint8_t *final_cmd = NULL;
								final_cmd = (uint8_t *)malloc(25);
								memset(final_cmd,0,25);
								cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,cmd_zx->valuestring,final_cmd);
								resend_zt(25,final_cmd,tem_id->valuestring,tem_type->valuestring);
								find_mac_and_send(tem_mac->valuestring,final_cmd,25);
								free(final_cmd);
								final_cmd = NULL;
							}
							else if(class==8)
							{
								uint8_t *final_cmd = NULL;
								final_cmd = (uint8_t *)malloc(20);
								memset(final_cmd,0,20);
								cmd_mix_scene(tem_mac->valuestring,tem_port->valuestring,cmd_zx->valuestring,final_cmd);
								resend_zt(20,final_cmd,tem_id->valuestring,tem_type->valuestring);
								find_mac_and_send(tem_mac->valuestring,final_cmd,20);
								free(final_cmd);
								final_cmd = NULL;
							}
							break;
						}
					}
				}
			}
			cJSON_Delete(dev_list_data);
			dev_list_data=NULL;
			return 0;
		}
		else if(strcmp(type_mx->valuestring,"2")==0)//背景音乐控制
		{
			if( NET_FLAG )
			{
				cJSON *dev_cmd_root = cJSON_GetObjectItem(mxid,"cmd");
				cJSON *dev_id_zx = cJSON_GetObjectItem(dev_cmd_root,"dev_id");
				cJSON *dev_type_zx = cJSON_GetObjectItem(dev_cmd_root,"dev_type");
				cJSON *cmd_root = cJSON_GetObjectItem(dev_cmd_root,"dev_cmd");
				cJSON *music_root = cJSON_CreateObject();
				cJSON_AddStringToObject(music_root,"co","orange");
				cJSON_AddStringToObject(music_root,"api","devCmd");
				cJSON *music_data = cJSON_CreateObject();
				cJSON_AddStringToObject(music_data,"dev_id",dev_id_zx->valuestring);
				cJSON_AddStringToObject(music_data,"dev_type",dev_type_zx->valuestring);
				cJSON *music_cmd =  cJSON_Duplicate(cmd_root,1);
				cJSON_AddItemToObject(music_data,"dev_cmd",music_cmd);
				cJSON_AddItemToObject(music_root,"data",music_data);
				char *send_char = cJSON_PrintUnformatted(music_root);
				int my_len = strlen(send_char);
				char *my_send_char = (char *)malloc(my_len+2);
				memset(my_send_char,0,my_len+2);
				memcpy(my_send_char,send_char,my_len);
				strcat(my_send_char,"\n\0");
				send(cd,my_send_char,my_len+1,0);
				free(send_char);
				send_char = NULL;
				free(my_send_char);
				my_send_char = NULL;
				cJSON_Delete(music_root);
				music_root = NULL;
			}
			return 0;
		}
		else if(strcmp(type_mx->valuestring,"3")==0)//切换安防控制
		{
			cJSON *dev_cmd_root = cJSON_GetObjectItem(mxid,"cmd");
			cJSON *model_af = cJSON_GetObjectItem(dev_cmd_root,"model");
			pthread_mutex_lock(&mutex_qj);
			if(strcmp(model_af->valuestring,qj_model))
			{
				memset(qj_model,0,5);
				memcpy(qj_model,model_af->valuestring,strlen(model_af->valuestring));
				int qj_model_fd = open("/root/qj_model.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
				write(qj_model_fd,qj_model,strlen(qj_model));
				fsync(qj_model_fd);
				close(qj_model_fd);
				pthread_mutex_unlock(&mutex_qj);
				int k;
				pthread_mutex_lock(&mutex_af);
				cJSON *secure_list = cJSON_Parse(secure_set_list);//遍历af列表
				pthread_mutex_unlock(&mutex_af);
				if(secure_list != NULL)
				{
					if(secure_list->child != NULL)
					{
						cJSON *my_model_data = cJSON_GetObjectItem(secure_list,"data");
						cJSON *my_model = cJSON_GetObjectItem(my_model_data,"model_set_list");
						cJSON *switch_model = cJSON_GetObjectItem(my_model,model_af->valuestring);
						int m_l = cJSON_GetArraySize(switch_model);
						cJSON *secure_arr_jx = NULL;
						cJSON *secure_id = NULL;
						cJSON *secure_type = NULL;
						cJSON *secure_state = NULL;
						for(k=0;k<m_l;k++)
						{
							secure_arr_jx = cJSON_GetArrayItem(switch_model,k);
							secure_id = cJSON_GetObjectItem(secure_arr_jx,"dev_id");
							secure_type = cJSON_GetObjectItem(secure_arr_jx,"dev_type");
							secure_state = cJSON_GetObjectItem(secure_arr_jx,"dev_state");
							if(NET_FLAG)
							{
								cJSON *secure_root = cJSON_CreateObject();
								cJSON *secure_root_data = cJSON_CreateObject();
								cJSON *secure_root_state = cJSON_CreateObject();
								cJSON_AddNumberToObject(secure_root,"retcode",0);
								cJSON_AddStringToObject(secure_root,"message","success");
								cJSON_AddStringToObject(secure_root,"api","secuStateRes");
								cJSON_AddItemToObject(secure_root,"data",secure_root_data);
								cJSON_AddItemToObject(secure_root_data,"dev_state",secure_root_state);
								cJSON_AddStringToObject(secure_root_data,"dev_id",secure_id->valuestring);
								cJSON_AddStringToObject(secure_root_data,"dev_type",secure_type->valuestring);
								if(strcmp(secure_type->valuestring,"020101")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else if(strcmp(secure_type->valuestring,"020102")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else if(strcmp(secure_type->valuestring,"020103")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else if(strcmp(secure_type->valuestring,"020104")==0)
									cJSON_AddStringToObject(secure_root_state,"dev_state","01");
								else
									cJSON_AddStringToObject(secure_root_state,"dev_state",secure_state->valuestring);
								char *secure_root_char = cJSON_PrintUnformatted(secure_root);
								int my_len = strlen(secure_root_char);
								char *my_send_char = (char *)malloc(my_len+2);
								memset(my_send_char,0,my_len+2);
								memcpy(my_send_char,secure_root_char,my_len);
								strcat(my_send_char,"\n\0");
								send(cd,my_send_char,my_len+1,0);
								free(secure_root_char);
								secure_root_char=NULL;
								free(my_send_char);
								my_send_char=NULL;
								cJSON_Delete(secure_root);
								secure_root=NULL;
							}
							pthread_mutex_lock(&mutex_zl);
							cJSON *device_state_list_data = cJSON_Parse(device_state_list);//遍历设备状态列表
							if(device_state_list_data != NULL)
							{
								if(device_state_list_data->child != NULL)
								{
									cJSON *my_device_state_list_data = cJSON_GetObjectItem(device_state_list_data,"data");
									cJSON *while_device_state_list_data = my_device_state_list_data->child;
									if(while_device_state_list_data==NULL)
									{
										cJSON *state_root = cJSON_CreateObject();
										cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
										cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
										char *state_char = cJSON_PrintUnformatted(device_state_list_data);
										memset(device_state_list,0,BUFFSIZE);
										memcpy(device_state_list,state_char,strlen(state_char));
										int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
										write(state_fd,state_char,strlen(state_char));
										fsync(state_fd);
										close(state_fd);
										free(state_char);
										state_char=NULL;
									}
									else
									{
										while(while_device_state_list_data != NULL)
										{
											if(strcmp(while_device_state_list_data->string,secure_id->valuestring)==0)
											{
												cJSON *dev_state_cjson = cJSON_GetObjectItem(my_device_state_list_data,secure_id->valuestring);
												num = cJSON_GetArraySize(dev_state_cjson);
												cJSON *arr_for=NULL;
												flag_have=0;
												int m;
												for(m=0;m<num;m++)
												{
													arr_for = cJSON_GetArrayItem(dev_state_cjson,m);
													if(!strcmp(arr_for->string,"dev_state"))
													{
														flag_have=1;
														break;
													}
												}
												if(flag_have==1)
												cJSON_DeleteItemFromObject(dev_state_cjson,"dev_state");
												cJSON_AddStringToObject(dev_state_cjson,"dev_state",secure_state->valuestring);
												char *state_char = cJSON_PrintUnformatted(device_state_list_data);
												memset(device_state_list,0,BUFFSIZE);
												memcpy(device_state_list,state_char,strlen(state_char));
												int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
												write(state_fd,state_char,strlen(state_char));
												fsync(state_fd);
												close(state_fd);
												free(state_char);
												state_char=NULL;
												break;
											}
											while_device_state_list_data = while_device_state_list_data->next;
											if(while_device_state_list_data==NULL)
											{
												cJSON *state_root = cJSON_CreateObject();
												cJSON_AddItemToObject(my_device_state_list_data,secure_id->valuestring,state_root);
												cJSON_AddStringToObject(state_root,"dev_state",secure_state->valuestring);
												char *state_char = cJSON_PrintUnformatted(device_state_list_data);
												memset(device_state_list,0,BUFFSIZE);
												memcpy(device_state_list,state_char,strlen(state_char));
												int state_fd = open("/root/device_state_list.txt",O_RDWR|O_CREAT|O_TRUNC,0777);
												write(state_fd,state_char,strlen(state_char));
												fsync(state_fd);
												close(state_fd);
												free(state_char);
												state_char=NULL;
											}
										}
									}
								}
							}
							pthread_mutex_unlock(&mutex_zl);
							cJSON_Delete(device_state_list_data);
							device_state_list_data=NULL;
						}
						if(NET_FLAG)
						{
							cJSON *secure_model_now = cJSON_CreateObject();
							cJSON *secure_model_now_data = cJSON_CreateObject();
							cJSON_AddNumberToObject(secure_model_now,"retcode",0);
							cJSON_AddStringToObject(secure_model_now,"message","success");
							cJSON_AddStringToObject(secure_model_now,"api","secuModelRes");
							cJSON_AddItemToObject(secure_model_now,"data",secure_model_now_data);
							cJSON_AddStringToObject(secure_model_now_data,"model",model_af->valuestring);
							char *secure_model_now_char = cJSON_PrintUnformatted(secure_model_now);
							int my_len = strlen(secure_model_now_char);
							char *my_send_char = (char *)malloc(my_len+2);
							memset(my_send_char,0,my_len+2);
							memcpy(my_send_char,secure_model_now_char,my_len);
							strcat(my_send_char,"\n\0");
							send(cd,my_send_char,my_len+1,0);
							free(secure_model_now_char);
							secure_model_now_char=NULL;
							free(my_send_char);
							my_send_char=NULL;
							cJSON_Delete(secure_model_now);
							secure_model_now=NULL;
						}
					}
				}
				cJSON_Delete(secure_list);
				secure_list=NULL;
			}
			else
				pthread_mutex_unlock(&mutex_qj);
			return 0;
		}
		else if(strcmp(type_mx->valuestring,"4")==0)//推送消息
		{
			cJSON *dev_cmd_root = cJSON_GetObjectItem(mxid,"cmd");
			cJSON *content_root = cJSON_GetObjectItem(dev_cmd_root,"content");
			if(NET_FLAG)
			{
				cJSON *root_msg = cJSON_CreateObject();
				cJSON *msg_data = cJSON_CreateObject();
				cJSON_AddItemToObject(root_msg,"data",msg_data);
				cJSON_AddStringToObject(root_msg,"co","orange");
				cJSON_AddStringToObject(root_msg,"api","gw_up_msg");
				cJSON_AddStringToObject(msg_data,"id",strid);
				cJSON_AddStringToObject(msg_data,"msg_type","0205");
				cJSON_AddStringToObject(msg_data,"content",content_root->valuestring);
				char *msg_char = cJSON_PrintUnformatted(root_msg);
				int my_len = strlen(msg_char);
				char *my_send_char = (char *)malloc(my_len+2);
				memset(my_send_char,0,my_len+2);
				memcpy(my_send_char,msg_char,my_len);
				strcat(my_send_char,"\n\0");
				send(cd,my_send_char,my_len+1,0);
				free(msg_char);
				msg_char=NULL; 
				free(my_send_char);
				my_send_char=NULL;
				cJSON_Delete(root_msg);
				root_msg=NULL;
			}
			return 0;
		}
		else if(strcmp(type_mx->valuestring,"5")==0)//退出
		{
			return 1;
		}
	}
	return 6;
}

void get_signal_u(char *u_data_str)
{
	int i;
	char *data_str = NULL;
	data_str= (char*)malloc(5);//signal
	memset(data_str,0,5);
	memcpy(data_str,u_data_str+30,4);
	data_str[4]='\0';
	char *mac_str = NULL;
	mac_str = (char*)malloc(17);//mac地址
	memset(mac_str,0,17);
	memcpy(mac_str,u_data_str+4,16);
	mac_str[16]='\0';
	pthread_mutex_lock(&mutex_sl);
	cJSON *dev_list_data = cJSON_Parse(device_list);//遍历设备列表
	pthread_mutex_unlock(&mutex_sl);
	if(dev_list_data != NULL)
	{
		if(dev_list_data->child != NULL)
		{
			cJSON *my_dev_list_data = cJSON_GetObjectItem(dev_list_data,"data");
			cJSON *my_dev_list_list = cJSON_GetObjectItem(my_dev_list_data,"dev_list");
			int	data_l =  cJSON_GetArraySize(my_dev_list_list);
			cJSON *data_arr_jx = NULL;
			cJSON *tem_mac = NULL;
			for(i=0;i<data_l;i++)
			{
				data_arr_jx = cJSON_GetArrayItem(my_dev_list_list,i);
				tem_mac = cJSON_GetObjectItem(data_arr_jx,"mac");
				if(mac_mac(mac_str,tem_mac->valuestring))
				{
					memcpy(mac_str,tem_mac->valuestring,16);
					break;
				}
			}
		}
	}
	cJSON *root_u = cJSON_CreateObject();//创建项目
	cJSON *data_object = cJSON_CreateObject();
	cJSON_AddNumberToObject(root_u,"retcode",0);
	cJSON_AddStringToObject(root_u,"message","success");
	cJSON_AddStringToObject(root_u,"api","up_device_signal");
	cJSON_AddItemToObject(root_u,"data",data_object);
	cJSON_AddStringToObject(data_object,"mac",mac_str);
	cJSON_AddStringToObject(data_object,"signal",data_str);
	char *send_char = cJSON_PrintUnformatted(root_u);
	int my_len = strlen(send_char);
	char *my_send_char = (char *)malloc(my_len+2);
	memset(my_send_char,0,my_len+2);
	memcpy(my_send_char,send_char,my_len);
	strcat(my_send_char,"\n\0");
	send(cd,my_send_char,my_len+1,0);
	free(data_str);
	data_str=NULL;
	free(mac_str);
	mac_str=NULL;
	free(send_char);
	send_char=NULL;
	free(my_send_char);
	my_send_char=NULL;
	cJSON_Delete(root_u);
	root_u=NULL;
	cJSON_Delete(dev_list_data);
	dev_list_data=NULL;
}



