#include "formuserparams.h"
#include "ui_formuserparams.h"
#include "cnrobo.h"

#include <QStringList>

FormUserParams::FormUserParams(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUserParams)
{
    ui->setupUi(this);
}

FormUserParams::~FormUserParams()
{
    delete ui;
}

void FormUserParams::on_btnGetUserParams_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QStringList params;

    pCon->getUserParams(params);

    for(int i = 0; i < params.count(); i++)
    {
        ui->txtUserPrams->append(params[i]);
    }
}

void FormUserParams::on_btnSetUserParams_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QTextDocument* txtDoc = ui->txtUserPrams->document();

    QString str = txtDoc->toPlainText();

    QStringList params = str.split("\n", QString::SkipEmptyParts);

    pCon->setUserParams(params);
}
