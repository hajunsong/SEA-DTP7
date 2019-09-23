#ifndef FORMROBOTCONF_H
#define FORMROBOTCONF_H

#include <QWidget>

namespace Ui {
class FormRobotConf;
}

class FormRobotConf : public QWidget
{
    Q_OBJECT

public:
    explicit FormRobotConf(QWidget *parent = 0);
    ~FormRobotConf();

private slots:
    void on_btnGetRobotConf_clicked();
    void on_btnSetRobotConf_clicked();

private:
    Ui::FormRobotConf *ui;
};

#endif // FORMROBOTCONF_H
