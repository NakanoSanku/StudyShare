⚠️==**不算是完全无脑教程，禁止复制粘贴刷写分区相关命令，刷机不备份，救🐔两行泪，再次警告不对任何刷砖行为负责，教程大多都应用前人经验**==⚠️
## 工具准备
- 硬件: 
	- TTL转USB模块
	- 杜邦线若干
	- 排针若干
	- 路由器一台
	- 网线一根
	- Windows电脑一台
- 软件:
     - [SSCOM](http://www.viewprotech.com/upfile/2019/06/20190603155148_810.rar)
     - Windows开启SSH/Telnet功能
     - [MIWIFIRepairTool](https://bigota.miwifi.com/xiaoqiang/tools/MIWIFIRepairTool.x86.zip)
     - [Tftpd64](https://bitbucket.org/phjounin/tftpd64/downloads/Tftpd64-4.64-setup.exe)
     - [HxD.exe](https://github.com/lemoeo/AX6S/raw/main/%E5%B7%A5%E5%85%B7/HxD.zip)
     - 小米路由官方固件
	     [Redmi AX3000](https://cdn.cnbj1.fds.api.mi-img.com/xiaoqiang/rom/ra81/miwifi_ra81_firmware_2c953_1.0.62.bin)
	     [Xiaomi CR8806](https://cdn.cnbj1.fds.api.mi-img.com/xiaoqiang/rom/cr8806/miwifi_cr8806_firmware_4622b_6.2.33.bin)
	     [Xiaomi CR8809](https://cdn.cnbj1.fds.api.mi-img.com/xiaoqiang/rom/cr8809/miwifi_cr8809_firmware_46dab_6.2.136.bin)
> CR8808 当前为6.2.18版本，可与8806/8809通刷
## 刷机方法
### 进入TTL
教程参考链接:[恩山论坛大佬](https://www.right.com.cn/forum/forum.php?mod=viewthread&tid=8255711&highlight=ttl&mobile=2)
补充几点:
- 使用sscom替换参考教程中的putty，无需设置端口，选择自动发送，延迟500ms，方便中断官方救砖进入TTL
- TTL 接线 
>  GND ->目标烧录模块的GND即电源负极
>  
>  TXD  ->目标烧录模块的RXD
>  
>  RXD  ->目标烧录模块的TXD
>  
>  ==vcc不要接！！！==
>  
>  ![18165ab4e2ff226.jpg](https://s2.loli.net/2023/01/13/nm5ZOoNFHKQT48L.jpg)
- 进入TTL以后先修改环境变量，依次逐行输入以下命令
```
setenv boot_wait on
```

```
setenv uart_en 1
```

```
saveenv
```
以后进入TTL只需给路由器插电瞬间(5s内)，输入任意键即可
### tftp前提准备
参考链接:[恩山大佬进阶教程第三第四步](https://www.right.com.cn/FORUM/forum.php?mod=viewthread&tid=8255773&page=1#pid17537975)
简单说就是修改电脑网卡
- ipv4-> 192.168.31.100
- 子网掩码->255.255.255.0
- 
打开tftpd64选择192.168.31.100网卡
挂在后台即可
### 刷入openwrt(可选)
参考链接:[GitHub开源项目](https://github.com/hzyitc/openwrt-redmi-ax3000)
	1. 下载固件 此项目release中下载ubi结尾文件到tftpd64根目录下
	2. 输入命令
```
tftpboot openwrt-ipq50xx-generic-redmi_ax3000-squashfs-nand-factory.ubi
```

```
flash rootfs_1
```

```
setenv flag_try_sys2_failed 0
```

```
setenv flag_boot_rootfs 1
```

```
setenv flag_last_success 1
```

```
saveenv
```

```
reboot
```
等待重启，网口ipv4改为192.168.1.2即可进入openwrt后台192.168.1.1账户root无密码，在system>backup中备份bdata分区

### 开启SSH
如果上面没有刷入openwrt需要在TTL中备份bdata分区


操作为[这位大佬35楼所说](https://www.right.com.cn/forum/thread-8268392-1-1.html)

有兴趣可以自己研究uboot命令使用

将bdata分区上传云端进行备份⚠️

修改得到的bdata数据:[查看此教程第四步](https://post.m.smzdm.com/p/axzwv9w9/)

计算初始密码:[这里输入sn码即可，路由器背面查看](https://miwifi.dev/ssh)

使用官方刷机工具刷回官方

ttl链接路由，刷入bdata分区或者openwrt提供的ssh刷入

TTL参考教程[第5步](https://www.right.com.cn/FORUM/forum.php?mod=viewthread&tid=8255773&page=1#pid17537975)

将修改后的bdata.bin放到tftpd64根目录下，tftp入路由器，擦除bdata分区，再写入

⚠️不同固件，分区不同地址，大小，🈲止复制粘贴

使用ssh刷入参考:[此教程第五步](https://post.m.smzdm.com/p/axzwv9w9/)

只需传入bdata文件到tmp后刷入即可
```
mtd write /tmp/bdata bdata
```
然后输入`reboot`
### 使用Telnet开启ssh
使用Windows终端，Telnet 192.168.31.1连接

输入账号root

密码上面计算所得

输入passwd修改密码

复制粘贴以下代码(别问问就是我也不懂，大概就是设置环境变量，然后启用脚本每次开启时自动执行启用ssh)
```
nvram set ssh_en=1
nvram set telnet_en=1
nvram set uart_en=1
nvram set boot_wait=on
nvram commit
sed -i 's/channel=.*/channel="debug"/g' /etc/init.d/dropbear
/etc/init.d/dropbear restart
mkdir /data/auto_ssh
cd /data/auto_ssh
curl -O https://fastly.jsdelivr.net/gh/lemoeo/AX6S@main/auto_ssh.sh
chmod +x auto_ssh.sh
uci set firewall.auto_ssh=include
uci set firewall.auto_ssh.type='script'
uci set firewall.auto_ssh.path='/data/auto_ssh/auto_ssh.sh'
uci set firewall.auto_ssh.enabled='1'
uci commit firewall
uci set system.@system[0].timezone='CST-8'
uci set system.@system[0].webtimezone='CST-8'
uci set system.@system[0].timezoneindex='2.84'
uci commit
reboot
```
等待重启

此时ssh就开完了

Windows终端输入 
```

SSH root@192.168.31.1
```
输入密码即可

至于shellclash，以及ad啥的建议看[链接](https://www.right.com.cn/forum/forum.php?mod=viewthread&tid=8267066&extra=page%3D1&mobile=2)
真TM详细！
