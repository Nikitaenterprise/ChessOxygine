#include "Figure.h"
#include "Game.h"

Figure::Figure(const std::string &name, const std::string &color, Game *ptr)
{
	_name = name;
	_color = color;
	_thisGame = ptr;
	_sprite = new ox::Sprite();
	_sprite->setResAnim(_thisGame->res.getResAnim(_color + _name));
	//_sprite->setResAnim(_thisGame->res.getResAnim("Chess_Sprite"));
	//_sprite->setScale(ox::Vector2(0.1, 0.1));
	_sprite->setScale(float(100 / _sprite->getSize().x), float(100 / _sprite->getSize().y));
	_sprite->attachTo(ox::getStage());

	//_sprite->addEventListener(ox::TouchEvent::CLICK, CLOSURE(this, &Figure::processEvents));
	_sprite->addEventListener(ox::TouchEvent::TOUCH_DOWN, CLOSURE(this, &Figure::processEvents));
	_sprite->addEventListener(ox::TouchEvent::TOUCH_UP, CLOSURE(this, &Figure::processEvents));
	_sprite->addEventListener(ox::TouchEvent::MOVE, CLOSURE(this, &Figure::processEvents));
	ox::getStage()->addEventListener(ox::TouchEvent::MOVE, CLOSURE(this, &Figure::processCursorPos));
}

void Figure::processCursorPos(ox::Event *event)
{
	if (this->isMove)
	{
		cursorPos.setZero();
		ox::TouchEvent *touch = (ox::TouchEvent*)event;
		cursorPos = ox::Vector2(touch->localPosition.x, touch->localPosition.y);
		ox::logs::messageln("processEvents000 locPos:'%f', '%f'", cursorPos.x, cursorPos.y);
		this->dPos = ox::Vector2(0, 0);
		this->dPos = cursorPos - this->pos -
			ox::Vector2(this->_sprite->getWidth(), this->_sprite->getHeight());
		ox::logs::messageln("processEvents locPos:'%f', '%f'", cursorPos.x, cursorPos.y);
		ox::logs::messageln("processEvents dPos:'%f', '%f'", dPos.x, dPos.y);
		ox::logs::messageln("processEvents pos:'%f', '%f'", pos.x, pos.y);
	}
}

void Figure::processEvents(ox::Event *event)
{
	if (event->type == ox::TouchEvent::TOUCH_DOWN && !this->isMove)
	{
		ox::logs::messageln("clickDown");
		this->_oldPos = this->_sprite->getPosition();
		this->isMove = true;
	}
	if (event->type == ox::TouchEvent::TOUCH_UP && this->isMove)
	{
		ox::logs::messageln("clickUp");
		//changeColor(this, sf::Color::White);
		int i = int(cursorPos.x) / 100, j = int(cursorPos.y) / 100;
		ox::logs::messageln("i,j: '%i', '%i'", i, j);
		if (canMoveHere(i, j))
		{
			ox::logs::messageln("canMove");

			move(i, j);
		}
		else this->_sprite->setPosition(this->_oldPos.x, this->_oldPos.y);
		//ox::spTween tween = _sprite->addTween(ox::Actor::TweenPosition(_sprite->getPosition().x, _sprite->getPosition().y), 100);
		//_thisGame->printBoard();
		this->isMove = false;
	}
	//if (event->type == ox::TouchEvent::MOVE && this->isMove)
	//{
	//	ox::logs::messageln("move");
	//	this->dPos = ox::Vector2(0, 0);
	//	//ox::TouchEvent *touchOnSprite = (ox::TouchEvent*)event;
	//	//ox::TouchEvent *touchOnStage;

	//	/*ox::Vector2 locPos;
	//	ox::getStage()->addEventListener(ox::TouchEvent::MOVE, [&](ox::Event* ev)
	//	{
	//		if (this->isMove)
	//		{
	//			locPos.setZero();
	//			ox::TouchEvent *touch = (ox::TouchEvent*)ev;
	//			locPos = ox::Vector2(touch->localPosition.x, touch->localPosition.y);
	//		}
	//		ox::logs::messageln("processEvents000 locPos:'%f', '%f'", locPos.x, locPos.y);
	//	});*/

	//	this->dPos = cursorPos - this->pos -
	//		ox::Vector2(this->_sprite->getWidth() / 2, this->_sprite->getHeight() / 2);
	//	/*this->dPos = ox::getStage()->getPosition() - this->pos -
	//		ox::Vector2(this->_sprite->getWidth() / 2, this->_sprite->getHeight() / 2);*/
	//	ox::logs::messageln("processEvents locPos:'%f', '%f'", cursorPos.x, cursorPos.y);
	//	ox::logs::messageln("processEvents dPos:'%f', '%f'", dPos.x, dPos.y);
	//	//ox::logs::messageln("processEvents localPos:'%f', '%f'", touchOnStage->localPosition.x, touchOnStage->localPosition.y);
	//	//ox::logs::messageln("processEvents stage:'%f', '%f'", ox::getStage()->getPosition().x, ox::getStage()->getPosition().y);
	//	ox::logs::messageln("processEvents pos:'%f', '%f'", pos.x, pos.y);
	//}
	//if (event->type ==
	//	ox::Event::MouseButtonPressed &&
	//	event.mouseButton.button == sf::Mouse::Left &&
	//	this->_sprite.getGlobalBounds().contains(static_cast<ox::Vector2> (sf::Mouse::getPosition(window))) &&
	//	this->isMove == false)
	//{
	//	this->_oldPos = this->_sprite->getPosition();
	//}
	//if (event.type ==
	//	sf::Event::MouseButtonPressed &&
	//	event.mouseButton.button == sf::Mouse::Left ||
	//	event.type == sf::Event::MouseMoved && this->isMove)
	//{
	//	if (this->_sprite.getGlobalBounds().contains(static_cast<ox::Vector2> (sf::Mouse::getPosition(window))))
	//	{
	//		this->isMove = true;
	//		this->dPos = ox::Vector2(0, 0);
	//		this->dPos = static_cast<ox::Vector2> (sf::Mouse::getPosition(window)) -
	//			this->pos - ox::Vector2(this->_sprite.getGlobalBounds().width / 2, this->_sprite.getGlobalBounds().height / 2);
	//		//changeColor(this, sf::Color::Green);
	//	}
	//}
	//if (event.type ==
	//	sf::Event::MouseButtonReleased &&
	//	event.mouseButton.button == sf::Mouse::Left)
	//{
	//	if (this->_sprite.getGlobalBounds().contains(static_cast<ox::Vector2> (sf::Mouse::getPosition(window)))
	//		&& this->isMove)
	//	{
	//		this->isMove = false;
	//		//changeColor(this, sf::Color::White);
	//		int i = int(sf::Mouse::getPosition(window).x) / 100, j = int(sf::Mouse::getPosition(window).y) / 100;
	//		if (canMoveHere(i, j))
	//		{
	//			move(i, j);
	//		}
	//		else this->_sprite.setPosition(this->_oldPos.x, this->_oldPos.y);
	//		_thisGame->printBoard();
	//	}
	//}
}

