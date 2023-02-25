/*
 * @Description: The Student Infomation Management System.
 * @version: 1.1.1
 * @Author: Panda-Young
 * @Date: 2022-04-09 03:25:39
 * Copyright (c) 2022 by Panda-Young, All Rights Reserved.
 */

#include "list.h"

bool MSG_DBG_ENABLE = FALSE;

/**
 * @description: UI operation interface
 * @param {int} argc
 * @param {char} *argv
 * @return {int}
 */
int main(int argc, char *argv[])
{
    MSG_PROMPT("Welcome to Use the Student Information Management System!\n");

    char cmd_ch;
    while ((cmd_ch = getopt(argc, argv, "::dhv")) != -1) {
        switch(cmd_ch) {
            case 'd' : {
                MSG_PROMPT("Enable debug massage.\n");
                MSG_DBG_ENABLE = TRUE;
                break;
            }
            case 'h' : {
                MSG_PROMPT("Please follow the instructions to choose.\n");
                break;
            }
            case 'v' : {
                MSG_PROMPT("Version: 1.1.0\n");
                break;
            }
        }
    }

    nodeptr_t head = (nodeptr_t)malloc(sizeof(node_t));
    if (head == NULL) {
        perror("malloc failed: ");
        return EALLOC;
    }
    head->next = NULL;
    unsigned char ui_code = ASCII_ENTER;

    if (access(FILE_NAME, F_OK)) {
        set_secure_password();
        MSG_PROMPT("There is no Students' infomation here. Press 'Y' to add info or any other key to Exit!\n");
        scanf("%c", &ui_code);
        create_file(head, &ui_code);
    } else {
        read_file(head);
    }

    while (ui_code != 0) {
        fflush(stdin);
        MSG_INFO("0. Exit the system\t");
        MSG_INFO("1. View all info\t");
        MSG_INFO("2. Add info\t\t");
        MSG_INFO("3. Delete info\n");
        MSG_INFO("4. Modify info\t\t");
        MSG_INFO("5. Find info\t\t");
        MSG_INFO("6. Sort info\n");

        if (scanf("%c", &ui_code)  && ui_code == ASCII_NEW_LINE) {
            scanf("%c", &ui_code);
        }
        switch (ui_code) {
            case '0':
            case 'q':
            case 'Q': {
                MSG_PROMPT("Welcome to Use next time!\n");
                ui_code = 0;
                break;
            }
            case '1':
            case 'v':
            case 'V': {
                if (verify_passwd()) {
                    ui_code = 0;
                    break;
                }
                view_info(head, &ui_code);
                break;
            }
            case '2':
            case 'a':
            case 'A': {
                add_info(head, &ui_code);
                break;
            }
            case '3':
            case 'd':
            case 'D': {
                delete_info(head);
                break;
            }
            case '4':
            case 'm':
            case 'M': {
                modify_info(head);
                break;
            }
            case '5':
            case 'f':
            case 'F': {
                find_info(head, &ui_code);
                break;
            }
            case '6':
            case 's':
            case 'S': {
                sort_info(head);
                break;
            }
            default : {
                MSG_ERR("Invalid input. Exit!\n");
                ui_code = 0;
                break;
            }
        }
    }

    int counter = 1;
    for (nodeptr_t current = head; current != NULL; current = current->next) {
        MSG_DBG("%d\t current ptr %p\n",counter++, current);
        free(current);
    }

    return EOK;
}
