# Analisi – 060-problema-giudizio-voto.c

## 1. Problema

Nel registro elettronico ogni voto in decimi va accompagnato da un giudizio
sintetico e da un livello di apprendimento. Dato un voto intero da 1 a 10,
il programma stampa giudizio, livello ed esito (sufficiente o insufficiente,
con i punti mancanti).

| Voto | Giudizio | Livello |
|------|----------|---------|
| 1–3 | gravemente insufficiente | non raggiunto |
| 4 | insufficiente | non raggiunto |
| 5 | mediocre | in via di acquisizione |
| 6 | sufficiente | base |
| 7 | discreto | intermedio |
| 8 | buono | intermedio |
| 9 | distinto | avanzato |
| 10 | ottimo | avanzato |

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `voto` | `int` | Voto in decimi, senza mezzi voti |
| `voto_valido` | `int` (0/1) | Voto nell'intervallo [1, 10] |

Il voto ha dieci valori discreti: due `switch` lo trasformano in giudizio e
livello. I raggruppamenti sono diversi nei due casi (il voto 4 ha un giudizio
proprio ma condivide il livello con 1–3), per questo gli `switch` sono due.
L'esito riguarda un intervallo (voto ≥ 6) e si esprime con un `if`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Voto sufficiente

**a) Input** – voto 8

**b) Output** – "Giudizio: buono", "Livello di apprendimento: intermedio",
"Esito: SUFFICIENTE"

**c) Variabili di supporto** – `voto_valido`

**d) Vincoli** – entrambi gli `switch` hanno il `default`, anche se il voto è
già stato controllato

**e) Assunzioni** – l'utente inserisce un numero intero

**f) Algoritmo in linguaggio naturale**
1. Leggere il voto.
2. Calcolare `voto_valido`; se falso stampare un errore e terminare.
3. Primo `switch`: stampare il giudizio.
4. Secondo `switch`: stampare il livello di apprendimento.
5. Se il voto è almeno 6 stampare "SUFFICIENTE", altrimenti "INSUFFICIENTE"
   con i punti mancanti (`6 - voto`), al singolare se manca un solo punto.

### Caso d'uso 2 – Voto insufficiente

**a) Input** – voto 5

**b) Output** – "mediocre", "in via di acquisizione",
"Esito: INSUFFICIENTE - manca 1 punto alla sufficienza"

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la scelta tra "manca/mancano" e "punto/punti" si fa con il
ternario

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Voto non valido

**a) Input** – voto 11 oppure 0

**b) Output** – "Voto 11 non valido."

**c) Variabili di supporto** – `voto_valido`

**d) Vincoli** – nessuno `switch` viene eseguito

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 2.
