file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} "BabyController.cpp" "BabyController.h" "CameraController.cpp" "CameraController.h" "Component.cpp" "Component.h" "Game.cpp" "Game.h" "Object.cpp" "Object.h" "PlayerController.cpp" "PlayerController.h" "RigidBody.cpp" "RigidBody.h" "Sprite.cpp" "Sprite.h")
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC sfml-graphics box2d)