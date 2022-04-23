/*
 * @Descripttion: 
 * @version: 0.1.0
 * @Author: PandaYoung
 * @Date: 2022-04-10 02:24:32
 */
#include "../inc/list.h"

nodeptr_t add_endnode(nodeptr_t end)
{
    if (end == NULL) {
        printf("end node is null.\n");
        return NULL;
    }
    nodeptr_t newnode = (nodeptr_t)malloc(sizeof(node_t));
    if (newnode == NULL) {
        perror("malloc failed: ");
        return NULL;
    }
    end->next = newnode;
    newnode->next = NULL;
    return newnode;
}

nodeptr_t add_beginnode(nodeptr_t head)
{
    if (head == NULL) {
        printf("head node is null.\n");
        return NULL;
    }
    nodeptr_t newnode = (nodeptr_t)malloc(sizeof(node_t));
    if (newnode == NULL) {
        perror("malloc failed: ");
        return NULL;
    }
    newnode->next = head;
    return newnode;
}

nodeptr_t add_randomnode(nodeptr_t head, nodeptr_t current)
{
    if (head == NULL || current == NULL) {
        printf("head or current node is null.\n");
        return NULL;
    }
    nodeptr_t newnode = (nodeptr_t)malloc(sizeof(node_t));
    if (newnode == NULL) {
        perror("malloc failed: ");
        return NULL;
    }
#ifndef ANOTHER_WAY
    nodeptr_t tmp = NULL;
    for (tmp = head; tmp->next != current; tmp = tmp->next);
    tmp->next = newnode;
    newnode->next = current;
#endif
#ifdef ANOTHER_WAY
    nodeptr_t tmp = current->next;
    newnode->next = tmp;
    current->next = newnode;
#endif
    return newnode;
}

int save_to_file(nodeptr_t tmp, int mode)
{
    FILE *fp = NULL;
    if (mode == 1) { // 将当前至结尾所有节点信息写入清空的文件，一般用于头节点
        if ((fp = fopen(FILE_NAME, "w+")) == NULL) {  
            perror("open file failed: ");
            return EFOPEN;
        }
        while(tmp != NULL) {
            fprintf(fp, "%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", tmp->data.name, tmp->data.stu_id, 
                        tmp->data.score[0], tmp->data.score[1], tmp->data.score[2],
                        tmp->data.stu_age, tmp->data.stu_sex);
            tmp = tmp->next;
        }
    } else if (mode == 0){ // 将当前节点信息追加至文件末尾
        if ((fp = fopen(FILE_NAME, "a+")) == NULL) {
            perror("open file failed: ");
            return EFOPEN;
        }
        fprintf(fp, "%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", tmp->data.name, tmp->data.stu_id, 
            tmp->data.score[0], tmp->data.score[1], tmp->data.score[2],
            tmp->data.stu_age, tmp->data.stu_sex);
    } else {
        return EMODE;
    }

    fclose(fp);
    return EOK;
}

int view_all_info()
{
    FILE *fp = NULL;
    if ((fp = fopen(FILE_NAME, "r")) == NULL) {
        perror("open file failed: ");
        return EFOPEN;
    }

    nodeptr_t head = (nodeptr_t)malloc(sizeof(node_t));
    if (head == NULL) {
        perror("malloc failed: ");
        return EALLOC;
    }
    head->next = NULL;

    bool any_info = FALSE;
    nodeptr_t current = head;
    while (fscanf(fp, "%s %d %d %d %d %d %d", current->data.name, &current->data.stu_id, 
            &current->data.score[0], &current->data.score[1], &current->data.score[2],
            &current->data.stu_age, &current->data.stu_sex) == NUM_ELEMENT) {
        any_info = TRUE;
        if(fgetc(fp) == 10 && fgetc(fp) == EOF) {
            break;
        } else {
            fseek(fp, -1, SEEK_CUR);
            current = add_endnode(current);
        }
    }

    if (any_info) {
        printf("Name\t\tID\t\tChinese\t\tMath\t\tEnglish\t\tAge\t\tSex\n");
        for (current = head; current != NULL; current = current->next) {
            printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", current->data.name, current->data.stu_id, 
                current->data.score[0], current->data.score[1], current->data.score[2],
                current->data.stu_age, current->data.stu_sex);
        }
    }

    fclose(fp);
    return EOK;
}