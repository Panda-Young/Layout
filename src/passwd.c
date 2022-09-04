/*
 * @Description: Secure password input and verification.
 * @version: 0.1.0
 * @Author: Panda-Young
 * @Date: 2022-04-10 01:51:03
 * Copyright (c) 2022 by Panda-Young, All Rights Reserved.
 */

#include <string.h>
#include <conio.h>
#include "list.h"

/**
 * @description: Hide plaintext input
 * @param {char} *passwd
 * @return {*}
 */
void HiddenInput(char *passwd)
{
    char ch = 0;
    int len = 0;
    while(ch = getch())
    {
        if(len >= 20 || ch == 13) { // 密码输入过长或enter结束输入
            break;
        }

        if(ch != '\b') { // 回车删除字符
            if(!((ch<='Z'&&ch>='A')||(ch<='z'&&ch>='a')||(ch<='9'&&ch>='0'))) {
                continue; // 密码仅由大小写字母和数字组成
            }
            passwd[len] = ch;
            MSG_INFO("*");
            len++;
        } else {
            MSG_INFO("\b \b");
            len--;
        }
    }
    passwd[len] = '\0';
    MSG_INFO("\n");
}

/**
 * @description: Verify password
 * @return {*}
 */
int verify_passwd()
{
    char passwd[20];
    int try_num = 0;
    MSG_PROMPT("Please input password. %d/%d\n", try_num + 1, TRY_TIMES);
    while (try_num != TRY_TIMES) {
        try_num++;
        HiddenInput(passwd);
        if (strcmp(passwd, "hello") == 0) {
            return EOK;
        }
        if (try_num != TRY_TIMES) {
            MSG_ERR("Mismatch! Please reinput password. %d/%d\n", try_num + 1, TRY_TIMES);
        } else {
            MSG_ERR("Mismatch! The number of attempts exceeds the limit. Exit!\n");
        }
    }
    return EPASSWD;
}
