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
void GuiControlClass::sub_ActiveCLanguageJsonBut()
{
    emit guiCLanguageJsonButClickSig();
}


/*************************************
 * 以下为SLOT实现
 * **********************************/

/**
 * @brief GuiControlClass::guiCLanguageJsonButClickSlot
 */
void GuiControlClass::guiCLanguageJsonButClickSlot()
{
    qDebug( "guiCLanguageJsonButClickSlot" );
}
