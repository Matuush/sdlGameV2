#pragma once
#include "Projectile.hpp"
#include "data/KeyState.hpp"

class Player : public Creature {
public:
	static std::vector<Player*> players;

	KeyState keyState = KeyState();

	Player() = default;
	Player(Vector2D p_position) : Creature(p_position, PLAYER_TEXTURE, DEFAULT_PLAYER_HEALTH, DEFAULT_PLAYER_DAMAGE) {
		terminalVelocity = PLAYER_TERMINAL_VELOCITY;
		solid = true;
		colliders.add(new Collider(getCenter(), KAPUSTA_WIDTH));
		Player::players.push_back(this);
	}
	~Player(){
		Player::players.erase(findIter(Player::players.begin(), Player::players.end(), this));
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
		new Projectile(getCenter(), shotPos, damage); 
		recoil(shotPos);
	}

private:
	Vector2D lastPos;

	inline void changeSprite() {
		lastRight = velocity.x < 0 ? false : (velocity.x > 0 ? true : lastRight);

		if (velocity < 1) currentFrame.y = 0, currentFrame.x = 0;
			//TODO currentFrame.y = RAW_PLAYER, currentFrame.x = (SDL_GetTicks() / 100 % 4 + 1) * RAW_PLAYER;
		else {
			int tick = (int)(SDL_GetTicks() / (7000 / velocity.getMagnitude())) % 2;
			currentFrame.x = texture.width * tick;
		}
	}
};