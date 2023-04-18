#ifndef _JOB_MANAGER_H_
#define _JOB_MANAGER_H_

#include <QObject>
#include <QSize>
#include <QPointF>
#include <QElapsedTimer>
#include <QList>
#include "JobResult.h"

class Job;
class JobManager : public QObject
{
    Q_OBJECT
public:
    explicit JobManager(QObject *parent = 0);

signals:
    // 任务完成的信号
    void primeFindFinished(QList<JobResult> jobResults);

    // 终止所有子任务
    void abortAllJobs();

public slots:
    // 分配给任务管理器的任务
    void calculate_range(int start_value, int end_value);
    // 子任务结果处理的槽函数
    void process(JobResult jobResult);

private:
    // 创建新的任务
    Job *createJob(int start_value, int end_value);
    // 清空正在运行的任务
    void clearJobs();

private:
    int mJobSize;
    int mReceivedJobResults;
    QList<JobResult> mJobResults;
    QElapsedTimer mTimer;
};
#endif