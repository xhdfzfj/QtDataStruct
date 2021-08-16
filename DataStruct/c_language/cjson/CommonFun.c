/*
 * @Author: your name
 * @Date: 2021-02-22 12:04:08
 * @LastEditTime: 2021-02-24 15:38:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \SourceCode\CommonFun\CommonFun.c
 */
#include <stddef.h>
#include "./CommonFun.h"


inline void FetekMemCpy( void *pDstP, const void *pSrcP, uint32_t pLen )
{  
    uint8_t *DstP = ( uint8_t * )pDstP;
    const uint8_t *SrcP = ( const uint8_t * )pSrcP;

    if ( DstP < SrcP ) //从低地址开始拷贝
    {  
        while ( pLen-- )
        {  
            *( DstP++ ) = *( SrcP++ );
        }  
    }
    else if ( DstP > SrcP ) //从高地址开始拷贝
    {  
        DstP += pLen;
        SrcP += pLen;

        while ( pLen-- )
        {
            *( --DstP ) = *( --SrcP );
        }  
    }
    else
    {
    }
}

/**
 * @brief 
 *      查找子内存
 * @param pSrcDataP 
 * @param pSrcDataLen 
 * @param pDestDataP 
 * @param pDestDataLen 
 * @return uint32_t
 *      0xffffffff 没有找到
 *      其它 子内存的启始下标 
 */
uint32_t fun_FindSubStr( uint8_t * pSrcDataP, uint16_t pSrcDataLen, uint8_t * pDestDataP, uint16_t pDestDataLen )
{
    uint32_t _retValue;
    uint16_t i, j;

    _retValue = 0xffffffff;

    i = 0;
    j = 0;

    if( pSrcDataLen >= pDestDataLen )
    {
        while( i < pSrcDataLen )
        {
            if( pSrcDataP[ i ] == pDestDataP[ j ] )
            {
                j += 1;
                if( j == pDestDataLen )
                {
                    _retValue = i + 1 - j;
                    break;
                }
            }
            else
            {
                j = 0;
            }
            i += 1;
        }
    }

    return _retValue;
}

/**
 * @brief 
 *      查找指定的字符
 * @param pDestP 
 *      目标缓冲区
 * @param pDestLen
 *      目标缓冲区大小 
 * @param pOrder 
 *      查找顺序
 * @return uint8_t* 
 */
uint8_t * fun_FindSubChar( uint8_t * pDestP, uint16_t pDestLen, uint8_t pDestValue, uint8_t pOrder )
{
    uint8_t * _retP;
    uint16_t i;

    _retP = NULL;

    if( pOrder == FIND_POSITION_ORDER )
    {
        //正序
        i = 0;
        while( i < pDestLen )
        {
            if( pDestP[ i ] == pDestValue )
            {
                _retP = &pDestP[ i ];
                break;
            }

            i += 1;
        }
    }
    else
    {
        //倒序
        i = pDestLen;
        while( i > 0 )
        {
            if( *( pDestP - ( pDestLen - i ) ) == pDestValue )
            {
                _retP = pDestP - ( pDestLen - i );
                break;
            }

            i -= 1;
        }
    }
    return _retP;
}

/**
 * @brief 
 * 
 * @param pMemP 
 * @param pMemLen 
 * @return uint32_t 
 */
uint32_t fun_DataBufToUint32Value( uint8_t * pMemP, uint16_t pMemLen )
{
    uint32_t _retValue;
    uint32_t _tmpU32Value;
    uint32_t i, j;

    _retValue = 0;

    for( i = 0; i < pMemLen; i++ )
    {
        _tmpU32Value = *( pMemP + i ) - 0x30;
        for( j = 0; j < ( pMemLen - i - 1 ); j++ )
        {
            _tmpU32Value *= 10;
        }
        _retValue += _tmpU32Value;
    }

    return _retValue;
}

/**
 * @brief
 *      对目标数组进行快速排序
 * @param pDestArrayP
 * @param pDestCount
 */
void sub_SortUint16Array( uint16_t * pDestArrayP, uint16_t pDestCount )
{
    uint16_t _middle;
    uint16_t _tmpU16Value;
    uint16_t _direct;
    uint16_t _tmpLen;
    uint16_t _start, _end;

    if( ( pDestCount == 0 ) || ( pDestCount == 1 ) )
    {
        return;
    }
    else if( pDestCount == 2 )
    {
        if( pDestArrayP[ 0 ] > pDestArrayP[ 1 ] )
        {
            _tmpU16Value = pDestArrayP[ 0 ];
            pDestArrayP[ 0 ] = pDestArrayP[ 1 ];
            pDestArrayP[ 1 ] = _tmpU16Value;
        }

        return;
    }

    _direct = 0;
    _start = 0;
    _tmpLen = pDestCount;
    _end = _tmpLen - 1;

    _middle = pDestArrayP[ _tmpLen >> 1 ];

    if( _middle == 21 )
    {
        printf( "test" );
    }

    while( _start <= _end )
    {
        if( _direct == 0 )
        {
            if( pDestArrayP[ _start ] >= _middle )
            {
                _direct = 1;
            }
            else
            {
                _start += 1;
            }
        }
        else
        {
            if( pDestArrayP[ _end ] <= _middle )
            {
                _tmpU16Value = pDestArrayP[ _end ];
                pDestArrayP[ _end ] = pDestArrayP[ _start ];
                pDestArrayP[ _start ] = _tmpU16Value;
                _direct = 0;
                _start += 1;
                _end -= 1;
            }
            else
            {
                _end -= 1;
            }
        }
    }

    if( _start > _end )
    {
        _tmpU16Value = _end;
        _end = _start;
        _start = _tmpU16Value;
    }
    else if( _start == _end )
    {
        _start -= 1;
    }

    sub_SortUint16Array( &pDestArrayP[ 0 ], _start + 1 );
    sub_SortUint16Array( &pDestArrayP[ _start + 1 ], pDestCount - ( _start + 1 ) );
}
