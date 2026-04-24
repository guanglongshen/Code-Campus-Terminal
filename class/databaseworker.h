#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include <QObject>

class DatabaseWorker : public QObject {
    Q_OBJECT
public:
    explicit DatabaseWorker(QObject *parent = nullptr);

signals:
    void dbInitialized(const QString &msg);

public slots:
    void onInitDatabase();
};

#endif // DATABASEWORKER_H
