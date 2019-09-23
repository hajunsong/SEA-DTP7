#include "formtest.h"
#include "ui_formtest.h"
#include "cnrobo.h"
#include "cnhelper.h"
#include <QPlainTextEdit>
#include <QTextDocument>
#include <QMessageBox>
#include <QTimer>
#include "cerror.h"
#include <QDateTime>
#include "dlgnumber.h"

FormTest* FormTest::m_pInstance;
QStringList FormTest::s_list;

FormTest::FormTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTest)
{
    ui->setupUi(this);
    on_rbtn_VariableData_clicked();

    m_timer = new QTimer(this);
    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));

}

FormTest* FormTest::getInstance()
{
    if(m_pInstance == NULL)
        m_pInstance = new FormTest();

    return m_pInstance;
}


FormTest::~FormTest()
{
    delete ui;
}

void FormTest::appendTxtOut(QStringList lsit)
{
    s_list.append(lsit);
}

void FormTest::showEvent(QShowEvent *)
{
    CNRobo* pCon = CNRobo::getInstance();

    m_axisCount = pCon->getAxisCount();

    QString watchStr = QString::number(pCon->getWatchDogLimit());

    ui->txtWatchCurTime->setText(watchStr);

    m_timer->start(100);
}

void FormTest::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormTest::onTimer()
{
    CNRobo* pCon = CNRobo::getInstance();

    /* error */
    bool error_status = pCon->isError();

    if(error_status && m_error)
    {
        int errorCode, axis, subCode;
        pCon->getLastErrorInfo(errorCode, axis, subCode);

        QString str = QString("errorCdoe =%1, axis =%2 subCode =%3").
                arg(QString::number(errorCode)).
                arg(QString::number(axis)).
                arg(QString::number(subCode));


        if(errorCode < 10000)
        {
            ui->txtOutput->append(str);
        }
        m_error = false;
    }
    else if(!error_status)
    {
        m_error = true;
    }

    /* warning */
    bool warning_status = pCon->isWarning();

    if(warning_status && m_warning)
    {
        int warningCode;
        pCon->getWarningCode(warningCode);

        QString str = QString("warningCode = %1").arg(QString::number(warningCode));

        if(warningCode < 10000)
        {
            ui->txtOutput->append(str);
        }
        m_warning = false;
    }
    else if(!warning_status)
    {
        m_warning = true;
    }

    /* */
    if(s_list.count() > 0)
    {
        for(int i = 0; i < s_list.count(); i++)
            ui->txtOutput->append(s_list[i]);

        s_list.clear();
    }
}

void FormTest::on_btnGetLog_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

    int retcode = 0;
    QStringList loglist;

    retcode = probo->getLogList(loglist);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    for(int i = 0; i < loglist.size(); i++)
        ui->txtOutput->append(loglist[i]);
}

void FormTest::on_btnListPrograms_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

    int retcode = 0;
    QStringList prgList;

    retcode = probo->getPrograms(prgList);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    for(int i = 0; i < prgList.size(); i++)
        ui->txtOutput->append(prgList[i]);
}

void FormTest::on_btnSetSteps_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

    int retcode = 0;
    QTextDocument* txtDoc = ui->txtPgm->document();
    QString prgName;
    QStringList steps;

    prgName = ui->txtPgmName->text();
    QString strText = txtDoc->toPlainText();

    if(prgName.isEmpty() | strText.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    steps = strText.split("\n", QString::SkipEmptyParts);

    if(prgName.isNull() | steps.isEmpty())
        return;

    retcode = probo->setProgramSteps(prgName, steps);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }
    else
        ui->txtOutput->append("setSteps Ok");
}

void FormTest::on_btnLoadProgram_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

    int retcode = 0;
    QString prgName;
    QStringList steps;
    QString strTrim;

    prgName = ui->txtPgmName->text();

    if(prgName.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    retcode = probo->getProgramSteps(prgName, steps);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    ui->txtPgm->clear();

    for(int i = 0; i < steps.count(); i++)
    {
        strTrim = steps[i];
        ui->txtPgm->appendPlainText(strTrim.trimmed());
    }
}

void FormTest::on_btnDeleteProgram_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

    int retcode = 0;
    QString prgName;

    prgName = ui->txtPgmName->text();

    if(prgName.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    retcode = probo->deleteProgram(prgName);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }
    else
        ui->txtOutput->append("DeletePtorgam Ok");
}

