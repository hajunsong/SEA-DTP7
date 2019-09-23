#ifndef FORMTESTDATABASE_H
#define FORMTESTDATABASE_H

#include <QWidget>
#include <QStringList>
#include <QPushButton>

enum DATABASE_TYPE
{
    DT_PROG = 1,
    DT_VAR,
    DT_DIR,
    DT_FILE
};

enum BTN_TYPE
{
    BT_LIST = 0,
    BT_MAKE,
    BT_LOAD,
    BT_SET,
    BT_COPY,
    BT_MOVE,
    BT_CHECK,
    BT_DELETE
};

namespace Ui {
class FormTestDatabase;
}

class FormTestDatabase : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestDatabase(QWidget *parent = 0);
    ~FormTestDatabase();

private slots:
    void on_rbtnProg_clicked();
    void on_rbtnVar_clicked();
    void on_rbtnDir_clicked();
    void on_rbtnFile_clicked();

    void on_btnList_clicked();
    void on_btnMake_clicked();
    void on_btnLoad_clicked();
    void on_btnSet_clicked();
    void on_btnCopy_clicked();
    void on_btnMove_clicked();
    void on_btnDelete_clicked();
    void on_btnCheckExist_clicked();

private:
    Ui::FormTestDatabase *ui;

    void setTxtOut(QStringList list);

    void setTxtMenu(DATABASE_TYPE type);
    QVector<QPushButton*> m_btnList;

    DATABASE_TYPE m_dtType;

};

#endif // FORMTESTDATABASE_H
