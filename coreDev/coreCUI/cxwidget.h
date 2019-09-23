#ifndef CXWIDGET_H
#define CXWIDGET_H

#include <QWidget>

class CxWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString wStyle READ wStyle WRITE setWStyle)

    QString m_style;

public:
    explicit CxWidget(QWidget *parent = 0);

    void setWStyle(QString style);
    QString wStyle() const { return m_style; }

protected:
    void paintEvent(QPaintEvent*);
signals:

public slots:
};

#endif // CXWIDGET_H
