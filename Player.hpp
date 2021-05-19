#pragma once
#include "Projectile.hpp"
#include "data/KeyState.hpp"

class Player : public Creature {
public:
	static std::vector<Player*> players;

	KeyState keyState = KeyState();
	double health = DEFAULT_PLAYER_HEALTH, damage = DEFAULT_PLAYER_DAMAGE;

	Player() = default;
	Player(Vector2D p_position) : Creature(p_position, PLAYER_TEXTURE, DEFAULT_PLAYER_HEALTH, DEFAULT_PLAYER_DAMAGE) {
		terminalVelocity = PLAYER_TERMINAL_VELOCITY;
		solid = true;
		colliders.add(new Collider(position + PLAYER_TEXTURE.width * SCALE / 2, KAPUSTA_WIDTH));
		Player::players.push_back(this);
	}
	~Player(){
		Player::players.erase(findIterP(Player::players.begin(), Player::players.end(), this));
	}

	void update() override {
		const double ratio = 2;
		velocity.y += keyState.w ? -movementAcceleration / ratio : movementAcceleration / ratio;
		velocity.x += keyState.a ? -movementAcceleration / ratio : movementAcceleration / ratio;
		velocity.y += keyState.s ? movementAcceleration / ratio : -movementAcceleration / ratio;
		velocity.x += keyState.d ? movementAcceleration / ratio : -movementAcceleration / ratio;

		updatePosCareless();

		changeSprite();
	}

	void input(SDL_Event* event) override{
		keyState.update(event);
	}
	void shoot(SDL_Event* event, Vector2D camPos){
		Vector2D shotPos = Vector2D(event->button.x + camPos.x, event->button.y + camPos.y);
		Projectile::projectiles.push_back(new Projectile(position + RAW_PLAYER * SCALE / 2, shotPos, damage)); 
		recoil(shotPos);
	}
private:
	double movementAcceleration = PLAYER_VELOCITY;
	Vector2D lastPos;

	inline void changeSprite() {
		lastRight = velocity.x < 0 ? false : (velocity.x > 0 ? true : lastRight);

		if (velocity < 1) currentFrame.y = 0, currentFrame.x = 0;
			//currentFrame.y = RAW_PLAYER, currentFrame.x = (SDL_GetTicks() / 100 % 4 + 1) * RAW_PLAYER;
		else {
			int tick = (int)(SDL_GetTicks() / (7000 / velocity.getMagnitude())) % 2;
			currentFrame.x = PLAYER_TEXTURE.width * tick;
		}
	}

	inline void recoil(Vector2D shotPos) {
		Vector2D tAcceleration = (position + PLAYER_TEXTURE.width / 2 * SCALE) - shotPos;
		tAcceleration.limit(movementAcceleration * 3);
		velocity += tAcceleration;
	}

	inline std::vector<Player*>::iterator findIterP(std::vector<Player*>::iterator first, std::vector<Player*>::iterator last, const Player* value){
    	for (; first != last; ++first)
        	if (*first == value) return first;
    	return last;
	}
};