/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2030, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.c
 * @author  涂鸦综合协议开发组
 * @version v1.0.0
 * @date    2020.12.25
 * @brief   用户需要主动调用的函数都在该文件内
 */

/****************************** 免责声明 ！！！ *******************************
由于MCU类型和编译环境多种多样，所以此代码仅供参考，用户请自行把控最终代码质量，
涂鸦不对MCU功能结果负责。
******************************************************************************/

#define MCU_API_GLOBAL

#include "cellular.h"

/**
 * @brief  hex转bcd
 * @param[in] {Value_H} 高字节
 * @param[in] {Value_L} 低字节
 * @return 转换完成后数据
 */
u8 hex_to_bcd(u8 Value_H,u8 Value_L)
{
    u8 bcd_value;

    if((Value_H >= '0') && (Value_H <= '9'))
        Value_H -= '0';
    else if((Value_H >= 'A') && (Value_H <= 'F'))
        Value_H = Value_H - 'A' + 10;
    else if((Value_H >= 'a') && (Value_H <= 'f'))
        Value_H = Value_H - 'a' + 10;

    bcd_value = Value_H & 0x0f;

    bcd_value <<= 4;
    if((Value_L >= '0') && (Value_L <= '9'))
        Value_L -= '0';
    else if((Value_L >= 'A') && (Value_L <= 'F'))
        Value_L = Value_L - 'a' + 10;
    else if((Value_L >= 'a') && (Value_L <= 'f'))
        Value_L = Value_L - 'a' + 10;

    bcd_value |= Value_L & 0x0f;

    return bcd_value;
}

/**
 * @brief  求字符串长度
 * @param[in] {str} 字符串地址
 * @return 数据长度
 */
u32 my_strlen(u8 *str)
{
    u32 len = 0;
    if(str == NULL) {
        return 0;
    }

    for(len = 0; *str ++ != '\0'; ) {
        len ++;
    }

    return len;
}

/**
 * @brief  把src所指内存区域的前count个字节设置成字符c
 * @param[out] {src} 待设置的内存首地址
 * @param[in] {ch} 设置的字符
 * @param[in] {count} 设置的内存长度
 * @return 待设置的内存首地址
 */
void *my_memset(void *src,u8 ch,u16 count)
{
    u8 *tmp = (u8 *)src;

    if(src == NULL) {
        return NULL;
    }

    while(count --) {
        *tmp ++ = ch;
    }

    return src;
}

/**
 * @brief  内存拷贝
 * @param[out] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {count} 拷贝数据个数
 * @return 数据处理完后的源地址
 */
void *my_memcpy(void *dest, const void *src, u16 count)
{
    u8 *pdest = (u8 *)dest;
    const u8 *psrc  = (const u8 *)src;
    u16 i;

    if(dest == NULL || src == NULL) {
        return NULL;
    }

    if((pdest <= psrc) || (pdest > psrc + count)) {
        for(i = 0; i < count; i ++) {
            pdest[i] = psrc[i];
        }
    }else {
        for(i = count; i > 0; i --) {
            pdest[i - 1] = psrc[i - 1];
        }
    }

    return dest;
}

/**
 * @brief  字符串拷贝
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @return 数据处理完后的源地址
 */
