cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(08-01-02-010-stdin-stdout-stderr                010-stdin-stdout-stderr.c)
add_executable(08-01-02-020-una-funzione-per-ogni-flusso       020-una-funzione-per-ogni-flusso.c)
add_executable(08-01-02-030-redirezione                        030-redirezione.c)
add_executable(08-01-02-040-problema-pagella-a-video-e-su-file 040-problema-pagella-a-video-e-su-file.c)
add_executable(08-01-02-050-problema-filtro-maiuscole          050-problema-filtro-maiuscole.c)
add_executable(08-01-02-060-problema-registro-degli-errori     060-problema-registro-degli-errori.c)
add_executable(08-01-02-070-problema-numerazione-delle-righe   070-problema-numerazione-delle-righe.c)
add_executable(08-01-02-080-problema-rapporto-multiplo         080-problema-rapporto-multiplo.c)
