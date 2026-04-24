#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "databaseworker.h"

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
    void databaseReady(const QString &msg);
};

#endif // DATABASEMANAGER_H