void FormTest::on_rbtn_VariableData_clicked()
{
    CUIFCTxt cft;

    cft.name_getbtn = "getVariableData";
    cft.name_setbtn = "setVariableData";
    cft.exam_a = "get : 1. Type:1~4 (1.Joint, 2.Trans, 3.Number, 4.String),  2.Name";
    cft.exam_b = "set : 1. Type:1~4(1.Joint, 2.Trans, 3.Number, 4.String),  2.Name,  3.Value:(1,2,3,4,5,6)";
    cft.findex = 1;
    cft.hiddenCmd = 0x0f7;

    setFunctionStruct(cft);
}

void FormTest::on_rbtn_VariableList_clicked()
{
    CUIFCTxt cft;

    cft.name_getbtn = "getVariableList";
    cft.exam_a = "get : 1. Type:1~4 (1.Joint, 2.Trans, 3.Number, 4.String),  2.Name";
    cft.exam_b = "";
    cft.findex = 2;
    cft.hiddenCmd = 0x003;

    setFunctionStruct(cft);
}

void FormTest::on_rbtn_VariableCount_clicked()
{
    CUIFCTxt cft;

    cft.name_getbtn = "getVariableCount";
    cft.exam_a = "get : 1. Type:1~4 (1.Joint, 2.Trans, 3.Number, 4.String),  2.Name";
    cft.exam_b = "";
    cft.findex = 3;
    cft.hiddenCmd = 0x003;

    setFunctionStruct(cft);
}

void FormTest::on_rbtn_VariableDelete_clicked()
{
    CUIFCTxt cft;

    cft.name_setbtn = "deleteVariable";
    cft.exam_a = "delete : 1. Name";
    cft.exam_b = "";
    cft.findex = 4;
    cft.hiddenCmd = 0x070;

    setFunctionStruct(cft);
}

void FormTest::on_rbtn_VarDeleteAll_clicked()
{
    CUIFCTxt cft;

    cft.name_setbtn = "deleteVariableAll";
    cft.exam_a = "";
    cft.exam_b = "";
    cft.findex = 5;
    cft.hiddenCmd = 0x010;

    setFunctionStruct(cft);
}

void FormTest::on_rbtn_Variables_clicked()
{
    CUIFCTxt cft;

    cft.name_getbtn = "getVariables";
    cft.name_setbtn = "setVariables";
    cft.exam_a = "";
    cft.exam_b = "";
    cft.findex = 6;
    cft.hiddenCmd = 0x173;

    setFunctionStruct(cft);
}

void FormTest::on_rbtn_ApplyVarFile_clicked()
{
    CUIFCTxt cft;

    cft.name_setbtn = "applyVariablefile";
    cft.exam_a = "path : 1. Input Variable Path";
    cft.exam_b = "";
    cft.findex = 7;
    cft.hiddenCmd = 0x030;

    setFunctionStruct(cft);
}

void FormTest::on_rbtn_ExtractVarFile_clicked()
{
    CUIFCTxt cft;

    cft.name_setbtn = "extractVariablefile";
    cft.exam_a = "path : 1. Input Variable Path";
    cft.exam_b = "";
    cft.findex = 8;
    cft.hiddenCmd = 0x030;

    setFunctionStruct(cft);
}


void FormTest::setFunctionStruct(CUIFCTxt& cft)
{
    ui->btn_GetData->setText(cft.name_getbtn);
    ui->btn_SetData->setText(cft.name_setbtn);
    ui->lb_Example->setText(cft.exam_a);
    ui->lb_Example_2->setText(cft.exam_b);

    m_functionIndex = cft.findex;
    SetWidgetHidden(cft.hiddenCmd);
}

void FormTest::SetWidgetHidden(int hdnCmd)
{
    /*get*/
    if(hdnCmd & 0x001)
        ui->btn_GetData->setHidden(false);
    else
        ui->btn_GetData->setHidden(true);

    if(hdnCmd & 0x002)
        ui->txt_GetParam1->setHidden(false);
    else
        ui->txt_GetParam1->setHidden(true);

    if(hdnCmd & 0x004)
        ui->txt_GetParam2->setHidden(false);
    else
        ui->txt_GetParam2->setHidden(true);

    if(hdnCmd & 0x008)
        ui->txt_GetParam3->setHidden(false);
    else
        ui->txt_GetParam3->setHidden(true);

    /*set*/
    if(hdnCmd & 0x010)
        ui->btn_SetData->setHidden(false);
    else
        ui->btn_SetData->setHidden(true);

    if(hdnCmd & 0x020)
        ui->txt_SetParam1->setHidden(false);
    else
        ui->txt_SetParam1->setHidden(true);

    if(hdnCmd & 0x040)
        ui->txt_SetParam2->setHidden(false);
    else
        ui->txt_SetParam2->setHidden(true);

    if(hdnCmd & 0x080)
        ui->txt_SetParam3->setHidden(false);
    else
        ui->txt_SetParam3->setHidden(true);

    if(hdnCmd & 0x100)
        ui->txt_EditData->setHidden(false);
    else
        ui->txt_EditData->setHidden(true);


    ui->txt_GetParam1->clear();
    ui->txt_GetParam2->clear();
    ui->txt_GetParam3->clear();
    ui->txt_SetParam1->clear();
    ui->txt_SetParam2->clear();
    ui->txt_SetParam3->clear();
    ui->txt_EditData->clear();

}

