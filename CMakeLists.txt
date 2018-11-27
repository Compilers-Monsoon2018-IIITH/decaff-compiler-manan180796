cmake_minimum_required(VERSION 3.10)

project(Decaf_Compiler)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ldl -lfl")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_FLEX_BISON_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/flex_bison_output)

# Create the directory for flex and bison outputs
file(MAKE_DIRECTORY ${CMAKE_FLEX_BISON_OUTPUT_DIRECTORY})

# Setup the required Libraries
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
find_package(BISON)
find_package(FLEX)

# Link the directories which contain required libraries
link_directories(/usr/lib/llvm-6.0/build/lib)

include_directories(/usr/lib/llvm-6.0/build/include)
include_directories(include)

BISON_TARGET(Parser parser.y    ${CMAKE_FLEX_BISON_OUTPUT_DIRECTORY}/parser.tab.c 
                                DEFINES_FILE ${CMAKE_FLEX_BISON_OUTPUT_DIRECTORY}/parser.tab.h )
FLEX_TARGET(Lexer scanner.l ${CMAKE_FLEX_BISON_OUTPUT_DIRECTORY}/lex.yy.c)


add_library(coreLibrary SHARED
    src/ArgumentDeclaration.cpp
    src/ArgumentDeclarationList.cpp
    src/AssignmentStatement.cpp
    src/BinaryExpression.cpp
    src/Block.cpp
    src/BoolLiteral.cpp
    src/BreakStatement.cpp
    src/CalloutArg.cpp
    src/CalloutArgList.cpp
    src/CalloutMethod.cpp
    src/CharLiteral.cpp
    src/ContinueStatement.cpp
    src/Expression.cpp
    src/ExpressionList.cpp
    src/Field.cpp
    src/FieldDeclaration.cpp
    src/FieldDeclarationList.cpp
    src/FieldList.cpp
    src/ForStatement.cpp
    src/IdList.cpp
    src/IfStatement.cpp
    src/IntLiteral.cpp
    src/LLVMIRGenerator.cpp
    src/Location.cpp
    src/MethodDeclaration.cpp
    src/MethodDeclarationList.cpp
    src/MethodStatement.cpp
    src/NestedUnaryExpression.cpp
    src/Program.cpp
    src/ReturnExpression.cpp
    src/SimpleMethod.cpp
    src/StatementList.cpp
    src/UnaryOperation.cpp
    src/VariableDeclaration.cpp
    src/VariableDeclarationList.cpp
)



# Add the main executable
add_executable(decafCompiler
${BISON_Parser_OUTPUTS}
${FLEX_Lexer_OUTPUTS})
target_link_libraries(decafCompiler coreLibrary)

target_include_directories(decafCompiler PRIVATE
        ${CMAKE_FLEX_BISON_OUTPUT_DIRECTORY})

llvm_map_components_to_libnames(llvm_libs support core irreader mcjit native)
target_link_libraries(decafCompiler ${llvm_libs})