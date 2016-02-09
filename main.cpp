#include <QCoreApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "hello world";

    //std::cout<<"Hello World!\n";

    return a.exec();
}
