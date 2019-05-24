#include "DifficultyWindow.h"

DifficultyWindow::DifficultyWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Create signals and slots for buttons
	connect(ui.btnEasy, SIGNAL(clicked()), this, SLOT(setDifficultyToEasy()));
	connect(ui.btnMedium, SIGNAL(clicked()), this, SLOT(setDifficultyToMedium()));
	connect(ui.btnDifficult, SIGNAL(clicked()), this, SLOT(setDifficultyToDifficult()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(startGame()));
	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(returnToStartWindow()));
}

DifficultyWindow::~DifficultyWindow()
{
}

void DifficultyWindow::setRasen(RasendeRoboterController * rasen)
{
	mRasen = rasen;
}
/*
void DifficultyWindow::setIAControler(IAController * iaController)
{
	mIAController = iaController;
}*/

void DifficultyWindow::setStartWindow(StartWindow * startWindow)
{
	mStartWindow = startWindow;
}

//Apply Easy difficulty to the IAController
void DifficultyWindow::setDifficultyToEasy() {
	mRasen->setDifficulty(3);
	//mIAController->setDifficulty(EASY);
}

//Apply Medium difficulty to the IAController
void DifficultyWindow::setDifficultyToMedium()
{
	mRasen->setDifficulty(2);
	//mIAController->setDifficulty(MEDIUM);
}

//Apply Difficult difficulty to the IAController
void DifficultyWindow::setDifficultyToDifficult()
{
	mRasen->setDifficulty(1);
	//mIAController->setDifficulty(DIFFICULT);
}

//Launch the game
void DifficultyWindow::startGame() {
	mRasen->show();
	this->close();
}

//Back to the start window
void DifficultyWindow::returnToStartWindow() {
	mStartWindow->show();
	this->close();
}
