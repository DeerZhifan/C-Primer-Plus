//
//  tree.c
//  C_Primer_Plus
//
//  Created by 杨智帆 on 2019/1/30.
//  Copyright © 2019 杨智帆. All rights reserved.
//
/* tree.c -- 实现二叉查找树接口 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

//  局部数据类型
typedef struct pair
{
    Trnode * parent;
    Trnode * child;
} Pair;

// 局部函数原型
static Trnode * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode(Trnode * new_node, Trnode * root);
static void InOrder(const Trnode * root, void (*pfun) (Item item));
static Pair SeekItem(const Item * pi, const Tree * ptree);
static void DeleteNode(Trnode ** ptr);
static void DeleteAllNodes(Trnode * root);

//  接口函数定义
//  初始化树为空
void InitializeTree(Tree * ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

//  判断树是否为空
bool TreeIsEmpty(const Tree * ptree)
{
    return ptree->size == 0;
}

//  判断树是否已满
bool TreeIsFull(const Tree * ptree)
{
    return ptree->size == MAXITEMS;
}

//  返回树中的项数
int TreeItemCount(const Tree * ptree)
{
    return ptree->size;
}

//  向树中增加项
bool AddItem(const Item * pi, Tree * ptree)
{
    Trnode * new_node;
    
    if (TreeIsFull(ptree))
    {
        fprintf(stderr, "Tree is full!\n");
        return false;
    }
    if (SeekItem(pi, ptree).child != NULL)
    {
        fprintf(stderr, "Attempted to add duplicated item\n");
        return false;
    }
    
    new_node = MakeNode(pi);
    if (new_node == NULL)
    {
        fprintf(stderr, "Couldn't create new node\n");
        return false;
    }
    
    ptree->size++;
    
    if (ptree->root == NULL)
        ptree->root = new_node;
    else
        AddNode(new_node, ptree->root);
    
    return true;
}

//  判断某项是否已存在树中
bool InTree(const Item * pi, const Tree * ptree)
{
    return (SeekItem(pi, ptree).child == NULL) ? false : true;
}

//  从树中删除某项
bool DeleteItem(const Item * pi, Tree * ptree)
{
    Pair look;
    
    look = SeekItem(pi, ptree);
    
    if (look.child == NULL)
        return false;
    
    if (look.parent == NULL)
        DeleteNode(&ptree->root);
    else if (look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right);
    ptree->size--;
    
    return true;
}

//  遍历树
void Traverse(const Tree * ptree, void (*pfun) (Item item))
{
    if (ptree != NULL)
        InOrder(ptree->root, pfun);
}

//  清空树
void DeleteAll(Tree * ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}




//  局部函数定义
//  生成新的节点并返回该节点的指针
static Trnode * MakeNode(const Item * pi)
{
    Trnode * new_node;
    
    new_node = (Trnode *) malloc(sizeof(Trnode));
    if (new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    
    return new_node;
}

//  判断操作是否从左子树进行
static bool ToLeft(const Item * i1, const Item * i2)
{
    int flag_1 = strcmp(i1->petname, i2->petname);
    int flag_2 = strcmp(i1->petkind, i2->petkind);
    
    if (flag_1 < 0 )
        return true;
    else if (flag_1 == 0 && flag_2 < 0)
        return true;
    else
        return false;
}

//  判断操作是否从右子树进行
static bool ToRight(const Item * i1, const Item * i2)
{
    int flag_1 = strcmp(i1->petname, i2->petname);
    int flag_2 = strcmp(i1->petkind, i2->petkind);
    
    if (flag_1 > 0)
        return true;
    else if (flag_1 == 0 && flag_2 > 0)
        return true;
    else
        return false;
}

//  向树中增加一个节点
static void AddNode(Trnode * new_node, Trnode * root)
{
    if (ToLeft(&new_node->item, &root->item))
    {
        if (root->left == NULL)
            root->left = new_node;
        else
            AddNode(new_node, root->left);
    }
    else if (ToRight(&new_node->item, &root->item))
    {
        if (root->right == NULL)
            root->right = new_node;
        else
            AddNode(new_node, root->right);
    }
    else
    {
        fprintf(stderr, "Location error in AddNode()\n");
        exit(1);
    }
}

//  递归遍历树，左子树->项->右子树
static void InOrder(const Trnode * root, void (*pfun) (Item item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        (*pfun) (root->item);
        InOrder(root->right, pfun);
    }
}

//  从树中查找某项，返回包含该项的节点指针，以及该节点的父节点的指针
static Pair SeekItem(const Item * pi, const Tree * ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;
    
    if (look.child == NULL)
        return look;
    
    while (look.child != NULL)
    {
        if (ToLeft(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else
            break;
    }
    
    return look;
}

//  从树中删除某个节点
static void DeleteNode(Trnode ** ptr)
// ptr是指向目标节点的父节点指针成员的地址，因此（*ptr）即代表指向目标节点的指针
{
    Trnode * temp;
    
    if ((*ptr)->left == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if ((*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else
    {
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
            continue;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
}

//  删除树中所有节点，左子节点->父节点->右节点
static void DeleteAllNodes(Trnode * root)
{
    Trnode * pright;
    
    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}
