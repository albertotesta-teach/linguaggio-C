# Analisi – 040-problema-media-mobile.c

## 1. Problema

Un sensore misura la CO2 in un'aula ogni 5 minuti a partire dalle 8:00.
Per non reagire a una singola lettura disturbata si calcola la media di 3
letture consecutive (media mobile) e si segnala quando supera 1000 ppm,
indicando l'orario del gruppo e il primo allarme.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `letture` | `int[]` | 12 | Letture in ppm, in ordine di tempo |
| `fine` | `const int *` | — | Indirizzo subito dopo l'ultima lettura |
| `finestra` | `const int *` | — | Prima lettura del gruppo di 3 |
| `primo_allarme` | `const int *` | — | Primo gruppo oltre soglia, `NULL` se nessuno |
| `media`, `allarmi` | `int` | — | Media del gruppo, numero di gruppi oltre soglia |

| Funzione | Compito |
|----------|---------|
| `stampa_orario` | Converte l'indice di una lettura in orario hh:mm |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Calcolo della media mobile

**a) Input** – le 12 letture dell'array

**b) Output** – 10 righe, una per gruppo, con orario, letture e media

**c) Variabili di supporto** – `finestra`, `media`

**d) Vincoli** – il gruppo non deve uscire dall'array: l'ultima posizione
valida è `fine - LARGHEZZA`

**e) Assunzioni** – media intera (troncata)

**f) Algoritmo in linguaggio naturale**
1. Partire con `finestra` sulla prima lettura.
2. Finché `finestra <= fine - 3`, calcolare la media di `*finestra`,
   `*(finestra + 1)` e `*(finestra + 2)`.
3. Avanzare con `finestra++`.

### Caso d'uso 2 – Segnalazione oltre soglia

**a) Input** – gruppi con media 1043, 1083, 1023

**b) Output** – "<- aprire le finestre" accanto ai tre gruppi

**c) Variabili di supporto** – `allarmi`, `primo_allarme`

**d) Vincoli** – `primo_allarme` si assegna solo la prima volta

**e) Assunzioni** – soglia 1000 ppm

**f) Algoritmo in linguaggio naturale** – se la media supera la soglia si
stampa l'avviso, si incrementa `allarmi` e, se `primo_allarme` è `NULL`, gli
si assegna `finestra`.

### Caso d'uso 3 – Orario del gruppo

**a) Input** – `finestra` che punta alla lettura di indice 4

**b) Output** – "08:20-08:30"

**c) Variabili di supporto** – indice `finestra - &letture[0]`

**d) Vincoli** – la differenza tra puntatori dà un numero di elementi

**e) Assunzioni** – letture ogni 5 minuti dalle 8:00

**f) Algoritmo in linguaggio naturale** – minuti = 8 × 60 + indice × 5; ore e
minuti si ottengono con `/ 60` e `% 60`.
