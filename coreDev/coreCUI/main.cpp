#include "mainwindow.h"
#include <QApplication>
#include <QFile>

#include "cnrobo.h"
#include "appconf.h"
#include "robotconf.h"

#include <QDebug>

#define ARG_SERVER_ADDRESS  1

void loadStyle()
{
    QApplication* pApp  = (QApplication*)QApplication::instance();

    QString dirApp = pApp->applicationDirPath();

#ifdef OS_IS_ANDROID
    QFile file(":/style/styles/androidstyle.css");
#else
    //QFile file(":/style/styles/defstyle.css");
    QFile file(dirApp.append("/defstyle.css"));
#endif

    if(file.open(QFile::ReadOnly))
    {
        QString str = file.readAll();
        file.close();
        pApp->setStyleSheet(str);
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList argList = a.arguments();

    /* arg data */
    bool serverAddressOK = false;
    QString serverAddress;

    int curArg = -1;
    for(int i = 0; i < argList.size(); i++)
    {
        QString str = argList[i];

        if(curArg < 0)  /* check option command */
        {

            if(str.compare("-server", Qt::CaseInsensitive) == 0)
            {
                curArg = ARG_SERVER_ADDRESS;
            }
        }
        else
        {
            if(curArg == ARG_SERVER_ADDRESS)
            {
                serverAddress = str;
                serverAddressOK = true;
            }
            curArg = -1;
        }
    }

    /* controller */
    CNRobo* pCon = CNRobo::getInstance();

    pCon->setRtTaskFlag(false);
    pCon->setCommandCycleTime(20);

    if(serverAddressOK)
    {
        pCon->setServerAddress(serverAddress);
    }

    int ret = pCon->startService();

    /* set styles */
    loadStyle();

    /* ui load */
    MainWindow w;
    w.show();

    QStringList conflist;
    QStringList rconflist;

    pCon->getRobotConf(rconflist);
    pCon->getAppConf(conflist);

    AppConf::init();
    RobotConf::init();

    AppConf::setCurAppConf(conflist);
    RobotConf::setCurRobotConf(rconflist);

    AppConf::getCurAppConf(conflist);
    RobotConf::getCurRobotConf(rconflist);

    return a.exec();
}
