#ifndef FORMMAINWINDOW_H
#define FORMMAINWINDOW_H

#include <QWidget>
#include <QPushButton>


namespace Ui {
class FormMainWindow;
}

class FormMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FormMainWindow(QWidget *parent = 0);
    ~FormMainWindow();

    QTimer* m_timer;

protected:
    void resizeWindow();
    void resizeEvent(QResizeEvent *);
    void printDriverErrorMsg();

private:
    void printOutputMessage();
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private slots:
    void onClickMenuButton();
    void onTimer();

private:
    Ui::FormMainWindow *ui;

    QTimer* m_pTimer;

    QList<QPushButton*> m_menuBtns;
};

#endif // FORMMAINWINDOW_H
