---
layout: post
title: Solve the 404 ERROR on github
category: github
tags: ruby, github, jekyll,404
description: fix the jekyll problem on github
---

 fix the jekyll problem on github

## Everything begin here

Today I try to push my blog to GitHub, but I find the files under "_post" folder can't be found, Github return 404 error. So I want to know why


### Find reason on internet

I have tried to find why on internet, there is some reason:

> 1. push the "_site" folder to Github.
> 2. the file under "_post" folder is named future date. 

but it's not the reason of my question.

I try to find the real address on Github, the addr is `"https://archer-fedora.github.io/2018/05/30/install-jekyll-on-Centos.html"` , 

from now on, it's ok, now I return the index page, the addr is `"https://archer-fedora.github.io/blog/"`, it's different!! 

I try to modify the addr to `"https://archer-fedora.github.io/blog/2018/05/30/install-jekyll-on-Centos.html"`, 

Get it! 

### Reason is the address is wrong.



### Fix the problem

I check the "_config.yml", the baseurl is set `"baseurl= /blog"`, I modify it to `"baseurl= /blog/"`

then I modify the index.md, the url add the baseurl prefix, push it to GitHub, It runs correct.




