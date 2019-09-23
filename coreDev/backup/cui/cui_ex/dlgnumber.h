#ifndef DLGNUMBER_H
#define DLGNUMBER_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class DlgNumber;
}

class DlgNumber : public QDialog
{
    Q_OBJECT

public:
    explicit DlgNumber(QWidget *parent = 0);
    ~DlgNumber();

    QString title;

    int iValue;
    float fValue;
    QString sValue;
private:
    void handdleButton(QPushButton* btn);
    void setDisplayText();
private slots:
    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();
    void on_btnDot_clicked();
    void on_btnMinus_clicked();
    void on_btnClear_clicked();
    void on_btnDel_clicked();
    void on_btnOK_clicked();
    void on_btnCancel_clicked();


private:
    Ui::DlgNumber *ui;
};

#endif // DLGNUMBER_H
