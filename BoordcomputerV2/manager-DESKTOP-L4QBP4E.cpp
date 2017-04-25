#include <QCoreApplication>
#include "dispatcher.h"
#include "controller.h"
#include "watchdog.h"
#include "eventinstigator.h"

using namespace cangateway;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    qDebug() << "Manager is running" << QThread::currentThread();
    //!< Debug

    EventInstigator instigator(&a);
    QTimer::singleShot(0, Qt::VeryCoarseTimer, &instigator, &EventInstigator::instigate);
    //!< Start Threads

    return a.exec();
}
