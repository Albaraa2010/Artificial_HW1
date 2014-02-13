#include "WriggleWorm.h"


boost::unordered_map<pair<char, char>, char> WriggleWorm::directionMap = WriggleWorm::populateMap();
boost::unordered_map<pair<char, char>, char> WriggleWorm::headDirectionMap = WriggleWorm::populateHeadMap();

//Creating wriggle worm to identify with as a wriggle worm within the puzzle.
WriggleWorm::WriggleWorm(const vector<vector<char>> &puzzleGrid, char wriggleIndex) {
	wormIndex = wriggleIndex;
	goalX = puzzleGrid[0].size() - 1;
	goalY = puzzleGrid.size() - 1;
	for (vector<vector<char>>::const_iterator i = puzzleGrid.begin(); i != puzzleGrid.end(); ++i) {
		for (vector<char>::const_iterator j = i->begin(); j != i->end(); ++j) {
			if (wriggleIndex == *j) {
				char currentBodyPiece = *j;
				char bodyPieceYCount = i - puzzleGrid.begin();
				char bodyPieceXCount = j - i->begin();

				//Initializes the tail as this is where the worm is starting
				wormTail = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);

				//While not reaching the head of the worm
				while ('U' != currentBodyPiece && 'D' != currentBodyPiece && 'R' != currentBodyPiece && 'L' != currentBodyPiece) {
					bool breaker = false;
					for (int k = -1; k <= 1; k++) {
						for (int l = -1; l <= 1; l++) {
							if (!(k == l) && k == 0 || l == 0) {
								if (bodyPieceXCount + l >= 0 && bodyPieceXCount + l < puzzleGrid[bodyPieceYCount].size() && 
									bodyPieceYCount + k >= 0 && bodyPieceYCount + k < puzzleGrid.size()) {

									if (puzzleGrid[bodyPieceYCount + k][bodyPieceXCount + l] == directionMap[{ char(l), char(k) }]) {
										currentBodyPiece = puzzleGrid[bodyPieceYCount + k][bodyPieceXCount + l];
										bodyPieceXCount = bodyPieceXCount + l;
										bodyPieceYCount = bodyPieceYCount + k;
										wormBody.push_back(WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece));
										breaker = true;
										break;
									} else if (puzzleGrid[bodyPieceYCount + k][bodyPieceXCount + l] == headDirectionMap[{ char(l), char(k) }]) {
										currentBodyPiece = puzzleGrid[bodyPieceYCount + k][bodyPieceXCount + l];
										bodyPieceXCount = bodyPieceXCount + l;
										bodyPieceYCount = bodyPieceYCount + k;
										wormHead = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);
										breaker = true;
										break;
									}
								}
							}
						}
						if (breaker) { break; }
					}
					/*
					if (bodyPieceXCount - 1 >= 0 && puzzleGrid[bodyPieceYCount][bodyPieceXCount - 1] == '>') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount][bodyPieceXCount - 1];
						bodyPieceXCount = bodyPieceXCount - 1;
						wormBody.push_back(WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece));

					} else if (bodyPieceXCount + 1 < puzzleGrid[bodyPieceYCount].size() && puzzleGrid[bodyPieceYCount][bodyPieceXCount + 1] == '<') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount][bodyPieceXCount + 1];
						bodyPieceXCount = bodyPieceXCount + 1;
						wormBody.push_back(WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece));

					} else if (bodyPieceYCount - 1 >= 0 && puzzleGrid[bodyPieceYCount - 1][bodyPieceXCount] == 'v') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount - 1][bodyPieceXCount];
						bodyPieceYCount = bodyPieceYCount - 1;
						wormBody.push_back(WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece));

					} else if (bodyPieceYCount + 1 < puzzleGrid.size() && puzzleGrid[bodyPieceYCount + 1][bodyPieceXCount] == '^') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount + 1][bodyPieceXCount];
						bodyPieceYCount = bodyPieceYCount + 1;
						wormBody.push_back(WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece));

					} else if (bodyPieceXCount - 1 >= 0 && puzzleGrid[bodyPieceYCount][bodyPieceXCount - 1] == 'R') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount][bodyPieceXCount - 1];
						bodyPieceXCount = bodyPieceXCount - 1;
						wormHead = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);

					} else if (bodyPieceXCount + 1 < puzzleGrid[bodyPieceYCount].size() && puzzleGrid[bodyPieceYCount][bodyPieceXCount + 1] == 'L') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount][bodyPieceXCount + 1];
						bodyPieceXCount = bodyPieceXCount + 1;
						wormHead = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);

					} else if (bodyPieceYCount - 1 >= 0 && puzzleGrid[bodyPieceYCount - 1][bodyPieceXCount] == 'D') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount - 1][bodyPieceXCount];
						bodyPieceYCount = bodyPieceYCount - 1;
						wormHead = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);

					} else if (bodyPieceYCount + 1 < puzzleGrid.size() && puzzleGrid[bodyPieceYCount + 1][bodyPieceXCount] == 'U') {
						currentBodyPiece = puzzleGrid[bodyPieceYCount + 1][bodyPieceXCount];
						bodyPieceYCount = bodyPieceYCount + 1;
						wormHead = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);
					}
					*/
				}
			}
		}
	}
}


