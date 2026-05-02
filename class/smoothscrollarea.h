#ifndef SMOOTHSCROLLAREA_H
#define SMOOTHSCROLLAREA_H

#include <QScrollArea>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QWheelEvent>
#include <QScroller>
#include <QScrollerProperties>

class SmoothScrollArea : public QScrollArea {
    Q_OBJECT
public:
    explicit SmoothScrollArea(QWidget *parent = nullptr);

protected:
    // 重写滚轮事件
    void wheelEvent(QWheelEvent *event) override;

private:
    QPropertyAnimation *m_vScrollAnimation;
};

#endif // SMOOTHSCROLLAREA_H
