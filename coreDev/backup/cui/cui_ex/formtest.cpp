#include "formtest.h"
#include "ui_formtest.h"
#include "cuiapi.h"
#include "cnhelper.h"
#include <QPlainTextEdit>
#include <QTextDocument>
#include <QMessageBox>
#include <QTimer>
#include "cerror.h"
#include <QDateTime>
#include "dlgnumber.h"
#include "cuiecat.h"


FormTest* FormTest::m_pInstance;
QStringList FormTest::s_list;

FormTest::FormTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTest)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));

}

FormTest* FormTest::getInstance()
{
    if(m_pInstance == NULL)
        m_pInstance = new FormTest();

    return m_pInstance;
}

FormTest::~FormTest()
{
    delete ui;
}

void FormTest::showEvent(QShowEvent *)
{
    CUIApp* pCon = CUIApp::getInstance();

    m_axisCount = pCon->getAxisCount();

    m_timer->start(100);
}

void FormTest::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormTest::appendTxtOut(QStringList list)
{
    s_list.append(list);
}

void FormTest::regenMessage()
{
    if(s_list.count() > 0)
    {
        for(int i = 0; i < s_list.count(); i++)
            ui->txtOutput->append(s_list[i]);

        s_list.clear();
    }
}

void FormTest::on_btnClean_clicked()
{
    ui->txtOutput->clear();
}

void FormTest::onTimer()
{
    CUIApp* pCon = CUIApp::getInstance();

    bool error_status = pCon->isError();

    if(error_status && m_error)
    {
        int errorCode, axis, subCode;
        pCon->getLastErrorInfo(errorCode, axis, subCode);

        QString str = QString("errorCdoe =%1, axis =%2 subCode =%3").
                arg(QString::number(errorCode)).
                arg(QString::number(axis)).
                arg(QString::number(subCode));


        if(errorCode < 10000)
        {
            ui->txtOutput->append(str);
        }
        m_error = false;
    }
    else if(!error_status)
    {
        m_error = true;
    }

    regenMessage();
}

void FormTest::on_btnGetLog_clicked()
{
    CUIApp* probo = CUIApp::getInstance();

    int retcode = 0;
    QStringList loglist;

    retcode = probo->getLogList(loglist);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    for(int i = 0; i < loglist.size(); i++)
        ui->txtOutput->append(loglist[i]);
}

void FormTest::on_btnMoveToPos_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    QString varName = ui->txtMoveToPos->text();
    float stableTime = ui->txtStableTime->text().toFloat();
    int retcode = pCon->moveToPosition2(varName,stableTime);

    ui->txtOutput->append(QString::number(retcode));
}

void FormTest::on_btnGetDateTime_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    QString strTime;
    pCon->getDateTime(strTime); //get - first format is Qt::ISODate

    QDateTime now = QDateTime::fromString(strTime, Qt::ISODate);
    ui->txtDateTime->setText(now.toString(Qt::ISODate)); //this format can change.
}

void FormTest::on_btnSetDateTime_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    QString strTime;
    strTime = ui->txtDateTime_2->text(); //getText Qt::ISODate

    QDateTime now = QDateTime::fromString(strTime, Qt::ISODate); //this format can change.
    pCon->setDateTime(now.toString(Qt::ISODate)); //set - last format is Qt::ISODate

}

void FormTest::on_btnSetLog_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    int code = ui->txtLogCode->text().toInt();
    QString msg = ui->txtLogMsg->text();
    pCon->setUserLog(code, msg);
}


void FormTest::setBase()
{
    CUIApp* pCon = CUIApp::getInstance();
    QString str;
    QString trans;
    trans.append("base1");
    str.sprintf("Base %s", trans.toStdString().c_str());

    char strbuf[32];
    memset(strbuf, 0, sizeof(strbuf));
    strcpy(strbuf, str.toStdString().c_str());

    pCon->executeCommand(strbuf);
}

void FormTest::on_btn_GetCurProgramStack_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    int task = 0;
    QStringList strList;
    pCon->getCurProgramStack(task, strList);
    for(int i = 0; i < strList.count(); i++)
        ui->txtOutput->append(strList[i]);
}

void FormTest::on_btnGetSlaveCount_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    int count;
    pCon->getSlaveCount(count);
    ui->txtOutput->append(QString::number(count));
}

