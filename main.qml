import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 700
    title: qsTr("Face++")

    property string photoUrl1;
    property string photoUrl2;
    property int buttonId: 1;

    Image
    {
        x:200;
        id:photo;
    }

    Button
    {
        implicitWidth:200
        text:"photo load"
        onClicked:
        {
           buttonId = 1;
           fileDialog.open();
        }
    }

    Button
    {
        implicitWidth:200
        y:50;
        text:"photo load 2"
        onClicked:
        {
           buttonId = 2;
           fileDialog.open();
        }
    }

    Button
    {
        implicitWidth:200
        y:100;
        text:"run"
        onClicked:
        {
            controller.run(photoUrl1);//, photoUrl2);
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.desktop
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        onAccepted: {
            photo.source = fileDialog.fileUrls[0];

            if (buttonId == 1)
            {
                photoUrl1 = photo.source;
            }
            else
            {
                 photoUrl2 = photo.source;
            }
        }
        onRejected: {
            console.log("Canceled")
        }
    }

}
