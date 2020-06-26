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



【1】原代码

![复制代码](https://common.cnblogs.com/images/copycode.gif)

```
 1 class Sanitation 
 2 {
 3 public:
 4     string washHands() 
 5     {
 6         return "Cleaned ...";
 7     }
 8 };
 9 
10 class Child : public Sanitation 
11 {
12 
13 };
```

![复制代码](https://common.cnblogs.com/images/copycode.gif)

【2】以委托取代继承

![复制代码](https://common.cnblogs.com/images/copycode.gif)

```
class Child
{
public:
    Child() 
    {
        m_pSanitation = new Sanitation();
    }

    string washHands() 
    {
        // 这里使用委托获得 washHands() 方法 
        return (m_pSanitation->washHands());
    }
    
private:
    Sanitation *m_pSanitation; // 具有委托对象 Sanitation 的实例
};
```

![复制代码](https://common.cnblogs.com/images/copycode.gif)





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

![图片](https://img-blog.csdnimg.cn/2020051816393535.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JhaXllamlhbnhpbg==,size_16,color_FFFFFF,t_70#pic_center)

接触这些坏代码可以分为三类：

1. 见名知意的代码坏味道：
2. 稍微解释即可掌握的代码坏味道；
3. 通过一些例子即可掌握的代码的坏味道；

本文主要聚焦在“见名知意的代码坏味道”，后续两类坏味道将在后续的文章中解释说明：

## 1. 重复代码

简单的复制/粘贴，或者无意间添加了相同逻辑的代码都是有可能的导致重复代码出现的。



**那么为什么重复的代码是一种坏味道？**

最明显的就是重复的代码容易造成修改时的遗漏，修改遗漏导致一个问题需要修改多次才能才能确定最终修改完成。如果有一部分修改了，另外一部分没有修改且没有被发现，日后再遇到感觉类似，实则不同的代码会花费大量的时间确定业务上的需求，实现上应该如何处理。

重复代码这类坏味道产生的成本很低，但是带来的影响却是很大。



**如何解决重复代码问题？**

1. Simple Design 为我们提供了参考参考原则：“通过测试，揭示意图，消除重复，最少元素”。
2. 如果重复代码发生在一个类中，且两段代码完全重复，可以借助 Extract Method （提炼函数）这个重构手法来消除重复；提炼函数时 IDE 一般都会自动提示是否同时修改重复的代码，减少重构的工作量。
3. 如果重复代码发生在一个类中，且两段代码之后部分重复。那么可以将部分重复的代码通过 Extract Method 的手法，提炼到单独的方法中，并替换掉部分重复的代码。
4. 如果重复的代码在不同的类中，且这些类是兄弟类，可以使用 Pull Up Method，将重复的代码提炼到父类，并让原本的类继承父类。
5. 如果重复的代码在不同的类中，且这些类之间关联性不大，那么可以 Extract Class，将重复的挪动到一个新的类中，原本出现重复的地方来调用这个新产生的类的方法。
6. 消除重复之后，检测代码表达的意图是否准确、完成，Extract Method 时可以通过良好的方法名来解释提炼的函数的作用和意图。

## 2 长函数

顾名思义，长度过长的函数。其中包括两种情况，横向过长，纵向过长。



**为什么长函数是一种坏味道？**

横向过长时，往往一眼无法快速了解该行代码要表达的意思和中间的过程。当出现 Bug 定位问题时也不容易一次性定位到问题所在。

纵向过长时，往往会感觉某个函数内部逻辑复杂、晦涩难懂。修改代码中也会因为无法照顾到要修改的方法中的其他行代码，而顾此失彼，最终导致难度难修改。经过多次修改后甚至原有的基本结构都会遭到破坏，导致后续修改难度逐渐增加。



**如何解决长函数的问题？**

1. 横向过长的代码，可以通过代码格式化、CheckStyle插件来发现和消除。比如，Lambda 表达式，可以选择在出现第一个“.”时就就开始换行。

```java
List<Node> nodes = items.stream().filter(Item::isFree).filter(Item::notWork).map(Formater::format).filter(Node::hadChildren).filter(Node::hadMarked).collection(Collectors.toList());
```

这行代码我们需要仔细读 才能清楚中间的过程。采用首个“.”出现换行的将会是如下格式：

```java
List<Node> nodes = items
  .stream()
  .filter(Item::isFree)
  .filter(Item::notWork)
  .map(Formater::format)
  .filter(Node::hadChildren)
  .filter(Node::hadMarked)
  .collection(Collectors.toList());
```

通过对横向代码格式化能够为代码带来更好的可读性。当然你可以在提交代码到仓库时勾选上 commit 时自动格式化代码的选项，避免没有 Check Style 等工具来守护代码，遗漏掉格式问题。

1. 纵向过长的代码。往往多个实现细节堆叠在一个方法中造成的，这种情况下使用 Inline Temp（内联局部变量）、 Extract Method 的重构手法来提炼小的函数。一个类中有很多零散的小函数也是常见的，因此提炼函数的同时记住，提炼函数的也是也是考虑创建新的类时候，将不同作用的函数提炼到响应职责的类中。
2. 纵向过长的代码，往往存在职责不够单一的情况，保持方法职责的单一有助于维护代码的可读性。通过 2 中 提到的 Extract Method，那么某个具体实现细节可以被提炼到一个小函数中，而原来的函数则职责就编程调度作用。所以方法的单一职责，更清晰的描述应该是一类事情，要么只在处理实现细节，要么处理调度协调代码调用。

```java
public class OrderService{

  ...

  public Order create(OrderDTO orderDTO) {
    // 创建条件是否符合 4 行
    ...

    // 货币转换 4 行
    ...

    // 折扣计算 5 行
    ...

    // 将 OrderDTO 转换为 Order 对3行
    ...

    // 存储 Order 1 行
    ... 

    // 通知下有业务 5 行
    ...

    return order;
  }
}
```

看遗留系统时和面试作业的时候，总是看到这类代码，可以通过提炼函数并遵守方法的单一职责原则，就能够简单的重构实现一个逻辑更为清晰的代码结构，如下：

```java
public class OrderService {

    ...

    public Order create(OrderDTO orderDTO) {
         verify(orderDTO);

         Order order = orderRepository.save(orderMapper.toOrder()); 

         notifyService.notify(order);

         return order;
    }


    private void verify(OrderDTO orderDTO) {
         // 创建条件是否符合 4 行
         ...
    }
}


public interface OrderMapper {
  ...
  public Order toOrder() {
    // 将 OrderDTO 转换为 Order 对3行
    Currency currency = CurrentyTranslator.translator(currency); // 货币转换
    BigDecimal price = currentyTranslator.calculate(products);   // 提炼函数
    ...
  }
}


public class CurrentyTranslator {
        public static Currency translate (Currency currency) {
        // 货币转换 4 行
            ...
    }
}

public class PriceService {

    public BigDecimal calculate(List<Product> products) {
            // 折扣计算 5 行
            ...
        return xxx;
    }

}

public class NotifyService {
    private void notify(Order order){
          // 通知下有业务 5 行
          ...
    }
}
```

上面只是一个简单的重构方法，其中涉及到的重构手法：

 Move Field（搬移函数）将上下文相关的变量挪动的一起；

 Extract Method (提炼函数) 将某个具体的实现提炼到一个职责单一的方法中。

 Extract Method （提炼类）一个类尤其单独的职责，因此将那些和原本的该类的职责关联性不大的逻辑方法提炼到特定的类中。

 Inline Field（内联临时变量）如果一个变量对语意理解并没有什么帮助，那么就可以采用内联临时变量的方法，消除显示的定义变量，从而减少代码的行数，同时阅读代码时也会更加清爽、聚焦。

更具实际业务场景还可以借助一些注解、工具类、AOP 来让验证、转换、通知部分变得更加简洁。通过提炼函数的重构手法，能够让后续的重构更加方便可靠。

如果翻阅一些开发规范会发现有的团队规定一个方法不超过 15 行，其实知道这个规范只能获取到一个参考量，注意到行数多对，更重要的时候发现问题后的小步重构。

## 3 过大的类

顾名思义就是一个类做了太多的事情。SOLID 原则告诉我们类的职责应该是单一的，而一个过大类很可能意味着承担了多个/多类职责。



**过大的类为什么是一种坏味道？**

由于过大的类承担了过多的职责，很容易导致 重复代码 且 重复代码 不容易被发现，而这往往是坏味道的开始。

如果过大的类对外提供服务发生了变动，并不容易快速响应这样的变化，可以对比一下一个小而职责单一的类中进行修改方便还是在多很多职责。

当过大的类因为某个地方发生变化，很可能导致不相关的调用方的代码也会发生变化，这是一种耦合性的表现。

当过大的类被继承时很可能导致其他的坏味道，例如遗留的馈赠。

因此，保持小而职责单一的类将会对系统的设计有很大的帮助。当然也可以参考 Simple Design，避免过度设计的前提下保持简单的设计。



**如何解决过大的类的代码坏味道？**

1. 观察这个过大的类的属性，看是否有关联的几个属性能够代表一定的业务意思，如果可以使用 Extract Class，将这几个属性挪动到一个新的类中，并将相关操作挪动到新的类中。循环往复，这样一个大的类能够拆分成多个小的且职责较为单一的类。
2. 观察这个大类中的方法，看是否存在兄弟关系的方法，如果有可以使用 Extract Subclass （提炼子类）的方法，将相关方法提炼到子类中，并考虑使用继承父类还是面向接口使用 Extract Interface（提炼接口）。这样相似行为的行为聚集在一个类中，拆分到多个类中，并可以进一步和方法的调用发来解耦。
3. 进一步观察剩余类的行为，如果这些行为在处理一类事情，那么可以停止了，在处理多类事情，可以按照处理逻辑的类型进一步拆分。

简而言之，使用一个亘古不变的法则：分治法。将过大的类，拆分成多个职责单一的小类，手段是 Extract Class，Extract Subclass，Extract Interface。

## 4 过长参数列表

当方法的参数列表过长时这也是一种代码的坏味道。

**为什么参数过长是一种坏味道？**

参数过长和过大的类、过长的函数、重复代码一样，起初并不会导致什么错误，但是代码随着时间向前演变过程，会给代码带来很多麻烦。

长参数函数的可读性很差，尤其是存在多个类似长参数方法时，并不容易判断出应该使用哪个方法。

当需要为长参数函数添加新的参数时，将会促使调用方发生变化，且新参数的位置也将让这个方法更加难以理解。



**如何解决长参数的代码坏味道？**

1. 如果传递的几个参数都出自一个对象，那么可以选择使用 Preserve Whole Object（保持完整对象）直接传递该对象。
2. 如果方法的参数来自不同的对象，可以选择使用 Introduce Parameter Object（引入参数对象）将多个参数放入一个新的类中，原来方法传递多个分开的参数，现在传递一个包含多个属性的一个对象。
3. 如果调用者先计算调用 A 方法得到计算结果，然后将计算结果在传递给这个长参数函数，那么可以考虑去除这个参数，改为在长参数函数中直接调用 A 得到结果，从而消除传递的部分参数，这个重构过程可以参考 Replace Parameter With Method（使函数替换参数）。

需要的注意的是，有些情况下长参数的存在也是合理的，因为在一定程度上可以避免某些依赖关系的产生。可以通过观察长参数函数变化的频率，并采用“事不过三，三则重构“的原则，保持进行重构的准备。

## 5 Switch 语句

Switch 语句代表一类语句，比如 if...else, switch... case 语句都是 switch 语句。

**为什么 Switch 语句是一种代码坏味道？**

首先并不是所有的 Switch 语句都是坏味道，Swith 语句开发中常见的语句。这里带有坏味道的 Switch 语句指的是那些造成重复代码的 Switch语句。例如：根据某个状态来判断执行执行哪个动作。

```text
public Order nextStep(...) {
        if (state == 1) {
                // do something
        } else if (state == 2) {
                // do something
        } else if (state == 3) {
                // do something
        } else {
                // do something
        }
}
```

这种实现方法很多代码中都会出现，但是多数人使用这种方式添加代码，并不意味着这是一种好的代码。这样的实现方式很容易造成长函数，而且每次修改的位置要非常精准，需要在多个条件中逐个遍历找到最终需要的那个，再修改，可读性上无疑也是很差的。

如何处理 Switch 语句这种代码坏味道呢？**

1. 如果 swtich 语句是某个方法的一部分，那么不妨使用 Extract Method（提炼函数）将其先提炼出一个单独的方法，缩小上下文范围。
2. 观察多个条件中的动作的关联关系，是否符合多态，如果是将符合多态的几个条件创建对应的类，并使用 Move Method （移动函数）移动到新创建的类中。
3. 使用状态模式、枚举等多种实现手段消除其中的 swtich 语句。

如果对有限状态机感兴趣可以参考文章：[《Java有限状态机的4种实现对比》](https://zhuanlan.zhihu.com/p/97442825)

总而言之，一旦打算通过叠加新的 swtich case 来添加新逻辑，那么就应该关注一下代码设计，因为这种操作很有可能就是为后续的代码在挖坑。同时理解清楚那些swtich 语句是具有坏味道的语句。

## 6 夸夸其谈的未来性

这是工作中最常见的一类问题，比如如果你听到这句话“我将文件上传的实现做了调整 ... 未来再使用的时候将会 ...”就应该警觉起来。

**为什么夸夸其谈的未来型是一种代码坏味道？**

未来意味着当下并不是必须的，过度的抽象和提升复杂性也会让系统难以理解和维护，同时也容易分散团队的注意力，如果用不到，那么就不值得做。

除非你在进行假设驱动开发，否则代码上总是谈未来容易绑架团队的思想，拿未来不确定的事情来解释事情的合理，会让那些务实者，关注投入产出比的抉择。并且容易让团队进入一个假象。

当业务上变动时，并不能及时的将代码进行变动，因为原来的代码中包含了一种对未来假设的实现，无形中增加了代码的复杂度，而且很容易增加团队沟通成本。

**如何解决夸夸其谈的未来性的代码坏味道？**

Simple Design （简单设计原则）能够帮助我们作出抉择。当实现业务代码时考虑”通过测试、揭示意图、消除重复、最少元素“。

当发现为未来而写的代码时，可以：

1. 删除那些觉的未来有用的参数、代码、方法调用。
2. 修正方法名，使方法名揭示当下业务场景的意图，避免抽象的技术描述词。

通过上面两个过程将代码原本的要表达的意思还原回来。

工作中有两类未来性。一类是假设调用方可以怎么使用；一类是未来必然发生的业务功能。代码的坏味道更多的指的是第一种情况，第二种情况可以开发之前体现进行简单设计和拆分，从而避免过度设计，同时可以避免谈未来性，来让代码随着功能一起小步重构并演进。

## 7 令人迷惑的临时字段

在一些场景下为了在实现上的临时方便性，有的开发者会直接在某个对象上添加一个属性，后续使用在需要的时候使用该属性。

**令人迷惑的临时字段的是什么代码坏味道？**

一个类包含属性和方法，属性都是该类相关的。而临时向类中添加的字段，虽然临时有关联性，但是单独来看这个类中的属性时，却会让人觉得非常费解。有些接口的返回值就是也是类似原因导致的结果，每次为了方便像类中直接添加一些临时属性，满足了当时的需要，但是后续再使用的时候却并不能区分哪些属性时必须的，哪些是不必须的，以及哪些被添加的字段的上下文分别是什么。

**如何解决令人迷惑的临时字段？**

1. 问题的原因是随意向类上添加字段，解决的方法就是将这个临时字段移走，可以为这个字段找到一个合适的类来存放，也可以使用 Extract Class （提炼类）将这个字段添加到一个新类中，然后将该字段的相关的逻辑移动到该类中，并确定该类的职责。
2. 可以将临时字段作为参数进行传递，但是为了避免过长参数的出现，可以选择将临时字段提炼到一个新的类中。

## 8 过多的注释

这是注释降低代码可读性，甚至误导了代码要要表达的意图。

**为什么过多的注释是一种代码坏味道？**

首先并不是所有的注视都是坏味道。

如果想通过注释来表达代码的意思，那么代码修改了注释也需要同步进行修改，如果代码修改了但是没有修正这是注释就有可能导致误导。

还有一种注释的坏味道，指的是不使用的代码通过注释掉来表示其弃用。后续代码的阅读者会经常收到断断续续的注释掉的代码影响。降低读代码和改代码的速度。

在 《Clean Code》 中罗列了一些注释的坏味道：

1. 喃喃自语
2. 多余的注释
3. 误导性注释
4. 循规方注释
5. 日志式注释
6. 废话注释
7. 用注释来解释变量意思
8. 用来标记位置的注释
9. 类的归属的注释
10. 注释掉的代码
    ...

作者：PageThinker
链接：https://zhuanlan.zhihu.com/p/141803738
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。



如上图，这 10 个代码坏味道是：

1. 发散式变化
2. 霰弹式修改
3. 依恋情结
4. 数据泥球
5. 基本类型偏执
6. 平行继承体系
7. 冗赘类
8. 过度耦合信息链
9. 异曲同工的类
10. 纯数据类

## 01 发散式变化

简而言之就是一个类总是因为不同类型的原因发生变化。例如：需要修改数据源时要修改该类，需要修改缓存时还需要修改这个类，甚至当修改某个策略的计算公式时还会牵连到这个类。这种总是/经常因为不同类型原因导致一个类发生变化的代码就是指的发散式变化。

**为什么发散式变化是代码坏味道？**

由于总是不同的原因导致一个类发生变化，意味着一个类中存在多种类型的行为（例如即操作订单，又操作合同，还操作零件信息等），大而全的类会导致下面两方面的问题：

1. 降低了代码可读性，存在不同上下问题的切换；
2. 很可能导致无法快速响应变化。大而复杂类，在修改和维护的时候，并不容易做出决策，同时单个原因的修改很可能导致一个原因修改导致和非相关的业务代码发生变动。
3. 随着代码的增加，代码的复杂性肯定是增加的，而发散式变化如果不被关注，很容易导致后续代码修改时类变成难以修改的大泥球。

发散式变化很容易导致另外一个坏味道出现，就是“过大的类”。

**如何解决发散式变化这种坏味道？**

单一职责原则可以用来解决发散式变化、过大的类的坏味道的指导原则：一个类只有一个引起其变化的原因。既然由于一个类存在过类行为，可以通过 Extract Class 来将不同的方法提炼到不同职责的类中。

发散式变化虽然很简单，但是却是很容易遇到的一种坏味道。因为刚开始添加的代码的很可能体会不到一个存在多类行为的坏处。只有当类发生变化或者修改的时候才会逐渐这种大而全的实现的缺点。

## 02 霰弹式修改

当一个类进行了修改会导致很多其他类也需要相应进行修改，我们称为“霰弹式修改”。

**为什么霰弹式修改是一种坏味道？**

1. 当出现霰弹式修改的时候，容易造成修改上的遗漏，因此需要多次编译、运行测试、测试功能才有可能完全修改，虽然有的问题编译的时候就可以发现已经很快了，但是反复的编译本来也是不断花费时间的，久而久之也是一种重复低效的。
2. 不难发现一个类的变化导致其他类相应的变化，这是一种强耦合的表现。

**如何解决霰弹式修改这种坏味道？**

既然霰弹式修改是一种耦合性的表现，我们可以将相关的代码通过 Move Field （移动属性）和 Move Method （移动方法）两种重构手段将代码移动到一个类中。这样做的好处是让变化的内容聚集到了，有助于简化后续的修改。

如果因为上面的操作类中添加了某些方法导致一个类有了多个职责，那么可以在进一步通过 Extract Method（提炼函数）来拆分职责。

也可以创建代理类或者方法重载来来解决特定的霰弹式修改导致的问题。

### 03 平行继承体系（Parallel Inheritance Hierarchies）

平行继承体系指：当一个类增加 1 个子类的时候，另外一个类也需要增加被迫增加一个子类。

例如：

<img src="https://pic3.zhimg.com/v2-265467078f3e06634004c2111620180e_b.jpg" data-caption="" data-size="normal" data-rawwidth="1719" data-rawheight="919" class="origin_image zh-lightbox-thumb" width="1719" data-original="https://pic3.zhimg.com/v2-265467078f3e06634004c2111620180e_r.jpg"/>



当添加 XXXVIPTaskService 的时候就会需要新增出新的 XXXVIPScoreService 。

**为什么平行继承体系是一种代码坏味道？**

1. 显而易见虽然没有直接关联，但是两者是同时产生并存的，但是两者的关联性并不显性的呈现，而是在 GradeService 中才体现出来。
2. 这样的实现容易导致在 GradeService 中 Switch 语句的产生，switch 语句本身就是一种重复的体现。关于Switch 语句的问题可以参考：[识别代码中的坏味道（一）](https://zhuanlan.zhihu.com/p/141435233)

**如何解决平行继承体系这种代码坏味道？**

围绕上面说的原因可以做出如下两步重构：

1. 建立直接引用。即 SVIPTaskService 直接引用 SVIPScoreService。
2. 参考[《Java有限状态机的4种实现对比》](https://zhuanlan.zhihu.com/p/97442825)消除继承体系，这里过程可以使用Move Field 和 Move Method 等重构手法。

通过上面的重构，隐形的关联变成直接引用。另外避免了 Switch 语句的问题。

## 04 依恋情结

刚开始接触代码中的坏味道时，乍一看你可能会觉得有些费解。其实它描述的问题却是很简单的，就是：一个类多次调用另外一个类的方法来获取最终的结果。如下

```java
public class OrderService {

        public List<Order> findAllOrders() {
                ...
        }

        public Order findLatestOrder(List<Order> orders) {
                ...
        }

        public Order addProduct(Order order, Product product) {
                ...
        }

}

public class CartService {
    ...

    public void addProduct(Product product) {
        ...
        List<Orders> orders = orderService.findAllOrders();
        Order order = orderService.findLatestOrder(orders);
        order = orderService.addProduct(product);
        ...
    }
}
```

再是不用考虑上面这段的代码业务上的合理性。代码中 CartService 中多次调用 OrderService 的方法，其目的就是执行最后的 addProduct() 方法，这就是一种依恋情结的代码。

**为什么依恋情结是代码坏味道？**

1. 仔细观察 CartService.addProduct() 方法不难发现那三行的代码的意图就是将 product 添加到最新的 order 中，如何实现将 product 添加到 product 这个目的，上面带代码显然展示了一种策略的具体实现。显然这种实现使得方法的职责不再单一。
2. 另外一个问题是，当 OrderService中的 findAllOrders()、findLatestOrder()、addProduct() 方法因为需求发生变动的时候，都有可能会牵连到 CartService 中的代码发生变化。因此上面中代码通过强耦合性虽然实现了功能，但是应对变化的能力也随之降低。代码是不断演进的，忽略了这种坏味道，会导致后续变化付出相应的代价。

**如何解决依恋情结这种代码坏味道？**

如果你看过上一篇内容或者看过上面前两个坏味道，那么应该也有一些思路了，如果一类在一个方法中多次依赖另外一个类，我们可以立即为有可能是职责没有划分划分明确的原因，可以通过一下手段进行重构：

1. 将多次产生调用的几行代码使用 Extract Method（提炼函数）提炼为一个新的函数，并通过名称来解释这几个行代码所要表达的意思。
2. 接下来可以使用 Move Method （搬移函数）将刚刚提炼的函数放置到一个更合适的类中，可以是刚刚被调用的类中，也可以创建新的类。

通过上面简单两步，我们可以将后续变化影响的范围变小，OrderService 内的变化将不再容易牵连到 CartService。

## 05 数据泥球

数据泥球指的是：多个类/方法参数中都有相同的属性，且这些相同的属性的业务意义也是相同的。

**为什么数据泥球是代码坏味道？**

很显然这是一种重复的表现。数据泥球容易造成如下问题：

1. 涉及到属性的调整，容易造成遗漏，需要多次调整。
2. 降低阅读代码的效率，因为每次都需要从类中识别出有几个属性是相关的在表达一个意思。
3. 随着代码的增加容易导致多大的类、长函数等多种坏味道。

**如何解决数据泥球这种代码坏味道？**

1. 如果类中的字段出现了数据泥球，对于这些重复的字段可以使用 Extract Class（ 提炼类） 将关联几个属性提炼到一个类中，赋予它一个业务的概念。
2. 如果是多个方法参数中出现了多个重复的多个参数，可以通过 Introduce Parameter Object（引入参数对象）将多个参数使用对象来代替，从而有效的减少重复和参数个数。
3. 其中 2 的另外一种情况，如何调用者先通过一些逻辑生成几个变量，再将这几个变量通过参数传递给调用的方法，那么可以使用 Presere Whole Object（保持对象完整），将变量生成提炼到一个函数中，并并取消参数的传递，而是在被调用的方法中直接调用原本要传递的参数。

## 06 基本类型偏执

描述的是这样一种代码实现方式：经常使用基本数据类型，而不愿意使用对象将这些基本数据类型和其行为进行封装。

**为什么基本类型偏执是代码坏味道？**

首先基本类型有其作用。问题出现在不做场景区分场景，所有场景都是用基本数据类型去搭建业务逻辑。

问题往往出现在这种场景：

> 几个基本数据类型共同表达意思概念，但是实现方式却是像搭积木一样，将逻辑一步步的拼接搭建起来，最终得到期望的结果。

这种实现的方式的问题就在于日后阅读代码的时候每次阅读都需要从头到位梳理一遍，才能清楚的其表达的意思，时间消耗有的是几秒钟，有的是几分钟，但是堆积读几次将会累积消耗更多的阅读时间。问题就出现在不够直白的揭示意图。

> 使用几个基本数据类型表示不同的类型，即所谓的 Type Code。

这种代码也是存在可读性的问题，而且非常容易导致 switch 语句的坏味道。

因此，并不是不能使用基本数据类型，而是应该在揭示某个业务意图的时候适当的使用封装，将多个基本数据类型封装到一个类中。从而通过对象直白的表达意图。

**如何解决基本类型偏执这种代码坏味道？**

1. 通过 Extract Method （提炼函数）将几个基本数据类型拼接的逻辑提炼为一个方法，比通过方法名来解释意图。
2. 如果按照1做了，发现类中出现不应该出现的职责，那么就可以将几个相关的基本数据类型通过 Extract Class（提炼类）将几个基本数据类型提炼为一个类来表达一个概念，然后通过 Move Method 来讲相关的操作挪动到该类中。
3. 如果使用基本数据类型来表示状态，可以选择使用 Replace Type Code with Class（以类取代类型码），并将相关的操作移动到类中，避免 Switch 语句。场景可以参考[《Java有限状态机的4种实现对比》](https://zhuanlan.zhihu.com/p/97442825)

## 07 冗赘类（Lacy Class）

这是单一职责的一个极端表现，即拆分了很多类，每个类的职责过度单一。

**为什么冗赘类是一种代码坏味道？**

因为每个类都是有阅读成本低的，职责拆分的过细，意味着多个关联性强的职责也被拆分了，因此阅读代码来成本不一定提升，反而因为过分的分散而导致理解起来需要会非常费劲。

**如何解决冗赘类这种代码坏味道？**

这个坏味道也给开发者一个提醒，极端的追求某些原则同样会导致不必要的麻烦，因此需要通过不断的练习和思考来获取平衡的这种点。

代码中一旦遇到职责过度拆分的情况就可以通过 Inline Class 或者 Collapse Hierarchy 来删除一些类，将概念合并到一个类中。

当代码更多的是处理业务逻辑的时候，那么其中的类应该像领域语言靠近，尽量避免凭空制造一些概念，拆分职责的时候和业务相结合更有利于我们将代码写的简单易读。

## 08 过度耦合的消息链

这种代码味道值得是不断从获取到的对象的子对象，导致很长的调用链。

例如

```java
public class User {
        ...
        private Address address;
        ...
}

public class Address {
        ...
        private City city;
        ...
}

public class City {
        ...
        private PostCode postCode;
        ...
}

public class PostCode {
        ...
        private String code;
        ...
}
```

多度耦合的消息链代码如下

```java
String postCode = user.getAddress()
                                            .getCity()
                                            .getPostCode()
                                            .getCode();
```

**为什么过度耦合的消息链是一种代码坏味道？**

1. 上面的实现虽然能够正常运行，但是会导致类之间的耦合，即 User 类的调用者需要在自己的内部来获得没有直接练习的 postCode 的实现；
2. 降低了可读性。将整个消息链读完之后才能知道得到了什么，而这个过程的很多很多消息链中的信息是我们并不需要知道的。

**如何解决过度耦合的消息链这种代码坏味道？**

可以通过 Extract Method 来提炼函数，然后 通过 Move Method 来将提炼的方法移动到合适的位置。

如果读过《重构》还会提到 Hide Delegate（隐藏代理关系）的重构手法。不过不推荐使用，因为它引入多个 Middle Man 这种实现，当消息链过长的时候，这是一个有工作量且重复的工作，另外增加了很多很多耦合性的方法。

因此可以有限照顾可读性，通过 Extract Method 和 Move Method 来进行重构，从而获取实现和维护性上的平衡。

## 09 异曲同工的类

即两个类做的同一件事或者同一类事。这种代码很常见，比如两个开发者同时执行自己的开发工作，创建了功能类似但是方法不同的类，Code Review 的时候很容易发现这种代码。

**为什么异曲同工的类是一种代码坏味道？**

按照上面的描述，如果保留两个职责类似的类会有什么不好？

1. 后续调用实现类时会导致选择上的疑虑，两个类应该选择用哪个，而疑虑之下就是时间的浪费。
2. 添加代码的时候，只向其中一个类中添加了逻辑，后续调用时 就会困扰调用者，而且容易导致两个类中容易出现重复的代码。

异曲同工的类是后续很多坏味道的开始。

**如何解决异曲同工的类这种代码坏味道？**

1. 一般情况，如果两个类是一般的工具类，可以选择使用Renove Method 和 Move Method 将类的职责描述清楚，并将相关的代码移动到一个类中，完成两个类的合并。
2. 如果两个类存并非普通的工具类而是存在一定的继承关系，可以采用 Extract SuperClass （提炼超类）。

当遇到代码中的坏味道的时候，请避免延迟决策和延迟解决，因为它很可能后续导致其他的坏味道。及时个人意识到可以延迟决策但是放在团队中会可能在这个地方重复遇到问题，导致后续坏味道不断被扩散。一次一旦遇到类似的坏味道可以遵守“童子军军规”：让营地比你来的时候更干净！

## 10 纯数据类

纯数据类指的是：一个类中只有属性和这些属性所涉及到的 getter、setter。

**为什么纯数据类是一种代码坏味道？**

纯数据类有其使用场景，比如 DTO 经常这种贫血模型。但是如果结合业务到的纯数据类频繁出现，那可不是什么好的事情，因为操作这个类中属性的方法将会散落在各个类中，即存在者多处强耦合。

**如何解决纯数据类这种代码坏味道？**

建议使用充血模型，一个类中除了拥有属性也应该包含具有一定业务逻辑的行为。那么可以选择

1. Extract Method 将部分调用逻辑进行提炼，提炼成一定的方法；
2. 再使用 Move Method 将方法移动到类中，
3. 最后 Hide Method 删除纯出局类中的 getter 和 setter。

纯数据类有其使用场景，但是应该时刻注意到哪些场景下数据类会引入坏味道，一旦发现尽早解决。

作者：PageThinker
链接：https://zhuanlan.zhihu.com/p/141993156
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。



这四个代码坏味道是：

1. 中间人（Middle Man）
2. 狎昵关系
3. 不完美的库类
4. 被拒绝的遗赠

### 01 中间人（Middle Man）

在上一篇文章中 [《识别代码中的坏味道（二）》](https://zhuanlan.zhihu.com/p/141803738)中在“过度耦合的消息链”这种代码坏味道曾经提及过中间人（Middle Man）这种代码坏味道，那么中间人到底是一类什么代码呢？

中间人指的是一种过度使用委托的代码，《重构》中给了一个参考值，如果一个类中有一半的方法都委托给其他对象进行，

**为什么中间人是一种代码坏味道？**

过度使用委托。这意味着当需求发生某些的变化的时候，这个中间人的类总是被牵连进来一并修改。这种中间人代码越多，浪费掉的时间也就越多。

**如何解决中间人这种代码坏味道？**

中间人的代码在于过度使用和委托两点。因此解决中间人这种代码坏味道就应该从减少委托下手：

删除中间人的方法，可以使用 Remove Middle Man（移除中间人）这种重构技巧。

当然如果原有代码的代理类中并不怎么变化，也可以选择延迟重构，依照“事不过三，三则重构”的原则可以选择当发生变化的时候进行重构。

### 02 狎昵关系（Inappropriate Intimacy）

指的是类之间花费太多的时间去探究彼此的私有的属性或者方法。

造成狎昵关系的原因可能是：

1. 两个类本来就不应该拆分开；
2. 两个类之间存在双向关联；
3. 因为继承导致了狎昵关系；
   ...

**为什么狎昵关系是一种代码坏味道？**

1. 狎昵关系会导致强耦合的表现；
2. 而且类和类之间的职责将会变得模糊；
3. 会因为访问对方的私有信息而导致过多的操作出现，或者产生封装上的妥协，让两个类纠缠不清。

**如何解决狎妮关系这种代码坏味道？**

1. 通过 Move Field （搬移属性），Move Method（搬移方法）来移动属性和方法的位置，让属性和方法移动到它们本应该出现的位置。
2. 如果直接移动属性和方法并不合适，可以尝试使用 Extract Class（提炼类）看是否能够找到公共类。
3. 如果是因为相互调用导致的问题，可以尝试 Change Bidirectional Association to Unidirectional（将双向关联改为单向关联）尝试将关联关系划清。
4. 如果是因为继承导致狎昵关系，可以尝试移除继承关系，改用代理类来实现。

### 03 不完美的库类

当直接使用第三方库的时候，导致代码可读性变差、意图不明确的问题。

**为什么不完美的库类是一种代码坏味道？**

第三方类库提供的功能能够在很场景下被复用。但是放在业务场景下，却总是要从业务视角切换到单纯的技术视角来来使用某些第三方类库。

例如

```java
Date newStart = new Date(
                                    previousEnd.getYear(), 
                                    previousEnd.getMonth(), 
                                    previousEnd.getDate() + 1);
```

一眼看上去这是在表达什么意思其实并不容易看到。不完美的类库就在于造成代码中语意化变差。

**如何解决不完美库类这种代码坏味道？**

很多开发者会采用注释的方式期望让代码可读，但是这类注释本身也是一种代码的坏味道。不过可以借助函数名来揭示意图。

所以遇到上面例子的情况，可以使用 Extract Method 来提炼一个函数，生成如下代码

```java
Date newStart = nextDay(previousEnd);


...


private Date nextDay(Date previousEnd) {
        return new Date(
                            previousEnd.getYear(), 
                            previousEnd.getMonth(), 
                            previousEnd.getDate() + 1); 
}
```

这样调用 nextDay() 的地方，就可以轻松的知道获取到 previousEnd 日期的下一天日期。

如果一个类中存在多种这种调用，或者多个类中都有类似的函数的时候，提炼一个单独一个类，并通过这个类对外提供这些方法无疑是一种消除重复提高复用的办法。实现这个类的方式可以使用代理的方式，也可以使用继承的方式。如果一个类只是提供代理方法，具体实现都要委托给类库，这样情况下，不如使用继承来生成的子类，并在子类中添加那些可以复用的方法。重构的过程可以参考 Introduce Local Extension（引入本地扩展）。

很显然第三方类库被设计的出发点往往是好的，但是实际调用的时候除了享受这种快速实现的方式，还需要关注第三方类库给当前项目带来的一些坏味道，并着手解决这些问题。

### 04 拒绝的遗赠

这个坏味道指的是当子类继承基类的时候，父类的一些方法即使子类并不需要也被迫被继承的情况。出现这种坏味道的一般有两种原因：

1. 继承体系设计的不好，还需要调整；
2. 基类实现了某个接口，导致子类不需要的时候也会实现那个接口对应的方法。

详细的例子可以参考：[《重构分析21: 被拒绝的遗赠（Refused Bequest）》](https://zhuanlan.zhihu.com/p/98756702)

**为什么拒绝的遗赠是一种代码坏味道？**

这个坏味道主要原因就是继承带来的坏味道，子类被迫实现某些方法或者从父类继承的方法对自身不但没有帮助甚至造成误导，比如：代码中通过继承实现 正方形 继承 长方形并求面积的例子，感兴趣可以参考《敏捷软件开发原则、模式、实践》中的里氏替换原则。

**如何解决拒绝的遗赠的这种代码坏味道？**

有两种思路：

1. 改善继承体系。剔除子类不需要的方法，并创建子类的兄弟，通过 Move Method 将不需要的方法移动到兄弟类中，通过 Move Field 将涉及到非公共属性也移动到兄弟子类中。
2. 使用代理来取代继承。这种方式的修改只涉及到对子类的调整，影响范围较小，并且也不会因此而像第一种重构方法那样因为要维护继承体系而导致一些新概念的产生。同时还能避免因为基类继承了某个接口，而导致的子类被迫实现某些方法的情况。

### 总结

至此 22 种常见的代码坏味道已经介绍完成。关注工具、框架的同时花一部分精力关注代码质量，能够让项目随着时间不断演进。当然实际工作中遇到的坏味道往往比这 22 种还要多。

项目中我们可以使用 [Check Style](https://zhuanlan.zhihu.com/p/105583516)、[PMD](https://zhuanlan.zhihu.com/p/105585075)、[Arch Unit](https://zhuanlan.zhihu.com/p/107151861)帮助我们及时发现项目中的问题，但是更”软“的部分需要我们花精力来理解清楚是什么、为什么、怎么解决。

或许你也已经发现了，很多情况下坏味道的原因在于变化时，无法快速应对变化，有的是代码设计的问题，有的是可读性的问题。即使代码坏味道也分为强烈的坏味道和淡淡的坏味道，所以重构的原则也是”事不过三、三则重构“，因此面对代码坏味道的时候如果代码坏味道很淡我们可以延迟消除坏味道。如果坏味道已经很强烈，或者淡淡的坏味道因为频繁的变化而导致效率下降时，那就不如先解决这种坏味道。















1、多此一举型代码。

if(a > b){
   return true;
}else{
   return false;
}
也许一些经验不那么老道的开发会觉得这段代码没问题呀，可以跑得通，确实，在逻辑上是没问题的，但是有更简洁明了的写法为何不用？if() 里面的条件是boolean ，然后我们的返回值也是boolean，所以可以改写成

return a > b;


2、瞎命名型代码。

int a;
String wzbt; // 文章标题
String fastdi; //fast di 快递  。。中西结合...
以上只是不规范命名的实例的冰山一角，良好的命名除了见名知意以外，还可以在长时间以后回来阅读代码时，更快的回忆起业务逻辑，不至于在各种无解的命名中乱了手脚，为了一时的方便而随意命名是非常不值得的。

 

3、if完一定要加else型代码

if(condition){
   //dosm
}else{
   return ;
}

if(condition){
   //dosm
}else{
   throw new Exception();
}

while(xx){
    if(condition){
            //dosm
    }else{
            continue;    
    }
}
很多情况下，我们通过一些语句的前置类减少不必要的else，让代码看起来更简练清晰。

if(!condition){
   return ;
}
//dosm

if(!condition){
   throw new Exception();
}
//dosm


   4、复制粘贴型

举个例子，项目中A模块引入B模块的优惠券业务，此时C模块也要引入B模块的优惠券业务，由于此时的优惠券业务可能是B模块中的几行代码，很多人就为了贪图方便，直接复制这几行代码直接放到C模块了。so easy，代码完美运行。

看起来似乎又没什么毛病，此时程序员的天敌产品经理过来了，他说在要在优惠券逻辑前面加点限制条件，ok，那么此时就要改动A模块跟B模块2份代码，而且要保持一致性，这个需求就完成了。过了一个版本，D模块也要引用优惠券业务，此时你又愉快的复制过去，然后可爱的产品经理又过来跟你说，这个版本我们要砍掉前面的限制条件...这时候你就要同步三段代码...跟产品经理的一场大战估计在所难免了。 

所以从上面的案例中，如果我们一开始不偷懒把公共逻辑抽取出来，在各个模块引用的话，不论怎么修改，我们只要维护一份逻辑就可以，不至于手忙脚乱。

 

5、又长又臭型代码

此类坏味道代码一般出现在“有历史“的代码中，经过不同开发人员的迭代，一个方法可能会出现几千行的情况，即使有注释，也会让人看得痛不欲生，这时候刚接手修改的人必然会说一句“WTF”了。

所以这就要求我们在平时写代码的过程中养成提炼的习惯，一般来说，当某块业务逻辑需要注释来说明的时候，一般都可以提炼成方法来调用，通过这种方式会使得阅读代码的时候逻辑更加清晰。

还有一种又长又臭情况是出现在方法的参数中，不断的迭代过程也会导致参数的增加或者修改，甚至有看过朋友公司的代码出现一个方法10多个参数的情况。一般来说，当参数超过5个的时候就要考虑封装到对象当中了。

 

6、无病呻吟型

//输出info日志
logger.info("xxx");

//定义num变量
int num  = 0;
