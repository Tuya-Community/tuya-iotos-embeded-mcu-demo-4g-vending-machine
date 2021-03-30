/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.h
 * @author  涂鸦综合协议开发组
 * @version v1.0.0
 * @date    2020.12.25
 * @brief   用户需要主动调用的函数都在该文件内
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

#ifndef __MCU_API_H_
#define __MCU_API_H_

#include "tuya_type.h"
#include "protocol.h"

#ifdef MCU_API_GLOBAL
  #define MCU_API_EXTERN
#else
  #define MCU_API_EXTERN   extern
#endif

/**
 * @brief  hex转bcd
 * @param[in] {Value_H} 高字节
 * @param[in] {Value_L} 低字节
 * @return 转换完成后数据
 */
u8 hex_to_bcd(u8 Value_H,u8 Value_L);

/**
 * @brief  求字符串长度
 * @param[in] {str} 字符串地址
 * @return 数据长度
 */
u32 my_strlen(u8 *str);

/**
 * @brief  把src所指内存区域的前count个字节设置成字符c
 * @param[out] {src} 待设置的内存首地址
 * @param[in] {ch} 设置的字符
 * @param[in] {count} 设置的内存长度
 * @return 待设置的内存首地址
 */
void *my_memset(void *src,u8 ch,u16 count);

/**
 * @brief  内存拷贝
 * @param[out] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {count} 拷贝数据个数
 * @return 数据处理完后的源地址
 */
void *my_memcpy(void *dest, const void *src, u16 count);

/**
 * @brief  字符串拷贝
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @return 数据处理完后的源地址
 */
i8 *my_strcpy(i8 *dest, const i8 *src);

/**
 * @brief  字符串比较
 * @param[in] {s1} 字符串 1
 * @param[in] {s2} 字符串 2
 * @return 大小比较值
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
i32 my_strcmp(i8 *s1 , i8 *s2);

/**
 * @brief  将int类型拆分四个字节
 * @param[in] {number} 4字节原数据
 * @param[out] {value} 处理完成后4字节数据
 * @return Null
 */
void int_to_byte(u32 number,u8 value[4]);

/**
 * @brief  将4字节合并为1个32bit变量
 * @param[in] {value} 4字节数组
 * @return 合并完成后的32bit变量
 */
u32 byte_to_int(const u8 value[4]);

/**
 * @brief  raw型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_raw_update(u8 dpid,const u8 value[],u16 len);

/**
 * @brief  bool型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_bool_update(u8 dpid,u8 value);

/**
 * @brief  value型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_value_update(u8 dpid,u32 value);

/**
 * @brief  string型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_string_update(u8 dpid,const u8 value[],u16 len);

/**
 * @brief  enum型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_enum_update(u8 dpid,u8 value);

/**
 * @brief  fault型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_fault_update(u8 dpid,u32 value);

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  raw型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_raw_update_syn(u8 dpid,const u8 value[],u16 len);

/**
 * @brief  bool型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_bool_update_syn(u8 dpid,u8 value);

/**
 * @brief  value型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_value_update_syn(u8 dpid,u32 value);

/**
 * @brief  string型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_string_update_syn(u8 dpid,const u8 value[],u16 len);

/**
 * @brief  enum型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_enum_update_syn(u8 dpid,u8 value);

/**
 * @brief  fault型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_fault_update_syn(u8 dpid,u32 value);
#endif

/**
 * @brief  mcu获取bool型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u8 mcu_get_dp_download_bool(const u8 value[],u16 len);

/**
 * @brief  mcu获取enum型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u8 mcu_get_dp_download_enum(const u8 value[],u16 len);

/**
 * @brief  mcu获取value型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u32 mcu_get_dp_download_value(const u8 value[],u16 len);

/**
 * @brief  串口接收数据暂存处理
 * @param[in] {value} 串口收到的1字节数据
 * @return Null
 * @note   在MCU串口处理函数中调用该函数,并将接收到的数据作为参数传入
 */
void uart_receive_input(u8 value);

/**
 * @brief  串口接收多个字节数据暂存处理
 * @param[in] {value} 串口要接收的数据的源地址
 * @param[in] {data_len} 串口要接收的数据的数据长度
 * @return Null
 * @note   如需要支持一次多字节缓存，可调用该函数
 */
void uart_receive_buff_input(u8 value[], u16 data_len);

/**
 * @brief  蜂窝设备串口数据处理服务
 * @param  Null
 * @return Null
 * @note   在MCU主函数while循环中调用该函数
 */
void cellular_uart_service(void);

