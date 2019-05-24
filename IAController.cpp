#include "IAController.h"
#include <list>
#include <time.h>
#include <algorithm>

/** 
 * Constructeur de l'IA
 * @param rrc le controller contenant les infos map, etc...
 */
/*IAController::IAController(RasendeRoboterController* rrc) {
	this->rrc = rrc;
	diffic = 0;
}*/
IAController::IAController(std::vector<std::vector<Case*>*>* cases, int diff) {
	casestbl = cases;
	diffic = diff;
}
/** Destructeur par défaut */
IAController::~IAController() {}

/**
 * Trouve une solution pour amener un robot donné sur une case donnée
 * (Solution choisie en fonction de la difficulté)
 * @param goal les coordonnées de la case d'arrivée
 * @param robot le robot à déplacer
 * @return un vecteur de coordonnées de cases formant le trajet
 */
std::vector<Move> IAController::getSolution(int* goal, int robot) {
	std::vector<int> theGoal;
	theGoal.push_back(goal[0]);
	theGoal.push_back(goal[1]);

	std::vector<std::vector<Move>> solutions;
	std::vector<std::vector<Move>> tmpSol;

	if (robot == 0) {
		for (int i = 1; i <= 4; i++) {
			tmpSol = shortestPaths(Move(i, theGoal, ' '), 5, false);
			solutions.insert(solutions.begin(), tmpSol.begin(), tmpSol.end());
		}
	} else {
		solutions = shortestPaths(Move(robot, theGoal, ' '), 10, false);
	}
	std::sort(solutions.begin(), solutions.end(), [](std::vector<Move> a, std::vector<Move> b) {return a.size() < b.size(); });

	return solutions.at(choseSolution(solutions));
}

int IAController::choseSolution(std::vector<std::vector<Move>> solutions) {
	std::vector<int> coeffs;
	int nbSol = solutions.size();
	int chosenSol;
	
	srand(time(NULL));

	switch (diffic) {
	case 1:		// DIFFICILE (plus de chance de prendre la meilleur sol)
		coeffs.push_back(100 * nbSol);
		for (int i = 1; i < nbSol; i++) {
			coeffs.push_back(coeffs.at(i - 1) + (100 * nbSol) / i);
		}
		break;
		
	case 2:		// NORMAL	(chances équivalente)
		for (int i = 1; i < nbSol; i++) {
			coeffs.push_back(coeffs.at(i - 1) + 1);
		}
		break;

	case 3:		// FACILE	(plus de chace de prendre la moins bonne solution)
		coeffs.push_back(100 / nbSol);
		for (int i = 1; i < nbSol; i++) {
			coeffs.push_back(coeffs.at(i - 1) + (100 * i) / nbSol);
		}
		break;

	default:	// INSANE	(prend la meilleur solution)
		coeffs.push_back(1);
	}

	int irand = rand() % coeffs.at(nbSol - 1);
	for (chosenSol = 0; chosenSol <= nbSol && irand > coeffs[chosenSol]; chosenSol++);

	return chosenSol;
}

/** Set la difficulté de l'IA */
void IAController::setDiffic(int newDiffic) {
	diffic = newDiffic;
}

/**
 * Cherche un certains nombre de plus courts chemins pour arriver au goal
 * @param firstMove le premier move de la soluton (donc le dernier coup effectué)
 * @param nbSolWanted le nombre de solutions à trouver
 * @return un vecteur contenant toutes les solutions (donc des vecteurs de coordonnées de cases)
 */
