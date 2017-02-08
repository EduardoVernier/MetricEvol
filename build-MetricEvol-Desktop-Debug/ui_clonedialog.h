/********************************************************************************
** Form generated from reading UI file 'clonedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLONEDIALOG_H
#define UI_CLONEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CloneDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CloneDialog)
    {
        if (CloneDialog->objectName().isEmpty())
            CloneDialog->setObjectName(QString::fromUtf8("CloneDialog"));
        CloneDialog->resize(400, 163);
        widget = new QWidget(CloneDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 371, 131));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CloneDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CloneDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CloneDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CloneDialog);
    } // setupUi

    void retranslateUi(QDialog *CloneDialog)
    {
        CloneDialog->setWindowTitle(QApplication::translate("CloneDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CloneDialog", "Enter Repository URL:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CloneDialog", "E.g. git://github.com/author/repo.git", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CloneDialog: public Ui_CloneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLONEDIALOG_H
