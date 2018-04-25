#include "BonusItem.h"
#include "Visitors.h"

BonusItem::BonusItem(Playground &playground)
		: playground_(playground) {}

void BonusItem::visit(IObjectVisitor &visitor) {
	visitor(*this);
}

void BonusItem::visit(IConstObjectVisitor &visitor) const {
	visitor(*this);
}

void BonusItem::position(Square const &value) {
	position_ = value;
}

Square const &BonusItem::position() const {
	return position_;
}

TextureRef const &BonusItem::texture() const {
	return texture_;
}

void BonusItem::texture(TextureRef const &texture) {
	texture_ = texture;
}

void BonusItem::bonus(Bonus value) {
	value_ = value;
}

void BonusItem::destroy() {
	playground_.remove(*this);
}

Bonus BonusItem::getBonus() const {
	return value_;
}

void BonusItem::take() {
	playground_.removeNow(*this);
}
