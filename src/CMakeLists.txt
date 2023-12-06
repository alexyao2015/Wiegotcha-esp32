# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources})
littlefs_create_partition_image(littlefs data FLASH_IN_PROJECT)
# message(FATAL_ERROR "sssdf")
add_custom_command(
  OUTPUT testing_command
  COMMAND touch ${CMAKE_SOURCE_DIR}/src/testing_command
  DEPENDS app
  )

add_custom_target(
  post_build_binary ALL
  DEPENDS testing_command
  )
# set_property(SOURCE ${COMPONENT_LIB} APPEND PROPERTY OBJECT_DEPENDS testing_command)


add_custom_command(
  OUTPUT some_file_your_command_produces.bin
  COMMAND ${CMAKE_COMMAND} -E echo "Helslo from post build step"
  DEPENDS app)
# add_custom_target(
#   post_build_binary ALL
#   DEPENDS some_file_your_command_produces.bin
#   )
target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLOG_LOCAL_LEVEL=ESP_LOG_VERBOSE")