void FormTest::on_btnGetSlaveType_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    QVector<CNR_SLAVE_TYPE> type;
    pCon->getSlaveType(type);
    int count = type.count();

    for(int i = 0; i < count; i++)
    {
        ui->txtOutput->append(QString::number(type[i]));
    }
}

void FormTest::on_btnSetEMS_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    if(pCon->isError())
    {
        pCon->setEMGOn(true);
        ui->btnSetEMS->setText("Set_EMS_ON");
    }
    else
    {
        pCon->setEMGOn(false);
        ui->btnSetEMS->setText("Set_EMS_OFF");
    }
}

void FormTest::on_btnGetSlaveModel_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    QStringList slvList;
    pCon->getSlaveModel(slvList);
    int count = slvList.count();

    for(int i = 0; i < count; i++)
    {
        ui->txtOutput->append(slvList[i]);
    }
}

void FormTest::on_btnGetAutoRunSubPrg_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    bool enable;
    pCon->getAutoRunSubProgram(enable);

    ui->txtGetAutoRunValue->setText(QString::number(enable));
}

void FormTest::on_btnSetAutoRunSubPrg_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    int value = ui->txtSetAutoRunValue->text().toInt();
    bool enable = value == 1 ? true : false;

    pCon->setAutoRunSubProgram(enable);
}

void FormTest::on_btnRebootSystem_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    pCon->rebootSystem();
}

void FormTest::on_btnCalcInverse_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    float* oldang = pCon->getCurJoint();
    float* trans = pCon->getCurTrans();
    cn_trans trIn;
    trIn.setEuler(trans);
    cn_conf confIn;
    confIn.init();

    float jointOut[32] = {0,};

    pCon->calcInverse(trIn, oldang, jointOut, confIn);

    int nAxis = pCon->getAxisCount();

    QStringList strList;

    for(int i = 0; i < nAxis; i++)
        strList.append(QString::number(jointOut[i]));

    QString str = strList.join(",");

    ui->txtOutput->append(str);
}

void FormTest::on_btnSetAutoRunSubPrg_2_clicked()
{

    CUIEcat* pCat = CUIEcat::getInstance();

    unsigned int value;
    pCat->getNetdevRxCrcErrors(value);

    ui->txtOutput->append(QString::number(value));
}


