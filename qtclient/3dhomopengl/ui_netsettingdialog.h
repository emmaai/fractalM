/********************************************************************************
** Form generated from reading UI file 'netsettingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETSETTINGDIALOG_H
#define UI_NETSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_netsettingDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *portlabel;
    QLineEdit *portlineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *hostlabel;
    QComboBox *hostcomboBox;

    void setupUi(QDialog *netsettingDialog)
    {
        if (netsettingDialog->objectName().isEmpty())
            netsettingDialog->setObjectName(QStringLiteral("netsettingDialog"));
        netsettingDialog->resize(400, 208);
        buttonBox = new QDialogButtonBox(netsettingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 160, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(netsettingDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 90, 241, 29));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        portlabel = new QLabel(layoutWidget);
        portlabel->setObjectName(QStringLiteral("portlabel"));

        horizontalLayout_2->addWidget(portlabel);

        portlineEdit = new QLineEdit(layoutWidget);
        portlineEdit->setObjectName(QStringLiteral("portlineEdit"));

        horizontalLayout_2->addWidget(portlineEdit);

        layoutWidget1 = new QWidget(netsettingDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(50, 20, 241, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        hostlabel = new QLabel(layoutWidget1);
        hostlabel->setObjectName(QStringLiteral("hostlabel"));

        horizontalLayout->addWidget(hostlabel);

        hostcomboBox = new QComboBox(layoutWidget1);
        hostcomboBox->setObjectName(QStringLiteral("hostcomboBox"));
        hostcomboBox->setEditable(true);
        hostcomboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);

        horizontalLayout->addWidget(hostcomboBox);


        retranslateUi(netsettingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), netsettingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), netsettingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(netsettingDialog);
    } // setupUi

    void retranslateUi(QDialog *netsettingDialog)
    {
        netsettingDialog->setWindowTitle(QApplication::translate("netsettingDialog", "Network Setting", 0));
        portlabel->setText(QApplication::translate("netsettingDialog", "port", 0));
        hostlabel->setText(QApplication::translate("netsettingDialog", "host", 0));
        hostcomboBox->clear();
        hostcomboBox->insertItems(0, QStringList()
         << QApplication::translate("netsettingDialog", "115.146.93.25", 0)
         << QApplication::translate("netsettingDialog", "localhost", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class netsettingDialog: public Ui_netsettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETSETTINGDIALOG_H
