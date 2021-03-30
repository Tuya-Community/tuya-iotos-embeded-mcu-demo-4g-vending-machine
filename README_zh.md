# Tuya IoTOS Embedded  MCU Demo 4G Evending-Machine

[English](./README.md) | [中文](./README_zh.md)

## 简介 

本Demo通过涂鸦智能云平台、涂鸦智能APP、IoTOS Embeded MCU SDK实现一款自动售货机，使用涂鸦4G系列模组，实现自动出货等智能化功能。

已实现功能包括：

+ 自动出货

+ 库存统计


## 快速上手 

### 移植
+ [MCU SDK获取](https://developer.tuya.com/cn/docs/iot/device-development/embedded-software-development/mcu-development-access/mcu-access-guide?id=K9hrbv1ub5owo#title-2-%E4%BA%A7%E5%93%81%E5%88%9B%E5%BB%BA)
+ [MCU SDK移植](https://developer.tuya.com/cn/docs/iot/device-development/embedded-software-development/mcu-development-access/wifi-mcu-sdk-solution/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9)

### Demo入口

入口文件：main.c

重要函数：main()

+ 对mcu的IO口，USART，定时器等进行初始化配置，所有事件在while(1)中轮询判断。




### DP点相关

+ 下发dp点处理: dp_download_m_num_handle()

| 函数名  | unsigned char dp_download_m_num_handle(const unsigned char value[], unsigned short length) |
| ------- | ------------------------------------------------------------ |
| value[] | 接收到的数据缓冲区                                           |
| length  | 接收到数据的长度                                             |
| Return  | SUCCESS: 成功  ERROR: 失败                                   |



### I/O 列表 

|  74HC595   |  74HC165   |   LED   | LZ201 CAT1 |
| :--------: | :--------: | :-----: | :--------: |
| PA7 INDATA |  PB13 PL   | PA1 LED |  PB10 TXD  |
|  PC5 OEN   |  PB12 CP   |         |  PB11RXD   |
|  PB0 LOCK  | PB14 ODATA |         | PC9 POWKEY |
| PB1 SHIFT  |            |         |            |



## 相关文档

涂鸦Demo中心：https://developer.tuya.com/demo/



## 技术支持

您可以通过以下方法获得涂鸦的支持:

- 开发者中心：https://developer.tuya.com
- 帮助中心: https://support.tuya.com/help
- 技术支持工单中心: [https://service.console.tuya.com](https://service.console.tuya.com/) 
