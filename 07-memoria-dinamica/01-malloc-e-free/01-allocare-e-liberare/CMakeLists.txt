cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(07-01-01-010-prima-malloc                    010-prima-malloc.c)
add_executable(07-01-01-020-array-di-dimensione-scelta      020-array-di-dimensione-scelta.c)
add_executable(07-01-01-030-struct-allocata                 030-struct-allocata.c)
add_executable(07-01-01-040-problema-voti-della-verifica    040-problema-voti-della-verifica.c)
add_executable(07-01-01-050-problema-misure-del-laboratorio 050-problema-misure-del-laboratorio.c)
add_executable(07-01-01-060-problema-scheda-studente        060-problema-scheda-studente.c)
add_executable(07-01-01-070-problema-posti-della-gita       070-problema-posti-della-gita.c)
add_executable(07-01-01-080-problema-copia-di-una-stringa   080-problema-copia-di-una-stringa.c)

# Libreria matematica (sqrt, pow, ...): necessaria su Linux, innocua su macOS
target_link_libraries(07-01-01-050-problema-misure-del-laboratorio m)
