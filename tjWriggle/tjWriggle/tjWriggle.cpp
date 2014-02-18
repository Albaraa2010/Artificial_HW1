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

#include <boost/unordered_map.hpp>
#include <boost/functional/hash/hash.hpp>
#include <boost/heap/priority_queue.hpp>

using namespace std;

//2 dimensional vector of characters.
typedef vector<vector<char>> vecChar;

struct puzzleGraphNode {
	vecChar* gameGrid;
	WormMove* parentMove;
	int parent;
};

//Graph using adjacency list that is directed, stores grid and worm move, and uses an edgweight of int value between vertices.
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, puzzleGraphNode, boost::property<boost::edge_weight_t, int> > myGraph;

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
int heuristic(WormMove* currentMove, map<char, WriggleWorm>* & allWorms) {
	int edgeWeight = 0;
	int xDifference, yDifference;
	if (currentMove->wormIndex == 0) {
		//The closer that the worm index 0 is to the goal the bigger the edgeweight.
		xDifference = allWorms->at(0).getGoalX() - currentMove->xCoord;
		yDifference = allWorms->at(0).getGoalY() - currentMove->yCoord;
		edgeWeight = edgeWeight + xDifference + yDifference;
	} else {
		//The farther that worms other than index 0 worm are from the goal the bigger the edgeweight.
		xDifference = abs(0 - currentMove->xCoord);
		yDifference = abs(0 - currentMove->yCoord);
	}
	return edgeWeight;
}
class compareEdgeWeights {
public:
	bool operator()(const pair<int, int> & p1, const pair<int, int> & p2) const {
		return p1.second < p2.second;
	}
};
string hashGrid(vecChar* node) {
	char* hashValue = new char[65]();
	for (vector<vector<char>>::iterator i = node->begin(); i != node->end(); ++i) {
		for (vector<char>::iterator j = i->begin(); j != i->end(); ++j) {
			int firstIndex = i - node->begin();
			int secondIndex = j - i->begin();
			hashValue[firstIndex * i->size() + secondIndex] = *j;
		}
	}
	return string(hashValue);
}
void greedyBestFirstGraphSearch(vecChar *puzzleGrid, short numWriggle) {
	boost::unordered_map<string, vecChar*> alreadyExists;
	boost::heap::priority_queue<pair<int, int>, boost::heap::compare<compareEdgeWeights>> queueBest;
	clock_t startTime = clock();
	vector<WormMove*> resultMoves;
	vecChar* currentNode;
	int currentParentIndex = 0;
	map<char, WriggleWorm>* allWorms = NULL;
	myGraph allPuzzlesGraph;
	currentNode = puzzleGrid;
	int temp = boost::add_vertex(allPuzzlesGraph);
	allPuzzlesGraph[temp].gameGrid = currentNode;
	allPuzzlesGraph[temp].parent = -1;

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
		if (isGoalReached(allWorms)) {
			break;
		}
		for (auto iter : allWormMoves) {
			int tempGraphIndex;
			int currentEdgeWeight;
			/*
			int currentParentXVal, currentParentYVal;
			if (iter->isHead) {
				currentParentXVal = allWorms->at(iter->wormIndex).getWormHead().xCoord;
				currentParentYVal = allWorms->at(iter->wormIndex).getWormHead().yCoord;
			} else {
				currentParentXVal = allWorms->at(iter->wormIndex).getWormTail().xCoord;
				currentParentYVal = allWorms->at(iter->wormIndex).getWormTail().yCoord;
			}*/
			string gridHashVal;
			map<char, WriggleWorm>* newWormSet = new map<char, WriggleWorm>(*allWorms);
			//Creating the new move 
			vecChar* newGrid = newWormSet->at(iter->wormIndex).newMovePuzzle(currentNode, iter, allWorms->at(iter->wormIndex));
			//Inserting new grid in graph
			gridHashVal = hashGrid(newGrid);
			if (alreadyExists.find(gridHashVal) == alreadyExists.end()) {
				currentEdgeWeight = heuristic(iter, allWorms);
				alreadyExists.insert({ gridHashVal, newGrid });
				tempGraphIndex = boost::add_vertex(allPuzzlesGraph);
				allPuzzlesGraph[tempGraphIndex].gameGrid = newGrid;
				allPuzzlesGraph[tempGraphIndex].parent = currentParentIndex;
				allPuzzlesGraph[tempGraphIndex].parentMove = iter;
				boost::add_edge(currentParentIndex, tempGraphIndex, currentEdgeWeight, allPuzzlesGraph);
				queueBest.push({tempGraphIndex, currentEdgeWeight});
			}
		}
		currentParentIndex = queueBest.top().first;
		currentNode = allPuzzlesGraph[currentParentIndex].gameGrid;
		queueBest.pop();
	}
	clock_t endTime = clock();
	int moveCount = 1;
	vector<WormMove> allMoves;
	while (currentParentIndex != 0) {
		allMoves.push_back(*allPuzzlesGraph[currentParentIndex].parentMove);
		moveCount++;
		currentParentIndex = allPuzzlesGraph[currentParentIndex].parent;
	}
	ofstream resultFile;

	resultFile.open("resultFile.txt");
	for (int i = allMoves.size() - 1; i >= 0; i--) {
		resultFile << allMoves[i];
	}
	vecChar* lastNode = currentNode;
	resultFile << *currentNode;
	resultFile << (endTime - startTime) << endl;
	resultFile << moveCount;
}
/*
void iterativelyDeepeningDepthFirstTreeSearch(vecChar *puzzleGrid, short numWriggle) {
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
					vecChar* newGrid = newWormSet->at(iter->wormIndex).newMovePuzzle(currentNode->gameGrid, iter, allWorms->at(iter->wormIndex));
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
*/
/*
void breadthFirstTreeSearch(vecChar &puzzleGrid, short numWriggle) {
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
			vecChar newGrid = allWorms[allWormMoves[i]->wormIndex].newMovePuzzle(currentNode->gameGrid, allWormMoves[i]);
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
	vecChar* puzzleGrid;

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
						puzzleGrid = new  vecChar(height, vector<char>(width, ' '));
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

		greedyBestFirstGraphSearch(puzzleGrid, numWriggle);
	}

	return 0;
}