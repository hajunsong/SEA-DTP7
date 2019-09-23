#include "formmainwindow.h"
#include "ui_formmainwindow.h"
#include <QTimer>
#include "cuiapi.h"
#include "cuiecat.h"
#include "QTextCursor"
#include <QSize>
#include <QRect>
#include <QTimer>
#include <QUrl>

extern "C" void* createTestWidget()
{
    FormMainWindow* pW = new FormMainWindow();

    return (void*)pW;
}


FormMainWindow::FormMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMainWindow)
{
    ui->setupUi(this);

    m_menuBtns.append(ui->btnPage1);
    m_menuBtns.append(ui->btnPage2);
    m_menuBtns.append(ui->btnPage4);
    m_menuBtns.append(ui->btnPage5);
    m_menuBtns.append(ui->btnPage6);
    m_menuBtns.append(ui->btnPage7);

    for(int i = 0; i < m_menuBtns.size(); i++)
    {
        m_menuBtns[i]->setCheckable(true);
        connect(m_menuBtns[i], SIGNAL(clicked()), this, SLOT(onClickMenuButton()));
    }

    QTextDocument* pdoc = ui->txtOutPut->document();

    pdoc->addResource(QTextDocument::ImageResource, QUrl("warning.png"), QImage(":/icon/resource/warning_16.png"));
    pdoc->addResource(QTextDocument::ImageResource, QUrl("info.png"), QImage(":/icon/resource/info_16.png"));
    pdoc->addResource(QTextDocument::ImageResource, QUrl("error.png"), QImage(":/icon/resource/error_16.png"));

}

FormMainWindow::~FormMainWindow()
{
    delete ui;
}


void FormMainWindow::showEvent(QShowEvent *)
{
    m_timer = new QTimer(this);

    m_timer->setInterval(500);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    m_timer->start();

    CUIApp* pCon = CUIApp::getInstance();

    pCon->filterSystemKey(true);

}

void FormMainWindow::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormMainWindow::onTimer()
{
    printOutputMessage();
}

void FormMainWindow::printOutputMessage()
{
    CUIApp* pCon = CUIApp::getInstance();

    QStringList strList;
    QVector<CNR_TP_MSG_STATUS> msgStatus;
    pCon->getTPWrite(strList, msgStatus);

    QTextCursor txtCursor = ui->txtOutPut->textCursor();
    QTextDocument* pdoc = ui->txtOutPut->document();

    for(int i = 0; i < msgStatus.count(); i++)
    {
        if(msgStatus[i] == CNR_TP_MSG_CLEAR)
            pdoc->setPlainText("");
    }

    for(int i = 0; i < strList.length(); i++)
    {
        QRegExp rx("(\\,|\\:)");

        switch(msgStatus[i])
        {
        case CNR_TP_MSG_ERROR:
            txtCursor.insertImage("error.png");
            break;
        case CNR_TP_MSG_WARNING:
            txtCursor.insertImage("warning.png");
            break;
        case CNR_TP_MSG_INFO:
            txtCursor.insertImage("info.png");
            break;
        }

        txtCursor.insertText(strList[i]);
        txtCursor.insertText("\n");
        ui->txtOutPut->ensureCursorVisible();

        // driver error message
        if(strList[i].section(rx,3,3).compare(QString(" driver error"), Qt::CaseInsensitive) == 0)
        {
            printDriverErrorMsg();
        }
    }
}

void FormMainWindow::printDriverErrorMsg()
{
    CUIApp* pCon = CUIApp::getInstance();
    CUIEcat* pCat = CUIEcat::getInstance();

    int nAxis = pCon->getAxisCount();

    QString errLog;

    errLog.push_back("DErr ");

    for(int i = 0; i < nAxis; i++)
    {
        int slvState;
        pCat->getSlaveStatus(i, slvState);

        if(slvState & 0x08)
        {
            int newest;
            pCat->readSDO(i, 0x10f3, 02, 8, (unsigned long*)&newest);

            if(newest >= 19) newest = 19;

            char errorCode[200];
            memset(errorCode,0,sizeof(errorCode));

            pCat->readSDO(i, 0x10f3, newest, -1, (unsigned long*)errorCode);

            int mainCode = errorCode[7];
            int subCode = errorCode[6];

            QString tmpStr;
            tmpStr.sprintf("- %d:%d.%d",i+1,mainCode,subCode);
            errLog.push_back(tmpStr);
        }
    }

    if(errLog.size() > 0)
    {
        pCon->setUserLog(-9900,errLog);
        pCon->enquePrintListItem(0,errLog);
    }
}


void FormMainWindow::resizeWindow()
{
}

void FormMainWindow::resizeEvent(QResizeEvent *)
{

#if 0
        ui->frameMainMenu->setMinimumWidth(200);
        ui->btnPage1->setMinimumHeight(150);
        ui->btnPage2->setMinimumHeight(150);
        ui->btnPage4->setMinimumHeight(150);
        ui->btnPage5->setMinimumHeight(150);
        ui->btnPage6->setMinimumHeight(150);
        ui->btnPage7->setMinimumHeight(150);


#endif

    ui->frameMainMenu->setMinimumWidth(100);

    ui->btnPage1->setMinimumHeight(51);
    ui->btnPage2->setMinimumHeight(51);
    ui->btnPage4->setMinimumHeight(51);
    ui->btnPage5->setMinimumHeight(51);
    ui->btnPage6->setMinimumHeight(51);
    ui->btnPage6->setMinimumHeight(51);


    ui->frameMainMenu->updateGeometry();
//    ui->centralWidget->updateGeometry();
}


void FormMainWindow::onClickMenuButton()
{
    QPushButton* pbtn = (QPushButton*)sender();

    int prevIndex = ui->stackedWidget->currentIndex();


    for(int i = 0; i < m_menuBtns.size(); i++)
    {
        if(pbtn == m_menuBtns[i])
        {
            if(prevIndex != i)
            {

                ui->stackedWidget->setCurrentIndex(i);

                m_menuBtns[i]->setChecked(true);
                if(prevIndex >= 0 && prevIndex < m_menuBtns.size())
                {
                    m_menuBtns[prevIndex]->setChecked(false);
                }

                break;
            }
        }
    }

}
