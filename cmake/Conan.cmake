macro(run_conan)
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
    endif ()

    set(ENV{CONAN_REVISIONS_ENABLED} 1)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    # Add (or remove) remotes as needed
    # conan_add_remote(NAME conan-center URL https://conan.bintray.com)
    conan_add_remote(NAME cci URL https://center.conan.io INDEX 0)
    conan_add_remote(
            NAME bincrafters URL
            https://bincrafters.jfrog.io/artifactory/api/conan/public-conan)

    conan_cmake_autodetect(settings)

    conan_cmake_install(
            PATH_OR_REFERENCE
            ${CMAKE_SOURCE_DIR}
            BUILD missing
            SETTINGS ${settings})

endmacro()