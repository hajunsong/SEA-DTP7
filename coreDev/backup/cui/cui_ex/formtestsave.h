#ifndef FORMTESTSAVE_H
#define FORMTESTSAVE_H

#include <QWidget>

namespace Ui {
class FormTestSave;
}

class FormTestSave : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestSave(QWidget *parent = 0);
    ~FormTestSave();

private slots:
    void on_btnSaveVariable_clicked();
    void on_btnSaveProgram_clicked();
    void on_btnSaveProgramAll_clicked();

private:
    Ui::FormTestSave *ui;
};

#endif // FORMTESTSAVE_H
