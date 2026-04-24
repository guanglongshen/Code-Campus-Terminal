#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasemanager.h"

#include <QMainWindow>
#include <QMenuBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QMenuBar *mBar;
    void initMenuBar();

    DatabaseManager *manager;
};
#endif // MAINWINDOW_H
