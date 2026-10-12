cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-02-01-010-tipo-con-campi          010-tipo-con-campi.c)
add_executable(06-02-01-020-inizializzazione        020-inizializzazione.c)
add_executable(06-02-01-030-typedef-struct          030-typedef-struct.c)
add_executable(06-02-01-040-problema-scheda-libro   040-problema-scheda-libro.c)
add_executable(06-02-01-050-problema-distanza-gps   050-problema-distanza-gps.c)
add_executable(06-02-01-060-problema-durata-lezioni 060-problema-durata-lezioni.c)
add_executable(06-02-01-070-problema-somma-frazioni 070-problema-somma-frazioni.c)
add_executable(06-02-01-080-problema-carta-imbarco  080-problema-carta-imbarco.c)

# Libreria matematica (sqrt, pow, ...): necessaria su Linux, innocua su macOS
target_link_libraries(06-02-01-050-problema-distanza-gps m)
