#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer* m_timer;

protected:
    void resizeWindow();
    void resizeEvent(QResizeEvent *);
private slots:
    void onClickMenuButton();
    void onTimer();

private:
    void printOutputMessage();
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    Ui::MainWindow *ui;

    QList<QPushButton*> m_menuBtns;
};

#endif // MAINWINDOW_H
