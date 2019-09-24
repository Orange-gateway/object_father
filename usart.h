#ifndef _USART_H_
#define _USART_H_
#include "stdint.h"
/*/串口打开函数/*/
int usart_open(int fd,char* port);

void usart_close(int fd);

int usart_init(int fd,int baudrate,int flew_ctrl,int databits,int check,int stopbits);

int usart_send(int fd, uint8_t *s_buff,int data_len);

#endif