std::vector<std::vector<Move>> IAController::shortestPaths(Move firstMove, int nbSolWanted, bool auxiliary) {
	std::vector<int> goal = firstMove.getGoal();
	int activeRobot = firstMove.getActiveRobot();

	std::vector<std::vector<Move>> solutions;

	Tree finalGoal(firstMove, 0);		// premier noeud de l'arbre

	std::list<Tree*> nextToProcess;		// prochains noeuds à traiter (permet parcours de l'arbre)
	nextToProcess.push_front(&finalGoal);

	int nbSolFound = 0;
	Tree *currentTree;					// noeud en cours de traitement
	Tree *newTree;
	std::vector<Move> starts;
	std::vector<int> startRobots;		// départ contenant le robot actif

	// continue à chercher tant que pas assez de solutions
	while (nbSolFound < nbSolWanted && nextToProcess.size() > 0) {
		currentTree = nextToProcess.front();
		starts = searchStarts(currentTree->getMove(), auxiliary);
		starts = unchecked(starts, &finalGoal);

		// check les solutions valides et les enlève de starts si nbMoves > 1
		startRobots = haveRobot(starts, activeRobot);
		for (int i = 0; i < startRobots.size(); i++) {
			// point départ solution
			Move moveSolution = starts.at(startRobots.at(i));
			int nbMoves = currentTree->getNbMoves() + moveSolution.getNbAuxiliaryMoves() + 1;
			if (nbMoves > 1) {
				Tree startSolution(moveSolution, nbMoves);
				startSolution.setPrevious(currentTree);

				// construction / save solution
				solutions.push_back(buildSolution(startSolution));
				nbSolFound++;
			}
			// enlève solution de starts
			starts.erase(starts.begin() + startRobots.at(i));
		}

		// ajoute les nouveaux chemins à l'arbre
		for (int i = 0; i < starts.size(); i++) {
			int nbMoves = currentTree->getNbMoves() + starts.at(i).getNbAuxiliaryMoves() + 1;
			newTree = new Tree(starts.at(i), nbMoves);
			currentTree->addNext(newTree);
			nextToProcess.push_back(newTree);
		}

		nextToProcess.pop_front();
		nextToProcess.sort([](Tree* a, Tree* b) {return a->getNbMoves() < b->getNbMoves(); });
	}

	return solutions;
}

std::vector<Move> IAController::buildSolution(Tree start) {
	std::vector<Move> newSol;
	//std::vector<Move> auxiliarySol;
	Tree *currentTree = start.getPrevious();
	Move currentMove;
	std::vector<Move> auxiliaryMoves;

	while (currentTree->getNbMoves() > 0) {
		currentMove = currentTree->getMove();
		auxiliaryMoves = currentMove.getAuxiliaryMoves();
		for (int i = 0; i < currentMove.getNbAuxiliaryMoves(); i++) {
			//auxiliarySol.push_back(auxiliaryMoves.at(i));
			newSol.push_back(auxiliaryMoves.at(i));
		}
		newSol.push_back(currentMove);
		currentTree = currentTree->getPrevious();
	}
	newSol.push_back(currentTree->getMove());
	//newSol.insert(newSol.begin(), auxiliarySol.begin(), auxiliarySol.end());

	return newSol;
}

/**
 * Cherche tous les départs possibles pour une case donnée
 * @param previousMove le move précédant effectuer (sera le suivant dans la solution finale)
 * @return un vecteur contenant toutes les coordonnées des cases "départ" (stockées dans des Move)
 */
std::vector<Move> IAController::searchStarts(Move previousMove, bool auxiliary) {
	std::vector<int> goal = previousMove.getGoal();
	int activeRobot = previousMove.getActiveRobot();
	std::vector<int> auxiliaryRobot = previousMove.getPrevAuxiliaryRobot();

	std::vector<Move> nsStarts;		// north/south starts
	std::vector<Move> weStarts;		// west/east starts

	Case *goalCase = casestbl->at(goal[0])->at(goal[1]);

	bool north = !previousMove.fromNorth() && (goalCase->hasNorthWall() || robotBlock(goal, -1, 0, activeRobot, auxiliaryRobot));
	bool south = !previousMove.fromSouth() && (goalCase->hasSouthWall() || robotBlock(goal, 1, 0, activeRobot, auxiliaryRobot));
	bool east = !previousMove.fromEast() && (goalCase->hasEastWall() || robotBlock(goal, 0, 1, activeRobot, auxiliaryRobot));
	bool west = !previousMove.fromWest() && (goalCase->hasWestWall() || robotBlock(goal, 0, -1, activeRobot, auxiliaryRobot));

	// check si mur Nord XOR Sud
	if ((north && !south) || (!north && south)) {
		nsStarts = yStarts(previousMove, north, auxiliary);
	}

	// check si mur Ouest XOR Est
	if ((west && !east) || (east && !west)) {
		weStarts = xStarts(previousMove, west, auxiliary);
	}

	// concat les 2 vecteurs et return le résultat
	nsStarts.insert(nsStarts.end(), weStarts.begin(), weStarts.end());
	return nsStarts;

}

