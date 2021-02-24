/*
 * @Author: your name
 * @Date: 2021-02-23 10:55:10
 * @LastEditTime: 2021-02-24 10:09:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \SourceCode\SimDevMgr\JsonParamDef.h
 */
#ifndef __JSONPARAMDEF_H__
#define __JSONPARAMDEF_H__

#include <stdint.h>

#define JSON_PARAM_UNKNOW_TYPE      0
#define JSON_PARAM_TAGVALUE_TYPE    1
#define JSON_PARAM_STRUCT_TYPE      2
#define JSON_PARAM_ARRAY_TYPE       3

typedef struct _JsonFlag_S
{
    uint8_t     jsonFlagName[ 64 ];
    uint16_t    jsonFlagLen;
}JsonFlag_S;

typedef struct _JsonStrValue_S
{
    uint8_t * mStrValueP;
    uint8_t   mStrValueLen;
}JsonStrValue_S;


typedef struct _JsonTagAndValue_S
{
    uint8_t * mTagName;
    uint8_t   mTagNameLen;
    uint8_t   mValueType;
    union
    {
        JsonStrValue_S mJsonStr_S;
        uint32_t       mDataValue;
    }JsonValue_U;
}JsonTagAndValue_S;


typedef struct _JsonParam_S
{
    uint8_t paramType;      //1:代表 TagAndValue 类型  2:代表结构体 3:代表数组

    union
    {
        JsonTagAndValue_S mTagAndValue_S;
        struct _JsonParam_S * mStructOrArrayP;
    }JsonParamValue_U;
    
    struct _JsonParam_S * nextP;
    struct _JsonParam_S * prevP;
}JsonParam_S;

#endif