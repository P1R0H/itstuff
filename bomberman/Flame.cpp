#include "Flame.h"
#include "Visitors.h"

Flame::Flame(Playground &playground)
		: playground_(playground) {}

void Flame::visit(IObjectVisitor &visitor) {
	visitor(*this);
}

void Flame::visit(IConstObjectVisitor &visitor) const {
	visitor(*this);
}

void Flame::position(Square const &value) {
	position_ = value;
}

Square const &Flame::position() const {
	return position_;
}

TextureRef const &Flame::texture() const {
	return texture_;
}

void Flame::texture(TextureRef const &texture) {
	texture_ = texture;
}

void Flame::gameTick() {
	FlameVisitor visitor;
	playground_.visitAll(visitor, playground_.Overlapping(position()));

	flameTick_--;
	if (flameTick_ == 0)
		playground_.remove(*this);
}