void FormTest::on_btn_SetData_pressed()
{
    switch (m_functionIndex)
    {
    case 1:
        setVariableData();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        deleteVariable();
        break;
    case 5:
        deleteVariableAll();
        break;
    case 6:
        setVariables();
        break;
    case 7:
        applyVariableFile();
        break;
    case 8:
        extractVariableFile();
    }
}

void FormTest::on_btn_GetData_pressed()
{
    switch (m_functionIndex)
    {
    case 1:
        getVariableData();
        break;
    case 2:
        getVariableList();
        break;
    case 3:
        getVariableCount();
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        getVariables();
        break;
    }
}

void FormTest::setVariableData()
{
    CNRobo* pCon = CNRobo::getInstance();

    int retcode = 0;
    int varType = 0;
    float floatValue;
    cn_variant variValue;
    QString strType;
    QString strName;
    QString strValue;
    QStringList retList;

    strType = ui->txt_SetParam1->text();
    strName = ui->txt_SetParam2->text();
    strValue = ui->txt_SetParam3->text();
    varType = strType.toInt();

    if(strType.isEmpty() || strName.isEmpty() || strValue.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    switch (varType)
    {
    case 1:
        memset(variValue.val.joint.joint, 0 ,sizeof(variValue.val.joint.joint));

        for(int i = 0; i < m_axisCount; i++)
        {
            floatValue = strValue.section(",",i,i).toFloat();
            variValue.val.joint.joint[i] = floatValue;
        }
        break;
        ui->txtOutput->append("Vaiable empty!");
        return;

    case 2:
    {
        for(int i = 0; i < 3; i++)
        {
            floatValue = strValue.section(",",i,i).toFloat();
            variValue.val.trans.p[i] = floatValue;
        }

        for(int i = 0; i < 3; i++)
        {
            floatValue = strValue.section(",",i+3,i+3).toFloat();
            variValue.val.trans.eu[i] = floatValue;
        }

        floatValue = strValue.section(",",6,6).toFloat();
        variValue.val.trans.ext[0] = floatValue;
    }
        break;
    case 3:
            floatValue = strValue.toFloat();
            variValue.val.f32 = floatValue;
        break;
    case 4:
            strcpy(variValue.val.str, CNHelper::toMultiByteCode(strValue));
        break;
    }

    retcode = pCon->setVariableData(varType, strName, variValue, true);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    retList.append("set =" + strType + "," + strName + "," + strValue);

    for(int i = 0; i < retList.size(); i++)
    {
        ui->txtOutput->append(retList[i]);
    }
}

void FormTest::getVariableData()
{
    CNRobo* pCon = CNRobo::getInstance();

    int retcode = 0;
    int varType =0;
    cn_variant varValue;
    QString strName;
    QString strType;

    strType = ui->txt_GetParam1->text();
    strName = ui->txt_GetParam2->text();
    varType = strType.toInt();

    if(strType.isEmpty() || strName.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    retcode = pCon->getVariableData(varType,strName,&varValue);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    QString str;
    QString retStr;
    QStringList retList;

    switch(varType)
    {
    case 1: /* joint */
        {
            for(int i = 0; i < m_axisCount; i++)
            {
                retStr.append(" " + QString::number(varValue.val.joint.joint[i]));
            }
            retList.append(strName + " = " + retStr);
        }
        break;
    case 2: /* trans */
        {
            for(int i = 0; i < 3; i++)
            {
                str.sprintf("%.3f", varValue.val.trans.p[i]);
                retStr.append(" " + str);
            }
            for(int i = 0; i < 3; i++)
            {
                str.sprintf("%.3f", varValue.val.trans.eu[i]);
                retStr.append(" " + str);
            }

            str.sprintf("%.3f", varValue.val.trans.ext[0]);
            retStr.append(" " + str);

            retList.append(strName + " = " + retStr);
        }
        break;
    case 3: /* number : float */
        {
            str.sprintf("%.3f", varValue.val.f32);
            retList.append(strName + " = " + str);
        }
        break;
    case 4: /* string */
        {
            retList.append(strName + " = " + varValue.val.str);
        }
        break;
    }

    if(retList.isEmpty())
    {
        ui->txtOutput->append("Vaiable empty!");
        return;
    }

    for(int i = 0; i < retList.size(); i++)
    {
        ui->txtOutput->append(retList[i]);
    }
}

void FormTest::getVariableList()
{
    CNRobo* pCon = CNRobo::getInstance();

    int retcode = 0;
    int varType = 0;
    QVector<cn_variant> varDatas;
    QStringList vatNames;
    QString strType;
    QStringList retList;
    QString str;

    strType = ui->txt_GetParam1->text();

    if(strType.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    varType = strType.toInt();

    retcode = pCon->getVariableList(varType, vatNames, varDatas);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    switch(varType)
    {
    case 1: /* joint */
    {
        for(int i = 0; i < vatNames.size(); i++)
        {
            retList.append(vatNames[i]);

            for (int j = 0; j < m_axisCount; j++)
            {
                str.sprintf("%.3f", varDatas[i].val.joint.joint[j]);
                retList.append(str);
            }
        }
    }
    break;
    case 2: /* trans */
    {
        for(int i = 0; i < vatNames.size(); i++)
        {
            retList.append(vatNames[i]);

            for(int j = 0; j < 3; j ++)
            {
                str.sprintf("%.3f", varDatas[i].val.trans.p[j]);
                retList.append(str);
            }
            for(int j = 0; j < 3; j ++)
            {
                str.sprintf("%.3f", varDatas[i].val.trans.eu[j]);
                retList.append(str);
            }

            str.sprintf("%.3f", varDatas[i].val.trans.ext[0]);
            retList.append(str);
        }
    }
    break;
    case 3: /* number */
    {
        for(int i = 0; i < vatNames.size(); i++)
        {
            retList.append(vatNames[i]);
            str.sprintf("%.3f", varDatas[i].val.f32);
            retList.append(str);
        }
    }
    break;
    case 4: /* string */
    {
        for(int i = 0; i < vatNames.size(); i++)
        {
            retList.append(vatNames[i]);
            retList.append(varDatas[i].val.str);
        }
    }
    break;
    }

    if(retList.isEmpty())
    {
        ui->txtOutput->append("Vaiable empty!");
        return;
    }

    for(int i = 0; i < retList.size(); i++)
    {
        ui->txtOutput->append(retList[i]);
    }
}


void FormTest::getVariableCount()
{
    CNRobo* pCon = CNRobo::getInstance();

    int retcode = 0;
    int varType = 0;
    int varCount = 0;
    QString strType;

    strType = ui->txt_GetParam1->text();

    if(strType.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    varType = strType.toInt();

    QStringList retList;

    retcode = pCon->getVariableCount(varType, &varCount);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
        return;
    }

    retList.append("variableCount =" + QString::number(varCount));

    for(int i = 0; i < retList.size(); i++)
    {
        ui->txtOutput->append(retList[i]);
    }
}

void FormTest::deleteVariable()
{
    CNRobo* pCon = CNRobo::getInstance();

    int retcode = 0;
    int varType = 0;
    QString strType;
    QString varName;

    strType = ui->txt_SetParam1->text();
    varName = ui->txt_SetParam2->text();

    if(strType.isEmpty() || varName.isEmpty())
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
        return;
    }

    varType = strType.toInt();

    qDebug("varType = %d", varType);
    qDebug("varName = %s", varName.toStdString().c_str());


    retcode = pCon->deleteVariable(varType, varName);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_REPORTED);
    }
    else
        ui->txtOutput->append("delete = " + QString::number(varType) + "," + varName);
}

