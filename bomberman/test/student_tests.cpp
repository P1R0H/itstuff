#include "Config.h"
#include "testhelper.h"

TEST_CASE("Basic player actions", "[student]") {
	Dimensions dimensions{ { 10, 13 }, Config::mesh };
	Playground playground{ dimensions };
	Player& player = playground.createPlayer();

	SECTION("Move down, no obstacles there") {
		player.position(Square{ Point{ 0, 0 }, 1 });
		REQUIRE(!player.isMoving());

		player.move(Direction::Down, 2);
		REQUIRE((player.position() == Square{ Point{ 0, 0 }, 1 }));
		REQUIRE(player.isMoving());

		player.gameTick();
		REQUIRE((player.position() == Square{ Point{ 0, 1 }, 1 }));
		REQUIRE(player.isMoving());

		player.gameTick();
		REQUIRE((player.position() == Square{ Point{ 0, 2 }, 1 }));
		REQUIRE(!player.isMoving());

		player.gameTick();
		REQUIRE((player.position() == Square{ Point{ 0, 2 }, 1 }));
		REQUIRE(!player.isMoving());
	}

	SECTION("Move left, stop on border") {
		player.position(Square{ Point{ 1, 0 }, 1 });
		REQUIRE(!player.isMoving());

		player.move(Direction::Left, 2);
		REQUIRE((player.position() == Square{ Point{ 1, 0 }, 1 }));
		REQUIRE(player.isMoving());

		player.gameTick();
		REQUIRE((player.position() == Square{ Point{ 0, 0 }, 1 }));
		REQUIRE(player.isMoving());

		player.gameTick();
		REQUIRE((player.position() == Square{ Point{ 0, 0 }, 1 }));
		REQUIRE(!player.isMoving());

		player.gameTick();
		REQUIRE((player.position() == Square{ Point{ 0, 0 }, 1 }));
		REQUIRE(!player.isMoving());
	}

	SECTION("Drop a bomb") {
		player.position(dimensions.coarseSquare(3, 2));
		player.bomb();
		REQUIRE(!containsBomb(playground, player.position()));
		playground.gameTick();
		REQUIRE(containsBomb(playground, player.position()));
	}
}