i8 *my_strcpy(i8 *dest, const i8 *src)
{
  i8 *p;   
	if((NULL == dest) || (NULL == src)) {
        return NULL;
    }

    p = dest;
    while(*src!='\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return p;
}

/**
 * @brief  字符串比较
 * @param[in] {s1} 字符串 1
 * @param[in] {s2} 字符串 2
 * @return 大小比较值
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
i32 my_strcmp(i8 *s1 , i8 *s2)
{
    while( *s1 && *s2 && *s1 == *s2 ) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/**
 * @brief  将int类型拆分四个字节
 * @param[in] {number} 4字节原数据
 * @param[out] {value} 处理完成后4字节数据
 * @return Null
 */
void int_to_byte(u32 number,u8 value[4])
{
    value[0] = number >> 24;
    value[1] = number >> 16;
    value[2] = number >> 8;
    value[3] = number & 0xff;
}

/**
 * @brief  将4字节合并为1个32bit变量
 * @param[in] {value} 4字节数组
 * @return 合并完成后的32bit变量
 */
u32 byte_to_int(const u8 value[4])
{
    u32 nubmer = 0;

    nubmer = (u32)value[0];
    nubmer <<= 8;
    nubmer |= (u32)value[1];
    nubmer <<= 8;
    nubmer |= (u32)value[2];
    nubmer <<= 8;
    nubmer |= (u32)value[3];

    return nubmer;
}

/**
 * @brief  raw型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_raw_update(u8 dpid,const u8 value[],u16 len)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_RAW);
    //
    send_len = set_cellular_uart_byte(send_len,len / 0x100);
    send_len = set_cellular_uart_byte(send_len,len % 0x100);
    //
    send_len = set_cellular_uart_buffer(send_len,(u8 *)value,len);

    cellular_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}

/**
 * @brief  bool型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_bool_update(u8 dpid,u8 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_BOOL);
    //
    send_len = set_cellular_uart_byte(send_len,0);
    send_len = set_cellular_uart_byte(send_len,1);
    //
    if(value == FALSE) {
        send_len = set_cellular_uart_byte(send_len,FALSE);
    }else {
        send_len = set_cellular_uart_byte(send_len,1);
    }

    cellular_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);

    return SUCCESS;
}

/**
 * @brief  value型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_value_update(u8 dpid,u32 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_VALUE);
    //
    send_len = set_cellular_uart_byte(send_len,0);
    send_len = set_cellular_uart_byte(send_len,4);
    //
    send_len = set_cellular_uart_byte(send_len,value >> 24);
    send_len = set_cellular_uart_byte(send_len,value >> 16);
    send_len = set_cellular_uart_byte(send_len,value >> 8);
    send_len = set_cellular_uart_byte(send_len,value & 0xff);

    cellular_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}

/**
 * @brief  string型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_string_update(u8 dpid,const u8 value[],u16 len)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_STRING);
    //
    send_len = set_cellular_uart_byte(send_len,len / 0x100);
    send_len = set_cellular_uart_byte(send_len,len % 0x100);
    //
    send_len = set_cellular_uart_buffer(send_len,(u8 *)value,len);

    cellular_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}

/**
 * @brief  enum型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_enum_update(u8 dpid,u8 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_ENUM);
    //
    send_len = set_cellular_uart_byte(send_len,0);
    send_len = set_cellular_uart_byte(send_len,1);
    //
    send_len = set_cellular_uart_byte(send_len,value);

    cellular_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}

/**
 * @brief  fault型dp数据上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值
 * @return Null
 * @note   Null
 */
u8 mcu_dp_fault_update(u8 dpid,u32 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_BITMAP);
    //
    send_len = set_cellular_uart_byte(send_len,0);

    if((value | 0xff) == 0xff) {
        send_len = set_cellular_uart_byte(send_len,1);
        send_len = set_cellular_uart_byte(send_len,value);
    }else if((value | 0xffff) == 0xffff) {
        send_len = set_cellular_uart_byte(send_len,2);
        send_len = set_cellular_uart_byte(send_len,value >> 8);
        send_len = set_cellular_uart_byte(send_len,value & 0xff);
    }else {
        send_len = set_cellular_uart_byte(send_len,4);
        send_len = set_cellular_uart_byte(send_len,value >> 24);
        send_len = set_cellular_uart_byte(send_len,value >> 16);
        send_len = set_cellular_uart_byte(send_len,value >> 8);
        send_len = set_cellular_uart_byte(send_len,value & 0xff);
    }

    cellular_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);

    return SUCCESS;
}

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  raw型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_raw_update_syn(u8 dpid,const u8 value[],u16 len)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_RAW);
    //
    send_len = set_cellular_uart_byte(send_len,len / 0x100);
    send_len = set_cellular_uart_byte(send_len,len % 0x100);
    //
    send_len = set_cellular_uart_buffer(send_len,(u8 *)value,len);

    cellular_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}

