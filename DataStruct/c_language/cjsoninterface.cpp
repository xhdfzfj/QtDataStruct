#include <cstring>
#include "Control/guicontrolclass.h"
#include "./cjson/JsonAnalyse.h"
#include "./cjson/CommonFun.h"
#include "./cjsoninterface.h"

/****************************************
 * 外部变量导入
 * *************************************/
extern GuiControlClass gGuiContrlObj;

/***************************************
 * 变量申明
 * ************************************/
uint8_t gCjsonBuf[ 1024 ];

uint8_t * fun_GetCjsonBuf( uint32_t & pRetBufSize )
{
    pRetBufSize = 1024;
    return gCjsonBuf;
}

void sub_CjsonMemoryChanage()
{
    JsonParam_S * _retResultP;
    uint8_t * _tmpP;
    uint16_t _tmpLen;

    _retResultP = nullptr;
    strcpy( ( char * )gCjsonBuf, "{\"paramters\":{\"tag1\":123456,\"tag2\":654321,\"tag3\":\"1234567890098765\"},\"command\":\"testcommand\"}" );
    _tmpLen = ( uint16_t )strlen( ( char * )gCjsonBuf );
    _tmpP = &gCjsonBuf[ _tmpLen + 1 ];

    fun_JsonAnalyse( gCjsonBuf, _tmpLen, _tmpP, &_retResultP );
}

/**
 * @brief sub_TestQuickSort
 *      测试快速排序
 */
uint16_t _testArray[] = { 10, 9,  6,  3,  4,  8,  7,  11, 14, 18, 6,  5,  2,  1,  0,
                          11, 12, 87, 64, 33, 43, 21, 12, 56, 19, 67, 90, 73, 77, 23,
                          91, 87, 56, 43, 35, 99, 24, 48, 76, 61, 64, 82, 83, 14, 29 };
//uint16_t _testArray[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
//                          10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
void sub_TestQuickSort( void )
{

    sub_SortUint16Array( &_testArray[ 0 ], 45 );
    printf( "end" );

    //uint16_t _testArray[] = { 10, 13, 12 };

    //sub_SortUint16Array( &_testArray[ 0 ], 3 );
}
