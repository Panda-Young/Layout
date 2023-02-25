/*
 * @Description: The specific inplementation of various function of the link list.
 * @version: 0.1.0
 * @Author: Panda-Young
 * @Date: 2022-04-10 02:24:32
 * Copyright (c) 2022 by Panda-Young, All Rights Reserved.
 */

#include "list.h"

extern bool msg_dbg_enable;

nodeptr_t add_endnode(nodeptr_t end)
{
    if (end == NULL) {
        MSG_INFO("end node is NULL.\n");
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
        MSG_INFO("head node is NULL.\n");
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
        MSG_INFO("head or current node is NULL.\n");
        return NULL;
    }
    nodeptr_t newnode = (nodeptr_t)malloc(sizeof(node_t));
    if (newnode == NULL) {
        perror("malloc failed: ");
        return NULL;
    }

    nodeptr_t tmp = NULL;
#if ANOTHER_WAY // before any node
    for (tmp = head; tmp->next != current; tmp = tmp->next);
    tmp->next = newnode;
    newnode->next = current;
#else // after any node
    tmp = current->next;
    newnode->next = tmp;
    current->next = newnode;
#endif
    return newnode;
}

/**
 * @description: reverse the list
 * @param {nodeptr_t} head
 * @return {nodeptr_t}
 */
nodeptr_t reverse_list(nodeptr_t head)
{
    if (head == NULL || head->next == NULL) {
        return head;
    }
#if ANOTHER_WAY // Recursion
    nodeptr_t Pnext = head->next;
    nodeptr_t Ptemp = reverse_list(Pnext);
    Pnext->next = head;
    head->next = NULL;
    return Ptemp;
#else // Iteration
    nodeptr_t Ptemp = NULL;
    nodeptr_t Pcurr = head;
    nodeptr_t Pnext;
    while (Pcurr != NULL) {
        Pnext = Pcurr->next;
        Pcurr->next = Ptemp;
        Ptemp = Pcurr;
        Pcurr = Pnext;
    }
    head = Ptemp;
#endif
    return head;
}

/**
 * @Descripttion: save node info to file
 * @param {nodeptr_t} tmp
 * @param {int} mode
 *              0   Write information about all nodes from the current to end to a cleared file,
 *      usually used for the header node.
 *              1   Append the current node information to the end of file.
 * @return {int}
 */
