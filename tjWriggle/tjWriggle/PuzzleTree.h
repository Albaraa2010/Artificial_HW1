#ifndef h_PuzzleTree
#define h_PuzzleTree

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#include "WriggleWorm.h"

using namespace std;
typedef vector<vector<char>> vecChar;

struct PuzzleNode {
	//Move made from a parent on the tree to the child (stored with the child)
	WormMove* parentMove;
	vecChar* gameGrid;
	vector<PuzzleNode*> children;
	map<char, WriggleWorm>* allWorms;
	PuzzleNode* parent;
	int nodeDepth;

	PuzzleNode() {};

	PuzzleNode(vecChar*  gameGrid, PuzzleNode* parent, WormMove* parentMove, map<char, WriggleWorm>* allWorms) {
		this->gameGrid = gameGrid;
		this->parent = parent;
		this->parentMove = parentMove;
		this->allWorms = allWorms;
		this->children = vector<PuzzleNode*>();
		if (parent != NULL) {
			this->nodeDepth = parent->nodeDepth + 1;
		} else {
			this->nodeDepth = 0;
		}
	};
	~PuzzleNode() {
		/*delete allWorms;
		delete gameGrid;
		for (vector<PuzzleNode*>::iterator i = children.begin(); i != children.end(); ++i) {
			delete *i;
		}
		delete parentMove;*/
	};

	map<char, WriggleWorm>* getAllWorms() {
		return allWorms;
	}
};

class PuzzleTree {
private:
	PuzzleNode root;
public:
	PuzzleTree();
	PuzzleTree(vecChar* gameGrid, map<char, WriggleWorm>* allWorms);
	PuzzleNode* getRoot();
	PuzzleNode* insert(PuzzleNode* parent, WormMove* parentMove, vecChar* gameGrid, map<char, WriggleWorm>* allWorms);
	~PuzzleTree();
};
#endif