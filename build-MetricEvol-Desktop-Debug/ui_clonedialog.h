/********************************************************************************
** Form generated from reading UI file 'clonedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLONEDIALOG_H
#define UI_CLONEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
            CloneDialog->setObjectName(QStringLiteral("CloneDialog"));
        CloneDialog->resize(400, 163);
        widget = new QWidget(CloneDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 371, 131));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
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
        CloneDialog->setWindowTitle(QApplication::translate("CloneDialog", "Dialog", 0));
        label->setText(QApplication::translate("CloneDialog", "Enter Repository URL:", 0));
        label_2->setText(QApplication::translate("CloneDialog", "E.g. git://github.com/author/repo.git", 0));
    } // retranslateUi

};

namespace Ui {
    class CloneDialog: public Ui_CloneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLONEDIALOG_H
