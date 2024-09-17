cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

if(POLICY CMP0092)
	cmake_policy(SET CMP0092 NEW) # Don't add -W3 warning level by default.
endif()

project(web-sample
	VERSION 1.0.0
	DESCRIPTION "Sample"
	HOMEPAGE_URL "https://github.com/Wend4r/web-sample"
	LANGUAGES C CXX
)

string(REGEX REPLACE "^[^-]*-" "" PROJECT_NAME_SUBSTRING "${PROJECT_NAME}")
string(TOLOWER "${PROJECT_NAME_SUBSTRING}" PROJECT_NAME_LOWER)
string(TOUPPER "${PROJECT_NAME_SUBSTRING}" PROJECT_NAME_UPPER)

set(PROJECT_OUTPUT_NAME "${PROJECT_NAME_SUBSTRING}")

set(PROJECT_AUTHOR "Sample author")
set(PROJECT_DESCRIPTION_FULL "Sample WEB application")
string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d")
string(TIMESTAMP PROJECT_BUILD_TIME "%H:%M:%S")

set(EXTERNAL_DIR "external")
set(INCLUDE_DIR "include")
set(SOURCE_DIR "src")
set(SOURCE_CGI_DIR "${SOURCE_DIR}/cgi")

include(cmake/platform/shared.cmake)

if(LINUX)
	include(cmake/platform/linux.cmake)
elseif(WINDOWS)
	include(cmake/platform/windows.cmake)
elseif(MACOS)
	include(cmake/platform/macos.cmake)
endif()

set(INCLUDE_DIRS
	${INCLUDE_DIR}
)

set(SOURCE_FILES
	${SOURCE_CGI_DIR}/utils.c
	${SOURCE_DIR}/cgi.cpp
	${SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF

	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

if(WINDOWS)
	set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILER_OPTIONS} ${PLATFORM_COMPILER_OPTIONS})
target_link_options(${PROJECT_NAME} PUBLIC ${LINK_OPTIOINS} ${PLATFORM_LINK_OPTIONS})

target_compile_definitions(${PROJECT_NAME} PUBLIC ${COMPILE_DEFINITIONS} ${PLATFORM_COMPILE_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} ${PLATFORM_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBRARIES} ${PLATFORM_LINK_LIBRARIES} ${GLAZE_NAME})
