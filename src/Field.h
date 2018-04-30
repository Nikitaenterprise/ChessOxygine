#pragma once
#include "Element.h"

class Field : public Element
{
public:
	Field(const Field &) = delete;
	Field & operator=(const Field &) = delete;
	Field();
	~Field();

	virtual void processEvents(ox::Event *event) override;
	virtual void update() override;

protected:
	std::vector<ox::ColorRectSprite*> _fieldElement;
};

#pragma once
