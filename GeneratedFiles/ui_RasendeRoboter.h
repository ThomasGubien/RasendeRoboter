/********************************************************************************
** Form generated from reading UI file 'RasendeRoboter.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RASENDEROBOTER_H
#define UI_RASENDEROBOTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RasendeRoboterClass
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QGraphicsView *graphicsView;
    QWidget *lay;
    QPushButton *startButton;
    QLabel *goalLabel;
    QPushButton *solutionButton;
    QLCDNumber *nbCoups;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;
    QRadioButton *redRadioButton;
    QRadioButton *blueRadioButton;
    QRadioButton *greenRadioButton;
    QRadioButton *yellowRadioButton;
    QPushButton *cancelButton;
    QPushButton *rightButton;
    QPushButton *leftButton;
    QPushButton *upButton;
    QPushButton *downButton;
    QLabel *label_3;
    QLCDNumber *nbCoups_2;
    QPushButton *annonceNbDpl;
    QLCDNumber *nbCoupsEstim;
    QLabel *label_estimation;

    void setupUi(QMainWindow *RasendeRoboterClass)
    {
        if (RasendeRoboterClass->objectName().isEmpty())
            RasendeRoboterClass->setObjectName(QStringLiteral("RasendeRoboterClass"));
        RasendeRoboterClass->resize(1299, 901);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RasendeRoboterClass->sizePolicy().hasHeightForWidth());
        RasendeRoboterClass->setSizePolicy(sizePolicy);
        RasendeRoboterClass->setFocusPolicy(Qt::NoFocus);
        RasendeRoboterClass->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(RasendeRoboterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 900, 900));
        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 900, 900));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        lay = new QWidget(widget);
        lay->setObjectName(QStringLiteral("lay"));
        lay->setGeometry(QRect(0, 0, 900, 900));
        lay->setStyleSheet(QStringLiteral(""));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(1050, 20, 91, 23));
        goalLabel = new QLabel(centralWidget);
        goalLabel->setObjectName(QStringLiteral("goalLabel"));
        goalLabel->setGeometry(QRect(1020, 60, 151, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(goalLabel->sizePolicy().hasHeightForWidth());
        goalLabel->setSizePolicy(sizePolicy1);
        goalLabel->setMinimumSize(QSize(47, 13));
        solutionButton = new QPushButton(centralWidget);
        solutionButton->setObjectName(QStringLiteral("solutionButton"));
        solutionButton->setGeometry(QRect(1050, 180, 111, 23));
        nbCoups = new QLCDNumber(centralWidget);
        nbCoups->setObjectName(QStringLiteral("nbCoups"));
        nbCoups->setGeometry(QRect(1120, 140, 64, 23));
        nbCoups->setStyleSheet(QStringLiteral("QLCDNumber{background-color:black;}"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1010, 140, 111, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(950, 340, 271, 16));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-11, -1, 1311, 911));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(143, 143, 143);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        redRadioButton = new QRadioButton(frame);
        redRadioButton->setObjectName(QStringLiteral("redRadioButton"));
        redRadioButton->setGeometry(QRect(1000, 380, 100, 40));
        blueRadioButton = new QRadioButton(frame);
        blueRadioButton->setObjectName(QStringLiteral("blueRadioButton"));
        blueRadioButton->setGeometry(QRect(1000, 440, 100, 40));
        greenRadioButton = new QRadioButton(frame);
        greenRadioButton->setObjectName(QStringLiteral("greenRadioButton"));
        greenRadioButton->setGeometry(QRect(1130, 440, 100, 40));
        yellowRadioButton = new QRadioButton(frame);
        yellowRadioButton->setObjectName(QStringLiteral("yellowRadioButton"));
        yellowRadioButton->setGeometry(QRect(1130, 380, 100, 40));
        cancelButton = new QPushButton(frame);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(1079, 639, 75, 75));
        cancelButton->setCursor(QCursor(Qt::PointingHandCursor));
        cancelButton->setFlat(true);
        rightButton = new QPushButton(frame);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        rightButton->setGeometry(QRect(1160, 630, 75, 75));
        rightButton->setCursor(QCursor(Qt::PointingHandCursor));
        rightButton->setAutoDefault(false);
        rightButton->setFlat(true);
        leftButton = new QPushButton(frame);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        leftButton->setGeometry(QRect(1000, 630, 75, 75));
        leftButton->setCursor(QCursor(Qt::PointingHandCursor));
        leftButton->setFlat(true);
        upButton = new QPushButton(frame);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(1080, 550, 75, 75));
        upButton->setCursor(QCursor(Qt::PointingHandCursor));
        upButton->setFocusPolicy(Qt::NoFocus);
        upButton->setStyleSheet(QStringLiteral(""));
        upButton->setAutoDefault(false);
        upButton->setFlat(true);
        downButton = new QPushButton(frame);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(1080, 710, 75, 75));
        downButton->setCursor(QCursor(Qt::PointingHandCursor));
        downButton->setFlat(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(990, 110, 125, 21));
        nbCoups_2 = new QLCDNumber(centralWidget);
        nbCoups_2->setObjectName(QStringLiteral("nbCoups_2"));
        nbCoups_2->setGeometry(QRect(1120, 110, 64, 23));
        nbCoups_2->setStyleSheet(QStringLiteral("QLCDNumber{background-color:black;}"));
        annonceNbDpl = new QPushButton(centralWidget);
        annonceNbDpl->setObjectName(QStringLiteral("annonceNbDpl"));
        annonceNbDpl->setGeometry(QRect(1050, 210, 111, 23));
        nbCoupsEstim = new QLCDNumber(centralWidget);
        nbCoupsEstim->setObjectName(QStringLiteral("nbCoupsEstim"));
        nbCoupsEstim->setGeometry(QRect(1120, 240, 64, 23));
        nbCoupsEstim->setStyleSheet(QStringLiteral("QLCDNumber{background-color:black;}"));
        label_estimation = new QLabel(centralWidget);
        label_estimation->setObjectName(QStringLiteral("label_estimation"));
        label_estimation->setGeometry(QRect(1060, 240, 111, 21));
        RasendeRoboterClass->setCentralWidget(centralWidget);
        frame->raise();
        startButton->raise();
        goalLabel->raise();
        solutionButton->raise();
        nbCoups->raise();
        label->raise();
        widget->raise();
        label_2->raise();
        label_3->raise();
        nbCoups_2->raise();
        annonceNbDpl->raise();
        nbCoupsEstim->raise();
        label_estimation->raise();

        retranslateUi(RasendeRoboterClass);

        upButton->setDefault(false);


        QMetaObject::connectSlotsByName(RasendeRoboterClass);
    } // setupUi

    void retranslateUi(QMainWindow *RasendeRoboterClass)
    {
        RasendeRoboterClass->setWindowTitle(QApplication::translate("RasendeRoboterClass", "RasendeRoboter", nullptr));
        startButton->setText(QApplication::translate("RasendeRoboterClass", "Nouvelle Partie", nullptr));
        goalLabel->setText(QApplication::translate("RasendeRoboterClass", "But: ", nullptr));
        solutionButton->setText(QApplication::translate("RasendeRoboterClass", "Afficher Solution", nullptr));
        label->setText(QApplication::translate("RasendeRoboterClass", "Nombres de coups IA:", nullptr));
        label_2->setText(QApplication::translate("RasendeRoboterClass", "Choix du robot a d\303\251placer :", nullptr));
        redRadioButton->setText(QString());
        blueRadioButton->setText(QString());
        greenRadioButton->setText(QString());
        yellowRadioButton->setText(QString());
        cancelButton->setText(QString());
        rightButton->setText(QString());
        leftButton->setText(QString());
        upButton->setText(QString());
        downButton->setText(QString());
        label_3->setText(QApplication::translate("RasendeRoboterClass", "Nombres de coups joueur:", nullptr));
        annonceNbDpl->setText(QApplication::translate("RasendeRoboterClass", "Faire une estimation", nullptr));
        label_estimation->setText(QApplication::translate("RasendeRoboterClass", "Estimation :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RasendeRoboterClass: public Ui_RasendeRoboterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RASENDEROBOTER_H
