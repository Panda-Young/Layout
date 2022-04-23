/*
 * @Descripttion: 
 * @version: 0.1.0
 * @Author: PandaYoung
 * @Date: 2022-04-09 03:25:39
 */

#include <unistd.h>
#include <conio.h>
#include "../inc/list.h"

int create_file()
{
    printf("There is no Students' infomation here, please add enter 'Y' or exit enter 'N'!\n");

    char confirm_code = getch();
    switch (confirm_code) {
        case 'y' :
        case 'Y' : {
            printf("Input Name, ID, Ch & Math & Eng scor, Age & Sex in proper order.\n");
            nodeptr_t head = (nodeptr_t)malloc(sizeof(node_t));
            if (head == NULL) {
                perror("malloc failed: ");
                return EALLOC;
            }
            scanf("%s %d %d %d %d %d %d", head->data.name, &head->data.stu_id, 
                    &head->data.score[0], &head->data.score[1], &head->data.score[2],
                    &head->data.stu_age, &head->data.stu_sex);
            head->next = NULL;
            save_to_file(head, 1);
            return EOK;
        }
        case 'n' :
        case 'N' : {
            printf("Exit.\n");
            return EOK;
        }
        default : {
            printf_red("Invalid input. Exit!\n");
            return EINPUT;
        }
    }
}

int main()
{
    printf_yellow("Welcome to Use the Student Information Management System!\n");

    if (access(FILE_NAME, F_OK)) {
        create_file();
    }

    unsigned short ui_code = 1;
    while (ui_code != 0) {
        printf_yellow("Please follow the instructions.\n");
        printf("0. Exit the system\n");
        printf("1. View all info\n");
        printf("2. Add info\n");
        printf("3. Modify info\n");
        printf("4. Delete info\n");
        printf("5. Sort by score\n");
        printf("6. Look up info\n");

        if (scanf("%d", &ui_code) != 1 || ui_code < 0 || ui_code > 6) {
            printf_red("Invalid input. Exit!\n");
            return EINPUT;
        }
        switch (ui_code) {
            case 0: {
                printf_yellow("Welcome to Use next time!\n");
                break;
            }
            case 1: {
                if (verify_passwd()) {
                    return EPASSWD;
                }
                view_all_info();
                break;
            }
            case 2: {
                // add_info();
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
        }
    }
    return EOK;
}
