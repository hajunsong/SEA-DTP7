#ifndef FORMDI_H
#define FORMDI_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QLabel>


namespace Ui {
class FormDI;
}

class FormDI : public QWidget
{
    Q_OBJECT
    QTimer* m_timer;
    QVector<QPushButton*> m_btnSet;
    QVector<QLabel*> m_lblSet;

    int m_idx;

public:
    explicit FormDI(QWidget *parent = 0);
    ~FormDI();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private slots:
    void updateStatus();
    void setDI();
    void on_btnPrev_clicked();
    void on_btnNext_clicked();

private:
    Ui::FormDI *ui;
};

#endif // FORMDI_H
