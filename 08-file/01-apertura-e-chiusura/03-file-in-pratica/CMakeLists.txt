cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(08-01-03-010-piu-file-aperti               010-piu-file-aperti.c)
add_executable(08-01-03-020-buffer-e-fflush               020-buffer-e-fflush.c)
add_executable(08-01-03-030-rimuovere-e-rinominare        030-rimuovere-e-rinominare.c)
add_executable(08-01-03-040-problema-salvataggio-sicuro   040-problema-salvataggio-sicuro.c)
add_executable(08-01-03-050-problema-divisione-per-classe 050-problema-divisione-per-classe.c)
add_executable(08-01-03-060-problema-unione-di-file       060-problema-unione-di-file.c)
add_executable(08-01-03-070-problema-copie-di-sicurezza   070-problema-copie-di-sicurezza.c)
add_executable(08-01-03-080-problema-file-di-blocco       080-problema-file-di-blocco.c)
