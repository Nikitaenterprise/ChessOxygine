#pragma once
#include "oxygine-framework.h"
#include "ox/oxygine.hpp"
#include "ox/Stage.hpp"
#include "ox/DebugActor.hpp"

#include <iostream>
#include <vector>
#include "Element.h"
#include "Field.h"
#include "Figure.h"

#define HEIGHT 800
#define WIDTH 800

class Game
{
public:
	Game(const Game &) = delete;
	Game & operator=(const Game &) = delete;
	Game();
	~Game();

	//void run(int minimumFramePerSeconds = 60);
	std::string getBoardElement(int i, int j) { return _board[j][i]; };
	Figure & getBoardFigure(int i, int j);
	void setBoardElement(int i, int j, std::string &str) { _board[j][i] = str; };
	void deleteFigure(Figure  *figure);
	void update();
	//void printBoard();

	//void setUp(ox::Stage stage) { instance = &stage; };

	ox::Resources res;
	Game *_thisGame = this;
	std::string _board[8][8] =
	{
		{ "wcastle", "wknight", "wbishop", "wqueen", "wking", "wbishop", "wknight", "wcastle" },
		{ "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" },
		{ "bcastle", "bknight", "bbishop", "bqueen", "bking", "bbishop", "bknight", "bcastle" },
	};

	//ox::spStage instance;
private:
	void processEvents();
	void render();
	Field _field;
	std::vector<Figure*> _figures;
};