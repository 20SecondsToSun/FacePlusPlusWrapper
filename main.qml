import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Face++")

    Button
    {
        implicitWidth:200
        text:"photo load"
        onClicked:
        {
            dataManager.open();
        }
    }


    Button
    {
        implicitWidth:200
        y:50;
        text:"run"
        onClicked:
        {
            controller.run();
        }
    }

}
