/********************************************************************************
** Form generated from reading UI file 'DifficultyWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFICULTYWINDOW_H
#define UI_DIFFICULTYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DifficultyWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnStart;
    QPushButton *btnEasy;
    QPushButton *btnMedium;
    QPushButton *btnDifficult;
    QPushButton *btnBack;

    void setupUi(QMainWindow *DifficultyWindow)
    {
        if (DifficultyWindow->objectName().isEmpty())
            DifficultyWindow->setObjectName(QStringLiteral("DifficultyWindow"));
        DifficultyWindow->resize(280, 276);
        DifficultyWindow->setStyleSheet(QStringLiteral("background-color: rgb(142, 142, 142);"));
        centralWidget = new QWidget(DifficultyWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnStart = new QPushButton(centralWidget);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnStart, 0, Qt::AlignHCenter);

        btnEasy = new QPushButton(centralWidget);
        btnEasy->setObjectName(QStringLiteral("btnEasy"));
        sizePolicy.setHeightForWidth(btnEasy->sizePolicy().hasHeightForWidth());
        btnEasy->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnEasy, 0, Qt::AlignHCenter);

        btnMedium = new QPushButton(centralWidget);
        btnMedium->setObjectName(QStringLiteral("btnMedium"));
        sizePolicy.setHeightForWidth(btnMedium->sizePolicy().hasHeightForWidth());
        btnMedium->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnMedium, 0, Qt::AlignHCenter);

        btnDifficult = new QPushButton(centralWidget);
        btnDifficult->setObjectName(QStringLiteral("btnDifficult"));
        sizePolicy.setHeightForWidth(btnDifficult->sizePolicy().hasHeightForWidth());
        btnDifficult->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnDifficult, 0, Qt::AlignHCenter);

        btnBack = new QPushButton(centralWidget);
        btnBack->setObjectName(QStringLiteral("btnBack"));

        verticalLayout->addWidget(btnBack, 0, Qt::AlignHCenter);

        DifficultyWindow->setCentralWidget(centralWidget);

        retranslateUi(DifficultyWindow);

        QMetaObject::connectSlotsByName(DifficultyWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DifficultyWindow)
    {
        DifficultyWindow->setWindowTitle(QApplication::translate("DifficultyWindow", "DifficultyWindow", nullptr));
        btnStart->setText(QApplication::translate("DifficultyWindow", "Jouez !", nullptr));
        btnEasy->setText(QApplication::translate("DifficultyWindow", "Facile", nullptr));
        btnMedium->setText(QApplication::translate("DifficultyWindow", "Moyen", nullptr));
        btnDifficult->setText(QApplication::translate("DifficultyWindow", "Difficile", nullptr));
        btnBack->setText(QApplication::translate("DifficultyWindow", "Retour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DifficultyWindow: public Ui_DifficultyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFICULTYWINDOW_H
