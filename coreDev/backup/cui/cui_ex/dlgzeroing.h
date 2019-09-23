#ifndef DLGZEROING_H
#define DLGZEROING_H

#include <QDialog>

namespace Ui {
class DlgZeroing;
}

class DlgZeroing : public QDialog
{
    Q_OBJECT

public:
    explicit DlgZeroing(QWidget *parent = 0);
    ~DlgZeroing();

private slots:
    void on_btnZeroing_clicked();
    void on_btnSetZeroingOffset_clicked();
    void on_btnGetZeroingOffset_clicked();
    void on_btnOk_clicked();
    void on_btnClose_clicked();
    void on_sbIndex_valueChanged(int arg1);

    void on_btnGetZeroingCount_clicked();

private:
    Ui::DlgZeroing *ui;
};

#endif // DLGZEROING_H
