#ifndef FORMTESTINCHING_H
#define FORMTESTINCHING_H

#include <QWidget>

namespace Ui {
class FormTestInching;
}

class FormTestInching : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestInching(QWidget *parent = 0);
    ~FormTestInching();

private slots:
    void on_btnSetInchingValue_clicked();
    void on_btnGetInchingValue_clicked();
    void on_btnGetInchingAValue_clicked();
    void on_btnSetInchingAValue_clicked();
    void on_btnGetInchingAccTime_clicked();
    void on_btnSetInchingAccTime_clicked();

private:
    Ui::FormTestInching *ui;
};

#endif // FORMTESTINCHING_H
