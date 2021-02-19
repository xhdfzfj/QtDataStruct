import QtQuick 2.0

Item
{
    id:xhdtoolbar

    property alias button1Label: button1.text
    property alias button2Label: button2.text
    signal button1Clicked
    signal button2Clicked

    Button
    {
        id: button1
        anchors.left: parent.left; anchors.leftMargin: 5; y: 3; width: 140; height: 32
        onClicked: toolbar.button1Clicked()
    }

    Button
    {
        id: button2
        anchors.right: parent.right; anchors.rightMargin: 5; y: 3; width: 140; height: 32
        onClicked: toolbar.button2Clicked()
    }
}
