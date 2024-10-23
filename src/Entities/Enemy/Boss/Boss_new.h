#pragma once
#include "../Enemy_new.h"

class Boss_new : public Enemy_new
{
public:
	Boss_new();


	TickData tick() override;
	TickData attack() override;
private:
	std::vector<Enemy_new> children;

};
