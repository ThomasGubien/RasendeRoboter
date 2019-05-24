#include "Move.h"

Move::Move() {
	for (int i = 0; i < 4; i++) {
		otherRobotsUsed[i] = false;
	}
}

Move::Move(int activeRobot, std::vector<int> goal, char origin) {
	this->activeRobot = activeRobot;
	this->goal = goal;
	for (int i = 0; i < 4; i++) {
		otherRobotsUsed[i] = (i == activeRobot - 1);
	}
	this->origin = origin;
}

Move::Move(int activeRobot, std::vector<int> goal, char origin, bool* otherRobotsUsed) {
	this->activeRobot = activeRobot;
	this->goal = goal;
	for (int i = 0; i < 4; i++) {
		this->otherRobotsUsed[i] = (i == activeRobot - 1) || otherRobotsUsed[i];
	}
	this->origin = origin;
}

Move::Move(int activeRobot, std::vector<int> goal, char origin, bool* otherRobotsUsed, std::vector<Move> auxiliaryMoves) {
	this->activeRobot = activeRobot;
	this->goal = goal;
	bool* auxiliaryUsedRobots = auxiliaryMoves.at(0).getOtherRobotsUsed();
	for (int i = 0; i < 4; i++) {
		this->otherRobotsUsed[i] = (i == activeRobot - 1) || otherRobotsUsed[i] || auxiliaryUsedRobots[i];
	}
	this->auxiliaryMoves = auxiliaryMoves;
	this->origin = origin;
}

Move::~Move() {
}

int Move::getActiveRobot() {
	return activeRobot;
}

bool* Move::getOtherRobotsUsed() {
	return otherRobotsUsed;
}

bool Move::isUsed(int robot) {
	return otherRobotsUsed[robot - 1];
}

void Move::setUsed(int robot) {
	otherRobotsUsed[robot - 1] = true;
}

std::vector<int> Move::getGoal() {
	return goal;
}

void Move::addAuxiliaryMove(Move newMove) {
	auxiliaryMoves.push_back(newMove);
}

std::vector<Move> Move::getAuxiliaryMoves() {
	return auxiliaryMoves;
}

int Move::getNbAuxiliaryMoves() {
	return auxiliaryMoves.size();
}

bool Move::fromNorth() {
	return origin == 'n';
}

bool Move::fromSouth() {
	return origin == 's';
}

bool Move::fromEast() {
	return origin == 'e';
}

bool Move::fromWest() {
	return origin == 'w';
}

char Move::getOrigin() {
	return origin;
}

std::vector<int> Move::getPrevAuxiliaryRobot() {
	std::vector<int> coord;
	if (auxiliaryMoves.size() == 0) {
		coord.push_back(-1);
		coord.push_back(-1);
		return coord;
	} // else

	return auxiliaryMoves.at(auxiliaryMoves.size() - 1).getGoal();
}