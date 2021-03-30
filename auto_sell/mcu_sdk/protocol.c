/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.c
 * @author  涂鸦综合协议开发组
 * @version v1.0.0
 * @date    2020.12.25
 * @brief
 *                       *******非常重要，一定要看哦！！！********
 *          1. 用户在此文件中实现数据下发/上报功能
 *          2. DP的ID/TYPE及数据处理函数都需要用户按照实际定义实现
 *          3. 当开始某些宏定义后需要用户实现代码的函数内部有#err提示,完成函数后请删除该#err
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

/******************************************************************************
                                移植须知:
1:MCU必须在while中直接调用mcu_api.c内的cellular_uart_service()函数
2:程序正常初始化完成后,建议不进行关串口中断,如必须关中断,关中断时间必须短,关中断会引起串口数据包丢失
3:请勿在中断/定时器中断内调用上报函数
******************************************************************************/

#include "cellular.h"
#include "usart.h"
#include "IO.h"

#ifdef WEATHER_ENABLE
/**
 * @var    weather_choose
 * @brief  天气数据参数选择数组
 * @note   用户可以自定义需要的参数，注释或者取消注释即可，注意更改
 */
const i8 *weather_choose[WEATHER_CHOOSE_CNT] = {
    "temp",
    "humidity",
    "condition",
    "pm25",
    /*"pressure",
    "realFeel",
    "uvi",
    "tips",
    "windDir",
    "windLevel",
    "windSpeed",
    "sunRise",
    "sunSet",
    "aqi",
    "so2 ",
    "rank",
    "pm10",
    "o3",
    "no2",
    "co",
    "conditionNum",*/
};
#endif


/******************************************************************************
                              第一步:初始化
1:在需要使用到cellular相关文件的文件中include cellular.h"
2:在MCU初始化中调用mcu_api.c文件中的cellular_protocol_init()函数
3:将MCU串口单字节发送函数填入protocol.c文件中uart_transmit_output函数内,并删除#error
4:在MCU串口接收函数中调用mcu_api.c文件内的uart_receive_input函数,并将接收到的字节作为参数传入
5:单片机进入while循环后调用mcu_api.c文件内的cellular_uart_service()函数
******************************************************************************/

/******************************************************************************
                        1:dp数据点序列类型对照表
          **此为自动生成代码,如在开发平台有相关修改请重新下载MCU_SDK**
******************************************************************************/
const DOWNLOAD_CMD_S download_cmd[] =
{
  {DPID_M_NUM, DP_TYPE_RAW},
  {DPID_R_NUM, DP_TYPE_RAW},
};



/******************************************************************************
                           2:串口单字节发送函数
请将MCU串口发送函数填入该函数内,并将接收到的数据作为参数传入串口发送函数
******************************************************************************/

/**
 * @brief  串口发送数据
 * @param[in] {value} 串口要发送的1字节数据
 * @return Null
 */
void uart_transmit_output(u8 value)
{
    //cai#error "请将MCU串口发送函数填入该函数,并删除该行"
	Uart3_PutChar(value);
/*
    //Example:
    extern void Uart_PutChar(u8 value);
    Uart_PutChar(value);                                    //串口发送函数
*/
}

/******************************************************************************
                           第二步:实现具体用户函数
1:APP下发数据处理
2:数据上报处理
******************************************************************************/

/******************************************************************************
                            1:所有数据上报处理
当前函数处理全部数据上报(包括可下发/可上报和只上报)
  需要用户按照实际情况实现:
  1:需要实现可下发/可上报数据点上报
  2:需要实现只上报数据点上报
此函数为MCU内部必须调用
用户也可调用此函数实现全部数据上报
******************************************************************************/

//自动化生成数据上报函数

/**
 * @brief  系统所有dp点信息上传,实现APP和muc数据同步
 * @param  Null
 * @return Null
 * @note   此函数SDK内部需调用，MCU必须实现该函数内数据上报功能，包括只上报和可上报可下发型数据
 */
void all_data_update(void)
{
    //cai#error "请在此处理可下发可上报数据及只上报数据示例,处理完成后删除该行"

    /*
    //此代码为平台自动生成，请按照实际数据修改每个可下发可上报函数和只上报函数
    mcu_dp_raw_update(DPID_R_NUM,当前库存情况指针,当前库存情况数据长度); //RAW型数据上报;

    */
}


