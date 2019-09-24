/* JSON_checker.h */
#ifndef _JSON_CHECKER_H_
#define _JSON_CHECKER_H_
typedef struct JSON_checker_struct
{
    int state;
    int depth;
    int top;
    int* stack;
} *JSON_checker;


JSON_checker new_JSON_checker(int depth);
int  JSON_checker_char(JSON_checker jc, int next_char);
int  JSON_checker_done(JSON_checker jc);

/*
    Read input string and check.

	if not json string return -1, else return 0.

    jc will contain a JSON_checker with a maximum depth of 20.
*/
int json_checker(const char *json_str);

#endif

