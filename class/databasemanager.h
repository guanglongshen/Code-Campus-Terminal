#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "databaseworker.h"
#include "addproblem.h"

#include <QObject>
#include <QThread>

class DatabaseManager : public QObject {
    Q_OBJECT
public:
    static DatabaseManager* instance();
    ~DatabaseManager();
private:
    DatabaseManager();
    QThread *managerThread;
    DatabaseWorker *worker;

signals:
    // 数据库已准备
    void databaseReady(const QString &msg);
    // 操作反馈结果
    void response(const QString &msg);

    // 请求存储题目
    void requestAddProblem(const PROBLEM_DESCRIBE &data);
};

#endif // DATABASEMANAGER_H
