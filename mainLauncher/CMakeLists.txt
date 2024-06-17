add_executable(mainLauncher mainLauncher.cpp)

target_link_libraries(mainLauncher PUBLIC src sfml-graphics tmxlite)
add_custom_target(copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(mainLauncher copy-resources)