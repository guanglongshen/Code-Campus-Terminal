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
        groupbox->setStyleSheet(
            "QGroupBox {"
            "   border: 1px solid #A0A0A0;"     // 明显的灰色边框
            "   border-radius: 0px;"            // 直角边框
            "   margin-top: 1ex;"               // 为标题留出顶部空间
            "   font-weight: bold;"             // 标题加粗
            "}"
            "QGroupBox::title {"
            "   subcontrol-origin: margin;"
            "   subcontrol-position: top left;" // 标题靠左上
            "   left: 10px;"                    // 距离左边框 10px
            "   color: #2C3E50;"                // 深色标题（深蓝灰色，更有质感）
            "   padding: 0 5px;"                // 标题文字两侧的留白
            "}"
        );
        QHBoxLayout *hlayout = new QHBoxLayout(this);
        hlayout->addWidget(groupbox);

        QVBoxLayout *layout = new QVBoxLayout(groupbox);
        layout->setContentsMargins(0, 15, 0, 5);
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
