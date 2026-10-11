cmake_minimum_required(VERSION 3.20)

# Un target eseguibile per ciascun file .c dell'esempio.
# Il prefisso del capitolo e della sezione rende il nome unico nel progetto.

add_executable(04-04-02-010-strlen-e-strcpy                  010-strlen-e-strcpy.c)
add_executable(04-04-02-020-strcat-e-strncat                 020-strcat-e-strncat.c)
add_executable(04-04-02-030-strcmp-e-strncmp                 030-strcmp-e-strncmp.c)
add_executable(04-04-02-040-problema-indirizzo-postale       040-problema-indirizzo-postale.c)
add_executable(04-04-02-050-problema-cambio-password         050-problema-cambio-password.c)
add_executable(04-04-02-060-problema-login                   060-problema-login.c)
add_executable(04-04-02-070-problema-prefissi-telefonici     070-problema-prefissi-telefonici.c)
add_executable(04-04-02-080-problema-elezione-rappresentanti 080-problema-elezione-rappresentanti.c)
