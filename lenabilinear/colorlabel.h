#ifndef COLORLABEL
#define COLORLABEL 
#include <QLabel>
#include <QColorDialog>
class colorLabel:public QLabel
{
    Q_OBJECT
public:
    explicit colorLabel(QWidget *parent = 0);
    void mouseDoubleClickEvent(QMouseEvent *);
    QColor functionColor;
    void setColor(QColor);

signals:
    void colorSelected(QColor *);
};
#endif //COLORLABEL
