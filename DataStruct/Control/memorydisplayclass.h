#ifndef MEMORYDISPLAYCLASS_H
#define MEMORYDISPLAYCLASS_H

#include <QPixmap>
#include <qqml.h>
#include <QtQuick/QQuickPaintedItem>

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

    /***********************************
     * 函数定义
     * ********************************/
public:
    MemoryDisplayClass( QQuickItem * pParent = nullptr );
    virtual ~MemoryDisplayClass();

    void sub_SetWidth( int pWdith );
    void sub_SetHeight( int pHeight );

private:
    void sub_ReadyMemoryDisplayBlock( uint8_t * pDataP, uint32_t pSize );
    QSize fun_CalcMemoryToBitmapSize( uint32_t pMemorySize, int pWdith );

    /*********************************
     * 系统重载
     * ******************************/
public:
    void paint( QPainter *painter );

signals:

};

#endif // MEMORYDISPLAYCLASS_H
