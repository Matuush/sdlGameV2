#pragma once
#include "Player.hpp"


class Enemy : public Creature {
public:
	static std::vector<Enemy*> enemies;

	Enemy() = default;
	Enemy(Vector2D p_position) : Creature(p_position, ENEMY_TEXTURE, DEFAULT_ENEMY_HEALTH, DEFAULT_ENEMY_DAMAGE) {
		terminalVelocity = DEFAULT_ENEMY_TERMINAL_VELOCITY;
		solid = true;
		colliders.add(new Collider(getCenter(), KAPUSTA_WIDTH));
		
		enemies.push_back(this);
	}
	~Enemy(){
		Enemy::enemies.erase(findIter(Enemy::enemies.begin(), Enemy::enemies.end(), this));
	}
protected:
	inline void changeSprite() {
		lastRight = velocity.x < 0 ? false : (velocity.x > 0 ? true : lastRight);
		int tick = (int)(SDL_GetTicks() / (500 / PLAYER_VELOCITY)) % 6;
		currentFrame = tick == 5 ? SDL_Rect {0, RAW_ENEMY, currentFrame.w, currentFrame.h} : SDL_Rect {tick* RAW_ENEMY, 0, currentFrame.w, currentFrame.h};
	}
	inline void findPlayer() {
		Player* closestPlayer = NULL;
		if (Player::players.size() > 0) {
			for (Player* p : Player::players)
				if (!closestPlayer || abs((p->getCenter() - getCenter()).getMagnitude()) < abs((closestPlayer->getCenter() - getCenter()).getMagnitude())) closestPlayer = p;
			velocity = closestPlayer->getCenter() - getCenter();
		}
		else velocity = MAP_SIZE / 2 - position;
	}
	void update() override{
		findPlayer();
		velocity.limit(terminalVelocity);

		//! COMBAT HERE
		move(velocity);
		{
			for(Player* p: Player::players)
				if(collides(p)) {
					punch(p);
					p->recoil(getCenter(), 12);
				}
			for(Projectile* p: Projectile::projectiles)
				if(collides(p)) {
					punch(p);
					recoil(p->getCenter(), 12);
				}
		}
		move(Vector2D(0, 0) - velocity);

		updatePosCareless();
		
		//changeSprite();

		if(health <= 0) {
			delete this;
			new Enemy(Vector2D(900.0, 900.0));
		}	
	}

	inline void punch(Creature* p){
		p->oof(this);
		oof(p);
	}

	void input(SDL_Event* event) override { }
};