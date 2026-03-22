cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il nome del target corrisponde al nome del file senza estensione,
# in modo che CLion mostri il tasto play accanto a ciascun file.

add_executable(010-dichiarazione-base               010-dichiarazione-base.c)
add_executable(020-inizializzazione                 020-inizializzazione.c)
add_executable(030-array-in-memoria                 030-array-in-memoria.c)
add_executable(040-problema-lancio-dado             040-problema-lancio-dado.c)
add_executable(050-problema-distribuzione-voti      050-problema-distribuzione-voti.c)
add_executable(060-problema-registro-voti           060-problema-registro-voti.c)
add_executable(070-problema-inventario-magazzino    070-problema-inventario-magazzino.c)
add_executable(080-problema-temperature-settimanali 080-problema-temperature-settimanali.c)
