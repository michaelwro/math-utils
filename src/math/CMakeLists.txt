target_sources(mathutils
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/crossProductMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Euler321.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/quaternionToDCM.cpp
)
