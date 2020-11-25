cmake_minimum_required (VERSION 3.18)

if(NOT DEFINED ${${PROJECT_NAME}_RESOURCES})
    if(NOT DEFINED ${DEFAULT_RESOERCES_PATH})
        set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
    endif()
    set(${PROJECT_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")
endif()

message(${${PROJECT_NAME}_RESOURCES}/)

# generate resource definitions from RESOURCE_FILES based on their location
set(RESOURCES_DEBUG_COMPILE_DEFINITIONS )
set(RESOURCES_RELEASE_COMPILE_DEFINITIONS )
foreach(relative_file_name ${RESOURCE_FILES})

    unset(resource_file CACHE)

    # find full name of resource file
    find_file(resource_file
        ${relative_file_name}
        HINTS ${${PROJECT_NAME}_RESOURCES}/
    )

    # create shader definition string
    string(REPLACE "/" "_" definition_name ${relative_file_name})
    string(REPLACE "\\" "_" definition_name ${definition_name})
    string(REGEX REPLACE "\\..*" "" definition_name ${definition_name})
    string(TOUPPER ${definition_name} definition_name)

    string(CONCAT resource_definition
        "RESOURCE_" ${definition_name} "=\"" ${resource_file} "\""
    )

    string(CONCAT resource_definition_release
        "RESOURCE_" ${definition_name} "=\"resources/" ${relative_file_name} "\""
    )

    # json configuration print out for vs code
    # message(
    #     "\"RESOURCE_" ${definition_name} "=\\\"" ${resource_file} "\\\"\","
    # )

    message(${resource_definition})
    message(${resource_definition_release})

    # message(${resource_definition_release})

    # add resource_definition to RESOURCES_DEBUG_COMPILE_DEFINITIONS list
    list(APPEND RESOURCES_DEBUG_COMPILE_DEFINITIONS ${resource_definition})
    list(APPEND RESOURCES_RELEASE_COMPILE_DEFINITIONS ${resource_definition_release})
endforeach()
