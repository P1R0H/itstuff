#pragma once

#include "GameObjectBase.h"
#include "Playground.h"

enum class Bonus;

// (brick, wood, stone, ...)
class Wall : public GameObjectBase {
public:
	Wall(Playground &playground);

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Square const &value) override;
	Square const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	/**
	 * @brief Sets the kind of bonus which drops from the wall when destroyed.
	 */
	void bonus(Bonus value);

	/**
	 * @brief Sets whether the wall is destroyable or not.
	 */
	void destroyable(bool value);
	bool isDestroyable() const;

	void destroy();
private:
	Playground &playground_;

	Square position_{};
	TextureRef texture_;

	bool destroyable_;

	Bonus bonus_ = Bonus::None;
};
