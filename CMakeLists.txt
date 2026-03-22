cmake_minimum_required(VERSION 3.20)
project(linguaggio-C C)

# Standard C utilizzato in tutto il progetto
set(CMAKE_C_STANDARD 11)

# Flag di compilazione: warning abilitati per tutti i target
add_compile_options(-Wall -Wextra)

# Inclusione delle sottocartelle degli esempi.
# Ogni cartella esempio ha il proprio CMakeLists.txt.
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/01-dichiarazione-e-inizializzazione)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/02-accesso-e-scorrimento)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/03-operazioni-su-array)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/04-array-e-funzioni)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/05-array-a-tappo)
add_subdirectory(04-array-e-stringhe/03-stringhe/01-dichiarazione-e-inizializzazione)
add_subdirectory(04-array-e-stringhe/03-stringhe/02-input-output-stringhe)
add_subdirectory(04-array-e-stringhe/03-stringhe/03-lunghezza-e-accesso-ai-caratteri)
