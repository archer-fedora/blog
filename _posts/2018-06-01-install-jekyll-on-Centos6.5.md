---
layout: common
title: install ruby on Centos6.5
---


{{page.date|date_to_string}}


## install ruby on Centos6.5

### install ruby of new version

#### 1. install the develop tools first:

yum groupinstall "Development tools"


#### 2. remove old version

yum erase ruby ruby-libs ruby-mode ruby-rdoc ruby-irb ruby-ri ruby-docs


#### 3. install depend

yum -y install zlib-devel curl-devel openssl-devel httpd-devel apr-devel apr-util-devel mysql-devel


#### 4. download and install new ruby

wget https://cache.ruby-lang.org/pub/ruby/2.3/ruby-2.3.7.tar.gz
tar -zxvf https://cache.ruby-lang.org/pub/ruby/2.3/ruby-2.3.7.tar.gz
cd ruby-2.3.7

./configure  (it's better to use cmd "--prefix")
make
make install


#### 5. update gem's source

gem sources --remove https://rubygems.org/
gem sources -a http://mirrors.ustc.edu.cn/rubygems/
gem sources -u


#### 6. install the nodejs

rpm -ivh http://mirrors.zju.edu.cn/epel/6/i386/epel-release-6-8.noarch.rpm
yum update
yum install nodejs


ps:
if you want add the var of path, you can modify the profile like this:

vi ~/.bash_profile 
