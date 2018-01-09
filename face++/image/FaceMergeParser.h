#ifndef FACEMERGEPARSER_H
#define FACEMERGEPARSER_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

class FaceMergeParser : public QObject
{
    Q_OBJECT
public:
    explicit FaceMergeParser(QObject *parent = nullptr);

    void parse(const QJsonObject& jsonObject);

signals:

public slots:
};

#endif // FACEMERGEPARSER_H
