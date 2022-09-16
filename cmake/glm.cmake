if (DEFINED GLM_IGNORE_PATHS)
    list(APPEND CMAKE_IGNORE_PREFIX_PATH ${GLM_IGNORE_PATHS})
endif ()

find_package(glm CONFIG)

if (NOT glm_FOUND)
    include(FetchContent)
    message(STATUS "Installing GLM")

    option(GLM_TEST_ENABLE "Disable" OFF)

    FetchContent_Declare(
            glm_external
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_PROGRESS TRUE)

    FetchContent_MakeAvailable(glm_external)
endif ()