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
    void on_btnStatr_clicked();
    void on_btnStop_clicked();

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

    void onTimer();

    void on_btnHome_clicked();

private:
    Ui::FormTestHome *ui;
};

#endif // FORMTESTHOME_H
