#pragma once
#include "Player.hpp"


class Enemy : public Creature {
public:
	static std::vector<Enemy*> enemies;

	Enemy() = default;
	Enemy(Vector2D p_position) : Creature(p_position, ENEMY_TEXTURE, DEFAULT_ENEMY_HEALTH, DEFAULT_ENEMY_DAMAGE) {
		terminalVelocity = DEFAULT_ENEMY_TERMINAL_VELOCITY;
		solid = true;
		colliders.add(new Collider(position + PLAYER_TEXTURE.width * SCALE / 2, KAPUSTA_WIDTH));

		enemies.push_back(this);
	}
	~Enemy(){
		Enemy::enemies.erase(findIter<Enemy*>(Enemy::enemies.begin(), Enemy::enemies.end(), this));
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
				if (!closestPlayer || abs((p->position - position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2).getMagnitude()) < abs((closestPlayer->position - position + PLAYER_TEXTURE.width / 2 - ENEMY_TEXTURE.width * 2).getMagnitude())) closestPlayer = p;
			velocity = closestPlayer->position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2 - position;
		}
		else velocity = MAP_SIZE / 2 - position;
	}
	void update() override{
		findPlayer();
		velocity.limit(terminalVelocity);

		move(velocity);
		for(Player* p: Player::players) if(collides(p)) punch(p);
		for(Projectile* p: Projectile::projectiles) if(collides(p)) {punch(p);}
		move(Vector2D(0, 0) - velocity);
		updatePosCareless();
		//changeSprite();

		//if(health <= 0) delete this;
	}

	inline void punch(Creature* p){
		p->oof(damage);
		oof(p->damage);
	}

	void input(SDL_Event* event) override { }
};