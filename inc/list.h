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

extern uint8_t MSG_DBG_ENABLE;

#define printf_grey(fmt, args...)   printf("\e[1;30m" fmt "\e[0m", ## args)
#define MSG_INFO(fmt, args...) \
do { \
    if (MSG_DBG_ENABLE == 3) { \
        printf("%s: L%d: %s():\t", __FILE__, __LINE__, __FUNCTION__); \
        printf("\e[1;32m" fmt "\e[0m", ## args); \
    } else { \
        printf("\e[1;32m" fmt "\e[0m", ## args); \
    } \
} while (0)
#define MSG_PROMPT(fmt, args...) \
do { \
    if (MSG_DBG_ENABLE == 3) { \
        printf("%s: L%d: %s():\t", __FILE__, __LINE__, __FUNCTION__); \
        printf("\e[1;33m" fmt "\e[0m", ## args); \
    } else { \
        printf("\e[1;33m" fmt "\e[0m", ## args); \
    } \
} while (0)
#define MSG_DBG(fmt, args...) \
do { \
    if (MSG_DBG_ENABLE == 1) { \
        printf("\e[1;34m" fmt "\e[0m", ## args); \
    } else if (MSG_DBG_ENABLE == 2 || MSG_DBG_ENABLE == 3) { \
        printf("%s: L%d: %s():\t", __FILE__, __LINE__, __FUNCTION__); \
        printf("\e[1;34m" fmt "\e[0m", ## args); \
    } \
} while (0)
#define MSG_ERR(fmt, args...) \
do { \
    if (MSG_DBG_ENABLE == 3) { \
        printf("%s: L%d: %s():\t", __FILE__, __LINE__, __FUNCTION__); \
        printf("\e[1;31m" fmt "\e[0m", ## args); \
    } else { \
        printf("\e[1;31m" fmt "\e[0m", ## args); \
    } \
} while (0)
#define MSG_FATAL(fmt, args...) \
do { \
    if (MSG_DBG_ENABLE == 3) { \
        printf("%s: L%d: %s():\t", __FILE__, __LINE__, __FUNCTION__); \
        printf("\e[1;35m" fmt "\e[0m", ## args); \
    } else { \
        printf("\e[1;35m" fmt "\e[0m", ## args); \
    } \
} while (0)
#define MSG_DATA(fmt, args...) \
do { \
    if (MSG_DBG_ENABLE == 3) { \
        printf("%s: L%d: %s():\t", __FILE__, __LINE__, __FUNCTION__); \
        printf("\e[1;36m" fmt "\e[0m", ## args); \
    } else { \
        printf("\e[1;36m" fmt "\e[0m", ## args); \
    } \
} while (0)
#define printf_white(fmt, args...)  printf("\e[1;37m" fmt "\e[0m", ## args)

#define FILE_NAME       "stu_info.txt"
#define STU_INFO_LABEL  "Name\t\tID\t\tChinese\t\tMath\t\tEnglish\t\tAge\t\tSex"

#define ANOTHER_WAY     0
#define NUM_ELEMENT     7
#define TRY_TIMES       3
#define ASCII_NEW_LINE  10
#define ASCII_ENTER     13
#define ASCII_CTRL_C    3

#define TRUE            true
#define FALSE           false
#define EOK             0
#define EINPUT         -1
#define EALLOC         -2
#define EFOPEN         -3
#define EPASSWD        -4
#define EMODE          -5

typedef enum {
    LOG_LEVEL_GREY = 0,   // grey
    LOG_LEVEL_INFO,       // green
    LOG_LEVEL_PROMPT,     // yellow
    LOG_LEVEL_DEBUG,      // blue
    LOG_LEVEL_ERROR,      // red
    LOG_LEVEL_FATAL,      // purple
    LOG_LEVEL_DATA,       // light blue
    LOG_LEVEL_WHITE,      // white
    LOG_LEVEL_MAX
}log_level_t;

typedef struct STU_INFO {
    int8_t      name[20];
    uint32_t    stu_id;
    uint16_t    score[3];
    uint16_t    stu_age;
    bool        stu_sex;
}stu_info_t;

typedef struct NODE {
    stu_info_t      data;
    struct NODE     *next;
}node_t, *nodeptr_t;

typedef enum ENCRYPT_METHOD {
    BitwiseXOR = 1,
    Arithmetic,
}encrypt_method_t;

int32_t verify_passwd();
int32_t set_secure_password();

void current_node_info(nodeptr_t current, log_level_t level);

nodeptr_t add_endnode(nodeptr_t end);
nodeptr_t add_beginnode(nodeptr_t head);
nodeptr_t add_randomnode(nodeptr_t head, nodeptr_t current);
nodeptr_t reverse_list(nodeptr_t head);
nodeptr_t bubble_sort(nodeptr_t head);
nodeptr_t quick_sort(nodeptr_t head, nodeptr_t end);

int32_t save_to_file(nodeptr_t tmp, bool mode);
int32_t create_file(nodeptr_t head, uint8_t *confirm_code);
int32_t read_file(nodeptr_t head);
int32_t view_info(nodeptr_t head, uint8_t *confirm_code);
int32_t add_info(nodeptr_t head, uint8_t *confirm_code);
int32_t modify_info(nodeptr_t head);
int32_t delete_info(nodeptr_t head);
int32_t find_info(nodeptr_t head, uint8_t *confirm_code);
int32_t sort_info(nodeptr_t head);

#endif
