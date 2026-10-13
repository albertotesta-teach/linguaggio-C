cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(07-02-01-010-calloc-azzera                   010-calloc-azzera.c)
add_executable(07-02-01-020-contatori-con-calloc            020-contatori-con-calloc.c)
add_executable(07-02-01-030-matrice-azzerata                030-matrice-azzerata.c)
add_executable(07-02-01-040-problema-istogramma-dei-voti    040-problema-istogramma-dei-voti.c)
add_executable(07-02-01-050-problema-presenze-del-mese      050-problema-presenze-del-mese.c)
add_executable(07-02-01-060-problema-parole-per-lunghezza   060-problema-parole-per-lunghezza.c)
add_executable(07-02-01-070-problema-posti-a-teatro         070-problema-posti-a-teatro.c)
add_executable(07-02-01-080-problema-crivello-di-eratostene 080-problema-crivello-di-eratostene.c)
