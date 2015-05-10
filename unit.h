#ifndef UNIT_H
#define UNIT_H
#include <QObject>
#include <QScreen>
class Unit : public QObject
{
    Q_OBJECT

public:
    explicit Unit(QObject *parent = 0);
    explicit Unit(const QSize& screenSize, QObject *parent = 0);
    explicit Unit(const QSize& screenSize, const QSize &designedForSize, QObject *parent = 0);
    explicit Unit(const QSize& screenSize, const QSize &designedForSize, const qreal ratioMin, QObject *parent = 0);
    explicit Unit(const QSize& screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, QObject *parent = 0);
    explicit Unit(const QSize& screenSize, const QSize &designedForSize, const qreal ratioMin, const qreal ratioMax, const bool roundUp, QObject *parent = 0);

    Q_INVOKABLE qreal pt(int pixel);
    Q_INVOKABLE int px(qreal point);
    Q_INVOKABLE int scale(qreal point, qreal ratio);
    Q_INVOKABLE qreal ratio();
    Q_INVOKABLE QString size();
    Q_INVOKABLE void roundUp(bool v);

protected slots:
    void computeRatio();

signals:
    void ratioChanged();

   private:
    bool mRoudUp;
    QSize mCurrentSize;
    QSize mIntendedSize;
    qreal mRatio;
    qreal mRatioMin;
    qreal mRatioMax;

    void init(const QSize& screenSize = QSize(1,1), const QSize &designedForSize = QSize(1,1), const qreal ratioMin = 0.0f, const qreal ratioMax = 99.0f, const bool roundUp = false);

};

#endif // UNIT_H
