cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(02-04-010-while-base                  010-while-base.c)
add_executable(02-04-020-ciclo-con-sentinella        020-ciclo-con-sentinella.c)
add_executable(02-04-030-do-while-validazione        030-do-while-validazione.c)
add_executable(02-04-040-problema-cifre-di-un-numero 040-problema-cifre-di-un-numero.c)
add_executable(02-04-050-problema-mcd-euclide        050-problema-mcd-euclide.c)
add_executable(02-04-060-problema-indovina-numero    060-problema-indovina-numero.c)
add_executable(02-04-070-problema-bancomat           070-problema-bancomat.c)
