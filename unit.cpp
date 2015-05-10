#include "unit.h"
#include <QtMath>
#include <QDebug>
Unit::Unit(QObject *parent) :
    QObject(parent)
{
    init();
}

Unit::Unit(const QSize& screenSize, QObject *parent) :
    QObject(parent)
{
    init(screenSize);
}

Unit::Unit(const QSize &screenSize, const QSize &designedForSize, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize);
}

Unit::Unit(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize, ratioMin);
}

Unit::Unit(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize, ratioMin, ratioMax);
}

Unit::Unit(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, const bool roundUp, QObject *parent) :
    QObject(parent)
{
    init(screenSize, designedForSize, ratioMin, ratioMax, roundUp);
}

qreal Unit::pt(int pixel)
{
    return qreal(pixel) / mRatio;
}

int Unit::px(qreal point)
{
    return scale(point, mRatio);
}

int Unit::scale(qreal point, qreal ratio)
{
    return mRoudUp?qCeil(point * ratio) : qFloor(point * ratio);
}

qreal Unit::ratio()
{
    return mRatio;
}

QString Unit::size()
{
    return QString("%1 x %2").arg(mCurrentSize.width()).arg(mCurrentSize.height());
}

void Unit::roundUp(bool r)
{
    mRoudUp = r;
}

void Unit::computeRatio()
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

void Unit::init(const QSize &screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, const bool roundUp)
{
    mCurrentSize = screenSize;
    mIntendedSize = designedForSize;
    mRatioMin = ratioMin;
    mRatioMax = ratioMax;
    mRoudUp = roundUp;

    computeRatio();
}

