cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-05-02-010-switch-su-enum                   010-switch-su-enum.c)
add_executable(06-05-02-020-funzioni-con-enum                020-funzioni-con-enum.c)
add_executable(06-05-02-030-da-testo-a-enum                  030-da-testo-a-enum.c)
add_executable(06-05-02-040-problema-distributore-bevande    040-problema-distributore-bevande.c)
add_executable(06-05-02-050-problema-giudizio-sintetico      050-problema-giudizio-sintetico.c)
add_executable(06-05-02-060-problema-calcolatrice-operazioni 060-problema-calcolatrice-operazioni.c)
add_executable(06-05-02-070-problema-direzioni-robot         070-problema-direzioni-robot.c)
add_executable(06-05-02-080-problema-esito-prenotazione      080-problema-esito-prenotazione.c)

# Libreria matematica (sqrt, pow, ...): necessaria su Linux, innocua su macOS
target_link_libraries(06-05-02-010-switch-su-enum m)
