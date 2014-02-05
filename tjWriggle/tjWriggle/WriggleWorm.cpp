#include "WriggleWorm.h"


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

				wormTail = WormPiece(bodyPieceYCount, bodyPieceXCount, currentBodyPiece);

				while ('U' != currentBodyPiece && 'D' != currentBodyPiece && 'R' != currentBodyPiece && 'L' != currentBodyPiece) {
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

char WriggleWorm::allPossibleMoves(const vector<vector<char>> &puzzleGrid, vector<WormMove*> &allWormMoves) {
	if (this->wormHead.xCoord - 1 >= 0 && puzzleGrid[this->wormHead.yCoord][this->wormHead.xCoord - 1] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormHead.yCoord, this->wormHead.xCoord - 1, this->wormIndex, true));

	}
	if (this->wormHead.xCoord + 1 < puzzleGrid[this->wormHead.yCoord].size() && puzzleGrid[this->wormHead.yCoord][this->wormHead.xCoord + 1] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormHead.yCoord, this->wormHead.xCoord + 1, this->wormIndex, true));

	}
	if (this->wormHead.yCoord - 1 >= 0 && puzzleGrid[this->wormHead.yCoord - 1][this->wormHead.xCoord] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormHead.yCoord - 1, this->wormHead.xCoord, this->wormIndex, true));

	}
	if (this->wormHead.yCoord + 1 < puzzleGrid.size() && puzzleGrid[this->wormHead.yCoord + 1][this->wormHead.xCoord] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormHead.yCoord + 1, this->wormHead.xCoord, this->wormIndex, true));

	}
	if (this->wormTail.xCoord - 1 >= 0 && puzzleGrid[this->wormTail.yCoord][this->wormTail.xCoord - 1] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormTail.yCoord, this->wormTail.xCoord - 1, this->wormIndex, false));

	}
	if (this->wormTail.xCoord + 1 < puzzleGrid[this->wormTail.yCoord].size() && puzzleGrid[this->wormTail.yCoord][this->wormTail.xCoord + 1] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormTail.yCoord, this->wormTail.xCoord + 1, this->wormIndex, false));

	}
	if (this->wormTail.yCoord - 1 >= 0 && puzzleGrid[this->wormTail.yCoord - 1][this->wormTail.xCoord] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormTail.yCoord - 1, this->wormTail.xCoord, this->wormIndex, false));

	}
	if (this->wormTail.yCoord + 1 < puzzleGrid.size() && puzzleGrid[this->wormTail.yCoord + 1][this->wormTail.xCoord] == 'e') {
		allWormMoves.push_back(new WormMove(this->wormTail.yCoord + 1, this->wormTail.xCoord, this->wormIndex, false));

	}
	return 0;
}

vector<vector<char>> WriggleWorm::newMovePuzzle(const vector<vector<char>> &puzzleGrid, const WormMove &wormMove) {
	vector<vector<char>> newPuzzleGrid(puzzleGrid);
	WriggleWorm newWriggleWorm = WriggleWorm(*this);
	if (wormMove.isHead == 1) {
		newPuzzleGrid[wormMove.yCoord][wormMove.xCoord] = this->wormHead.direction;
		newWriggleWorm.wormHead.xCoord = wormMove.xCoord;
		newWriggleWorm.wormHead.yCoord = wormMove.yCoord;
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
		} else {
			newWriggleWorm.wormTail.xCoord = this->wormHead.xCoord;
			newWriggleWorm.wormTail.yCoord = this->wormHead.yCoord;
		}
		newPuzzleGrid[this->wormTail.yCoord][this->wormTail.xCoord] = 'e';
	} else {
		newPuzzleGrid[wormMove.yCoord][wormMove.xCoord] = this->wormTail.direction;
		newWriggleWorm.wormTail.xCoord = wormMove.xCoord;
		newWriggleWorm.wormTail.yCoord = wormMove.yCoord;
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
		} else {
			newWriggleWorm.wormHead.xCoord = this->wormTail.xCoord;
			newWriggleWorm.wormHead.yCoord = this->wormTail.yCoord;
		}
		newPuzzleGrid[this->wormHead.yCoord][this->wormHead.xCoord] = 'e';
	}

	if (newWriggleWorm.wormBody.size() > 0) {
		for (int i = 0; i < newWriggleWorm.wormBody.size(); i++) {
			if (i == 0) {
				if (newWriggleWorm.wormBody[i].xCoord == newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord < newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = 'v';

				} else if (newWriggleWorm.wormBody[i].xCoord == newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord > newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '^';

				} else if (newWriggleWorm.wormBody[i].xCoord < newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord == newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '>';

				} else if (newWriggleWorm.wormBody[i].xCoord > newWriggleWorm.wormTail.xCoord && newWriggleWorm.wormBody[i].yCoord == newWriggleWorm.wormTail.yCoord) {
					newPuzzleGrid[newWriggleWorm.wormBody[i].yCoord][newWriggleWorm.wormBody[i].xCoord] = '<';

				}
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
		if (newWriggleWorm.wormHead.xCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord < newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'D';

		} else if (newWriggleWorm.wormHead.xCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord > newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'U';

		} else if (newWriggleWorm.wormHead.xCoord < newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'R';

		} else if (newWriggleWorm.wormHead.xCoord > newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].xCoord && newWriggleWorm.wormHead.yCoord == newWriggleWorm.wormBody[newWriggleWorm.wormBody.size() - 1].yCoord) {
			newPuzzleGrid[newWriggleWorm.wormHead.yCoord][newWriggleWorm.wormHead.xCoord] = 'L';

		}
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

bool WriggleWorm::isGoal() {
	return ((this->wormHead.xCoord == goalX && this->wormHead.yCoord == goalY) || (this->wormTail.xCoord == goalX && this->wormTail.yCoord == goalY));
}

void WriggleWorm::printPuzzle(const vector<vector<char>> &puzzleGrid) {
	for (vector<vector<char>>::const_iterator i = puzzleGrid.begin(); i != puzzleGrid.end(); ++i) {
		for (vector<char>::const_iterator j = i->begin(); j != i->end(); ++j) {
			cout << *j << ' ';
		}
		cout << endl;
	}
}