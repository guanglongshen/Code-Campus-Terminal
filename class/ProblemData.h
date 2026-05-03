#ifndef PROBLEMDATA_H
#define PROBLEMDATA_H

#include <QJsonDocument>
#include <QString>
#include <QMetaType>

struct PROBLEM_DESCRIBE {
    QString title, content, inputF, outputF, samples, hint;
    int samplesCount;
};

Q_DECLARE_METATYPE(PROBLEM_DESCRIBE)

#endif // PROBLEMDATA_H
