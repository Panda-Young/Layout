/*
 * @Description: 
 * @version: 0.1.0
 * @Author: PandaYoung
 * @Date: 2022-05-08 11:11:11
 */
#include "../inc/list.h"
#include <string.h>

nodeptr_t bubble_sort(nodeptr_t head)
{
    head = head->next;                  
    if (head == NULL) {
        return NULL;            
    }
    nodeptr_t tmp = (nodeptr_t)malloc(sizeof(node_t));
    if (tmp == NULL) {
        perror("malloc failed: ");
        return NULL;
    }
    nodeptr_t end = NULL; // 定义一个尾,初值为空，以后为每次的最大值
    while (end != head) {
        nodeptr_t p = head;
        nodeptr_t pnext = head->next;
        while (pnext != end) {
            if (p->data.stu_id > pnext->data.stu_id) {
                memcpy((void *)&tmp->data,   (void *)&p->data,     sizeof(stu_info_t));
                memcpy((void *)&p->data,     (void *)&pnext->data, sizeof(stu_info_t));
                memcpy((void *)&pnext->data, (void *)&tmp->data,   sizeof(stu_info_t));
            }
            p = p->next;  
            pnext = pnext->next;  
        }
        end = p;
    }
    return head;
}