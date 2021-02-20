#include "drawelementclass.h"

/**
 * @brief DrawElementClass::DrawElementClass
 *      构造函数
 */
DrawElementClass::DrawElementClass( QRect pRect, QString pContent )
{
    mRect = pRect;
    mContent = pContent;
}

/**
 * @brief DrawElementClass::~DrawElementClass
 *     析构函数
 */
DrawElementClass::~DrawElementClass()
{

}
