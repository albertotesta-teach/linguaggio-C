cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(07-01-03-010-memory-leak                      010-memory-leak.c)
add_executable(07-01-03-020-doppio-free-e-puntatore-pendente 020-doppio-free-e-puntatore-pendente.c)
add_executable(07-01-03-030-fuori-dai-limiti                 030-fuori-dai-limiti.c)
add_executable(07-01-03-040-problema-contatore-allocazioni   040-problema-contatore-allocazioni.c)
add_executable(07-01-03-050-problema-riga-sicura             050-problema-riga-sicura.c)
add_executable(07-01-03-060-problema-prestiti-attrezzatura   060-problema-prestiti-attrezzatura.c)
add_executable(07-01-03-070-problema-copia-del-registro      070-problema-copia-del-registro.c)
add_executable(07-01-03-080-problema-archivio-foto           080-problema-archivio-foto.c)
