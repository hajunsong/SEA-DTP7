#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>

namespace Ui {
class FormMain;
}

class FormMain : public QWidget
{
    Q_OBJECT

public:
    explicit FormMain(QWidget *parent = 0);
    ~FormMain();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private slots:
    void on_btnTest_clicked();
    void on_btnLogin_clicked();
    void on_btnLock_clicked();
    void onTimer();

    void on_btnDI_clicked();
    void on_btnDO_clicked();
    void on_btnAI_clicked();
    void on_btnAO_clicked();
    void on_btnZeroing_clicked();
    void on_btnDOSet_clicked();
    void on_btnAOSet_clicked();
    void on_btnService_clicked();
    void on_btnClean_clicked();

private:
    Ui::FormMain *ui;

    QTimer* m_timer;
};

#endif // FORMMAIN_H
