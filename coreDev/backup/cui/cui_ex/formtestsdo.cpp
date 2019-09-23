#include "formtestsdo.h"
#include "ui_formtestsdo.h"
#include "cuiapi.h"
#include "formtest.h"
#include "cerror.h"



FormTestSDO::FormTestSDO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestSDO)
{
    ui->setupUi(this);
}

FormTestSDO::~FormTestSDO()
{
    delete ui;
}


void FormTestSDO::on_btnGetSDO_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    int id = ui->txtAxisNumber->text().toInt();
    QTextDocument* txtdoc = ui->txtSDO->document();
    QString strText = txtdoc->toPlainText();
    QStringList strList = strText.split("\n", QString::SkipEmptyParts);
    int lenth = strList.length();

    int args[1024];

    memset(args, 0, sizeof(args));
    QString str;

    for(int i = 0; i < lenth; i++)
    {
        str = strList[i];
        args[i] = str.section(',',0,0).toInt(NULL, 16);
    }

    unsigned long datas[64];
    memset(datas, 0, sizeof(datas));

    pCon->getSDO(id, args, lenth, (unsigned long*)&datas);

//  example code)
//    void* datas;
//    unsigned long* idatas = ((unsigned long*)&datas);       //unsigned long get
//    int* idatas = ((int*)&datas);                           //int read

    for(int i = 0; i <lenth; i++)
    {
        str = QString::number(datas[i]);
        appendTxtOut(str);
    }
}

void FormTestSDO::on_btnSetSDO_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    int id = ui->txtAxisNumber->text().toInt();
    QTextDocument* txtdoc = ui->txtSDO->document();
    QString strText = txtdoc->toPlainText();
    QStringList strList = strText.split("\n", QString::SkipEmptyParts);
    int lenth = strList.length();

    int args[1024];
    unsigned long values[1024];
    memset(args, 0, sizeof(args));
    memset(values, 0, sizeof(values));
    QString str;

    for(int i = 0; i < lenth; i++)
    {
        str = strList[i];
        args[i] = str.section(',',0,0).toInt(NULL, 16);
        values[i] = str.section(',',1,1).toULong(NULL, 10);     //unsigned long write
//        values[i] = str.section(',',1,1).toInt(NULL, 10);     //int write
    }

    int retcode = pCon->setSDO(id, args, lenth, values);

    appendTxtOut(QString::number(retcode));
}

void FormTestSDO::on_btnGetSDOList_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
    QTextDocument* txtdoc = ui->txtSDO->document();
    QString strText = txtdoc->toPlainText();
    QStringList strList = strText.split("\n", QString::SkipEmptyParts);
    int argLenth = strList.length();

    int args[1024];
    memset(args, 0, sizeof(args));
    QString str;

    for(int i = 0; i < argLenth; i++)
    {
        str = strList[i];
        args[i] = str.section(',',0,0).toInt(NULL, 16);
    }

    unsigned long datas[64];
    memset(datas, 0, sizeof(datas));

    int dataLenth;

    pCon->getSDOList(args, argLenth, datas, dataLenth);

    for(int i = 0; i <dataLenth; i++)
    {
        str = QString::number(datas[i]);
        appendTxtOut(str);
    }
}

void FormTestSDO::appendTxtOut(const QString& str)
{
    FormTest* pTest = FormTest::getInstance();
    QStringList list;

    list.append(str);
    pTest->appendTxtOut(list);
}
