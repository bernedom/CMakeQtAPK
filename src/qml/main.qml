import QtQuick 2.11
import QtQuick.Window 2.11

Window{
    id: mainWindow
    objectName: "mainWindow"

    visible: true
    title: "QML for Android Example"
    width: 800
    height: 600

    Connections{
        target: SlideShow
        function onImageChanged(str : string) {
            changeImage(str)
            }
        }

    

    function changeImage(str : string)
    {
        img.source = str
    }

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
        id: img
        objectName: "img"
        anchors.centerIn: parent
        cache: false
        source: "/sunset0.jpg"
    }

    }
}