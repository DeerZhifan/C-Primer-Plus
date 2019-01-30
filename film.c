//
//  film.c
//  C_Primer_Plus
//
//  Created by 杨智帆 on 2019/1/26.
//  Copyright © 2019 杨智帆. All rights reserved.
//

/* film.c -- 使用抽象数据类型(ADT)风格的链表 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>     /* 提供exit()的原型 */
#include "list.h"       /* 定义List、Item  */
void showmovies(Item item);
char * sgs5(char *, int);

void film(void)
{
    List movies;
    Item temp;
    
    /* 初始化 */
    InitializeList(&movies);
    if (ListIsFull(&movies))
    {
        fprintf(stderr, "No memory available! Bye!\n");
        exit(1);
    }
    
    /* 获取用户输入并储存 */
    puts("Enter first movie title:");
    while (sgs5(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
    {
        puts("Enter your rating <0-10>:");
        scanf("%d", &temp.rating);
        while (getchar() != '\n')
            continue;
        if (AddItem(temp, &movies) == false)
        {
            fprintf(stderr, "Problem allocating memory\n");
            break;
        }
        if (ListIsFull(&movies))
        {
            puts("The list is now full.");
            break;
        }
        puts("Enter the next movie title (empty line to stop):");
    }
    
    /* 显示 */
    if (ListIsEmpty(&movies))
        puts("No data entered.");
    else
    {
        puts("Here is the movie list: \n");
        Traverse(&movies, showmovies);
    }
    printf("You entered %d movies.\n", ListItemCount(&movies));
    
    /* 清理 */
    EmptyTheList(&movies);
    puts("Bye!");
}

void showmovies(Item item)
{
    printf("Movie: %s Rating: %d\n", item.title, item.rating);
}

char * sgs5(char * p, int n)
{
    char * find;
    char * ret_val;
    
    ret_val = fgets(p, n, stdin);
    if (ret_val)
    {
        find = strchr(p, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    
    return ret_val;
}
