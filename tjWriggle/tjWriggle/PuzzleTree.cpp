#include "PuzzleTree.h"

PuzzleTree::PuzzleTree() {
}

PuzzleTree::PuzzleTree(const vector<vector<char>> &gameGrid) {
	this->root = PuzzleNode(gameGrid, NULL, NULL); 
}

PuzzleNode* PuzzleTree::getRoot() {
	return &this->root;
}

PuzzleTree::~PuzzleTree() {
}

//Inserting a puzzle in the tree.
PuzzleNode* PuzzleTree::insert(PuzzleNode* parent, WormMove* parentMove, const vector<vector<char>> &gameGrid) {
	PuzzleNode* resultPuzzle = new PuzzleNode(gameGrid, parent, parentMove);
	parent->children.push_back(resultPuzzle);

	return resultPuzzle;
}
