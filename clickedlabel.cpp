#include "clickedlabel.h"

ClickedLabel::ClickedLabel()
{

}

void ClickedLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "Clicked";
    emit onClicked();

}