/**
 * Cherche les départs en provenance de l'axe Y pour une case donnée
 * @param previousMove le move précédant effectuer (sera le suivant dans la solution finale)
 * @param goSouth la direction dans laquelle chercher (true = south, false = north)
 */
std::vector<Move> IAController::yStarts(Move previousMove, bool goSouth, bool auxiliary) {
	std::vector<int> goal = previousMove.getGoal();
	int activeRobot = previousMove.getActiveRobot();
	std::vector<int> auxiliaryRobot = previousMove.getPrevAuxiliaryRobot();

	Case *currentCase;				// case en cours d'exploration
	std::vector<int> coordCurrentCase;

	char origin = goSouth ? 'n' : 's';
	int move = goSouth ? 1 : -1;	// sens du mouvement de recherche
	int posY = goal[0];				// pos en Y de currentCase

	std::vector<Move> foundStarts;	// liste des départs trouvés
	std::vector<Move> auxiliaryMoves;
	bool* usedRobots;

	bool blockedWest,
		 blockedEast,
		 activeRobotFound;

	// tant que peut avancer ou que pas trouvé activeRobot
	do {
		// next case
		posY += move;
		currentCase = casestbl->at(posY)->at(goal[1]);

		// maj coordonnées currentCase
		coordCurrentCase.clear();
		coordCurrentCase.push_back(posY);
		coordCurrentCase.push_back(goal[1]);

		// check si currentCase contien activeRobot
		activeRobotFound = currentCase->getRobot() == activeRobot;

		// check si mur ou robot sur un côté (pas les 2 sinon on peut pas y accéder)
		blockedWest = currentCase->hasWestWall() || robotBlock(coordCurrentCase, 0, -1, activeRobot, auxiliaryRobot);
		blockedEast = currentCase->hasEastWall() || robotBlock(coordCurrentCase, 0, 1, activeRobot, auxiliaryRobot);

		// si bloquée que d'un seul côté ou contient robot actif
		if (activeRobotFound || (blockedWest && !blockedEast) || (!blockedWest && blockedEast)) {
			foundStarts.push_back(Move(activeRobot, coordCurrentCase, origin, previousMove.getOtherRobotsUsed()));
		
		// si bloquée aucun côté et contient pas robot actif ET pas déjà un chemin auxiliaire
		} else if (!blockedWest && !blockedEast && !auxiliary) {
			auxiliaryMoves = createStart(coordCurrentCase, previousMove, false);
			if (auxiliaryMoves.size() > 0) {
				usedRobots = auxiliaryMoves.at(0).getOtherRobotsUsed();
				foundStarts.push_back(Move(activeRobot, coordCurrentCase, origin, usedRobots, auxiliaryMoves));
			}
		}
	} while (!activeRobotFound && !currentCase->hasNorthWall() && !currentCase->hasSouthWall() && !robotBlock(coordCurrentCase, move, 0, activeRobot, auxiliaryRobot));

	return foundStarts;
}

/**
 * Cherche les départs en provenance de l'axe X pour une case donnée
 * @param previousMove le move précédant effectué (sera le suivant dans la solution finale)
 * @param goEast la direction dans laquelle chercher (true = east, false = west)
 */
