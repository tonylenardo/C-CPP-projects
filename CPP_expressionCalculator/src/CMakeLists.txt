set(HEADER_LIST "${Calculadora_SOURCE_DIR}/include/*.hh")
add_executable(Calculadora calculadora.cpp token.cpp operation.cpp postfix.cpp tokenizer.cpp)
target_include_directories(
Calculadora
PUBLIC
"${Calculadora_SOURCE_DIR}/include")