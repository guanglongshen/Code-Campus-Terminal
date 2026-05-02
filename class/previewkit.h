#ifndef PREVIEWKIT_H
#define PREVIEWKIT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPlainTextEdit>
#include <QTimer>
#include <QTextBrowser>
#include <QNetworkAccessManager>
#include <QLineEdit>
#include <QGroupBox>

class TitleKit : public QWidget {
    Q_OBJECT
public:
    explicit TitleKit(const QString &block_name, const QString &placeholder = "", QWidget *parent = nullptr) {
        QGroupBox *groupbox = new QGroupBox(block_name);

        QHBoxLayout *hlayout = new QHBoxLayout(this);
        hlayout->addWidget(groupbox);

        QVBoxLayout *layout = new QVBoxLayout(groupbox);
        layout->setContentsMargins(15, 15, 15, 15);
        layout->setAlignment(Qt::AlignTop);

        problem_names = new QLineEdit;
        problem_names->setPlaceholderText(placeholder);
        layout->addWidget(problem_names);
    }
    QString getText() const {
        return problem_names->text();
    }
    void setText(const QString &t);

signals:

private:
    QLineEdit *problem_names;
};

class PreviewKit : public QWidget {
    Q_OBJECT
public:
    explicit PreviewKit(const QString &block_name, const QString &placeholder = "", QWidget *parent = nullptr);
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