std::vector<Move> IAController::xStarts(Move previousMove, bool goEast, bool auxiliary) {
	std::vector<int> goal = previousMove.getGoal();
	int activeRobot = previousMove.getActiveRobot();
	std::vector<int> auxiliaryRobot = previousMove.getPrevAuxiliaryRobot();

	Case *currentCase;				// case en cours d'exploration
	std::vector<int> coordCurrentCase;

	char origin = goEast ? 'w' : 'e';
	int move = goEast ? 1 : -1;		// sens du mouvement de recherche
	int posX = goal[1];				// pos en Y de currentCase

	std::vector<Move> foundStarts;	// liste des départs trouvés
	std::vector<Move> auxiliaryMoves;
	bool* usedRobots;

	bool blockedNorth,
		 blockedSouth,
		 activeRobotFound;

	// tant que peut avancer ou que pas trouvé activeRobot
	do {
		// next case
		posX += move;
		currentCase = casestbl->at(goal[0])->at(posX);
		
		// maj coordonnées currentCase
		coordCurrentCase.clear();
		coordCurrentCase.push_back(goal[0]);
		coordCurrentCase.push_back(posX);

		// check si currentCase contien activeRobot
		activeRobotFound = currentCase->getRobot() == activeRobot;

		// check si mur ou robot sur un côté (pas les 2 sinon on peut pas y accéder)
		blockedNorth = currentCase->hasNorthWall() || robotBlock(coordCurrentCase, -1, 0, activeRobot, auxiliaryRobot);
		blockedSouth = currentCase->hasSouthWall() || robotBlock(coordCurrentCase, 1, 0, activeRobot, auxiliaryRobot);

		// si bloquée que d'un seul côté ou contient robot actif
		if (activeRobotFound || (blockedNorth && !blockedSouth) || (!blockedNorth && blockedSouth)) {
			foundStarts.push_back(Move(activeRobot, coordCurrentCase, origin, previousMove.getOtherRobotsUsed()));

		// si bloquée aucun côté et contient pas robot actif ET pas déjà un chemin auxiliaire
		} else if (!blockedNorth && !blockedSouth && !auxiliary) {
			auxiliaryMoves = createStart(coordCurrentCase, previousMove, true);
			if (auxiliaryMoves.size() > 0) {
				foundStarts.push_back(Move(activeRobot, coordCurrentCase, origin, previousMove.getOtherRobotsUsed(), auxiliaryMoves));
			}
		}
	} while (!activeRobotFound && !currentCase->hasEastWall() && !currentCase->hasWestWall() && !robotBlock(coordCurrentCase, 0, move, activeRobot, auxiliaryRobot));

	return foundStarts;
}

/**
 * Crée un départ pour une case en bougeant un robot non actif qui n'a pas déjà bougé
 * @param goal la case pour laquelle créer un départ
 * @param previousMove le move précédant effectué (sera le suivant dans la solution finale)
 * @return une liste de move pour créer un départ à la case (vide si impossible)
 */
std::vector<Move> IAController::createStart(std::vector<int> goal, Move previousMove, bool verticalSearch) {
	std::vector<Move> auxiliaryMoves;

	bool* unmovableRobots = previousMove.getOtherRobotsUsed();
	std::vector<std::vector<int>> startableCases = canBeStart(goal, previousMove, verticalSearch);

	std::vector<std::vector<Move>> foundPaths;
	bool betterSolution; 
	int amSize;			// auxiliaryMoves size

	// pour chaque robot bougeable
	for (int robot = 0; robot < 4; robot++) {
		if (!unmovableRobots[robot]) {
			// pour chaque case startable
			for (int i = 0; i < startableCases.size(); i++) {
				Move firstMove(robot + 1, startableCases.at(i), ' ', previousMove.getOtherRobotsUsed());
				foundPaths = shortestPaths(firstMove, 1, true);
				amSize = auxiliaryMoves.size();
				betterSolution = foundPaths.size() > 0 && (amSize == 0 || foundPaths.at(0).size() < amSize);
				auxiliaryMoves = betterSolution ? foundPaths.at(0) : auxiliaryMoves;
			}
		}
	}

	return auxiliaryMoves;
}


