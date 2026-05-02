#include "smoothscrollarea.h"

void SmoothScrollArea::wheelEvent(QWheelEvent *event) {
    // 如果按住了 Ctrl 键（通常用于缩放），不处理滚动
    if (event->modifiers() & Qt::ControlModifier) {
        QScrollArea::wheelEvent(event);
        return;
    }

    // 获取滚轮滚动的角度增量
    int wheelDelta = event->angleDelta().y();
    if (wheelDelta != 0) {
        // 确定当前的动画目标值（如果动画正在运行，则从预计的终点继续累加，防止连续滚动时卡顿）
        int currentTarget =
            m_vScrollAnimation->state() == QAbstractAnimation::Running
                ? m_vScrollAnimation->endValue().toInt()
                : verticalScrollBar()->value();

        // 计算滚动距离（Qt默认每滚一格 angleDelta().y() 是 120）
        // 这里将每次滚动的距离设置为滚动条的单步长 * 3，你也可以直接写死像素值比如
        int numDegrees = wheelDelta / 8;
        int numSteps = numDegrees / 10; // 滚轮的格数
        int stepPixels = verticalScrollBar()->singleStep() * 3 * numSteps;

        int newTarget = currentTarget - stepPixels;

        // 限制目标值在合理范围内，防止越界
        newTarget = qBound(verticalScrollBar()->minimum(), newTarget,
                           verticalScrollBar()->maximum());

        // 停止当前动画并启动新动画
        m_vScrollAnimation->stop();
        m_vScrollAnimation->setStartValue(verticalScrollBar()->value());
        m_vScrollAnimation->setEndValue(newTarget);
        m_vScrollAnimation->start();
    } else {
        // 处理横向滚动等其他情况
        QScrollArea::wheelEvent(event);
    }
}
SmoothScrollArea::SmoothScrollArea(QWidget *parent) : QScrollArea(parent) {
    setWidgetResizable(true);
    setFrameShape(QFrame::NoFrame);

    // // 1. 保留你原来的：左键拖拽动力学滚动
    // QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);
    // QScroller *scroller = QScroller::scroller(viewport());
    // QScrollerProperties props = scroller->scrollerProperties();
    // props.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor, 0.6);
    // props.setScrollMetric(QScrollerProperties::MinimumVelocity, 0.0);
    // props.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.5);
    // props.setScrollMetric(QScrollerProperties::AcceleratingFlickMaximumTime, 0.4);
    // scroller->setScrollerProperties(props);

    // 2. 新增：为垂直滚动条创建平滑动画对象
    m_vScrollAnimation =
        new QPropertyAnimation(verticalScrollBar(), "value", this);
    m_vScrollAnimation->setEasingCurve(
        QEasingCurve::OutCubic);          // 使用缓出曲线，体验最丝滑
    m_vScrollAnimation->setDuration(400); // 动画持续时间（毫秒），可根据喜好微调
}
