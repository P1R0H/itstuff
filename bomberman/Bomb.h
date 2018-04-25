#pragma once

#include <functional>

#include "Config.h"
#include "Flame.h"
#include "GameObjectBase.h"
#include "Playground.h"

/**
 *
 */
class Bomb : public GameObjectBase {
public:
	Bomb(Playground &playground);

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Square const &value) override;
	Square const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	void gameTick() override;

	void setExplosionCallback(std::function<void()> explosionCallback);

	void explode();

	void setRange(int range);

private:
	Playground &playground_;

	Square position_{};
	TextureRef texture_;

	std::function<void()> explosionCallback_;

	int timer_ = Config::bombTime;
	int range_ = 1;
};
