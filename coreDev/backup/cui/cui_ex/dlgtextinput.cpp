#include "dlgtextinput.h"
#include "ui_dlgtextinput.h"

DlgTextInput::DlgTextInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgTextInput)
{
    ui->setupUi(this);
}

DlgTextInput::~DlgTextInput()
{
    delete ui;
}


void DlgTextInput::setText()
{
    ui->textInput->setText(str);
}

void DlgTextInput::on_btnOK_clicked()
{
    str = ui->textInput->text();

    QDialog::accept();

}

void DlgTextInput::on_btnCancel_clicked()
{
    QDialog::reject();

}

