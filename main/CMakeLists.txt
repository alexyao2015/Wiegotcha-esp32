# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

# idf_component_register(SRCS ${app_sources})
idf_component_register(
    SRCS
        fs.cpp
        http.cpp
        main.cpp
        wiegotcha.c
        wifi.cpp
    )
littlefs_create_partition_image(littlefs data FLASH_IN_PROJECT)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLOG_LOCAL_LEVEL=ESP_LOG_VERBOSE")