void FormTest::deleteVariableAll()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->deleteVariableAll();
}

void FormTest::setVariables()
{
    CNRobo* pCon = CNRobo::getInstance();
    QList<cn_variant> values;
    values.clear();

    /* set text to string */
    QString param1 = ui->txt_SetParam1->text().trimmed();
    QString param2 = ui->txt_SetParam2->text().trimmed();
    QString editData = ui->txt_EditData->toPlainText();

    /* split string , types, names, datalist */
    QStringList varType = param1.split(",",QString::SkipEmptyParts);
    QStringList varNames = param2.split(",",QString::SkipEmptyParts);
    QStringList dataList = editData.split("\n",QString::SkipEmptyParts);

    /* data count */
    int nCount = varNames.count();


    /* append type, data in values*/
    for(int i = 0; i < nCount; i++)
    {
        /* type */
        QString strType = varType[i];
        int type = strType.toInt();

        /* variable data */
        QString strTemp = dataList[i];
        QStringList vars = strTemp.split(",", QString::SkipEmptyParts);

        QString strWork;
        cn_variant var;
        memset(&var, 0, sizeof(struct cn_variant));

        switch (type) {
        case 1:
        var.type = CNVAR_JOINT;
        for(int j = 0; j < vars.count(); j++)
        {
            strWork = vars[j];
            var.val.joint.joint[j] = strWork.toFloat();
        }

        var.val.joint.count = vars.count();
            break;
        case 2:
        var.type = CNVAR_TRANS;
        for(int j = 0; j < 3; j++)
        {
            strWork = vars[j];
            var.val.trans.p[j] = strWork.toFloat();
        }
        for(int j = 0; j < 3; j++)
        {
            strWork = vars[j+3];
            var.val.trans.eu[j] = strWork.toFloat();
        }

        strWork = vars[6];
        var.val.trans.ext[0] = strWork.toFloat();

            break;
        case 3:
        var.type = CNVAR_FLOAT;
        strWork = vars[0];
        var.val.f32 = strWork.toFloat();
            break;
        case 4:
        var.type = CNVAR_STRING;
        strWork = vars[0];
        strcpy(var.val.str, strWork.toStdString().c_str());
            break;
        }

        /* append var */
        values.append(var);
    }

    /* nameCount == variableCount */
    if(varNames.count() != values.count())
        return;

    /* set */
    pCon->setVariables(varNames, values);

    if(varNames.count() != values.count())
        return;

    /* check type error type is CNVAR_NONE(-1) */
    for(int i = 0; i < values.count(); i++)
    {
        cn_variant var = values[i];

        QStringList strList;

        strList.append(varNames[i]);

        /* type, data */
        switch (var.type)
        {
        case CNVAR_JOINT:
            strList.append("(1)");
            break;
        case CNVAR_TRANS:
            strList.append("(2)");
            break;
        case CNVAR_FLOAT:
            strList.append("(3)");
            break;
        case CNVAR_STRING:
            strList.append("(4)");
            break;
        default:
            strList.append("(-1)");
            break;
        }

        QString str = strList.join(",");
        ui->txtOutput->append(str);
    }
}

