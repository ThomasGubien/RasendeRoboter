#include "RasendeRoboterController.h"
#include <QtWidgets/QApplication>
#include <qmessagebox.h>
#include <time.h>

RasendeRoboterController::RasendeRoboterController(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label_estimation->setVisible(0);
	ui.nbCoupsEstim->setVisible(0);

	// On cree la scene graphique dans laquelle on dessinera tout le jeu.
	QGraphicsScene* scene = new QGraphicsScene;

	// On définie le Layout au format grille qui représentera notre plateau dans le code (un widget par case)
	QGridLayout* layout = new QGridLayout;

	// On crée l'élément graphique qui affichera le plateau
	QPixmap plateau;
	plateau.load("Resources/Plateau.png");												// Chargement de l'image
	plateau = plateau.scaled(ui.graphicsView->width(), ui.graphicsView->height());		// Redimmentionnement de l'image
	scene->addPixmap(plateau);															// On ajoute l'image du plateau a la fenetre graphique 
	
	initWalls();

	int nw, sw, ew, ww;

	// Pour chaque ligne du tableau
	for (int i = 0; i < 16; i++) {

		// On crée la ligne
		cases.push_back(new std::vector<Case*>);

		// Pour chaque colone du tableau
		for (int j = 0; j < 16; j++) {

			nw = i == 0;			// if(i == 0){ nw = 1; } else{ nw = 0; }
			sw = i == 15;
			ew = j == 15;
			ww = j == 0;
			
			// Si on se trouve en (1,4) ou (5,1) ou (15,14) ou (8,10) sur la grille
			if (isStartPosition(i, j) != 0)
				cases[i]->push_back(new Case(isStartPosition(i, j), nw, sw, ew, ww));									// On crée une case avec un robot dessu
			// Sinon
			else
				cases[i]->push_back(new Case(0, nw, sw, ew, ww));												// On crée une case vide

			// On definie la position et la taille de la case (fonction du widget)
			cases.at(i)->at(j)->setGeometry(0, 0, ui.graphicsView->width() / 16, ui.graphicsView->height() / 16);	// On met le widget en position (0,0) sur la grille (organisation automatique en
																												// fonction de la ligne et de la colonne grace au GridLayout). La largeur et la hauteur
																												// du widget est la taille de la fenetre graphique divisé par le nombre de cases
			// Si la case a un robot
			///if (cases.at(i)->at(j)->getRobot()) {
				///cases.at(i)->at(j)->setStyleSheet("image: url(Resources/robot.png);");								// On applique une image de robot sur le widget
			///}

			switch (cases.at(i)->at(j)->getRobot()) {
			case 1: cases.at(i)->at(j)->setStyleSheet("image: url(Resources/Robot_Red.png);");
				// On ajoute la position du robot à robotPos;
				robotPos[0][0] = i;
				robotPos[0][1] = j;
				break;
			case 2: cases.at(i)->at(j)->setStyleSheet("image: url(Resources/Robot_Blue.png);");
				// On ajoute la position du robot à robotPos;
				robotPos[1][0] = i;
				robotPos[1][1] = j;
				break;
			case 3: cases.at(i)->at(j)->setStyleSheet("image: url(Resources/Robot_Yellow.png);");
				// On ajoute la position du robot à robotPos;
				robotPos[2][0] = i;
				robotPos[2][1] = j;
				break;
			case 4: cases.at(i)->at(j)->setStyleSheet("image: url(Resources/Robot_Green.png);");
				// On ajoute la position du robot à robotPos;
				robotPos[3][0] = i;
				robotPos[3][1] = j;
				break;
			default:
				break;
			}

			if (i == 7 && j == 7) {
				cases.at(i)->at(j)->setStyleSheet("image: url(Resources/RC1.png);");
			}
			if (i == 7 && j == 8) {
				cases.at(i)->at(j)->setStyleSheet("image: url(Resources/RC2.png);");
			}
			if (i == 8 && j == 8) {
				cases.at(i)->at(j)->setStyleSheet("image: url(Resources/RC3.png);");
			}
			if (i == 8 && j == 7) {
				cases.at(i)->at(j)->setStyleSheet("image: url(Resources/RC4.png);");
			}

			// On ajoute le widget au layout
			layout->addWidget(cases.at(i)->at(j), i, j);
		}
	}

	for (auto elem : init) {
		if (elem.n)
			cases.at(elem.i)->at(elem.j)->setNorthWall(1);
		if (elem.s)
			cases.at(elem.i)->at(elem.j)->setSouthWall(1);
		if (elem.e)
			cases.at(elem.i)->at(elem.j)->setEastWall(1);
		if (elem.w)
			cases.at(elem.i)->at(elem.j)->setWestWall(1);
	}

	// Modifie l'apparence des boutons de déplacement
	ui.upButton->setStyleSheet("background-image: url(Resources/upArrow.png)");
	ui.downButton->setStyleSheet("background-image: url(Resources/downArrow.png)");
	ui.leftButton->setStyleSheet("background-image: url(Resources/leftArrow.png)");
	ui.rightButton->setStyleSheet("background-image: url(Resources/rightArrow.png)");
	ui.cancelButton->setStyleSheet("background-image: url(Resources/cancel.png)");

	connecters();
	ia = new IAController(&cases, difficulty);

	// On associe le layout du code avec celui de la fenetre du jeu défini dans RasendeRoboter.ui
	ui.lay->setLayout(layout);

	// On associe la scene graphique du code avec celle de la fenetre du jeu défini dans RasendeRoboter.ui
	ui.graphicsView->setScene(scene);

	// TEMPORAIRE
	/*robotPos[0] = 5;
	robotPos[1] = 12;

	cancelPos = 0;
	*/

	// Initialisation des goals
	initGoal();

	ui.redRadioButton->setStyleSheet("image: url(Resources/Robot_Red.png);");
	ui.blueRadioButton->setStyleSheet("image: url(Resources/Robot_Blue.png);");
	ui.yellowRadioButton->setStyleSheet("image: url(Resources/Robot_Yellow.png);");
	ui.greenRadioButton->setStyleSheet("image: url(Resources/Robot_Green.png);");
}

