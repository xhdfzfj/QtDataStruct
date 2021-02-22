import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import xhd.memory.drawitem 1.0

ApplicationWindow {
    width: 1024
    height: 768
    visible: true
    title: qsTr("开放平台")

    ColumnLayout
    {
        id:mainColumLayout
        anchors.fill: parent

        Rectangle
        {
            id:topToolButtonRect
            //color: "red"
            Layout.preferredHeight: 60
            Layout.preferredWidth: parent.width
            RowLayout
            {
                anchors.fill: parent
                Button
                {
                    id: cJsonBut
                    anchors.left: parent.left
                    anchors.leftMargin: 5       //这个属性在 anchors.left后才生效
                    text: qsTr("C语言JSON")
                    onClicked:
                    {
                        console.log( qsTr( "c language json click" ) );
                        MyGuiControlObj.sub_ActiveCLanguageJsonBut();
                        mainColumLayout.changeViewToCjson();
                    }
                }
                Button
                {
                    id:debugBut
                    anchors.left:cJsonBut.right
                    anchors.leftMargin: 5
                    text:qsTr("测试")
                }
            }
        }

        ScrollView
        {
            id:mainScrollView
            clip: true
            Layout.preferredWidth: parent.width

            Layout.preferredHeight: parent.height - topToolButtonRect.height

            onWidthChanged:
            {
                console.log( "ScrollView width chanage" );
                mainColumLayout.sizeChanageLinkAction( 0 );
            }
            onHeightChanged:
            {
                console.log( "ScrollView height chanage" );
                contentHeight = 5000;
                mainColumLayout.sizeChanageLinkAction( 1 );
            }

            XhdMemoryDrawItem
            {
                id:memoryDrawItem
            }
        }

        /************************************
         * JS函数部份
         ************************************/
        property var currentContentItemType;    //1代表cjson的内存为示
        property var cjsonGuiObj;
        property var cjsonItemObj;

        function changeViewToCjson()
        {
            console.log( "changeViewToCjson" );
            currentContentItemType = 1;
//            cjsonGuiObj = Qt.createComponent( "CjsonGui.qml" );
//            currentContentItemType = 1;
//            if( cjsonGuiObj.status === Component.Ready )
//            {
//                console.log( "createComponent ready" );

//                cjsonItemObj = cjsonGuiObj.createObject( mainScrollView );
//                mainScrollView.contentItem = cjsonItemObj;
//                mainScrollView.contentItem.parent = mainScrollView;

//                cjsonItemObj.memoryDrawWidth = mainScrollView.width;
//                mainScrollView.update();
//            }
//            else
//            {
//                console.log( "createComponent error" );
//            }
            memoryDrawItem.mMemoryItemWidth = mainScrollView.width;
        }


        function sizeChanageLinkAction( pSizeChangeType )
        {
            console.log( "qml:sizeChangeLinkAction " + pSizeChangeType );
            if( currentContentItemType === undefined )
            {
                console.log( "currentContentItemType is invalid" );
            }
            else
            {
                if( currentContentItemType === 1 )  //使用cjson的内存显示方式
                {
//                    if( cjsonItemObj !== undefined )
//                    {
//                        if( pSizeChangeType === 0 )
//                        {
//                            cjsonItemObj.memoryDrawWidth = mainScrollView.width;

//                        }
//                    }
                    memoryDrawItem.mMemoryItemWidth = mainScrollView.width;
                }
            }
        }

    }
}
