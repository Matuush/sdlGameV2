#pragma once
#include "Entity.hpp"

class Projectile : public Creature {
public:
	static std::vector<Projectile*> projectiles;
	Projectile() = default;
	Projectile(Vector2D p_position, Vector2D destination, double p_damage) : Creature(p_position, BULLET_TEXTURE, 9, p_damage){
		terminalVelocity = DEFAULT_BULLET_TERMINAL_VELOCITY;
		velocity = (destination - position).setMagnitude(terminalVelocity);

		solid = false;
		colliders.add(new Collider(getCenter(), BULLET_WIDTH));

		projectiles.push_back(this);
	}
	~Projectile(){
		Projectile::projectiles.erase(findIter(Projectile::projectiles.begin(), Projectile::projectiles.end(), this));
	}
private:
	void update() override {
		updatePosCareless();
		if (position.x < 0 || position.y < 0 || position.x > MAP_SIZE.x || position.y > MAP_SIZE.y || velocity < 5 || health < 9) delete this;
	}
	void input(SDL_Event* event) override {}
};