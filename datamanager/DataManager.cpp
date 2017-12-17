#include "DataManager.h"


#include <QStandardPaths>
#include <QGuiApplication>
#include <QMessageBox>
#include <QImageReader>
#include <QImageWriter>
#include <QDir>

DataManager::DataManager(QObject *parent) : QObject(parent)
{

}

void DataManager::open()
{
//    QFileDialog dialog(this,);
//    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

//    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first()))
//    {

//    }
}

void DataManager::initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
            ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
    {
        mimeTypeFilters.append(mimeTypeName);
    }

    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    if (acceptMode == QFileDialog::AcceptSave)
    {
        dialog.setDefaultSuffix("jpg");
    }
}

bool DataManager::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();

    if (newImage.isNull())
    {
//        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
//                                 tr("Cannot load %1: %2")
//                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    //setImage(newImage);
   // setWindowFilePath(fileName);

   // const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
   //         .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
   // statusBar()->showMessage(message);
    return true;
}
