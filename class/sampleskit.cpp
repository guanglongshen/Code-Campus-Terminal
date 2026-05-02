#include "sampleskit.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QScroller>
#include <QScrollArea>
#include <QScrollBar>

SamplesKit::SamplesKit(const QString &block_name, QWidget *parent)
    : QWidget{parent} {

    QGroupBox *groupbox = new QGroupBox(block_name);
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(groupbox);

    QVBoxLayout *layout = new QVBoxLayout(groupbox);
    layout->setContentsMargins(0, 15, 0, 5);
    layout->setAlignment(Qt::AlignTop);

    SmoothScrollArea *scrollArea = new SmoothScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *container = new QWidget;
    scrollArea->setWidget(container);

    splitter = new QSplitter(Qt::Vertical);
    splitter->setChildrenCollapsible(false);
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->addWidget(splitter);

    QHBoxLayout *addHbox = new QHBoxLayout;
    addHbox->setAlignment(Qt::AlignRight);
    addSamplesButton = new QPushButton(tr("添加样例组（注意：样例输入与输出均无内容时，这组样例将不会存入！）"));

    connect(addSamplesButton, &QPushButton::clicked, [this](){
        this->setUpdatesEnabled(false);

        QString ids = tr("样例组");
        ids = ids + QString("#%1").arg(splitter->count() + 1);
        Samples *newSample = new Samples(ids);
        splitter->addWidget(newSample);

        // 链接删除信号
        connect(newSample, &Samples::requestDelete, this, &SamplesKit::handleDelete);
        sampleCount = splitter->count();

        this->setUpdatesEnabled(true);
    });
    addHbox->addWidget(addSamplesButton);

    layout->addWidget(scrollArea);
    layout->addLayout(addHbox);
}

void SamplesKit::updateOrders() {
    splitter->setUpdatesEnabled(false);

    for (int i = 0; i < splitter->count(); i++) {
        // 类型转换
        Samples *modify = qobject_cast<Samples*>(splitter->widget(i));

        if (modify) {
            QString ids = tr("样例组");
            modify->setId(ids + QString(" #%1").arg(i + 1));
        }
    }
    this->sampleCount = splitter->count();

    splitter->setUpdatesEnabled(true);
}

void SamplesKit::handleDelete(Samples *target) {
    if (!target) return ;

    // 销毁
    target->deleteLater();

    // deleteLater 需要再下一轮事件循环执行，因此需要显示的脱离
    target->setParent(nullptr);

    // 重新编号
    updateOrders();
}
