
file(GLOB_RECURSE jni_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library( # Sets the name of the library.
             testmultone-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
              ${jni_src}
             )


find_library( # Sets the name of the path variable.
                      log-lib

                      # Specifies the name of the NDK library that
                      # you want CMake to locate.
                      log )

target_link_libraries( # Specifies the target library.
                       testmultone-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )