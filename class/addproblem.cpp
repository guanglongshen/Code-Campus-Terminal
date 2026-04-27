#include "addproblem.h"
#include "previewkit.h"
#include <QGroupBox>
#include <QScrollArea>
#include <QSplitter>

AddProblem::AddProblem(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QScrollArea *vScrollArea = new QScrollArea(this);
    vScrollArea->setWidgetResizable(true);
    vScrollArea->setFrameShape(QFrame::NoFrame);


    QWidget *container = new QWidget();
    container->setMinimumHeight(1500);
    QVBoxLayout *contentLayout = new QVBoxLayout(container);
    contentLayout->setAlignment(Qt::AlignTop);

    QSplitter *scrollContent = new QSplitter(Qt::Vertical);
    contentLayout->addWidget(scrollContent);
    // scrollContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scrollContent->setChildrenCollapsible(false);

    problem_name = new TitleKit(tr("题目名称"), tr("请在此填写题目名称"));
    scrollContent->addWidget(problem_name);

    problem_describe = new PreviewKit(tr("题目描述"), tr("请在此填写题目内容"));
    input_format = new PreviewKit(tr("输入格式"), tr("请在此填写输入格式"));
    output_format = new PreviewKit(tr("输出格式"), tr("请在此填写输出格式"));
    hint = new PreviewKit(tr("说明"), tr("请在此填写说明"));
    scrollContent->addWidget(problem_describe);
    scrollContent->addWidget(input_format);
    scrollContent->addWidget(output_format);
    scrollContent->addWidget(hint);

    scrollContent->setStretchFactor(0, 0); // 题目名称固定大小
    scrollContent->setStretchFactor(1, 1);
    scrollContent->setStretchFactor(2, 1);
    scrollContent->setStretchFactor(3, 1);
    scrollContent->setStretchFactor(4, 1);

    vScrollArea->setWidget(container);
    mainLayout->addWidget(vScrollArea);
}
