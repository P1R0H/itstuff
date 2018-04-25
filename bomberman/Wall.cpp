#include "Wall.h"
#include "Visitors.h"

Wall::Wall(Playground &playground)
		: playground_(playground) {}

void Wall::visit(IObjectVisitor &visitor) {
	visitor(*this);
}

void Wall::visit(IConstObjectVisitor &visitor) const {
	visitor(*this);
}

void Wall::position(Square const &value) {
	position_ = value;
}

Square const &Wall::position() const {
	return position_;
}

TextureRef const &Wall::texture() const {
	return texture_;
}

void Wall::texture(TextureRef const &texture) {
	texture_ = texture;
}

void Wall::bonus(Bonus value) {
	bonus_ = value;
}

void Wall::destroyable(bool value) {
	destroyable_ = value;
}

bool Wall::isDestroyable() const {
	return destroyable_;
}

void Wall::destroy() {
	if (bonus_ != Bonus::None) {
		BonusItem &item = playground_.createBonusItem(bonus_);
		item.position(position());
	}
	playground_.remove(*this);
}
