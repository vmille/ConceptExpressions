cmake_minimum_required(VERSION 3.5)
project(ConceptExpressions)
add_compile_options(-fconcepts)

add_subdirectory(CLoop)
add_subdirectory(TemplateExpressions)
add_subdirectory(ConceptExpressions)
add_subdirectory(OperatorConceptExpressions)
