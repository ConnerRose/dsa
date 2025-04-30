file(GLOB TEST_SOURCES "*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME} containers)

  if (CMAKE_BUILD_TYPE MATCHES "DebugGit")
    target_compile_options(${TEST_NAME} PRIVATE -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer -Wall -Wextra -Werror -pedantic)
    target_link_options(${TEST_NAME} PRIVATE -fsanitize=address -fsanitize=leak)
  else()
    target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -g -O3)
  endif()
endforeach()
