#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <strstream>
#include <iomanip>
#include <strstream>
#include <iomanip>
#include "../XhdDefine.h"
#include "../Common.h"
#include "memorydisplayclass.h"

using namespace std;

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
    mFontSetFlag = false;

    sub_SignalsConnect();

    mFontSetFlag = false;
}

/**
 * @brief MemoryDisplayClass::~MemoryDisplayClass
 *      析构函数
 */
MemoryDisplayClass::~MemoryDisplayClass()
{
    DrawElementClass * _tmpObjP;

    if( mTempDataP != nullptr )
    {
        delete mTempDataP;
    }

    if( mDisplayMapP != nullptr )
    {
        delete mDisplayMapP;
    }

    sub_ClearDisplayElementS();
}

/**
 * @brief MemoryDisplayClass::sub_SignalsConnect
 */
void MemoryDisplayClass::sub_SignalsConnect( void )
{
    QObject::connect( this, SIGNAL( widthChanged() ),
                      this, SLOT( sub_WidthChangeSlot() ) );
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

        memset( mTempDataP, 0xFF, pDataSize );

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

    setHeight( _tmpSize.height() );
    mHeight = _tmpSize.height();

    sub_ClearDisplayElementS();
    sub_CreateMemoryDisplayElementS( mMemoryBlockP, mMemotryBlockSize, _tmpSize );
    this->update();

}

/**
 * @brief MemoryDisplayClass::sub_ClearDisplayElementS
 *      清除已有的显示元素
 */
void MemoryDisplayClass::sub_ClearDisplayElementS( void )
{
    DrawElementClass * _tmpObjP;

    while( !mDisplayElementS.empty() )
    {
        _tmpObjP = mDisplayElementS.front();
        delete _tmpObjP;

        mDisplayElementS.pop_front();
    }
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

    if( !mFontSetFlag )
    {
        mDisplayFont = _tmpFont;
        mFontSetFlag = true;
    }
    else
    {
        _tmpFont = mDisplayFont;
    }

    QFontMetrics _tmpFontMetrics(_tmpFont );

    qDebug() << "current font is " << _tmpFont.family();

    QString _testStr( "FF" );

    int _fontWidth;
    int _rowWidth;
    int i;
    int _offsetInfoWidth;

    _fontWidth = _tmpFontMetrics.horizontalAdvance( _testStr );
    _testStr = "F";
    _fontWidth += _tmpFontMetrics.horizontalAdvance( _testStr );

    _testStr = "QQQQQQQQ: ";
    _offsetInfoWidth = _tmpFontMetrics.horizontalAdvance( _testStr );
    mOffsetLabelSize = _offsetInfoWidth;
    mPerFontSize = _fontWidth;

    _rowWidth = 0;
    i = 0;

    while( _rowWidth < ( pWidth - _offsetInfoWidth ) )
    {
        _rowWidth += _fontWidth;
        i += 1;
    }

    mRowFontCount = i;

    qDebug() << "row byte:" << i;

    int _rowHeight = _tmpFontMetrics.height();
    _rowHeight += ( _rowHeight / 2 );

    mRowHeight = _rowHeight;

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
 * @brief MemoryDisplayClass::sub_CreateMemoryDisplayElementS
 *      根据内存的大小生成显示元素
 * @param pDataP
 *
 * @param pDataSize
 * @param pDestSize
 *      目标画布的大小
 */
void MemoryDisplayClass::sub_CreateMemoryDisplayElementS( uint8_t * pDataP, uint32_t pDataSize, QSize pDestSize )
{
    QRect * _tmpRectP;
    DrawElementClass * _tmpDrawObjP;
    uint32_t i, _tmpU32Value;
    QFontMetrics _tmpFontMetrics( mDisplayFont );
    QString _tmpStr;

    int _row;

    int _x;
    int _y;

    i = 0;
    _y = 0;
    _x = 0;

    _row = -1;
    while( i < pDataSize )
    {
        if( i % mRowFontCount == 0 )
        {
            //行首,要加入一个偏移的提示
            if( _row != -1 )
            {
                return;
            }
            _row += 1;
            _tmpRectP = new QRect( 0, _row * mRowHeight, mOffsetLabelSize, mRowHeight );
            _tmpU32Value = _row * mRowFontCount;

            sub_IntToHex( _tmpU32Value, _tmpStr, 8 );
            _tmpStr += ":";
            _tmpDrawObjP = new DrawElementClass( *_tmpRectP, _tmpStr, ColorFlag::BLUE );
            delete _tmpRectP;

            _y = _row * mRowHeight;
            _x = mOffsetLabelSize;

            mDisplayElementS.push_back( _tmpDrawObjP );
        }
        _tmpU32Value = static_cast< uint32_t >( pDataP[ i ] );

        sub_IntToHex( _tmpU32Value, _tmpStr, 2 );

        _tmpRectP = new QRect( _x, _y, mPerFontSize, mRowHeight );
        _tmpDrawObjP = new DrawElementClass( *_tmpRectP, _tmpStr, ColorFlag::GREEN );
        delete _tmpRectP;

        _x += mPerFontSize;

        mDisplayElementS.push_back( _tmpDrawObjP );

        i += 1;
    }

    if( !mDisplayElementS.empty() )
    {
        sub_DrawElementsToPixmap();
    }

    return;
}

/**
 * @brief MemoryDisplayClass::sub_DrawElementsToPixmap
 *      画元素到内存图片上
 */
void MemoryDisplayClass::sub_DrawElementsToPixmap( void )
{
    QPainter * _tmpPainter = new QPainter( mDisplayMapP );
    QColor _tmpColor;
    QRect _tmpRect;
    QString _tmpStr;

    foreach( DrawElementClass * _tmpDrawObjP, mDisplayElementS )
    {
        _tmpColor = _tmpDrawObjP->GetFrontColor();
        _tmpPainter->setPen( _tmpColor );
        _tmpRect = _tmpDrawObjP->GetRect();
        _tmpStr = _tmpDrawObjP->GetContent();
        _tmpPainter->setPen( _tmpColor );
        _tmpPainter->drawText( _tmpRect.x(), _tmpRect.y(), _tmpStr );

        if( _tmpRect.y() == 0 )
        {
            qDebug() << "breakpoint";
        }
    }

    delete _tmpPainter;

    mDisplayMapP->save( "test.bmp" );
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

    if( mDisplayMapP != nullptr )
    {
        painter->drawPixmap( X_SPACE_SIZE, Y_SPACE_SIZE, *mDisplayMapP, 0, 0, mDisplayMapP->width(), mDisplayMapP->height() );

//        QBrush _tmpBrush;
//        QColor _tmpColor( Qt::yellow );

//        _tmpBrush.setColor( _tmpColor );
//        _tmpBrush.setStyle( Qt::BrushStyle::SolidPattern );
//        painter->fillRect( 80, 80, 40, 40, _tmpBrush );
    }
}

/*********************************
 * 以下SLOT部份
 * ******************************/

void MemoryDisplayClass::sub_WidthChangeSlot()
{
    qDebug() << "memory block item width change";
}
