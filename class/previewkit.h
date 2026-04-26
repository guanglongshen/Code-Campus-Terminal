#ifndef PREVIEWKIT_H
#define PREVIEWKIT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPlainTextEdit>
#include <QTimer>
#include <QTextBrowser>
#include <QNetworkAccessManager>

class PreviewKit : public QWidget {
    Q_OBJECT
public:
    explicit PreviewKit(const QString &placeholder = "", QWidget *parent = nullptr);
    QString getText() const;
    void setText(const QString &t);

signals:

private:
    QPlainTextEdit *contentEdit;
    QTextBrowser *previewView;
    QNetworkAccessManager *networkManager;
    QTimer *renderTimer;

    void update();
};

#endif // PREVIEWKIT_H
