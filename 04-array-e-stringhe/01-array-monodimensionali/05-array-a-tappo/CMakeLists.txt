cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il nome del target corrisponde al nome del file senza estensione,
# in modo che CLion mostri il tasto play accanto a ciascun file.

add_executable(010-introduzione-al-tappo            010-introduzione-al-tappo.c)
add_executable(020-operazioni-con-tappo             020-operazioni-con-tappo.c)
add_executable(030-tappo-su-array-di-char           030-tappo-su-array-di-char.c)
add_executable(040-problema-lista-della-spesa       040-problema-lista-della-spesa.c)
add_executable(050-problema-log-eventi              050-problema-log-eventi.c)
add_executable(060-problema-coda-prenotazioni       060-problema-coda-prenotazioni.c)
add_executable(070-problema-sensori-attivi          070-problema-sensori-attivi.c)
add_executable(080-problema-playlist-musicale       080-problema-playlist-musicale.c)
