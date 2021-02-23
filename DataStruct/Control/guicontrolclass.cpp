#include "../c_language/cjsoninterface.h"
#include "guicontrolclass.h"

/**
 * @brief GuiControlClass::GuiControlClass
 * @param parent
 */
GuiControlClass::GuiControlClass(QObject *parent) : QObject(parent)
{

}

/**
 * @brief GuiControlClass::sub_SignalConntectSlot
 */
void GuiControlClass::sub_SignalConntectSlot()
{
    QObject::connect( this, SIGNAL( guiCLanguageJsonButClickSig() ),
                      this, SLOT( guiCLanguageJsonButClickSlot() ) );
}

/**
 * @brief GuiControlClass::sub_ActiveCLanguageJsonBut
 */
void GuiControlClass::sub_ActiveCLanguageJsonBut( QObject * pDestObjP )
{
    mMemoryDisplayObjP = ( MemoryDisplayClass * ) pDestObjP;

    emit guiCLanguageJsonButClickSig();
}

/**
 * @brief GuiControlClass::sub_CjsonMemoryTest
 */
void GuiControlClass::sub_CjsonMemoryTest( void )
{
    uint8_t * _tmpP;
    uint32_t _tmpValue;

    sub_CjsonMemoryChanage();

    _tmpP = fun_GetCjsonBuf( _tmpValue );
    mMemoryDisplayObjP->sub_ReadyMemoryDisplayBlock( _tmpP, _tmpValue );
}


/*************************************
 * 以下为SLOT实现
 * **********************************/

/**
 * @brief GuiControlClass::guiCLanguageJsonButClickSlot
 */
void GuiControlClass::guiCLanguageJsonButClickSlot()
{
    uint8_t * _tmpP;
    uint32_t _tmpValue;

    _tmpP = fun_GetCjsonBuf( _tmpValue );
    mMemoryDisplayObjP->sub_ReadyMemoryDisplayBlock( _tmpP, _tmpValue );
}
