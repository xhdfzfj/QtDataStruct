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
            color: "red"
            Layout.preferredHeight: 60
            Layout.preferredWidth: parent.width
        }

        ScrollView
        {
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height - topToolButtonRect.height

            ListView
            {
                id: listView
                width: parent.width
                model: 20
                clip:true
                delegate: ItemDelegate
                {
                    text: "Item " + (index + 1)
                    width: listView.width
                }
            }
        }
    }
}
