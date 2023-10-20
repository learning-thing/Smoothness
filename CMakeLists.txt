cmake_minimum_required( VERSION 3.27.0 )

project( operator )

add_executable( operator src/main.cpp )
target_link_libraries( operator raylib )
target_include_directories(operator PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/lib>
  $<INSTALL_INTERFACE:src/lib>  # <prefix>/include/mylib
)


add_executable( smoothnesstypes src/anima.cpp )
target_link_libraries( smoothnesstypes raylib )
target_include_directories(smoothnesstypes PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/lib>
  $<INSTALL_INTERFACE:src/lib>  # <prefix>/include/mylib
)

add_executable( gearsincos src/gear.cpp )
target_link_libraries( gearsincos raylib )


add_executable( RotMove src/RotMove.cpp )
target_link_libraries( RotMove raylib )


add_executable( RotMove3d src/RotMove3d.cpp )

find_package(raylib 2.0.5 REQUIRED)
target_link_libraries( RotMove3d raylib )

add_executable(drift src/car.cpp)
target_link_libraries(drift raylib )


add_executable(waves src/waves.cpp)
target_link_libraries(waves raylib )

add_executable(wavesAnimation src/renderwaves.cpp)
target_link_libraries(wavesAnimation raylib )

add_executable(test src/test.c)
target_link_libraries(test raylib)