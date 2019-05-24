#pragma once

#include <QtCore/QVariant>

class Move {
private:
	int activeRobot;					// Qui bouge
	bool otherRobotsUsed[4];			// Robots qui ont �t� utilis�s pour ce move ou d'autres ant�rieurs
	std::vector<int> goal;				// Case � atteindre
	std::vector<Move> auxiliaryMoves;	// Moves d'autres robots pour atteindre goal
	char origin;						// Direction d'o� vient le move ('n', 's', 'e', 'w')

public:
	Move();
	Move(int activeRobot, std::vector<int> goal, char origin);
	Move(int activeRobot, std::vector<int> goal, char origin, bool* otherRobotsUsed);
	Move(int activeRobot, std::vector<int> goal, char origin, bool* otherRobotsUsed, std::vector<Move> auxiliaryMoves);
	~Move();

	int getActiveRobot();
	bool* getOtherRobotsUsed();
	bool isUsed(int robot);
	void setUsed(int robot);

	std::vector<int> getGoal();

	void addAuxiliaryMove(Move newMove);
	std::vector<Move> getAuxiliaryMoves();
	int getNbAuxiliaryMoves();

	bool fromNorth();
	bool fromSouth();
	bool fromEast();
	bool fromWest();
	char getOrigin();

	std::vector<int> getPrevAuxiliaryRobot();
};