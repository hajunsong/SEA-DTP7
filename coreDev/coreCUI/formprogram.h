#ifndef FORMPROGRAM_H
#define FORMPROGRAM_H


#include <QWidget>
#include <QAbstractTableModel>
#include <QModelIndex>



namespace Ui {
class FormProgram;
}



class ProgramStepModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    QStringList steps;

    void regen();  
    void appendStep(QString str);
    void editStep(QString str, int index);

    ProgramStepModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

};


class FormProgram : public QWidget
{
    Q_OBJECT

public:
    explicit FormProgram(QWidget *parent = 0);
    ~FormProgram();

private:
    Ui::FormProgram *ui;

protected:
    void regenProgramSteps();
    void showEvent(QShowEvent *);
private slots:


    void on_btnOpenProgram_clicked();
    void on_btnInsertProgram_clicked();
    void on_btnSaveProgram_clicked();
    void on_btnEditProgram_clicked();
};

#endif // FORMPROGRAM_H
