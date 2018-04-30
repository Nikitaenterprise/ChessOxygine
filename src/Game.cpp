#include "Game.h"

Game::Game(ox::spStage stage)
{
	_thisStage = stage;

	res.loadXML("res.xml");

	class
	{
	public:
		char *startPosition[8][8] =
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
		void operator()(ox::Point &pos, std::string &name)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (startPosition[i][j] == "empty") continue;
					if (startPosition[i][j] == name)
					{
						pos.x = j;
						pos.y = i;
						startPosition[i][j] = "empty";
						goto breakLoop;
					}
				}
			}
		breakLoop:
			return;
		};

		void setFigure(std::vector<Figure*> &_figures, std::string &name, std::string &color, ox::Point &pos, int &k, Game *ptr)
		{
			_figures.push_back(new Figure(name, color, ptr));
			//_figures[k]->setGamePtr(ptr);
			(*this)(pos, color + name);
			ox::logs::message("pos: '%i', '%i'\n", pos.x, pos.y);
			ox::Vector2 tmp(800 / 8 * pos.x, 800 / 8 * pos.y);
			ox::logs::message("tmp: '%f', '%f'\n", tmp.x, tmp.y);
			_figures[k]->setPosition(tmp);
			pos.setZero();
			tmp.setZero();
			k++;
		};
	} getStartCoord;

	int k = 0;
	ox::Point pos;
	std::vector<std::string> figuresName = { "pawn", "castle", "knight", "bishop", "queen", "king" };
	std::vector<std::string> figuresColor = { "w", "b" };
	for (auto &color : figuresColor)
	{
		for (auto &name : figuresName)
		{
			if (name == "pawn")
				for (int l = 0; l < 8; l++)	getStartCoord.setFigure(_figures, name, color, pos, k, this);
			else if (name == "king" || name == "queen") getStartCoord.setFigure(_figures, name, color, pos, k, this);
			else if (name == "castle" || name == "knight" || name == "bishop")
				for (int l = 0; l < 2; l++)	getStartCoord.setFigure(_figures, name, color, pos, k, this);
		}
	}
	//for (auto &obj : _figures) obj->setGamePtr(this);
	res.print();
}

Game::~Game()
{

}

Figure & Game::getBoardFigure(int i, int j)
{
	for (const auto &obj : _figures)
	{
		if (static_cast<int>(obj->_oldPos.x / 100) == i && static_cast<int>(obj->_oldPos.y / 100) == j)
			return *obj;
	}
}

void Game::deleteFigure(Figure  *figure)
{
	_figures.erase(std::remove(_figures.begin(), _figures.end(), figure), _figures.end());
	figure->~Figure();
}

void Game::update()
{
	for (const auto obj : _figures)	obj->update();
}
