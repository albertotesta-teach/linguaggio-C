cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(02-02-010-if-semplice                        010-if-semplice.c)
add_executable(02-02-020-if-else                            020-if-else.c)
add_executable(02-02-030-if-annidati-e-catene               030-if-annidati-e-catene.c)
add_executable(02-02-040-problema-equazione-secondo-grado   040-problema-equazione-secondo-grado.c)
add_executable(02-02-050-problema-tariffa-biglietto         050-problema-tariffa-biglietto.c)
add_executable(02-02-060-problema-classificazione-triangolo 060-problema-classificazione-triangolo.c)

# Libreria matematica (sqrt, pow, ...): necessaria su Linux, innocua su macOS
target_link_libraries(02-02-040-problema-equazione-secondo-grado m)
