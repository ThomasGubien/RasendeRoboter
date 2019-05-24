#pragma once

#include <QMainWindow>
#include <QPushButton>
#include "ui_difficultyWindow.h"
#include "RasendeRoboterController.h"
#include "IAController.h"
#include "StartWindow.h"
class StartWindow;

class DifficultyWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::DifficultyWindow ui;
	int mDifficulty;

	RasendeRoboterController* mRasen;
	//IAController* mIAController;
	StartWindow* mStartWindow;
	
	enum Difficulties {
		EASY = 1,
		MEDIUM = 2,
		DIFFICULT = 3
	};

public:
	DifficultyWindow(QWidget *parent = Q_NULLPTR);
	~DifficultyWindow();
	
	void setRasen(RasendeRoboterController* rasen);
	//void setIAControler(IAController* iaController);
	void setStartWindow(StartWindow* startWindow);

public slots:
	void startGame();
	void setDifficultyToEasy();
	void setDifficultyToMedium();
	void setDifficultyToDifficult();
	void returnToStartWindow();

};
