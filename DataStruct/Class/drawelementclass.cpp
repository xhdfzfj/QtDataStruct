#include "drawelementclass.h"

<<<<<<< main
=======
<<<<<<< 7099b95a1e0a522b7f3f003a54bdf5f529201b21
DrawElementClass::DrawElementClass()
=======
>>>>>>> 内存显示完成了
/**
 * @brief DrawElementClass::DrawElementClass
 *      构造函数
 */
<<<<<<< main
DrawElementClass::DrawElementClass( QRect pRect, QString pContent )
{
    mRect = pRect;
    mContent = pContent;
=======
DrawElementClass::DrawElementClass( QRect pRect, QString pContent, ColorFlag pColor )
{
    mRect = pRect;
    mContent = pContent;
    mColor = pColor;
    if( mColor == ColorFlag::BLACK )
    {
        mFrontColor.setRgb( 0, 0, 0, 255 );
    }
    else if( mColor == ColorFlag::BLUE )
    {
        mFrontColor = Qt::blue;
    }
    else if( mColor == ColorFlag::GREEN )
    {
        mFrontColor = Qt::green;
    }
    else if( mColor == ColorFlag::RED )
    {
        mFrontColor = Qt::red;
    }
    else if( mColor == ColorFlag::YELLOW )
    {
        mFrontColor = Qt::yellow;
    }
>>>>>>> 内存显示完成了
}

/**
 * @brief DrawElementClass::~DrawElementClass
 *     析构函数
 */
DrawElementClass::~DrawElementClass()
<<<<<<< main
=======
>>>>>>> 内存显示完成了
>>>>>>> 内存显示完成了
{

}
