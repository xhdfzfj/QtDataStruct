#include <cstring>
#include "Control/guicontrolclass.h"
#include "./cjson/JsonAnalyse.h"
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
