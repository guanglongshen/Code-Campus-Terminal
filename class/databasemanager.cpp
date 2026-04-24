#include "databasemanager.h"

// 全局静态 “操作员”
DatabaseManager *DatabaseManager::instance() {
    static DatabaseManager inst;
    return &inst;
}

DatabaseManager::~DatabaseManager() {
    if (managerThread->isRunning()) {
        managerThread->quit();
        managerThread->wait();  // 阻塞等待，直到线程真正退出
    }
}

DatabaseManager::DatabaseManager() {
    // 创建线程，并将数据库“操作员”移动到此多线程
    managerThread = new QThread(this);
    worker = new DatabaseWorker();
    worker->moveToThread(managerThread);

    // 信号相关联
    connect(worker, &DatabaseWorker::dbInitialized, this, &DatabaseManager::databaseReady);
    connect(managerThread, &QThread::started, worker, &DatabaseWorker::onInitDatabase);
    connect(managerThread, &QThread::finished, worker, &QObject::deleteLater);

    managerThread->start();
}
