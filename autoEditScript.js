"ui";
importClass(android.os.Build);
importClass(android.view.WindowManager);
showLoginUI();
let operator, user, password;
var color = "#6699ff";
//显示登录界面
function showLoginUI() {
  ui.layout(
    <frame>
      <vertical>
        <appbar bg="#6699ff">
          <toolbar id="toolbar" title="嘻专校园网一键登录脚本" />
        </appbar>
        <linear>
          <text w="56" gravity="center" color="#111111" size="16">
            学号
          </text>
          <input id="user" w="*" h="40" />
        </linear>
        <linear>
          <text w="56" gravity="center" color="#111111" size="16">
            密码
          </text>
          <input id="password" w="*" h="40" password="true" />
        </linear>
        <radiogroup margin="0 16">
          <radio id="cmcc" text="中国移动" />
          <radio id="unicom" text="中国联通" />
          <radio id="telecom" text="中国电信" />
          <radio id="wxxy" text="无锡学院" />
        </radiogroup>
        <linear gravity="center">
          <button id="saveAndroid" text="保存安卓脚本" />
          <button id="saveRouter" text="保存路由器脚本" />
        </linear>
        <linear gravity="center">
          <text text="脚本将保存在根目录下"></text>
          <text text="路径为/sdcard/auto.sh"></text>
        </linear>
        <button id="star" text="star my github" />
      </vertical>
    </frame>
  );

  ui.saveAndroid.on("click", () => {
    if (save()) {
      let template =
        "CURRENT_IP=$(ifconfig | grep inet |grep Bcast | awk '{print $2}')\n" +
        "curl  'http://10.1.99.100:801/eportal/portal/login?callback=dr1003&login_method=1&user_account=,1," +
        user +
        operator +
        "&user_password=" +
        password +
        "&wlan_user_ip='$CURRENT_IP'&wlan_user_ipv6=&wlan_user_mac=000000000000&wlan_ac_ip=&wlan_ac_name=&jsVersion=4.1.3&terminal_type=1&lang=zh-cn&v=6727&lang=zh'";
      files.write("/sdcard/auto.sh", template);
      toast("脚本已保存至根目录下,路径为" + "/sdcard/auto.sh");
      app.viewFile("/sdcard/auto.sh");
    } else {
      toast("请确认信息是否填写完毕");
    }
  });

  ui.saveRouter.on("click", () => {
    if (save()) {
      let template =
        "CURRENT_IP=$(ip addr | grep eth | grep inet | awk '{print $2}' | cut -d " /
          " -f 1)\n" +
        "curl  'http://10.1.99.100:801/eportal/portal/login?callback=dr1003&login_method=1&user_account=,1," +
        user +
        operator +
        "&user_password=" +
        password +
        "&wlan_user_ip='$CURRENT_IP'&wlan_user_ipv6=&wlan_user_mac=000000000000&wlan_ac_ip=&wlan_ac_name=&jsVersion=4.1.3&terminal_type=1&lang=zh-cn&v=6727&lang=zh'";
      files.write("/sdcard/auto.sh", template);
      toast("脚本已保存至根目录下,路径为" + "/sdcard/auto.sh");
      app.viewFile("/sdcard/auto.sh");
    } else {
      toast("请确认信息是否填写完毕");
    }
  });
}
//设置状态栏颜色
if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
  let window = activity.getWindow();
  window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
  window.setStatusBarColor(colors.parseColor(color));
  window.setNavigationBarColor(colors.parseColor("#FFFFFF"));
}

ui.star.on("click", () => {
  app.openUrl("https://github.com/NakanoSanku");
});

function save() {
  if (ui.cmcc.checked) {
    operator = "@cmcc";
  } else if (ui.unicom.checked) {
    operator = "@unicom";
  } else if (ui.telecom.checked) {
    operator = "@telecom";
  } else if (ui.wxxy.checked) {
    operator = "";
  } else {
    toast("请选择你的捍卫者!");
    return false;
  }
  if (ui.user.text() == "") {
    toast("请选择填写你的学号!");
    return false;
  }
  user = ui.user.text();
  if (ui.password.text() == "") {
    toast("请选择填写你的密码!");
    return false;
  }
  password = ui.password.text();
  return true;
}
