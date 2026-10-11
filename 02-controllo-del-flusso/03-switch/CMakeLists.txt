cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(02-03-010-switch-base                   010-switch-base.c)
add_executable(02-03-020-casi-raggruppati              020-casi-raggruppati.c)
add_executable(02-03-030-switch-su-caratteri           030-switch-su-caratteri.c)
add_executable(02-03-040-problema-giorni-del-mese      040-problema-giorni-del-mese.c)
add_executable(02-03-050-problema-distributore-bevande 050-problema-distributore-bevande.c)
add_executable(02-03-060-problema-giudizio-voto        060-problema-giudizio-voto.c)
