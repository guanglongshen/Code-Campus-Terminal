#ifndef SAMPLESKIT_H
#define SAMPLESKIT_H

#include <QWidget>
#include <QPlainTextEdit>

class SamplesKit : public QWidget {
    Q_OBJECT
public:
    explicit SamplesKit(QWidget *parent = nullptr);

signals:

private:
    QPlainTextEdit *Input;
    QPlainTextEdit *Output;
};

#endif // SAMPLESKIT_H