void RasendeRoboterController::moveRobot(char dir) {
	QMessageBox msg;
	if (robotSelect != 0 && annonce != 0)
	{
		// Save l'ancienne case
		prevRobotPos[cancelPos][0] = robotPos[robotSelect - 1][0];
		prevRobotPos[cancelPos][1] = robotPos[robotSelect - 1][1];
		prevRobotPos[cancelPos][2] = robotSelect;
		cancelPos++;

		// Vire le robot de l'ancienne case
		cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("");
		cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setRobot(0);

		// Cherche la nouvelle case
		switch (dir) {
		case 'n':
			while (!cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->hasNorthWall() && !cases.at(robotPos[robotSelect - 1][0] - 1)->at(robotPos[robotSelect - 1][1])->getRobot()) {
				robotPos[robotSelect - 1][0]--;
			}
			break;

		case 's':
			while (!cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->hasSouthWall() && !cases.at(robotPos[robotSelect - 1][0] + 1)->at(robotPos[robotSelect - 1][1])->getRobot()) {
				robotPos[robotSelect - 1][0]++;
			}
			break;

		case 'w':
			while (!cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->hasWestWall() && !cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1] - 1)->getRobot()) {
				robotPos[robotSelect - 1][1]--;
			}
			break;

		case 'e':
			while (!cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->hasEastWall() && !cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1] + 1)->getRobot()) {
				robotPos[robotSelect - 1][1]++;
			}
			break;
		}

		// Pose le robot sur la nouvelle case
		switch (robotSelect)
		{
		case 1:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Red.png);");
			break;
		case 2:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Blue.png);");
			break;
		case 3:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Yellow.png);");
			break;
		case 4:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Green.png);");
			break;
		}
		cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setRobot(1);
		nbDeplacement++;
		ui.nbCoups_2->display(static_cast<int>(nbDeplacement));

		if (isAtGoal(robotPos[robotSelect - 1][0], robotPos[robotSelect - 1][1])  &&
			(cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->getGoalColor() == robotSelect ||
				cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->getGoalColor() == 5))				// case multicolore
		{
			if (nbDeplacement < static_cast<int>(sol.size()) && nbDeplacement == annonce)
			{
				cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setGoalActiv(0);

				msg.setText("----------- Victoire !!! -----------");
				msg.exec();
			}
			else {
				if (nbDeplacement != static_cast<int>(sol.size()))
				{
					msg.setText("----------- Perdu -----------");
					msg.exec();
				}
				else {
					msg.setText("----------- Egalite -----------");
					msg.exec();
				}
			}
		}
		
	}
	else {
		msg.warning(NULL, "", "Veuillez selectionner un robot ou faire une annonce");
	}
}

