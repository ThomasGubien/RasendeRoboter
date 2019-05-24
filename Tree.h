#pragma once

#include <QtCore/QVariant>
#include "Move.h"

class Tree {
private:
	Move move;
	std::vector<Tree*> nexts;
	Tree *previous;

	int nbMoves;

public:
	Tree(Move move, int nbMoves);
	~Tree();

	Move getMove();

	void addNext(Tree* next);
	std::vector<Tree*> getNexts();

	void setPrevious(Tree* previous);
	Tree* getPrevious();

	int getNbMoves();

	std::vector<Move> notInTree(std::vector<Move> toSearch);
};