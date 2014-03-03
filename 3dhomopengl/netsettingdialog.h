#ifndef NETSETTINGDIALOG_H
#define NETSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class netsettingDialog;
}

class netsettingDialog : public QDialog
{
    Q_OBJECT

public:
    netsettingDialog(QWidget *parent = 0);
	~netsettingDialog();
    QString getHost();
    QString getPort();


private slots:
    /*
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetFortuneButton();
    void sessionOpened();
*/
private:
    Ui::netsettingDialog *ui;

    };


#endif // NETSETTINGDIALOG_H
