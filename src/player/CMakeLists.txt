aux_source_directory(. SRC)
include_directories(../)
add_library(player ${SRC})
target_link_libraries(player state)