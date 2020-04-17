
IF( LIBCLANG_INCLUDE_DIR AND LIBCLANG_LIBRARY )
    SET(LIBCLANG_FIND_QUIETLY TRUE)
ENDIF( LIBCLANG_INCLUDE_DIR AND LIBCLANG_LIBRARY )


# Ubuntu does not have libclang in the standard locations, unlike Arch Linux
# hence below in the HINTS section, possible locations in Ubuntu are listed out

IF ( UNIX )

   FIND_PATH( LIBCLANG_INCLUDE_DIR "clang-c/Index.h"  
   HINTS "/usr/lib/llvm-3.8/include"
         "/usr/lib/llvm-6.0/include"
         "/usr/lib/llvm-8/include"
         "/usr/lib/llvm-9/include"
         "/usr/lib/llvm-10/include"
         "/usr/lib/llvm-11/include"
         "/usr/lib/llvm-12/include"
   )
   FIND_LIBRARY(LIBCLANG_LIBRARY NAMES "clang" 
   HINTS "/usr/lib/llvm-3.8/lib"
         "/usr/lib/llvm-6.0/lib"
         "/usr/lib/llvm-8/lib"
         "/usr/lib/llvm-9/lib"
         "/usr/lib/llvm-10/lib"
         "/usr/lib/llvm-11/lib"
         "/usr/lib/llvm-12/lib"
   )

ELSE ( UNIX )

   FIND_PATH( LIBCLANG_INCLUDE_DIR "clang-c/Index.h"  )
   FIND_LIBRARY( LIBCLANG_LIBRARY NAMES "clang" )

ENDIF ( UNIX )

IF( LIBCLANG_LIBRARY AND LIBCLANG_INCLUDE_DIR )
        SET( CLANG_FOUND TRUE )
ENDIF( LIBCLANG_LIBRARY AND LIBCLANG_INCLUDE_DIR )

IF( LIBCLANG_LIBRARY )
        SET( LIBCLANG_LIBRARIES ${LIBCLANG_LIBRARY} )
ENDIF( LIBCLANG_LIBRARY )

IF( LIBCLANG_INCLUDE_DIR )
        SET( LIBCLANG_INCLUDE_DIRS ${LIBCLANG_INCLUDE_DIR} )
ENDIF( LIBCLANG_INCLUDE_DIR )

IF( CLANG_FOUND )
        IF( NOT LIBCLANG_FIND_QUIETLY )
                MESSAGE( STATUS "Found LibClang header files in ${LIBCLANG_INCLUDE_DIR}")
                MESSAGE( STATUS "Found LibClang libraries: ${LIBCLANG_LIBRARY}")
        ENDIF( NOT LIBCLANG_FIND_QUIETLY )
ELSE(CLANG_FOUND)
        IF( LIBCLANG_FIND_REQUIRED)
                MESSAGE( FATAL_ERROR "Could not find LibClang" )
        ELSE( LIBCLANG_FIND_REQUIRED)
                MESSAGE( STATUS "Optional package LibClang was not found" )
        ENDIF( LIBCLANG_FIND_REQUIRED)
		
ENDIF(CLANG_FOUND)


