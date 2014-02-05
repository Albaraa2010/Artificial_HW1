// tjWriggle.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <time.h>

#include "WriggleWorm.h"
#include "PuzzleTree.h"


using namespace std;

void printAllMoves(const vector<WormMove*> &allWormMoves) {
	for (vector<WormMove*>::const_iterator i = allWormMoves.begin(); i != allWormMoves.end(); ++i) {
		(*i)->print();
	}
}

bool isGoalReached(map<char, WriggleWorm> allWorms) {
	return allWorms['0'].isGoal();
}

void breadthFirstTreeSearch(vector<vector<char>> &puzzleGrid, short numWriggle) {
	time_t startTime = time(NULL);
	PuzzleTree resultTree = PuzzleTree(puzzleGrid);
	PuzzleNode* currentNode = resultTree.getRoot();
	queue<PuzzleNode*> currentChildrenList;
	map<char, WriggleWorm> allWorms;
	vector<WormMove*> resultMoves;

	while (!isGoalReached(allWorms)) {
		vector<WormMove*> allWormMoves;
		allWorms = map<char, WriggleWorm>();

		char buffer[2];
		for (int i = 0; i < numWriggle; i++) {
			_itoa_s(i, buffer, 10);
			allWorms.insert(pair<char, WriggleWorm>(buffer[0], WriggleWorm(currentNode->gameGrid, buffer[0])));
			allWorms[buffer[0]].allPossibleMoves(currentNode->gameGrid, allWormMoves);
		}
		if (isGoalReached(allWorms)) {
			break;
		}
		for (int i = 0; i < allWormMoves.size(); i++) {
			vector<vector<char>> newGrid = allWorms[allWormMoves[i]->wormIndex].newMovePuzzle(currentNode->gameGrid, *allWormMoves[i]);
			currentChildrenList.push(resultTree.insert(currentNode, allWormMoves[i], newGrid));
		}
		currentNode = currentChildrenList.front();
		currentChildrenList.pop();
	}
	PuzzleNode* lastNode = currentNode;
	while (currentNode->parent != NULL) {
		resultMoves.push_back(currentNode->parentMove);
		currentNode = currentNode->parent;
	}
	time_t endTime = time(NULL);
	for (vector<WormMove*>::reverse_iterator it = resultMoves.rbegin(); it != resultMoves.rend(); ++it) {
		(*it)->print();
	}
	WriggleWorm::printPuzzle(lastNode->gameGrid);
	cout << endTime - startTime << endl;
	cout << resultMoves.size();
}

int main(int argc, char* argv[]) {

	string puzzleName = argv[1];
	ifstream puzzleFile;
	short lineCount = 0;
	short charCount = 0;
	short width, height, numWriggle;
	vector<vector<char>> puzzleGrid;

	puzzleFile.open(puzzleName);


	if (puzzleFile.is_open()) {

		while (!puzzleFile.eof()) {

			char character = puzzleFile.get();
			if ('\n' == character) {
				lineCount++;
				charCount = 0;
			} else if (lineCount == 0) {
				if (' ' != character) {
					switch (charCount) {

					case 0:
						width = static_cast<short>(character - '0');
						break;

					case 1:
						height = static_cast<short>(character - '0');
						break;

					case 2:
						numWriggle = static_cast<short>(character - '0');
						puzzleGrid = vector<vector<char>>(height, vector<char>(width, ' '));
						break;
					}
				} else {
					++charCount;
				}
			} else if (lineCount >= 1) {
				if (' ' != character && lineCount - 1 < height && charCount < width) {
					puzzleGrid[lineCount - 1][charCount++] = character;
				}
			}
		}

		breadthFirstTreeSearch(puzzleGrid, numWriggle);
	}

	return 0;
}