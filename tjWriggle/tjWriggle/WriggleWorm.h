#ifndef h_WriggleWorm
#define h_WriggleWorm

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

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
namespace std {
	template<> struct hash< std::string > {
		size_t operator()(const std::string& x) const {
			return hash< const char* >()(x.c_str());
		}
	};
}
struct eqstr {
	bool operator()(const char* n1, const char* n2) {
		return strncmp(n1, n2, 3) == 0;
	}
};
/*
struct Key {
	std::string first;
	std::string second;

	bool operator==(const Key &other) const {
		return (first == other.first
			&& second == other.second);
	}
};

namespace std {
	template <>
	struct hash<Key> {
		std::size_t operator()(const Key& k) const {
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<string>()(k.first)
				^ (hash<string>()(k.second) << 1)) >> 1);
		}
	};
}
*/
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

	static string hashPair(const char c1, const char c2) {
		char *hashValue = new char[3]();

		hashValue[0] = c1 + 5;
		hashValue[1] = c2 + 5;
		hashValue[2] = 0;

		return string(hashValue);
	}

	static unordered_map<string, char> populateMap() {
		unordered_map<string, char> map = unordered_map<string, char>();
		map.insert({ { "-1", "0" }, '>' });
		map.insert({ { "1", "0" }, '<' });
		map.insert({ { "0", "-1" }, 'v' });
		map.insert({ { "0", "1" }, '^' });
		return map;
	}
	static unordered_map<string, char> populateHeadMap() {
		unordered_map<string, char> map = unordered_map<string, char>();
		map.insert({ { "-1", "0" }, 'L' });
		map.insert({ { "1", "0" }, 'R' });
		map.insert({ { "0", "-1" }, 'D' });
		map.insert({ { "0", "1" }, 'U' });
		return map;
	}

private:
	static unordered_map<string, char> directionMap;
	static unordered_map<string, char> headDirectionMap;
	WormPiece wormHead;
	WormPiece wormTail;
	short goalX, goalY;
	//The number worm depending on the tail.
	char wormIndex;
	//Body pieces include of all pieces between tail and head.
	vector<WormPiece> wormBody;
};

#endif

