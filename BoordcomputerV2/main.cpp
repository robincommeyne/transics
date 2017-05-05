#include <QCoreApplication>

#include "dispatcher.h"
#include "controller.h"
#include "watchdog.h"
#include "manager.h"

using namespace cangateway;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    qDebug() << "main is started" << QThread::currentThread();

    Manager initializer(&a);
    QTimer::singleShot(0, Qt::VeryCoarseTimer, &initializer, &Manager::Init);
    //!< Start Threads

    return a.exec();
}
