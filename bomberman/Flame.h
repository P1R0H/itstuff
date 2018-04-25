#pragma once

#include "Config.h"
#include "GameObjectBase.h"
#include "Playground.h"


/**
 * Should destroy itself after a specific amount of ticks.
 */
class Flame : public GameObjectBase {
public:
	Flame(Playground &playground);

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Square const &value) override;
	Square const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	void gameTick() override;

private:
	Playground &playground_;

	Square position_{};
	TextureRef texture_;

	int flameTick_ = Config::fireTime;
};
