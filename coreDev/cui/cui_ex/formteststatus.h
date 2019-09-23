#ifndef FORMTESTSTATUS_H
#define FORMTESTSTATUS_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class FormTestStatus;
}

class FormTestStatus : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestStatus(QWidget *parent = 0);
    ~FormTestStatus();

    QTimer* m_timer;

private:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private slots:
    void onTimer();

private:
    Ui::FormTestStatus *ui;
};

#endif // FORMTESTSTATUS_H
