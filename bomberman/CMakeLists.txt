cmake_minimum_required(VERSION 3.0)

set(USE_SDL2 true CACHE bool "Whether to use SDL2")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(${USE_SDL2})
	find_package(PkgConfig)

	# if pkg config is found, try finding SDL2 with it
	if(${PKG_CONFIG_FOUND})
		message("-- Looking for SDL2 using pkg-config")
		pkg_search_module(SDL2 sdl2)
		if(${SDL2_FOUND})
			set(SDL2_FROM_PKG_CONFIG 1)
		endif()
	endif()

	if(NOT SDL2_FOUND)
		message("-- including Hunter package manager")
		include("cmake/HunterGate.cmake")

		HunterGate(
			URL "https://github.com/ruslo/hunter/archive/v0.19.102.tar.gz"
			SHA1 "49a8333d7efc24c531aed97159fe58a68374185f"
		)
	endif()
endif() # USE_SDL2

project(bomberman)

if(${USE_SDL2})
	if(NOT SDL2_FOUND)
		message("-- Adding SDL2 through Hunter")
		hunter_add_package(SDL2)
		set(SDL2_FOUND 1)
	endif()

	find_package(SDL2 CONFIG)

	if("${PKG_CONFIG_FOUND}")
		string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
	endif()
endif() # USE_SDL2

# C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/brick_gray0.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/stone2_gray0.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/human.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/troll.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/delayed_fireball.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/conjure_flame.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/sticky_flame.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/potion_bubbly.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/gameOver.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/maps/classic.txt ${CMAKE_CURRENT_BINARY_DIR}/maps/classic.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/maps/default.txt ${CMAKE_CURRENT_BINARY_DIR}/maps/default.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/maps/empty.txt ${CMAKE_CURRENT_BINARY_DIR}/maps/empty.txt COPYONLY)

add_library(bomber
	./Player.cpp
	./Bomb.cpp
	./Flame.cpp
	./Wall.cpp
	./MapParser.cpp
	./BonusItem.cpp
	./GameObjectFactory.cpp
	./Playground.cpp
	./Geometry.cpp
	./Config.cpp
	./Dimensions.cpp
	./Bomberman.cpp
)

target_include_directories(bomber PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

if(${USE_SDL2})
	add_executable(bomberman
		./main.cpp
		./SDLWrapper.cpp
		./Grid.cpp
		./Textures.cpp
		./PlayerControl.cpp
	)

	target_include_directories(bomberman SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb/include)

	if (SDL2_FROM_PKG_CONFIG)
		target_link_libraries(bomberman
			bomber
			${SDL2_LIBRARIES}
		)

		target_include_directories(bomberman PRIVATE
			${SDL2_INCLUDE_DIRS}
		)

	elseif(SDL2_FOUND)

		target_link_libraries(bomberman
			bomber
			SDL2::SDL2main
			SDL2::SDL2
		)
	endif()
endif() # USE_SDL2


add_executable(testbomb
	./test/main.cpp
	./test/student_tests.cpp
)

target_link_libraries( testbomb
	bomber
)
