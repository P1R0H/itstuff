#pragma once

#include "Bomb.h"
#include "GameObjectBase.h"
#include "IObjectVisitor.h"
#include "Playground.h"

class Player : public GameObjectBase {
public:
	Player(Playground &playground);

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Square const &value) override;
	Square const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	/**
	 * Player should start moving in the given direction.
	 * In every game tick (that is, in every call to gameTick() method),
	 * the player should move by an unit vector in the given direction.
	 * However, if there is an obstacle which can be avoided, during the
	 * game tick the player moves by an unit vector according to the
	 * obstacle avoiding algorithm. See the specification for more detail.
	 */
	void move(Direction direction, int ticks);

	/**
	 * @brief Returns true if player is moving.
	 * The player is moving since `Player::move` is called
	 * until the `ticks`-th call of gameTick().
	 */
	bool isMoving() const;

	/**
	 * @brief Drops a bomb on player's current position.
	 */
	void bomb();

	/**
	 * @brief Returns true if player is dead.
	 */
	bool isDead() const;
	bool isBlocked(Square position) const;

	void gameTick() override;
	void addBonus(Bonus bonus);
	void die();

	//testing
	bool poisoned() { return poison_ != 0; }

private:
	Playground &playground_;

	Square position_{};
	TextureRef texture_;

	int moveTick_ = 0;
	Vector moveDirection_;

	int maxBombs_ = 1;
	int bombRange_ = 1;
	int poison_ = 0;

	bool dead_ = false;
};
