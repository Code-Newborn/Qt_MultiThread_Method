// JobResult.h
// 结构体负责存储某个范围内的质数
#ifndef JOBRESULT_H
#define JOBRESULT_H
#include <QSize>
#include <QVector>
#include <QPointF>

struct JobResult
{
    JobResult() : start_value(0), stop_value(0) {}
    JobResult(int start, int end) : start_value(start), stop_value(end)
    {
    }
    // 搜索范围的起始值
    int start_value;

    // 搜索范围的终止值
    int stop_value;

    // 查找到的结果
    QVector<int> values;
};

#endif // JOBRESULT_H