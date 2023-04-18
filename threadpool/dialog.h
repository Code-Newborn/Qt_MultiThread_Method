#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <memory>
#include <QWidget>
#include <QThread>
#include <QList>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "JobManager.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    // 接收结果的槽函数
    void processJobResults(QList<JobResult> jobResults);
    // 开始计算的槽函数
    void start_calculate_job();
signals:
    void requestCalculate(int start_value, int end_value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;

private:
    // 任务管理器
    JobManager mJobManager;
    // 任务管理的线程
    QThread mManagerThread;
};
#endif // DIALOG_H
