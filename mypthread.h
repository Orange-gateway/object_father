#ifndef _MYPTHREAD_H_
#define _MYPTHREAD_H_
#include "stdint.h"
#include "main.h"
/*线程回收的链函数*/
void fun(void *p);
/*线程发送至串口函数*/
void pthread_u_send(char *str);
/*线程发送至服务器函数*/
void pthread_v_send(uint8_t *u_data);
/*线程串口接收函数*/
void pthread_usart_receive(void);
/*线程接收服务器函数*/
void pthread_client_receive(void);
/*心跳机制*/
void heart_jump(void);
void reconnect(int num);
void re_send_success_or_failed(RSD *p,char *dev_id,char *dev_type,char *data_str,int ret_num,char *message);
void re_send(void);
void resend_zt(int len,uint8_t *cmd,char *dev_id,char *dev_type);
void my_timer(void);
void up_resend(uint8_t *data);
void get_status(char *gw_mac);
void human_zt(char *mac,char *port);
void human_check(void);
void gateway_send_heart_jump(void);
#endif
