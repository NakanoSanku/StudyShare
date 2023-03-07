# 3.7更新
```sh
CURRENT_IP=$(ifconfig |grep inet |grep broadcast |awk '{print $2}')
```
将ip获取方式更改为ifconfig以便适应无root设备

# 更新
安卓一键登录 将eth更换为wlan0即可，需root权限执行sh脚本
至于自动化自行解决，magisk 或者 tasker
# 更新
```sh
CURRENT_IP=$(ip addr | grep eth | grep inet | awk '{print $2}' |  cut -d "/" -f 1)

#linux

curl 'http://10.1.99.100:801/eportal/portal/login?callback=dr1003&login_method=1&user_account=你的账号@cmcc&user_password=你的密码&wlan_user_ip='$CURRENT_IP'&wlan_user_ipv6=&wlan_user_mac=000000000000&wlan_ac_ip=10.1.1.1&wlan_ac_name=&jsVersion=4.1.3&terminal_type=1&lang=zh-cn&v=2348&lang=zh'
```
只需替换你从网页抓取你的账号以及密码即可完成脚本编写，注意账号不完全等于你的学号！注意路由器部分固件可能不带curl！大坑！

直接跳到第九步开始看！！！

# -无锡学院校园网自动登录教程
准备工作： 拥有一台能够ssh访问的路由器 有一台电脑

第一步：下载并安装winscp 

第二步：用网线连接已经刷好机的路由器

第三步：打开winscp 新建会话 将文件协议改为scp 主机名输入你路由器后台的管理地址 账号密码为路由器后台管理员的账号密码 点击登录

第四步：点击打开终端，找不到的话按shift+ctrl+T 

第五步：输入命令ip addr并在输出的结果中找到有ip地址的那一“段”，划重点是整段一般为eth+数字的格式，然后记住这一段是eth几 

第六步：写第一行代码创建一个变量来存储你的ip地址 例如：`CURRENT_IP=$(ip addr | grep eth3 | grep inet | awk '{print $2}' |  cut -d "/" -f 1 )`

注：CURRENT_IP为变量名可以自定义，规则和c语言相同 后面的$(一段)是获取ip地址的命令

ip addr 为获取ip信息  grep的意思就是定位到带有这个字符串的地方，eth3和inet为特征字符串， awk '{print $2}'意思就是截取第二字符块 ，cut -d "/" -f 1 为将得到的字符块截出在"/"字符前的部分

我们要做的就是将eth3改为自己刚刚得到的eth几即可

第八步：输入第二行代码 #linux

第九步：打开浏览器注销你的校园网 按f12即打开开发者 点击Network(网络）勾选Preserve log （保存日志） 输入你的账号密码登录校园网
![QQ截图20221231124712.png](https://s2.loli.net/2022/12/31/54rqcHNW2tiDLIx.png)

第十步：点击日志里的login？callback 再点Headers 复制Request URL后面的那一段
```
http://10.1.99.100:801/eportal/portal/login?callback=dr1003&login_method=1&user_account=%2C0%2C你的账号%40unicom&user_password=你的密码&wlan_user_ip=你的ip地址&wlan_user_ipv6=&wlan_user_mac=000000000000&wlan_ac_ip=&wlan_ac_name=&jsVersion=4.1.3&terminal_type=1&lang=zh-cn&v=10107&lang=zh
```
你只需修改ip地址那一段（注意是在自己复制到的基础上修改！）将你的ip地址改为'$CURRENT_IP'

第十一步：继续写第三行代码curl '你第十步得到的代码行'

最后展示一下完整代码
```
CURRENT_IP=$(ip addr | grep eth3 | grep inet | awk '{print $2}' |  cut -d "/" -f 1 )

#linux

curl'http://10.1.99.100:801/eportal/portal/login?callback=dr1003&login_method=1&user_account=%2C0%2C你的账号%40unicom&user_password=你的密码&wlan_user_ip=你的ip地址&wlan_user_ipv6=&wlan_user_mac=000000000000&wlan_ac_ip=&wlan_ac_name=&jsVersion=4.1.3&terminal_type=1&lang=zh-cn&v=10107&lang=zh'
```

建议自己编写，不要在我的基础上修改，否则问题颇多，然后将编码格式改为UTF-8 ,后缀改为.sh，名字自取，英文！！！

第十二步：再次打开winscp，在你路由器的根目录下寻找etc文件夹 在其中寻找storage文件夹将刚刚编写好的sh文件复制进去

第十三步：再次打开终端,输入命令行 ： sh /etc/storage/auto.sh 

auto就是传进去的文件名

看到返回数字1 或者 2就代表成功了

然后在路由器中配置自动执行脚本即可
