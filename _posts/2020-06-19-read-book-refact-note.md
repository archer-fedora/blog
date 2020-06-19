---
layout: post
title:  Read Book
category: book
tags: refact
description: read book

---

## 

# 重构代码读书笔记

## 坏味道

**令人迷惑的临时变量**

将一个表达式提取为一个单独的函数，新函数可以被其它函数调用。之中有一段实例代码，用python改写如下：

```
def calc_price(self):
	base_price = self._quality * self._item_price
	if base_price > 1000:
		return base_price * 0.95
	else:
		return base_price * 0.98
```

重构后是这样的

```
def calc_price(self):
	if self.base_price() > 1000:
		return self.base_price() * 0.95
	else:
		return self.base_price() * 0.98

def base_price(self):
	return self._quality * self._item_price
```

