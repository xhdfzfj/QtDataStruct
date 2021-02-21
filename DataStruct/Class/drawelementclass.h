#ifndef DRAWELEMENTCLASS_H
#define DRAWELEMENTCLASS_H

<<<<<<< main
#include <QRect>
=======
<<<<<<< 7099b95a1e0a522b7f3f003a54bdf5f529201b21
=======
#include <QRect>
#include <QColor>
>>>>>>> 内存显示完成了
#include <QString>

typedef enum _ColorFlag
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
<<<<<<< main
}ColorFlag;
=======
    BLACK,
}ColorFlag;
>>>>>>> 内存显示完成了
>>>>>>> 内存显示完成了

class DrawElementClass
{
public:
<<<<<<< main
    DrawElementClass( QRect pRect, QString pContent );
    virtual ~DrawElementClass();

private:
    QRect mRect;        //当前的位置与大小
    QString mContent;   //当前的内容
=======
<<<<<<< 7099b95a1e0a522b7f3f003a54bdf5f529201b21
    DrawElementClass();
=======
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
>>>>>>> 内存显示完成了
>>>>>>> 内存显示完成了
};

#endif // DRAWELEMENTCLASS_H
