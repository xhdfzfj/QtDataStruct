#include <stddef.h>
#include <string.h>
#include "./CommonFun.h"
#include "./JsonAnalyse.h"

/***********************************************
 * 常量声明
 * ********************************************/
const uint16_t JsonStrMinSize = 10;

const JsonFlag_S FeederJsonFlagS[] = { 
                                        { "Command", 7 },
                                        { "", 0xffff },
                            };
const uint8_t FeederCommandArray[][ 64 ] = { "AddNewDev", "" };
const uint8_t QuotationFlag = 0x22;         //引号的ASCII码
const uint8_t ColonFlag = 0x3a;             //冒号的ASCII码

/**
 * @brief 
 *      获取JSON标签的值与类型
 * @param pSrcP 
 * @param pSrcLen 
 * @param pRetValueLen
 * @param pRetValueType 
 *      1 字符串
 *      2 uint32_t数值
 *      3 数组
 *      4 结构
 * @return uint8_t* 
 */
uint8_t * fun_GetTagValueAndTagType( uint8_t * pSrcP, uint16_t pSrcLen, uint16_t * pRetValueLen, uint32_t * pRetValueType )
{
    uint8_t * _retP;
    uint8_t * _tmpP;
    uint16_t i;

    _retP = NULL;
    _tmpP = pSrcP;
    if( *_tmpP == QuotationFlag )
    {
        *pRetValueType = JSON_VALUE_STRING; //字符串
        i = 1;
        while( i < pSrcLen )
        {
            if( _tmpP[ i ] == QuotationFlag )
            {
                _retP = &_tmpP[ 1 ];
                *pRetValueLen = i - 1;
                break;
            }
            i += 1;
        }
    }
    else
    {
        *pRetValueType = JSON_VALUE_DATA;
        i = 0;
        while( i < pSrcLen )
        {
            if( ( _tmpP[ i ] < 0x30 ) || ( _tmpP[ i ] > 0x39 ) )
            {
                _retP = &_tmpP[ 0 ];
                *pRetValueLen = i;
                break;
            }
            i += 1;
        }
    }

    return _retP;
}

/**
 * @brief 
 * 
 * @param pSrcP 
 * @return uint8_t* 
 */
uint8_t * fun_FindJsonTagEndPos( uint8_t * pSrcP )
{
    uint8_t * _retP;
    uint16_t i;

    i = 0;
    while( ( pSrcP[ i ] != ',' ) && ( pSrcP[ i ] != ']' ) && ( pSrcP[ i ] != '}' ) )
    {
        i += 1;
    } 

    _retP = pSrcP + i;
    return _retP;
}

/**
 * @brief 
 * 
 * @param pDestBufP 
 * @param pStartPos 
 * @param pEndPos 
 */
void sub_ClearJsonBuf( uint8_t * pDestBufP, uint16_t pStartPos, uint32_t pEndPos )
{
    uint8_t * _tmpP;
    uint16_t _tmpLen, i;

    _tmpLen = pEndPos + 1 - pStartPos;
    _tmpP = pDestBufP;
    i = 0;
    while( i < _tmpLen )
    {
        pDestBufP[ pStartPos + i ] = 0;
        i += 1;
    }
}

/**
 * @brief 
 *      查找足够的空闲空间
 * @param pDestSpaceP 
 * @param pDestSpaceLen 
 * @param pReqLen 
 * @return uint8_t* 
 */
uint8_t * fun_FindFreeJsonSpace( uint8_t * pDestSpaceP, uint16_t pDestSpaceLen, uint8_t pReqLen )
{
    uint8_t * _retP;
    uint16_t i, j;

    _retP = NULL;

    j = 0;
    for( i = 0; i < pDestSpaceLen; i++ )
    {
        if( pDestSpaceP[ i ] == 0x00 )
        {
            if( _retP == NULL )
            {
                _retP = &pDestSpaceP[ i ];
                if( ( ( uint32_t )_retP & 0x03 ) != 0 )
                {
                    _retP = NULL;
                    j = 1;
                }
            }
            else
            {
                j += 1;
                if( j >= pReqLen )
                {
                    break;
                }
            }
        }
        else
        {
            _retP = NULL;
            j = 0;
        }
    }

    if( ( _retP != NULL ) && ( j < pReqLen ) )
    {
        _retP = NULL;
    }

    return _retP;
}

