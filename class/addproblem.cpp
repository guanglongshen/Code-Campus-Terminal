#include "addproblem.h"
#include "previewkit.h"
#include <QGroupBox>
#include <QScrollArea>
#include <QSplitter>

AddProblem::AddProblem(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle(tr("编辑题目"));
    // --- 集中管理样式表 ---
    // 这里统一设置了字体、GroupBox 样式、以及所有按钮的交互效果
    this->setStyleSheet(
        // 1. 全局字体设置 (英文 Consolas, 中文 微软雅黑/黑体)
        "QWidget { font-family: 'Consolas', 'Microsoft YaHei', 'SimHei'; font-size: 14px; }"

        // 2. GroupBox 样式
        "QGroupBox {"
        "   border: 1px solid #A0A0A0; border-radius: 0px; margin-top: 1ex; font-weight: bold;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin; subcontrol-position: top left; left: 10px; color: #2C3E50; padding: 0 5px;"
        "}"

        // 3. 统一按钮样式 (文本高亮蓝效果)
        // 包含添加按钮和删除按钮的共有属性
        "QPushButton {"
        "   border: none; background: transparent; color: black; padding: 5px;"
        "}"
        "QPushButton:hover { color: #0078D7; }"
        "QPushButton:pressed { color: #005A9E; }"

        // 4. 针对性修饰
        "QPushButton#deleteBtn { font-weight: bold; font-size: 16px; }"
        "QPlainTextEdit { border: 1px solid #CCC; background: white; }"
        "QLineEdit { border: 1px solid #CCC; background: white; }"
    );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    SmoothScrollArea *vScrollArea = new SmoothScrollArea(this);
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
    samples = new SamplesKit(tr("样例"));
    hint = new PreviewKit(tr("说明"), tr("请在此填写说明"));
    scrollContent->addWidget(problem_describe);
    scrollContent->addWidget(input_format);
    scrollContent->addWidget(output_format);
    scrollContent->addWidget(samples);
    scrollContent->addWidget(hint);

    scrollContent->setStretchFactor(0, 0); // 题目名称固定大小
    scrollContent->setStretchFactor(1, 1);
    scrollContent->setStretchFactor(2, 1);
    scrollContent->setStretchFactor(3, 1);
    scrollContent->setStretchFactor(4, 1);

    vScrollArea->setWidget(container);
    mainLayout->addWidget(vScrollArea);
}
