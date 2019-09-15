---
layout: post
title:  今日leetcode完成
category: coding
tags: leetcode
description: leetcode 

---

## ## 今日leetcode完成



验证回文串
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。

示例 1:

输入: "A man, a plan, a canal: Panama"
输出: true
示例 2:

输入: "race a car"
输出: false



```c++
int isValid(char c) 
{
    if (c >= 'a' && c<='z') return 1;
    if (c >= 'A' && c<='Z') return 1;
    if (c >= '0' && c<='9') return 1;
    return 0;
}

bool isPalindrome(char * s){ 
    if (s == NULL) return false;
    int len = strlen(s);
    if (len <= 1) return true;
    int index = 0;
    int j = len - 1;
    while(index <= j) {
        if (!isValid(s[index])) {
            index++;
            continue;
        }
        if (!isValid(s[j])) {
            j--;
            continue;
        }
        if( tolower(s[index]) != tolower(s[j])) {
            return false;
        }
        index++;
        j--;
    }
    return true;
}
```




