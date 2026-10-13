cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(07-01-02-010-funzione-che-alloca       010-funzione-che-alloca.c)
add_executable(07-01-02-020-non-restituire-un-locale  020-non-restituire-un-locale.c)
add_executable(07-01-02-030-chi-libera                030-chi-libera.c)
add_executable(07-01-02-040-problema-unisci-stringhe  040-problema-unisci-stringhe.c)
add_executable(07-01-02-050-problema-tabella-dei-voti 050-problema-tabella-dei-voti.c)
add_executable(07-01-02-060-problema-filtra-misure    060-problema-filtra-misure.c)
add_executable(07-01-02-070-problema-elenco-iscritti  070-problema-elenco-iscritti.c)
add_executable(07-01-02-080-problema-torneo           080-problema-torneo.c)
