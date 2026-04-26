#include "databaseworker.h"

#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
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
        // 创建一些初始表
        QSqlQuery query(db);
        QString createTableSql = R"(
            CREATE TABLE IF NOT EXISTS problems (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                time_limit INTEGER DEFAULT 1000,
                memory_limit INTEGER DEFAULT 512,
                content TEXT,
                input_format TEXT,
                output_format TEXT,
                hint TEXT,
                samples TEXT
            )
        )";

        QString threadAddress = QString("0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
        if (!query.exec(createTableSql)) {
            emit dbInitialized(tr("题库表创建失败: %1").arg(query.lastError().text()));
            return ;
        } else {
            emit dbInitialized(tr("数据库初始化成功！线程: %1 | 题库表已创建!").arg(threadAddress));
        }
    } else {
        QString error = "数据库初始化失败！" + db.lastError().text();
        emit dbInitialized(tr("%1").arg(error));
        return ;
    }
}
