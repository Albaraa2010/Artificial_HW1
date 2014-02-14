#include "PuzzleTree.h"

PuzzleTree::PuzzleTree() {
}

PuzzleTree::PuzzleTree(vector<vector<char>>* gameGrid, map<char, WriggleWorm>* allWorms) {
	this->root = PuzzleNode(gameGrid, NULL, NULL, allWorms); 
}

PuzzleNode* PuzzleTree::getRoot() {
	return &this->root;
}

PuzzleTree::~PuzzleTree() {
}

//Inserting a puzzle in the tree.
PuzzleNode* PuzzleTree::insert(PuzzleNode* parent, WormMove* parentMove, vector<vector<char>>* gameGrid, map<char, WriggleWorm>* allWorms) {
	PuzzleNode* resultPuzzle = new PuzzleNode(gameGrid, parent, parentMove, allWorms);
	parent->children.push_back(resultPuzzle);

	return resultPuzzle;
}
