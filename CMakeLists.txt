cmake_minimum_required(VERSION 3.20)
project(linguaggio-C C)

# Standard C utilizzato in tutto il progetto
set(CMAKE_C_STANDARD 11)

# Flag di compilazione: warning abilitati per tutti i target
add_compile_options(-Wall -Wextra)

# Inclusione delle sottocartelle degli esempi.
# Ogni cartella esempio ha il proprio CMakeLists.txt.

# ── 01 - Introduzione ────────────────────────────────────────────────────────
add_subdirectory(01-introduzione/01-hello-world)
add_subdirectory(01-introduzione/02-variabili-e-tipi)
add_subdirectory(01-introduzione/03-input-output)
add_subdirectory(01-introduzione/04-operatori)

# ── 03 - Funzioni ───────────────────────────────────────────────────────────
add_subdirectory(03-funzioni/01-definizione-e-chiamata)
add_subdirectory(03-funzioni/02-parametri-e-return)
add_subdirectory(03-funzioni/03-passaggio-per-riferimento)
add_subdirectory(03-funzioni/04-scope-e-visibilita)

# ── 04 - Array e stringhe ────────────────────────────────────────────────────
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/01-dichiarazione-e-inizializzazione)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/02-accesso-e-scorrimento)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/03-operazioni-su-array)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/04-array-e-funzioni)
add_subdirectory(04-array-e-stringhe/01-array-monodimensionali/05-array-a-tappo)
add_subdirectory(04-array-e-stringhe/03-stringhe/01-dichiarazione-e-inizializzazione)
add_subdirectory(04-array-e-stringhe/03-stringhe/02-input-output-stringhe)
add_subdirectory(04-array-e-stringhe/03-stringhe/03-lunghezza-e-accesso-ai-caratteri)