WriggleWorm::WriggleWorm(const WriggleWorm & oldWorm) {
	this->wormBody = vector<WormPiece>(oldWorm.wormBody);
	this->wormHead = oldWorm.wormHead;
	this->wormTail = oldWorm.wormTail;
	this->wormIndex = oldWorm.wormIndex;
	this->goalX = oldWorm.goalX;
	this->goalY = oldWorm.goalY;
}

WriggleWorm::~WriggleWorm() {
}

//Finding all possible moves of tail and head of all of the wriggle worms within the puzzle
void WriggleWorm::allPossibleMoves(const vector<vector<char>> &puzzleGrid, vector<WormMove*> &allWormMoves) {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!(i == j) && i == 0 || j == 0) {
				if (this->wormHead.xCoord + j >= 0 && this->wormHead.xCoord + j  < puzzleGrid[this->wormHead.yCoord].size() && this->wormHead.yCoord + i >= 0 && 
					this->wormHead.yCoord + i < puzzleGrid.size() && puzzleGrid[this->wormHead.yCoord + i][this->wormHead.xCoord + j] == 'e') {
					allWormMoves.push_back(new WormMove(this->wormHead.yCoord + i, this->wormHead.xCoord + j, this->wormIndex, true));
				}
				if (this->wormTail.xCoord + j >= 0 && this->wormTail.xCoord + j  < puzzleGrid[this->wormTail.yCoord].size() && this->wormTail.yCoord + i >= 0 && 
					this->wormTail.yCoord + i < puzzleGrid.size() && puzzleGrid[this->wormTail.yCoord + i][this->wormTail.xCoord + j] == 'e') {
					allWormMoves.push_back(new WormMove(this->wormTail.yCoord + i, this->wormTail.xCoord + j, this->wormIndex, false));
				}
			}
		}
	}
}

