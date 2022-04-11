/*
 * @Descripttion: 
 * @version: 0.1.0
 * @Author: PandaYoung
 * @Date: 2022-04-09 03:25:39
 */

#include <unistd.h>
#include "../inc/list.h"

#define DEBUG_COLOR_OFF       "\033[0m"                 //关闭所有属性  
#define DEBUG_COLOR_ERR       "\033[1;31m"				//高亮红色
#define DEBUG_COLOR_WARN      "\033[1;33m"				//高亮黄色
#define PRINT_COLOR_INFO      "\033[1;37m"              //白色
#define DEBUG_COLOR_END       "\033[0;33m"				//灰色

int create_file()
{
    printf("There is no Students' infomation here, please add by 'Y' or exit by 'N'!\n");

    char confirm_code;
    scanf("%c", &confirm_code);
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
            save_to_file(head, 0);
            return EOK;
        }
        case 'n' :
        case 'N' : {
            printf("Exit.\n");
            return EOK;
        }
        default : {
            printf("Invalid input\n");
            return EINPUT;
        }
    }
}

int main()
{
    printf(DEBUG_COLOR_WARN "Welcome to Use the Student Information Management System!\n");

    if (access(FILE_NAME, F_OK)) {
        create_file();
    }

    printf(DEBUG_COLOR_OFF "Please follow the instructions.\n");
    printf("1. View all info\n");
    printf("2. Add info\n");
    printf("3. Modify info\n");
    printf("4. Delete info\n");
    printf("5. Sort by score\n");
    printf("6. Look up info\n");

    unsigned short ui_code;
    scanf("%d", &ui_code);
    switch(ui_code) {
        case 1: {
            if(verify_passwd()){
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
        default: {
            printf("Invalid input. %d\n", ui_code);
        }
    }

    return EOK;
}