/******************************************************************************
                                WARNING!!!
                            2:所有数据上报处理
自动化代码模板函数,具体请用户自行实现数据处理
******************************************************************************/
/*****************************************************************************
函数名称 : dp_download_m_num_handle
功能描述 : 针对DPID_M_NUM的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 只下发类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_m_num_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为RAW
    unsigned char ret;
		const unsigned char error[6]={"ERROR1"};
    /*
    //RAW类型数据处理
    
    */
		if((length==6)&&(value[0]<11)&&(value[1]<10))
		{
			IoT_receive[Q_U3.rear].data[0]=value[0];
			IoT_receive[Q_U3.rear].data[1]=value[1];
			IoT_receive[Q_U3.rear].data[2]=value[2];
			IoT_receive[Q_U3.rear].data[3]=value[3];
			IoT_receive[Q_U3.rear].data[4]=value[4];
			IoT_receive[Q_U3.rear].data[5]=value[5];
			F_TASK_MOTOR_OPEN++;
			rear_inc(&Q_U3);
		}
		else
		{
			mcu_dp_raw_update(DPID_R_NUM,error,6);
		}
    //处理完DP数据后应有反馈
    ret = mcu_dp_raw_update(DPID_M_NUM,value,length);
		//mcu_dp_raw_update(DPID_R_NUM,IoT_receive,length);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}




/******************************************************************************
                                WARNING!!!
此部分函数用户请勿修改!!
******************************************************************************/

/**
 * @brief  dp下发处理函数
 * @param[in] {dpid} dpid 序号
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {length} dp数据长度
 * @return dp处理结果
 * -           0(ERROR): 失败
 * -           1(SUCCESS): 成功
 * @note   该函数用户不能修改
 */
u8 dp_download_handle(u8 dpid,const u8 value[], u16 length)
{
    /*********************************
    当前函数处理可下发/可上报数据调用
    具体函数内需要实现下发数据处理
    完成用需要将处理结果反馈至APP端,否则APP会认为下发失败
    ***********************************/
    u8 ret;
    switch(dpid) {
        case DPID_M_NUM:
            //货物号处理函数
            ret = dp_download_m_num_handle(value,length);
        break;


        default:
        break;
    }
    return ret;
}

/**
 * @brief  获取所有dp命令总和
 * @param[in] Null
 * @return 下发命令总和
 * @note   该函数用户不能修改
 */
u8 get_download_cmd_total(void)
{
    return(sizeof(download_cmd) / sizeof(download_cmd[0]));
}


/******************************************************************************
                                WARNING!!!
此代码为SDK内部调用,请按照实际dp数据实现函数内部数据
******************************************************************************/

#ifdef SUPPORT_MCU_FIRM_UPDATE
/**
 * @brief  升级包大小选择
 * @param[in] {package_sz} 升级包大小
 * @ref           0x00: 256byte (默认)
 * @ref           0x01: 512byte
 * @ref           0x02: 1024byte
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void upgrade_package_choose(u8 package_sz)
{
    #error "请自行实现请自行实现升级包大小选择代码,完成后请删除该行"
    u16 send_len = 0;
    send_len = set_cellular_uart_byte(send_len, package_sz);
    cellular_uart_write_frame(UPDATE_START_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  MCU进入固件升级模式
 * @param[in] {value} 固件缓冲区
 * @param[in] {position} 当前数据包在于固件位置
 * @param[in] {length} 当前固件包长度(固件包长度为0时,表示固件包发送完成)
 * @return Null
 * @note   MCU需要自行实现该功能
 */
