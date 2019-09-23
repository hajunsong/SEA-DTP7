#ifndef FORMTESTWORLDZONE_H
#define FORMTESTWORLDZONE_H

#include <QWidget>
#include <QTimer>
#include <QShowEvent>
#include <QHideEvent>

namespace Ui {
class FormTestWorldZone;
}

class FormTestWorldZone : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestWorldZone(QWidget *parent = 0);
    ~FormTestWorldZone();

    QTimer* m_timer;

    int m_index;

private slots:
    void onTimer();


    void on_btnAddBox_clicked();
    void on_btnAddCyl_clicked();
    void on_btnClear_clicked();
    void on_btnSetEnable_clicked();
    void on_btnGetBox_clicked();
    void on_btnGetCyl_clicked();

private:
    Ui::FormTestWorldZone *ui;

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

    void appendTxtOut(QStringList& list);
    void appendTxtOut(const QString& str);

};

#endif // FORMTESTWORLDZONE_H
