#ifndef h_WriggleWorm
#define h_WriggleWorm

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/functional/hash/hash.hpp>

using namespace std;

struct WormPiece {
	short xCoord;
	short yCoord;
	char direction;

	WormPiece() {
	};

	WormPiece(short y, short x, char dir) {
		xCoord = x;
		yCoord = y;
		direction = dir;
	};
};

struct WormMove {
	short xCoord;
	short yCoord;
	char wormIndex;
	bool isHead;

	WormMove() {};

	WormMove(short y, short x, char index, bool head) {
		xCoord = x;
		yCoord = y;
		wormIndex = index;
		isHead = head;
	};

	friend ostream& operator<<(ostream& out, WormMove& move) {
		out << move.wormIndex << " " << !move.isHead << " " << move.xCoord << " " << move.yCoord << endl;
		return out;
	}
};
class WriggleWorm {

public:
	WriggleWorm() {};
	WriggleWorm(const vector<vector<char>> &puzzleGrid, char wriggleIndex);
	WriggleWorm(const WriggleWorm & oldWorm);
	~WriggleWorm();

	//Returns all possible moves for all wriggles (tail and head) within the puzzle.
	void allPossibleMoves(const vector<vector<char>> &puzzleGrid, vector<WormMove*> &allWormMoves);

	//Does the move and fixes the directions of the worm.
	vector<vector<char>> newMovePuzzle(const vector<vector<char>> &puzzleGrid, const WormMove *wormMove);

	//To output the puzzle to a file through the use of << operator
	friend ostream& operator<<(ostream& out, const vector<vector<char>> &puzzleGrid);

	//If goal is found.
	bool isGoal();

	static boost::unordered_map<pair<char, char>, char> populateMap() {
		boost::unordered_map<pair<char, char>, char> map = boost::unordered_map<pair<char, char>, char>();
		map.insert({ { -1, 0 }, '>' });
		map.insert({ { 1, 0 }, '<' });
		map.insert({ { 0, -1 }, 'v' });
		map.insert({ { 0, 1 }, '^' });
		return map;
	}
	static boost::unordered_map<pair<char, char>, char> populateHeadMap() {
		boost::unordered_map <pair<char, char>, char> map = boost::unordered_map<pair<char, char>, char>();
		map.insert({ { -1, 0 }, 'R' });
		map.insert({ { 1, 0 }, 'L' });
		map.insert({ { 0, -1 }, 'D' });
		map.insert({ { 0, 1 }, 'U' });
		return map;
	}

private:
	static boost::unordered_map<pair<char, char>, char> directionMap;
	static boost::unordered_map<pair<char, char>, char> headDirectionMap;
	WormPiece wormHead;
	WormPiece wormTail;
	short goalX, goalY;
	//The number worm depending on the tail.
	char wormIndex;
	//Body pieces include of all pieces between tail and head.
	vector<WormPiece> wormBody;
};
#endif