std::vector<std::vector<int>> IAController::canBeStart(std::vector<int> goal, Move previousMove, bool verticalSearch) {
	/* TODO
	 * cherche case autour qui peuvent etre start
	 * remonte arbre pour check si bloque pas un previous move ?
	 */
	std::vector<std::vector<int>> startableCases;
	std::vector<int> caseBefore;	// case à gauche ou en haut
	std::vector<int> caseAfter;		// case à droite ou en bas
	Case* goalCase;
	int activeRobot = previousMove.getActiveRobot();

	int toNorth = (verticalSearch && goal.at(0) > 0) ? -1 : 0;
	int toSouth = (verticalSearch && goal.at(0) < 15) ? 1 : 0;
	int toEast = (!verticalSearch && goal.at(1) > 0) ? 1 : 0;
	int toWest = (!verticalSearch && goal.at(1) < 15) ? -1 : 0;

	// case à droite ou en bas
	if (toSouth != 0 || toEast != 0) {
		caseAfter.push_back(goal.at(0) + toSouth);
		caseAfter.push_back(goal.at(1) + toEast);
		goalCase = casestbl->at(caseAfter.at(0))->at(caseAfter.at(1));
		
		if (startable(goalCase, caseAfter, previousMove)) {
			startableCases.push_back(caseAfter);
		}
	}

	// case à gauche ou en haut
	if (toNorth != 0 || toWest != 0) {
		caseBefore.push_back(goal.at(0) + toNorth);
		caseBefore.push_back(goal.at(1) + toWest);
		goalCase = casestbl->at(caseBefore.at(0))->at(caseBefore.at(1));

		if (startable(goalCase, caseBefore, previousMove)) {
			startableCases.push_back(caseBefore);
		}
	}

	return startableCases;
}

bool IAController::startable(Case* toTest, std::vector<int> coordCase, Move previousMove) {
	int activeRobot = previousMove.getActiveRobot();
	std::vector<int> auxiliaryRobot = previousMove.getPrevAuxiliaryRobot();

	bool northBlocked = !previousMove.fromNorth() && (toTest->hasNorthWall() || robotBlock(coordCase, -1, 0, activeRobot, auxiliaryRobot));
	bool southBlocked = !previousMove.fromSouth() && (toTest->hasSouthWall() || robotBlock(coordCase, 1, 0, activeRobot, auxiliaryRobot));
	bool eastBlocked = !previousMove.fromEast() && (toTest->hasEastWall() || robotBlock(coordCase, 0, 1, activeRobot, auxiliaryRobot));
	bool westBlocked = !previousMove.fromWest() && (toTest->hasWestWall() || robotBlock(coordCase, 0, -1, activeRobot, auxiliaryRobot));

	return (northBlocked && !southBlocked) || (!northBlocked && southBlocked) || (eastBlocked && !westBlocked) || (!eastBlocked && westBlocked);
}

/**
 * Check si un robot doit être considéré comme un mur sur une case adjacente à une case donnée
 * @param currentCase la case de référence
 * @param moveY direction dans laquelle chercher en Y (1 = south, -1 = north, 0 = bouge pas)
 * @param moveX direction dans laquelle chercher en X (1 = east, -1 = west, 0 = bouge pas)
 * @param activeRobot le robot qui bouge
 * @param auxiliaryRobot coordonnées du robot auxiliaire utilisé au move précédent (-1, -1 si aucun)
 * @return true si la case adjacente contient un robot non actif, false sinon
 */
bool IAController::robotBlock(std::vector<int> currentCase, int moveY, int moveX, int activeRobot, std::vector<int> auxiliaryRobot) {
	int x = currentCase.at(1) + moveX;
	int y = currentCase.at(0) + moveY;
	int robot = casestbl->at(y)->at(x)->getRobot();
	return (robot != 0 && robot != activeRobot) || (auxiliaryRobot.at(0) == y && auxiliaryRobot.at(1) == x);
}

/**
 * Filtre les cases qui ont déjà été parcourues
 * @param toCheck le vecteur des cases à filtrer
 * @return un vecteur ne contenant que des cases non parcourues
 */
std::vector<Move> IAController::unchecked(std::vector<Move> toCheck, Tree* tree) {
	return tree->notInTree(toCheck);
}

/**
 * Cherche si des cases trouvées contiennent le bon robot 
 * @param toCheck le vecteur des cases à filtrer
 * @return un vecteur des positions dans toCheck des cases contenant le bon robot
 */
std::vector<int> IAController::haveRobot(std::vector<Move> toCheck, int activeRobot) {
	std::vector<int> withActiveRobot;
	std::vector<int> goalInCheck;
	Case *caseInCheck;

	for (int i = toCheck.size() - 1; i >= 0 ; i--) {
		goalInCheck = toCheck.at(i).getGoal();
		caseInCheck = casestbl->at(goalInCheck.at(0))->at(goalInCheck.at(1));
		if (caseInCheck->getRobot() == activeRobot) {
			withActiveRobot.push_back(i);
		}
	}

	return withActiveRobot;
}