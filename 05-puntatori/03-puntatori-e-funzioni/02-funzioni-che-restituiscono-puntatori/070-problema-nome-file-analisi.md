# Analisi – 070-problema-nome-file.c

## 1. Problema

I compiti consegnati sulla piattaforma della scuola hanno percorsi come
`4B/informatica/verifica-3.c`. Per l'archivio servono cartella, nome ed
estensione separati, segnalando i file senza cartella o senza estensione.
La ricerca usa una versione di `strrchr` scritta a mano.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `percorsi` | `char[5][40]` | `4B/informatica/verifica-3.c`, `4B/informatica/relazione.lab.pdf`, `5A/sistemi/v1.2/schema`, `appunti.txt`, `4B/storia/.nascosto` |

### Output

- Per ogni percorso: il percorso, la cartella (o `(nessuna)`), il nome del
  file senza estensione e l'estensione (o `(nessuna)`).

### Vincoli

- `ultimo(s, c)` restituisce un puntatore all'ultima occorrenza di `c`,
  oppure `NULL`.
- La cartella è tutto ciò che precede l'ultima `/`; il nome inizia subito
  dopo (`barra + 1`), oppure all'inizio del percorso se non c'è `/`.
- L'estensione si cerca solo nel nome (non nel percorso), dopo l'ultimo `.`:
  così il punto di una cartella come `v1.2` non viene preso.
- Un punto all'inizio del nome (file nascosto) non indica un'estensione.
- Le parti si stampano con `%.*s` senza copiarle.

### Assunzioni

- Il separatore delle cartelle è `/`; il percorso non termina con `/`.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `percorso` | `const char *` | Percorso esaminato |
| `barra` | `const char *` | Ultima `/` del percorso, `NULL` se assente |
| `nome` | `const char *` | Inizio del nome del file |
| `punto` | `const char *` | Ultimo `.` del nome, `NULL` se assente |

| Funzione | Compito |
|----------|---------|
| `ultimo(s, c)` | Puntatore all'ultima occorrenza di `c`, `NULL` se assente |

### Algoritmo in linguaggio naturale

1. Per ogni percorso:
   1. trovare l'ultima `/`; il nome inizia dopo la barra (o all'inizio);
   2. trovare l'ultimo `.` nel nome;
   3. stampare la cartella (`barra − percorso` caratteri) o `(nessuna)`;
   4. se non c'è un punto o il punto è il primo carattere del nome, stampare
      il nome intero senza estensione; altrimenti il nome fino al punto e
      l'estensione dopo il punto.

## 3. Casi di test

### Test 1 – Percorsi del sorgente

- **Cosa si verifica:** ultimo punto e ultima barra, punto in una cartella,
  file senza cartella, file nascosto.
- **Input:** nessuno.
- **Output atteso:**
  ```
  4B/informatica/verifica-3.c
    cartella:   4B/informatica
    nome:       verifica-3
    estensione: c
  4B/informatica/relazione.lab.pdf
    cartella:   4B/informatica
    nome:       relazione.lab
    estensione: pdf
  5A/sistemi/v1.2/schema
    cartella:   5A/sistemi/v1.2
    nome:       schema
    estensione: (nessuna)
  appunti.txt
    cartella:   (nessuna)
    nome:       appunti
    estensione: txt
  4B/storia/.nascosto
    cartella:   4B/storia
    nome:       .nascosto
    estensione: (nessuna)
  ```
