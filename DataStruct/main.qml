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
                        mainColumLayout.changeViewToCjson( memoryDrawItem );
                        MyGuiControlObj.sub_ActiveCLanguageJsonBut( memoryDrawItem );
                    }
                }
                Button
                {
                    id:avlTreeBut
                    anchors.left:cJsonBut.right
                    anchors.leftMargin: 5
                    text:qsTr("平衡树")
                    onClicked:
                    {
                        console.log( qsTr( "Avl Tree Click" ) )
                        mainColumLayout.changeViewToAvlTree();
                        MyGuiControlObj.sbu_ActiveAvlTreeBut( memoryDrawItem );
                    }
                }

                Button
                {
                    id:debugBut
                    anchors.left:parent.right - 100
                    anchors.rightMargin: 5
                    text:qsTr("测试")
                    onClicked:
                    {
                        mainColumLayout.debugTestAction();
                    }
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


        function changeViewToAvlTree()
        {
            currentContentItemType = 2;
            memoryDrawItem.mMemoryItemWidth = mainScrollView.width;
            memoryDrawItem.mMemoryItemHeight = mainScrollView.height
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
                    memoryDrawItem.mMemoryItemWidth = mainScrollView.width;
                }
            }
        }

        function debugTestAction()
        {
            if( currentContentItemType === undefined )
            {
                console.log( "currentContentItemType is invalid" );
            }
            else
            {
                if( currentContentItemType === 1 )  //使用cjson的内存显示方式
                {
                    MyGuiControlObj.sub_CjsonMemoryTest();
                }
                else if( currentContentItemType === 2 )  //测试AVL平衡树
                {
                    MyGuiControlObj.sub_AvlTreeAddNode();
                }
            }
        }

    }
}
