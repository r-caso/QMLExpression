cmake_minimum_required (VERSION 3.22)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (QMLExpression VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(qml-expression STATIC)

target_sources(qml-expression PRIVATE
	src/expression.cpp
	src/formatter.cpp
)

target_include_directories(qml-expression PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)