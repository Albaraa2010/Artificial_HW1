#ifndef h_PuzzleTree
#define h_PuzzleTree

#include <iostream>
#include <fstream>
#include <vector>

#include "WriggleWorm.h"

using namespace std;

struct PuzzleNode {
	//Move made from a parent on the tree to the child (stored with the child)
	WormMove* parentMove;
	vector<vector<char>> gameGrid;
	vector<PuzzleNode*> children;
	PuzzleNode* parent;
	int nodeDepth;

	PuzzleNode() {};

	PuzzleNode(const vector<vector<char>> &gameGrid, PuzzleNode* parent, WormMove* parentMove) {
		this->gameGrid = vector<vector<char>>(gameGrid);
		this->parent = parent;
		this->parentMove = parentMove;
		this->children = vector<PuzzleNode*>();
		if (parent != NULL) {
			this->nodeDepth = parent->nodeDepth + 1;
		} else {
			this->nodeDepth = 0;
		}
	};
	~PuzzleNode() {
		/*for (vector<PuzzleNode*>::iterator i = children.begin(); i != children.end(); ++i) {
			delete *i;
		}
		delete parentMove;*/
	};
};

class PuzzleTree {
private:
	PuzzleNode root;
public:
	PuzzleTree();
	PuzzleTree(const vector<vector<char>> &gameGrid);
	PuzzleNode* getRoot();
	PuzzleNode* insert(PuzzleNode* parent, WormMove* parentMove, const vector<vector<char>> &gameGrid);
	~PuzzleTree();
};
#endif