#include "colorlabel.h"
#include <QDebug>

colorLabel::colorLabel(QWidget *parent):QLabel(parent)
{
    functionColor = QColor::fromRgb(170,170,255);
    QString backGroundColor = QString::fromLatin1(" QLabel { background-color : %1}").arg(functionColor.name());
    this->setStyleSheet(backGroundColor);

}

void colorLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    functionColor = QColorDialog::getColor(this->functionColor,this);
    if(functionColor.isValid())
    {
	QString backGroundColor = QString::fromLatin1(" QLabel { background-color : %1}").arg(functionColor.name());
	this->setStyleSheet(backGroundColor);
    }
    emit colorSelected(&functionColor);
}

void colorLabel::setColor(QColor functionColor)
{
     QString backGroundColor = QString::fromLatin1(" QLabel { background-color : %1}").arg(functionColor.name());
    this->setStyleSheet(backGroundColor);

}

