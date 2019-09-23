#include "formtestdatabase.h"
#include "ui_formtestdatabase.h"
#include <QPushButton>
#include "cnrobo.h"
#include "formtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <QTextStream>


FormTestDatabase::FormTestDatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestDatabase)
{
    ui->setupUi(this);

    m_btnList.append(ui->btnList);
    m_btnList.append(ui->btnMake);
    m_btnList.append(ui->btnLoad);
    m_btnList.append(ui->btnSet);
    m_btnList.append(ui->btnCopy);
    m_btnList.append(ui->btnMove);
    m_btnList.append(ui->btnDelete);
    m_btnList.append(ui->btnCheckExist);

    on_rbtnProg_clicked();
}

FormTestDatabase::~FormTestDatabase()
{
    delete ui;
}

void FormTestDatabase::on_rbtnProg_clicked()
{
    m_dtType = DT_PROG;
    setTxtMenu(m_dtType);
}

void FormTestDatabase::on_rbtnVar_clicked()
{
    m_dtType = DT_VAR;
    setTxtMenu(m_dtType);
}

void FormTestDatabase::on_rbtnDir_clicked()
{
    m_dtType = DT_DIR;
    setTxtMenu(m_dtType);
}

void FormTestDatabase::on_rbtnFile_clicked()
{
    m_dtType = DT_FILE;
    setTxtMenu(m_dtType);
}

void FormTestDatabase::setTxtMenu(DATABASE_TYPE type)
{
    for(int i = 0; i < m_btnList.count(); i++)
    {
        if(type == DT_PROG)
        {
            if(i == BT_MOVE || i == BT_MAKE)
                m_btnList[i]->hide();
            else
                m_btnList[i]->show();

            ui->lbl1->setText("Path");
            ui->lbl2->setText("Name");
            ui->btnCopy->setText("import");
        }
        else if(type == DT_VAR)
        {
            if(i == BT_LOAD || i == BT_SET)
                m_btnList[i]->hide();
            else
                m_btnList[i]->show();

            ui->lbl1->setText("Path1");
            ui->lbl2->setText("Path2");
        }
        else if(type == DT_FILE)
        {
            m_btnList[i]->show();

            ui->lbl1->setText("Path1");
            ui->lbl2->setText("Path2");
            ui->btnSet->setText("save");
        }
        else
            ui->btnSet->setText("set");
    }
}

void FormTestDatabase::on_btnList_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QStringList pList;

    QString path1 = ui->txtPath1->text();

    if(m_dtType == DT_DIR)
        pCon->getDatabaseDirList(path1 , pList);
    else
        pCon->getDatabaseFileList(path1 , pList);

    setTxtOut(pList);
}

void FormTestDatabase::on_btnMake_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString path1 = ui->txtPath1->text();
    QString dirPath;

    ui->txtPgm->clear();

    dirPath.append(path1);

    if(m_dtType == DT_FILE)
        pCon->makeDatabaseText(dirPath);
    else if(m_dtType == DT_DIR)
        pCon->makeDatabaseDir(dirPath);
}

void FormTestDatabase::on_btnLoad_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString path1 = ui->txtPath1->text();
    QString path2 = ui->txtPath2->text();
    QString dirPath;

    ui->txtPgm->clear();

    if(m_dtType == DT_FILE)
        dirPath.append(path1);
    else
        dirPath.sprintf("%s/%s",path1.toStdString().c_str(), path2.toStdString().c_str());

    QStringList pList;

    if(m_dtType == DT_PROG)
    {
        pCon->getProgramFile(dirPath, pList);
    }
    else if(m_dtType == DT_VAR)
    {
        QList<cn_variant> variables;
        QStringList varNames;

        pCon->getVariableFile(dirPath, varNames, variables);

        if(variables.count() <= 0)
            return;

        for(int i = 0; i < variables.count(); i++)
        {

            QStringList vList;

            cn_variant var = variables[i];

            qDebug("var.type = %d", var.type);


            switch (var.type)
            {
            case CNVAR_JOINT:
                vList.append(QString::number(1));
                vList.append(varNames[i]);

                for(int j = 0; j < var.val.joint.count; j++)
                    vList.append(QString::number(var.val.joint.joint[j]));
                break;
            case CNVAR_TRANS:
                vList.append(QString::number(2));
                vList.append(varNames[i]);

                for(int j = 0; j < 3; j++)
                    vList.append(QString::number(var.val.trans.p[j]));

                for(int j = 0; j < 3; j++)
                    vList.append(QString::number(var.val.trans.eu[j]));

                break;
            case CNVAR_FLOAT:
                vList.append(QString::number(3));
                vList.append(varNames[i]);

                vList.append(QString::number(var.val.f32));
                break;
            case CNVAR_STRING:
                vList.append(QString::number(4));
                vList.append(varNames[i]);

                vList.append(var.val.str);
                break;
            }

            QString str = varNames[i];
            qDebug("varNames = %s", str.toStdString().c_str());

            QString varStr = vList.join(",");
            pList.append(varStr.trimmed());

         }
    }
    else if(m_dtType == DT_FILE)
    {
        int nbuf = 0;
        char filePath[64];
        char buf[1048576];

        memset(filePath, 0, sizeof(filePath));
        memset(buf, 0, sizeof(buf));

        pCon->loadDatabaseFile(path1, buf, nbuf);

        if(path2.isEmpty())
            return;

        strcpy(filePath, path2.toStdString().c_str());

        FILE *fp = NULL;

        fp = fopen(filePath, "wb");

        if(fp == NULL)
            goto error_exit;

        fwrite(buf, nbuf, 1, fp);

error_exit:
        if(fp) fclose(fp);

        return;
    }

    qDebug("dirPath7 = %s", dirPath.toStdString().c_str());

    QString strTrim;
    for(int i = 0; i < pList.count(); i++)
    {
        strTrim = pList[i];
        ui->txtPgm->appendPlainText(strTrim.trimmed());
    }

    qDebug("dirPath8 = %s", dirPath.toStdString().c_str());
}

