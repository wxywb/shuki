project(shuki)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/ImageMagick-6)

set(MAIN_SRC_FILE ${CMAKE_SOURCE_DIR}/source/ShukiModel.cpp)
set(MAIN_SRC_FILE ${MAIN_SRC_FILE} ${CMAKE_SOURCE_DIR}/source/ShukiModel.cpp)
set(MAIN_SRC_FILE ${MAIN_SRC_FILE} ${CMAKE_SOURCE_DIR}/source/ShukiShader.cpp)
set(MAIN_SRC_FILE ${MAIN_SRC_FILE} ${CMAKE_SOURCE_DIR}/source/ShukiTexture.cpp)
set(MAIN_SRC_FILE ${MAIN_SRC_FILE} ${CMAKE_SOURCE_DIR}/source/ShukiCamera.cpp)
set(MAIN_SRC_FILE ${MAIN_SRC_FILE} ${CMAKE_SOURCE_DIR}/source/ShukiTechnique.cpp)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_library(libshuki ${MAIN_SRC_FILE})

target_link_libraries(libshuki freeglut)
target_link_libraries(libshuki glew32)
target_link_libraries(libshuki assimp)

add_subdirectory(${CMAKE_SOURCE_DIR}/example)
