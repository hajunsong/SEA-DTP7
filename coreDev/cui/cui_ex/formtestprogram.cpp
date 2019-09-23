#include "formtestprogram.h"
#include "ui_formtestprogram.h"
#include "cuiapi.h"
#include "formtest.h"
#include "cerror.h"


FormTestProgram::FormTestProgram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestProgram)
{
    ui->setupUi(this);
    }

FormTestProgram::~FormTestProgram()
{
    delete ui;
}

void FormTestProgram::on_btnListPrograms_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    QStringList txtOut;

    int retcode = 0;
    QStringList prgList;

    retcode = probo->getPrograms(prgList);

    if(retcode != 0)
    {
        txtOut.append(CUI_ERR_NOT_REPORTED);
        return;
    }

    for(int i = 0; i < prgList.size(); i++)
        txtOut.append(prgList[i]);

    appendTxtOut(txtOut);
}

void FormTestProgram::on_btnSetSteps_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    QStringList txtOut;

    int retcode = 0;
    QTextDocument* txtDoc = ui->txtPgm->document();
    QString prgName;
    QStringList steps;

    prgName = ui->txtPgmName->text();
    QString strText = txtDoc->toPlainText();

    if(prgName.isEmpty() | strText.isEmpty())
    {
        txtOut.append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    steps = strText.split("\n", QString::SkipEmptyParts);

    if(prgName.isNull() | steps.isEmpty())
        return;

    retcode = probo->setProgramSteps(prgName, steps);

    if(retcode != 0)
    {
        txtOut.append(CUI_ERR_NOT_REPORTED);
        return;
    }
    else
        txtOut.append("setSteps Ok");

    appendTxtOut(txtOut);
}

void FormTestProgram::on_btnLoadProgram_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    QStringList txtOut;

    int retcode = 0;
    QString prgName;
    QStringList steps;
    QString strTrim;

    prgName = ui->txtPgmName->text();

    if(prgName.isEmpty())
    {
        txtOut.append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    retcode = probo->getProgramSteps(prgName, steps);

    if(retcode != 0)
    {
        txtOut.append(CUI_ERR_NOT_REPORTED);
        return;
    }

    ui->txtPgm->clear();

    for(int i = 0; i < steps.count(); i++)
    {
        strTrim = steps[i];
        ui->txtPgm->appendPlainText(strTrim.trimmed());
    }

    appendTxtOut(txtOut);
}

void FormTestProgram::on_btnDeleteProgram_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    QStringList txtOut;

    int retcode = 0;
    QString prgName;

    prgName = ui->txtPgmName->text();

    if(prgName.isEmpty())
    {
        txtOut.append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    retcode = probo->deleteProgram(prgName);

    if(retcode != 0)
    {
        txtOut.append(CUI_ERR_NOT_REPORTED);
        return;
    }
    else
        txtOut.append("DeletePtorgam Ok");

    appendTxtOut(txtOut);
}


void FormTestProgram::appendTxtOut(QStringList list)
{
    FormTest* pTest = FormTest::getInstance();
    pTest->appendTxtOut(list);
}

