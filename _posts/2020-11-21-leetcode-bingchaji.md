layout: post
title:  Read Book
category: book
tags: refact
description: read book

# 				并查集模版



```c
int findFather(int x)
{
    if(pre[x] == x) return x;
    pre[x] = findFather(pre[x]);
		return pre[x];
}

void Uion(int x, int y) 
{
    int rootx;
    int rooty;
    rootx = findFather(x);
    rooty = findFather(y);
    if (rootx == rooty) {
        return;
    }
    pre[rootx] = rooty;
}


```