void Figure::update()
{
	if (isMove)
	{
		this->pos += this->dPos;
		ox::logs::messageln("from Update dPos:'%f', '%f'", dPos.x, dPos.y);
		ox::logs::messageln("from Update Pos:'%f', '%f'", pos.x, pos.y);
		this->_sprite->setPosition(this->pos);
		this->dPos.setZero();
	}
}

void Figure::move(int i, int j)
{
	ox::logs::messageln("boardElement: '%s'", _thisGame->getBoardElement(i, j).c_str());
	if (_thisGame->getBoardElement(i, j).front() == this->_color.front())
	{
		this->_sprite->setPosition(this->_oldPos.x, this->_oldPos.y);
	}
	if (_thisGame->getBoardElement(i, j).front() != this->_color.front()
		&& _thisGame->getBoardElement(i, j) != "empty")
	{
		_thisGame->setBoardElement(int(this->_oldPos.x / 100), int(this->_oldPos.y / 100), std::string("empty"));
		_thisGame->deleteFigure(&_thisGame->getBoardFigure(i, j));
		_thisGame->setBoardElement(i, j, std::string("empty"));

	}
	if (_thisGame->getBoardElement(i, j) == "empty")
	{
		ox::logs::messageln("empty");
		_thisGame->setBoardElement(int(this->_oldPos.x / 100), int(this->_oldPos.y / 100), std::string("empty"));
		this->_sprite->setPosition(ox::Vector2(i * 100, j * 100));
		this->_newPos = this->_sprite->getPosition();
		_thisGame->setBoardElement(i, j, this->_color + this->_name);
	}
	this->isFirsTimeMoving = false;
	this->_oldPos = this->_sprite->getPosition();
}

bool Figure::canMoveHere(int i, int j)
{
	ox::logs::messageln("canMoveHere");
	enum line { horizontal, vertical, diagonalL, diagonalR };
	bool canMove = false;
	int colorVariable = 1;
	int iOld = static_cast<int> (this->_oldPos.x / 100);
	int jOld = static_cast<int> (this->_oldPos.y / 100);

	if (this->_color == "w") colorVariable *= -1;

	if (this->_name == "pawn")
	{
		if (this->isFirsTimeMoving && i - iOld == 0 && j - jOld == -2 * colorVariable)
		{
			this->isFirsTimeMoving = false;
			canMove = true;
		}
		if (i - iOld == 0 && j - jOld == -1 * colorVariable) canMove = true;
		if ((i - iOld == -1 * colorVariable || i - iOld == 1 * colorVariable)
			&& j - jOld == -1 * colorVariable)
		{
			if (_thisGame->getBoardElement(i, j) != "empty") canMove = true;
		}
	}
	if (this->_name == "king")
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
			if (this->isFirsTimeMoving && checkLine(i - 1, j, iOld, jOld, line::horizontal))
			{
				_thisGame->getBoardFigure(i - 2, j).move(i + 1, j);
				canMove = true;
			}
			break;
		case 6:
			if (this->isFirsTimeMoving && checkLine(i, j, iOld, jOld, line::horizontal))
			{
				_thisGame->getBoardFigure(i + 1, j).move(i - 1, j);
				canMove = true;
			}
			break;
		}

	}
	if (this->_name == "knight")
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
	if (this->_name == "castle")
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
	if (this->_name == "bishop")
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
	if (this->_name == "queen")
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
