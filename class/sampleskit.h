#ifndef SAMPLESKIT_H
#define SAMPLESKIT_H

#include "smoothscrollarea.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>

class Samples : public QWidget {
    Q_OBJECT
signals:
    void requestDelete(Samples *ptr);
public:
    explicit Samples(const QString &ID, QWidget *parent = nullptr) {
        id = new QLabel(ID);
        input = new QPlainTextEdit;
        output = new QPlainTextEdit;

        input->setPlaceholderText(tr("样例输入"));
        output->setPlaceholderText(tr("样例输出"));

        QVBoxLayout *mainLayout = new QVBoxLayout;
        this->setLayout(mainLayout);

        QHBoxLayout *groups = new QHBoxLayout;
        groups->setAlignment(Qt::AlignLeft);
        groups->addWidget(id);
        deleteButton = new QPushButton("x");

        connect(deleteButton, &QPushButton::clicked, [this](){
            emit requestDelete(this);
        });
        groups->addWidget(deleteButton);

        QSplitter *edit = new QSplitter(Qt::Horizontal);
        edit->addWidget(input);
        edit->addWidget(output);

        mainLayout->addLayout(groups);
        mainLayout->addWidget(edit);
    }

    void setId(const QString &text) {
        id->setText(text);
    }

private:
    QLabel *id;
    QPlainTextEdit *input;
    QPlainTextEdit *output;
    QPushButton *deleteButton;
};

class SamplesKit : public QWidget {
    Q_OBJECT
public:
    explicit SamplesKit(const QString &block_name, QWidget *parent = nullptr);

signals:

private:
    QPushButton *addSamplesButton;
    QSplitter *splitter;    // 管理多个 Samples
    int sampleCount = 0;    // 样例 ID

    void updateOrders();
public slots:
    void handleDelete(Samples *target);
};

#endif // SAMPLESKIT_H