/**
 * @brief 
 * 
 * @param pDestStrP 
 * @return uint32_t 
 */
uint8_t * fun_FindJsonStrEnd( uint8_t * pDestStrP )
{
    uint8_t * _retP;

    _retP = NULL;

    _retP = pDestStrP;
    while( *_retP != 0x22 ) //引号
    {
        _retP += 1;
    }

    return _retP;
}

/**
 * @brief 
 *      获取JSON TAG的值的类型
 * @param pDestP 
 * @return uint32_t 
 */
uint32_t fun_GetTagValueType( uint8_t * pDestP )
{
    uint32_t _retValue;

    _retValue = JSON_PARAM_UNKNOW_TYPE;
    if( ( *pDestP != '{' ) && ( *pDestP != '[' ) ) 
    {
        _retValue = JSON_PARAM_TAGVALUE_TYPE;
    }
    else if( *pDestP == '{' )
    {
        _retValue = JSON_PARAM_STRUCT_TYPE;
    }
    else if( *pDestP == '[' )
    {
        _retValue = JSON_PARAM_ARRAY_TYPE;
    }

    return _retValue;
}

/**
 * @brief 
 * 
 * @param pMultBufP 
 * @param pMultBufLen 
 * @param pBackupFreeP 
 * @param pRetUseFreeCount 
 * @return JsonParam_S* 
 */
JsonParam_S * fun_CreateFreeResultNode( uint8_t * pMultBufP, uint16_t pMultBufLen, uint8_t * pBackupFreeP, uint16_t * pRetUseFreeCount, uint8_t pDataLen )
{
    JsonParam_S * _retNodeP;
    uint16_t _tmpReqLen;
    uint8_t * _tmpP;
    uint32_t _tmpU32Value;

    _retNodeP = NULL;

    _tmpReqLen = sizeof( JsonParam_S ) + pDataLen;
    _tmpP = fun_FindFreeJsonSpace( pMultBufP, pMultBufLen, _tmpReqLen );
    if( _tmpP != NULL )
    {
        _retNodeP = ( JsonParam_S * )_tmpP;
    }
    else
    {
        _tmpU32Value = ( uint32_t )pBackupFreeP;
        _tmpReqLen += ( 4 - ( _tmpU32Value & 0x03 ) );
        _tmpU32Value += 3;
        _tmpU32Value &= 0xfffffffc;
        
        _retNodeP = ( JsonParam_S * )_tmpU32Value;
        *pRetUseFreeCount = _tmpReqLen;
    }

    _retNodeP->nextP = NULL;
    _retNodeP->prevP = NULL;
    return _retNodeP;
}

/**
 * @brief 
 * 
 * @param pJsonStructP 
 * @param pJsonLen 
 * @return uint16_t 
 */
uint16_t fun_FindJsonStructLen( uint8_t * pJsonStructP, uint16_t pJsonLen )
{
    uint16_t _retLen;
    uint8_t _tmpCount;
    uint16_t i;
    uint8_t j;

    _retLen = 0;
    _tmpCount = 0;
    j = 0;
    for( i = 0; i < pJsonLen; i++ )
    {
        j += 1;
        if( pJsonStructP[ i ] == '{' )
        {
            _tmpCount += 1;
        }
        else if( pJsonStructP[ i ] == '}' )
        {
            _tmpCount -= 1;
            if( _tmpCount == 0 )
            {
                break;
            }
        }
    }

    if( _tmpCount == 0 )
    {
        if( j != 0 )
        {
            _retLen = j;
        }
    }
    return _retLen;
}

/**
 * @brief 
 * 
 * @param pJsonParamType 
 * @param pTagNameP 
 * @param pTagNameLen 
 * @param pDstParamP 
 */
