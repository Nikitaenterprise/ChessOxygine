#include "Figure.h"
#include "Game.h"

Figure::Figure(const std::string &name, const std::string &color, Game *ptr)
{
	_name = name;
	_color = color;
	_thisGame = ptr;
	_sprite = new ox::Sprite();
	_sprite->setResAnim(_thisGame->res.getResAnim(_color + _name));
	_sprite->setScale(float(100 / _sprite->getSize().x), float(100 / _sprite->getSize().y));
	_sprite->attachTo(ox::getStage());

	//DEBUG sprite
	DEBUGSprite = new ox::ColorRectSprite();
	DEBUGSprite->setSize(10, 10);
	DEBUGSprite->setPosition(_sprite->getAnchor());
	DEBUGSprite->setColor(ox::Color(0, 0, 0, 255));
	DEBUGSprite->attachTo(ox::getStage());

	_sprite->addEventListener(ox::TouchEvent::TOUCH_DOWN, CLOSURE(this, &Figure::processEvents));
	_sprite->addEventListener(ox::TouchEvent::TOUCH_UP, CLOSURE(this, &Figure::processEvents));
	_sprite->addEventListener(ox::TouchEvent::MOVE, CLOSURE(this, &Figure::processEvents));
	_thisGame->_thisStage->addEventListener(ox::TouchEvent::MOVE, CLOSURE(this, &Figure::processCursorPos));
}

void Figure::processCursorPos(ox::Event *event)
{
	if (isMove)
	{
		cursorPos.setZero();
		ox::TouchEvent *touch = (ox::TouchEvent*)event;
		cursorPos = touch->localPosition;
		ox::logs::messageln("processEvents000 locPos:'%f', '%f'", cursorPos.x, cursorPos.y);
		dPos.setZero();
		dPos = cursorPos - pos - ox::Vector2(_sprite->getWidth()/2, _sprite->getHeight()/2);
		ox::logs::messageln("processEvents locPos:'%f', '%f'", cursorPos.x, cursorPos.y);
		ox::logs::messageln("processEvents dPos:'%f', '%f'", dPos.x, dPos.y);
		ox::logs::messageln("processEvents pos:'%f', '%f'", pos.x, pos.y);
	}
}

void Figure::processEvents(ox::Event *event)
{
	if (event->type == ox::TouchEvent::TOUCH_DOWN && !isMove)
	{
		ox::logs::messageln("clickDown");
		_oldPos = _sprite->getPosition();
		isMove = true;
	}
	if (event->type == ox::TouchEvent::TOUCH_UP && isMove)
	{
		ox::logs::messageln("clickUp");
		int i = int(cursorPos.x) / 100, j = int(cursorPos.y) / 100;
		ox::logs::messageln("i,j: '%i', '%i'", i, j);
		ox::logs::messageln("\n");
		ox::logs::messageln("oldPos: %f, %f", _oldPos.x, _oldPos.y);
		ox::logs::messageln("curPos: %f, %f", pos.x, pos.y);
		if (canMoveHere(i, j))
		{
			ox::logs::messageln("canMove");
			move(i, j);
		}
		else _sprite->setPosition(_oldPos);
		isMove = false;
	}
}

void Figure::update()
{
	if (isMove)
	{
		pos += dPos;
		ox::logs::messageln("from Update dPos:'%f', '%f'", dPos.x, dPos.y);
		ox::logs::messageln("from Update Pos:'%f', '%f'", pos.x, pos.y);
		_sprite->setPosition(pos);
		dPos.setZero();
	}
}

void Figure::move(int i, int j)
{
	ox::logs::messageln("boardElement: '%s'", _thisGame->getBoardElement(i, j).c_str());
	if (_thisGame->getBoardElement(i, j).front() == _color.front())
	{
		_sprite->setPosition(_oldPos);
	}
	if (_thisGame->getBoardElement(i, j).front() != _color.front()
		&& _thisGame->getBoardElement(i, j) != "empty")
	{
		_thisGame->setBoardElement(int(_oldPos.x / 100), int(_oldPos.y / 100), std::string("empty"));
		_thisGame->deleteFigure(&_thisGame->getBoardFigure(i, j));
		_thisGame->setBoardElement(i, j, std::string("empty"));
	}
	if (_thisGame->getBoardElement(i, j) == "empty")
	{
		ox::logs::messageln("empty");
		_thisGame->setBoardElement(int(_oldPos.x / 100), int(_oldPos.y / 100), std::string("empty"));
		_sprite->setPosition(ox::Vector2(i * 100, j * 100));
		_newPos = _sprite->getPosition();
		_thisGame->setBoardElement(i, j, _color + _name);
	}
	isFirsTimeMoving = false;
	_oldPos = _sprite->getPosition();
}

