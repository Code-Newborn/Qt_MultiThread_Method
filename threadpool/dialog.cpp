#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Dialog),
      mJobManager(),
      mManagerThread(this)
{
    ui->setupUi(this);

    // 为了防止任务管理器阻碍主线程,将其移动到子线程中
    // mJobManager不能指定父对象,否则无法移动到其它线程中
    mJobManager.moveToThread(&mManagerThread);
    connect(this, &Dialog::requestCalculate, &mJobManager, &JobManager::calculate_range);
    connect(&mJobManager, &JobManager::primeFindFinished, this, &Dialog::processJobResults);
    mManagerThread.start();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(start_calculate_job()));
}

Dialog::~Dialog()
{
    mManagerThread.quit();
    mManagerThread.wait(1000);
    if (!mManagerThread.isFinished())
    {
        mManagerThread.terminate();
    }

    delete ui;
}

void Dialog::processJobResults(QList<JobResult> jobResults)
{
    int total_find_count = 0;
    for (JobResult &jobResult : jobResults)
    {
        total_find_count += jobResult.values.size();
    }
    QMessageBox::information(this, "tips", QString("Find:%1 piece").arg(total_find_count));
}

void Dialog::start_calculate_job()
{
    int start_value = ui->lineEdit_2->text().toInt();
    int end_value = ui->lineEdit->text().toInt();
    emit requestCalculate(start_value, end_value);
}

void Dialog::on_pushButton_clicked()
{
}
