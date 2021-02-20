#ifndef MEMORYDISPLAYCLASS_H
#define MEMORYDISPLAYCLASS_H

#include <QPixmap>
#include <qqml.h>
#include <QtQuick/QQuickPaintedItem>
#include <QList>
#include "../Class/drawelementclass.h"

class MemoryDisplayClass : public QQuickPaintedItem
{
    Q_OBJECT
    #ifdef Q_OS_LINUX
    QML_ELEMENT
    #endif

    Q_PROPERTY( int mMemoryItemWidth WRITE sub_SetWidth )
    Q_PROPERTY( int mMemoryItemHeight WRITE sub_SetHeight )

    /***********************************
     * 变量定义
     * ********************************/
private:
    int mWidth;
    int mHeight;
    uint8_t * mMemoryBlockP;
    uint32_t mMemotryBlockSize;
    QPixmap * mDisplayMapP;
    bool mFontSetFlag;
    QList< DrawElementClass * > mDisplayElementS;
    QFont mDisplayFont;
    int mPerFontSize;
    int mOffsetLabelSize;
    int mRowFontCount;
    int mRowHeight;

    /***********************************
     * 函数定义
     * ********************************/
public:
    MemoryDisplayClass( QQuickItem * pParent = nullptr );
    virtual ~MemoryDisplayClass() override;

    void sub_SetWidth( int pWdith );
    void sub_SetHeight( int pHeight );

private:
    void sub_ReadyMemoryDisplayBlock( uint8_t * pDataP, uint32_t pSize );
    QSize fun_CalcMemoryToBitmapSize( uint32_t pMemorySize, int pWdith );
    void sub_CreateMemoryDisplayElementS( uint8_t * pDataP, uint32_t pDataSize, QSize pDestSize );

    /*********************************
     * 系统重载
     * ******************************/
public:
    void paint( QPainter *painter ) override;

signals:

};

#endif // MEMORYDISPLAYCLASS_H
