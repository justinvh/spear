
add_library(gui window.cc)
target_link_libraries(gui ${SDL2_LIBRARY} ${VULKAN_LIB} ${SPDLOG_LIBRARY})
