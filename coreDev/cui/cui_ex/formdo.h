#ifndef FORMDO_H
#define FORMDO_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QLabel>


namespace Ui {
class FormDO;
}

class FormDO : public QWidget
{
    Q_OBJECT

    QTimer* m_timer;
    QVector<QPushButton*> m_btnSet;
    QVector<QLabel*> m_lblSet;

    int m_idx;


public:
    explicit FormDO(QWidget *parent = 0);
    ~FormDO();
protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private slots:
    void updateStatus();
    void setDO();
    void resetAll_DO();
    void on_btnPrev_clicked();
    void on_btnNext_clicked();
    void on_btnReset_clicked();

private:
    Ui::FormDO *ui;
};

#endif // FORMDO_H
