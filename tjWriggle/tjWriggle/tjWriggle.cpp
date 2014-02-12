// tjWriggle.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <time.h>
#include <stack>
#include <unordered_map>
#include <boost/unordered_map.hpp>

#include "WriggleWorm.h"
#include "PuzzleTree.h"


using namespace std;

//Print all of the possible moves stored within allWormMoves
void printAllMoves(const vector<WormMove*> &allWormMoves) {
	for (vector<WormMove*>::const_iterator i = allWormMoves.begin(); i != allWormMoves.end(); ++i) {
		cout << (*i);
	}
}

//If goal is reached of worm index '0' 
bool isGoalReached(map<char, WriggleWorm> allWorms) {
	if (allWorms.size() > 0) {
		return allWorms['0'].isGoal();
	} else {
		return false;
	}
}

/*
struct eqstr {
	bool operator()(const char* n1, const char* n2) {
		return strncmp(n1, n2, 64) == 0;
	}
};

char *hashGrid (PuzzleNode* node) {
	char* hashValue = new char[64]();
	for (vector<vector<char>>::iterator i = node->gameGrid.begin(); i != node->gameGrid.end(); ++i) {
		for (vector<char>::iterator j = i->begin(); j != i->end(); ++j) {
			int firstIndex = i - node->gameGrid.begin();
			int secondIndex = j - i->begin();
			hashValue[firstIndex * i->size() + secondIndex] = *j;
		}
	}
	return hashValue;
}
*/

void iterativelyDeepeningDepthFirstTreeSearch(vector<vector<char>> &puzzleGrid, short numWriggle) {
	clock_t startTime = clock();
	map<char, WriggleWorm> allWorms;
	vector<WormMove*> resultMoves;
	PuzzleNode* currentNode;
	int depthLimit = 0;

	//While tail or head have not reached the goal indexed at bottom right corner. 
	while (!isGoalReached(allWorms)) {

		//Initializing tree
		PuzzleTree resultTree = PuzzleTree(puzzleGrid);
		//Using root as current node
		currentNode = resultTree.getRoot();
		//Initializing stack
		stack<PuzzleNode*> currentChildrenList;
		//Putting root as first item within stack
		currentChildrenList.push(resultTree.getRoot());

		//While stack is not empty
		while (!currentChildrenList.empty()) {
			
			vector<WormMove*> allWormMoves;
			allWorms = map<char, WriggleWorm>();
			currentNode = currentChildrenList.top();
			currentChildrenList.pop();
			//unordered_map<const char*, PuzzleNode*, hash<const char *>, eqstr> allStates;

			char buffer[2];

			for (int i = 0; i < numWriggle; i++) {
				_itoa_s(i, buffer, 10);
				//Inserting all wriggle worms in allworms
				allWorms.insert(pair<char, WriggleWorm>(buffer[0], WriggleWorm(currentNode->gameGrid, buffer[0])));

				//Inserting all moves of each wriggle worm found into allWormMoves 
				allWorms[buffer[0]].allPossibleMoves(currentNode->gameGrid, allWormMoves);
			}
			if (isGoalReached(allWorms)) {
				break;
			}
			if (currentNode->nodeDepth < depthLimit) {
				for (int i = allWormMoves.size() - 1; i >= 0; i--) {
					//Creating the new move 
					vector<vector<char>> newGrid = allWorms[allWormMoves[i]->wormIndex].newMovePuzzle(currentNode->gameGrid, allWormMoves[i]);
					//Inserting new grid in tree
					PuzzleNode* temp = resultTree.insert(currentNode, allWormMoves[i], newGrid);
					//char* hash = hashGrid(temp);

					//if (allStates.find(hash) == allStates.end()) {
						//allStates[hash] = temp;
						//Inserting new grid on top of stack
						currentChildrenList.push(temp);
					//}
				}
			}
		}
		resultTree = PuzzleTree(puzzleGrid);
		currentChildrenList = stack<PuzzleNode*>();
		depthLimit++;
		cout << depthLimit << endl;
	}

	//Going back to get the path of the result
	PuzzleNode* lastNode = currentNode;
	while (currentNode->parent != NULL) {
		resultMoves.push_back(currentNode->parentMove);
		currentNode = currentNode->parent;
	}
	clock_t endTime = clock();

	ofstream resultFile;

	resultFile.open("resultFile.txt");

	for (vector<WormMove*>::reverse_iterator it = resultMoves.rbegin(); it != resultMoves.rend(); ++it) {
		resultFile << (**it);
	}
	resultFile << (lastNode->gameGrid);
	resultFile << (endTime - startTime) << endl;
	resultFile << resultMoves.size();

	resultFile.close();
}
/*
void breadthFirstTreeSearch(vector<vector<char>> &puzzleGrid, short numWriggle) {
	clock_t startTime = clock();
	PuzzleTree resultTree = PuzzleTree(puzzleGrid);
	PuzzleNode* currentNode = resultTree.getRoot();
	queue<PuzzleNode*> currentChildrenList;
	map<char, WriggleWorm> allWorms;
	vector<WormMove*> resultMoves;

	while (true) {
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
			vector<vector<char>> newGrid = allWorms[allWormMoves[i]->wormIndex].newMovePuzzle(currentNode->gameGrid, allWormMoves[i]);
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
	clock_t endTime = clock();
	for (vector<WormMove*>::reverse_iterator it = resultMoves.rbegin(); it != resultMoves.rend(); ++it) {
		cout << (**it);
	}
	cout << (lastNode->gameGrid);
	cout << (endTime - startTime) << endl;
	cout << resultMoves.size();
}
*/
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

		iterativelyDeepeningDepthFirstTreeSearch(puzzleGrid, numWriggle);
	}

	return 0;
}