// Job.h
#ifndef JOB_H
#define JOB_H

// 任务的主要目标是寻找某个范围内的质数
#include <QObject>
#include <QRunnable>
#include <QAtomicInteger>
#include "JobResult.h"
#include <QThread>

class Job : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Job(QObject *parent = 0);
    void run() override;
    // 设置搜索的起始值
    void set_start_value(const int start_value);

    // 设置搜索的终止值
    void set_end_value(const int end_value);
signals:
    // 计算结果的信号
    void jobCompleted(JobResult jobResult);

public slots:
    // 用来结束线程任务
    void abort();

private:
    // 判断是否为质数
    int is_prime(int num);

private:
    // 为了防止锁影响任务效率,通过引入原子类型进行线程控制
    QAtomicInteger<bool> mAbort;
    int m_start_value;
    int m_end_value;
};

#endif // JOB_H