void FormTest::getVariables()
{
    CNRobo* pCon = CNRobo::getInstance();

    QList<cn_variant> values;
    values.clear();

    /* set text to string */
    QString param1 = ui->txt_GetParam1->text().trimmed();

    /* split string , names */
    QStringList varNames = param1.split(",",QString::SkipEmptyParts);

    /* get */
    pCon->getVariables(varNames, values);

    /* nameCount == variableCount */
    if(varNames.count() != values.count())
        return;

    /* type */
    int type;

    /* print name, type, type */
    for(int i = 0; i < varNames.count(); i++)
    {
        cn_variant var = values[i];
        QStringList strList;

        /* name */
        strList.append(varNames[i]);

        /* type, data */
        switch (var.type)
        {
        case CNVAR_JOINT:
            strList.append("(1)");
            for(int j = 0; j < var.val.joint.count; j++)
            {
                strList.append(QString::number(var.val.joint.joint[j]));
            }
            break;
        case CNVAR_TRANS:
            strList.append("(2)");
            for(int j = 0; j < 3; j++)
                strList.append(QString::number(var.val.trans.p[j]));

            for(int j = 0; j < 3; j++)
                strList.append(QString::number(var.val.trans.eu[j]));

            strList.append(QString::number(var.val.trans.ext[0]));

            break;
        case CNVAR_FLOAT:
            strList.append("(3)");
            strList.append(QString::number(var.val.f32));
            break;
        case CNVAR_STRING:
            strList.append("(4)");
            strList.append(var.val.str);
            break;
        default:
            strList.append("(-1)");
            break;
        }

        QString str = strList.join(",");
        ui->txtOutput->append(str);
    }
}


void FormTest::applyVariableFile()
{
    CNRobo* pCon = CNRobo::getInstance();
    QString varPath = ui->txt_SetParam1->text();

    int retcode = pCon->importVariable(varPath);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
    }
    else
        ui->txtOutput->append("apply = " + varPath);
}


void FormTest::extractVariableFile()
{
    CNRobo* pCon = CNRobo::getInstance();
    QString varPath = ui->txt_SetParam1->text();

    int retcode = pCon->exportVariable(varPath);

    if(retcode != 0)
    {
        ui->txtOutput->append(CUI_ERR_NOT_INPUTTED);
    }
    else
        ui->txtOutput->append("extract = " + varPath);
}


