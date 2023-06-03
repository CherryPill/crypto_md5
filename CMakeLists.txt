cmake_minimum_required(VERSION 3.21)

project(md5_hash_tool)

set(CMAKE_C_STANDARD 11)
set_source_files_properties(src/res/crypto_md5.rc PROPERTIES)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${C_INCLUDE_PATH}/include)
link_directories(${C_INCLUDE_PATH}/lib)

add_executable(md5_hash_tool WIN32
        src/main.c
        src/res/crypto_md5.rc
        src/io/fileIO.c
        src/global/globalVars.c
        src/global/globalVars.h
        src/enc/hashing.c
        src/proc/mainwindowProc.c
        src/util/utility.c
        src/ui/view.c
        src/res/resource1.h
        src/handler/error_handler.c
        src/handler/error_handler.h
        src/consts/text_consts.c
        src/consts/text_consts.h
)


target_link_libraries(md5_hash_tool comctl32)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_link_options(md5_hash_tool PRIVATE "LINKER:/MANIFEST:NO")
endif ()

