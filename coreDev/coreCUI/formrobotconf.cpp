#include "formrobotconf.h"
#include "ui_formrobotconf.h"
#include "cnrobo.h"
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
    CNRobo* pCon = CNRobo::getInstance();

    QStringList dataList;

    pCon->getRobotConf(dataList);

    for(int i = 0; i < dataList.count(); i++)
    {
        ui->txtRobotConf->append(dataList[i]);
    }

}

void FormRobotConf::on_btnSetRobotConf_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QTextDocument* txtDoc = ui->txtRobotConf->document();

    QString str = txtDoc->toPlainText();

    QStringList dataList = str.split("\n", QString::SkipEmptyParts);

    pCon->setRobotConf(dataList);

}
