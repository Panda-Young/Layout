/*
 * @Description: Secure password input and verification.
 * @version: 0.1.0
 * @Author: Panda-Young
 * @Date: 2022-04-10 01:51:03
 * Copyright (c) 2022 by Panda-Young, All Rights Reserved.
 */

#include "list.h"

#define MAX_INPUT_LEN 30
#define MAX_PW_LEN 15
#define MIN_PW_LEN 8
#define KEY_FILE "key"

extern bool msg_dbg_enable;

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
        if (ch == 13) { // end with press [Enter]
            break;
        }
        if(ch != '\b') { // backspace
            if(!((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || (ch <= '9' && ch >= '0'))) {
                continue;
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
    MSG_DBG(msg_dbg_enable, "HiddenInput:%s\n", passwd);
}

/**
 * @description: encrypt password string to key file.
 * @param {char} *key_file
 * @param {char} *pw_str
 * @return {int}
 */
int encrypt(char *key_file, char *pw_str, encrypt_method_t MODE)
{
    int8_t encrypt_str[MAX_INPUT_LEN] = {0};
    switch (MODE)
    {
        case BitwiseXOR: {
            for (int i = 0; i < strlen(pw_str); i++) {
                encrypt_str[i] = pw_str[i] ^ 'F';
            }
            break;
        }
        case Arithmetic: {
            break;
        }
        default: {
            break;
        }
    }

    MSG_DBG(msg_dbg_enable, "after encrypt str:%s\n", encrypt_str);

    FILE *KEY = fopen(key_file, "w+");
    if (KEY == NULL) {
        MSG_ERR("open key file error\n");
        return EFOPEN;
    }
    fwrite(encrypt_str, strlen(encrypt_str), 1, KEY);
    fclose(KEY);
    return EOK;
}

/**
 * @description: decrypt key file to password string.
 * @param {char} *key_file
 * @param {char} *pw_str
 * @return {char *}
 */
int decrypt(char *key_file, char *pw_str, encrypt_method_t MODE)
{
    int8_t decrypt_str[MAX_INPUT_LEN] = {0};
    FILE *KEY = fopen(key_file, "r");
    if (KEY == NULL) {
        MSG_ERR("open key file error\n");
        return EFOPEN;
    }
    fseek(KEY, 0, SEEK_END);
    int pw_len = ftell(KEY);
    fseek(KEY, 0, SEEK_SET);
    fread(decrypt_str, pw_len, 1, KEY);
    fclose(KEY);
    KEY = NULL;
    MSG_DBG(msg_dbg_enable, "before decrypt str:%s\n", decrypt_str);

    switch (MODE)
    {
        case BitwiseXOR: {
            for (int i = 0; i < strlen(decrypt_str); i++) {
                pw_str[i] = decrypt_str[i] ^ 'F';
            }
            break;
        }
        case Arithmetic: {
            break;
        }
        default: {
            break;
        }
    }

    MSG_DBG(msg_dbg_enable, "after decrypt str:%s\n", pw_str);

    return EOK;
}

/**
 * @description: Verify password
 * @return {int}
 */
int verify_passwd()
{
    if (access(KEY_FILE, F_OK) != 0) {
        MSG_ERR("There is no saved password.\n");
        set_secure_password();
        return EOK;
    }

    char passwd[MAX_INPUT_LEN] = {0}, pw_str[MAX_INPUT_LEN] = {0};
    if (decrypt(KEY_FILE, pw_str, BitwiseXOR) != EOK) {
        MSG_ERR("Can't get saved password.\n");
        return EFOPEN;
    }
    int try_num = 0;
    MSG_PROMPT("Please input password. %d/%d\n", try_num + 1, TRY_TIMES);
    while (try_num != TRY_TIMES) {
        try_num++;
        HiddenInput(passwd);
        if (strcmp(passwd, pw_str) == 0) {
            return EOK;
        }
        if (try_num != TRY_TIMES) {
            MSG_ERR("Mismatch! Please reinput password. %d/%d\n", try_num + 1, TRY_TIMES);
        } else {
            MSG_ERR("3 incorrect password attempts. Exit!\n");
        }
    }
    return EPASSWD;
}

/**
 * @description: Set an secure password of 8 to 15 characters, including uppercase and lowercase letters and numbers.
 * @return {*}
 */
int set_secure_password()
{
    int8_t pw_str[MAX_INPUT_LEN] = {0}, pw_str2[MAX_INPUT_LEN] = {0};
    uint16_t uppercase = 0, lowercase = 0, numbers = 0, others_ch = 0;

    MSG_PROMPT("Please set password of 8 to 15 characters, including uppercase and lowercase letters and numbers.\n");

    while (1) {
        memset(pw_str, 0, MAX_INPUT_LEN);
        memset(pw_str2, 0, MAX_INPUT_LEN);
        uppercase = 0;
        lowercase = 0;
        numbers = 0;
        others_ch = 0;

        HiddenInput(pw_str);

        for (int i = 0; i < strlen(pw_str); i ++) {
            if (pw_str[i] >= 'a' && pw_str[i] <= 'z') {
                lowercase++;
            } else if (pw_str[i] >= 'A' && pw_str[i] <= 'Z') {
                uppercase++;
            } else if (pw_str[i] >= '0' && pw_str[i] <= '9') {
                numbers++;
            } else {
                others_ch++;
            }
        }

        if (lowercase > 0 && uppercase > 0 && numbers > 0 && others_ch == 0
            && strlen(pw_str) >= MIN_PW_LEN && strlen(pw_str) <= MAX_PW_LEN)
        {
            MSG_PROMPT("Please enter again to confirm password:\n");
            HiddenInput(pw_str2);
            if (strcmp(pw_str, pw_str2) == 0) {
                encrypt(KEY_FILE, pw_str, BitwiseXOR);
                break;
            } else {
                MSG_PROMPT("The passwords entered twice are different! Reinput:\n");
                continue;
            }
        } else if (strlen(pw_str) < MIN_PW_LEN || strlen(pw_str) > MAX_PW_LEN) {
            MSG_ERR("Password length needs to be set from 8 to 15! Reinput:\n");
            continue;
        } else if (others_ch > 0) {
            MSG_ERR("Password can't contain space or special characters! Reinput:\n");
            continue;
        } else {
            MSG_ERR("Password must contain uppercase and lowercase letters and numbers! Reinput:\n");
            continue;
        }
    }

    MSG_DBG(msg_dbg_enable, "entered pw:%s\nlength: %ld\n", pw_str, strlen(pw_str));
    return EOK;
}
