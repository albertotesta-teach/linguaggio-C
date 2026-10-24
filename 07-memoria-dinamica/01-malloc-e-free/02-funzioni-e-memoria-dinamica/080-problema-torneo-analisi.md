# Analisi – 080-problema-torneo.c

## 1. Problema

Il torneo di calcetto d'istituto ha un numero di squadre che cambia ogni
anno. Il `Torneo` contiene un puntatore a un array di `Squadra` allocato da
`crea_torneo`. Le partite aggiornano punti e gol; la classifica usa un
array temporaneo di indici allocato e liberato dentro la funzione, senza
riordinare l'array delle squadre.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `n` | `int` | Numero di squadre, da 2 a 16 |
| nomi | `char[16]` | Nome di ogni squadra |
| `comando` | `char` | `P squadra gol squadra gol`, `C` classifica, `Q` fine (anche minuscoli) |

### Output

- `nome mancante o ripetuto: uso Sk` se un nome manca o è già usato.
- `P`: `A g1 - g2 B registrata`, `Squadre non valide.`,
  `Risultato non valido.`
- `C`: la classifica con giocate, gol fatti e subiti, differenza reti e
  punti.
- `Numero non valido.`, `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- `crea_torneo`: due allocazioni con liberazione della prima se la
  seconda fallisce; `distruggi_torneo` accetta `NULL`.
- Vittoria 3 punti, pareggio 1.
- Ordine: più punti, a parità differenza reti maggiore; a parità completa
  resta l'ordine di inserimento.
- La classifica ordina (selezione) un array di indici
  `malloc(n * sizeof *ordine)`, liberato prima di uscire dalla funzione.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Ogni squadra ha un nome di una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Squadra` | `typedef struct { char nome[16]; int punti; int giocate; int fatti; int subiti; } Squadra;` | Statistiche di una squadra |
| `Torneo` | `typedef struct { char nome[24]; int n_squadre; Squadra *squadre; } Torneo;` | Il torneo con l'array dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `t` | `Torneo *` | Torneo creato (`NULL` se dati non validi o memoria esaurita) |
| `a`, `b` | `int` | Indici delle squadre della partita |
| `ordine` (in `classifica`) | `int *` | Indici ordinati |

| Funzione | Compito |
|----------|---------|
| `crea_torneo`, `distruggi_torneo` | Allocazione e liberazione |
| `cerca_squadra(t, nome)` | Indice della squadra, −1 se assente |
| `registra(s, fatti, subiti)` | Aggiorna una squadra |
| `precede(a, b)` | Criterio della classifica |
| `classifica(t)` | Ordina gli indici e stampa |

### Algoritmo in linguaggio naturale

1. Leggere n e creare il torneo; leggere i nomi, sostituendo con `Sk`
   quelli mancanti o ripetuti.
2. Finché il comando non è `Q`: con `P` leggere il risultato, cercare le
   squadre e registrarlo per entrambe; con `C` stampare la classifica;
   scartare il resto della riga.
3. Distruggere il torneo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Quattro squadre

- **Input:** `4`, `Leoni`, `Tigri`, `Leoni`, `Aquile`,
  `P Leoni 2 Tigri 1`, `p S3 0 Aquile 0`, `P Tigri 3 Aquile 1`,
  `P Leoni 1 Leoni 1`, `P Orsi 1 Leoni 0`, `P Leoni x`, `C`, `X`, `Q`
- **Output atteso:**
  ```
    nome mancante o ripetuto: uso S3
    Leoni 2 - 1 Tigri registrata
    S3 0 - 0 Aquile registrata
    Tigri 3 - 1 Aquile registrata
    Squadre non valide.
    Squadre non valide.
    Risultato non valido.
    Calcetto d'istituto
       squadra       G  GF  GS  DR  punti
     1 Leoni         1   2   1  +1     3
     2 Tigri         2   4   3  +1     3
     3 S3            1   0   0  +0     1
     4 Aquile        2   1   3  -2     1
    Comando sconosciuto.
  ```
  (Leoni e Tigri hanno punti e differenza reti uguali: resta l'ordine di
  inserimento).

### Test 2 – Numero non valido

- **Input:** `1`
- **Output atteso:** `Numero non valido.`
