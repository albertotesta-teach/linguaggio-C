cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il nome del target corrisponde al nome del file senza estensione,
# in modo che CLion mostri il tasto play accanto a ciascun file.

add_executable(010-stringa-base          010-stringa-base.c)
add_executable(020-inizializzazione      020-inizializzazione.c)
add_executable(030-memoria-e-terminatore 030-memoria-e-terminatore.c)
add_executable(040-problema-codice-fiscale  040-problema-codice-fiscale.c)
add_executable(050-problema-targa          050-problema-targa.c)
add_executable(060-problema-codice-prodotto 060-problema-codice-prodotto.c)
