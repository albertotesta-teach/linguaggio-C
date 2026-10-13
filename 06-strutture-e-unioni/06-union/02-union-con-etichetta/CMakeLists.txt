cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-06-02-010-etichetta-enum              010-etichetta-enum.c)
add_executable(06-06-02-020-switch-sull-etichetta       020-switch-sull-etichetta.c)
add_executable(06-06-02-030-funzioni-costruttrici       030-funzioni-costruttrici.c)
add_executable(06-06-02-040-problema-figure-geometriche 040-problema-figure-geometriche.c)
add_executable(06-06-02-050-problema-celle-foglio       050-problema-celle-foglio.c)
add_executable(06-06-02-060-problema-pagamenti-bar      060-problema-pagamenti-bar.c)
add_executable(06-06-02-070-problema-catalogo-media     070-problema-catalogo-media.c)
add_executable(06-06-02-080-problema-risultati-misure   080-problema-risultati-misure.c)

# Libreria matematica (sqrt, pow, ...): necessaria su Linux, innocua su macOS
target_link_libraries(06-06-02-040-problema-figure-geometriche m)
