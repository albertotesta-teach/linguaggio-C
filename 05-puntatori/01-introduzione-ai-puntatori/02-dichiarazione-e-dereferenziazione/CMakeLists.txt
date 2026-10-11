cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(05-01-02-010-dichiarazione-e-uso            010-dichiarazione-e-uso.c)
add_executable(05-01-02-020-piu-puntatori-stessa-variabile 020-piu-puntatori-stessa-variabile.c)
add_executable(05-01-02-030-puntatore-null                 030-puntatore-null.c)
add_executable(05-01-02-040-problema-termostato            040-problema-termostato.c)
add_executable(05-01-02-050-problema-giocatore-di-turno    050-problema-giocatore-di-turno.c)
add_executable(05-01-02-060-problema-conto-attivo          060-problema-conto-attivo.c)
add_executable(05-01-02-070-problema-riordino-scorte       070-problema-riordino-scorte.c)
add_executable(05-01-02-080-problema-record-gara           080-problema-record-gara.c)
