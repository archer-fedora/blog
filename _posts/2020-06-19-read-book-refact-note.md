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

## 基本类型偏执 ##

```text
/**
* a 存款
* b 收入
**/
public getSum(int a，int b){
    return a+b;
}
```

```text
public class Money{

    public int value;//货币面值
    public String name;//货币名称
    public float rate; //汇率
}

public getSum(Money a,Money b){
  return a.value*a.rate+b.value*b.rate;
}
```





## 惊现switch ##

```
public static int getServiceCode(String str){
     int code = 0;
     if(str.equals("Age")){
         code = 1;
     }else if(str.equals("Address")){
         code = 2;
     }else  if(str.equals("Name")){
         code = 3;
     }else if(str.equals("No")){
         code = 4;
     }
     return  code;
 }
```

　　重构后的代码如下所示：

```
public static void initialMap(){
     map.put("Age",1);
     map.put("Address",2);
     map.put("Name",3);
     map.put("No",4);
 }
```



#### 以多态取代条件表达式(Replace Conditional with Polymorphism)

**问题**

你手上有个条件表达式，它根据对象类型的不同而选择不同的行为。

```
class Bird {
  //...
  double getSpeed() {
    switch (type) {
      case EUROPEAN:
        return getBaseSpeed();
      case AFRICAN:
        return getBaseSpeed() - getLoadFactor() * numberOfCoconuts;
      case NORWEGIAN_BLUE:
        return (isNailed) ? 0 : getBaseSpeed(voltage);
    }
    throw new RuntimeException("Should be unreachable");
  }
}
```

**解决**

将这个条件表达式的每个分支放进一个子类内的覆写函数中，然后将原始函数声明为抽象函数。

```
abstract class Bird {
  //...
  abstract double getSpeed();
}

class European extends Bird {
  double getSpeed() {
    return getBaseSpeed();
  }
}
class African extends Bird {
  double getSpeed() {
    return getBaseSpeed() - getLoadFactor() * numberOfCoconuts;
  }
}
class NorwegianBlue extends Bird {
  double getSpeed() {
    return (isNailed) ? 0 : getBaseSpeed(voltage);
  }
}

// Somewhere in client code
speed = bird.getSpeed();
```





### 代码坏味道之代码臃肿

> **[代码臃肿(Bloated)](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之代码臃肿.md)这组坏味道意味着：代码中的类、函数、字段没有经过合理的组织，只是简单的堆砌起来。这一类型的问题通常在代码的初期并不明显，但是随着代码规模的增长而逐渐积累（特别是当没有人努力去根除它们时）。**

- [过长函数](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之代码臃肿.md#过长函数)
- [过大的类](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之代码臃肿.md#过大的类)
- [基本类型偏执](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之代码臃肿.md#基本类型偏执)
- [过长参数列](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之代码臃肿.md#过长参数列)
- [数据泥团](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之代码臃肿.md#数据泥团)

### 代码坏味道之滥用面向对象

> **[滥用面向对象(Object-Orientation Abusers)](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之滥用面向对象.md)这组坏味道意味着：代码部分或完全地违背了面向对象编程原则。**

- [switch 声明](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之滥用面向对象.md#switch-声明)
- [临时字段](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之滥用面向对象.md#临时字段)
- [被拒绝的馈赠](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之滥用面向对象.md#被拒绝的馈赠)
- [异曲同工的类](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之滥用面向对象.md#异曲同工的类)

### 代码坏味道之变革的障碍

> **[变革的障碍(Change Preventers)](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之变革的障碍.md)这组坏味道意味着：当你需要改变一处代码时，却发现不得不改变其他的地方。这使得程序开发变得复杂、代价高昂。**

- [发散式变化](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之变革的障碍.md#发散式变化)
- [霰弹式修改](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之变革的障碍.md#霰弹式修改)
- [平行继承体系](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之变革的障碍.md#平行继承体系)

### 代码坏味道之非必要的

> **[非必要的(Dispensables)](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之非必要的.md)这组坏味道意味着：这样的代码可有可无，它的存在反而影响整体代码的整洁和可读性。**

- [过多的注释](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之非必要的.md#过多的注释)
- [重复代码](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之非必要的.md#重复代码)
- [冗余类](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之非必要的.md#冗余类)
- [纯稚的数据类](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之非必要的.md#纯稚的数据类)
- [夸夸其谈未来性](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之非必要的.md#夸夸其谈未来性)

### 代码坏味道之耦合

> **[耦合(Couplers)](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之耦合.md)这组坏味道意味着：不同类之间过度耦合。**

- [依恋情结](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之耦合.md#依恋情结)
- [狎昵关系](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之耦合.md#狎昵关系)
- [过度耦合的消息链](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之耦合.md#过度耦合的消息链)
- [中间人](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之耦合.md#中间人)
- [不完美的库类](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之耦合.md#不完美的库类)

## 扩展阅读

- [代码的坏味道和重构](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/)
- [代码坏味道之代码臃肿](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之代码臃肿.md)
- [代码坏味道之滥用面向对象](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之滥用面向对象.md)
- [代码坏味道之变革的障碍](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之变革的障碍.md)
- [代码坏味道之非必要的](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之非必要的.md)
- [代码坏味道之耦合](https://github.com/dunwu/blog/blob/master/source/_posts/design/refactor/代码坏味道之耦合.md)