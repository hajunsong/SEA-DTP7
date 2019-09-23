#include "formtestvariable.h"
#include "ui_formtestvariable.h"

#include "formtest.h"
#include "cuiapi.h"
#include "cerror.h"

FormTestVariable::FormTestVariable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestVariable)
{
    ui->setupUi(this);

    on_rbtn_VariableData_clicked();


    CUIApp* pCon = CUIApp::getInstance();

    m_axisCount = pCon->getAxisCount();

}

FormTestVariable::~FormTestVariable()
{
    delete ui;
}

void FormTestVariable::on_rbtn_VariableData_clicked()
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

void FormTestVariable::on_rbtn_VariableList_clicked()
{
    CUIFCTxt cft;

    cft.name_getbtn = "getVariableList";
    cft.exam_a = "get : 1. Type:1~4 (1.Joint, 2.Trans, 3.Number, 4.String),  2.Name";
    cft.exam_b = "";
    cft.findex = 2;
    cft.hiddenCmd = 0x003;

    setFunctionStruct(cft);
}

void FormTestVariable::on_rbtn_VariableCount_clicked()
{
    CUIFCTxt cft;

    cft.name_getbtn = "getVariableCount";
    cft.exam_a = "get : 1. Type:1~4 (1.Joint, 2.Trans, 3.Number, 4.String),  2.Name";
    cft.exam_b = "";
    cft.findex = 3;
    cft.hiddenCmd = 0x003;

    setFunctionStruct(cft);
}

void FormTestVariable::on_rbtn_VariableDelete_clicked()
{
    CUIFCTxt cft;

    cft.name_setbtn = "deleteVariable";
    cft.exam_a = "delete : 1. Name";
    cft.exam_b = "";
    cft.findex = 4;
    cft.hiddenCmd = 0x070;

    setFunctionStruct(cft);
}

void FormTestVariable::on_rbtn_VarDeleteAll_clicked()
{
    CUIFCTxt cft;

    cft.name_setbtn = "deleteVariableAll";
    cft.exam_a = "";
    cft.exam_b = "";
    cft.findex = 5;
    cft.hiddenCmd = 0x010;

    setFunctionStruct(cft);
}

void FormTestVariable::on_rbtn_Variables_clicked()
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

void FormTestVariable::setFunctionStruct(CUIFCTxt& cft)
{
    ui->btn_GetData->setText(cft.name_getbtn);
    ui->btn_SetData->setText(cft.name_setbtn);
    ui->lb_Example->setText(cft.exam_a);
    ui->lb_Example_2->setText(cft.exam_b);

    m_functionIndex = cft.findex;
    setWidgetHidden(cft.hiddenCmd);
}

void FormTestVariable::setWidgetHidden(int hdnCmd)
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

void FormTestVariable::on_btn_SetData_pressed()
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
        break;
    case 8:
        break;
    }
}

void FormTestVariable::on_btn_GetData_pressed()
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

void FormTestVariable::setVariableData()
{
    CUIApp* pCon = CUIApp::getInstance();

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
        appendTxtOut(CUI_ERR_NOT_INPUTTED);
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
        break;    {
        appendTxtOut("Vaiable empty!");
        return;
    }
    case 2:
        for(int i = 0; i < 6; i++)
        {
            floatValue = strValue.section(",",i,i).toFloat();
            variValue.val.trans.p[i] = floatValue;
        }

        break;
    case 3:
            floatValue = strValue.toFloat();
            variValue.val.f32 = floatValue;
        break;
    case 4:
            strcpy(variValue.val.str, strValue.toStdString().c_str());
        break;
    }

    retcode = pCon->setVariableData(varType, strName, variValue, true);

    if(retcode != 0)
    {
        appendTxtOut(CUI_ERR_NOT_REPORTED);
        return;
    }

    retList.append("set =" + strType + "," + strName + "," + strValue);

    for(int i = 0; i < retList.size(); i++)
    {
        appendTxtOut(retList[i]);
    }
}