void FormTest::on_btnGetSDO_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
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

    unsigned long dataList[64];
    memset(dataList, 0, sizeof(dataList));

    pCon->getSDO(id, args, lenth, (unsigned long*)&dataList);

//  example code)
//    void* dataList;
//    unsigned long* idataList = ((unsigned long*)&dataList);       //unsigned long get
//    int* idataList = ((int*)&dataList);                           //int read

    for(int i = 0; i <lenth; i++)
    {
        str = QString::number(dataList[i]);
        ui->txtOutput->append(str);
    }
}

void FormTest::on_btnSetSDO_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
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

    ui->txtOutput->append(QString::number(retcode));
}

void FormTest::on_btnGetSDOList_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
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

    unsigned long dataList[64];
    memset(dataList, 0, sizeof(dataList));

    int dataLenth;

    pCon->getSDOList(args, argLenth, dataList, dataLenth);

    for(int i = 0; i <dataLenth; i++)
    {
        str = QString::number(dataList[i]);
        ui->txtOutput->append(str);
    }
}

void FormTest::on_btnWatchDog_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int time = ui->txtWatchTime->text().toInt(NULL, 10);
    int retcode = pCon->setWatchDogLimit(time);

    ui->txtOutput->append(QString::number(retcode));
}

void FormTest::on_btnMoveToPos_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    QString varName = ui->txtMoveToPos->text();
    float stableTime = ui->txtStableTime->text().toFloat();
    int retcode = pCon->moveToPosition2(varName,stableTime);

    ui->txtOutput->append(QString::number(retcode));
}

void FormTest::on_btnGetDateTime_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    QString strTime;
    pCon->getDateTime(strTime); //get - first format is Qt::ISODate

    QDateTime now = QDateTime::fromString(strTime, Qt::ISODate);
    ui->txtDateTime->setText(now.toString(Qt::ISODate)); //this format can change.
}

void FormTest::on_btnSetDateTime_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    QString strTime;
    strTime = ui->txtDateTime_2->text(); //getText Qt::ISODate

    QDateTime now = QDateTime::fromString(strTime, Qt::ISODate); //this format can change.
    pCon->setDateTime(now.toString(Qt::ISODate)); //set - last format is Qt::ISODate

}

void FormTest::on_btnSetInchingValue_clicked()
{
    DlgNumber dlg;

    CNRobo* pCon = CNRobo::getInstance();

    int level = 0;
    float step_mm = 0;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    dlg.sValue.clear();

    if(dlg.exec())
        step_mm = dlg.sValue.toFloat();

    QString str = QString("%1 / %2").arg(QString::number(level)).arg(QString::number(step_mm));

    ui->txtInchingValue_2->setText(str);

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->setInchingStep(level, step_mm);
}

void FormTest::on_btnGetInchingValue_clicked()
{
    DlgNumber dlg;

    CNRobo* pCon = CNRobo::getInstance();

    int level;
    float step_mm;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->getInchingStep(level, step_mm);

    QString str = QString("%2").arg(QString::number(step_mm));

    ui->txtInchingValue->setText(str);
}

void FormTest::on_btnSetLog_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int code = ui->txtLogCode->text().toInt();
    QString msg = ui->txtLogMsg->text();
    pCon->setUserLog(code, msg);
}


void FormTest::setBase()
{
    CNRobo* pCon = CNRobo::getInstance();
    QString str;
    QString trans;
    trans.append("base1");
    str.sprintf("Base %s", trans.toStdString().c_str());
    pCon->executeCommand(CNHelper::toMultiByteCode(str));
}

void FormTest::on_btnGetInchingAValue_clicked()
{
    DlgNumber dlg;

    CNRobo* pCon = CNRobo::getInstance();

    int level;
    float step_deg;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->getInchingStepAngular(level, step_deg);

    QString str = QString("%2").arg(QString::number(step_deg));
    ui->txtInchingAngleValue->setText(str);
}

void FormTest::on_btnSetInchingAValue_clicked()
{
    DlgNumber dlg;

    CNRobo* pCon = CNRobo::getInstance();

    int level = 0;
    float step_deg = 0;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    dlg.sValue.clear();

    if(dlg.exec())
        step_deg = dlg.sValue.toFloat();

    QString str = QString("%1 / %2").arg(QString::number(level)).arg(QString::number(step_deg));

    ui->txtInchingAngleValue_2->setText(str);

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->setInchingStepAngular(level, step_deg);
}

