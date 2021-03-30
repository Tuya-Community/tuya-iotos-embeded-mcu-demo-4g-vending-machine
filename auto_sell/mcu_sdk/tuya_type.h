/**********************************Copyright (c)**********************************
**                       版权所有 (C), 2015-2021, 涂鸦科技
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file tuya_type.h
 * @brief common data type definitions
 * @author Leon
 * @date  2020.03.05
 * @par   email:
 *        zhangpeng@tuya.com
 * @copyright HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @par company  
 *      http://www.tuya.com
 */


#ifndef  __TUYA_TYPE_H__
#define  __TUYA_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__IAR_SYSTEMS_ICC__) 
    #define VIRTUAL_FUNC __weak
#else 
    #define VIRTUAL_FUNC __attribute__((weak))
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef STATIC
#define STATIC static
#endif

#ifndef CONST
#define CONST const
#endif

#ifndef SIZEOF
#define SIZEOF sizeof
#endif

#ifndef INLINE
#define INLINE inline
#endif


#ifndef NULL
    #ifdef __cplusplus
    #define NULL 0
    #else
    #define NULL ((void *)0)
    #endif
#endif


#ifndef bool_t
typedef unsigned char   bool_t;
#endif

#ifndef i8
typedef signed char   i8;
#endif

#ifndef u8
typedef unsigned char   u8;
#endif

#ifndef i16
typedef signed short   i16;
#endif

#ifndef u16
typedef unsigned short   u16;
#endif

#ifndef i32
typedef signed int  i32;
#endif

#ifndef u32
typedef unsigned int u32;
#endif

#ifndef i64
typedef long long  i64;
#endif

#ifndef u64
typedef unsigned long long u64;
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifdef __cplusplus
}
#endif 

#endif
