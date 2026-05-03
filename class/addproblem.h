#ifndef ADDPROBLEM_H
#define ADDPROBLEM_H

#include "smoothscrollarea.h"
#include "ProblemData.h"
#include "previewkit.h"
#include "sampleskit.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonDocument>

class AddProblem : public QDialog {
    Q_OBJECT
signals:
    // 题目保存发送的信号
    void problemSubmitted(const PROBLEM_DESCRIBE &problem);
public:
    explicit AddProblem(QWidget *parent = nullptr);

private:
    TitleKit *problem_name;
    PreviewKit *problem_describe;
    PreviewKit *input_format;
    PreviewKit *output_format;
    SamplesKit *samples;
    PreviewKit *hint;
    QPushButton *save;
    QPushButton *cancel;
    SmoothScrollArea *vScrollArea;
};

#endif // ADDPROBLEM_H
