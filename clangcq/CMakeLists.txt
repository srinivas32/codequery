cmake_minimum_required(VERSION 3.2.2)
project(CQClang)

find_package(LibClang REQUIRED)
find_package(Sqlite REQUIRED)

include_directories( "." )
include_directories( "../querylib" )
include_directories( "${LIBCLANG_INCLUDE_DIRS}" )
include_directories( "${SQLITE_INCLUDE_DIR}" )


set( CQCLANG_SRCS
     main_cqclang.cpp
   )

add_executable( cqclang ${CQCLANG_SRCS} )
target_link_libraries( cqclang ${LIBCLANG_LIBRARIES} ${SQLITE_LIBRARIES} small_lib )

install(TARGETS cqclang RUNTIME DESTINATION bin)

