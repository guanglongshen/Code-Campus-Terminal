#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include "ProblemData.h"

#include <QObject>

class DatabaseWorker : public QObject {
    Q_OBJECT
public:
    explicit DatabaseWorker(QObject *parent = nullptr);

signals:
    void dbInitialized(const QString &msg);

    // 数据库操作
    void operateInformation(const QString &msg);

public slots:
    void onInitDatabase();
    void onAddProblem(const PROBLEM_DESCRIBE &data);
};

#endif // DATABASEWORKER_H
