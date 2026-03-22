cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il nome del target corrisponde al nome del file senza estensione,
# in modo che CLion mostri il tasto play accanto a ciascun file.

add_executable(010-somma-e-media                    010-somma-e-media.c)
add_executable(020-minimo-massimo-e-ricerca         020-minimo-massimo-e-ricerca.c)
add_executable(030-trasformazione-elementi          030-trasformazione-elementi.c)
add_executable(040-problema-andamento-borsa         040-problema-andamento-borsa.c)
add_executable(050-problema-contatore-caratteri     050-problema-contatore-caratteri.c)
add_executable(060-problema-classifica-gara         060-problema-classifica-gara.c)
add_executable(070-problema-paghe-dipendenti        070-problema-paghe-dipendenti.c)
add_executable(080-problema-rilevamento-traffico    080-problema-rilevamento-traffico.c)
