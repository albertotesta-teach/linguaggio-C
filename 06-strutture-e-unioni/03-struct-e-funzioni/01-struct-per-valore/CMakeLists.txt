cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-03-01-010-parametro-per-valore           010-parametro-per-valore.c)
add_executable(06-03-01-020-struct-restituita              020-struct-restituita.c)
add_executable(06-03-01-030-costo-della-copia              030-costo-della-copia.c)
add_executable(06-03-01-040-problema-calcolatrice-frazioni 040-problema-calcolatrice-frazioni.c)
add_executable(06-03-01-050-problema-orari-treni           050-problema-orari-treni.c)
add_executable(06-03-01-060-problema-banchi-laboratorio    060-problema-banchi-laboratorio.c)
add_executable(06-03-01-070-problema-cambio-valuta         070-problema-cambio-valuta.c)
add_executable(06-03-01-080-problema-impedenze-circuito    080-problema-impedenze-circuito.c)

# Libreria matematica (sqrt, pow, ...): necessaria su Linux, innocua su macOS
target_link_libraries(06-03-01-080-problema-impedenze-circuito m)
