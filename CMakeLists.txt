cmake_minimum_required(VERSION 3.16)
project(ProjectLib VERSION 1.0.0 LANGUAGES CXX C)

if (NOT DEFINED BUILD_PROJECTLIB_CLI)
	set(BUILD_PROJECTLIB_CLI ON)
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
string(TIMESTAMP ProjectLib_Timestamp)

set(ProjectLib_Sources 
	src/lib/zip/zip.c
	src/lib/XML/XML.cpp
	src/lib/VersionCapabilities.cpp
	src/lib/GeneralProjectHeader.cpp
    src/lib/Project.cpp
	src/lib/XMLExport.cpp
	src/lib/OCSExport.cpp
	src/lib/SoftwareSpecific/Timeline/TimelineSpecificData.cpp)

set(ProjectLib_Headers
	include/XML/XML.hpp
	include/Common.h
	include/GeneralProjectHeader.h
	include/Project.h
	include/XMLExport.h
	include/OCSExport.h
	include/SoftwareSpecific/Timeline/TimelineSpecificData.h)

add_library(ProjectLib SHARED ${ProjectLib_Sources} ${ProjectLib_Headers})
target_compile_definitions(ProjectLib PRIVATE OCS_PROJECTLIB_TIMESTAMP="${ProjectLib_Timestamp}")
target_include_directories(ProjectLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_property(TARGET ProjectLib PROPERTY CXX_STANDARD 20)
set_property(TARGET ProjectLib PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ProjectLib PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (BUILD_PROJECTLIB_CLI)
	set(ProjectLibCLI_Sources src/cli/ProjectLibCLI.cpp)
	add_executable(ProjectLibCLI ${ProjectLibCLI_Sources})
	target_link_libraries(ProjectLibCLI PRIVATE ProjectLib)
	set_property(TARGET ProjectLibCLI PROPERTY CXX_STANDARD 20)
	set_property(TARGET ProjectLibCLI PROPERTY CXX_STANDARD_REQUIRED ON)
endif()