/**
 * @brief  bool型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_bool_update_syn(u8 dpid,u8 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_BOOL);
    //
    send_len = set_cellular_uart_byte(send_len,0);
    send_len = set_cellular_uart_byte(send_len,1);
    //
    if(value == FALSE) {
        send_len = set_cellular_uart_byte(send_len,FALSE);
    }else {
        send_len = set_cellular_uart_byte(send_len,1);
    }

    cellular_uart_write_frame(STATE_UPLOAD_SYN_CMD, MCU_TX_VER, send_len);

    return SUCCESS;
}

/**
 * @brief  value型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_value_update_syn(u8 dpid,u32 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_VALUE);
    //
    send_len = set_cellular_uart_byte(send_len,0);
    send_len = set_cellular_uart_byte(send_len,4);
    //
    send_len = set_cellular_uart_byte(send_len,value >> 24);
    send_len = set_cellular_uart_byte(send_len,value >> 16);
    send_len = set_cellular_uart_byte(send_len,value >> 8);
    send_len = set_cellular_uart_byte(send_len,value & 0xff);

    cellular_uart_write_frame(STATE_UPLOAD_SYN_CMD, MCU_TX_VER, send_len);

    return SUCCESS;
}

/**
 * @brief  string型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @param[in] {len} 数据长度
 * @return Null
 * @note   Null
 */
u8 mcu_dp_string_update_syn(u8 dpid,const u8 value[],u16 len)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_STRING);
    //
    send_len = set_cellular_uart_byte(send_len,len / 0x100);
    send_len = set_cellular_uart_byte(send_len,len % 0x100);
    //
    send_len = set_cellular_uart_buffer(send_len,(u8 *)value,len);

    cellular_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}

/**
 * @brief  enum型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_enum_update_syn(u8 dpid,u8 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_ENUM);
    //
    send_len = set_cellular_uart_byte(send_len,0);
    send_len = set_cellular_uart_byte(send_len,1);

    send_len = set_cellular_uart_byte(send_len,value);

    cellular_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}

/**
 * @brief  fault型dp数据同步上传
 * @param[in] {dpid} dpid号
 * @param[in] {value} 当前dp值指针
 * @return Null
 * @note   Null
 */
u8 mcu_dp_fault_update_syn(u8 dpid,u32 value)
{
    u16 send_len = 0;

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    send_len = set_cellular_uart_byte(send_len,dpid);
    send_len = set_cellular_uart_byte(send_len,DP_TYPE_BITMAP);
    //
    send_len = set_cellular_uart_byte(send_len,0);

    if((value | 0xff) == 0xff) {
        send_len = set_cellular_uart_byte(send_len,1);
        send_len = set_cellular_uart_byte(send_len,value);
    }else if((value | 0xffff) == 0xffff) {
        send_len = set_cellular_uart_byte(send_len,2);
        send_len = set_cellular_uart_byte(send_len,value >> 8);
        send_len = set_cellular_uart_byte(send_len,value & 0xff);
    }else {
        send_len = set_cellular_uart_byte(send_len,4);
        send_len = set_cellular_uart_byte(send_len,value >> 24);
        send_len = set_cellular_uart_byte(send_len,value >> 16);
        send_len = set_cellular_uart_byte(send_len,value >> 8);
        send_len = set_cellular_uart_byte(send_len,value & 0xff);
    }

    cellular_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}
#endif

/**
 * @brief  mcu获取bool型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u8 mcu_get_dp_download_bool(const u8 value[],u16 len)
{
    return(value[0]);
}

/**
 * @brief  mcu获取enum型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u8 mcu_get_dp_download_enum(const u8 value[],u16 len)
{
    return(value[0]);
}

/**
 * @brief  mcu获取value型下发dp值
 * @param[in] {value} dp数据缓冲区地址
 * @param[in] {len} dp数据长度
 * @return 当前dp值
 * @note   Null
 */
u32 mcu_get_dp_download_value(const u8 value[],u16 len)
{
    return(byte_to_int(value));
}

/**
 * @brief  串口接收数据暂存处理
 * @param[in] {value} 串口收到的1字节数据
 * @return Null
 * @note   在MCU串口处理函数中调用该函数,并将接收到的数据作为参数传入
 */
