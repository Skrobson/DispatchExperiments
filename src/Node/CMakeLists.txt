add_library(Node INTERFACE)
target_include_directories(Node INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(NodeTest NodeTest.cpp)
target_link_libraries(NodeTest Node)