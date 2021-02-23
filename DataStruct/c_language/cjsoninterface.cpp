#include "Control/guicontrolclass.h"
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
    gCjsonBuf[ 0 ] = 0xAA;
    gCjsonBuf[ 256 ] = 0xBB;
}
