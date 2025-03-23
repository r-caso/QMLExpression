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

target_include_directories(QMLExpression PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Set up installation paths (customize as needed)
include(GNUInstallDirs)

# Install the library binary
install(TARGETS QMLExpression
    EXPORT QMLExpressionTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the header files
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export targets
install(EXPORT QMLExpressionTargets
    FILE QMLExpressionTargets.cmake
    NAMESPACE QMLExpression::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QMLExpression
)

# Create and install package configuration files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfig.cmake.in"
"@PACKAGE_INIT@

include(\"\${CMAKE_CURRENT_LIST_DIR}/QMLExpressionTargets.cmake\")
check_required_components(QMLExpression)
")

configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QMLExpression
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/QMLExpressionConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QMLExpression
)