#include <functional>
#include <QTime>
#include <QRandomGenerator>
#include <QDebug>
#include "../c_language/cjsoninterface.h"
#include "guicontrolclass.h"

/**
 * @brief GuiControlClass::GuiControlClass
 * @param parent
 */
GuiControlClass::GuiControlClass(QObject *parent) : QObject(parent)
{
    mAvlTreeObjP = nullptr;
}

/**
 * @brief GuiControlClass::sub_SignalConntectSlot
 */
void GuiControlClass::sub_SignalConntectSlot()
{
    QObject::connect( this, SIGNAL( guiCLanguageJsonButClickSig() ),
                      this, SLOT( guiCLanguageJsonButClickSlot() ) );
    QObject::connect( this, SIGNAL( guiAvlTreeButClickSig() ),
                      this, SLOT( guiAvlTreeButClickSlot() ) );
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
 * @brief GuiControlClass::sbu_ActiveAvlTreeBut
 *      准备进行平衡树的测试
 * @param pDestObjP
 */
void GuiControlClass::sbu_ActiveAvlTreeBut( QObject * pDestObjP )
{
    mMemoryDisplayObjP = ( MemoryDisplayClass * )pDestObjP;
    emit guiAvlTreeButClickSig();
}

/**
 * @brief GuiControlClass::sub_AvlTreeAddNode
 *      一步一动的向AVL树加入节点
 */
void GuiControlClass::sub_AvlTreeAddNode( void )
{
    int _tmpTestValue;

    do
    {
        _tmpTestValue = QRandomGenerator::global()->bounded( 1000 );
    }while( mAvlTreeObjP->fun_JudgeExistCompareValue( _tmpTestValue ) );

    mAvlTreeObjP->sub_InsertNode( _tmpTestValue, _tmpTestValue );
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

/**
 * @brief GuiControlClass::sub_AvlTreeCallBack
 *      给平衡树的专用回调接口
 * @param pNewNode
 */
void GuiControlClass::sub_AvlTreeCallBack( TreeNodeClass< int, int > * pNewNode )
{
    qDebug() << "test test test callback";
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

/**
 * @brief GuiControlClass::guiAvlTreeButClickSlot
 *      AVLTREE测试准备
 */
void GuiControlClass::guiAvlTreeButClickSlot()
{
    if( mAvlTreeObjP != nullptr )
    {
        delete mAvlTreeObjP;
    }

    mAvlTreeObjP = new AvlTreeClass< int, int >();

    function< void( TreeNodeClass< int, int > * ) > _tmpFun;

    _tmpFun = std::bind( &GuiControlClass::sub_AvlTreeCallBack, this, std::placeholders::_1 );
    mAvlTreeObjP->sub_SetUiDisplayCallBack( _tmpFun );
}