void FormTest::on_btnEcatStats_clicked()
{

    CUIEcat* pCat = CUIEcat::getInstance();

    QStringList strList;

    unsigned short value;
    unsigned int uivalue;
    int ivalue;
    __uint64_t ui64value;

    pCat->getDecErrorState(uivalue);           //Dec Error State
    strList.append(QString("Dec Error State = %1").arg(uivalue));

    pCat->getRtCycletimeAvg(uivalue);          //Dec RT Cycletime Avg
    strList.append(QString("Dec RT Cycletime Avg = %1").arg(uivalue));

    pCat->getRtCycletimeMin(uivalue);          //Dec RT Cycletime Min
    strList.append(QString("Dec RT Cycletime Min = %1").arg(uivalue));

    pCat->getRtCycletimeMax(uivalue);          //Dec RT Cycletime Max
    strList.append(QString("Dec RT Cycletime Max = %1").arg(uivalue));

    pCat->getRtTaskRuntimeAvg(uivalue);        //Dec RT Task Runtime Avg
    strList.append(QString("Dec RT Task Runtime Avg = %1").arg(uivalue));

    pCat->getRtRaskRuntimeMin(uivalue);        //Dec RT Task Runtime Min
    strList.append(QString("Dec RT Task Runtime Min = %1").arg(uivalue));

    pCat->getRtTaskRuntimeMax(uivalue);        //Dec RT Task Runtime Max
    strList.append(QString("Dec RT Task Runtime Max = %1").arg(uivalue));

    pCat->getCurWorkingCount(value);           //Current working cnt
    strList.append(QString("Current working cnt = %1").arg(value));

    pCat->getOnlineSlaveNum(value);            //Online slave num
    strList.append(QString("Online slave num = %1").arg(value));

    pCat->getRtTaskState(value);               //RT task state
    strList.append(QString("RT task state = %1").arg(value));

    pCat->getRtTaskCount(uivalue);             //RT task cnt
    strList.append(QString("RT task cnt = %1").arg(uivalue));

    pCat->getWCChangeCount(value);             //Working cnt change cnt
    strList.append(QString("Working cnt change cnt = %1").arg(value));

    pCat->getOnlineSlaveNumErrorCount(value);  //Online slave err
    strList.append(QString("Online slave err = %1").arg(value));

    pCat->getRdyEventErrorCount(value);        //Ready ev err
    strList.append(QString("Ready ev err = %1").arg(value));

    pCat->getAppEventErrorCount(value);        //APP ev err
    strList.append(QString("APP ev err = %1").arg(value));

    pCat->getEndEventErrorCount(value);        //END ev err
    strList.append(QString("END ev err = %1").arg(value));

    pCat->getWaitPeriodErrorCount(value);      //Wait period err
    strList.append(QString("Wait period err = %1").arg(value));

    pCat->getDeepSleepErrorCount(value);       //Deep sleep err
    strList.append(QString("Deep sleep err = %1").arg(value));

    pCat->getWakeupLargeErrorCount(value);     //Wakeup large err
    strList.append(QString("Wakeup large err = %1").arg(value));

    pCat->getNetdevRxLengthErrors(uivalue);    //Netdev Rx length err
    strList.append(QString("Netdev Rx length err = %1").arg(uivalue));

    pCat->getNetdevRxCrcErrors(uivalue);       //Netdev Rx crc err
    strList.append(QString("Netdev Rx crc err = %1").arg(uivalue));

    pCat->getNetdevRxFifoErrors(uivalue);      //Netdev Rx fifo err
    strList.append(QString("Netdev Rx fifo err = %1").arg(uivalue));

    pCat->getEcdevTxCount(ui64value);          //Ecdev Tx cnt
    strList.append(QString("Ecdev Tx cnt = %1").arg(ui64value));

    pCat->getEcdevRxCount(ui64value);          //Ecdev Rx cnt
    strList.append(QString("Ecdev Rx cnt = %1").arg(ui64value));

    pCat->getEcdevLostPacket(uivalue);         //Lost Frames
    strList.append(QString("Lost Frames = %1").arg(uivalue));

    pCat->getEcdevTxBytes(ui64value);          //Ecdev Tx Byte
    strList.append(QString("Ecdev Tx Byte = %1").arg(ui64value));

    pCat->getEcdevRxBytes(ui64value);          //Ecdev Rx Byte
    strList.append(QString("Ecdev Rx Byte = %1").arg(ui64value));

    pCat->getCurDCDiffTime(ivalue);            //Cur DC Diff Time
    strList.append(QString("Cur DC Diff Time = %1").arg(ivalue));

    pCat->getNetdevRxCrcErrors(uivalue);     //Packet Crc Error
    strList.append(QString("Packet Crc Error = %1").arg(uivalue));

    unsigned int uiArr[16];
    memset(uiArr, 0, sizeof(uiArr));
    pCat->getDCTimeDiagTable(uiArr, 16);           //DC Diagnosis Table
    unsigned int* totalcnt = &uiArr[1];

    strList.append(QString("DC Total Count = %1").arg(uiArr[0]));

    for(int i = 0; i < 10; i++)
    {
        strList.append(QString("DC Count = %1(%2%)").arg(totalcnt[i]).arg(((float)totalcnt[i]/(float)uiArr[0])*100));
    }

    int count = strList.count();
    for(int i = 0; i < count; i++)
        ui->txtOutput->append(strList[i]);


}

void FormTest::on_btnVersion_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    QStringList strList;

    QString verStr;
    pCon->getVersion(CUIApp::VT_CORECON, verStr);
    strList.append(verStr);

    pCon->getVersion(CUIApp::VT_MASTER, verStr);
    strList.append(verStr);

    pCon->getVersion(CUIApp::VT_KERNEL, verStr);
    strList.append(verStr);

    int count = strList.count();
    for(int i = 0; i < count; i++)
        ui->txtOutput->append(strList[i]);
}

void FormTest::on_btnMultiData_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    QStringList strList;

    int size;
    pCon->MA_getArmSize(size);

    strList.append(QString("%1 = %2").arg("size").arg(size));

    int master;
    pCon->MA_getMasterArm(master);
    strList.append(QString("%1 = %2").arg("master").arg(master));

    int order[10];
    pCon->MA_getArmOrder(order);


    for(int i = 0; i < size; i++)
    {
        strList.append(QString("%1 = %2").arg("order").arg(order[i]));

        float value;
        pCon->MA_getHint(i, value);

        strList.append(QString("%1 = %2").arg("hint").arg(value));
    }

    int count = strList.count();
    for(int i = 0; i < count; i++)
        ui->txtOutput->append(strList[i]);
}
