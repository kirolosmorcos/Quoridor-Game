#include "PawnItem.h"

#include <iostream>
#include <QPainter>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include "../util/Constants.h"

PawnItem::PawnItem(QColor color)
    : m_color(color)
{
    setZValue(2);
}

QRectF PawnItem::boundingRect() const
{
    qreal r = PAWN_RADIUS;
    return QRectF(-r, -r, 2*r, 2*r);
}

void PawnItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *,
                     QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(m_color);
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(boundingRect());
}

void PawnItem::animateMove(const QPointF &targetPos)
{

    auto *anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(160);
    anim->setStartValue(pos());
    anim->setEndValue(targetPos);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

}
