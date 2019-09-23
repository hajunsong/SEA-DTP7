#ifndef DLGTEXTINPUT_H
#define DLGTEXTINPUT_H

#include <QDialog>

namespace Ui {
class DlgTextInput;
}

class DlgTextInput : public QDialog
{
    Q_OBJECT

public:

    QString str;
    int     integer;

public:
    explicit DlgTextInput(QWidget *parent = 0);
    ~DlgTextInput();

    void setText();

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

private:
    Ui::DlgTextInput *ui;
};

#endif // DLGTEXTINPUT_H
