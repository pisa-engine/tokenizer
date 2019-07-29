EXECUTE_PROCESS(COMMAND git submodule update --init
                WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
                OUTPUT_QUIET
        )

if (NOT TARGET Catch2)
# Add Catch
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Catch2)
endif()

if (NOT TARGET Boost::boost)
# Add Boost
add_subdirectory(boost-cmake)
endif()
