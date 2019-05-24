#include "Tree.h"

Tree::Tree(Move move, int nbMoves) {
	this->move = move;
	this->nbMoves = nbMoves;
}

Tree::~Tree() {
}

Move Tree::getMove() {
	return move;
}

void Tree::addNext(Tree* next) {
	for (int i = 0; i < 4; i++) {
		if (next->move.isUsed(i-1) || this->move.isUsed(i-1)) {
			next->move.setUsed(i-1);
		}
	}

	nexts.push_back(next);
	next->previous = this;
}

std::vector<Tree*> Tree::getNexts() {
	return nexts;
}

void Tree::setPrevious(Tree* previous) {
	this->previous = previous;
}

Tree* Tree::getPrevious() {
	return previous;
}

int Tree::getNbMoves() {
	return nbMoves;
}

std::vector<Move> Tree::notInTree(std::vector<Move> toSearch) {
	// cherche sur ce noeud
	for (int i = 0; i < toSearch.size(); i++) {
		std::vector<int> thisCase = move.getGoal();
		Move moveToSearch = toSearch.at(i);
		if (moveToSearch.getGoal().at(0) == thisCase.at(0) && moveToSearch.getGoal().at(1) == thisCase.at(1)) {
			toSearch.erase(toSearch.begin() + i);
		}
	}

	// sert à rien de continuer si plus rien à chercher
	if (toSearch.size() == 0) {
		return toSearch;
	} // else

	// cherche dans les nexts
	for (int i = 0; i < nexts.size(); i++) {
		toSearch = nexts.at(i)->notInTree(toSearch);
	}

	return toSearch;
}