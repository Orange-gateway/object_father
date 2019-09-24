#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <sys/select.h>
/*  tcp初始化函数   */
int client_init(void);
void tcp_server_init(void);
void net_fd_zt(int net_fd,char *mac,fd_set* inset);
void up_net_fd(int net_fd);
void getpeermac( int sockfd, char *buf );
void send_to_son_hart_jump(int send_net);
int find_net_fd_repeat(int num_fd);
#endif
