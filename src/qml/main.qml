import QtQuick 2.11
import QtQuick.Window 2.11

Window{
    id: mainWindow
    objectName: "mainWindow"

    visible: true
    title: "QML for Android Example"
    width: 800
    height: 600

    Item
    {
        focus: true

        anchors.top: parent.top
        anchors.left: parent.left

        height: parent.height
        width: parent.width

        Keys.onEscapePressed: {
            mainWindow.close()
            event.accepted = true;
        }

    Image {
        anchors.centerIn: parent
        source: "/sunset.jpg"
    }

    }
}