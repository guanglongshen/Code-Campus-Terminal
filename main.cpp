#include "class/ProblemData.h"
#include "class/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QSettings>
#include <QTranslator>
#include <QtSql>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qRegisterMetaType<PROBLEM_DESCRIBE>("PROBLEM_DESCRIBE");

    // 设置本地基础信息以及配置信息
    QCoreApplication::setOrganizationName("Code Campus Terminal");
    QCoreApplication::setApplicationName("CCT");
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::applicationDirPath());
    QSettings::setDefaultFormat(QSettings::IniFormat);


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "CodeCampusTerminal_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.showMaximized();
    return QCoreApplication::exec();
}
