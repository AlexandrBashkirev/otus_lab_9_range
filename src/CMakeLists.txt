
include(${CMAKE_HOME_DIRECTORY}/conanbuildinfo.cmake)

conan_cmake_run(REQUIRES
                    range-v3/0.5.0@ericniebler/stable
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

list(APPEND ${PROJECT_NAME}_SOURCES
    range_main.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(range ${CONAN_LIBS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)