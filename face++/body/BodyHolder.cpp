#include "BodyHolder.h"

BodyHolder::BodyHolder(QObject *parent) : QObject(parent)
{

}


void BodyHolder::flush()
{
    _isReady = false;
}

bool BodyHolder::ready() const
{
    return _isReady;
}


void BodyHolder::newBodyData(const Body& body)
{
    _body = body;
    _isReady = true;
}


QRect BodyHolder::getBodyRect() const
{
    return _body.getHumanbodyRectangle();
}
