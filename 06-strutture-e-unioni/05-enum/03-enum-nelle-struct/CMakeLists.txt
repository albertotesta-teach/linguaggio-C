cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-05-03-010-campo-enum                  010-campo-enum.c)
add_executable(06-05-03-020-macchina-a-stati            020-macchina-a-stati.c)
add_executable(06-05-03-030-tabella-indicizzata-da-enum 030-tabella-indicizzata-da-enum.c)
add_executable(06-05-03-040-problema-ticket-assistenza  040-problema-ticket-assistenza.c)
add_executable(06-05-03-050-problema-ascensore          050-problema-ascensore.c)
add_executable(06-05-03-060-problema-tessere-mensa      060-problema-tessere-mensa.c)
add_executable(06-05-03-070-problema-gioco-tris         070-problema-gioco-tris.c)
add_executable(06-05-03-080-problema-analisi-testo      080-problema-analisi-testo.c)
