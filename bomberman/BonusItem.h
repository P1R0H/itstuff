#pragma once

#include "GameObjectBase.h"
#include "Playground.h"

enum class Bonus;

class BonusItem : public GameObjectBase {
public:
	BonusItem(Playground &playground);

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Square const &value) override;
	Square const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	/**
	 * @brief Sets the kind of bonus.
	 */
	Bonus getBonus() const;

	void bonus(Bonus value);
	void take();
	void destroy();

private:
	Playground &playground_;

	Square position_{};
	TextureRef texture_;

	Bonus value_;
};
