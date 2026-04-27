#ifndef ADDPROBLEM_H
#define ADDPROBLEM_H

#include "previewkit.h"
#include <QDialog>
#include <QLineEdit>


class AddProblem : public QDialog {
    Q_OBJECT
public:
    explicit AddProblem(QWidget *parent = nullptr);

private:
    TitleKit *problem_name;
    PreviewKit *problem_describe;
    PreviewKit *input_format;
    PreviewKit *output_format;

    PreviewKit *hint;
};

#endif // ADDPROBLEM_H
