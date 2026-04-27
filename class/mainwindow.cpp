#include "mainwindow.h"
#include "previewkit.h"
#include <QMenu>
#include <QVBoxLayout>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->setWindowTitle(tr("编程竞赛 [教师端]"));

    // 初始化数据库
    connect(DatabaseManager::instance(), &DatabaseManager::databaseReady, this, [this](const QString &msg){
        this->statusBar()->showMessage(msg, 3000);
    });

    // 初始化菜单栏
    initMenuBar();

    // TEST
    QWidget *container = new QWidget(this);
    QHBoxLayout *vlayout = new QHBoxLayout(container);
    PreviewKit *testing = new PreviewKit("题目描述", "请输入题目描述", this);
    vlayout->addWidget(testing);
    this->setCentralWidget(container);
}

MainWindow::~MainWindow() = default;

void MainWindow::initMenuBar() {
    mBar = this->menuBar();

    QMenu *mainMenu = mBar->addMenu(tr("平台(&P)"));
    QAction *help = mainMenu->addAction(tr("帮助"));
    mainMenu->addSeparator();
    QAction *exitAct = mainMenu->addAction(tr("退出"));
    connect(exitAct, &QAction::triggered, this, &QMainWindow::close);

    QMenu *problemsetMenu = mBar->addMenu(tr("题库(&P)"));
    QAction *checkLibrary = problemsetMenu->addAction(tr("查看题库"));
    problemsetMenu->addSeparator();
    QAction *addProblem = problemsetMenu->addAction(tr("添加题目"));
    QAction *delteProblem = problemsetMenu->addAction(tr("删除题目"));
    QAction *modifyProblem = problemsetMenu->addAction(tr("修改题目"));
}
