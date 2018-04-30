#include "Element.h"
#include "Game.h"

Element::Element()
{
}

Element::~Element()
{
}

void Element::setScale(const ox::Vector2 & vec)
{
	_sprite->setLocalScale(vec);
}

void Element::setPosition(const ox::Vector2 & vec)
{
	/*sf::Vector2f offset(52, 52);
	sf::Vector2f temp(_image.getSize().x / 4 - offset.x, _image.getSize().y / 2 - offset.y);
	_sprite.setPosition(vec);
	this->pos = vec + temp;
	_oldPos = this->_sprite.getPosition();*/

	ox::logs::messageln("setPosition vec:'%f', '%f'\n", vec.x, vec.y);
	ox::Vector2 offset(0, 10);
	ox::Vector2 temp(_sprite->getSize().x / 4 - offset.x, _sprite->getSize().y / 2 - offset.y);
	this->_sprite->setPosition(vec);
	//ox::logs::messageln("setPosition vec:'%f', '%f'\n", vec.x, vec.y);
	//ox::logs::messageln("setPosition SpritePos:'%d', '%d'\n", _sprite->getPosition().x, _sprite->getPosition().y);
	//this->pos = vec + temp;
	_oldPos = pos = this->_sprite->getPosition();// vec - offset;//temp;
	ox::logs::messageln("setPosition vec:'%f', '%f'\n", vec.x, vec.y);
	ox::logs::messageln("SpritePos:'%f', '%f'\n", _sprite->getPosition().x, _sprite->getPosition().y);
	//ox::logs::messageln("pos:'%d', '%d'\n", pos.x, pos.y);
	//ox::logs::messageln("vec:'%d', '%d'\n", vec.x, vec.y);
	//_oldPos = pos;
	ox::logs::messageln("setPosition vec:'%f', '%f'\n", vec.x, vec.y);
}

void Element::setGamePtr(Game *game)
{
	_thisGame = game->_thisGame;
}