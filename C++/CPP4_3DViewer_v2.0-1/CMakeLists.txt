cmake_minimum_required(VERSION 3.21)
project(3DViewer_v2_0)

set(CMAKE_CXX_STANDARD 17)

# 'Google_test' is the subproject name

include(FetchContent)
FetchContent_Declare(
        googletest
        Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(HEADER_FILES
        src/model/facade.h
        src/tests/test_view/test_view.h
        src/model/dao/data_model.h
        src/model/kernel/parser.h
        src/controller/controller.h
        src/model/kernel/strategy_transform/transformer.h
        src/model/kernel/strategy_transform/transform_strategy.h
        src/model/kernel/strategy_transform/move.h
        src/model/kernel/strategy_transform/rotate.h
        src/model/kernel/strategy_transform/scale.h
        src/model/kernel/optimal_scale_calculator.h

        )

set(SOURCE_FILES
        src/model/facade.cc
        src/tests/test_view/test_view.cc
        src/model/dao/data_model.cc
        src/model/kernel/parser.cc
        src/controller/controller.cc
        src/model/kernel/strategy_transform/transform_strategy.cc
        src/model/kernel/strategy_transform/move.cc
        src/model/kernel/strategy_transform/rotate.cc
        src/model/kernel/strategy_transform/scale.cc
        src/model/kernel/optimal_scale_calculator.cc
        )

add_library(viewer_2_0 STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(viewer_tests
        src/tests/tests.cc)

target_link_libraries(viewer_tests
        viewer_2_0
        gtest
        gtest_main
        )

add_test(test_all viewer_tests)