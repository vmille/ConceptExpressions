cmake_minimum_required(VERSION 3.5)
project(ConceptExpressions)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fconcepts)
endif()

add_subdirectory(ConceptSample)

add_subdirectory(CLoop)
add_subdirectory(ObjectOperator)
add_subdirectory(VirtualObject)
add_subdirectory(TemplateExpressions_1)
add_subdirectory(TemplateExpressions_2)
add_subdirectory(ConceptExpressions_1)
add_subdirectory(ConceptExpressions_2)
add_subdirectory(Metaclass)
