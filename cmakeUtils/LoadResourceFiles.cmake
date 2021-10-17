cmake_minimum_required (VERSION 3.18)

function(LOAD_RESOURCE_DEFINITIONS RESOURCE_DIR OUT_DEBUG_DEFINITIONS OUT_RELEASE_DEFINITIONS)
    file(GLOB_RECURSE
        RESOURCE_LIST
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_DIR}
        "${RESOURCE_DIR}/*"
    )
    
    set(DEBUG_LIST )
    set(RELEASE_LIST )
    foreach(resource_file ${RESOURCE_LIST})
    
        # generate files definition name
        string(REGEX REPLACE "^\/" "" definition_name ${resource_file})
        string(REPLACE "/" "_" definition_name ${definition_name})
        string(REPLACE "\\" "_" definition_name ${definition_name})
        string(REPLACE "." "_" definition_name ${definition_name})
        string(TOUPPER ${definition_name} definition_name)
        
        # find files full path
        unset(resource_file_fullname CACHE)
        find_file(resource_file_fullname
            ${resource_file}
            HINTS ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_DIR}
        )
        
        # define files fill path as debug definition
        string(CONCAT resource_definition
            "RESOURCE_" ${definition_name} "=\"${resource_file_fullname}\""
        )

        # define file relative path as release definition
        string(CONCAT resource_definition_release
            "RESOURCE_" ${definition_name} "=\"${RESOURCE_DIR}/${resource_file}\""
        )

        # # print out json valid configuration for vscode
        # message(
        #     "\"RESOURCE_" ${definition_name} "=\\\"${resource_file_fullname}\\\"\","
        # )
        
        list(APPEND DEBUG_LIST ${resource_definition})
        list(APPEND RELEASE_LIST ${resource_definition_release})
    endforeach()
    
    set(${OUT_DEBUG_DEFINITIONS} ${DEBUG_LIST} PARENT_SCOPE)
    set(${OUT_RELEASE_DEFINITIONS} ${RELEASE_LIST} PARENT_SCOPE)
endfunction()
