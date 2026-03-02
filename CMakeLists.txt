cmake_minimum_required(VERSION 3.20)
project(linguaggio-C C)

# Standard C utilizzato in tutto il progetto
set(CMAKE_C_STANDARD 11)

# Flag di compilazione: warning abilitati per tutti i target
add_compile_options(-Wall -Wextra)

# Inclusione delle sottocartelle degli esempi.
# Ogni cartella esempio ha il proprio CMakeLists.txt.
add_subdirectory(04-array-e-stringhe/03-stringhe/01-dichiarazione-e-inizializzazione)
add_subdirectory(04-array-e-stringhe/03-stringhe/02-input-output-stringhe)
add_subdirectory(04-array-e-stringhe/03-stringhe/03-lunghezza-e-accesso-ai-caratteri)
