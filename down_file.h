#ifndef _DOWN_FILE_H_
#define _DOWN_FILE_H_
#include "cjson.h"
int url_parser(char *url, char *hostname, char *urlfile, int *port);
int tcp_client(char *hostname,int port);
int send_http_request(int sockfd,char *hostname,int port,char *filename);
int recv_http_request(int sockfd);
void down_file(cJSON *root);
#endif