//Creating the move of a certain wriggle worm's head or tail
vector<vector<char>> WriggleWorm::newMovePuzzle(const vector<vector<char>> &puzzleGrid, const WormMove *wormMove) {
	vector<vector<char>> newPuzzleGrid(puzzleGrid);
	WriggleWorm newWriggleWorm = WriggleWorm(*this);

	//If the head is moving
	if (wormMove->isHead == 1) {
		newPuzzleGrid[wormMove->yCoord][wormMove->xCoord] = this->wormHead.direction;
		newWriggleWorm.wormHead.xCoord = wormMove->xCoord;
		newWriggleWorm.wormHead.yCoord = wormMove->yCoord;

		//If there is a body within the worm (other than the head and tail)
		if (this->wormBody.size() > 0) {
			for (int i = (this->wormBody.size() - 1); i >= 0; i--) {
				if (i == (this->wormBody.size() - 1)) {
					newPuzzleGrid[this->wormHead.yCoord][this->wormHead.xCoord] = this->wormBody[i].direction;
					newWriggleWorm.wormBody[i].xCoord = this->wormHead.xCoord;
					newWriggleWorm.wormBody[i].yCoord = this->wormHead.yCoord;
				} else {
					newPuzzleGrid[this->wormBody[i + 1].yCoord][this->wormBody[i + 1].xCoord] = this->wormBody[i].direction;
					newWriggleWorm.wormBody[i].xCoord = this->wormBody[i + 1].xCoord;
					newWriggleWorm.wormBody[i].yCoord = this->wormBody[i + 1].yCoord;
				}
			}
			newPuzzleGrid[this->wormBody[0].yCoord][this->wormBody[0].xCoord] = this->wormTail.direction;
			newWriggleWorm.wormTail.xCoord = this->wormBody[0].xCoord;
			newWriggleWorm.wormTail.yCoord = this->wormBody[0].yCoord;

		//Otherwise just move the head and at this point move the tail where the head was.
		} else {
			newPuzzleGrid[this->wormHead.yCoord][this->wormHead.xCoord] = this->wormTail.direction;
			newWriggleWorm.wormTail.xCoord = this->wormHead.xCoord;
			newWriggleWorm.wormTail.yCoord = this->wormHead.yCoord;
		}
		newPuzzleGrid[this->wormTail.yCoord][this->wormTail.xCoord] = 'e';

	//If move is beginning with tail.
	} else {
		newPuzzleGrid[wormMove->yCoord][wormMove->xCoord] = this->wormTail.direction;
		newWriggleWorm.wormTail.xCoord = wormMove->xCoord;
		newWriggleWorm.wormTail.yCoord = wormMove->yCoord;

		//If there is a body within the worm (other than the head and tail)
		if (this->wormBody.size() > 0) {
			for (int i = 0; i < this->wormBody.size(); i++) {
				if (i == 0) {
					newPuzzleGrid[this->wormTail.yCoord][this->wormTail.xCoord] = this->wormBody[i].direction;
					newWriggleWorm.wormBody[i].xCoord = this->wormTail.xCoord;
					newWriggleWorm.wormBody[i].yCoord = this->wormTail.yCoord;
				} else {
					newPuzzleGrid[this->wormBody[i - 1].yCoord][this->wormBody[i - 1].xCoord] = this->wormBody[i].direction;
					newWriggleWorm.wormBody[i].xCoord = this->wormBody[i - 1].xCoord;
					newWriggleWorm.wormBody[i].yCoord = this->wormBody[i - 1].yCoord;
				}
			}
			newPuzzleGrid[this->wormBody[this->wormBody.size() - 1].yCoord][this->wormBody[this->wormBody.size() - 1].xCoord] = this->wormHead.direction;
			newWriggleWorm.wormHead.xCoord = this->wormBody[this->wormBody.size() - 1].xCoord;
			newWriggleWorm.wormHead.yCoord = this->wormBody[this->wormBody.size() - 1].yCoord;

		//Otherwise just move the tail and at this point move the head where the head was.
		} else {
			newPuzzleGrid[this->wormTail.yCoord][this->wormTail.xCoord] = this->wormHead.direction;
			newWriggleWorm.wormHead.xCoord = this->wormTail.xCoord;
			newWriggleWorm.wormHead.yCoord = this->wormTail.yCoord;
		}
		newPuzzleGrid[this->wormHead.yCoord][this->wormHead.xCoord] = 'e';
	}

	//Fixing the direction of the worm to all go towards the tail.

	//If there is a body (other than head and tail)
	if (newWriggleWorm.wormBody.size() > 0) {

		//Loop through body.
		for (int i = 0; i < newWriggleWorm.wormBody.size(); i++) {
			if (i == 0) {

				//If first body piece attached to tail.
				if (newWriggleWorm.wormBody[i].xCoord == newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord < newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = 'v';

				} else if (newWriggleWorm.wormBody[i].xCoord == newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord > newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '^';

				} else if (newWriggleWorm.wormBody[i].xCoord < newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord == newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '>';

				} else if (newWriggleWorm.wormBody[i].xCoord > newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord == newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '<';

				}

				//All other body pieces (from body to body)
			} else {
				if (newWriggleWorm.wormBody[i].xCoord == newWriggleWorm.wormBody[i - 1].xCoord && newWriggleWorm.wormBody[i].yCoord < newWriggleWorm.wormBody[i - 1].yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = 'v';

				} else if (newWriggleWorm.wormBody[i].xCoord == newWriggleWorm.wormBody[i - 1].xCoord && newWriggleWorm.wormBody[i].yCoord > newWriggleWorm.wormBody[i - 1].yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '^';

				} else if (newWriggleWorm.wormBody[i].xCoord < newWriggleWorm.wormBody[i - 1].xCoord && newWriggleWorm.wormBody[i].yCoord == newWriggleWorm.wormBody[i - 1].yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '>';

				} else if (newWriggleWorm.wormBody[i].xCoord > newWriggleWorm.wormBody[i - 1].xCoord && newWriggleWorm.wormBody[i].yCoord == newWriggleWorm.wormBody[i - 1].yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '<';

				}
			}
		}

		//Fix the direction of the head
		if (newWriggleWorm.wormHead.xCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord < newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'D';

		} else if (newWriggleWorm.wormHead.xCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord > newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'U';

		} else if (newWriggleWorm.wormHead.xCoord < newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'R';

		} else if (newWriggleWorm.wormHead.xCoord > newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'L';

		}

	//If no body just fix the direction of the Head directly towards the tail.
	} else {
		if (newWriggleWorm.wormHead.xCoord == newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormHead.yCoord < newWriggleWorm.wormTail.yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'D';
			newPuzzleGrid[newWriggleWorm.wormTail.yCoord][newWriggleWorm.wormTail.xCoord] = this->wormTail.direction;

		} else if (newWriggleWorm.wormHead.xCoord == newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormHead.yCoord > newWriggleWorm.wormTail.yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'U';
			newPuzzleGrid[newWriggleWorm.wormTail.yCoord][newWriggleWorm.wormTail.xCoord] = this->wormTail.direction;

		} else if (newWriggleWorm.wormHead.xCoord < newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormHead.yCoord == newWriggleWorm.wormTail.yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'R';
			newPuzzleGrid[newWriggleWorm.wormTail.yCoord][newWriggleWorm.wormTail.xCoord] = this->wormTail.direction;

		} else if (newWriggleWorm.wormHead.xCoord > newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormHead.yCoord == newWriggleWorm.wormTail.yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'L';
			newPuzzleGrid[newWriggleWorm.wormTail.yCoord][newWriggleWorm.wormTail.xCoord] = this->wormTail.direction;

		}
	}

	return newPuzzleGrid;
}

//If the goal is found return true.
bool WriggleWorm::isGoal() {
	return ((this->wormHead.xCoord == goalX && this->wormHead.yCoord == goalY) || (this->wormTail.xCoord == goalX && this->wormTail.yCoord == goalY));
}

//To allow printing of the puzzle (or outputting to the file).
ostream& operator<<(ostream& out, const vector<vector<char>> &puzzleGrid) {
	for (vector<vector<char>>::const_iterator i = puzzleGrid.begin(); i != puzzleGrid.end(); ++i) {
		for (vector<char>::const_iterator j = i->begin(); j != i->end(); ++j) {
			out << *j << ' ';
		}
		out << endl;
	}

	return out;
}