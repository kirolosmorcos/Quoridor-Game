#ifndef PAWNITEM_H
#define PAWNITEM_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QPoint>

class PawnItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit PawnItem(QColor color);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *,
               QWidget *) override;

    void animateMove(const QPointF &targetPos);

    // QPoint boardPos() const { return m_boardPos; }
    // void setBoardPos(int r, int c) { m_boardPos = QPoint(r, c); }


    QColor m_color;
    // QPoint m_boardPos;


};

#endif
