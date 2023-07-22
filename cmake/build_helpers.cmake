macro(add_zephyr_test test)

    message(STATUS "Adding ${test} test")

    add_executable(${test} test/${test}.cpp)

    target_compile_options(${test} PUBLIC
        -fcoroutines
        -pthread
        -Wall
        -Wextra
    )

    target_include_directories(${test} PUBLIC
        include
    )

    target_link_libraries(${test} PUBLIC zephyr -lpthread -latomic uring)

    add_dependencies(${test} uring)

    add_test(
        NAME ${test}
        COMMAND ${test}
    )

endmacro()

macro(add_zephyr_example example)

    message(STATUS "Adding ${example} example")

    add_executable(${example} examples/${example}.cpp)

    target_compile_options(${example} PUBLIC
        -fcoroutines
        -pthread
        -Wall
        -Wextra
    )

    target_include_directories(${example} PUBLIC
        include
    )

    target_link_libraries(${example} PUBLIC zephyr -lpthread -latomic uring)

    add_dependencies(${example} uring)

endmacro()