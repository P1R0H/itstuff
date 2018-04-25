#include "Bomb.h"
#include "Bonus.h"
#include "BonusItem.h"
#include "Flame.h"
#include "Player.h"
#include "Wall.h"

#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory(Playground& playground)
		: playground_(playground) {}

std::unique_ptr<Wall> GameObjectFactory::createBrick() const {
	// Brick is a destroyable wall.
	// It can be destroed by an explosion of a bomb.

	// Set those textures on the objects created there.
	TextureRef texture{ "brick_gray0.png" };
	Wall newWall = Wall(playground_);
	newWall.texture(texture);
	newWall.destroyable(true);

	return std::make_unique<Wall>(newWall);
}

std::unique_ptr<Wall> GameObjectFactory::createStone() const {
	// Stone is a non-destroyable wall.
	TextureRef texture{ "stone2_gray0.png" };
	Wall newWall = Wall(playground_);
	newWall.texture(texture);
	newWall.destroyable(false);

	return std::make_unique<Wall>(newWall);
}

std::unique_ptr<Flame> GameObjectFactory::createFlame() const {
	TextureRef texture{ "conjure_flame.png" };
	Flame newFlame = Flame(playground_);
	newFlame.texture(texture);

	return std::make_unique<Flame>(newFlame);
}

std::unique_ptr<Player> GameObjectFactory::createPlayer() const {
	TextureRef texture{ "human.png" };
	Player newPlayer = Player(playground_);
	newPlayer.texture(texture);

	return std::make_unique<Player>(newPlayer);
}

std::unique_ptr<Bomb> GameObjectFactory::createBomb() const {
	TextureRef texture{ "delayed_fireball.png" };
	Bomb newBomb = Bomb(playground_);
	newBomb.texture(texture);
	newBomb.setExplosionCallback([]() { return; });

	return std::make_unique<Bomb>(newBomb);
}

std::unique_ptr<BonusItem> GameObjectFactory::createBonusItem(Bonus bonus) const {
	TextureRef texture = [&] {
		switch (bonus) {
		case Bonus::Poison:
			return TextureRef{ "potion_bubbly.png" };
		default:
			return TextureRef{ "sticky_flame.png" };
		}
	}();
	BonusItem newItem = BonusItem(playground_);
	newItem.bonus(bonus);
	newItem.texture(texture);

	return std::make_unique<BonusItem>(newItem);
}
