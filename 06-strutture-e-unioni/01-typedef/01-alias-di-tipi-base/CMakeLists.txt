cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-01-01-010-nome-a-un-tipo                010-nome-a-un-tipo.c)
add_executable(06-01-01-020-cambiare-tipo-in-un-punto     020-cambiare-tipo-in-un-punto.c)
add_executable(06-01-01-030-alias-non-tipo-nuovo          030-alias-non-tipo-nuovo.c)
add_executable(06-01-01-040-problema-registro-temperature 040-problema-registro-temperature.c)
add_executable(06-01-01-050-problema-scontrino-mensa      050-problema-scontrino-mensa.c)
add_executable(06-01-01-060-problema-consumo-acqua        060-problema-consumo-acqua.c)
add_executable(06-01-01-070-problema-cronometro           070-problema-cronometro.c)
add_executable(06-01-01-080-problema-media-pesata         080-problema-media-pesata.c)