void uart_receive_input(u8 value)
{
    //cai#error "请在收到多个字节的串口数据时调用此函数,串口数据由MCU_SDK处理,用户请勿再另行处理,完成后删除该行"

    if(1 == rx_buf_out - rx_buf_in) {
        //串口接收缓存已满
    }else if((rx_buf_in > rx_buf_out) && ((rx_buf_in - rx_buf_out) >= sizeof(cellular_uart_rx_buf))) {
        //串口接收缓存已满
    }else {
        //串口接收缓存未满
        if(rx_buf_in >= (u8 *)(cellular_uart_rx_buf + sizeof(cellular_uart_rx_buf))) {
            rx_buf_in = (u8 *)(cellular_uart_rx_buf);
        }

        *rx_buf_in ++ = value;
    }
}

/**
 * @brief  串口接收多个字节数据暂存处理
 * @param[in] {value} 串口要接收的数据的源地址
 * @param[in] {data_len} 串口要接收的数据的数据长度
 * @return Null
 * @note   如需要支持一次多字节缓存，可调用该函数
 */
void uart_receive_buff_input(u8 value[], u16 data_len)
{
    //cai#error "请在需要一次缓存多个字节串口数据处调用此函数,串口数据由MCU_SDK处理,用户请勿再另行处理,完成后删除该行"

    u16 i = 0;
    for(i = 0; i < data_len; i++) {
        uart_receive_input(value[i]);
    }
}

/**
 * @brief  蜂窝设备串口数据处理服务
 * @param  Null
 * @return Null
 * @note   在MCU主函数while循环中调用该函数
 */
void cellular_uart_service(void)
{
    //cai#error "请直接在main函数的while(1){}中添加cellular_uart_service(),调用该函数不要加任何条件判断,完成后删除该行"
    static u16 rx_in = 0;
    u16 offset = 0;
    u16 rx_value_len = 0;

    while((rx_in < sizeof(cellular_data_process_buf)) && with_data_rxbuff() > 0) {
        cellular_data_process_buf[rx_in ++] = take_byte_rxbuff();
    }

    if(rx_in < PROTOCOL_HEAD)
        return;

    while((rx_in - offset) >= PROTOCOL_HEAD) {
        if(cellular_data_process_buf[offset + HEAD_FIRST] != FRAME_FIRST) {
            offset ++;
            continue;
        }

        if(cellular_data_process_buf[offset + HEAD_SECOND] != FRAME_SECOND) {
            offset ++;
            continue;
        }

        if(cellular_data_process_buf[offset + PROTOCOL_VERSION] != MCU_RX_VER) {
            offset += 2;
            continue;
        }

        rx_value_len = cellular_data_process_buf[offset + LENGTH_HIGH] * 0x100;
        rx_value_len += (cellular_data_process_buf[offset + LENGTH_LOW] + PROTOCOL_HEAD);
        if(rx_value_len > sizeof(cellular_data_process_buf) + PROTOCOL_HEAD) {
            offset += 3;
            continue;
        }

        if((rx_in - offset) < rx_value_len) {
            break;
        }

        //数据接收完成
        if(get_check_sum((u8 *)cellular_data_process_buf + offset,rx_value_len - 1) != cellular_data_process_buf[offset + rx_value_len - 1]) {
            //校验出错
            //printf("crc error (crc:0x%X  but data:0x%X)\r\n",get_check_sum((u8 *)cellular_data_process_buf + offset,rx_value_len - 1),cellular_data_process_buf[offset + rx_value_len - 1]);
            offset += 3;
            continue;
        }

        data_handle(offset);
        offset += rx_value_len;
    }//end while

    rx_in -= offset;
    if(rx_in > 0) {
        my_memcpy((i8 *)cellular_data_process_buf, (const i8 *)cellular_data_process_buf + offset, rx_in);
    }
}

/**
 * @brief  协议串口初始化函数
 * @param  Null
 * @return Null
 * @note   在MCU初始化代码中调用该函数
 */
