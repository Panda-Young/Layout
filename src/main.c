/******************************************************************************
 * @Description: The Student Infomation Management System.
 * @version: 1.1.1
 * @Author: Panda-Young
 * @Date: 2022-04-09 03:25:39
 * Copyright (c) 2022 by Panda-Young, All Rights Reserved.
 *****************************************************************************/

#include "list.h"
#include "log.h"

uint8_t MSG_DBG_ENABLE = FALSE;

/**
 * @description: UI operation interface
 * @param {int} argc
 * @param {int8_t} *argv
 * @return {int}
 */
int32_t main(int32_t argc, char *argv[])
{
    if (check_license() != 0) {
        return 0;
    }

    MSG_PROMPT("Welcome to Use the Student Information Management System!\n");

    int8_t optind_ch;
    while ((optind_ch = getopt(argc, argv, "::d::hv")) != -1) {
        switch (optind_ch) {
            case 'd' : {
                MSG_PROMPT("Enable debug massage.\n");
                if (optarg == NULL) {
                    MSG_DBG_ENABLE = 1;
                } else {
                    MSG_DBG_ENABLE = atoi(optarg);
                    if (!(MSG_DBG_ENABLE == 0 || MSG_DBG_ENABLE == 1 || MSG_DBG_ENABLE == 2 || MSG_DBG_ENABLE == 3)) {
                        MSG_ERR("Invalid paramter, set debug log level to default.\n");
                        MSG_DBG_ENABLE = 0;
                    }
                }
                break;
            }
            case 'h' : {
                bless_you();
                MSG_PROMPT("Please follow the instructions to choose.\n");
                break;
            }
            case 'v' : {
                MSG_PROMPT("Version: 1.1.1\n");
                break;
            }
            default: {
                MSG_ERR("Invalid operater paramter: -\?\n");
                break;
            }
        }
    }

    nodeptr_t head = (nodeptr_t)calloc(sizeof(node_t), 1);
    if (head == NULL) {
        perror("malloc failed: ");
        return EALLOC;
    }
    head->next = NULL;
    uint8_t ui_code = ASCII_ENTER;
    uint8_t login = 0;

    if (access(FILE_NAME, F_OK)) {
        set_secure_password();
        MSG_PROMPT("There is no Students' infomation here. Press 'Y' to add info or any other key to Exit!\n");
        scanf("%c", &ui_code);
        fflush_stdin();
        create_file(head, &ui_code);
    } else {
        read_file(head);
    }

    while (ui_code != 0) {
        MSG_INFO("0. Exit the system\t");
        MSG_INFO("1. View all info\t");
        MSG_INFO("2. Add info\t\t");
        MSG_INFO("3. Delete info\n");
        MSG_INFO("4. Modify info\t\t");
        MSG_INFO("5. Find info\t\t");
        MSG_INFO("6. Sort info\n");

        scanf("%c", &ui_code);
        fflush_stdin();
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
                if (login) {
                    view_info(head, &ui_code);
                } else if (verify_passwd() == 0) {
                    login = 1;
                    view_info(head, &ui_code);
                } else {
                    ui_code = 0;
                    break;
                }
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

    free_all_node(head);

    return EOK;
}
