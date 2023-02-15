import QtQuick 2.15
import QtQuick.Window 2.15
import "components" // import all components
import QtQuick.Layouts
import QtQuick.Controls 2.15
import com.sudoku.app 1.0

Window {
    id: mainWindow
    width: 400
    height: 640
    visible: true
    title: qsTr("Test Sudoku")

    property int pickedNumber: 1; // currently picked number
    property int pickedX
    property int pickedY
    property bool shouldCheck: false

    // change field color depending on options picked
    function getFieldColor(idx)
    {

        if (SudokuField.field[idx].isFixed) {
            return "#2A2878"
        }

        else {
            if(shouldCheck)
            {
                if (SudokuField.field[idx].isCorrect) {
                    if (fieldGrid.currentIndex == idx) {
                        return "#437067"
                    }
                    else {
                        return "#63A89A"
                    }
                }
                else {
                    if (fieldGrid.currentIndex == idx) {
                        return "#613342"
                    }
                    else {
                        return "#965167"
                    }
                }
            }

            else {
                if (fieldGrid.currentIndex == idx) {
                    return "#6875A1"
                }
                else {
                    return "silver"
                }
            }
        }
    }

    // background image
    Image {
        width: mainWindow.width
        height: mainWindow.height
        source: "pics/backgroundCropped.jpg"
        visible: true
        fillMode: Image.Stretch
    }

    // GAME ITEM

    Item {
        id: sudokuGameItem

        visible: SudokuField.isFinished? false : true

        // button to change game
        Rectangle {
            x: (mainWindow.width - 300) / 2
            y: (mainWindow.height - 300) / 2 - 50
            width: 297; height: 33

            gradient: Gradient {
                GradientStop {position: 0.0; color: "#626F99" }
                GradientStop {position: 1.0; color: "#94938E" }
            }
            border.width: 3
            border.color: "#3A498A"

            Text {
                anchors.centerIn:  parent
                font.pixelSize: 10
                font.family: "Comfortaa Bold"
                text: "load new game"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    SudokuField.writeField()
                }
            }
        }

        // number field to enter numbers
        // is at some point also supposed to show the amount of each number
        Rectangle {
            x: (mainWindow.width - 300) / 2
            y: (mainWindow.height - 300) / 2 + 316
            width: 297; height: 33

            Row {
                spacing: 0
                width: parent.width
                height: parent.height
                Repeater {
                    model: 9
                    Rectangle {
                        width: 33; height: 33;
                        gradient: Gradient {
                            GradientStop {position: 0.0; color: "#626F99" }
                            GradientStop {position: 1.0; color: "#94938E" }
                        }
                        border.width: 3
                        border.color: pickedNumber == (index + 1)? "#63458A" : "#3A498A"

                        Text {
                            anchors.centerIn:  parent
                            font.pixelSize: 10
                            font.family: "Comfortaa Bold"
                            text: index + 1
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                pickedNumber = index + 1

                                SudokuField.field[fieldGrid.currentIndex].setCurrentNumber(pickedNumber)
                            }

                        }
                    }
                }
            }
        }

        // now being smarter with my 9x9 sudoku grid, using GridView which has an
        // index option (currentIndex)

        // sudoku field
        Rectangle {
            x: (mainWindow.width - 300) / 2
            y: (mainWindow.height - 300) / 2
            width: 300; height: 300
            color: "transparent"
            border.color:  "#030327"; border.width: 3



            GridView {
                id: fieldGrid
                anchors.fill: parent
                // x: (mainWindow.width - 300) / 2
                // y: (mainWindow.height - 300) / 2

                cellWidth: 33; cellHeight: 33
                width: parent.width
                height: parent.height
                model: SudokuField.field // need to instantiate it this way

                // // creating extra border around 3x3 grids
                Grid {
                    columns: 3; spacing: 0
                    Repeater { // repeater to make 9 identical rectangle borders
                        model: 9
                        Rectangle {color: "transparent"; border.color: "#1A184A"; width: 100; height: 100; border.width: 3}
                    }
                }

                Component { // delegate for rendering
                    id: fieldDelegate
                    Rectangle {
                        id: wrapper
                        // color: fieldGrid.currentIndex == index ? "#6875A1" : "silver"
                        color: getFieldColor(index)
                        width: fieldGrid.cellWidth
                        height: fieldGrid.cellHeight
                        border.color: "#030327"

                        Text {
                            anchors.centerIn: parent
                            font.pixelSize: 12
                            font.family: "Comfortaa Bold"
                            font.bold: SudokuField.field[index].isFixed? true : false
                            color: SudokuField.field[index].isFixed? "white" : "black"
                            text: SudokuField.field[index].currentNumber == 0? "": SudokuField.field[index].currentNumber // replace 0 with empty string
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                fieldGrid.currentIndex = index
                                pickedX = parent.x
                                pickedY = parent.y
                            }
                        }
                    }
                }

                delegate: fieldDelegate
                focus: true
            }

        }


        // options
        Rectangle {
            id: optionsParent
            x: (mainWindow.width - 300) / 2
            y: (mainWindow.height - 300) / 2 + 366
            width: 297; height: 50
            color: "transparent"
            border.color: "transparent"

            Column {

                Rectangle {
                    width: optionsParent.width; height: optionsParent.height / 2
                    color: "transparent"
                    border.color: "transparent"
                    Row {
                        anchors.fill: parent
                        Text {
                            text: "Continuiously check?"
                            font.pixelSize: 10
                            anchors.verticalCenter: parent.verticalCenter
                            font.family: "Comfortaa Bold"
                            color: "white"
                        }
                        Switch {
                            checked: false
                            anchors.verticalCenter: parent.verticalCenter
                            onCheckedChanged: {
                                shouldCheck = checked
                            }
                        }
                    }
                }
            }
        }
    }

    Item {
        id: endscreenItem
        visible: SudokuField.isFinished? true:false
        Rectangle {
            id: imRect
            x: (mainWindow.width - 300) / 2
            y: (mainWindow.height - 300) / 2
            width: 300; height: 70
            color: "transparent"

            Image {
                id: youwinText
                width: parent.width
                height: parent.height
                source: "pics/you_win.png"
                visible: true
                fillMode: Image.Stretch

            }
        }




        // cute gif

        AnimatedImage {
            x: imRect.x
            y: imRect.y + 250
            width: 200
            height: 200

            source: "pics/cute_cat.gif"
            playing: true
            fillMode: Image.Stretch
        }

        // button to load new game from endscreen
        Rectangle {
            x: imRect.x
            y: imRect.y + 100
            width: 297; height: 33

            gradient: Gradient {
                GradientStop {position: 0.0; color: "#626F99" }
                GradientStop {position: 1.0; color: "#94938E" }
            }
            border.width: 3
            border.color: "#3A498A"

            Text {
                anchors.centerIn:  parent
                font.pixelSize: 10
                font.family: "Comfortaa Bold"
                text: "load new game"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    SudokuField.writeField()
                }
            }
        }


    }



}