void FormTest::on_btn_GetCurProgramStack_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int task = 0;
    QStringList strList;
    pCon->getCurProgramStack(task, strList);
    for(int i = 0; i < strList.count(); i++)
        ui->txtOutput->append(strList[i]);
}

void FormTest::on_btnGetHomePosition_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    int index = ui->txtHomePositionIndex->text().toInt();
    int npos = pCon->getAxisCount();
    float pos[32];
    memset(pos, 0, sizeof(pos));
    float bound;

    pCon->getHomePosition(index, pos, npos, bound);

    ui->txtOutput->append(QString::number(index));

    for(int i = 0; i < npos; i++)
        ui->txtOutput->append(QString::number(pos[i]));

    ui->txtOutput->append(QString::number(bound));
}

void FormTest::on_btnSetHomePosition_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    int index = ui->txtHomePositionIndex->text().toInt();
    int npos = pCon->getAxisCount();
    float pos[32];
    memset(pos, 0, sizeof(pos));
    float bound = 0.01;

    QString str = ui->txtHomePositionPos->text();

    for(int i = 0; i < npos; i++)
    {
        pos[i] = str.section(",",i,i).toFloat();
    }

    pCon->setHomePosition(index, pos, npos, bound);
}

void FormTest::on_btnGetSlaveCount_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int count;
    pCon->getSlaveCount(count);
    ui->txtOutput->append(QString::number(count));
}

void FormTest::on_btnGetSlaveType_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    QVector<CNR_SLAVE_TYPE> type;
    pCon->getSlaveType(type);
    int count = type.count();

    for(int i = 0; i < count; i++)
    {
        ui->txtOutput->append(QString::number(type[i]));
    }
}

void FormTest::on_btnSetEMS_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    if(!pCon->isError())
    {
        pCon->setEMGOn(true);
        ui->btnSetEMS->setText("Set_EMS_OFF");
    }
    else
    {
        pCon->setEMGOn(false);
        ui->btnSetEMS->setText("Set_EMS_OON");
    }
}

void FormTest::on_btnGetSlaveModel_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QStringList slvList;
    pCon->getSlaveModel(slvList);
    int count = slvList.count();

    for(int i = 0; i < count; i++)
    {
        ui->txtOutput->append(slvList[i]);
    }
}

void FormTest::on_btnGetAutoRunSubPrg_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    bool enable;
    pCon->getAutoRunSubProgram(enable);

    ui->txtGetAutoRunValue->setText(QString::number(enable));
}

void FormTest::on_btnSetAutoRunSubPrg_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int value = ui->txtSetAutoRunValue->text().toInt();
    bool enable = value == 1 ? true : false;

    pCon->setAutoRunSubProgram(enable);
}

void FormTest::on_btnSaveProgram_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    QString progName = ui->txtSaveProgram->text();
    pCon->saveProgram(progName);
}

void FormTest::on_btnSaveProgramAll_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->saveProgramAll();
}

void FormTest::on_btnSaveVariable_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->saveVariable();
}

void FormTest::on_btnGetProgramAutoSave_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    bool enable;
    pCon->getProgramAutoSave(enable);
    ui->txtAutoSaveStatus->setText(enable == true ? "True" : "False");
}

void FormTest::on_btnSetProgramAutoSave_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    bool enable = ui->rbtn_AutoSaveTrue->isChecked();
    pCon->setProgramAutoSave(enable);
}

void FormTest::on_btnGetVariableAutoSave_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    bool enable;
    pCon->getVariableAutoSave(enable);
    ui->txtAutoSaveStatus->setText(enable == true ? "True" :"False");
}

void FormTest::on_btnSetVariableAutoSave_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    bool enable = ui->rbtn_AutoSaveTrue->isChecked();
    pCon->setVariableAutoSave(enable);
}

void FormTest::on_btnSetCmdCycleTime_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int msec = ui->txtCmdCycleTime->text().toInt();
    pCon->setCommandCycleTime(msec);
}

void FormTest::on_btnGetCmdCycleTime_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int msec = pCon->getCommandCycleTime();
    ui->txtCmdCycleTime->setText(QString::number(msec));
}


void FormTest::on_btnRebootSystem_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->rebootSystem();
}
void FormTest::on_btnClean_clicked()
{
    ui->txtOutput->clear();
}

void FormTest::on_btnGetInchingAcc_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    float accTime;
    pCon->getInchingAccTime(accTime);

    ui->txtGetInchingAcc->setText(QString::number(accTime));
}

