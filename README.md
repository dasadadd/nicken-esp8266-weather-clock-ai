# nicken ESP8266 联网天气时钟 + 真实AI模型调用

## 项目亮点
- ESP8266 实现 WiFi 联网 + 多传感器融合
- **真实外部AI模型落地**（设备主动调用 adviceslip API 生成天气建议）
- 多页面 OLED UI + 自动切换 + 稳定调试
- 可完整演示、可讲解，适合简历核心项目

## 功能列表
- NTP 网络对时 + DS3231 硬件RTC
- DHT11 实时温湿度
- Open-Meteo 天气API
- 4页OLED显示（时间/天气/WiFi/AI建议）
- AI建议页：结合本地传感器 + 外部AI模型生成动态建议

## 技术栈
- MCU：ESP8266 (Wemos D1 Mini)
- 语言：Arduino C++
- 库：U8g2、HTTPClient、ArduinoJson、RTClib、DHT
- 技能：I2C 通信、HTTP 请求、JSON 解析、UI 状态机、API 容错处理

## 硬件接线
详见下表（已验证）：

| 模块       | 引脚       | Wemos D1 Mini |
|------------|------------|---------------|
| OLED + DS3231 | SDA/SCL | D2 / D1      |
| DHT11      | DATA       | D4            |
| 电源       | VCC/GND    | 3.3V / GND    |

![硬件实物](https://github.com/dasadadd/nicken-esp8266-weather-clock-ai/blob/main/面包板实物照.jpg)

## 演示效果
（后续会补充B站视频）



欢迎交流与合作！