void RasendeRoboterController::upHandler() {
	 moveRobot('n');
}

void RasendeRoboterController::downHandler() {
	moveRobot('s');
}

void RasendeRoboterController::leftHandler() {
	moveRobot('w');
}

void RasendeRoboterController::rightHandler() {
	moveRobot('e');
}

void RasendeRoboterController::cancelHandler() {
	if (robotSelect != 0 && annonce != 0) {
		// Vérif s'il y a des action à annuler
		if (cancelPos > 0) {
			cancelPos--;


			robotSelect = prevRobotPos[cancelPos][2];
			// Vire le robot de la case actuelle
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("");
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setRobot(0);

			// Met à jour la pos du robot

			robotPos[robotSelect - 1][0] = prevRobotPos[cancelPos][0];
			robotPos[robotSelect - 1][1] = prevRobotPos[cancelPos][1];

			// Pose le robot sur la nouvelle case
			switch (robotSelect)
			{
			case 1:
				cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Red.png);");
				break;
			case 2:
				cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Blue.png);");
				break;
			case 3:
				cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Yellow.png);");
				break;
			case 4:
				cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Green.png);");
				break;
			}
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setRobot(1);

			uncheckRadio();
			nbDeplacement--;
			ui.nbCoups_2->display(static_cast<int>(nbDeplacement));
		// Tu étais trop jeune pour nous quitter. Ceci sera à jamais ton mémorial
		/*	
			
                                 _____  _____
                                <     `/     |
                                 >          (
                                |   _     _  |
                                |  |_) | |_) |
                                |  | \ | |   |
                                |            |
                 ______.______%_|            |__________  _____
               _/                                       \|     |
              |					  DIFFICULTY                   <
              |_____.-._________              ____/|___________|
                                | * 06/12/18 |
                                | + 06/12/18 |
                                |            |
                                |            |
                                |   _        <
                                |__/         |
                                 / `--.      |
                               %|            |%
                           |/.%%|          -< @%%%
                           `\%`@|     v      |@@%@%%    
                         .%%%@@@|%    |    % @@@%%@%%%%
                    _.%%%%%%@@@@@@%%_/%\_%@@%%@@@@@@@%%%%%%
		*/
		/*switch (difficulty)
		{
		case 1:
		nbDeplacement++;
		break;
		case 3:
		nbDeplacement--;
		break;
		}*/

		}
	}
}

