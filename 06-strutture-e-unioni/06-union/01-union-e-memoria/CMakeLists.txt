cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(06-06-01-010-campi-sovrapposti          010-campi-sovrapposti.c)
add_executable(06-06-01-020-un-campo-alla-volta        020-un-campo-alla-volta.c)
add_executable(06-06-01-030-vedere-i-byte              030-vedere-i-byte.c)
add_executable(06-06-01-040-problema-indirizzo-ip      040-problema-indirizzo-ip.c)
add_executable(06-06-01-050-problema-colore-rgba       050-problema-colore-rgba.c)
add_executable(06-06-01-060-problema-anatomia-float    060-problema-anatomia-float.c)
add_executable(06-06-01-070-problema-pacchetto-sensore 070-problema-pacchetto-sensore.c)
add_executable(06-06-01-080-problema-risparmio-memoria 080-problema-risparmio-memoria.c)
