#ifndef DRAWELEMENTCLASS_H
#define DRAWELEMENTCLASS_H

#include <QRect>
#include <QColor>
#include <QString>

typedef enum _ColorFlag
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
}ColorFlag;

class DrawElementClass
{
public:
    DrawElementClass( QRect pRect, QString pContent, ColorFlag pColor = ColorFlag::BLACK );
    virtual ~DrawElementClass();

public:
    QColor GetFrontColor()  {   return mFrontColor; }
    QRect GetRect()         {   return mRect; }
    QString GetContent()    {   return mContent; }

private:
    QRect mRect;        //当前的位置与大小
    QString mContent;   //当前的内容
    ColorFlag mColor;
    QColor mFrontColor;
};

#endif // DRAWELEMENTCLASS_H
