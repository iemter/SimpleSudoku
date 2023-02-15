import QtQuick 2.15

Item {
    Rectangle {
        x: (mainWindow.width - 300) / 2
        y: (mainWindow.height - 300) / 2
        width: 300; height: 100
        color: "transparent"

        Image {
            id: youwinText

            source: "pics/you_win.png"
            visible: true
            fillMode: Image.Stretch

        }
    }


}