int save_to_file(nodeptr_t tmp, bool mode)
{
    FILE *fp = NULL;
    if (mode == 0) {
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
    } else if (mode == 1){
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

/**
 * @Descripttion: creat new file to save infomation
 * @param {nodeptr_t} head
 * @param {unsigned char} *confirm_code
 * @return {int}
 */
int create_file(nodeptr_t head, unsigned char *confirm_code)
{
    if (head == NULL) {
        return EALLOC;
    }
    if(*confirm_code == 'y' || *confirm_code == 'Y') {
        nodeptr_t current = head;
        while (1) {
            MSG_PROMPT("Input Name, ID, Ch & Math & Eng score, Age & Sex in proper order.\n");
            scanf("%s %d %hd %hd %hd %hd %d", current->data.name, &current->data.stu_id,
                    &current->data.score[0], &current->data.score[1], &current->data.score[2],
                    &current->data.stu_age, &current->data.stu_sex);

            MSG_PROMPT("Whether continue to add info? Press 'Y' or any other key to End!\n");
            if (scanf("%c", confirm_code) && *confirm_code == 10) {
                scanf("%c", confirm_code);
            }
            if (*confirm_code == 'y' || *confirm_code == 'Y') {
                current = add_endnode(current);
            } else {
                break;
            }
        }
        save_to_file(head, 0);
        for (nodeptr_t temp = head->next; temp != NULL; temp = temp->next) {
            free(temp);
        }
    } else {
        MSG_PROMPT("Welcome to Use next time!\n");
        *confirm_code = 0;
    }
    return EOK;
}

/**
 * @description: read information from file
 * @param {nodeptr_t} head
 * @param {bool} *any_info
 * @return {int}
 */
int read_file(nodeptr_t head)
{
    FILE *fp = NULL;
    if ((fp = fopen(FILE_NAME, "r")) == NULL) {
        perror("open file failed: ");
        return EFOPEN;
    }

    for (nodeptr_t current = head->next; current != NULL; current = current->next) {
        free(current);
    }

    int node_num = 0;
    nodeptr_t current = head;
    while (fscanf(fp, "%s %d %hd %hd %hd %hd %d", current->data.name, &current->data.stu_id,
            &current->data.score[0], &current->data.score[1], &current->data.score[2],
            &current->data.stu_age, &current->data.stu_sex) == NUM_ELEMENT) {
        node_num++;
        if(fgetc(fp) == 10 && fgetc(fp) == EOF) {
            break;
        } else {
            fseek(fp, -1, SEEK_CUR);
            if ((current = add_endnode(current)) ==  NULL) {
                MSG_ERR("add new link node error\n");
                return EALLOC;
            }
        }
    }
    fclose(fp);
    return node_num;
}

/**
 * @Descripttion: View all information in the file
 * @param {nodeptr_t} head
 * @param {unsigned char} *confirm_code
 * @return {int}
 */
int view_info(nodeptr_t head, unsigned char *confirm_code)
{
    if (head == NULL) {
        MSG_ERR("malloc failed");
        return EALLOC;
    }

    int node_num = read_file(head);
    int counter = 1;

    if (node_num > 0) {
        MSG_DATA("Name\t\tID\t\tChinese\t\tMath\t\tEnglish\t\tAge\t\tSex\n");
        for (nodeptr_t current = head; current != NULL; current = current->next) {
            MSG_DATA("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%s\n", current->data.name,
                current->data.stu_id, current->data.score[0], current->data.score[1],
                current->data.score[2], current->data.stu_age, current->data.stu_sex? "boy" : "girl");
            MSG_DBG(msg_dbg_enable, "%d\t current ptr %p\n",counter++, current);
        }
    } else if (node_num == 0) {
        MSG_INFO("The content of the file is empty! Press 'Y' to add info or any other key to Exit!\n");
        if (scanf("%c", confirm_code) && *confirm_code == 10) {
            scanf("%c", confirm_code);
        }
        create_file(head, confirm_code);
    } else {
        MSG_ERR("read file error, result %d", node_num);
    }

    return EOK;
}

/**
 * @description: Delete someone's information
 * @param {nodeptr_t} head
 * @param {unsigned char} *confirm_code
 * @return {int}
 */
int add_info(nodeptr_t head, unsigned char *confirm_code)
{
    if (head == NULL) {
        MSG_ERR("malloc failed");
        return EALLOC;
    }

    nodeptr_t current = head;
    for (; current->next != NULL; current = current->next);
    *confirm_code = 'Y';

    while (1) {
        if (*confirm_code == 'y' || *confirm_code == 'Y') {
#if ANOTHER_WAY
            head = add_beginnode(head);
#elif ANOTHER_WAY2
            current = add_randomnode(head, head);
#else
            current = add_endnode(current);
#endif
    } else {
        break;
    }

        MSG_PROMPT("Input Name, ID, Ch & Math & Eng score, Age & Sex in proper order.\n");
        if (scanf("%s %d %hd %hd %hd %hd %d", current->data.name, &current->data.stu_id,
                &current->data.score[0], &current->data.score[1], &current->data.score[2],
                &current->data.stu_age, &current->data.stu_sex) != NUM_ELEMENT) {
            MSG_ERR("Please check student information.\n");
            return EINPUT;
        }

        MSG_PROMPT("Whether continue to add info? Press 'Y' or any other key to End!\n");
        fflush(stdin);
        scanf("%c", confirm_code);
    }
    MSG_DBG(msg_dbg_enable, "head ptr %p\n",head);
    save_to_file(head, 0);

    return EOK;
}

/**
 * @description: Delete someone's information
 * @param {nodeptr_t} head
 * @return {int}
 */
int delete_info(nodeptr_t head)
{
    unsigned int stu_id;
    MSG_PROMPT("Please input student id you want to delete.\n");
    scanf("%d", &stu_id);

    nodeptr_t current = head;
    for (; current != NULL; current = current->next) {
        if (current->data.stu_id == stu_id) {
            nodeptr_t Ppre = head;
            for (; Ppre->next != current; Ppre = Ppre->next);
            Ppre->next = current->next;
            free(current);
            current = NULL;
            break;
        }
    }
    if (current == NULL) {
        MSG_ERR("No information about the student was found\n");
        fflush(stdin);
        return EINPUT;
    }
    save_to_file(head, 0);

    return EOK;
}

/**
 * @description: Modify someone's information
 * @param {nodeptr_t} head
 * @return {int}
 */
int modify_info(nodeptr_t head)
{
    unsigned int stu_id;
    MSG_PROMPT("Please input student id you want to modify.\n");
    fflush(stdin);
    scanf("%d", &stu_id);

    nodeptr_t current = head;
    for (; current != NULL; current = current->next) {
        if (current->data.stu_id == stu_id) {
            MSG_PROMPT("Input Name, ID, Ch & Math & Eng score, Age & Sex in proper order.\n");
            scanf("%s %d %hd %hd %hd %hd %d", current->data.name, &current->data.stu_id,
                    &current->data.score[0], &current->data.score[1], &current->data.score[2],
                    &current->data.stu_age, &current->data.stu_sex);

            MSG_DATA("Name\t\tID\t\tChinese\t\tMath\t\tEnglish\t\tAge\t\tSex\n");
            MSG_DATA("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%s\n",
                current->data.name, current->data.stu_id,
                current->data.score[0], current->data.score[1], current->data.score[2],
                current->data.stu_age, current->data.stu_sex? "boy" : "girl");
            break;
        }
    }
    if (current == NULL) {
        MSG_ERR("No information about the student was found!\n");
        fflush(stdin);
        return EINPUT;
    }
    save_to_file(head, 0);
    return EOK;
}

/**
 * @description: Find someone's information
 * @param {nodeptr_t} head
 * @return {int}
 */
int find_info(nodeptr_t head, unsigned char *confirm_code)
{
    while (1) {
        MSG_PROMPT("Please input student id you want to find.\n");
        unsigned int stu_id = 0;
        scanf("%d", &stu_id);
        if (stu_id != 0) {
            nodeptr_t current = head;
            for (; current != NULL; current = current->next) {
                if (current->data.stu_id == stu_id) {
                    MSG_DATA("Name\t\tID\t\tChinese\t\tMath\t\tEnglish\t\tAge\t\tSex\n");
                    MSG_DATA("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%s\n",
                        current->data.name, current->data.stu_id,
                        current->data.score[0], current->data.score[1], current->data.score[2],
                        current->data.stu_age, current->data.stu_sex? "boy" : "girl");
                    break;
                }
            }
            if (current == NULL) {
                MSG_ERR("No information about the student was found!\n");
            }
            MSG_PROMPT("Whether to continue? 'Y' or 'N'.\n");
            fflush(stdin);
            scanf("%c", confirm_code);
            if (*confirm_code == 'y' || *confirm_code == 'Y') {
                continue;
            } else {
                break;
            }
        } else {
            MSG_ERR("Invalid input! Whether to continue? 'Y' or 'N'.\n");
            fflush(stdin);
            scanf("%c", confirm_code);
            if (*confirm_code == 'y' || *confirm_code == 'Y') {
                continue;
            } else {
                break;
            }
            fflush(stdin);
        }
    }
    return EOK;
}

/**
 * @description: sort information by students' score
 * @param {nodeptr_t} head
 * @return {int}
 */
int sort_info(nodeptr_t head)
{
    if (head->next != NULL) {
#if ANOTHER_WAY
        nodeptr_t end = NULL;
        for(end = head; end->next != NULL; end = end->next);
        quick_sort(head, end);
#else
        bubble_sort(head);
#endif

        MSG_DBG(msg_dbg_enable, "Name\t\tID\t\tChinese\t\tMath\t\tEnglish\t\tAge\t\tSex\n");
        for (nodeptr_t current = head; current != NULL; current = current->next) {
            MSG_DBG(msg_dbg_enable, "%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%s\n",
                current->data.name, current->data.stu_id,
                current->data.score[0], current->data.score[1], current->data.score[2],
                current->data.stu_age, current->data.stu_sex? "boy" : "girl");
        }
        save_to_file(head, 0);
    }
    return EOK;
}
