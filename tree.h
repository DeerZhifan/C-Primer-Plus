//
//  tree.h
//  C_Primer_Plus
//
//  Created by 杨智帆 on 2019/1/30.
//  Copyright © 2019 杨智帆. All rights reserved.
//

/* tree.h -- 二叉查找树(该树不允许有重复的项) */

#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdbool.h>

#define SLEN 20
#define MAXITEMS 10

// 类型定义
typedef struct item
{
    char petname[SLEN];
    char petkind[SLEN];
} Item;

typedef struct trnode
{
    Item item;
    struct trnode * left;
    struct trnode * right;
} Trnode;

typedef struct tree
{
    Trnode * root;
    int size;
} Tree;

// 函数原型

//  操作：         初始化树为空
//  前提条件：      ptree指向一个树
//  后置条件：      树被初始化为空
void InitializeTree(Tree * ptree);

//  操作：         确定树是否为空
//  前提条件：      ptree指向一个树
//  后置条件：      如果树为空，该函数返回true，否则返回false
bool TreeIsEmpty(const Tree * ptree);

//  操作：         确定树是否已满
//  前提条件：      ptree指向一个树
//  后置条件：      如果树已满，该函数返回true，否则返回false
bool TreeIsFull(const Tree * ptree);

//  操作：         确定树的项数
//  前提条件：      ptree指向一个树
//  后置条件：      返回树的项数
int TreeItemCount(const Tree * ptree);

//  操作：         在树中添加一个项
//  前提条件：      pi是待添加项的地址，ptree指向一个树
//  后置条件：      如果可以添加，则添加一个项且该函数返回true，否则返回false
bool AddItem(const Item * pi, Tree * ptree);

//  操作：         在树中查找一个项
//  前提条件：      pi指向一个项，ptree指向一个树
//  后置条件：      如果在树中找到该项，则该函数返回true，否则返回false
bool InTree(const Item * pi, const Tree * ptree);

//  操作：         在树中删除一个项
//  前提条件：      pi是待删除项的地址，ptree指向一个树
//  后置条件：      如果成功从树中删除该项，则该函数返回true，否则返回false
bool DeleteItem(const Item * pi, Tree * ptree);

//  操作：         把函数应用于树中的每一项
//  前提条件：      ptree指向一个树, pfun指向一个函数
//  后置条件：      pfun指向的函数为树中的每一项执行一次
void Traverse(const Tree * ptree, void (*pfun) (Item item));

//  操作：         删除树中的所有内容
//  前提条件：      ptree指向一个树
//  后置条件：      树为空
void DeleteAll(Tree * ptree);

#endif /* tree_h */
