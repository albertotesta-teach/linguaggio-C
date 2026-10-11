cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(05-01-03-010-non-inizializzato-e-null             010-non-inizializzato-e-null.c)
add_executable(05-01-03-020-tipi-dei-puntatori                   020-tipi-dei-puntatori.c)
add_executable(05-01-03-030-puntatori-const                      030-puntatori-const.c)
add_executable(05-01-03-040-problema-configurazione-sola-lettura 040-problema-configurazione-sola-lettura.c)
add_executable(05-01-03-050-problema-statistiche-facoltative     050-problema-statistiche-facoltative.c)
add_executable(05-01-03-060-problema-correzione-errori           060-problema-correzione-errori.c)
add_executable(05-01-03-070-problema-selezione-sicura            070-problema-selezione-sicura.c)
add_executable(05-01-03-080-problema-limiti-di-sicurezza         080-problema-limiti-di-sicurezza.c)
