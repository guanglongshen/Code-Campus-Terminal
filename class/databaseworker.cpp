#include "databaseworker.h"

#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QThread>

DatabaseWorker::DatabaseWorker(QObject *parent)
    : QObject{parent} {}

void DatabaseWorker::onInitDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "database_worker");

    QString dbDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dbDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString dbPath = dir.filePath("problemset.db");
    db.setDatabaseName(dbPath);

    if (db.open()) {
        QString threadAddress = QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
        emit dbInitialized(tr("数据库初始化成功！线程: %1").arg(threadAddress));
    } else {
        QString error = "数据库初始化失败！" + db.lastError().text();
        emit dbInitialized(tr("%1").arg(error));
    }
}
