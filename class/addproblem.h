#ifndef ADDPROBLEM_H
#define ADDPROBLEM_H

#include "previewkit.h"
#include <QDialog>


class AddProblem : public QDialog {
    Q_OBJECT
public:
    AddProblem(QWidget *parent);

private:
    QTextLine *problem_name;
    PreviewKit *problem_describe;
    PreviewKit *input_format;
    PreviewKit *output_format;

    PreviewKit *hint;
};

#endif // ADDPROBLEM_H
