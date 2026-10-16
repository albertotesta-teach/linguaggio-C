cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(08-01-01-010-fopen-e-fclose                   010-fopen-e-fclose.c)
add_executable(08-01-01-020-modalita-di-apertura             020-modalita-di-apertura.c)
add_executable(08-01-01-030-file-che-non-esiste              030-file-che-non-esiste.c)
add_executable(08-01-01-040-problema-diario-delle-uscite     040-problema-diario-delle-uscite.c)
add_executable(08-01-01-050-problema-copia-di-un-file        050-problema-copia-di-un-file.c)
add_executable(08-01-01-060-problema-registro-del-giorno     060-problema-registro-del-giorno.c)
add_executable(08-01-01-070-problema-statistiche-di-un-testo 070-problema-statistiche-di-un-testo.c)
add_executable(08-01-01-080-problema-confronto-di-due-file   080-problema-confronto-di-due-file.c)
