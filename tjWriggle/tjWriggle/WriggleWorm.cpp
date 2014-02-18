#include "WriggleWorm.h"

boost::unordered_map<pair<char, char>, char> WriggleWorm::directionMap = WriggleWorm::populateMap();
boost::unordered_map<pair<char, char>, char> WriggleWorm::headDirectionMap = WriggleWorm::populateHeadMap();

//Creating wriggle worm to identify with as a wriggle worm within the puzzle.
WriggleWorm::WriggleWorm(const vecChar &puzzleGrid, char wriggleIndex) {
	wormIndex = wriggleIndex;
	goalX = puzzleGrid[0].size() - 1;
	goalY = puzzleGrid.size() - 1;
	for (vecChar::const_iterator i = puzzleGrid.begin(); i != puzzleGrid.end(); ++i) {
		for (vector<char>::const_iterator j = i->begin(); j != i->end(); ++j) {
			if (wriggleIndex == *j) {
				char currentBodyPiece = *j;
				char bodyPieceYCount = i - puzzleGrid.begin();
				char bodyPieceXCount = j - i->begin();

				//Initializes the tail as this is where the worm is starting
				wormTail = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);

				//While not reaching the head of the worm

				while ('U' != currentBodyPiece && 'D' != currentBodyPiece && 'R' != currentBodyPiece && 'L' != currentBodyPiece) {
					/*bool breaker = false;
					for (int k = -1; k <= 1; k++) {
						for (int l = -1; l <= 1; l++) {
							if (!(k == l) && k == 0 || l == 0) {
								if (bodyPieceXCount + l >= 0 && bodyPieceXCount + l < puzzleGrid[bodyPieceYCount].size() && 
									bodyPieceYCount + k >= 0 && bodyPieceYCount + k < puzzleGrid.size()) {
									if (puzzleGrid[bodyPieceYCount + k][bodyPieceXCount + l] == directionMap[{ l, k }]) {
										currentBodyPiece = puzzleGrid[bodyPieceYCount + k][bodyPieceXCount + l];
										bodyPieceXCount = bodyPieceXCount + l;
										bodyPieceYCount = bodyPieceYCount + k;
										wormBody.push_back(WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece));
										breaker = true;
										break;
									} else if (puzzleGrid[bodyPieceYCount + k][bodyPieceXCount + l] == headDirectionMap[{ l, k }]) {
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
						if (breaker == true) { break; }
					}*/

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
void WriggleWorm::allPossibleMoves(const vecChar &puzzleGrid, vector<WormMove*> &allWormMoves) {
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
vecChar* WriggleWorm::newMovePuzzle(vecChar* puzzleGrid, const WormMove *wormMove, const WriggleWorm oldWriggleWorm) {
	vecChar* newPuzzleGrid = new vecChar(*puzzleGrid);
	//If the head is moving
	if (wormMove->isHead == 1) {
		(*newPuzzleGrid)[wormMove->yCoord][wormMove->xCoord] = oldWriggleWorm.wormHead.direction;
		this->wormHead.xCoord = wormMove->xCoord;
		this->wormHead.yCoord = wormMove->yCoord;

		//If there is a body within the worm (other than the head and tail)
		if (oldWriggleWorm.wormBody.size() > 0) {
			for (int i = (oldWriggleWorm.wormBody.size() - 1); i >= 0; i--) {
				if (i == (oldWriggleWorm.wormBody.size() - 1)) {
					(*newPuzzleGrid)[oldWriggleWorm.wormHead.yCoord][oldWriggleWorm.wormHead.xCoord] = oldWriggleWorm.wormBody[i].direction;
					this->wormBody[i].xCoord = oldWriggleWorm.wormHead.xCoord;
					this->wormBody[i].yCoord = oldWriggleWorm.wormHead.yCoord;
				} else {
					(*newPuzzleGrid)[oldWriggleWorm.wormBody[i + 1].yCoord][oldWriggleWorm.wormBody[i + 1].xCoord] = oldWriggleWorm.wormBody[i].direction;
					this->wormBody[i].xCoord = oldWriggleWorm.wormBody[i + 1].xCoord;
					this->wormBody[i].yCoord = oldWriggleWorm.wormBody[i + 1].yCoord;
				}
			}
			(*newPuzzleGrid)[oldWriggleWorm.wormBody[0].yCoord][oldWriggleWorm.wormBody[0].xCoord] = oldWriggleWorm.wormTail.direction;
			this->wormTail.xCoord = oldWriggleWorm.wormBody[0].xCoord;
			this->wormTail.yCoord = oldWriggleWorm.wormBody[0].yCoord;

		//Otherwise just move the head and at this point move the tail where the head was.
		} else {
			(*newPuzzleGrid)[oldWriggleWorm.wormHead.yCoord][oldWriggleWorm.wormHead.xCoord] = oldWriggleWorm.wormTail.direction;
			this->wormTail.xCoord = oldWriggleWorm.wormHead.xCoord;
			this->wormTail.yCoord = oldWriggleWorm.wormHead.yCoord;
		}
		(*newPuzzleGrid)[oldWriggleWorm.wormTail.yCoord][oldWriggleWorm.wormTail.xCoord] = 'e';

	//If move is beginning with tail.
	} else {
		(*newPuzzleGrid)[wormMove->yCoord][wormMove->xCoord] = oldWriggleWorm.wormTail.direction;
		this->wormTail.xCoord = wormMove->xCoord;
		this->wormTail.yCoord = wormMove->yCoord;

		//If there is a body within the worm (other than the head and tail)
		if (oldWriggleWorm.wormBody.size() > 0) {
			for (int i = 0; i < oldWriggleWorm.wormBody.size(); i++) {
				if (i == 0) {
					(*newPuzzleGrid)[oldWriggleWorm.wormTail.yCoord][oldWriggleWorm.wormTail.xCoord] = oldWriggleWorm.wormBody[i].direction;
					this->wormBody[i].xCoord = oldWriggleWorm.wormTail.xCoord;
					this->wormBody[i].yCoord = oldWriggleWorm.wormTail.yCoord;
				} else {
					(*newPuzzleGrid)[oldWriggleWorm.wormBody[i - 1].yCoord][oldWriggleWorm.wormBody[i - 1].xCoord] = oldWriggleWorm.wormBody[i].direction;
					this->wormBody[i].xCoord = oldWriggleWorm.wormBody[i - 1].xCoord;
					this->wormBody[i].yCoord = oldWriggleWorm.wormBody[i - 1].yCoord;
				}
			}
			(*newPuzzleGrid)[oldWriggleWorm.wormBody[oldWriggleWorm.wormBody.size() - 1].yCoord][oldWriggleWorm.wormBody[oldWriggleWorm.wormBody.size() - 1].xCoord] = oldWriggleWorm.wormHead.direction;
			this->wormHead.xCoord = oldWriggleWorm.wormBody[oldWriggleWorm.wormBody.size() - 1].xCoord;
			this->wormHead.yCoord = oldWriggleWorm.wormBody[oldWriggleWorm.wormBody.size() - 1].yCoord;

		//Otherwise just move the tail and at this point move the head where the head was.
		} else {
			(*newPuzzleGrid)[oldWriggleWorm.wormTail.yCoord][oldWriggleWorm.wormTail.xCoord] = oldWriggleWorm.wormHead.direction;
			this->wormHead.xCoord = oldWriggleWorm.wormTail.xCoord;
			this->wormHead.yCoord = oldWriggleWorm.wormTail.yCoord;
		}
		(*newPuzzleGrid)[oldWriggleWorm.wormHead.yCoord][oldWriggleWorm.wormHead.xCoord] = 'e';
	}

	//Fixing the direction of the worm to all go towards the tail.

	//If there is a body (other than head and tail)
	if (this->wormBody.size() > 0) {

		//Loop through body.
		for (int i = 0; i < this->wormBody.size(); i++) {
			if (i == 0) {

				//If first body piece attached to tail.
				if (this->wormBody[i].xCoord == this->wormTail.xCoord && this->wormBody[i].yCoord < this->wormTail.yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = 'v';
					this->wormBody[i].direction = 'v';

				} else if (this->wormBody[i].xCoord == this->wormTail.xCoord && this->wormBody[i].yCoord > this->wormTail.yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = '^';
					this->wormBody[i].direction = '^';

				} else if (this->wormBody[i].xCoord < this->wormTail.xCoord && this->wormBody[i].yCoord == this->wormTail.yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = '>';
					this->wormBody[i].direction = '>';

				} else if (this->wormBody[i].xCoord > this->wormTail.xCoord && this->wormBody[i].yCoord == this->wormTail.yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = '<';
					this->wormBody[i].direction = '<';

				}

				//All other body pieces (from body to body)
			} else {
				if (this->wormBody[i].xCoord == this->wormBody[i - 1].xCoord && this->wormBody[i].yCoord < this->wormBody[i - 1].yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = 'v';
					this->wormBody[i].direction = 'v';

				} else if (this->wormBody[i].xCoord == this->wormBody[i - 1].xCoord && this->wormBody[i].yCoord > this->wormBody[i - 1].yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = '^';
					this->wormBody[i].direction = '^';

				} else if (this->wormBody[i].xCoord < this->wormBody[i - 1].xCoord && this->wormBody[i].yCoord == this->wormBody[i - 1].yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = '>';
					this->wormBody[i].direction = '>';

				} else if (this->wormBody[i].xCoord > this->wormBody[i - 1].xCoord && this->wormBody[i].yCoord == this->wormBody[i - 1].yCoord) {
					(*newPuzzleGrid)[this->wormBody[i].yCoord][this->wormBody[i].xCoord] = '<';
					this->wormBody[i].direction = '<';

				}
			}
		}

		//Fix the direction of the head
		if (this->wormHead.xCoord == this->wormBody[this->wormBody.size() - 1].xCoord && this->wormHead.yCoord < this->wormBody[this->wormBody.size() - 1].yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'D';
			this->wormHead.direction = 'D';

		} else if (this->wormHead.xCoord == this->wormBody[this->wormBody.size() - 1].xCoord && this->wormHead.yCoord > this->wormBody[this->wormBody.size() - 1].yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'U';
			this->wormHead.direction = 'U';

		} else if (this->wormHead.xCoord < this->wormBody[this->wormBody.size() - 1].xCoord && this->wormHead.yCoord == this->wormBody[this->wormBody.size() - 1].yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'R';
			this->wormHead.direction = 'R';

		} else if (this->wormHead.xCoord > this->wormBody[this->wormBody.size() - 1].xCoord && this->wormHead.yCoord == this->wormBody[this->wormBody.size() - 1].yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'L';
			this->wormHead.direction = 'L';

		}

	//If no body just fix the direction of the Head directly towards the tail.
	} else {
		if (this->wormHead.xCoord == this->wormTail.xCoord && this->wormHead.yCoord < this->wormTail.yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'D';
			this->wormHead.direction = 'D';
			(*newPuzzleGrid)[this->wormTail.yCoord][this->wormTail.xCoord] = oldWriggleWorm.wormTail.direction;
			this->wormTail.direction = oldWriggleWorm.wormTail.direction;

		} else if (this->wormHead.xCoord == this->wormTail.xCoord && this->wormHead.yCoord > this->wormTail.yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'U';
			this->wormHead.direction = 'U';
			(*newPuzzleGrid)[this->wormTail.yCoord][this->wormTail.xCoord] = oldWriggleWorm.wormTail.direction;
			this->wormTail.direction = oldWriggleWorm.wormTail.direction;

		} else if (this->wormHead.xCoord < this->wormTail.xCoord && this->wormHead.yCoord == this->wormTail.yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'R';
			this->wormHead.direction = 'R';
			(*newPuzzleGrid)[this->wormTail.yCoord][this->wormTail.xCoord] = oldWriggleWorm.wormTail.direction;
			this->wormTail.direction = oldWriggleWorm.wormTail.direction;

		} else if (this->wormHead.xCoord > this->wormTail.xCoord && this->wormHead.yCoord == this->wormTail.yCoord) {
			(*newPuzzleGrid)[this->wormHead.yCoord][this->wormHead.xCoord] = 'L';
			this->wormHead.direction = 'L';
			(*newPuzzleGrid)[this->wormTail.yCoord][this->wormTail.xCoord] = oldWriggleWorm.wormTail.direction;
			this->wormTail.direction = oldWriggleWorm.wormTail.direction;

		}
	}

	return newPuzzleGrid;
}

//If the goal is found return true.
bool WriggleWorm::isGoal() {
	return ((this->wormHead.xCoord == goalX && this->wormHead.yCoord == goalY) || (this->wormTail.xCoord == goalX && this->wormTail.yCoord == goalY));
}

//To allow printing of the puzzle (or outputting to the file).
ostream& operator<<(ostream& out, const vecChar &puzzleGrid) {
	for (vecChar::const_iterator i = puzzleGrid.begin(); i != puzzleGrid.end(); ++i) {
		for (vector<char>::const_iterator j = i->begin(); j != i->end(); ++j) {
			out << *j << ' ';
		}
		out << endl;
	}

	return out;
}