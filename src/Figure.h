#pragma once
#include "Element.h"

class Figure : public Element
{
public:
	Figure(const std::string & name, const std::string & color, Game *ptr);

	virtual void processEvents(ox::Event *event) override;
	virtual void update() override;
	void move(int i, int j);
	bool canMoveHere(int i, int j);
	bool checkLine(int i, int j, int iOld, int jOld, int line);
	void processCursorPos(ox::Event * event);

	Figure *figurePtr = this;
	bool isMove = false;
	bool isFirsTimeMoving = true;
	std::string _name;
	std::string _color;
};
