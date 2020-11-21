layout: post
title:  Read Book
category: book
tags: leetcode
description: read book

# 				BFS模版





```c
#define N 9999

struct TreeNode* g_stack[N];
int g_begin;
int g_end;

void Init()
{
    g_begin = -1;
    g_end = -1;
}

void Push(struct TreeNode* v)
{
    g_end = (g_end + 1) % N;
    g_stack[g_end] = v;
}

struct TreeNode* Pop()
{
    g_begin = (g_begin + 1) % N;
    return g_stack[g_begin];
}

int GetNum()
{
    return (g_end + N - g_begin)%N;
}

int* g_res[N];
int g_num;
int g_col[N];
void Bfs(struct TreeNode* root)
{
    while(GetNum()>0) {
        int len = GetNum();
        g_res[g_num] = malloc(sizeof(int)*len);
        for (int i = 0; i< len; i++) {
            struct TreeNode* r = Pop();
            if (r->left) Push(r->left);
            if (r->right) Push(r->right);
            g_res[g_num][i] = r->val;
        }
        g_col[g_num] = len;
        g_num++;
    }
}

```