void FormTestVariable::getVariableData()
{
    CUIApp* pCon = CUIApp::getInstance();

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
        appendTxtOut(CUI_ERR_NOT_INPUTTED);
        return;
    }

    retcode = pCon->getVariableData(varType,strName,&varValue);

    if(retcode != 0)
    {
        appendTxtOut(CUI_ERR_NOT_REPORTED);
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
        appendTxtOut("Vaiable empty!");
        return;
    }

    for(int i = 0; i < retList.size(); i++)
    {
        appendTxtOut(retList[i]);
    }
}

void FormTestVariable::getVariableList()
{
    CUIApp* pCon = CUIApp::getInstance();

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
        appendTxtOut(CUI_ERR_NOT_INPUTTED);
        return;
    }

    varType = strType.toInt();

    retcode = pCon->getVariableList(varType, vatNames, varDatas);

    if(retcode != 0)
    {
        appendTxtOut(CUI_ERR_NOT_REPORTED);
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
                str.sprintf("%.3f", varDatas[0].val.trans.p[j]);
                retList.append(str);
            }
            for(int j = 0; j < 3; j ++)
            {
                str.sprintf("%.3f", varDatas[0].val.trans.eu[j]);
                retList.append(str);
            }
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
        appendTxtOut("Vaiable empty!");
        return;
    }

    for(int i = 0; i < retList.size(); i++)
    {
        appendTxtOut(retList[i]);
    }
}


void FormTestVariable::getVariableCount()
{
    CUIApp* pCon = CUIApp::getInstance();

    int retcode = 0;
    int varType = 0;
    int varCount = 0;
    QString strType;

    strType = ui->txt_GetParam1->text();

    if(strType.isEmpty())
    {
        appendTxtOut(CUI_ERR_NOT_INPUTTED);
        return;
    }

    varType = strType.toInt();

    QStringList retList;

    retcode = pCon->getVariableCount(varType, &varCount);

    if(retcode != 0)
    {
        appendTxtOut(CUI_ERR_NOT_REPORTED);
        return;
    }

    retList.append("variableCount =" + QString::number(varCount));

    for(int i = 0; i < retList.size(); i++)
    {
        appendTxtOut(retList[i]);
    }
}

void FormTestVariable::deleteVariable()
{
    CUIApp* pCon = CUIApp::getInstance();

    int retcode = 0;
    int varType = 0;
    QString strType;
    QString varName;

    strType = ui->txt_SetParam1->text();
    varName = ui->txt_SetParam2->text();

    if(strType.isEmpty() || varName.isEmpty())
    {
        appendTxtOut(CUI_ERR_NOT_INPUTTED);
        return;
    }

    varType = strType.toInt();

    qDebug("varType = %d", varType);
    qDebug("varName = %s", varName.toStdString().c_str());


    retcode = pCon->deleteVariable(varType, varName);

    if(retcode != 0)
    {
        appendTxtOut(CUI_ERR_NOT_REPORTED);
    }
    else
        appendTxtOut("delete = " + QString::number(varType) + "," + varName);
}

void FormTestVariable::deleteVariableAll()
{
    CUIApp* pCon = CUIApp::getInstance();
    pCon->deleteVariableAll();
}

void FormTestVariable::setVariables()
{
    CUIApp* pCon = CUIApp::getInstance();
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
            strWork = vars[j];
            var.val.trans.eu[j] = strWork.toFloat();
        }
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
        appendTxtOut(str);
    }
}

void FormTestVariable::getVariables()
{
    CUIApp* pCon = CUIApp::getInstance();

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

            break;
        case CNVAR_FLOAT:
            strList.append("(3)");
            strList.append(QString::number(var.val.f32));
            break;
        case CNVAR_STRING:
            strList.append("(4)");
            strList.append(var.val.str);
            break;
        }

        QString str = strList.join(",");
        appendTxtOut(str);
    }
}


void FormTestVariable::appendTxtOut(QStringList& list)
{
    FormTest* pTest = FormTest::getInstance();
    pTest->appendTxtOut(list);
}

void FormTestVariable::appendTxtOut(const QString& str)
{
    FormTest* pTest = FormTest::getInstance();
    QStringList list;

    list.append(str);
    pTest->appendTxtOut(list);
}
