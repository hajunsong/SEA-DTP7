#ifndef DLGPROGRAM_H
#define DLGPROGRAM_H

#include <QDialog>
#include <QStringList>
#include <QListWidgetItem>

namespace Ui {
class DlgProgram;
}

class DlgProgram : public QDialog
{
    Q_OBJECT

    QStringList m_listProgram;
    QString m_selectedProgram;
public:
    explicit DlgProgram(QWidget *parent = 0);
    ~DlgProgram();

    QString& getSelectedProgram() { return m_selectedProgram; }

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();
    void on_programList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::DlgProgram *ui;
};

#endif // DLGPROGRAM_H