bool Figure::canMoveHere(int i, int j)
{
	ox::logs::messageln("canMoveHere: %i, %i", i, j);
	enum line { horizontal, vertical, diagonalL, diagonalR };
	bool canMove = false;
	int colorVariable = 1;
	int iOld = static_cast<int> (_oldPos.x / 100);
	int jOld = static_cast<int> (_oldPos.y / 100);

	if (_color == "w") colorVariable *= -1;

	if (_name == "pawn")
	{
		ox::logs::messageln("pawn");
		ox::logs::messageln("%i, %i, %i, %i", i, j, iOld, jOld);
		if (isFirsTimeMoving && i - iOld == 0 && j - jOld == -2 * colorVariable)
		{
			ox::logs::messageln("pawn forward");
			isFirsTimeMoving = false;
			canMove = true;
		}
		if (i - iOld == 0 && j - jOld == -1 * colorVariable) canMove = true;
		if ((i - iOld == -1 * colorVariable || i - iOld == 1 * colorVariable)
			&& j - jOld == -1 * colorVariable)
		{
			ox::logs::messageln("pawn attack");
			if (_thisGame->getBoardElement(i, j) != "empty") canMove = true;
		}
	}
	if (_name == "king")
	{
		if ((i - iOld == 0 && j - jOld == -1 * colorVariable)
			|| (i - iOld == 1 * colorVariable && j - jOld == -1 * colorVariable)
			|| (i - iOld == 1 * colorVariable && j - jOld == 0)
			|| (i - iOld == 1 * colorVariable && j - jOld == 1 * colorVariable)
			|| (i - iOld == 0 && j - jOld == 1 * colorVariable)
			|| (i - iOld == -1 * colorVariable && j - jOld == 1 * colorVariable)
			|| (i - iOld == -1 * colorVariable && j - jOld == 0)
			|| (i - iOld == -1 * colorVariable && j - jOld == -1 * colorVariable)) canMove = true;

		switch (i)
		{
		case 2:
			if (isFirsTimeMoving && checkLine(i - 1, j, iOld, jOld, line::horizontal))
			{
				_thisGame->getBoardFigure(i - 2, j).move(i + 1, j);
				canMove = true;
			}
			break;
		case 6:
			if (isFirsTimeMoving && checkLine(i, j, iOld, jOld, line::horizontal))
			{
				_thisGame->getBoardFigure(i + 1, j).move(i - 1, j);
				canMove = true;
			}
			break;
		}
	}
	if (_name == "knight")
	{
		if ((i - iOld == 1 * colorVariable && j - jOld == -2 * colorVariable)
			|| (i - iOld == 2 * colorVariable && j - jOld == -1 * colorVariable)
			|| (i - iOld == 2 * colorVariable && j - jOld == 1 * colorVariable)
			|| (i - iOld == 1 * colorVariable && j - jOld == 2 * colorVariable)
			|| (i - iOld == -1 * colorVariable && j - jOld == 2 * colorVariable)
			|| (i - iOld == -2 * colorVariable && j - jOld == 1 * colorVariable)
			|| (i - iOld == -2 * colorVariable && j - jOld == -1 * colorVariable)
			|| (i - iOld == -1 * colorVariable && j - jOld == -2 * colorVariable)) canMove = true;
	}
	if (_name == "castle")
	{
		if (j - jOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::horizontal);
		}
		if (i - iOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::vertical);
		}
	}
	if (_name == "bishop")
	{
		if (i - iOld == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalL);
		}
		if (i - iOld == (j - jOld) * -1
			|| (i - iOld) * -1 == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalR);
		}
	}
	if (_name == "queen")
	{
		if (j - jOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::horizontal);
		}
		if (i - iOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::vertical);
		}
		if (i - iOld == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalL);
		}
		if (i - iOld == (j - jOld) * -1
			|| (i - iOld) * -1 == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalR);
		}
	}
	return canMove;
}

bool Figure::checkLine(int i, int j, int iOld, int jOld, int line)
{
	bool canMove = true;
	switch (line)
	{
	case 0:
		if (i < iOld)
		{
			for (int m = i + 1; m < iOld; m++)
			{
				if (_thisGame->getBoardElement(m, j) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		if (i > iOld)
		{
			for (int m = i - 1; m > iOld; m--)
			{
				if (_thisGame->getBoardElement(m, j) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		break;
	case 1:
		if (j < jOld)
		{
			for (int m = j + 1; m < jOld; m++)
			{
				if (_thisGame->getBoardElement(i, m) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		if (j > jOld)
		{
			for (int m = j - 1; m > jOld; m--)
			{
				if (_thisGame->getBoardElement(i, m) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		break;
	case 2:
		if (i < iOld && j < jOld)
		{
			for (int m = i + 1, n = j + 1; m < iOld && n < jOld; m++, n++)
			{
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		if (i > iOld && j > jOld)
		{
			for (int m = i - 1, n = j - 1; m > iOld && n > jOld; m--, n--)
			{
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		break;
	case 3:
		if (i < iOld && j > jOld)
		{
			for (int m = i + 1, n = j - 1; m < iOld && n > jOld; m++, n--)
			{
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		if (i > iOld && j < jOld)
		{
			for (int m = i - 1, n = j + 1; m > iOld && n < jOld; m--, n++)
			{
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		break;
	}
	return canMove;
}
