import QtQuick 2.0
import xhd.memory.drawitem 1.0

Item
{
    id:xhdTestItem;

    //property alias cjsonRectWidth: cjsonRect.width
    //property alias cjsonRectHeight: cjsonRect.height
    property alias memoryDrawWidth : memoryDrawItem.mMemoryItemWidth
    property alias memoryDrawHeight : memoryDrawItem.mMemoryItemHeight

    //Rectangle
    //{
        //id:cjsonRect

        XhdMemoryDrawItem
        {
            id:memoryDrawItem
            onWidthChanged:
            {
                console.log( qsTr("width size change") );
            }
        }
    //}

    Component.onCompleted:
    {
        console.log( qsTr( "cjson gui 实例" ) );
        //memoryDrawItem.mMemoryItemWidth = 100;
    }
}
