// tjWriggle.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <time.h>
#include <stack>
#include <boost/unordered_map.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "WriggleWorm.h"
#include "PuzzleTree.h"


using namespace std;

//Print all of the possible moves stored within allWormMoves
void printAllMoves(const vector<WormMove*> &allWormMoves) {
	for (vector<WormMove*>::const_iterator i = allWormMoves.begin(); i != allWormMoves.end(); ++i) {
		cout << (**i);
	}
}

//If goal is reached of worm index '0' 
bool isGoalReached(map<char, WriggleWorm>* allWorms) {
	if (allWorms && allWorms->size() > 0) {
		return allWorms->at('0').isGoal();
	} else {
		return false;
	}
}
struct puzzleGraphNode {
	vector<vector<char>>* gameGrid;
};
void GreedyBestFirstGraphSearch(vector<vector<char>> *puzzleGrid, short numWriggle) {
	clock_t startTime = clock();
	vector<WormMove*> resultMoves;
	vector<vector<vector<char>>*> allNodes;
	vector<vector<char>>* currentNode;
	map<char, WriggleWorm>* allWorms = NULL;
	boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, puzzleGraphNode ,boost::property<boost::edge_weight_t, int> > allPuzzlesGraph;

	currentNode = puzzleGrid;
	allNodes.push_back(currentNode);
	int temp = boost::add_vertex(allPuzzlesGraph);
	cout << temp << endl;
	temp = boost::add_vertex(allPuzzlesGraph);
	cout << temp << endl;
	allPuzzlesGraph[temp].gameGrid = currentNode;

	while (!isGoalReached(allWorms)) {
		vector<WormMove*> allWormMoves;
		allWorms = new map<char, WriggleWorm>();
		char firstBuffer[2];
		for (int i = 0; i < numWriggle; i++) {
			_itoa_s(i, firstBuffer, 10);
			//Inserting all wriggle worms in allworms
			allWorms->insert(pair<char, WriggleWorm>(firstBuffer[0], WriggleWorm(*currentNode, firstBuffer[0])));
		}
		for (map<char, WriggleWorm>::iterator iter = allWorms->begin(); iter != allWorms->end(); ++iter) {
			//Inserting all moves of each wriggle worm found into allWormMoves 
			iter->second.allPossibleMoves(*currentNode, allWormMoves);
		}
		for (auto iter : allWormMoves) {
			map<char, WriggleWorm>* newWormSet = new map<char, WriggleWorm>(*allWorms);
			//Creating the new move 
			vector<vector<char>>* newGrid = newWormSet->at(iter->wormIndex).newMovePuzzle(currentNode, iter, allWorms->at(iter->wormIndex));
			//Inserting new grid in graph
			boost::add_vertex(allPuzzlesGraph);
			allNodes.push_back(newGrid);
			//Check heuristic
			boost::add_edge(0, 0, 0, allPuzzlesGraph);
		}
	}
	clock_t endTime = clock();

	ofstream resultFile;

	resultFile.open("resultFile.txt");


	cout << (endTime - startTime) << endl;
	cout << resultMoves.size();
}

void iterativelyDeepeningDepthFirstTreeSearch(vector<vector<char>> *puzzleGrid, short numWriggle) {
	clock_t startTime = clock();
	vector<WormMove*> resultMoves;
	PuzzleNode* currentNode;
	int depthLimit = 0;
	map<char, WriggleWorm>* allWorms = NULL;
	//While tail or head have not reached the goal indexed at bottom right corner. 
	while (!isGoalReached(allWorms)) {
		allWorms = new map<char, WriggleWorm>();
		char firstBuffer[2];
		//Initializing tree
		PuzzleTree resultTree = PuzzleTree(puzzleGrid, allWorms);
		//Using root as current node
		currentNode = resultTree.getRoot();
		//Initializing stack
		stack<PuzzleNode*> currentChildrenList;
		//Putting root as first item within stack
		currentChildrenList.push(resultTree.getRoot());
		for (int i = 0; i < numWriggle; i++) {
			_itoa_s(i, firstBuffer, 10);
			//Inserting all wriggle worms in allworms
			allWorms->insert(pair<char, WriggleWorm>(firstBuffer[0], WriggleWorm(*(currentNode->gameGrid), firstBuffer[0])));
		}

		//While stack is not empty
		while (!currentChildrenList.empty()) {
			vector<WormMove*> allWormMoves;
			allWormMoves.reserve(8);
			currentNode = currentChildrenList.top();
			allWorms = currentNode->getAllWorms();
			currentChildrenList.pop();
			//unordered_map<const char*, PuzzleNode*, hash<const char *>, eqstr> allStates;

			char buffer[2];

			for (map<char, WriggleWorm>::iterator iter = allWorms->begin(); iter != allWorms->end(); ++iter) {
				//Inserting all moves of each wriggle worm found into allWormMoves 
				iter->second.allPossibleMoves(*currentNode->gameGrid, allWormMoves);
			}
			if (isGoalReached(allWorms)) {
				break;
			}
			if (currentNode->nodeDepth < depthLimit) {
				for (auto iter: allWormMoves) {
					map<char, WriggleWorm>* newWormSet = new map<char, WriggleWorm>(*allWorms);
					//Creating the new move 
					vector<vector<char>>* newGrid = newWormSet->at(iter->wormIndex).newMovePuzzle(currentNode->gameGrid, iter, allWorms->at(iter->wormIndex));
					//Inserting new grid in tree
					PuzzleNode* temp = resultTree.insert(currentNode, iter, newGrid, newWormSet);
					//char* hash = hashGrid(temp);

					//if (allStates.find(hash) == allStates.end()) {
						//allStates[hash] = temp;
						//Inserting new grid on top of stack
						currentChildrenList.push(temp);
					//}
				}
			}
		}
		currentChildrenList = stack<PuzzleNode*>();
		depthLimit++;
		clock_t tempTime = clock();
		cout << (tempTime - startTime) << ' ' << depthLimit << endl;
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
	resultFile << *(lastNode->gameGrid);
	resultFile << (endTime - startTime) << endl;
	resultFile << resultMoves.size();

	resultFile.close();
	for (vector<WormMove*>::reverse_iterator it = resultMoves.rbegin(); it != resultMoves.rend(); ++it) {
		cout << (**it);
	}
	cout << *(lastNode->gameGrid);
	cout << (endTime - startTime) << endl;
	cout << resultMoves.size();
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
	vector<vector<char>>* puzzleGrid;

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
						puzzleGrid = new  vector<vector<char>>(height, vector<char>(width, ' '));
						break;
					}
				} else {
					++charCount;
				}
			} else if (lineCount >= 1) {
				if (' ' != character && lineCount - 1 < height && charCount < width) {
					puzzleGrid->at(lineCount - 1)[charCount++] = character;
				}
			}
		}

		GreedyBestFirstGraphSearch(puzzleGrid, numWriggle);
	}

	return 0;
}