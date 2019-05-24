#include "StartWindow.h"

StartWindow::StartWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
	mDiffWin = new DifficultyWindow();
	//Create signals and slots for buttons
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(startGame()));
	connect(ui.btnDifficulty, SIGNAL(clicked()), this, SLOT(changeToDifficultyWindow()));
	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(quitApplication()));

	//Set background image
	//QPixmap bkgnd("Resources/background.jpg");
	//bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	//QPalette palette;
	//palette.setBrush(QPalette::Background, bkgnd);
	//this->setPalette(palette);
}

StartWindow::~StartWindow()
{
}

void StartWindow::startGame() {
	mDiffWin;
	mRasen->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
	mRasen->show();
	this->close();
}

//Switch to difficulty selection window
void StartWindow::changeToDifficultyWindow() {
	mDiffWin->setStartWindow(this);
	//mDiffWin->setIAControler(mIAController);
	mDiffWin->setRasen(mRasen);
	mDiffWin->show();
	this->close();
}

void StartWindow::quitApplication() {
	this->close();
}
/*
void StartWindow::setIAControler(IAController* iaControler)
{
	mIAController = iaControler;
}
*/
void StartWindow::setRasen(RasendeRoboterController *rasen)
{
	mRasen = rasen;
}
