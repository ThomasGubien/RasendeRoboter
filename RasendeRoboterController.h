#pragma once

#include <iostream>
#include <qinputdialog.h>
#include "ui_RasendeRoboter.h"
#include "InitPoint.h"
#include "IAController.h"

class RasendeRoboterController : public QMainWindow
{
	Q_OBJECT

private:
	Ui::RasendeRoboterClass ui;

	std::vector<InitPoint> init;
	std::vector<std::vector<Case*>*> cases; // Vecteur à 2 dimensions contenant les cases du plateau
	std::vector<std::vector<int>> goals;    // Vecteur à 2 dimentions contenant les coordonnées des goals
	std::vector<Move> sol;

	int robotPos[4][2];						// Coord du robot à bouger (1 pour rouge / 2 pour bleu / 3 pour jaune / 4 pour vert)
	int prevRobotPos[20][3];				// Ancienne position du robot (pour ctrl-z)
	int cancelPos;							// Position dans prevRobotPos
	int nbDeplacement;						// Nombre de déplacements réalisés
	int robotSelect = 0;					// Robot selection
	int coord[2];
	int difficulty = 3;
	int annonce = 0;						// nbDpl estime par le joueur
	bool partieEnCours = 0;					// 1 = une partie est en cours / 0 = pas de partie en cours

	/*QTimer *timer;						// Pour le timer
	int temps;*/

	IAController* ia;
public:
	RasendeRoboterController(QWidget *parent = Q_NULLPTR);
	

	void moveRobot(char dir);					// Bouge le currentRobot dans une direction donnée (char = 'n', 's', 'e' ou 'w')
	int isStartPosition(int i, int j);
	bool isAtGoal(int i, int j);				// Check si le robot est sur la case d'arrivée

	void initWalls();
	void initGoal();
	void connecters();

	int checkMancheEnCours();
	void RasendeRoboterController::moveRobot();	// deplace les robots selon la solution de l'IA
	void uncheckRadio();						// deselectionne les radioButton
	void resetPos();

	void setDifficulty(int d) { difficulty = d; }

	std::vector<std::vector<Case*>*> getCases(); // TODO Renvoyer une copie ? Peut-être un peu lourd ? Je sais paaaaaas x)


public slots:
	void upHandler();
	void downHandler();
	void leftHandler();
	void rightHandler();
	void cancelHandler();
	void startHandler();
	void redRadioHandler();
	void blueRadioHandler();
	void yellowRadioHandler();
	void greenRadioHandler();
	void solutionHandler();
	void annonceHandler();
};
