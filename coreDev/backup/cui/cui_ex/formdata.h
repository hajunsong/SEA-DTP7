#ifndef FORMDATA_H
#define FORMDATA_H

#include <QWidget>

namespace Ui {
class FormData;
}

class FormData : public QWidget
{
    Q_OBJECT

    void regenJoint();
    void regenTrans();
    void regenNumber();
    void regenString();

    void updateJointItem(int index);
    void updateTransItem(int index);

    void teachVarJoint();

public:
    explicit FormData(QWidget *parent = 0);
    ~FormData();

protected:
    void showEvent(QShowEvent* evt);

private slots:
    void on_btnEdit_clicked();

private:
    Ui::FormData *ui;

    QStringList m_jointLabels;
    QStringList m_transLabels;
    QStringList m_numberLabels;
};

#endif // FORMDATA_H
