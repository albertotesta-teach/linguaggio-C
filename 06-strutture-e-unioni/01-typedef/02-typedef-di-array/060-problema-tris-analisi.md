# Analisi – 060-problema-tris.c

## 1. Problema

Due studenti giocano a tris sulla griglia 3 × 3. A turno scrivono riga e colonna; una mossa fuori griglia o su una casella occupata va ripetuta. La partita termina con un tris o con la griglia piena.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Griglia` | `typedef char Griglia[3][3];` | le nove caselle del tris |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `g` | `Griglia` | 3 × 3 | ' ' libera, 'X' o 'O' |
| `giocatore` | `char` | — | Simbolo di turno |
| `riga`, `colonna` | `int` | — | Mossa letta, da 1 a 3 |
| `finita` | `int` | — | Fine della partita |

| Funzione | Compito |
|----------|---------|
| `stampa(g)` | Disegna la griglia |
| `ha_vinto(g, simbolo)` | 1 se il simbolo occupa una riga, una colonna o una diagonale |
| `piena(g)` | 1 se non ci sono caselle libere |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Mossa valida

**a) Input** – `2 2`

**b) Output** – griglia con X al centro, turno a O

**c) Variabili di supporto** – `g`

**d) Vincoli** – casella libera e dentro la griglia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scrivere il simbolo nella casella e cambiare giocatore.

### Caso d'uso 2 – Mossa da ripetere

**a) Input** – `2 2` su casella occupata; `4 1`

**b) Output** – "Casella occupata, ripetere."; "Fuori dalla griglia, ripetere."

**c) Variabili di supporto** – —

**d) Vincoli** – il turno non passa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare limiti e casella prima di scrivere.

### Caso d'uso 3 – Vittoria

**a) Input** – X in 1 3, 2 2, 3 1

**b) Output** – "Tris! Vince il giocatore X."

**c) Variabili di supporto** – `finita`

**d) Vincoli** – il controllo si fa dopo ogni mossa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ha_vinto controlla tre righe, tre colonne e due diagonali; se nessuno vince e la griglia è piena è pareggio.
