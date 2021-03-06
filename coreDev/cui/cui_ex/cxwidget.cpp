#include "cxwidget.h"
#include "ui_cxwidget.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

CxWidget::CxWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CxWidget)
{
    ui->setupUi(this);
}

CxWidget::~CxWidget()
{
    delete ui;
}


void CxWidget::setWStyle(QString style)
{
    m_style = style;

    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}


void CxWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
