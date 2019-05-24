#pragma once

#include "Move.h"
//#include "RasendeRoboterController.h"
#include "Tree.h"
#include "Case.h"

class IAController {
private:
	//RasendeRoboterController* rrc;	// Lien vers le RasendeRoboterController pour les infos map, etc
	std::vector<std::vector<Case*>*>* casestbl;
	int diffic;						// Difficulté de l'IA

	// choisi une solution parmis toutes celles trouvées en fonction de la difficulté
	int choseSolution(std::vector<std::vector<Move>> solutions);

	// Recherche des plus courts chemins -> coeur de l'algo
	std::vector<std::vector<Move>> shortestPaths(Move firstMove, int nbSolWanted, bool auxiliary);
	std::vector<Move> buildSolution(Tree start);

	// Recherche des départs possibles pour une case
	std::vector<Move> searchStarts(Move previousMove, bool auxiliary);
	std::vector<Move> yStarts(Move previousMove, bool goSouth, bool auxiliary);		// cherche sur axe y
	std::vector<Move> xStarts(Move previousMove, bool goEast, bool auxiliary);		// cherche sur axe x
	std::vector<Move> createStart(std::vector<int> goal, Move previousMove, bool vertical);
	std::vector<std::vector<int>> canBeStart(std::vector<int> goal, Move previousMove, bool vertical);
	bool startable(Case* toTest, std::vector<int> coordCase, Move previousMove);
	
	// Check si un robot doit être considéré comme un mur sur une case adjacente
	bool robotBlock(std::vector<int> currentCase, int moveY, int moveX, int activeRobot, std::vector<int> auxiliaryRobot);

	// Filtre les cases qui ont déjà été parcourues
	std::vector<Move> unchecked(std::vector<Move> toCheck, Tree* tree);

	// Cherche si des cases trouvées contiennent le bon robot (null si aucune)
	std::vector<int> haveRobot(std::vector<Move> toCheck, int activeRobot);

public:
	//IAController(RasendeRoboterController* rrc);
	IAController(std::vector<std::vector<Case*>*>* cases, int diff);
	~IAController();

	// Fonction à appeler pour recevoir une solution -> choisi une soluton parmis toutes celle trouvées
	std::vector<Move> getSolution(int* goal, int robot);

	// Set la difficulté de l'IA
	void setDiffic(int newDiffic);
};