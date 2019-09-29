#ifndef _DEVICE_CONTROL_H_
#define _DEVICE_CONTROL_H_
#include "cjson.h"
#include <stdint.h>

void cmd_mix(char *mac,char *port,char *cmd,uint8_t *final_cmd);
void cmd_mix_47(char *mac,char *port,char *cmd,uint8_t *final_cmd);
void cmd_mix_scene(char *mac,char *port,char *cmd,uint8_t *final_cmd);
void cmd_mix_sensor(char *mac,char *port,char *cmd,uint8_t *final_cmd);
void cmd_mix_get_stastus1(char *mac,char *port,char *cmd,uint8_t *final_cmd);
void cmd_mix_get_signal(char *mac,char *cmd,uint8_t *final_cmd);//获取信号质量合成指令
void cmd_delete_mix(char *mac,char *cmd,uint8_t *final_cmd);
void cmd_request_describ_mix(char *mac,char *cmd,uint8_t *final_cmd);
void cmd_mix_kt(char *lid,char *cmd,char *kt_code,char *mac,char *id,int len,uint8_t *final_cmd);//发送至串口合成命令(kt)
void cmd_mix_fkt(char *fkt_code,char *mac,int len,uint8_t *final_cmd);//发送至串口合成命令(fkt)
void cmd_mix_lock(char *mac,char *port,uint8_t *final_cmd);//发送至串口合成命令(开锁控制指令)
void cmd_hw_study_or_complish(char *mac,uint8_t *final_cmd,int flag);//发送至串口红外学习命令合成
void dev_lock_con(int i,int u_data_len,uint8_t *u_data,char *u_data_str);
void dev_com_con(cJSON *root);
void dev_room_con(cJSON *root);
void dev_sec_con(cJSON *root);
void voice_open(cJSON *data_arr_jx,char *Voice_CMD);
void voice_close(cJSON *data_arr_jx);
void voice_judge(cJSON *data_arr_jx,char *Voice_CMD);
void voice_con(cJSON *root);
void switchSecuModel(cJSON *root);
void update_secure(void);
void hw_study_or_complish_con(cJSON *root,int flag);
void dev_hw_con(cJSON *root);
void up_hw_code(cJSON *root);
void get_hw_code_ser(cJSON *root);
void get_new_lid_ver(cJSON *root);
void down_scene_list(char *str);
void down_scene_mx(char *str);
void down_dev_list(char *str);
void down_dev_state_list(char *str);
void down_bind_list(char *str);
void down_timer_list(char *str);
void down_sec_list(char *str);
void down_voice_list(char *str);
void down_room_list(char *str);
void get_identify(cJSON *root);
void let_go_to_net(cJSON *root);
void voice_com_con_u(int i,uint8_t *u_data,char *u_data_str);
void dev_com_con_u(int i,int u_data_len,uint8_t *u_data,char *u_data_str);
void dev_com_kt_con(int i,int u_data_len,uint8_t *u_data,char *u_data_str);
void hw_study_or_one_key(int u_data_len,uint8_t *u_data,char *u_data_str);
void dev_online(int i,int u_data_len,char *u_data_str);
void dev_status_u(uint8_t *u_data,int i,int u_data_len,char *u_data_str);
void dev_descrip_u(int i,int u_data_len,char *u_data_str);
void dev_sensor_81(int i,int u_data_len,char *u_data_str);
void dev_into_net(uint8_t *u_data);
void dev_sensor_82(uint8_t *u_data,int i,int u_data_len,char *u_data_str);
void up_dev_describe(cJSON *root);
void up_dev_des(void);//随着列表更新而更新状态列表
void run_the_scene(char *str_id);
void run_scene(char *sce_id);
void run_scene_u_triger(char *dev_id,char *status);
void run_scene_u_triger_sensor(char *dev_id,char *status);
void power_65(uint8_t *u_data,int i,int u_data_len,char *u_data_str);
int scene_time_judge(char *my_time,cJSON *mxid,char *strid);
int scene_time_NULL(cJSON *mxid,char *strid);
void get_signal(void);
void get_signal_u(char *u_data_str);
void update_state(void);
void gw_bind_self_mac(char *data_str);//绑定主网关mac
void gw_mac_bind_dev_mac(char *u_data_str);//绑定子网关mac
void delete_gw_bind_mac(char *del_mac);//删除绑定mac

#endif
