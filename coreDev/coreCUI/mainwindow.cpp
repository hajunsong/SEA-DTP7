#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "devtype.h"
#include <QDesktopWidget>
#include <QSize>
#include <QRect>
#include <QTimer>
#include <QUrl>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if DEV_TYPE == DEV_DTP7
    QMainWindow::showFullScreen();
#endif

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    m_timer = new QTimer(this);

    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    m_timer->start(100);
}

void MainWindow::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void MainWindow::onTimer()
{
    printOutputMessage();
}


void MainWindow::printOutputMessage()
{
    CNRobo* pCon = CNRobo::getInstance();

    QStringList strList;
    QVector<CNR_TP_MSG_STATUS> msgStatus;
    pCon->getTPWrite(strList, msgStatus);

    QTextCursor txtCursor = ui->txtOutPut->textCursor();
    QTextDocument* pdoc = ui->txtOutPut->document();

    for(int i = 0; i <msgStatus.count(); i++)
    {
        if(msgStatus[i] == CNR_TP_MSG_CLEAR)
            pdoc->setPlainText("");
    }

    for(int i = 0; i < strList.length(); i++)
    {
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
    }
}

void MainWindow::resizeWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *)
{  

#if DEV_TYPE == DEV_ANDROID
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
    ui->centralWidget->updateGeometry();
}


void MainWindow::onClickMenuButton()
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
