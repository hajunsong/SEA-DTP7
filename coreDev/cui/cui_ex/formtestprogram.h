#ifndef FORMTESTPROGRAM_H
#define FORMTESTPROGRAM_H

#include <QWidget>

namespace Ui {
class FormTestProgram;
}

class FormTestProgram : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestProgram(QWidget *parent = 0);
    ~FormTestProgram();

signals:
    void appendText(QString str);

private slots:
    void on_btnListPrograms_clicked();
    void on_btnSetSteps_clicked();
    void on_btnLoadProgram_clicked();
    void on_btnDeleteProgram_clicked();

private:
    Ui::FormTestProgram *ui;

    void appendTxtOut(QStringList list);
};

#endif // FORMTESTPROGRAM_H