void sub_FillJsonStructOrArrayTag( uint8_t pJsonParamType, uint8_t * pTagNameP, uint8_t pTagNameLen, JsonParam_S * pDstParamP )
{
    JsonParam_S * _tmpParamP;
    uint32_t i;

    _tmpParamP = pDstParamP;

    _tmpParamP->paramType = pJsonParamType;
    _tmpParamP->JsonParamValue_U.mTagAndValue_S.mTagName = ( uint8_t * )_tmpParamP + sizeof( JsonParam_S );
    for( i = 0; i < pTagNameLen; i++ )
    {
        _tmpParamP->JsonParamValue_U.mTagAndValue_S.mTagName[ i ] = pTagNameP[ i ];
    }

    _tmpParamP->JsonParamValue_U.mTagAndValue_S.mTagNameLen = pTagNameLen;

}

/**
 * @brief 
 *      处理JSON的结构体
 * @param pJsonStructBufP 
 * @param pJsonStructBufLen 
 * @param pResult 
 *      结构体的结果
 * @return uint32_t 
 *      1 代表成功
 */
uint32_t fun_JsonStructHandle( uint8_t * pJsonStructBufP, uint16_t pJsonStructBufLen, uint8_t * pFreeP, uint16_t * pFreeUseCount,
                               uint8_t * pJsonAllBufP, uint16_t pJsonBufAllLen, JsonParam_S ** pResult )
{
    uint8_t _errFlag;
    uint32_t _retValue;
    JsonParam_S * _tmpRootNodeP;
    JsonParam_S * _tmpCurrNodeP;
    JsonParam_S * _tmpNodeP;
    uint8_t * _tmpP;
    uint8_t * _tmpP2;
    uint8_t * _tmpP1;
    uint32_t i, _tmpStartPos;
    uint16_t _tmpCurIndex;
    uint16_t _tmpAllLen;
    uint16_t _tmpTagNameLen;
    uint16_t _tmpTagValueLen;
    uint16_t _tmpLen;
    uint16_t _tmpU16Value;
    uint32_t _tmpU32Value;
    uint8_t * _tmpFreeP;
    uint16_t _tmpFreeUseCount;
    uint8_t _tmpU8Value;

    _tmpRootNodeP = NULL;
    _tmpCurrNodeP = NULL;
    _tmpAllLen = pJsonStructBufLen;
    _tmpP = pJsonStructBufP;
    _retValue = 0;
    _tmpCurIndex = 0;
    _errFlag = 0;
    _tmpFreeUseCount = 0;
    _tmpFreeP = pFreeP;

    while( _tmpCurIndex < _tmpAllLen )
    {
        i = fun_FindSubStr( &_tmpP[ _tmpCurIndex ], _tmpAllLen - _tmpCurIndex, ( uint8_t * )( &ColonFlag ), 1 );
        if( i != 0xffffffff )
        {
            _tmpLen = ( uint16_t )( i + 1 );
            _tmpP2 = fun_FindSubChar( &_tmpP[ i + _tmpCurIndex ], _tmpLen, QuotationFlag, FIND_INVERT_ORDER );
            if( _tmpP2 != NULL )
            {
                _tmpLen = ( uint32_t )_tmpP2 - ( uint32_t )( &_tmpP[ _tmpCurIndex ] );
                _tmpP1 = fun_FindSubChar( _tmpP2 - 1, _tmpLen, QuotationFlag, FIND_INVERT_ORDER );
                _tmpStartPos = ( uint32_t )_tmpP1 - ( uint32_t )_tmpP;
                _tmpStartPos += 1;  //越过引号
                _tmpTagNameLen = ( uint32_t )_tmpP2 - ( uint32_t )_tmpP1 - 1;   //扣除前后两个引号
                _tmpU16Value = 0;
                _tmpU32Value = fun_GetTagValueType( ( &_tmpP[ i + _tmpCurIndex ] ) + 1 );
                switch ( _tmpU32Value )
                {
                    case JSON_PARAM_TAGVALUE_TYPE:  //TAGNAM AND VALUE
                        _tmpLen = _tmpAllLen - _tmpCurIndex - i - 1;
                        _tmpP1 = fun_GetTagValueAndTagType( &_tmpP[ i + _tmpCurIndex + 1 ], _tmpLen, &_tmpTagValueLen, &_tmpU32Value );
                        if( _tmpP1 != NULL )
                        {
                            _retValue = fun_CreateOrAddJsonResult( &_tmpP[ _tmpStartPos ], _tmpTagNameLen, _tmpP1, _tmpTagValueLen, 
                                                                    _tmpU32Value, _tmpFreeP, &_tmpU16Value, pJsonAllBufP, pJsonBufAllLen, &_tmpNodeP );
                            if( _retValue )
                            {
                                _tmpFreeUseCount += _tmpU16Value;
                                _tmpFreeP += _tmpU16Value;
                                if( _tmpRootNodeP == NULL )
                                {
                                    _tmpRootNodeP = _tmpNodeP;
                                    _tmpCurrNodeP = _tmpNodeP;                                   
                                }
                                else
                                {
                                    _tmpCurrNodeP->nextP = _tmpNodeP;
                                    _tmpCurrNodeP = _tmpNodeP;
                                }

                                _tmpLen = 1;   //TAG NAME引号之前的字符
                                _tmpLen += _tmpTagNameLen + _tmpTagValueLen + 2 + 1; //2个引号和 1个冒号
                                if( _tmpU32Value == JSON_VALUE_STRING )
                                {
                                    _tmpLen += 2;   //2个字符串的引号
                                }

                                _tmpCurIndex += _tmpLen;
                                sub_ClearJsonBuf( &_tmpP[ _tmpStartPos - 2 ], 0, _tmpLen - 1 ); //从第1个引号之前的一个字符开始清理
                            }
                            else
                            {
                                _errFlag = 1;
                            }
                        }
                        else
                        {
                            _errFlag = 1;
                        }
                        break;
                }
            }
            if( _errFlag )
            {
                break;
            }
        }
        else
        {
            _tmpCurIndex += 1;  //TODO:要修改
        }

        if( ( _tmpAllLen - _tmpCurIndex ) < ( 2 + 1 + 1 ) ) //剩余的长度不满足 2个引号 1个冒号 1个逗号
        {
            _retValue = 1;
            *pResult = _tmpRootNodeP;
            *pFreeUseCount = _tmpFreeUseCount;
            sub_ClearJsonBuf( &_tmpP[ _tmpCurIndex ], 0, ( _tmpAllLen - _tmpCurIndex - 1 ) );
            break;
        }
    }

    if( _errFlag )
    {
        _retValue = 0;
    }

    return _retValue;
}

