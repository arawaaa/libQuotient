# SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
#
# SPDX-License-Identifier: BSD-3-Clause

set(quotest_SRCS quotest.cpp)

add_executable(quotest ${quotest_SRCS})
target_link_libraries(quotest PRIVATE Qt5::Core Qt5::Test ${PROJECT_NAME})

option(${PROJECT_NAME}_INSTALL_TESTS "install quotest (former qmc-example) application" ON)
add_feature_info(InstallQuotest ${PROJECT_NAME}_INSTALL_TESTS
                 "the library functional test suite")

if (${PROJECT_NAME}_INSTALL_TESTS)
    install(TARGETS quotest RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif ()