void FormTestDatabase::on_btnSet_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString path1 = ui->txtPath1->text();
    QString path2 = ui->txtPath2->text();
    QString dirPath;
    QStringList varNames;

    int nAxis = pCon->getAxisCount();

    if(m_dtType == DT_FILE)
        dirPath.append(path1);
    else
        dirPath.sprintf("%s/%s",path1.toStdString().c_str(), path2.toStdString().c_str());

    QTextDocument* txtDoc = ui->txtPgm->document();
    QStringList pList;

    QString strText = txtDoc->toPlainText();
    pList = strText.split("\n", QString::SkipEmptyParts);

    if(m_dtType == DT_PROG)
    {
        pCon->createProgramFile(dirPath, pList);
    }
    else if(m_dtType == DT_VAR)
    {
        QList<cn_variant> variables;

        for(int i = 0; i < pList.count(); i++)
        {
            cn_variant var;
            QString str = pList[i];
            int type = str.section(",",0,0, QString::SectionSkipEmpty).toInt();

            varNames.append(str.section(",",1,1, QString::SectionSkipEmpty));

            switch (type) {
            case 1:
                var.type = CNVAR_JOINT;
                var.val.joint.count = nAxis;
                for(int j = 0; j < nAxis; j++)
                    var.val.joint.joint[j] = str.section(",",j+2,j+2, QString::SectionSkipEmpty).toFloat();
                break;
            case 2:
                var.type = CNVAR_TRANS;
                for(int j = 0; j < 3; j++)
                    var.val.trans.p[j] = str.section(",",j+2,j+2, QString::SectionSkipEmpty).toFloat();

                for(int j = 0; j < 3; j++)
                    var.val.trans.eu[j] = str.section(",",j+2+3,j+2+3, QString::SectionSkipEmpty).toFloat();

                break;
            case 3:
                var.type = CNVAR_FLOAT;
                var.val.f32 = str.section(",",2,2, QString::SectionSkipEmpty).toFloat();
                break;
            case 4:
                var.type = CNVAR_STRING;
                strcpy(var.val.str, str.section(",",2,2, QString::SectionSkipEmpty).toStdString().c_str());
                break;
            }

            variables.append(var);
        }

        pCon->createVariableFile(dirPath, varNames, variables);

    }
    else if(m_dtType == DT_FILE)
    {
        int retcode = 0;
        int i = 0;
        int ibuf;
        int nbuf = 0;

        char filePath[64];
        char buf[1048576];

        memset(buf, 0, sizeof(buf));
        memset(filePath, 0, sizeof(filePath));

        strcpy(filePath, path1.toStdString().c_str());

        FILE *fp = NULL;

        fp = fopen(filePath, "rb");

        if(fp == NULL)
            goto error_exit;

        do{
            retcode = fread(&ibuf, 1, 1, fp);

            buf[i] = ibuf;

            i++;
        }while(retcode == 1);

        nbuf = i;

        if(path2.isEmpty())
            goto error_exit;

        pCon->saveDatabaseFile(path2, buf, nbuf);

error_exit:
        if(fp) fclose(fp);

    }
}

void FormTestDatabase::on_btnCopy_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString path = ui->txtPath1->text();
    QString newPath = ui->txtPath2->text();

    if(m_dtType == DT_FILE)
        pCon->copyDatabaseFile(path, newPath);
    else if(m_dtType == DT_DIR)
        pCon->copyDatabaseDir(path, newPath);
    else if(m_dtType == DT_PROG)
    {
        QString filePath;
        filePath.sprintf("%s/%s",path.toStdString().c_str(), newPath.toStdString().c_str());

        pCon->importProgram(filePath);
    }
}

void FormTestDatabase::on_btnMove_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString path = ui->txtPath1->text();
    QString newPath = ui->txtPath2->text();

    if(m_dtType == DT_FILE)
        pCon->moveDatabaseFile(path, newPath);
    else if(m_dtType == DT_DIR)
        pCon->moveDatabaseDir(path, newPath);
}

void FormTestDatabase::on_btnDelete_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString path1 = ui->txtPath1->text();
    QString path2 = ui->txtPath2->text();
    QString dirPath;

    if(m_dtType == DT_FILE || m_dtType == DT_DIR)
        dirPath.append(path1);
    else
        dirPath.sprintf("%s/%s",path1.toStdString().c_str(), path2.toStdString().c_str());

    if(m_dtType == DT_DIR)
        pCon->deleteDatabaseDir(dirPath);
    else
        pCon->deleteDatabaseFile(dirPath);
}

void FormTestDatabase::on_btnCheckExist_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString dirFilePath = ui->txtPath1->text();

    bool exist;

    pCon->checkDirFileExist(dirFilePath, exist);

    QStringList list;

    if(exist)
        list.append("exist!");
    else
        list.append("empty!");

    setTxtOut(list);
}

void FormTestDatabase::setTxtOut(QStringList list)
{
    FormTest* pTest = FormTest::getInstance();
    pTest->appendTxtOut(list);
}


