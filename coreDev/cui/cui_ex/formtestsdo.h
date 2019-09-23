#ifndef FORMTESTSDO_H
#define FORMTESTSDO_H

#include <QWidget>

namespace Ui {
class FormTestSDO;
}

class FormTestSDO : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestSDO(QWidget *parent = 0);
    ~FormTestSDO();

private slots:
    void on_btnGetSDO_clicked();
    void on_btnSetSDO_clicked();
    void on_btnGetSDOList_clicked();

private:
    Ui::FormTestSDO *ui;

    void appendTxtOut(const QString& str);
};

#endif // FORMTESTSDO_H
