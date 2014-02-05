#ifndef h_WriggleWorm
#define h_WriggleWorm

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct WormPiece {
	int xCoord;
	int yCoord;
	char direction;

	WormPiece() {};

	WormPiece(int y, int x, char dir) {
		xCoord = x;
		yCoord = y;
		direction = dir;
	};
};

struct WormMove {
	int xCoord;
	int yCoord;
	char wormIndex;
	bool isHead;


	WormMove() {};

	WormMove(int y, int x, char index, bool head) {
		xCoord = x;
		yCoord = y;
		wormIndex = index;
		isHead = head;
	};

	void print() const {
		cout << wormIndex << " " << !isHead << " " << xCoord << " " << yCoord << endl;
	}

};

class WriggleWorm {

public:

	WriggleWorm() {};
	WriggleWorm(const vector<vector<char>> &puzzleGrid, char wriggleIndex);
	WriggleWorm(const WriggleWorm & oldWorm);
	~WriggleWorm();

	//Returns all possible moves for all wriggles (tail and head) within the puzzle.
	char allPossibleMoves(const vector<vector<char>> &puzzleGrid, vector<WormMove*> &allWormMoves);
	vector<vector<char>> newMovePuzzle(const vector<vector<char>> &puzzleGrid, const WormMove &wormMove);
	static void printPuzzle(const vector<vector<char>> &puzzleGrid);
	bool isGoal();

private:
	WormPiece wormHead;
	WormPiece wormTail;
	short goalX, goalY;
	char wormIndex;
	vector<WormPiece> wormBody;


};

#endif

