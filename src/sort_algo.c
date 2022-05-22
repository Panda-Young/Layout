/*
 * @Description: 
 * @version: 0.1.0
 * @Author: PandaYoung
 * @Date: 2022-05-08 11:11:11
 */
#include "../inc/list.h"
#include <string.h>

void swap_node(nodeptr_t tmp_a, nodeptr_t tmp_b)
{
    stu_info_t tmp;
    memcpy((void *)&tmp,         (void *)&tmp_a->data, sizeof(stu_info_t));
    memcpy((void *)&tmp_a->data, (void *)&tmp_b->data, sizeof(stu_info_t));
    memcpy((void *)&tmp_b->data, (void *)&tmp,         sizeof(stu_info_t));
}

nodeptr_t bubble_sort(nodeptr_t head)
{
    nodeptr_t end = NULL;
    while (end != head) {
        nodeptr_t p = head;
        nodeptr_t pnext = head->next;
        while (pnext != end) {
            if (p->data.stu_id > pnext->data.stu_id) {
                swap_node(p, pnext);
            }
            p = p->next;  
            pnext = pnext->next;  
        }
        end = p;
    }

    return head;
}

nodeptr_t quick_sort(nodeptr_t head, nodeptr_t end)
{
    if (head == NULL || head->next == NULL || head == end) {
        return head;
    }

    int pivot = head->data.stu_id;
    nodeptr_t left = head->next, left_pre = head, right = head->next;

    while (right != end->next) {
        if (right->data.stu_id < pivot) {
            swap_node(left, right);
            left_pre = left;
            left = left->next;
        }
        right = right->next;
    }
    swap_node(head, left_pre);

    quick_sort(head, left_pre);
    quick_sort(left, end);

    return head;
}