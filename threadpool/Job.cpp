// Job.cpp
#include "Job.h"
Job::Job(QObject *parent) : QObject(parent),
                            mAbort(false),
                            m_start_value(0),
                            m_end_value(0)
{
}
void Job::run()
{
    Q_ASSERT(m_end_value >= m_end_value);
    JobResult jobResult(m_start_value, m_end_value);

    for (int index = m_start_value; index <= m_end_value; ++index)
    {
        if (mAbort.loadRelaxed())
        {
            return;
        }
        if (is_prime(index))
        {
            jobResult.values.append(index);
        }
    }
    QThread::msleep(800);
    emit jobCompleted(jobResult);
}
void Job::set_start_value(const int start_value)
{
    m_start_value = start_value;
}
void Job::set_end_value(const int end_value)
{
    m_end_value = end_value;
}
void Job::abort()
{
    mAbort.storeRelaxed(true);
}
int Job::is_prime(int num)
{
    if (num == 1)
        return 0;
    if (num == 2)
        return 1;
    if (num % 2 == 0)
        return 0;
    for (int index = 3; index <= sqrt(num); index += 2)
    {
        if (num % index == 0)
            return 0;
    }
    return 1;
}
