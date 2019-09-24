#ifndef _HANZI_H_
#define _HANZI_H_
#include "include.h"
extern const uint16_t GB2312_Unicode[][2];
char judge(uint16_t tmp);
char* str_judge(char *str);
char* tiqu(char *str);
int judge_number(char *voice_str);
int judge_number_kt(char *voice_str);
#endif


