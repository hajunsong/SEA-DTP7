#ifndef FORMTESTHOME_H
#define FORMTESTHOME_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class FormTestHome;
}

class FormTestHome : public QWidget
{
    Q_OBJECT

    QTimer* m_timer;

public:
    explicit FormTestHome(QWidget *parent = 0);
    ~FormTestHome();

private slots:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

    void onTimer();

    void on_btnStatr_clicked();
    void on_btnStop_clicked();
    void on_btnHome_clicked();
    void on_btnSystemLimitOn_clicked();
    void on_btnSystemLimitOff_clicked();
    void on_btnGetHomePosition_clicked();
    void on_btnSetHomePosition_clicked();

private:
    Ui::FormTestHome *ui;

    void appendTxtOut(const QString& str);

};

#endif // FORMTESTHOME_H
