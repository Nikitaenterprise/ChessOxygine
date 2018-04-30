#pragma once
#include "ox/oxygine.hpp"
#include <string>
#include <iostream>
#include <vector>

class Game;
class Element
{
public:
	Element(const Element &) = delete;
	Element & operator=(const Element &) = delete;
	Element();
	~Element();

	void setScale(const ox::Vector2 &vec);
	void setPosition(const ox::Vector2 &vec);
	void setGamePtr(Game *game);
	virtual void processEvents(ox::Event *event) = 0;
	virtual void update() = 0;

	ox::Vector2 pos;
	ox::Vector2 dPos;
	ox::Vector2 _oldPos;
	ox::Vector2 _newPos;
	ox::Vector2 cursorPos;

	Game *_thisGame = nullptr;

protected:
	ox::spSprite DEBUGSprite;
	ox::spSprite _sprite;
};