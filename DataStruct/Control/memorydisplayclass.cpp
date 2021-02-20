#include <QDebug>
#include <QFontMetrics>
#include "../XhdDefine.h"
#include "memorydisplayclass.h"

uint8_t * mTempDataP;

/**
 * @brief MemoryDisplayClass::MemoryDisplayClass
 *      构造函数
 * @param pParent
 */
MemoryDisplayClass::MemoryDisplayClass( QQuickItem * pParent ) : QQuickPaintedItem( pParent )
{
    qDebug() << "MemoryDisplayClass 初始化";
    mMemoryBlockP = nullptr;
    mTempDataP = nullptr;
    mDisplayMapP = nullptr;
}

/**
 * @brief MemoryDisplayClass::~MemoryDisplayClass
 *      析构函数
 */
MemoryDisplayClass::~MemoryDisplayClass()
{
    if( mTempDataP != nullptr )
    {
        delete mTempDataP;
    }

    if( mDisplayMapP != nullptr )
    {
        delete mDisplayMapP;
    }
}

/**
 * @brief MemoryDisplayClass::sub_SetWidth
 *      QML中调用设置ITEM的宽度
 * @param pWdith
 */
void MemoryDisplayClass::sub_SetWidth( int pWidth )
{
    mWidth = pWidth;
    setWidth( mWidth );

    sub_ReadyMemoryDisplayBlock( nullptr, DEFAULT_MEMORY_BLOCK_SIZE );

    update();
}

/**
 * @brief MemoryDisplayClass::sub_SetHeight
 *      QML中调用设置ITEM的高度
 * @param pHeight
 */
void MemoryDisplayClass::sub_SetHeight( int pHeight )
{
    mHeight = pHeight;
    setHeight( mHeight );
    update();
}

/**
 * @brief MemoryDisplayClass::sub_ReadyMemoryDisplayBlock
 *      准备进行内存的显示
 * @param pDataP
 * @param pDataSize
 */
void MemoryDisplayClass::sub_ReadyMemoryDisplayBlock( uint8_t * pDataP, uint32_t pDataSize )
{
    if( pDataP == nullptr )
    {
        if( mTempDataP == nullptr )
        {
            mTempDataP = new uint8_t [ pDataSize ];
        }
        else
        {
            delete mTempDataP;
            mTempDataP = new uint8_t [ pDataSize ];
            memset( mTempDataP, 0xFF, pDataSize );
        }

        mMemoryBlockP = mTempDataP;
        mMemotryBlockSize = pDataSize;
    }
    else
    {
        if( mMemoryBlockP != pDataP )
        {
            mMemoryBlockP = pDataP;
            mMemotryBlockSize = pDataSize;
        }
    }

    QSize _tmpSize = fun_CalcMemoryToBitmapSize( mMemotryBlockSize, mWidth - ( 2 * X_SPACE_SIZE ) );

    if( mDisplayMapP != nullptr )
    {
        delete mDisplayMapP;
    }

    mDisplayMapP = new QPixmap( _tmpSize );
}

/**
 * @brief MemoryDisplayClass::fun_CalcMemoryToBitmapSize
 *      计算出要显示指定大小的内存所要的Pixmap的大小
 * @param pMemorySize
 * @return
 */
QSize MemoryDisplayClass::fun_CalcMemoryToBitmapSize( uint32_t pMemorySize, int pWidth )
{
    QSize _retSize;
    QFont _tmpFont;
    QFontMetrics _tmpFontMetrics(_tmpFont );

    qDebug() << "current font is " << _tmpFont;

    QString _testStr( "FF" );

    int _fontWidth;
    int _rowWidth;
    int i;
    int _offsetInfoWidth;

    _fontWidth = _tmpFontMetrics.horizontalAdvance( _testStr );
    _testStr = "F";
    _fontWidth += _tmpFontMetrics.horizontalAdvance( _testStr );

    _testStr = "FFFFFFFF: ";
    _offsetInfoWidth = _tmpFontMetrics.horizontalAdvance( _testStr );

    _rowWidth = 0;
    i = 0;

    while( _rowWidth < ( pWidth - _offsetInfoWidth ) )
    {
        _rowWidth += _fontWidth;
        i += 1;
    }

    qDebug() << "row byte:" << i;

    int _rowHeight = _tmpFontMetrics.height();
    _rowHeight += ( _rowHeight / 2 );

    int _tmpSize = static_cast< int >( pMemorySize );

    int _height;

    _height = 0;
    if( i != 0 )
    {
        _height = ( _tmpSize + i - 1 ) / i;
        _height *= _rowHeight;
    }
    _retSize.setWidth( _rowWidth );
    _retSize.setHeight( _height );

    return _retSize;
}


/**
 * @brief MemoryDisplayClass::paint
 *      系统要求重载的函数
 * @param painter
 */
void MemoryDisplayClass::paint( QPainter *painter )
{
    qDebug() << "宽度" << this->width();
    qDebug() << "高度" << this->height();
}
