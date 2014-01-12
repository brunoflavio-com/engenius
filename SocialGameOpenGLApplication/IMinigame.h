#pragma once
class IMinigame
{
public:
	virtual bool isOver()=0;
	virtual bool isWinner()=0;
	virtual float getPoints()=0;
};