/**
 * @brief  协议串口初始化函数
 * @param  Null
 * @return Null
 * @note   在MCU初始化代码中调用该函数
 */
void cellular_protocol_init(void);

#ifndef CELLULAR_CONTROL_SELF_MODE
/**
 * @brief  MCU获取复位蜂窝设备成功标志
 * @param  Null
 * @return 复位标志
 * -           0(RESET_CELLULAR_ERROR):失败
 * -           1(RESET_CELLULAR_SUCCESS):成功
 * @note   1:MCU主动调用mcu_reset_cellular()后调用该函数获取复位状态
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
u8 mcu_get_reset_cellular_flag(void);

/**
 * @brief  MCU主动重置蜂窝设备激活状态
 * @param  Null
 * @return Null
 * @note   1:MCU主动调用,通过mcu_get_reset_celluluar_flag()函数获取重置蜂窝设备是否成功
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
void mcu_reset_cellular(void);

/**
 * @brief  获取设置蜂窝设备工作模式状态成功标志
 * @param  Null
 * @return 蜂窝mode flag
 * -           0(SET_CELLULARCONFIG_ERROR):失败
 * -           1(SET_CELLULARCONFIG_SUCCESS):成功
 * @note   1:MCU主动调用mcu_set_cellular_mode()后调用该函数获取复位状态
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
u8 mcu_get_cellular_mode_flag(void);

/**
 * @brief  MCU设置蜂窝设备工作模式
 * @param[in] {mode} 进入的模式
 * @ref        1:全功能模式
 * @ref        4:飞行模式
 * @return Null
 * @note   1:MCU主动调用
 *         2:成功后,可判断set_cellularmode_flag是否为TRUE;TRUE表示为设置工作模式成功
 *         3:如果为模块自处理模式,MCU无须调用该函数
 */
void mcu_set_cellular_mode(u8 mode);

/**
 * @brief  MCU主动获取当前蜂窝设备工作状态
 * @param  Null
 * @return cellular work state
 * -          0: SIM卡未连接
 * -          1: 搜索网络中
 * -          2: 已成功注册未联网
 * -          3: 联网成功并获取到IP
 * -          4: 已连接到云端
 * -          0xff: 未知状态
 * @note   如果为模块自处理模式,MCU无须调用该函数
 */
u8 mcu_get_cellular_work_state(void);
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU获取格林时间
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_green_time(void);
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU获取系统时间,用于校对本地时钟
 * @param  Null
 * @return Null
 * @note   MCU主动调用完成后在mcu_write_rtctime函数内校对rtc时钟
 */
void mcu_get_system_time(void);
#endif

#ifdef CELLULAR_HEARTSTOP_ENABLE
/**
 * @brief  通知蜂窝模组关闭心跳
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void cellular_heart_stop(void);
#endif

#ifdef GET_CELLULAR_STATUS_ENABLE
/**
 * @brief  获取当前蜂窝模组联网状态
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_cellular_connect_status(void);
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取模块MAC
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_module_mac(void);
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取 蜂窝设备 模块剩余内存
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_module_remain_memory(void);
#endif

#ifdef GET_CELLULAR_RSSI_ENABLE
/**
 * @brief  获取当前蜂窝设备信号强度
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_cellular_rssi(void);
#endif

#ifdef CELLULAR_SERVICE_ENABLE
/**
 * @brief  获取蜂窝设备的工作模式
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_cellular_work_mode(void);

/**
 * @brief  获取国际移动用户识别码
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_IMSI(void);

/**
 * @brief  获取 SIM 卡识别码
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_IMCI(void);

/**
 * @brief  获取设备 IMEI
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_IMEI(void);



#ifdef GNSS_SERIVCE_ENABLE
/**
 * @brief   通过模组获取到经纬度信息
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_gnss_location(void);
/**
 * @brief  通过模组获取到当前设备的速度
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_gnss_speed(void);
/**
 * @brief  通过模组获取的当前的GNSS设备的信号强度
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_gnss_rssi(void);

/**
 * @brief  控制GNSS设备，启动、关闭，以及定位跟踪模式（GPS+BD是默认的）
 * @param  [in] {enable} true:启动,false:关闭
 * @param  [in] {mode} GNSS 定位跟踪模式
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_control_gnss(bool_t enable,GNSS_ATTACH_MODE_e mode);

/**
 * @brief  复位 GNSS 设备
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_reset_gnss(u8 pin,bool_t level);

/**
 * @brief  启动或者关闭WIFI定位
 * @param  [in] {enable} true:启动,false:停止
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_control_wifi_location(bool_t enable);

#endif

#endif

#endif
