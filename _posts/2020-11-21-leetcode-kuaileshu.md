



layout: post
title:  Read Book
category: book
tags: refact
description: read book

# 				Uthash模版



```
struct HashData {
    int key;
    int val;
    UT_hash_handle hh;
};

bool isHappy(int n){
    if (n == 1) return true;
    struct HashData *all = NULL;
    struct HashData *ele = NULL;
    HASH_FIND_INT(all, &n, ele);
    while (ele == NULL) {
        struct HashData *tmp = malloc(sizeof(struct HashData));
        tmp->key = n;
        HASH_ADD_INT(all, key, tmp);
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n = n / 10;
        }
        if (sum == 1) return true;
        n = sum;
        HASH_FIND_INT(all, &sum, ele);
    }
    return false;
}
```

