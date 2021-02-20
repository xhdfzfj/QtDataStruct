#ifndef DRAWELEMENTCLASS_H
#define DRAWELEMENTCLASS_H

#include <QRect>
#include <QString>

typedef enum _ColorFlag
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
}ColorFlag;

class DrawElementClass
{
public:
    DrawElementClass( QRect pRect, QString pContent );
    virtual ~DrawElementClass();

private:
    QRect mRect;        //当前的位置与大小
    QString mContent;   //当前的内容
};

#endif // DRAWELEMENTCLASS_H
