/*
 * @Description: log header
 * @version: 0.1.0
 * @Author: Panda-Young
 * @Date: 2022-04-09 03:28:51
 * @Copyright (c) 2022 by Panda-Young, All Rights Reserved.
 */

#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>
#include <stdint.h>

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

void bless_you();

#endif
