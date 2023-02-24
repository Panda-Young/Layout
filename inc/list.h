/*
 * @Description: Header file
 * @version: 0.1.0
 * @Author: Panda-Young
 * @Date: 2022-04-09 03:28:51
 * @Copyright (c) 2022 by Panda-Young, All Rights Reserved.
 */

#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <conio.h>

#define _DBG_MSG_ENABLE 0
#define printf_grey(fmt, args...)   printf("\e[1;30m" fmt "\e[0m", ## args) // grey
#define MSG_INFO(fmt, args...)      printf("\e[1;32m" fmt "\e[0m", ## args) // green
#define MSG_PROMPT(fmt, args...)    printf("\e[1;33m" fmt "\e[0m", ## args) // yellow
#if _DBG_MSG_ENABLE
#define MSG_DBG(fmt, args...)       printf("\e[1;34m" fmt "\e[0m", ## args) // blue
#else
#define MSG_DBG(fmt, args...)
#endif
#define MSG_ERR(fmt, args...)       printf("\e[1;31m" fmt "\e[0m", ## args) // red
#define MSG_FATAL(fmt, args...)     printf("\e[1;35m" fmt "\e[0m", ## args) // purple
#define MSG_DATA(fmt, args...)      printf("\e[1;36m" fmt "\e[0m", ## args) // light blue
#define printf_white(fmt, args...)  printf("\e[1;37m" fmt "\e[0m", ## args) // white

#define FILE_NAME       "stu_info.txt"

#define ANOTHER_WAY     0
#define DEBUG_SORT_MSG  1
#define DEBUG_PTR_MSG   0
#define NUM_ELEMENT     7
#define TRY_TIMES       3
#define ASCII_NEW_LINE  10
#define ASCII_ENTER     13

#define TRUE            1
#define FALSE           0
#define EOK             0
#define EINPUT         -1
#define EALLOC         -2
#define EFOPEN         -3
#define EPASSWD        -4
#define EMODE          -5

typedef struct {
    char            name[20];
    unsigned int    stu_id;
    unsigned short  score[3];
    unsigned short  stu_age;
    bool            stu_sex;
}stu_info_t;

typedef struct node {
    stu_info_t      data;
    struct node     *next;
}node_t, *nodeptr_t;

int verify_passwd();
int set_secure_password();

nodeptr_t add_endnode(nodeptr_t end);
nodeptr_t add_beginnode(nodeptr_t head);
nodeptr_t add_randomnode(nodeptr_t head, nodeptr_t current);
nodeptr_t reverse_list(nodeptr_t head);
nodeptr_t bubble_sort(nodeptr_t head);
nodeptr_t quick_sort(nodeptr_t head, nodeptr_t end);

int save_to_file(nodeptr_t tmp, bool mode);
int create_file(nodeptr_t head, unsigned char *confirm_code);
int read_file(nodeptr_t head);
int view_info(nodeptr_t head, unsigned char *confirm_code);
int add_info(nodeptr_t head, unsigned char *confirm_code);
int modify_info(nodeptr_t head);
int delete_info(nodeptr_t head);
int find_info(nodeptr_t head, unsigned char *confirm_code);
int sort_info(nodeptr_t head);

#endif