void cellular_protocol_init(void)
{
    //cai#error " 请在main函数中添加cellular_protocol_init()完成协议初始化,并删除该行"
    rx_buf_in = (u8 *)cellular_uart_rx_buf;
    rx_buf_out = (u8 *)cellular_uart_rx_buf;

    stop_update_flag = DISABLE;

#ifndef CELLULAR_CONTROL_SELF_MODE
    cellular_work_state = CELLULAR_SATE_UNKNOW;
#endif
}



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
u8 mcu_get_reset_celluluar_flag(void)
{
    return reset_cellular_flag;
}

/**
 * @brief  MCU主动重置蜂窝设备激活状态
 * @param  Null
 * @return Null
 * @note   1:MCU主动调用,通过mcu_get_reset_celluluar_flag()函数获取重置蜂窝设备是否成功
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
void mcu_reset_cellular(void)
{
    reset_cellular_flag = RESET_CELLULAR_ERROR;

    cellular_uart_write_frame(RESET_CELLULAR_NET, MCU_TX_VER, 0);
}

/**
 * @brief  获取设置蜂窝设备工作模式状态成功标志
 * @param  Null
 * @return 蜂窝mode flag
 * -           0(SET_CELLULARCONFIG_ERROR):失败
 * -           1(SET_CELLULARCONFIG_SUCCESS):成功
 * @note   1:MCU主动调用mcu_set_cellular_mode()后调用该函数获取复位状态
 *         2:如果为模块自处理模式,MCU无须调用该函数
 */
u8 mcu_get_cellular_mode_flag(void)
{
    return set_cellularmode_flag;
}

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
void mcu_set_cellular_mode(u8 mode)
{
    u8 length = 0;

    set_cellularmode_flag = SET_CELLULARCONFIG_ERROR;

    length = set_cellular_uart_byte(length, mode);

    cellular_uart_write_frame(SET_CELLULAR_WORK_MODE, MCU_TX_VER, length);
}

/**
 * @brief  MCU主动获取当前蜂窝设备工作状态
 * @param  Null
 * @return 蜂窝 work state
 * -          0: SIM卡未连接
 * -          1: 搜索网络中
 * -          2: 已成功注册未联网
 * -          3: 联网成功并获取到IP
 * -          4: 已连接到云端
 * -          0xff: 未知状态
 * @note   如果为模块自处理模式,MCU无须调用该函数
 */
