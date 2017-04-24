include_directories(include)

add_subdirectory(cmd)
add_subdirectory(file)
add_subdirectory(gfx)
add_subdirectory(gui)
add_subdirectory(input)
add_subdirectory(net)
add_subdirectory(phys)
add_subdirectory(snd)

add_executable(spear main.cc)
target_link_libraries(spear cmd)