void RasendeRoboterController::startHandler() {
	srand(time(NULL));
	int activeRobot;
	annonce = 0;
	
	if (checkMancheEnCours() >= 0)
	{
		resetPos();
		partieEnCours = 1;
		/*threadTimer.start(chrono::milliseconds(1000), [] {
		cout << "Hello!" << endl;
		});

		this_thread::sleep_for(chrono::seconds(2));
		threadTimer.stop();*/

		// =========================TEST==================================
		// on test si il reste des goals jamais atteind
		if (goals.size() > 0) {
			nbDeplacement = 0;
			// Selection d'un goal de manière aléatoire
			int irand = rand() % goals.size();
			std::string s = "But : x->";
			s.append(std::to_string(goals[irand][1]));
			s.append(" / y->");
			s.append(std::to_string(goals[irand][0]));
			s.append("\nCouleur du robot : ");

			// Définit le goal en temps que goal actif
			cases.at(goals[irand][0])->at(goals[irand][1])->setGoalActiv(1);

			// Entoure le goal pour etre facilement visualisable
			switch (cases.at(goals[irand][0])->at(goals[irand][1])->getGoalColor())
			{
			case 1:
				cases.at(goals[irand][0])->at(goals[irand][1])->setStyleSheet("border: 3px solid red; border-radius: 10px;");


				s.append("rouge");

				// On définit le robot à déplacer
				cancelPos = 0;
				activeRobot = 1;

				break;
			case 2:
				cases.at(goals[irand][0])->at(goals[irand][1])->setStyleSheet("border: 3px solid blue; border-radius: 10px;");


				s.append("bleu");

				
				cancelPos = 0;
				activeRobot = 2;

				break;
			case 3:
				cases.at(goals[irand][0])->at(goals[irand][1])->setStyleSheet("border: 3px solid yellow; border-radius: 10px;");

				s.append("jaune");

				cancelPos = 0;
				activeRobot = 3;

				break;
			case 4:
				cases.at(goals[irand][0])->at(goals[irand][1])->setStyleSheet("border: 3px solid green; border-radius: 10px;");

				s.append("vert");

				cancelPos = 0;
				activeRobot = 4;

				break;
			case 5:
				cases.at(goals[irand][0])->at(goals[irand][1])->setStyleSheet("border: 3px solid black; border-radius: 10px;");

				s.append("toutes les couleurs");

				cancelPos = 0;
				activeRobot = 0;

				break;
			}
			ui.goalLabel->setText(s.c_str());

			coord[0] = goals[irand][0];
			coord[1] = goals[irand][1];
			sol = ia->getSolution(coord, activeRobot);
			ui.nbCoups->display(static_cast<int>(sol.size()));

			//solutionHandler();

			// Supprime le goal de la liste pour ne plus être accessible durant cette partie
			goals.erase(goals.begin() + irand);

		}
		else {
			partieEnCours = 0;
		}
	}
	
	
	// =================================================================
}

void RasendeRoboterController::resetPos() {
	for (int i = 0; i < 4; i++)
	{
		cases.at(robotPos[i][0])->at(robotPos[i][1])->setRobot(0);
		cases.at(robotPos[i][0])->at(robotPos[i][1])->setStyleSheet("");
	}

	cases.at(0)->at(0)->setRobot(1);
	cases.at(0)->at(0)->setStyleSheet("image: url(Resources/Robot_Red.png);");
	robotPos[0][0] = 0;
	robotPos[0][1] = 0;

	cases.at(2)->at(1)->setRobot(2);
	cases.at(2)->at(1)->setStyleSheet("image: url(Resources/Robot_Blue.png);");
	robotPos[1][0] = 2;
	robotPos[1][1] = 1;


	cases.at(4)->at(7)->setRobot(3);
	cases.at(4)->at(7)->setStyleSheet("image: url(Resources/Robot_Yellow.png);");
	robotPos[2][0] = 4;
	robotPos[2][1] = 7;

	cases.at(5)->at(12)->setRobot(4);
	cases.at(5)->at(12)->setStyleSheet("image: url(Resources/Robot_Green.png);");
	robotPos[3][0] = 5;
	robotPos[3][1] = 12;
}

int RasendeRoboterController::checkMancheEnCours() {
	for (int i = 0; i < 16; i++) {

		// On crée la ligne
		cases.push_back(new std::vector<Case*>);

		// Pour chaque colone du tableau
		for (int j = 0; j < 16; j++) {
			if (cases.at(i)->at(j)->isGoalActiv())
			{
				QMessageBox::StandardButton reply;
				reply = QMessageBox::question(this, "Manche en cours", "Une manche est en cours, en continuant maintenant, la manche sera perdue. Continuer ?",
					QMessageBox::Yes | QMessageBox::No);
				if (reply == QMessageBox::Yes) {
					cases.at(i)->at(j)->setGoalActiv(0);
					cases.at(i)->at(j)->setStyleSheet("");
					return 1;
				}
				else {
					return -1;
				}
			}
		}
	}
	return 0;
}