void FormTest::on_btnSetInchingAcc_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    float accTime = ui->txtSetInchingAcc->text().toFloat();

    pCon->setInchingAccTime(accTime);
}

void FormTest::on_btnCheckMode_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    if(!pCon->getCheckMode())
    {
        QString progName = pCon->getCurProgramName(0);
        pCon->setCheckProgram(progName,0);
        pCon->setCheckMode(true);
    }
    else
    {
        pCon->setCheckMode(false);
    }
}

void FormTest::on_btnChechKeyFWD_pressed()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->setCheckKey(1);
}

void FormTest::on_btnChechKeyFWD_released()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->setCheckKey(0);

}

void FormTest::on_btnCalcInverse_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    float* oldang = pCon->getCurJoint();
    float* trans = pCon->getCurTrans();
    cn_trans trIn;
    cn_conf confIn;
    float jointOut[32] = {0,};

    for(int i = 0; i < 3; i++)
    {
        trIn.p[i] = trans[i];
        trIn.eu[i] = trans[i+3];
    }
    confIn.cfx = 0x00;
    pCon->calcInverse(trIn, oldang, jointOut, confIn);

    int nAxis = pCon->getAxisCount();

    QStringList strList;

    for(int i = 0; i < nAxis; i++)
        strList.append(QString::number(jointOut[i]));

    QString str = strList.join(",");

    ui->txtOutput->append(str);
}

void FormTest::on_btnBaseFrame_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    cn_trans2 baseFrame;
    pCon->getCurBaseFrame(baseFrame);

    QString str;
    str.sprintf("%f,%f,%f \n %f,%f,%f, \n %f,%f,%f, \n %f,%f,%f,",
                baseFrame.n.x, baseFrame.n.y, baseFrame.n.z,
                baseFrame.o.x, baseFrame.o.y, baseFrame.o.z,
                baseFrame.a.x, baseFrame.a.y, baseFrame.a.z,
                baseFrame.p.x, baseFrame.p.y, baseFrame.p.z
                );

    ui->txtOutput->append(str);
}

void FormTest::on_btnGetVersion2_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QStringList strList;

    QString strVer;
    pCon->getVersion2(CNRobo::VT_CNROBO, strVer);
    strList.append(strVer);

    pCon->getVersion2(CNRobo::VT_CORESERVER, strVer);
    strList.append(strVer);

    pCon->getVersion2(CNRobo::VT_MASTER, strVer);
    strList.append(strVer);

    pCon->getVersion2(CNRobo::VT_KERNEL, strVer);
    strList.append(strVer);


    for(int i = 0; i < strList.size(); i++)
        ui->txtOutput->append(strList[i]);
}

void FormTest::on_btnGetTrajectory_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    int type = ui->txtTrajType->text().toInt();

    int size;
    pCon->getTrajectoryLogSize(size);

    int nCount = pCon->getAxisCount();

    if(size >= 10000)
        size = 10000;

    QStringList strList;

    cn_trajectory trj[10000]; //20sec

    if(type == 0)
    {
        pCon->getTrajectoryS(trj, size);

        for(int i = 0; i < size; i++)
        {
            strList.append(QString::number(trj[i].S));
        }
    }
    else if(type == 1)
    {
        pCon->getTrajectoryCurEncoder(trj, size);

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < nCount; j++)
            {
                strList.append(QString::number(trj[i].enc[j]));
            }
        }
    }
    else if(type == 2)
    {
        pCon->getTrajectoryCmdEncoder(trj, size);

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < nCount; j++)
            {
                strList.append(QString::number(trj[i].enc[j]));
            }
        }
    }
    else if(type == 3)
    {
        pCon->getTrajectoryCmdTrans(trj, size);

        for(int i = 0; i < size; i++)
        {
            strList.append(QString::number(trj[i].trans.x));
            strList.append(QString::number(trj[i].trans.y));
            strList.append(QString::number(trj[i].trans.z));
        }
    }

    for(int i = 0; i < strList.size(); i++)
        ui->txtOutput->append(strList[i]);
}


void FormTest::on_btnStartTrajectory_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->startTrajectoryLogging();
}

void FormTest::on_btnStopTrajectory_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->stopTrajectoryLogging();
}

void FormTest::on_btnServoOnMode_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    int mode = ui->txtServoOnMode->text().toInt();

    pCon->setServoOnMode(mode);
}

void FormTest::on_btn_SetBuzzerOn_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->setDTPBuzzerOn2(10,1,1);
}

void FormTest::on_btn_setBuzzerOff_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->setDTPBuzzerOff();
}