u8 mcu_get_cellular_work_state(void)
{
    return cellular_work_state;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU获取格林时间
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_green_time(void)
{
    cellular_uart_write_frame(GET_ONLINE_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU获取系统时间,用于校对本地时钟
 * @param  Null
 * @return Null
 * @note   MCU主动调用完成后在mcu_write_rtctime函数内校对rtc时钟
 */
void mcu_get_system_time(void)
{
    cellular_uart_write_frame(GET_LOCAL_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef CELLULUA_HEARTSTOP_ENABLE
/**
 * @brief  通知蜂窝模组关闭心跳
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void cellular_heart_stop(void)
{
    cellular_uart_write_frame(HEAT_BEAT_STOP, MCU_TX_VER, 0);
}
#endif

#ifdef GET_CELLULAR_STATUS_ENABLE
/**
 * @brief  获取当前蜂窝模组联网状态
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_cellular_connect_status(void)
{
    cellular_uart_write_frame(GET_CELLULAR_STATE_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  获取蜂窝模块蓝牙MAC
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_module_mac(void)
{
    cellular_uart_write_frame(GET_MAC_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef GET_MODULE_REMAIN_MEMORY_ENABLE
/**
 * @brief  获取 蜂窝 模块剩余内存
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void get_module_remain_memory(void)
{
    cellular_uart_write_frame(GET_MODULE_REMAIN_MEMORY_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef GET_CELLULAR_RSSI_ENABLE
/**
 * @brief  获取当前蜂窝设备信号强度
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_get_cellular_rssi(void)
{
  cellular_uart_write_frame(GET_CELLULAR_RSSI, MCU_TX_VER, 0);
}
#endif


#ifdef SET_FEATURE_TEST_ENABLE
/**
 * @brief  开始蜂窝设备自检功能
 * @param  Null
 * @return Null
 * @note   MCU需要自行调用该功能
 */
void mcu_set_feature_test(void)
{
    cellular_uart_write_frame(GET_FEATURE_TEST_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef CELLULAR_SERVICE_ENABLE
/**
 * @brief  获取蜂窝设备的工作模式
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_cellular_work_mode(void)
{
    u16 length = 0;
    length = set_cellular_uart_byte(length, GET_CELLULAR_WORK_MODE);
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}

/**
 * @brief  获取国际移动用户识别码
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_IMSI(void)
{
    u16 length = 0;
    length = set_cellular_uart_byte(length, GET_CELLULAR_IMSI);
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}

/**
 * @brief  获取 SIM 卡识别码
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_IMCI(void)
{
    u16 length = 0;
    length = set_cellular_uart_byte(length, GET_CELLULAR_IMCI);
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}

/**
 * @brief  获取设备 IMEI
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_IMEI(void)
{
    u16 length = 0;
    length = set_cellular_uart_byte(length, GET_CELLULAR_IMEI);
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}
#ifdef GNSS_SERIVCE_ENABLE
/**
 * @brief  获取GNSS 定位信息
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_gnss_location(void)
{
    u16 length = 0;
    length = set_cellular_uart_byte(length, GET_CELLULAR_GPS_LOCATION);
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}
/**
 * @brief  获取GNSS 当前速度
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_gnss_speed(void)
{
    u16 length = 0;
    length = set_cellular_uart_byte(length, GET_CELLULAR_GPS_SPEED);
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}
/**
 * @brief  获取GNSS 当前信号强度
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_gnss_rssi(void)
{
    u16 length = 0;
    length = set_cellular_uart_byte(length, GET_CELLULAR_GPS_SNR);
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}

/**
 * @brief  控制GNSS服务
 * @param  [in] {enable} true:启动,false:关闭
 * @param  [in] {mode} GNSS定位跟踪类型
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_control_gnss(bool_t enable,GNSS_ATTACH_MODE_e mode)
{
    u16 length = 0;
    u8 cmd[3] = {0};
    cmd[0] = SET_CELLULAR_CTRL_GNSS;
    cmd[1] = enable;
    cmd[2] = mode;
    length = set_cellular_uart_buffer(length, cmd,sizeof(cmd));
    cellular_uart_write_frame(SET_CELLULAR_CMD, MCU_TX_VER, length);
}

/**
 * @brief  复位GNSS设备
 * @param  [in] {pin} 蜂窝设备连接到GNSS设备RST的PIN脚
 * @return [in] {level} tree:高电平复位，false:低电平复位
 * @note   MCU需要自行实现该功能
 */
void mcu_reset_gnss(u8 pin,bool_t level)
{
    u16 length = 0;
    u8 cmd[3] = {0};
    cmd[0] = SET_CELLULAR_RESET_GNSS;
    cmd[1] = pin;
    cmd[2] = level;
    length = set_cellular_uart_buffer(length, cmd,sizeof(cmd));
    cellular_uart_write_frame(SET_CELLULAR_CMD, MCU_TX_VER, length);
}

/**
 * @brief  控制WIFI定位服务
 * @param  [in] {enable} true:启动,false:关闭
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_control_wifi_location(bool_t enable)
{
    u16 length = 0;
    u8 cmd[2] = {0};
    cmd[0] = SET_CELLULAR_CTRL_WIFI;
    cmd[1] = enable;
    length = set_cellular_uart_buffer(length, cmd,sizeof(cmd));
    cellular_uart_write_frame(SET_CELLULAR_CMD, MCU_TX_VER, length);
}

/**
 * @brief  获取WIFI定位信息
 * @param  Null
 * @return Null
 * @note   MCU需要自行实现该功能
 */
void mcu_get_wifi_location(void)
{
    u16 length = 0;
    u8 cmd[1] = {0};
    cmd[0] = GET_CELLULAR_WIFI_LOCATION;
    length = set_cellular_uart_buffer(length, cmd,sizeof(cmd));
    cellular_uart_write_frame(GET_CELLULAR_CMD, MCU_TX_VER, length);
}


#endif
#endif