/**
 * @brief 
 * 
 * @param pJsonTagP 
 * @param pJsonTagLen 
 * @param pJsonValueP 
 * @param pJsonValueLen 
 * @param pJsonValueType 
 * @param pBackupFreeP 
 * @param pJsonBufP 
 * @param pJsonBufLen 
 * @param pResultP 
 * @return uint32_t 
 *      0代表出错
 */
uint32_t fun_CreateOrAddJsonResult( uint8_t * pJsonTagP, uint8_t pJsonTagLen, 
                                    uint8_t * pJsonValueP, uint8_t pJsonValueLen, uint8_t pJsonValueType, 
                                    uint8_t * pBackupFreeP, uint16_t * pRetBackUpUseCount, uint8_t * pJsonBufP, uint16_t pJsonBufLen, 
                                    JsonParam_S ** pResultP )
{
    JsonParam_S * _retJsonParamP;
    uint8_t * _tmpP;    
    uint32_t _retValue;
    uint16_t i;
    uint16_t _tmpReqLen;
    uint32_t _tmpU32Value;

    _retValue = 0;
    _tmpReqLen = sizeof( JsonParam_S );
    _tmpReqLen += pJsonTagLen;
    if( pJsonValueType == JSON_VALUE_STRING )
    {
        _tmpReqLen += pJsonValueLen;
    }
    else if( pJsonValueType == JSON_VALUE_DATA )
    {
        _tmpReqLen += sizeof( uint32_t );
    }
    
    _tmpP = fun_FindFreeJsonSpace( pJsonBufP, pJsonBufLen, _tmpReqLen );
    if( _tmpP != NULL )
    {
        _retJsonParamP = ( JsonParam_S * )_tmpP;
    }
    else
    {
        _tmpU32Value = ( uint32_t )pBackupFreeP;
        _tmpReqLen += ( 4 - ( _tmpU32Value & 0x03 ) );
        _tmpU32Value += 3;
        _tmpU32Value &= 0xfffffffc;
        _retJsonParamP = ( JsonParam_S * )( _tmpU32Value );
        *pRetBackUpUseCount = _tmpReqLen;
    }
    _retJsonParamP->nextP = NULL;
    _retJsonParamP->prevP = NULL;
 
    if( pJsonValueType == JSON_VALUE_STRING )
    {
        _retJsonParamP->paramType = JSON_PARAM_TAGVALUE_TYPE;
        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagName = ( uint8_t * )_retJsonParamP + sizeof( JsonParam_S );
        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagNameLen = pJsonTagLen;
        for( i = 0; i < pJsonTagLen; i++ )
        {
            _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagName[ i ] = pJsonTagP[ i ];
        }

        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mValueType = JSON_VALUE_STRING;
        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.JsonValue_U.mJsonStr_S.mStrValueLen = pJsonValueLen;
        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.JsonValue_U.mJsonStr_S.mStrValueP = 
                        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagName + _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagNameLen;
        for( i = 0; i < pJsonValueLen; i++ )
        {
            _retJsonParamP->JsonParamValue_U.mTagAndValue_S.JsonValue_U.mJsonStr_S.mStrValueP[ i ] = pJsonValueP[ i ];
        }
    }
    else if( pJsonValueType == JSON_VALUE_DATA )
    {
        _tmpU32Value = fun_DataBufToUint32Value( pJsonValueP, pJsonValueLen );

        _retJsonParamP->paramType = JSON_PARAM_TAGVALUE_TYPE;
        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagName = ( uint8_t * )_retJsonParamP + sizeof( JsonParam_S );
        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagNameLen = pJsonTagLen;
        for( i = 0; i < pJsonTagLen; i++ )
        {
            _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mTagName[ i ] = pJsonTagP[ i ];
        }

        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.mValueType = JSON_VALUE_DATA;
        _retJsonParamP->JsonParamValue_U.mTagAndValue_S.JsonValue_U.mDataValue = _tmpU32Value;
    }

    _retValue = 1;

    *pResultP = _retJsonParamP;

    return _retValue;
}                                    


