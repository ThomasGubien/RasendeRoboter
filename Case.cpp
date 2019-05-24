#include "Case.h"


//Constructeur par d�faut
Case::Case()
{
	QWidget::QWidget();
	robot = 0;
	wall_N = 0;
	wall_S = 0;
	wall_E = 0;
	wall_W = 0;
	goal = 0;
	goalActiv = 0;
	goalColor = 0;
}

//Constructeur surcharg�
Case::Case(int r, bool n, bool s, bool e, bool w) {
	robot = r;
	wall_N = n;
	wall_S = s;
	wall_E = e;
	wall_W = w;
	goal = 0;
	goalActiv = 0;
	goalColor = 0;
}

//Destructeur par d�faut
Case::~Case() {
}

bool Case::hasWall() {
	return wall_N || wall_S || wall_E || wall_W;
}