if(EXISTS ${CMAKE_HOME_DIRECTORY}/conanbuildinfo.cmake)
    include(conanbuildinfo.cmake)
else()
    message(FATAL_ERROR "Conan not installed. Run 'conan install .'")
endif()

list(APPEND ${PROJECT_NAME}_SOURCES
    range_main.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(range CONAN_PKG::range-v3)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)