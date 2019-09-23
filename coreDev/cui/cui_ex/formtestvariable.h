#ifndef FORMTESTVARIABLE_H
#define FORMTESTVARIABLE_H

#include <QWidget>

struct CUIFCTxt
{
    QString name_getbtn;
    QString name_setbtn;
    QString exam_a;
    QString exam_b;
    int findex;
    int hiddenCmd;
};

namespace Ui {
class FormTestVariable;
}

class FormTestVariable : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestVariable(QWidget *parent = 0);
    ~FormTestVariable();

private slots:
    void on_rbtn_VariableData_clicked();
    void on_rbtn_VariableList_clicked();
    void on_rbtn_VariableCount_clicked();
    void on_rbtn_VariableDelete_clicked();
    void on_rbtn_VarDeleteAll_clicked();
    void on_rbtn_Variables_clicked();
    void on_btn_SetData_pressed();
    void on_btn_GetData_pressed();

private:
    Ui::FormTestVariable *ui;

    void setVariableData();
    void getVariableData();

    void getVariableList();
    void getVariableCount();

    void deleteVariable();
    void deleteVariableAll();

    void setVariables();
    void getVariables();

    void setWidgetHidden(int hdnCmd);
    void setFunctionStruct(CUIFCTxt& cft);

    int m_axisCount;
    int m_functionIndex;

    void appendTxtOut(QStringList &list);
    void appendTxtOut(const QString& str);

};

#endif // FORMTESTVARIABLE_H
