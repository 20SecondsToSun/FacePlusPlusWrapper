import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 700
    title: qsTr("Face++")

    property string photoUrl;

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
           fileDialog.open();
        }
    }

    Button
    {
        implicitWidth:200
        y:50;
        text:"run"
        onClicked:
        {
            controller.run(photoUrl);
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.desktop
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        onAccepted: {
            photo.source = photoUrl = fileDialog.fileUrls[0];

        }
        onRejected: {
            console.log("Canceled")
        }
    }

}
