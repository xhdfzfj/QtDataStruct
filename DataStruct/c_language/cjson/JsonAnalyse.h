/*
 * @Author: your name
 * @Date: 2021-02-23 17:29:23
 * @LastEditTime: 2021-02-23 18:58:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \SourceCode\CommonFun\JsonAnalyse.h
 */
#ifndef __JSONANALYSE_H__
#define __JSONANALYSE_H__

#include <stdint.h>
#include "./JsonParamDef.h"

/*************************************************
 * 宏定义
 * **********************************************/
#define JSON_VALUE_STRING   1   //字符串类型
#define JSON_VALUE_DATA     2   //数值类型

/*************************************************
 *  函数声明
 * **********************************************/

#if __cplusplus
extern "C" {
#endif
uint32_t fun_JsonAnalyse( uint8_t * pJsonBufP, uint16_t pJsonLen, uint8_t * pFreeSpaceP, JsonParam_S ** pResultP );
uint32_t fun_CreateOrAddJsonResult( uint8_t * pJsonTagP, uint8_t pJsonTagLen, 
                                    uint8_t * pJsonValueP, uint8_t pJsonValueLen, uint8_t pJsonValueType, 
                                    uint8_t * pBackupFreeP, uint16_t * pRetBackUpUseCount, uint8_t * pJsonBufP, uint16_t pJsonBufLen, 
                                    JsonParam_S ** pResultP );
#if __cplusplus
}
#endif
#endif
