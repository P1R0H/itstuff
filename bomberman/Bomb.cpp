#include "Bomb.h"
#include "Visitors.h"

Bomb::Bomb(Playground &playground)
		: playground_(playground) {}

void Bomb::visit(IObjectVisitor &visitor) {
	visitor(*this);
}

void Bomb::visit(IConstObjectVisitor &visitor) const {
	visitor(*this);
}

void Bomb::position(Square const &value) {
	position_ = value;
}

Square const &Bomb::position() const {
	return position_;
}

TextureRef const &Bomb::texture() const {
	return texture_;
}

void Bomb::texture(TextureRef const &texture) {
	texture_ = texture;
}

void Bomb::gameTick() {
	timer_--;
	if (timer_ == 0) {
		explode();
	}
}

void Bomb::setExplosionCallback(std::function<void()> explosionCallback) {
	explosionCallback_ = explosionCallback;
}

void Bomb::explode() {
	explosionCallback_();

	for (Direction direction : { Direction::Up, Direction::Down, Direction::Left, Direction::Right }) {
		for (int i = 1; i <= range_; i++) {
			if (!playground_.isValid(position() + toVector(direction) * i * Config::mesh))
				break;

			BombExploder visitor;
			playground_.visitAll(visitor, playground_.Overlapping(position() + toVector(direction) * i * Config::mesh));
			if(visitor.stop)
				break;

			Flame &newFlame = playground_.createFlame();
			newFlame.position(position() + toVector(direction) * i * Config::mesh);
		}
	}

	Flame &newFlame = playground_.createFlame();
	newFlame.position(position());

	playground_.remove(*this);
}

void Bomb::setRange(int range) {
	range_ = range;
}