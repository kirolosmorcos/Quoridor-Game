#include "WallItem.h"
#include <QBrush>
#include <QPen>
#include "../util/Constants.h"

WallItem::WallItem(ori o)
{
    setBrush(Qt::black);
    setZValue(4);
    setOrientation(o);
}

void WallItem::setOrientation(ori o){
    orientation = o;

    if (o == ori::Horizontal) {
        setRect(0, 0, WALL_LEN, WALL_THICK);
        setTransformOriginPoint(WALL_LEN / 2, WALL_THICK / 2);
    }
    else {
        setRect(0, 0, WALL_THICK, WALL_LEN);
        setTransformOriginPoint(WALL_THICK / 2, WALL_LEN / 2);
    }


}

    // 🔹 Drop animation
    // setScale(0);

    // auto *a = new QPropertyAnimation(this, "scale");
    // a->setDuration(180);
    // a->setStartValue(0);
    // a->setEndValue(1);
    // a->start(QAbstractAnimation::DeleteWhenStopped);



