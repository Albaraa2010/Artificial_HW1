#ifndef h_PuzzleTree
#define h_PuzzleTree

#include <iostream>
#include <fstream>
#include <vector>

#include "WriggleWorm.h"

using namespace std;

struct PuzzleNode {
	WormMove* parentMove;
	vector<vector<char>> gameGrid;
	vector<PuzzleNode*> children;
	PuzzleNode* parent;

	PuzzleNode() {};

	PuzzleNode(const vector<vector<char>> &gameGrid, PuzzleNode* parent, WormMove* parentMove) {
		this->gameGrid = vector<vector<char>>(gameGrid);
		this->parent = parent;
		this->parentMove = parentMove;
		this->children = vector<PuzzleNode*>();
	};

	~PuzzleNode() {
		delete parent;
		delete parentMove;
	};

};

class PuzzleTree {


private:

public:
	PuzzleTree();

	PuzzleNode root;

	PuzzleTree(const vector<vector<char>> &gameGrid);

	PuzzleNode* insert(PuzzleNode* parent, WormMove* parentMove, const vector<vector<char>> &gameGrid);

	~PuzzleTree();
};

#endif
