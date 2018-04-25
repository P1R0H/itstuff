#pragma once

// A collection of useful visitors.
#include "Bomb.h"
#include "BonusItem.h"
#include "ObjectVisitorSkeleton.h"
#include "Player.h"
#include "Wall.h"




struct DeadPlayerDetector : ConstObjectVisitorSkeleton {
	bool detected = false;
	void operator()(Player const &player) override { detected = detected || player.isDead(); }
};
struct CheckBombVisitor : ConstObjectVisitorSkeleton {
	bool can = true;
	void operator()(Bomb const & /*bomb*/) override { can = false; }
};

struct BlockedWayDetector : ConstObjectVisitorSkeleton {
	bool blocked = false;
	Square myPosition;
	Square nextSquare;
	void operator()(Wall const & /*wall*/) override { blocked = true; }
	void operator()(Bomb const &bomb) override {
		if(overlap(myPosition, bomb.position()))
			blocked = blocked || overlap(round(nextSquare), bomb.position());
		else
			blocked = blocked || overlap(nextSquare, bomb.position());
	}
};

struct BombExploder : ObjectVisitorSkeleton {
	bool stop = false;
	void operator()(Wall &wall) override {
		if(wall.isDestroyable())
			wall.destroy();
		stop = true;
	}
	void operator()(BonusItem &item) override { item.destroy(); }
	void operator()(Player &player) override { player.die(); }
};

struct FlameVisitor : ObjectVisitorSkeleton {
	void operator()(Player &player) override { player.die(); }
	void operator()(Bomb &bomb) override { bomb.explode(); }
};

struct BonusVisitor : ObjectVisitorSkeleton {
	Bonus bonus = Bonus::None;
	void operator()(BonusItem &item) override {
		bonus = item.getBonus();
		item.take();
	};
};