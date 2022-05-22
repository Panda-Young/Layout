/*
 * @Descripttion:  Student Information Management System
 * @version: 0.1.2
 * @Author: PandaYoung
 * @Date: 2022-04-09 03:25:39
 */

#include <unistd.h>
#include <conio.h>
#include "../inc/list.h"

/**
 * @description: UI operation interface
 * @param {*}
 * @return {int}
 */
int main()
{
    printf_yellow("Welcome to Use the Student Information Management System!\n");

    nodeptr_t head = (nodeptr_t)malloc(sizeof(node_t));
    if (head == NULL) {
        perror("malloc failed: ");
        return EALLOC;
    }
    head->next = NULL;
    unsigned char ui_code = 13;

    if (access(FILE_NAME, F_OK)) {
        printf("There is no Students' infomation here. Press 'Y' to add info or any other key to Exit!\n");
        scanf("%c", &ui_code);
        create_file(head, &ui_code);
    }

    while (ui_code != 0) {
        printf_yellow("Please follow the instructions.\n");
        printf("0. Exit the system\t");
        printf("1. View all info\t");
        printf("2. Add info\t\t");
        printf("3. Delete info\n");
        printf("4. Modify info\t\t");
        printf("5. Find info\t\t");
        printf("6. Sort info\n");

        if (scanf("%c", &ui_code)  && ui_code == 10) {
            scanf("%c", &ui_code);
        }
        switch (ui_code) {
            case '0':
            case 'q':
            case 'Q': {
                printf_yellow("Welcome to Use next time!\n");
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
                find_info(head);
                break;
            }
            case '6':
            case 's':
            case 'S': {
                sort_info(head);
                break;
            }
            default: {
                printf_red("Invalid input. Exit!\n");
                ui_code = 0;
                break;
            }
        }
    }

    nodeptr_t current = head;
    int counter = 1;
    for (current = head; current != NULL; current = current->next) {
#if DEBUG_FREE_MSG
        printf_light_blue("%d\t current ptr %p\n",counter++, current);
#endif
        free(current);
    }

    return EOK;
}
