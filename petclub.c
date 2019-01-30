//
//  petclub.c
//  C_Primer_Plus
//
//  Created by 杨智帆 on 2019/1/30.
//  Copyright © 2019 杨智帆. All rights reserved.
//

//  petclub.c -- 使用二叉查找树接口
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

char menu(void);
void addpet(Tree * pt);
void droppet(Tree * pt);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(Item item);
void uppercase(char * str);
char * sgs6(char * st, int n);

void petclub(void)
{
    Tree pets;
    char choice;
    
    InitializeTree(&pets);
    while ((choice = menu()) != 'q')
    {
        switch (choice)
        {
            case 'a': addpet(&pets);
                break;
            case 'l': showpets(&pets);
                break;
            case 'f': findpet(&pets);
                break;
            case 'n': printf("%d pets in club\n", TreeItemCount(&pets));
                break;
            case 'd': droppet(&pets);
                break;
            default: puts("Switching error!");
        }
    }
    DeleteAll(&pets);
    puts("Bye!");
}

char menu(void)
{
    int ch;
    
    puts("Nerfville Pet Club Membership Program");
    puts("Enter the letter corresponding to your choice:");
    puts("a)    add a pet       l)    show list of pets");
    puts("n)    number of pets  f)    find pets");
    puts("d)    delete a pet    q)    quit");
    
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("alnfdq", ch) == NULL)
            puts("Please enter an a l n f d q");
        else
            break;
    }
    if (ch == EOF)
        ch = 'q';
    
    return ch;
}

void addpet(Tree * pt)
{
    Item temp;
    
    if (TreeIsFull(pt))
        puts("No room in the club");
    else
    {
        puts("Please enter the name of pet:");
        sgs6(temp.petname, SLEN);
        puts("Please enter the pet kind:");
        sgs6(temp.petkind, SLEN);
        uppercase(temp.petname);
        uppercase(temp.petkind);
        AddItem(&temp, pt);
    }
}

void showpets(const Tree * pt)
{
    if (TreeIsEmpty(pt))
        puts("Nothing to show!");
    else
        Traverse(pt, printitem);
}

void printitem(Item item)
{
    printf("Pet: %-19s  Kind: %-19s\n", item.petname, item.petkind);
}

void findpet(const Tree * pt)
{
    Item temp;
    
    if (TreeIsEmpty(pt))
    {
        puts("Nothing to find!");
        return;
    }
    
    puts("Please enter the name of the pet you wish to find: ");
    sgs6(temp.petname, SLEN);
    puts("Please enter the petkind:");
    sgs6(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    printf("%s the %s ", temp.petname, temp.petkind);
    if (InTree(&temp, pt))
        printf("is a member.\n");
    else
        printf("is not a member.\n");
}

void droppet(Tree * pt)
{
    Item temp;
    
    if (TreeIsEmpty(pt))
    {
        puts("Nothing to drop!");
        return;
    }
    
    puts("Please enter the name of the pet you wish to delete:");
    sgs6(temp.petname, SLEN);
    puts("Please enter the petkind:");
    sgs6(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    printf("%s the %s ", temp.petname, temp.petkind);
    if (DeleteItem(&temp, pt))
        printf("is dropped from the club.\n");
    else
        printf("is not a member.\n");
}

void uppercase(char * str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}

char * sgs6(char * st, int n)
{
    char * ret_val;
    char * find;
    
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    
    return ret_val;
}
