#include "drawelementclass.h"

/**
 * @brief DrawElementClass::DrawElementClass
 *      构造函数
 */
DrawElementClass::DrawElementClass( QRect pRect, QString pContent, ColorFlag pColor )
{
    mRect = pRect;
    mContent = pContent;
    mColor = pColor;
    mBorderFlag = false;
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
}

/**
 * @brief DrawElementClass::~DrawElementClass
 *     析构函数
 */
DrawElementClass::~DrawElementClass()
{

}
