#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdint.h>
#include <pthread.h>
#define BUFFSIZE 81920
 int cd;//socket 描述符
 int down_cd;
 int fd;//串口描述符
 int NET_FLAG; 
 int device_flag;
 int down_gw_flag;
 time_t first;//接收更新时间
 time_t second;//心跳更新时间
 time_t net_record_time;//入网记录时间
 pthread_t id_client;//联网线程id，全局变量，拿来心跳kill重连
 pthread_mutex_t mutex_v;//全开全关下发锁
 pthread_mutex_t mutex_sl;//遍历设备列表锁
 pthread_mutex_t mutex_zl;//遍历设备状态列表锁
 pthread_mutex_t mutex_bl;//遍历多联绑定列表锁
 pthread_mutex_t mutex_qj;//安防模式文件锁
 pthread_mutex_t mutex_af;//安防列表文件锁
 pthread_mutex_t mutex_scene;//情景文件
 pthread_mutex_t mutex_time;//定时器列表
 pthread_mutex_t mutex_voice;//离线语音锁
 pthread_mutex_t mutex_code;//码库锁
 pthread_mutex_t mutex_down_file;//下载文件锁
 pthread_mutex_t mutex_room;//房间锁
 pthread_mutex_t mutex_gw_dev_mac;//主、子网关绑定锁
 pthread_cond_t cond;
 pthread_mutex_t mutex_waite;//信道等待锁
 pthread_mutex_t mutex_sign_mac;//标记mac锁
 typedef struct resend //重发结构体
 {
 	time_t now_time;//登记现在的时间
 	int now_times;//登记现在的次数
 	char dev_id[20];
 	char dev_type[10];
 	uint8_t cmd[64];//命令
 	struct resend *next;
 }RSD;
 RSD *resend_head,*resend_z,*resend_d;
 typedef struct human //human_body结构体
 {
	time_t now_time;//登记现在的时间
 	char mac[17];
 	char port[3];
 	int flag;
 	struct human *next;
 }HB;
 HB *human_head,*human_z,*human_d;
 typedef struct net_fd_record //子网关网络描述符
 {
 	int fd_net;
 	int flag;
 	char mac[13];
 	struct net_fd_record *next;
 }NET_F;
 NET_F *net_head,*net_z,*net_d;
 typedef struct sign_mac //主网关标记设备mac结构体
 {
 	uint8_t the_mac[8];
 	int flag_have;
 	struct sign_mac *next;
 }SIG_MAC;
 SIG_MAC *sign_mac_head,*sign_mac_z,*sign_mac_d;
 char str_from_server[819200];//中间转换缓冲区
 char scene_list[BUFFSIZE];//情景列表缓存区
 char scene_detail[819200];//情景明细缓存区
 char device_list[819200];//设备列表缓存区
 char timer_list[BUFFSIZE];//定时器列表缓存区
 char secure_set_list[BUFFSIZE];//安放设置列表缓存区
 char multi_bind[BUFFSIZE];//多联绑定缓存区
 char voice_list[BUFFSIZE];//离线语音列表缓存区
 char device_state_list[BUFFSIZE];//设备状态缓存区
 char gw_dev_mac_list[10240];//主、子网关设备绑定列表
 char code_id[BUFFSIZE];//码库id缓存区
 char gw_sn[100];//sn缓存区
 char room_list[10240];//房间列表缓冲区
 int identify_flag;//身份验证成功标志
 int go_net_flag;//允许入网标志
 int onekey_or_study_flag;
 char qj_model[5];
 char gw_version[9];
 
 char zigbee_channel[3];
 char zigbee_id[5];
 char my_gw_mac[13];
#endif