void RasendeRoboterController::solutionHandler() {
	if (checkMancheEnCours() >= 0) {
		QMessageBox msg;
		msg.setText("----------- Perdu -----------");
		msg.exec();
	}

	std::string s2 = "Goal : ";
	s2.append(std::to_string(coord[0]));
	s2.append("-");
	s2.append(std::to_string(coord[1]));
	s2.append("\n");
	s2.append("nbStarts : ");
	s2.append(std::to_string(sol.size()));
	s2.append("\n");
	for (int i = 0; i < sol.size(); i++) {
		s2.append(std::to_string(sol.at(i).getActiveRobot()));
		s2.append(": ");
		s2.append(std::to_string(sol.at(i).getGoal().at(0)));
		s2.append("-");
		s2.append(std::to_string(sol.at(i).getGoal().at(1)));
		s2.append("\n");
	}

	QMessageBox msg;
	msg.setText(s2.c_str());
	msg.exec();

	moveRobot();
	
}

void RasendeRoboterController::redRadioHandler() {
	if (partieEnCours) {
		robotSelect = 1;
	}
	else {
		QMessageBox msg;
		uncheckRadio();
		msg.warning(NULL, "", "Veuillez demarrer une partie avant de selectionner un robot");
	}
}

void RasendeRoboterController::blueRadioHandler() {
	if (partieEnCours) {
		robotSelect = 2;
	}
	else {
		QMessageBox msg;
		uncheckRadio();
		msg.warning(NULL, "", "Veuillez demarrer une partie avant de selectionner un robot");
	}
}

void RasendeRoboterController::yellowRadioHandler() {
	if (partieEnCours) {
		robotSelect = 3;
	}
	else {
		QMessageBox msg;
		uncheckRadio();
		msg.warning(NULL, "", "Veuillez demarrer une partie avant de selectionner un robot");
	}
}

void RasendeRoboterController::greenRadioHandler() {
	if (partieEnCours) {
		robotSelect = 4;
	}
	else {
		QMessageBox msg;
		uncheckRadio();
		msg.warning(NULL, "", "Veuillez demarrer une partie avant de selectionner un robot");
	}

}

void RasendeRoboterController::annonceHandler() {
	if (partieEnCours) {
		if (annonce != 0)
		{
			int modif = QInputDialog::getText(this, "Annonce", "Combien de coup prend votre solution ?").toInt();
			if (annonce > modif)
				annonce = modif;
			else {
				QMessageBox msg;
				msg.warning(NULL, "Annoce trop grande", "Vous ne pouvez pas entrer une annonce superieure à l'annonce initiale.");
			}
		}
		else {
			annonce = QInputDialog::getText(this, "Annonce", "Combien de coup prend votre solution ?").toInt();

			ui.label_estimation->setVisible(1);
			ui.nbCoupsEstim->setVisible(1);
			ui.nbCoupsEstim->display(annonce);
		}
	}
	else {
		QMessageBox msg;
		msg.warning(NULL, "", "Aucune partie en cours");
	}
}

void RasendeRoboterController::moveRobot() {
	for (int i = 0; i < sol.size(); i++) {
		robotSelect = sol[i].getActiveRobot();
		cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("");
		cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setRobot(0);

		robotPos[robotSelect - 1][0] = sol[i].getGoal()[0];
		robotPos[robotSelect - 1][1] = sol[i].getGoal()[1];

		switch (robotSelect)
		{
		case 1:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Red.png);");
			break;
		case 2:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Blue.png);");
			break;
		case 3:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Yellow.png);");
			break;
		case 4:
			cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setStyleSheet("image: url(Resources/Robot_Green.png);");
			break;
		}
		_sleep(500);
	}

	cases.at(robotPos[robotSelect - 1][0])->at(robotPos[robotSelect - 1][1])->setGoalActiv(0);
}

std::vector<std::vector<Case*>*> RasendeRoboterController::getCases() {
	return cases; 
}


int RasendeRoboterController::isStartPosition(int i, int j) {
	///if ((i == 0 && j == 0) || (i == 2 && j == 1) || (i == 4 && j == 7) || (i == 5 && j == 12))
		///return 1;
	///return 0;
	if (i == 0 && j == 0)
		return 1;
	else if (i == 2 && j == 1)
		return 2;
	else if (i == 4 && j == 7)
		return 3;
	else if (i == 5 && j == 12)
		return 4;
	return 0;
}


