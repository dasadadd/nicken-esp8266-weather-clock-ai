#include "ntp.h"
#include "serial.h"
#include "oled.h"

// 创建UDP和NTP客户端实例
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8 * 3600); // 使用阿里云NTP服务器，设置东八区

void ntpInit() {
    serialPrint("初始化NTP客户端...");
    timeClient.begin();
    serialPrint("NTP客户端初始化完成");
}

   //                获取时间            
String ntpGetTime() {
    timeClient.update();  // 更新时间
    
    // 获取时分秒
    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();
    int seconds = timeClient.getSeconds();
    
    // 格式化时间字符串 (HH:MM:SS)
     char timeStr[9];
    sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);//sprintf 的作用：把数据 “打印” 到字符串里，而不是打印到屏幕上，%02d 的含义：输出一个整数，如果不足 2 位，前面补 0
                                                               //sprintf 的作用：把数据 “打印” 到字符串里，而不是打印到屏幕上
    return String(timeStr);    
}
 
 //        获取日期
String ntpGetDate() {
    timeClient.update();  // 更新时间
    
   // 将epoch时间转换为日期  将 “从网络获取的时间戳（秒数）” 转换为 “人类可读的时间结构体（年月日时分秒）”。
    time_t epochTime = timeClient.getEpochTime();  
    
    //含义：获取 Unix 时间戳。timeClient.getEpochTime()：向 NTP 服务器询问时间，服务器返回一个巨大的整数。。
    //这个整数代表 从 1970 年 1 月 1 日 00:00:00 到现在经过了多少秒。
                                               
    struct tm *ptm = gmtime ((time_t *)&epochTime);   //含义：将 “秒数” 解析成 “时间结构体”。

    //gmtime：Greenwich Mean Time，将时间戳转换为 UTC 时间（世界标准时间，不带时区）
    //(time_t *)&epochTime：取 epochTime 的地址，并强制类型转换，传给函数。
    //struct tm *ptm：接收结果。ptm 现在指向一个结构体，里面包含了 tm_year, tm_mon, tm_mday, tm_hour 等字段。

    
    int year = ptm->tm_year + 1900;
    int month = ptm->tm_mon + 1;
    int day = ptm->tm_mday;
    
    // 格式化日期字符串 (YYYY-MM-DD)
    char dateStr[11];
    sprintf(dateStr, "%04d-%02d-%02d", year, month, day);
    return String(dateStr);
}

   //同步时间（需定期同步一次）  手动
   bool ntpSync() {
    serialPrint("正在同步网络时间...");
    oledShow(0, 16, "正在同步网络时间...");
    
    // 尝试强制更新时间
    if (timeClient.forceUpdate()) {
        serialPrint("时间同步成功");
        oledClear();
        oledShow(0, 16, "时间同步成功");
        oledShow(0, 32, "日期: " + ntpGetDate());
        oledShow(0, 48, "时间: " + ntpGetTime());
        return true;
    } else {
        serialPrint("时间同步失败");
        oledClear();
        oledShow(0, 16, "时间同步失败");
        return false;
    }
}
