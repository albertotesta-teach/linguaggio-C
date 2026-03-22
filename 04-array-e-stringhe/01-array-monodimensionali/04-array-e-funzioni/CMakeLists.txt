cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il nome del target corrisponde al nome del file senza estensione,
# in modo che CLion mostri il tasto play accanto a ciascun file.

add_executable(010-passaggio-array-a-funzione     010-passaggio-array-a-funzione.c)
add_executable(020-funzioni-su-array              020-funzioni-su-array.c)
add_executable(030-funzioni-che-modificano-array  030-funzioni-che-modificano-array.c)
add_executable(040-problema-normalizzazione-misure 040-problema-normalizzazione-misure.c)
add_executable(050-problema-cifrario-cesare       050-problema-cifrario-cesare.c)
add_executable(060-problema-gestione-magazzino    060-problema-gestione-magazzino.c)
add_executable(070-problema-analisi-partita       070-problema-analisi-partita.c)
add_executable(080-problema-registro-presenze     080-problema-registro-presenze.c)
