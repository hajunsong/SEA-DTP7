#include "formtestsave.h"
#include "ui_formtestsave.h"
#include "cuiapi.h"
#include "formtest.h"
#include "cerror.h"

FormTestSave::FormTestSave(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestSave)
{
    ui->setupUi(this);
}

FormTestSave::~FormTestSave()
{
    delete ui;
}

void FormTestSave::on_btnSaveProgram_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    QString progName = ui->txtSaveProgram->text();
    pCon->saveProgram(progName);
}

void FormTestSave::on_btnSaveProgramAll_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    pCon->saveProgramAll();
}

void FormTestSave::on_btnSaveVariable_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    pCon->saveVariable();
}
