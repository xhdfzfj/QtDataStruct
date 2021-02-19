#ifndef MEMORYDISPLAYCLASS_H
#define MEMORYDISPLAYCLASS_H

#include <QtQuick/QQuickPaintedItem>

class MemoryDisplayClass : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY( int mMemoryItemWidth WRITE sub_SetWidth );
    Q_PROPERTY( int mMemoryItemHeight WRITE sub_SetHeight );

    /***********************************
     * 变量定义
     * ********************************/
private:
    int mWidth;
    int mHeight;

    /***********************************
     * 函数定义
     * ********************************/
public:
    MemoryDisplayClass( QQuickItem * pParent = nullptr );

    void sub_SetWidth( int pWdith );
    void sub_SetHeight( int pHeight );

    void paint( QPainter *painter );    //系统要求重载的

signals:

};

#endif // MEMORYDISPLAYCLASS_H
