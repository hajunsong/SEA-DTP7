#include "formio.h"
#include "ui_formio.h"

FormIO::FormIO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormIO)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    m_btns.append(ui->btnSystem);
    m_btns.append(ui->btnDO);
    m_btns.append(ui->btnDI);
    m_btns.append(ui->btnAO);
    m_btns.append(ui->btnAI);


    connect(ui->btnSystem, SIGNAL(clicked()), this, SLOT(changePage()));
    connect(ui->btnDO, SIGNAL(clicked()), this, SLOT(changePage()));
    connect(ui->btnDI, SIGNAL(clicked()), this, SLOT(changePage()));
    connect(ui->btnAO, SIGNAL(clicked()), this, SLOT(changePage()));
    connect(ui->btnAI, SIGNAL(clicked()), this, SLOT(changePage()));

}

FormIO::~FormIO()
{
    delete ui;
}

void FormIO::changePage()
{
    QPushButton* btn = (QPushButton*)sender();
    int index = m_btns.indexOf(btn);

    ui->stackedWidget->setCurrentIndex(index);


}