u8 mcu_firm_update_handle(const u8 value[],u32 position,u16 length)
{
    #error "请自行完成MCU固件升级代码,完成后请删除该行"
    if(length == 0) {
        //固件数据发送完成

    }else {
        //固件数据处理

    }

    return SUCCESS;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  获取到的格林时间
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_greentime(u8 time[])
{
    #error "请自行完成相关代码,并删除该行"
    /*
    time[0] 为是否获取时间成功标志，为 0 表示失败，为 1表示成功
    time[1] 为年份，0x00 表示 2000 年
    time[2] 为月份，从 1 开始到12 结束
    time[3] 为日期，从 1 开始到31 结束
    time[4] 为时钟，从 0 开始到23 结束
    time[5] 为分钟，从 0 开始到59 结束
    time[6] 为秒钟，从 0 开始到59 结束
    */
    if(time[0] == 1) {
        //正确接收到蜂窝模块返回的格林数据

    }else {
        //获取格林时间出错,有可能是当前蜂窝模块未联网
    }
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU校对本地RTC时钟
 * @param[in] {time} 获取到的格林时间数据
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_write_rtctime(u8 time[])
{
    #error "请自行完成RTC时钟写入代码,并删除该行"
    /*
    Time[0] 为是否获取时间成功标志，为 0 表示失败，为 1表示成功
    Time[1] 为年份，0x00 表示 2000 年
    Time[2] 为月份，从 1 开始到12 结束
    Time[3] 为日期，从 1 开始到31 结束
    Time[4] 为时钟，从 0 开始到23 结束
    Time[5] 为分钟，从 0 开始到59 结束
    Time[6] 为秒钟，从 0 开始到59 结束
    Time[7] 为星期，从 1 开始到 7 结束，1代表星期一
   */
    if(time[0] == 1) {
        //正确接收到蜂窝模块返回的本地时钟数据

    }else {
        //获取本地时钟数据出错,有可能是当前蜂窝模块未联网
    }
}
#endif

#ifdef WEATHER_ENABLE
/**
* @brief  mcu打开天气服务
 * @param  Null
 * @return Null
 */
void mcu_open_weather(void)
{
    i32 i = 0;
    i8 buffer[13] = {0};
    u8 weather_len = 0;
    u16 send_len = 0;

    weather_len = sizeof(weather_choose) / sizeof(weather_choose[0]);

    for(i=0;i<weather_len;i++) {
        buffer[0] = sprintf(buffer+1,"w.%s",weather_choose[i]);
        send_len = set_cellular_uart_buffer(send_len, (u8 *)buffer, buffer[0]+1);
    }

    #error "请根据提示，自行完善打开天气服务代码，完成后请删除该行"
    /*
    //当获取的参数有和时间有关的参数时(如:日出日落)，需要搭配t.unix或者t.local使用，需要获取的参数数据是按照格林时间还是本地时间
    buffer[0] = sprintf(buffer+1,"t.unix"); //格林时间   或使用  buffer[0] = sprintf(buffer+1,"t.local"); //本地时间
    send_len = set_cellular_uart_buffer(send_len, (u8 *)buffer, buffer[0]+1);
    */

    buffer[0] = sprintf(buffer+1,"w.date.%d",WEATHER_FORECAST_DAYS_NUM);
    send_len = set_cellular_uart_buffer(send_len, (u8 *)buffer, buffer[0]+1);

    cellular_uart_write_frame(WEATHER_OPEN_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  打开天气功能返回用户自处理函数
 * @param[in] {res} 打开天气功能返回结果
 * @ref       0: 失败
 * @ref       1: 成功
 * @param[in] {err} 错误码
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void weather_open_return_handle(u8 res, u8 err)
{
    #error "请自行完成打开天气功能返回数据处理代码,完成后请删除该行"
    u8 err_num = 0;

    if(res == 1) {
        //打开天气返回成功
    }else if(res == 0) {
        //打开天气返回失败
        //获取错误码
        err_num = err;
    }
}

/**
 * @brief  天气数据用户自处理函数
 * @param[in] {name} 参数名
 * @param[in] {type} 参数类型
 * @ref       0: int 型
 * @ref       1: string 型
 * @param[in] {data} 参数值的地址
 * @param[in] {day} 哪一天的天气  0:表示当天 取值范围: 0~6
 * @ref       0: 今天
 * @ref       1: 明天
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void weather_data_user_handle(i8 *name, u8 type, const u8 *data, i8 day)
{
    #error "这里仅给出示例，请自行完善天气数据处理代码,完成后请删除该行"
    i32 value_int;
    i8 value_string[50];//由于有的参数内容较多，这里默认为50。您可以根据定义的参数，可以适当减少该值

    my_memset(value_string, '\0', 50);

    //首先获取数据类型
    if(type == 0) { //参数是INT型
        value_int = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
    }else if(type == 1) {
        my_strcpy(value_string, data);
    }

    //注意要根据所选参数类型来获得参数值！！！
    if(my_strcmp(name, "temp") == 0) {
        printf("day:%d temp value is:%d\r\n", day, value_int);          //int 型
    }else if(my_strcmp(name, "humidity") == 0) {
        printf("day:%d humidity value is:%d\r\n", day, value_int);      //int 型
    }else if(my_strcmp(name, "pm25") == 0) {
        printf("day:%d pm25 value is:%d\r\n", day, value_int);          //int 型
    }else if(my_strcmp(name, "condition") == 0) {
        printf("day:%d condition value is:%s\r\n", day, value_string);  //string 型
    }
}
#endif

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  状态同步上报结果
 * @param[in] {result} 结果
 * @ref       0: 失败
 * @ref       1: 成功
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_upload_syn_result(u8 result)
{
    #error "请自行完成状态同步上报结果代码,并删除该行"

    if(result == 0) {
        //同步上报出错
    }else {
        //同步上报成功
    }
}
#endif

#ifdef GET_CELLULAR_STATUS_ENABLE
/**
 * @brief  获取蜂窝设备 状态结果
 * @param[in] {result} 指示 蜂窝设备 工作状态
 * @ref       0(状态1): SIM卡未连接
 * @ref       1(状态2): 搜索网络中
 * @ref       2(状态3): 已成功注册未联网
 * @ref       3(状态4): 联网成功并获取到IP
 * @ref       4(状态5): 已连接到云端
 * @ref       0xff: 未知状态
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_cellular_status(u8 result)
{
    #error "请自行完成获取 蜂窝设备 状态结果代码,并删除该行"

    switch(result) {
        case 0:
            //蜂窝设备工作状态1
        break;

        case 1:
            //蜂窝设备工作状态2
        break;

        case 2:
            //蜂窝设备工作状态3
        break;

        case 3:
            //蜂窝设备工作状态4
        break;

        case 4:
            //蜂窝设备工作状态5
        break;

        default:break;
    }
}
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取模块mac结果
 * @param[in] {mac} 模块 MAC 数据
 * @ref       mac[0]: 为是否获取mac成功标志，0x00 表示成功，0x01 表示失败
 * @ref       mac[1]~mac[6]: 当获取 MAC地址标志位如果mac[0]为成功，则表示模块有效的MAC地址
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_mac(u8 mac[])
{
    #error "请自行完成mac获取代码,并删除该行"
    /*
    mac[0]为是否获取mac成功标志，0x00 表示成功，为0x01表示失败
    mac[1]~mac[6]:当获取 MAC地址标志位如果mac[0]为成功，则表示模块有效的MAC地址
   */

    if(mac[0] == 1) {
        //获取mac出错
    }else {
        //正确接收到蜂窝模块返回的mac地址
    }
}
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取模块内存
 * @param[in] {module_memory} 获取模块内存的大小
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void remain_memory_result(u32 module_memory)
{
    #error "请自行实现获取模块内存处理代码,完成后请删除该行"

}
#endif

#ifdef GET_CELLULAR_RSSI_ENABLE
/**
 * @brief  获取当前蜂窝设备的LTE信号强度
 * @param[in] {rssi} 获取信号强度结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_cellular_rssi_result(u8 rssi)
{
    #error "请自行实现获取当前蜂窝设备信号强度处理代码,完成后请删除该行"
    if(0 == rssi) {
        //获取失败
    }else {
        //rssi为正值，表示信号强度，单位为dBi
    }
}
#endif

#ifdef SET_FEATURE_TEST_ENABLE
/**
 * @brief  获取模组的自检状态
 * @param[in] {sim_st} SIM卡状态.1:tree,0:fail
 * @param[in] {auth} 是否经过涂鸦授权产测.1:tree,0:fail
 * @param[in] {rf} RF射频是否经过校准. 1:校准完成,0:未校准
 * @param[in] {signal} 获取当前设备的信号强度 0~31
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void get_feature_test_result(u8 sim_st,u8 auth,u8 rf,u8 signal)
{
    #error "Complete the rssi fetch processing code yourself and delete the line"
}
#endif

#ifdef CELLULAR_SERVICE_ENABLE
/**
 * @brief  获取蜂窝设备的工作模式结果
 * @param[in] {result} 工作模式结果
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_cellular_work_mode_result(u8 result)
{
    #error "请自行实现获取蜂窝设备的工作模式结果处理代码,完成后请删除该行"

    switch(result) {
        case 1:
            //全功能模式
        break;

        case 4:
            //飞行模式
        break;

        default:break;
    }
}

/**
 * @brief  获取国际移动用户识别码结果
 * @param[in] {imsi} imsi码 15个字节
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_cellular_IMSI_result(u8 imsi[], u16 data_len)
{
    #error "请自行实现获取国际移动用户识别码结果处理代码,完成后请删除该行"


}

/**
 * @brief  获取国际移动用户识别码结果
 * @param[in] {imci} imci码 20个字节
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_cellular_IMCI_result(u8 imci[], u16 data_len)
{
    #error "请自行实现获取国际移动用户识别码结果处理代码,完成后请删除该行"


}

/**
 * @brief  获取设备 IMEI 结果
 * @param[in] {imei} imei码 15个字节
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_cellular_IMEI_result(u8 imei[], u16 data_len)
{
    #error "请自行实现获取国际移动用户识别码结果处理代码,完成后请删除该行"


}

/**
 * @brief  获取设备GNSS定位信息
 * @param[in] {location} gnss定位信息,字符串类型:如“120.661,32.221”(经度、纬度)
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_gnss_location_result(u8 location[], u16 data_len)
{
    #error "请自行实现获取GNSS定位信息处理代码,完成后请删除该行"
    u8 ret = location[0];
    if (!ret) {
        //获取失败
    }
    else {
        //获取成功
    }
}

/**
 * @brief  获取设备GNSS当前速度
 * @param[in] {speed} gnss设备的当前速度,单位100m/H
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_gnss_speed_result(u8 speed[], u16 data_len)
{
    #error "请自行实现获取GNSS定位信息处理代码,完成后请删除该行"
    u8 ret = speed[0];
    u16 u16speed = speed[1] << 8 | speed[2];
    if (!ret) {
        //获取失败
    }
    else {
        //获取成功
    }
}

/**
 * @brief  获取设备GNSS当前信号强度
 * @param[in] {rssi} gnss设备的当前信号强度
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_gnss_rssi_result(u8 rssi[], u16 data_len)
{
    #error "请自行实现获取GNSS定位信息处理代码,完成后请删除该行"
    u8 ret = rssi[0];
    u8 u8rssi = rssi[1];
    if (!ret) {
        //获取失败
    }
    else {
        //获取成功
    }
}

static void remove_chacator(u8 *src,u8 *desc,i8 chacator1,i8 charactor2,i8 charactor3)
{
    u16 i = 0,j = 0;
    u16 len = strlen((i8*)src);

    for ( i = 0; i < len; i ++) {
        if (src[i] != chacator1 && src[i] != charactor2 && src[i] != charactor3) {
            desc[j] = src[i];
            j ++;
        }
    }
}

/**
 * @brief  获取设备蜂窝设备WIFI定位信息
 * @param[in] {location} gnss定位信息,字符串类型:如0x02["b27e525dc87d",-64],["957e5b5d087d",-64]
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_cellular_wifi_location_result(u8 ap_info[], u16 data_len)
{
    //#error "请自行实现获取蜂窝设备的WIFI定位信息处理代码,完成后请删除该行"
    /**/
    u8 i,j;
    i8 wifi_info[256]={0};
    i8 mac[21] = {0};
    i8 rssi[8] = {0};
    u16 offset = 0;
    i8 *ptemp = NULL;
    i8 *psrc = NULL;
    u8 send_ap_count = 0;

    u8 ap_count = ap_info[0];
    u8 loop_count =( ap_count/MAX_AP_COUNT);
    if (ap_count%MAX_AP_COUNT) {
        loop_count ++;
    }
    if (data_len < 2  || data_len >= CELLULAR_DATA_PROCESS_LMT) {
        return;
    }
    if (!ap_count) {
        //获取失败
    }
    else {
        //获取成功
        if (strchr((char*)ap_info+1,'[')) {    //如果是1格式
            remove_chacator(ap_info+1,wifi_info,'[','"',']');
        }
        else {  //格式：112233445566,-XX(-x)
            memcpy(wifi_info,ap_info+1,data_len -1);
        }
        if (strlen(wifi_info) < 200) {
            //mcu_dp_string_update 直接上传给涂鸦云。客户自行调用
        }
        else {
           ptemp = (char*)wifi_info;
            for (j = 0; j < loop_count; j ++) {
                memset(ap_info,0,data_len);
                psrc = ap_info;
                if (j < loop_count-1) {
                    send_ap_count = MAX_AP_COUNT;
                }
                else {
                    send_ap_count = ap_count%MAX_AP_COUNT;
                }
                for ( i = 0; i < send_ap_count; i ++) {
                    sscanf(ptemp,"%[^,],%[^,]",mac,rssi);
                    if (strlen(rssi) && strlen(mac)) {

                        sprintf(psrc+strlen(psrc),"%s,",mac);
                        sprintf(psrc+strlen(psrc),"%s",rssi);
						ptemp += strlen(mac);
						ptemp += 1; //‘,’
						ptemp += strlen(rssi);
						if (strchr(ptemp,',')) {
							ptemp += 1;
						}
                        if (i < send_ap_count -1) {
                            sprintf(psrc+strlen(psrc),"%s",",");
                        }
                    }
                    memset(mac,0,sizeof(mac));
                    memset(rssi,0,sizeof(rssi));
                }
                //mcu_dp_string_update(dip,psrc,strlen(psrc));
				//printf("%d psrc = %s\r\n",j,psrc);
            }
        }
    }
}

/**
 * @brief  设置GNSS
 * @param[in] {gnss_mode} 设置GNSS状态返回值,GNSS定位模式状态返回
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void get_set_gnss_result(u8 gnss_status, u8 gnss_mode)
{
    #error "请自行实现设置GNSS定位功能处理代码,完成后请删除该行"
    if (!gnss_status) {
        //设置失败
    }
    else {
        //设置成功
    }
    if (!gnss_mode) {
        //设置失败
    }
    else {
        //设置成功
    }
}

/**
 * @brief  打开或者关闭WIFI定位功能
 * @param[in] {result} 设置状态返回值
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void set_cellular_wifi_result(u8 result)
{
    #error "请自行实现设置蜂窝设备的WIFI定位功能处理代码,完成后请删除该行"
    if (!result) {
        //设置失败
    }
    else {
        //设置成功
    }
}

/**
 * @brief  复位GNSS设置
 * @param[in] {result} 设置状态返回值
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void reset_gnss_result(u8 result)
{
    #error "请自行实现设置蜂窝设备的定位功能处理代码,完成后请删除该行"
    if (!result) {
        //设置失败
    }
    else {
        //设置成功
    }
}

/**
 * @brief  蜂窝设备服务处理
 * @param[in] {p_data} 数据缓冲区
 * @param[in] {data_len} 数据长度
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void cellular_service_process(u8 p_data[], u16 data_len)
{
    switch(p_data[0]) {
        case GET_CELLULAR_WORK_MODE:
            get_cellular_work_mode_result(p_data[1]);
        break;

        case GET_CELLULAR_IMSI:
            get_cellular_IMSI_result(p_data + 1, data_len - 1);
        break;

        case GET_CELLULAR_IMCI:
            get_cellular_IMCI_result(p_data + 1, data_len - 1);
        break;

        case GET_CELLULAR_IMEI:
            get_cellular_IMEI_result(p_data + 1, data_len - 1);
        break;

        case GET_CELLULAR_GPS_LOCATION:
            get_gnss_location_result(p_data + 1, data_len - 1);
        break;
        case GET_CELLULAR_GPS_SNR:
            get_gnss_rssi_result(p_data + 1, data_len - 1);
        break;
        case GET_CELLULAR_GPS_SPEED:
            get_gnss_speed_result(p_data + 1, data_len - 1);
        break;
        case GET_CELLULAR_WIFI_LOCATION:
            get_cellular_wifi_location_result(p_data + 1, data_len - 1);
        break;
        case SET_CELLULAR_CTRL_GNSS:
            get_set_gnss_result(p_data[1],p_data[2]);
        break;
        case SET_CELLULAR_CTRL_WIFI:
            set_cellular_wifi_result(p_data[1]);
        break;
        case SET_CELLULAR_RESET_GNSS:
            reset_gnss_result(p_data[1]);
        break;
        default:break;
    }
}
#endif






