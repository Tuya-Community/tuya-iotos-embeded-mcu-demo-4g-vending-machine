# Tuya IoTOS Embedded  MCU Demo 4G vending-Machine

[English](./README.md) | [中文](./README_zh.md)

## Introduction  

This Demo uses the Tuya smart cloud platform, Tuya smart APP, and IoTOS Embedded MCU SDK to realize a vending machine, which uses the Tuya 4G series module to realize automatic delivery and other intelligent functions.

The implemented features include:

+ Automatic shipment
+ Inventory statistics


## Quick start  

### Migration
+ [Get MCU SDK](https://developer.tuya.com/en/docs/iot/device-development/embedded-software-development/mcu-development-access/mcu-access-guide?id=K9hrbv1ub5owo#title-2-%E4%BA%A7%E5%93%81%E5%88%9B%E5%BB%BA)
+ [MCU SDK Migration](https://developer.tuya.com/en/docs/iot/device-development/embedded-software-development/mcu-development-access/wifi-mcu-sdk-solution/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9)

### Demo entry

Entry file：main.c

Important functions：main()

+ Initialize and configure MCU IO port, USART, timer, etc. All events are polled and judged in while(1)。




### DataPoint related

+ Issue DP point processing: dp_download_m_num_handle()

| function name | unsigned char dp_download_m_num_handle(const unsigned char value[], unsigned short length) |
| ------------- | ------------------------------------------------------------ |
| value[]       | receive data buffer                                          |
| length        | the length of buffer                                         |
| Return        | SUCCESS: Success ERROR: Failure                              |



### I/O List  

|  74HC595   |  74HC165   |   LED   | LZ201 CAT1 |
| :--------: | :--------: | :-----: | :--------: |
| PA7 INDATA |  PB13 PL   | PA1 LED |  PB10 TXD  |
|  PC5 OEN   |  PB12 CP   |         |  PB11RXD   |
|  PB0 LOCK  | PB14 ODATA |         | PC9 POWKEY |
| PB1 SHIFT  |            |         |            |



## Related Documents

  Tuya Demo Center: https://developer.tuya.com/demo/



## Technical Support

  You can get support for Tuya by using the following methods:

- Developer Center: https://developer.tuya.com
- Help Center: https://support.tuya.com/help
- Technical Support Work Order Center: [https://service.console.tuya.com](https://service.console.tuya.com/) 

