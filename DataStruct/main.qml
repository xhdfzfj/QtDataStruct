import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 1024
    height: 768
    visible: true
    title: qsTr("Scroll")

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
            }
        }

        ScrollView
        {
            id:mainScrollView
            objectName: mainScrollViewObj
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height - topToolButtonRect.height


        }

        property var cjsonGuiObj;
        property var cjsionItemObj;
        function changeViewToCjson()
        {
            //mainScrollView.contentItem = CjsonGui;
            cjsonGuiObj = Qt.createComponent( "CjsonGui.qml" );
            if( cjsonGuiObj.status == Component.Ready )
            {
                console.log( "createComponent ready" );

                cjsionItemObj = cjsonGuiObj.createObject( mainScrollView.contentItem );
                //cjsionItemObj.cjsonRectWidth = mainScrollView.width;
                //cjsionItemObj.cjsonRectHeight = 100;

                cjsionItemObj.memoryDrawWidth = mainScrollView.width;
                cjsionItemObj.memoryDrawHeight = 200;
            }
        }
    }
}
