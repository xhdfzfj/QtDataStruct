/*
 * @Author: your name
 * @Date: 2020-10-31 10:40:04
 * @LastEditTime: 2021-02-24 15:29:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \SourceCode\CommonFun\CommonFun.h
 */
#pragma once
#ifndef __COMMONFUN_H__
#define __COMMONFUN_H__

#include <stdint.h>

#define ALIGN_HANDLE( A )   ( ( A & 0x03 ) == 0 ? A : ( ( A + 3 ) & 0xFFFFFFFFC ) )
#define FIND_INVERT_ORDER   0   //倒序
#define FIND_POSITION_ORDER 1   //正序

/*****************************
 *  数据定义
 * ***************************/
typedef struct _ListHead_S
{
    void * mListContentP;
    void * mCurContentP;
    uint32_t mElementCount;
}ListHead_S;

void FetekMemCpy( void *pDstP, const void *pSrcP, uint32_t pLen );
uint32_t fun_FindSubStr( uint8_t * pSrcDataP, uint16_t pSrcDataLen, uint8_t * pDestDataP, uint16_t pDestDataLen );
uint8_t * fun_FindSubChar( uint8_t * pDestP, uint16_t pDestLen, uint8_t pDestValue, uint8_t pOrder );
uint32_t fun_DataBufToUint32Value( uint8_t * pMemP, uint16_t pMemLen );
 

#endif