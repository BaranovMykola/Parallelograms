#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel();
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void onClicked();
};

#endif // CLICKEDLABEL_H
