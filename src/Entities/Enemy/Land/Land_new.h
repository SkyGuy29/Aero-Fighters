#pragma once
class Land
{
public:
	Land(sf::Vector2f pos, sf::Vector2f vel,
		EntityID ID, unsigned char orientation = 0) :
		Enemy(pos, vel, ID, orientation), IHasHealth(ID) {}

	void tick(EntityHolder& entities) override;
private:

};

