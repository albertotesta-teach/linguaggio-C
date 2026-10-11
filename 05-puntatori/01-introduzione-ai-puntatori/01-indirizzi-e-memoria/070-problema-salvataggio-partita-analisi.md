# Analisi – 070-problema-salvataggio-partita.c

## 1. Problema

Un gioco a livelli salva la partita copiando byte per byte le variabili
dello stato: vite, punteggio, livello, tempo di gioco, personaggio e la
mappa dei livelli completati. Bisogna sapere quanto è grande un
salvataggio e quanti slot entrano in 1024 byte, confrontando la mappa dei
livelli memorizzata come array di `int` o di `char`.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `vite` | `int` | — | Vite rimaste |
| `punteggio` | `long` | — | Punteggio (può superare i limiti di `short`) |
| `livello` | `short` | — | Livello corrente |
| `tempo_gioco` | `double` | — | Secondi giocati |
| `personaggio` | `char` | — | Iniziale del personaggio |
| `completati_int` | `int[]` | 40 | Livelli completati, 4 byte ciascuno |
| `completati_char` | `char[]` | 40 | Livelli completati, 1 byte ciascuno |
| `base`, `con_int`, `con_char` | `size_t` | — | Dimensioni del salvataggio |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabella dello stato

**a) Input** – variabili dello stato

**b) Output** – tipo, indirizzo e byte di ogni variabile

**c) Variabili di supporto** – nessuna

**d) Vincoli** – indirizzi stampati con `%p` e `(void *)`

**e) Assunzioni** – gli indirizzi cambiano a ogni esecuzione

**f) Algoritmo in linguaggio naturale** – stampare `&variabile` e `sizeof(variabile)`.

### Caso d'uso 2 – Dimensione del salvataggio e slot

**a) Input** – dimensioni delle variabili

**b) Output** – 183 byte → 5 slot; 63 byte → 16 slot; 120 byte risparmiati

**c) Variabili di supporto** – `base`, `con_int`, `con_char`

**d) Vincoli** – gli slot sono un numero intero (divisione intera)

**e) Assunzioni** – il salvataggio contiene solo i byte delle variabili

**f) Algoritmo in linguaggio naturale**
1. `base` = somma delle variabili semplici.
2. Aggiungere la mappa come `int` o come `char`.
3. Slot = 1024 / dimensione; risparmio = differenza delle due dimensioni.
