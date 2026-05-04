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
#include <QIntValidator>
#include <QLabel>

class TitleKit : public QWidget {
    Q_OBJECT
public:
    explicit TitleKit(const QString &block_name, const QString &placeholder = "", QWidget *parent = nullptr) {
        QGroupBox *groupbox = new QGroupBox(block_name);

        QHBoxLayout *hlayout = new QHBoxLayout(this);
        hlayout->addWidget(groupbox);

        QHBoxLayout *layout = new QHBoxLayout(groupbox);
        layout->setContentsMargins(15, 15, 15, 15);
        layout->setAlignment(Qt::AlignTop);

        problem_names = new QLineEdit;
        problem_names->setPlaceholderText(placeholder);
        layout->addWidget(problem_names);

        const int widthForLabel = 100, widthForEdit = 50;
        QHBoxLayout *limitLayout = new QHBoxLayout;
        // limitLayout->setAlignment(Qt::AlignRight);
        QLabel *title_time = new QLabel(tr("时间限制(ms):"));
        title_time->setFixedWidth(widthForLabel);
        time_limit = new QLineEdit;
        time_limit->setObjectName("time_limit_edit");
        time_limit->setToolTip(tr("时间限制范围：50 ~ 10,000 ms"));
        time_limit->setText("1000");
        time_limit->setPlaceholderText("1000");
        time_limit->setFixedWidth(widthForEdit);
        validator_time = new QIntValidator(0, 99999, this);
        time_limit->setValidator(validator_time);
        limitLayout->addWidget(title_time);
        limitLayout->addWidget(time_limit);
        limitLayout->addSpacing(20);
        connect(time_limit, &QLineEdit::editingFinished, this, [=](){
            int val = time_limit->text().toInt();
            if (val < 50) {
                time_limit->setText("50");
            } else if (val > 10000) {
                time_limit->setText("10000");
            }
        });

        QLabel *title_space = new QLabel(tr("空间限制(MB):"));
        title_space->setFixedWidth(widthForLabel);
        space_limit = new QLineEdit;
        space_limit->setObjectName("space_limit_edit");
        space_limit->setToolTip(tr("空间限制范围：8 ~ 1024 MB"));
        space_limit->setText("512");
        space_limit->setPlaceholderText("512");
        space_limit->setFixedWidth(widthForEdit);
        validator_space = new QIntValidator(0, 9999, this);
        space_limit->setValidator(validator_space);
        connect(space_limit, &QLineEdit::editingFinished, this, [=](){
            int val = space_limit->text().toInt();
            if (val < 8) {
                space_limit->setText("8");
            } else if (val > 1024) {
                space_limit->setText("1024");
            }
        });

        limitLayout->addWidget(title_space);
        limitLayout->addWidget(space_limit);

        layout->addLayout(limitLayout);
    }
    QString getText() const {
        return problem_names->text().trimmed();
    }
    void setText(const QString &t){
        problem_names->setText(t);
    }

    int getTextPosition() {
        return problem_names->height();
    }

signals:

private:
    QLineEdit *problem_names;
    QLineEdit *time_limit, *space_limit;
    QIntValidator *validator_time, *validator_space;
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
