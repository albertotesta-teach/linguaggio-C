# Analisi – 040-problema-menu-del-giorno.c

## 1. Problema

Il menu settimanale della mensa ha primo, secondo e contorno per ogni giorno da lunedì a venerdì, con nomi di lunghezza molto diversa. Lo studente sceglie il giorno e il programma stampa il menu; alla fine indica il nome di piatto più lungo, per il tabellone.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `giorni`, `primi`, `secondi`, `contorni` | `const char *[]` | 5 | Testi costanti di lunghezza variabile |
| `g` | `int` | — | Giorno scelto (1-5, 0 fine) |
| `piu_lungo` | `const char *` | — | Puntatore al nome più lungo |

| Funzione | Compito |
|----------|---------|
| `stampa_menu(g, giorni, primi, secondi, contorni)` | Stampa il menu del giorno di indice `g` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Menu del giorno

**a) Input** – `3`

**b) Output** – Mercoledì: Minestrone di verdure, Merluzzo al forno, Patate al forno

**c) Variabili di supporto** – `g - 1`

**d) Vincoli** – l'indice dei quattro array è lo stesso

**e) Assunzioni** – giorni numerati da 1

**f) Algoritmo in linguaggio naturale** – chiamare `stampa_menu` con `g - 1`; la funzione stampa `primi[g]`, `secondi[g]`, `contorni[g]`.

### Caso d'uso 2 – Giorno non valido

**a) Input** – `7`

**b) Output** – "Giorno non valido."

**c) Variabili di supporto** – nessuna

**d) Vincoli** – indice sempre tra 0 e 4

**e) Assunzioni** – un input non numerico termina

**f) Algoritmo in linguaggio naturale** – controllare l'intervallo prima di usare l'indice.

### Caso d'uso 3 – Nome più lungo

**a) Input** – tutti i piatti

**b) Output** – "Pasta al pomodoro e basilico" (28 caratteri)

**c) Variabili di supporto** – `piu_lungo`

**d) Vincoli** – si conserva il puntatore, non una copia del testo

**e) Assunzioni** – a parità vale il primo trovato

**f) Algoritmo in linguaggio naturale** – confrontare `strlen` di ogni piatto con quello di `piu_lungo` e spostare il puntatore.
