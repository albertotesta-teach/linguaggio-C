cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-04-01-010-campo-struct                    010-campo-struct.c)
add_executable(06-04-01-020-inizializzazione-annidata       020-inizializzazione-annidata.c)
add_executable(06-04-01-030-copia-e-confronto-annidati      030-copia-e-confronto-annidati.c)
add_executable(06-04-01-040-problema-prestiti-biblioteca    040-problema-prestiti-biblioteca.c)
add_executable(06-04-01-050-problema-anagrafica-studenti    050-problema-anagrafica-studenti.c)
add_executable(06-04-01-060-problema-pianta-del-laboratorio 060-problema-pianta-del-laboratorio.c)
add_executable(06-04-01-070-problema-visite-museo           070-problema-visite-museo.c)
add_executable(06-04-01-080-problema-tratte-ferroviarie     080-problema-tratte-ferroviarie.c)

# Libreria matematica (sqrt, pow, ...): necessaria su Linux, innocua su macOS
target_link_libraries(06-04-01-060-problema-pianta-del-laboratorio m)
