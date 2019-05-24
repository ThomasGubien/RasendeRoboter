#pragma once

#include <QMainWindow>
#include <QPushButton>
#include "ui_StartWindow.h"
#include "RasendeRoboterController.h"
#include "IAController.h"
#include "DifficultyWindow.h"
#include <qmessagebox.h>
class DifficultyWindow;

class StartWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::StartWindow ui;
	RasendeRoboterController *mRasen;
	//IAController *mIAController;
	DifficultyWindow *mDiffWin;

public:
	StartWindow(QWidget *parent = Q_NULLPTR);
	~StartWindow();

	void setRasen(RasendeRoboterController* rasen);
	//void setIAControler(IAController* iaController);


public slots:
	void startGame();
	void changeToDifficultyWindow();
	void quitApplication();

};
