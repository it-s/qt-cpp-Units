#include "Units.h"
#include <QtMath>
#include <QDebug>
Units::Units(QObject *parent) :
    QObject(parent)
{
    init();
}

Units::Units(const QSize& screenSize, QObject *parent) :
    QObject(parent)
{
    init(screenSize);
}

Units::Units(const QSize &screenSize, const QSize &designedForSize, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize);
}

Units::Units(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize, ratioMin);
}

Units::Units(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize, ratioMin, ratioMax);
}

Units::Units(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, const bool roundUp, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize, ratioMin, ratioMax, roundUp);
}

qreal Units::pt(int pixel)
{
    return qreal(pixel) / mRatio;
}

int Units::px(qreal point)
{
    return scale(point, mRatio);
}

int Units::scale(qreal point, qreal ratio)
{
    return mRoudUp?qCeil(point * ratio) : qFloor(point * ratio);
}

qreal Units::ratio()
{
    return mRatio;
}

QString Units::size()
{
    return QString("%1 x %2").arg(mCurrentSize.width()).arg(mCurrentSize.height());
}

void Units::roundUp(bool r)
{
    mRoudUp = r;
}

void Units::computeRatio()
{

    qreal d= qSqrt(qPow(mIntendedSize.width(),2)+ qPow(mIntendedSize.height(), 2));

    //Compute the diagonal length of the current app window (IS)
    qreal appd =  qSqrt(qPow(mCurrentSize.width(),2)+ qPow(mCurrentSize.height(), 2));

    //Calculate the ration between what IS and what SHOULD be
    mRatio = appd/d;

    if (qAbs(mRatio) < qAbs(mRatioMin)) mRatio = mRatioMin;
    if (qAbs(mRatio) > qAbs(mRatioMax)) mRatio = mRatioMax;

    qDebug()<<"RATIO COMPUTED "<<mRatio;

    emit ratioChanged();
}

void Units::init(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, const bool roundUp)
{
    mCurrentSize = screenSize;
    mIntendedSize = designedForSize;
    mRatioMin = ratioMin;
    mRatioMax = ratioMax;
    mRoudUp = roundUp;

    computeRatio();
}

