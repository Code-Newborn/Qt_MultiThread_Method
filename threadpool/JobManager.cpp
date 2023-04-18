#include "JobManager.h"
#include <QDebug>
#include <QThreadPool>
#include "Job.h"

// 任务分组的步长值
#define CALCULATE_PER_PAGE 1

JobManager::JobManager(QObject *parent)
    : QObject(parent),
      mJobResults(),
      mTimer(),
      mReceivedJobResults(0),
      mJobSize(0)
{
}

void JobManager::calculate_range(int start_value, int end_value)
{
    Q_ASSERT(end_value >= start_value);
    mTimer.start();
    clearJobs();

    // 按照步长拆分到几个组里面进行计算
    for (int index = start_value; index <= end_value; index += CALCULATE_PER_PAGE)
    {
        int current_page_end_value = std::min(index + CALCULATE_PER_PAGE, end_value);
        QThreadPool::globalInstance()->start(createJob(index, current_page_end_value));
        ++mJobSize;
    }
}

void JobManager::process(JobResult jobResult)
{
    // 对收集到的任务计算结果进行处理
    mReceivedJobResults++;
    mJobResults.append(jobResult);

    if (mReceivedJobResults == mJobSize)
    {
        emit primeFindFinished(mJobResults);
        mJobResults.clear();
    }

    if (mReceivedJobResults == mJobSize)
    {
        qDebug() << "Total cost" << mTimer.elapsed() << " ms";
    }
}

Job *JobManager::createJob(int start_value, int end_value)
{
    Job *job = new Job();
    job->set_start_value(start_value);
    job->set_end_value(end_value);
    connect(this, &JobManager::abortAllJobs, job, &Job::abort);
    connect(job, &Job::jobCompleted, this, &JobManager::process);
    return job;
}

void JobManager::clearJobs()
{
    mReceivedJobResults = 0;
    mJobSize = 0;
    emit abortAllJobs();
    QThreadPool::globalInstance()->clear();
}