void RasendeRoboterController::initWalls() {

	init.push_back(InitPoint(0, 3, 0, 0, 1, 0));		//i, j, north, south, east, west.
	init.push_back(InitPoint(0, 4, 0, 0, 0, 1));
	init.push_back(InitPoint(0, 9, 0, 0, 1, 0));
	init.push_back(InitPoint(0, 10, 0, 0, 0, 1));

	init.push_back(InitPoint(1, 13, 0, 1, 1, 0));
	init.push_back(InitPoint(1, 14, 0, 0, 0, 1));
	init.push_back(InitPoint(1, 15, 0, 1, 0, 0));

	init.push_back(InitPoint(2, 5, 0, 1, 1, 0));
	init.push_back(InitPoint(2, 6, 0, 0, 0, 1));
	init.push_back(InitPoint(2, 9, 0, 1, 0, 0));
	init.push_back(InitPoint(2, 13, 1, 0, 0, 0));
	init.push_back(InitPoint(2, 15, 1, 0, 0, 0));

	init.push_back(InitPoint(3, 2, 0, 1, 0, 0));
	init.push_back(InitPoint(3, 5, 1, 0, 0, 0));
	init.push_back(InitPoint(3, 8, 0, 0, 1, 0));
	init.push_back(InitPoint(3, 9, 1, 0, 0, 1));
	init.push_back(InitPoint(3, 14, 0, 1, 0, 0));

	init.push_back(InitPoint(4, 0, 0, 1, 0, 0));
	init.push_back(InitPoint(4, 2, 1, 0, 1, 0));
	init.push_back(InitPoint(4, 3, 0, 0, 0, 1));
	init.push_back(InitPoint(4, 14, 1, 0, 1, 0));

	init.push_back(InitPoint(5, 0, 1, 0, 0, 0));
	init.push_back(InitPoint(5, 1, 0, 1, 0, 0));
	init.push_back(InitPoint(5, 6, 0, 0, 1, 0));
	init.push_back(InitPoint(5, 7, 0, 1, 0, 1));

	init.push_back(InitPoint(6, 0, 0, 0, 1, 0));
	init.push_back(InitPoint(6, 1, 1, 0, 0, 1));
	init.push_back(InitPoint(6, 7, 1, 1, 0, 0));
	init.push_back(InitPoint(6, 8, 0, 1, 0, 0));
	init.push_back(InitPoint(6, 11, 0, 0, 1, 0));
	init.push_back(InitPoint(6, 12, 0, 1, 0, 1));

	init.push_back(InitPoint(7, 6, 0, 0, 1, 0));
	init.push_back(InitPoint(7, 7, 1, 1, 1, 1));
	init.push_back(InitPoint(7, 8, 1, 1, 1, 1));
	init.push_back(InitPoint(7, 9, 0, 0, 0, 1));
	init.push_back(InitPoint(7, 12, 1, 0, 0, 0));

	init.push_back(InitPoint(8, 6, 0, 0, 1, 0));
	init.push_back(InitPoint(8, 7, 1, 1, 1, 1));
	init.push_back(InitPoint(8, 8, 1, 1, 1, 1));
	init.push_back(InitPoint(8, 9, 0, 0, 0, 1));

	init.push_back(InitPoint(9, 3, 0, 0, 1, 0));
	init.push_back(InitPoint(9, 4, 0, 1, 0, 1));
	init.push_back(InitPoint(9, 6, 0, 1, 0, 0));
	init.push_back(InitPoint(9, 7, 1, 0, 0, 0));
	init.push_back(InitPoint(9, 8, 1, 0, 0, 0));
	init.push_back(InitPoint(9, 12, 0, 0, 1, 0));
	init.push_back(InitPoint(9, 13, 0, 1, 0, 1));

	init.push_back(InitPoint(10, 0, 0, 1, 0, 0));
	init.push_back(InitPoint(10, 4, 1, 0, 0, 0));
	init.push_back(InitPoint(10, 5, 0, 0, 1, 0));
	init.push_back(InitPoint(10, 6, 1, 0, 0, 1));
	init.push_back(InitPoint(10, 13, 1, 0, 0, 0));

	init.push_back(InitPoint(11, 0, 1, 0, 0, 0));
	init.push_back(InitPoint(11, 7, 0, 1, 0, 0));
	init.push_back(InitPoint(11, 9, 0, 1, 1, 0));
	init.push_back(InitPoint(11, 10, 0, 0, 0, 1));
	init.push_back(InitPoint(11, 15, 0, 1, 0, 0));

	init.push_back(InitPoint(12, 1, 0, 1, 0, 0));
	init.push_back(InitPoint(12, 7, 1, 0, 1, 0));
	init.push_back(InitPoint(12, 8, 0, 0, 0, 1));
	init.push_back(InitPoint(12, 9, 1, 0, 0, 0));
	init.push_back(InitPoint(12, 14, 0, 1, 0, 0));
	init.push_back(InitPoint(12, 15, 1, 0, 0, 0));

	init.push_back(InitPoint(13, 1, 1, 0, 1, 0));
	init.push_back(InitPoint(13, 2, 0, 0, 0, 1));
	init.push_back(InitPoint(13, 10, 0, 1, 0, 0));
	init.push_back(InitPoint(13, 14, 1, 0, 1, 0));

	init.push_back(InitPoint(14, 3, 0, 1, 1, 0));
	init.push_back(InitPoint(14, 4, 0, 0, 0, 1));
	init.push_back(InitPoint(14, 9, 0, 0, 1, 0));
	init.push_back(InitPoint(14, 10, 1, 0, 0, 1));

	init.push_back(InitPoint(15, 3, 1, 0, 0, 0));
	init.push_back(InitPoint(15, 4, 0, 0, 1, 0));
	init.push_back(InitPoint(15, 5, 0, 0, 0, 1));
	init.push_back(InitPoint(15, 11, 0, 0, 1, 0));
	init.push_back(InitPoint(15, 12, 0, 0, 0, 1));
}

