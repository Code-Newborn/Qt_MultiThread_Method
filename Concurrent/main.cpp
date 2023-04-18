#include <QCoreApplication>

#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>
#include <QImage>
#include <QElapsedTimer>

#include <opencv2/opencv.hpp>

// Define a struct to hold the image data and index
struct ImageData
{
    QImage image;
    int index;
    cv::Mat opencv_image;
};

QMutex imagelock;

cv::Mat QImage2Mat(QImage image)
{
    cv::Mat mat = cv::Mat::zeros(image.height(), image.width(), image.format()); // 初始化Mat
    qDebug() << "format" << image.format();

    switch (image.format()) // 判断image的类型
    {
    case QImage::QImage::Format_Grayscale8: // 灰度图
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void *)image.constBits(), image.bytesPerLine());
        qDebug() << "gray" << mat.depth();
        break;
    case QImage::Format_RGB888: // 3通道彩色
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void *)image.constBits(), image.bytesPerLine());
        qDebug() << "3 channel" << mat.depth();
        break;
    case QImage::Format_ARGB32: // 4通道彩色
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void *)image.constBits(), image.bytesPerLine());
        qDebug() << "4 channel" << mat.depth();
        break;
    case QImage::Format_RGB32: //
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void *)image.constBits(), image.bytesPerLine());
        qDebug() << "Format_RGB32" << mat.depth();
        break;
    default:
        qDebug() << "default" << mat.depth();
        return mat;
    }
    return mat;
}

ImageData fun(QPair<cv::Mat, int> data)
{
    qDebug() << "线程ID" << QThread::currentThreadId() << "In fun Image index" << data.second;

    QElapsedTimer timer0; // 定义对象
    timer0.start();       // 开始计时
    putText(data.first, std::to_string(data.second), cv::Point(100, 100), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 4, 8);
    cv::Mat opencv_image1;
    //     cv::cvtColor(data.first, opencv_image1, cv::COLOR_RGBA2GRAY); // 转灰度

    // Process the image...
    // ...
    Canny(data.first, opencv_image1, 200, 220);

    QThread::msleep(0); // 线程延迟1ms
    ImageData imageData;
    // imageData.image = image;
    imageData.index = data.second;
    imageData.opencv_image = opencv_image1;

    return imageData;
}

int refTest(ImageData &a, ImageData &b)
{
    int m = a.index;
    int n = b.index;
    return m + n;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //    cv::Mat im = cv::imread("image1.png",cv::IMREAD_COLOR);
    //    qDebug()<<im.depth();
    //    cv::imshow("original", im);
    //    cv::waitKey(0);

    //    // 单张QImage加载耗时
    //    QElapsedTimer timer0; // 定义对象
    //    timer0.start();       // 开始计时
    //    QImage qimage1("image1.png");
    //    qDebug() << "Load a Qimage took" << timer0.elapsed() << "milliseconds"; // 显示结果

    qDebug() << "本机的线程数" << QThread::idealThreadCount();

    // Define the list of image file paths
    QStringList imagePaths = {
        "image1.png",
        "image2.png",
        "image3.png",
        "image4.png",
        "image5.png",
        "image6.png",
        "image7.png",
        "image8.png",
        "image9.png",
        "image10.png",
        "image11.png",
        "image12.png",
        "image13.png",
        "image14.png",
        "image15.png",
        "image16.png",
        "image17.png",
        "image18.png",
        "image19.png",
        "image20.png",
        "image21.png",
        "image22.png",
        "image23.png",
        "image24.png",
        "image25.png",
        "image26.png",
        "image27.png",
        "image28.png",
        "image29.png",
        "image30.png",
        "image31.png",
        "image32.png",
        "image33.png",
        "image34.png",
        "image35.png",
        "image36.png",
        "image37.png",
        "image38.png",
        "image39.png",
        "image40.png",
        "image41.png",
        "image42.png",
        "image43.png",
        "image44.png",
        "image45.png",
        "image46.png",
        "image47.png",
        "image48.png",
        "image49.png",
        "image50.png"};

    QList<QPair<cv::Mat, int>> list_opencvimage;

    for (size_t i = 0; i < 5; i++)
    {
        cv::Mat cvimage = cv::imread(imagePaths[i].toStdString());
        list_opencvimage.append(QPair<cv::Mat, int>(cvimage, i));
    }

    QElapsedTimer timer0; // 定义对象
    timer0.start();       // 开始计时
    cv::Mat opencv_image1;
    Canny(list_opencvimage[0].first, opencv_image1, 200, 220);

    qDebug() << "Single Canny took" << timer0.elapsed() << "milliseconds"; // 显示结果

    //    qDebug()<<list_opencvimage[1].first.depth();
    //    cv::imshow("original", list_opencvimage[1].first);
    //    cv::waitKey(0);

    // Define a vector to hold the processed image data
    QVector<ImageData> imageDataVector;

    QElapsedTimer timer; // 定义对象
    timer.start();       // 开始计时

    // Process the images concurrently using QtConcurrent::mapped
    QFuture<ImageData> future = QtConcurrent::mapped(list_opencvimage, fun);

    // Wait for the future to finish and store the results in the imageDataVector
    future.waitForFinished();

    for (const ImageData &imageData : future.results())
    {
        imageDataVector.append(imageData);
    }
    qDebug() << "OpencvImage Operation took" << timer.elapsed() << "milliseconds"; // 显示结果

    // Sort the imageDataVector by index
    std::sort(imageDataVector.begin(), imageDataVector.end(), [](const ImageData a, const ImageData b)
              { return a.index < b.index; });

    // qDebug() << "OpencvImage Operation took" << timer.elapsed() << "milliseconds"; // 显示结果

    // Output the sorted image data
    for (const ImageData &imageData : imageDataVector)
    {
        qDebug() << "Image" << imageData.index << "width:" << imageData.opencv_image.cols << "height:" << imageData.opencv_image.rows;
    }

    cv::namedWindow("mat");
    cv::Mat toshow;
    cv::resize(imageDataVector[0].opencv_image, toshow, cv::Size(imageDataVector[0].opencv_image.cols / 2, imageDataVector[0].opencv_image.rows / 2), 0.5, 0.5);
    cv::moveWindow("mat", 100, 100);
    cv::imshow("mat", toshow);

    cv::waitKey();

    return a.exec();
}
