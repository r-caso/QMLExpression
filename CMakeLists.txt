cmake_minimum_required (VERSION 3.22)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (QMLExpression VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the static library
add_library(QMLExpression STATIC)

target_sources(QMLExpression PRIVATE
    src/expression.cpp
    src/formatter.cpp
)

# Proper include paths for build and install
target_include_directories(QMLExpression PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Install rules
install(TARGETS QMLExpression EXPORT QMLExpressionTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Export configuration
install(EXPORT QMLExpressionTargets
    FILE QMLExpressionTargets.cmake
    NAMESPACE QMLExpression::
    DESTINATION lib/cmake/QMLExpression
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfigVersion.cmake"
    DESTINATION lib/cmake/QMLExpression
)

configure_file(QMLExpressionConfig.cmake.in QMLExpressionConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfig.cmake"
    DESTINATION lib/cmake/QMLExpression
)