/// Initialise les goals pour la partie en cours 
void RasendeRoboterController::initGoal() {
	
	//Goal de couleur bleu
	cases.at(2)->at(5)->setGoal(1);
	cases.at(2)->at(5)->setGoalColor(2);
	goals.push_back(std::vector<int>(2));
	goals[0][0] = 2;
	goals[0][1] = 5;

	cases.at(3)->at(9)->setGoal(1);
	cases.at(3)->at(9)->setGoalColor(2);
	goals.push_back(std::vector<int>(2));
	goals[1][0] = 3;
	goals[1][1] = 9;

	cases.at(9)->at(13)->setGoal(1);
	cases.at(9)->at(13)->setGoalColor(2);
	goals.push_back(std::vector<int>(2));
	goals[2][0] = 9;
	goals[2][1] = 13;

	cases.at(10)->at(6)->setGoal(1);
	cases.at(10)->at(6)->setGoalColor(2);
	goals.push_back(std::vector<int>(2));
	goals[3][0] = 10;
	goals[3][1] = 6;

	//Goal de couleur vert
	cases.at(1)->at(13)->setGoal(1);
	cases.at(1)->at(13)->setGoalColor(4);
	goals.push_back(std::vector<int>(2));
	goals[4][0] = 1;
	goals[4][1] = 13;

	cases.at(4)->at(2)->setGoal(1);
	cases.at(4)->at(2)->setGoalColor(4);
	goals.push_back(std::vector<int>(2));
	goals[5][0] = 4;
	goals[5][1] = 2;

	cases.at(14)->at(3)->setGoal(1);
	cases.at(14)->at(3)->setGoalColor(4);
	goals.push_back(std::vector<int>(2));
	goals[6][0] = 14;
	goals[6][1] = 3;

	cases.at(14)->at(10)->setGoal(1);
	cases.at(14)->at(10)->setGoalColor(4);
	goals.push_back(std::vector<int>(2));
	goals[7][0] = 14;
	goals[7][1] = 10;

	//Goal de couleur rouge
	cases.at(4)->at(14)->setGoal(1);
	cases.at(4)->at(14)->setGoalColor(1);
	goals.push_back(std::vector<int>(2));
	goals[8][0] = 4;
	goals[8][1] = 14;

	cases.at(5)->at(7)->setGoal(1);
	cases.at(5)->at(7)->setGoalColor(1);
	goals.push_back(std::vector<int>(2));
	goals[9][0] = 5;
	goals[9][1] = 7;

	cases.at(13)->at(1)->setGoal(1);
	cases.at(13)->at(1)->setGoalColor(1);
	goals.push_back(std::vector<int>(2));
	goals[10][0] = 13;
	goals[10][1] = 1;

	cases.at(13)->at(14)->setGoal(1);
	cases.at(13)->at(14)->setGoalColor(1);
	goals.push_back(std::vector<int>(2));
	goals[11][0] = 13;
	goals[11][1] = 14;

	//Goal de couleur jaune
	cases.at(6)->at(1)->setGoal(1);
	cases.at(6)->at(1)->setGoalColor(3);
	goals.push_back(std::vector<int>(2));
	goals[12][0] = 6;
	goals[12][1] = 1;

	cases.at(6)->at(12)->setGoal(1);
	cases.at(6)->at(12)->setGoalColor(3);
	goals.push_back(std::vector<int>(2));
	goals[13][0] = 6;
	goals[13][1] = 12;

	cases.at(9)->at(4)->setGoal(1);
	cases.at(9)->at(4)->setGoalColor(3);
	goals.push_back(std::vector<int>(2));
	goals[14][0] = 9;
	goals[14][1] = 4;

	cases.at(11)->at(9)->setGoal(1);
	cases.at(11)->at(9)->setGoalColor(3);
	goals.push_back(std::vector<int>(2));
	goals[15][0] = 11;
	goals[15][1] = 9;

	//Goal multicolor
	cases.at(12)->at(7)->setGoal(1);
	cases.at(12)->at(7)->setGoalColor(5);
	goals.push_back(std::vector<int>(2));
	goals[16][0] = 12;
	goals[16][1] = 7;
}

