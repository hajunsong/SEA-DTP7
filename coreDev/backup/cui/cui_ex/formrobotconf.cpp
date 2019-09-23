#include "formrobotconf.h"
#include "ui_formrobotconf.h"
#include "cuiapi.h"
#include <QStringList>


FormRobotConf::FormRobotConf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRobotConf)
{
    ui->setupUi(this);
}

FormRobotConf::~FormRobotConf()
{
    delete ui;
}


void FormRobotConf::on_btnGetRobotConf_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    QStringList datas;

    pCon->getRobotConf(datas);

    for(int i = 0; i < datas.count(); i++)
    {
        ui->txtRobotConf->append(datas[i]);
    }

}

void FormRobotConf::on_btnSetRobotConf_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    QTextDocument* txtDoc = ui->txtRobotConf->document();

    QString str = txtDoc->toPlainText();

    QStringList datas = str.split("\n", QString::SkipEmptyParts);

    pCon->setRobotConf(datas);

}