/**
 * @brief 
 *      解析json串
 * @param pJsonBufP 
 * @param pJsonLen 
 * @return uint32_t 
 *      0代表解析出错
 */
uint32_t fun_JsonAnalyse( uint8_t * pJsonBufP, uint16_t pJsonLen, uint8_t * pFreeSpaceP, JsonParam_S ** pResultP )
{
    uint32_t i;
    uint16_t _tmpFreeUseCount;
    uint16_t _tmpLen;
    uint16_t _tmpU16Value;
    uint8_t * _tmpP;
    uint8_t * _tmpJsonValueP;
    uint32_t _retValue;
    uint32_t _tmpU32Value;
    uint16_t _tmpStartPos;
    uint16_t _tmpEndPos;
    uint16_t _tmpTagNameLen;
    uint8_t * _tmpBackupFreeP;
    uint8_t * _tmpP1;
    uint8_t * _tmpP2;
    JsonParam_S * _tmpParentNodeP;
    JsonParam_S * _tmpCurrResultP;
    uint32_t _tmpTestCount;         //测试用的

    _tmpTestCount = 0;
    _retValue = 0;
    _tmpBackupFreeP = pFreeSpaceP;
    
    _tmpBackupFreeP = ( uint8_t * )( ( ( ( uint32_t )_tmpBackupFreeP ) + 0x03 ) & 0xfffffffc );
    _tmpTestCount += ( 4 - ( ( uint32_t )pFreeSpaceP & 0x03 ) );

    _retValue = 0;
    //要进行从头的扫描处理
    _tmpP = pJsonBufP;
    i = fun_FindSubStr( _tmpP, pJsonLen, ( uint8_t * )( &ColonFlag ), 1 );
    while( i != 0xffffffff )
    {
        _tmpP = &pJsonBufP[ i ];
        _tmpLen = ( uint32_t )_tmpP - ( uint32_t )pJsonBufP + 1;    //从缓冲区头到冒号位置的字符个数
        _tmpP2 = fun_FindSubChar( _tmpP, _tmpLen, QuotationFlag, FIND_INVERT_ORDER );
        if( _tmpP2 != NULL )
        {
            _tmpLen = ( uint32_t )_tmpP - ( uint32_t )pJsonBufP + 1;    //从缓冲区头到倒序第一个引号位置的字符个数
            _tmpP1 = fun_FindSubChar( _tmpP2 - 1, _tmpLen - 1, QuotationFlag, FIND_INVERT_ORDER );
            if( _tmpP1 != NULL )
            {
                _tmpStartPos = ( uint32_t )_tmpP1 - ( uint32_t )pJsonBufP;
                _tmpStartPos += 1;  //越过引号
                _tmpTagNameLen = ( uint32_t )_tmpP2 - ( uint32_t )_tmpP1 - 1;   //扣除前后两个引号
                _tmpU16Value = 0;
                _tmpU32Value = fun_GetTagValueType( _tmpP + 1 );
                switch ( _tmpU32Value )
                {
                    case JSON_PARAM_TAGVALUE_TYPE:  //TAGNAM AND VALUE
                        _tmpLen = pJsonLen - ( uint32_t )( _tmpP + 1 );
                        _tmpJsonValueP = fun_GetTagValueAndTagType( _tmpP + 1, _tmpLen, &_tmpU16Value, &_tmpU32Value );
                        if( _tmpJsonValueP != NULL )
                        {
                            _tmpFreeUseCount = 0;
                            _retValue = fun_CreateOrAddJsonResult( &pJsonBufP[ _tmpStartPos ], _tmpTagNameLen, 
                                                                _tmpJsonValueP, _tmpU16Value, _tmpU32Value, 
                                                                _tmpBackupFreeP, &_tmpFreeUseCount, pJsonBufP, pJsonLen, &( _tmpParentNodeP ) );
                            _tmpBackupFreeP += _tmpFreeUseCount;
                            
                            _tmpTestCount += _tmpFreeUseCount;
                            
                            _tmpP = fun_FindJsonTagEndPos( _tmpJsonValueP + _tmpU16Value );
                            _tmpEndPos = ( uint32_t )( _tmpP ) - ( uint32_t )( pJsonBufP );
                            sub_ClearJsonBuf( pJsonBufP, _tmpStartPos - 1 - 1,/* 减1 为了从引号开始 1引号前字符*/ _tmpEndPos );
                            
                            if( _retValue == 0 )
                            {
                                _tmpU16Value = 0xaaaa;
                            }
                            else
                            {
                                _retValue = 0;
                            }

                            if( *pResultP == NULL )
                            {
                                *pResultP = _tmpParentNodeP;
                                _tmpCurrResultP = _tmpParentNodeP;
                            }
                            else
                            {
                                _tmpCurrResultP->nextP = _tmpParentNodeP;
                            }
                            
                            _tmpLen = ( uint32_t )pJsonLen - _tmpEndPos;
                            _tmpP = &pJsonBufP[ _tmpEndPos + 1 ];
                            i = fun_FindSubStr( _tmpP, _tmpLen, ( uint8_t * )( &ColonFlag ), 1 );
                            if( i != 0xFFFFFFFF )
                            {
                                i += ( _tmpEndPos + 1 );    //变为从缓冲区头开始的偏移
                            }
                        }
                        else
                        {
                            _tmpU16Value = 0xaaaa;
                        }
                        break;
                        
                    case JSON_PARAM_STRUCT_TYPE:
                        _tmpLen = ( uint32_t )( _tmpP + 1 ) - ( uint32_t )( pJsonBufP );
                        _tmpLen = pJsonLen - _tmpLen;
                        _tmpU16Value = fun_FindJsonStructLen( _tmpP + 1/*加1为了越过冒号*/, _tmpLen );
                        if( _tmpU16Value == 0 )
                        {
                            _tmpU16Value = 0xaaaa;
                        }
                        else
                        {
                            _tmpLen = _tmpU16Value;
                            _tmpFreeUseCount = 0;
                            _retValue = fun_JsonStructHandle( _tmpP + 1/*加1为了越过冒号*/, _tmpLen, _tmpBackupFreeP, &_tmpFreeUseCount, pJsonBufP, pJsonLen, &( _tmpParentNodeP ) );
                            _tmpBackupFreeP += _tmpFreeUseCount;
                            
                            _tmpTestCount += _tmpFreeUseCount;
                            
                            if( _retValue )
                            {
                                if( *pResultP == NULL )
                                {
                                    _tmpFreeUseCount = 0;
                                    _tmpCurrResultP = fun_CreateFreeResultNode( pJsonBufP, pJsonLen, _tmpBackupFreeP, &_tmpFreeUseCount, _tmpTagNameLen );
                                    _tmpBackupFreeP += _tmpFreeUseCount;
                                    *pResultP = _tmpCurrResultP;
                                }

                                sub_FillJsonStructOrArrayTag( JSON_PARAM_STRUCT_TYPE, &pJsonBufP[ _tmpStartPos ], _tmpTagNameLen, _tmpCurrResultP );
                                
                                _tmpCurrResultP->JsonParamValue_U.mStructOrArrayP = _tmpParentNodeP;
                                
                                sub_ClearJsonBuf( pJsonBufP, _tmpStartPos - 1 - 1, _tmpStartPos + _tmpTagNameLen  + 1 + 1 + 1 );

                                _tmpEndPos = _tmpStartPos + _tmpTagNameLen + 1 + _tmpLen + 1;   //加上冒号与结束的特别字符
                                _tmpLen = ( uint32_t )pJsonLen - _tmpEndPos;
                                _tmpP = &pJsonBufP[ _tmpEndPos + 1 ];
                                i = fun_FindSubStr( _tmpP, _tmpLen, ( uint8_t * )( &ColonFlag ), 1 );
                                if( i != 0xFFFFFFFF )
                                {
                                    i += ( _tmpEndPos + 1 );    //变为从缓冲区头开始的偏移
                                }
                            }
                            else
                            {
                                _tmpU16Value = 0xaaaa;
                            }
                        }
                        break;
                    
                    case JSON_PARAM_ARRAY_TYPE:
                        break;
                    
                    default:
                        _tmpU16Value = 0xaaaa;
                        break;
                }
                if( _tmpU16Value == 0xaaaa )
                {
                    break;  //退出循环
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    
    if( i == 0xffffffff )
    {
        _retValue = 1;
    }
    
    return _retValue;
}


/**
 * @brief 
 *      查找指定TAG的分析结果
 * @param pSrcJsonParamP 
 * @param pTagContenP 
 * @param pTagContentLen 
 * @return JsonParam_S* 
 */
JsonParam_S * fun_FindJsonTag( JsonParam_S * pSrcJsonParamP, uint8_t * pTagContenP, uint16_t pTagContentLen )
{
    JsonParam_S * _tmpParamP;
    JsonParam_S * _retP;
    JsonParam_S * _tmpParentP;

    _retP = NULL;
    _tmpParamP = NULL;
    _tmpParamP = pSrcJsonParamP;
    while( _tmpParamP != NULL )
    {
        if( _tmpParamP->paramType == JSON_PARAM_TAGVALUE_TYPE )
        {
            if( _tmpParamP->JsonParamValue_U.mTagAndValue_S.mTagNameLen == pTagContentLen )
            {
                if( memcmp( _tmpParamP->JsonParamValue_U.mTagAndValue_S.mTagName, pTagContenP, pTagContentLen ) == 0 )
                {
                    _retP = _tmpParamP;
                    break;
                }
            }
            
            _tmpParamP = _tmpParamP->nextP;
        }
        else
        {
            //属于结构体与数组
            _tmpParentP = _tmpParamP;
            _tmpParamP = _tmpParentP->JsonParamValue_U.mStructOrArrayP;
            _retP = fun_FindJsonTag( _tmpParamP, pTagContenP, pTagContentLen );
            if( _retP != NULL )
            {
                break;
            }
            else
            {
                _tmpParamP = _tmpParentP->nextP;
                _tmpParentP = NULL;
            }
        }
    }

    return _retP;
}
