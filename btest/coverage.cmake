set(GCOVR_COMMAND gcovr)
set(GCOVR_OPTIONS --html --output coverage.html --root ${CMAKE_SOURCE_DIR})

execute_process(
   COMMAND ${GCOVR_COMMAND} ${GCOVR_OPTIONS}
   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
   RESULT_VARIABLE GCOVR_RESULT
)

if(NOT ${GCOVR_RESULT} EQUAL 0)
   message(FATAL_ERROR "gcovr failed")
endif()
