cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il nome del target corrisponde al nome del file senza estensione,
# in modo che CLion mostri il tasto play accanto a ciascun file.

add_executable(010-accesso-per-indice                   010-accesso-per-indice.c)
add_executable(020-scorrimento-con-cicli                020-scorrimento-con-cicli.c)
add_executable(030-lettura-da-tastiera                  030-lettura-da-tastiera.c)
add_executable(040-problema-rilevazioni-pluviometriche  040-problema-rilevazioni-pluviometriche.c)
add_executable(050-problema-cassa-automatica            050-problema-cassa-automatica.c)
add_executable(060-problema-rubrica-telefonica          060-problema-rubrica-telefonica.c)
add_executable(070-problema-sensori-industriali         070-problema-sensori-industriali.c)
add_executable(080-problema-questionario                080-problema-questionario.c)
