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

# ── 02 - Controllo del flusso ───────────────────────────────────────────
add_subdirectory(02-controllo-del-flusso/01-logica-booleana)
add_subdirectory(02-controllo-del-flusso/02-if-else)
add_subdirectory(02-controllo-del-flusso/03-switch)
add_subdirectory(02-controllo-del-flusso/04-while-do-while)
add_subdirectory(02-controllo-del-flusso/05-for)
add_subdirectory(02-controllo-del-flusso/06-break-continue)

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
add_subdirectory(04-array-e-stringhe/02-array-multidimensionali/01-dichiarazione-e-inizializzazione)
add_subdirectory(04-array-e-stringhe/02-array-multidimensionali/02-accesso-e-scorrimento)
add_subdirectory(04-array-e-stringhe/02-array-multidimensionali/03-operazioni-su-matrici)
add_subdirectory(04-array-e-stringhe/02-array-multidimensionali/04-matrici-e-funzioni)
add_subdirectory(04-array-e-stringhe/02-array-multidimensionali/05-griglie-di-caratteri)
add_subdirectory(04-array-e-stringhe/03-stringhe/01-dichiarazione-e-inizializzazione)
add_subdirectory(04-array-e-stringhe/03-stringhe/02-input-output-stringhe)
add_subdirectory(04-array-e-stringhe/03-stringhe/03-lunghezza-e-accesso-ai-caratteri)
add_subdirectory(04-array-e-stringhe/04-funzioni-su-stringhe/01-funzioni-scritte-a-mano)
add_subdirectory(04-array-e-stringhe/04-funzioni-su-stringhe/02-libreria-string-h)
add_subdirectory(04-array-e-stringhe/04-funzioni-su-stringhe/03-ricerca-nelle-stringhe)
add_subdirectory(04-array-e-stringhe/04-funzioni-su-stringhe/04-caratteri-e-conversioni)
add_subdirectory(04-array-e-stringhe/04-funzioni-su-stringhe/05-array-di-stringhe)

# ── 05 - Puntatori ───────────────────────────────────────────────────────────
add_subdirectory(05-puntatori/01-introduzione-ai-puntatori/01-indirizzi-e-memoria)
add_subdirectory(05-puntatori/01-introduzione-ai-puntatori/02-dichiarazione-e-dereferenziazione)
add_subdirectory(05-puntatori/01-introduzione-ai-puntatori/03-errori-e-puntatori-sicuri)
add_subdirectory(05-puntatori/02-puntatori-e-array/01-aritmetica-dei-puntatori)
add_subdirectory(05-puntatori/02-puntatori-e-array/02-array-come-puntatori)
add_subdirectory(05-puntatori/02-puntatori-e-array/03-stringhe-e-puntatori)
add_subdirectory(05-puntatori/03-puntatori-e-funzioni/01-parametri-per-riferimento)
add_subdirectory(05-puntatori/03-puntatori-e-funzioni/02-funzioni-che-restituiscono-puntatori)
add_subdirectory(05-puntatori/03-puntatori-e-funzioni/03-puntatori-a-funzione)
add_subdirectory(05-puntatori/04-puntatori-a-puntatori/01-doppio-puntatore)
add_subdirectory(05-puntatori/04-puntatori-a-puntatori/02-array-di-puntatori)
add_subdirectory(05-puntatori/04-puntatori-a-puntatori/03-matrici-e-puntatori)
add_subdirectory(06-strutture-e-unioni/01-typedef/01-alias-di-tipi-base)
add_subdirectory(06-strutture-e-unioni/01-typedef/02-typedef-di-array)
add_subdirectory(06-strutture-e-unioni/01-typedef/03-typedef-di-puntatori-a-funzione)
add_subdirectory(06-strutture-e-unioni/02-struct/01-dichiarazione-e-accesso)
add_subdirectory(06-strutture-e-unioni/02-struct/02-assegnamento-e-confronto)
add_subdirectory(06-strutture-e-unioni/02-struct/03-array-di-struct)
