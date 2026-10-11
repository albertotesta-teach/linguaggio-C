cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il nome del target è il nome del file senza estensione preceduto da "01-"
# (numero della sezione, come nelle altre cartelle delle stringhe), per non coincidere con target di altre cartelle.

add_executable(01-010-stringa-base            010-stringa-base.c)
add_executable(01-020-inizializzazione        020-inizializzazione.c)
add_executable(01-030-memoria-e-terminatore   030-memoria-e-terminatore.c)
add_executable(01-040-problema-codice-fiscale 040-problema-codice-fiscale.c)
add_executable(01-050-problema-targa          050-problema-targa.c)
add_executable(01-060-problema-codice-prodotto 060-problema-codice-prodotto.c)
