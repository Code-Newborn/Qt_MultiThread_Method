#include "dialog.h"

#include <QApplication>

#include "JobResult.h"
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<JobResult>("JobResult");
    qRegisterMetaType<QList<JobResult>>("QList<JobResult>");

    Dialog w;
    w.show();
    return a.exec();
}
