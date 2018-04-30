#include "Field.h"
#include "Game.h"

Field::Field()
{
	for (int i = 0; i < 8 * 8; i++)
	{
		_fieldElement.push_back(new ox::ColorRectSprite());
		_fieldElement[i]->setSize(ox::Vector2(800 / 8, 800 / 8));
		_fieldElement[i]->attachTo(ox::getStage());
	}

	int i = 0, j = 0;
	int inverse = -1;
	for (auto it = _fieldElement.begin(); it != _fieldElement.end(); it++)
	{
		if (inverse == 1)
		{
			if (i % 2 == 0)	(*it)->setColor(ox::Color(137, 125, 114));
			else if (i % 2 != 0) (*it)->setColor(ox::Color::White);
		}
		else if (inverse == -1)
		{
			if (i % 2 == 0)	(*it)->setColor(ox::Color::White);
			else if (i % 2 != 0) (*it)->setColor(ox::Color(137, 125, 114));
		}
		(*it)->setPosition(ox::Vector2(i * 800.0f / 8, j * 800.0f / 8));

		i++;
		if (i % 8 == 0)
		{
			j++;
			i = 0;
			inverse *= -1;
		}
	}
}

Field::~Field()
{
}

void Field::processEvents(ox::Event * event)
{
}

void Field::update()
{
}