bool RasendeRoboterController::isAtGoal(int i, int j) {
	if (cases.at(i)->at(j)->isGoalActiv())
	{
		return 1;
	}
	return 0;
}

void RasendeRoboterController::uncheckRadio() {
	ui.redRadioButton->setAutoExclusive(false);
	ui.redRadioButton->setChecked(0);
	ui.redRadioButton->setAutoExclusive(true);

	ui.blueRadioButton->setAutoExclusive(false);
	ui.blueRadioButton->setChecked(0);
	ui.blueRadioButton->setAutoExclusive(true);

	ui.yellowRadioButton->setAutoExclusive(false);
	ui.yellowRadioButton->setChecked(0);
	ui.yellowRadioButton->setAutoExclusive(true);

	ui.greenRadioButton->setAutoExclusive(false);
	ui.greenRadioButton->setChecked(0);
	ui.greenRadioButton->setAutoExclusive(true);
}


void RasendeRoboterController::connecters() {

	connect(ui.upButton, SIGNAL(clicked()), this, SLOT(upHandler()));
	connect(ui.downButton, SIGNAL(clicked()), this, SLOT(downHandler()));
	connect(ui.leftButton, SIGNAL(clicked()), this, SLOT(leftHandler()));
	connect(ui.rightButton, SIGNAL(clicked()), this, SLOT(rightHandler()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(cancelHandler()));
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(startHandler()));
	connect(ui.solutionButton, SIGNAL(clicked()), this, SLOT(solutionHandler()));
	connect(ui.redRadioButton, SIGNAL(clicked()), this, SLOT(redRadioHandler()));
	connect(ui.blueRadioButton, SIGNAL(clicked()), this, SLOT(blueRadioHandler()));
	connect(ui.yellowRadioButton, SIGNAL(clicked()), this, SLOT(yellowRadioHandler()));
	connect(ui.greenRadioButton, SIGNAL(clicked()), this, SLOT(greenRadioHandler()));
	connect(ui.annonceNbDpl, SIGNAL(clicked()), this, SLOT(annonceHandler()));

}