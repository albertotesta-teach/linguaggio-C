# Analisi – 040-problema-classifica-in-ordine.c

## 1. Problema

Al traguardo della corsa campestre i giudici comunicano i tempi, non
sempre nell'ordine di arrivo. La classifica è un vettore dinamico di
`Arrivo` tenuto sempre ordinato per tempo: ogni nuovo tempo si inserisce
nella sua posizione e un atleta squalificato si rimuove. La classifica è
pronta in ogni momento, con il distacco dal primo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `A nome mm:ss` arrivo, `S nome` squalifica, `C` classifica, `Q` fine (anche minuscoli) |

### Output

- `nome in posizione P`, `nome ha gia' un tempo.`, `Dati non validi.`
- `squalifica di nome: chi seguiva sale di una posizione`,
  `Atleta non in classifica.`
- `C`: posizione, nome, tempo `mm:ss` e distacco `+N s` dal primo.
- `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- Vettore `{Arrivo *dati; int n; int capacita;}` con capacità iniziale 4 e
  raddoppio; il `main` usa solo le funzioni del vettore.
- `inserisci` sposta avanti gli elementi da `posizione` in poi
  (dall'ultimo); `rimuovi` sposta indietro i successivi.
- Posizione del nuovo tempo: prima del primo tempo strettamente maggiore,
  quindi a parità viene dopo chi è già in classifica.
- Secondi da 0 a 59, minuti non negativi.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Il nome è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Arrivo` | `typedef struct { char nome[20]; int secondi; } Arrivo;` | Un atleta con il tempo |
| `Classifica` | `typedef struct { Arrivo *dati; int n; int capacita; } Classifica;` | Vettore ordinato |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `classifica` | `Classifica *` | Il vettore |
| `a`, `primo` | `Arrivo` | Elemento da inserire o stampare, vincitore |
| `posizione` | `int` | Posizione di inserimento o di rimozione |

| Funzione | Compito |
|----------|---------|
| `crea_classifica`, `distruggi_classifica` | Allocazione e liberazione |
| `inserisci(c, posizione, a)` | Inserimento con spostamento |
| `rimuovi(c, posizione)` | Rimozione con spostamento |
| `lunghezza`, `elemento` | Accesso |
| `posizione_per_tempo(c, secondi)` | Dove inserire il nuovo tempo |
| `cerca(c, nome)` | Posizione dell'atleta, −1 se assente |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; con `A`
   controllare e inserire nella posizione giusta; con `S` cercare e
   rimuovere; con `C` stampare; scartare il resto della riga.
2. Distruggere la classifica.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Arrivi e squalifica

- **Input:** `A Rossi 12:30`, `a Bianchi 11:58`, `A Verdi 12:30`,
  `A Neri 13:05`, `A Rossi 11:00`, `A Gialli 12:70`, `C extra`,
  `S Bianchi`, `s Mori`, `C`, `X`, `Q`
- **Output atteso:**
  ```
    Rossi in posizione 1
    Bianchi in posizione 1
    Verdi in posizione 3
    Neri in posizione 4
    Rossi ha gia' un tempo.
    Dati non validi.
     1. Bianchi    11:58  +0 s
     2. Rossi      12:30  +32 s
     3. Verdi      12:30  +32 s
     4. Neri       13:05  +67 s
    squalifica di Bianchi: chi seguiva sale di una posizione
    Atleta non in classifica.
     1. Rossi      12:30  +0 s
     2. Verdi      12:30  +0 s
     3. Neri       13:05  +35 s
    Comando sconosciuto.
  ```
  (Verdi, con lo stesso tempo di Rossi, si inserisce dopo di lui).
