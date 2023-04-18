#include <QCoreApplication>
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>

int is_prime(int num)
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    long lsize = 160000;
    long count = 0;

    QElapsedTimer timer;
    timer.start();

    // for (long i = 0; i < lsize; i++)
    // {
    //     if (is_prime(i))
    //     {
    //         count++;
    //     }
    // }

    QThread::msleep(800);

    qDebug() << "find 0 to " << lsize << "prime number" << count << "took" << timer.elapsed() << "milseconds";

    return a.exec();
}
