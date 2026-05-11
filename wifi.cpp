#include "wifi.h"
#include "serial.h"

void wifiInit() {
    WiFi.mode(WIFI_STA);      // 设置为站点模式（作为客户端连接到路由器）
    WiFi.disconnect();        // 断开当前可能存在的连接 
    delay(100);              // 等待WiFi模块稳定，避免立即连接可能出现的问题
    serialPrint("WiFi模块初始化完成");
}

bool wifiConnect(const char* ssid, const char* password) {
    serialPrint("正在连接WiFi...");
    serialPrint("SSID: " + String(ssid));
    
    // 开始连接WiFi
    WiFi.begin(ssid, password);
    
    // 等待连接，最多等待20秒
    // 每秒检查一次连接状态，超时返回失败
    int attempts = 0;  //attempts设立值，表示只等待多少次
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(1000);  // 等待1秒
        serialPrint("等待连接..." + String(attempts + 1));
        attempts++;

        //WL_CONNECTED的意思是，如果连接成功返回的值
    }
    
    // 检查连接结果
    if (WiFi.status() == WL_CONNECTED) {
        serialPrint("WiFi连接成功");
        serialPrint("IP地址: " + WiFi.localIP().toString());
        return true;
    } else {
        serialPrint("WiFi连接失败");
        return false;
    }
}