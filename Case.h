#pragma once

#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include <vector>

class Case : public QWidget
{
private:
	int robot;
	bool wall_N;
	bool wall_S;
	bool wall_E;
	bool wall_W;
	bool goal;										// Définie la case en temps que goal si = 1
	bool goalActiv;									// Si = 1, la case est la case à atteindre
	int goalColor;									// 1 = rouge / 2 = bleu / 3 = jaune / 4 = vert / 5 = multicolore / 0 si goal != 1

public:
	Case();
	Case(int r, bool n, bool s, bool e, bool w);
	~Case();

	int getRobot() { return robot; }				// return le numéro du robot présent sur la case (-1 si aucun robot)
	bool hasNorthWall() { return wall_N; }			// La case a un mur au nord
	bool hasSouthWall() { return wall_S; }			// La case a un mur au sud
	bool hasEastWall() { return wall_E; }			// La case a un mur a l'est
	bool hasWestWall() { return wall_W; }			// La case a un mur a l'ouest
	bool hasWall();									// La case a un mur
	bool isGoal() { return goal; }					// La case est un goal si = 1 
	bool isGoalActiv() { return goalActiv; }		// La case est le goal actif si = 1
	int getGoalColor() { return goalColor; }		// return la couleur du goal

	void setRobot(int r) { robot = r; }			// Set robot à r
	void setNorthWall(bool n) { wall_N = n; }		// Set wall_N à n
	void setSouthWall(bool s) { wall_S = s; }		// Set wall_S à s
	void setEastWall(bool e) { wall_E = e; }		// Set wall_E à e
	void setWestWall(bool w) { wall_W = w; }		// Set wall_W à w
	void setGoal(bool g) { goal = g; }				// Set goal à g
	void setGoalActiv(bool gA) { goalActiv = gA; }	// Set goalActiv à gA
	void setGoalColor(int c) { goalColor = c; }		// Set goalColor à c

};