#include "Player.h"
#include "Visitors.h"

Player::Player(Playground &playground)
		: playground_(playground) {}

void Player::visit(IObjectVisitor &visitor) {
	visitor(*this);
}

void Player::visit(IConstObjectVisitor &visitor) const {
	visitor(*this);
}

void Player::position(Square const &value) {
	position_ = value;
}

Square const &Player::position() const {
	return position_;
}

TextureRef const &Player::texture() const {
	return texture_;
}

void Player::texture(TextureRef const &texture) {
	texture_ = texture;
}

void Player::move(Direction direction, int ticks) {
	// The function `Vector toVector(Direction direction);`
	// from `Geometry.h` could be helpful.

	moveDirection_ = (poison_ == 0) ? toVector(direction) : toVector(other(direction));
	moveTick_ = ticks;
}

bool Player::isMoving() const {
	return moveTick_ != 0;
}

void Player::bomb() {
	CheckBombVisitor visitor;
	playground_.visitAll(visitor, playground_.Overlapping(position()));

	if (visitor.can && maxBombs_ != 0) {
		Bomb &bomb = playground_.createBomb();
		bomb.position(round(position()));
		bomb.setRange(bombRange_);

		bomb.setExplosionCallback([this]() { this->maxBombs_++; });

		maxBombs_--;
	}
}

bool Player::isDead() const {
	return dead_;
}

void Player::gameTick() {
	if (isMoving()) {
		if (!isBlocked(position()))
			position(position() + moveDirection_);
		else {
			if (!isBlocked(round(position())))
				position(position() + one( round(position()).from - Point{position().from.x, position().from.y }));
		}
		moveTick_--;
	}

	if(poison_ != 0)
		poison_--;

	BonusVisitor visitor;
	playground_.visitAll(visitor, playground_.Overlapping(position()));
	addBonus(visitor.bonus);
}

bool Player::isBlocked(Square position) const {
	BlockedWayDetector visitor;
	visitor.myPosition = position;
	visitor.nextSquare = this->position() + moveDirection_ * Config::mesh;

	playground_.visitAll(visitor, playground_.Overlapping(position + moveDirection_));
	if (!playground_.isValid(position + moveDirection_))
		visitor.blocked = true;

	return visitor.blocked;
}

void Player::die() {
	dead_ = true;
	playground_.killPlayer(*this);
}

void Player::addBonus(Bonus bonus) {
	switch (bonus) {
	case Bonus::BombRange:
		bombRange_++;
		break;
	case Bonus::BombMax:
		maxBombs_++;
		break;
	case Bonus::Poison:
		poison_ += Config::poisonTime;
		break;
	default:
		break;
	}
}
