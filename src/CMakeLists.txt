file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.h *.cpp )

add_library(src ${SOURCES} )
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC sfml-graphics sfml-audio box2d)