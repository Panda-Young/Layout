/*
 * @Descripttion: 
 * @version: 0.1.0
 * @Author: PandaYoung
 * @Date: 2022-04-09 03:28:51
 */
#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define FILE_NAME   "stu_info.txt"
#define NUM_ELEMENT 7
#define TRY_TIMES   3

#define TRUE        1
#define FALSE       0
#define EOK         0
#define EINPUT      -1
#define EALLOC      -2
#define EFOPEN      -3
#define EPASSWD     -4
#define EMODE       -5

typedef struct {
    char            name[20];
    unsigned int    stu_id;
    unsigned short  score[3];
    unsigned short  stu_age;
    bool            stu_sex;
}stu_info_t;

typedef struct node {
    stu_info_t      data;
    struct node     *next;
}node_t, *nodeptr_t;

int verify_passwd();

nodeptr_t add_endnode(nodeptr_t end);
nodeptr_t add_beginnode(nodeptr_t head);
nodeptr_t add_randomnode(nodeptr_t head, nodeptr_t current);
int save_to_file(nodeptr_t tmp, int mode);
int view_all_info(void);

#endif