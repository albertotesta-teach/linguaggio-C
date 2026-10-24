# Analisi – 040-problema-contatore-allocazioni.c

## 1. Problema

Nel progetto di gruppo nessuno sa più quali blocchi sono stati liberati.
Invece di chiamare direttamente `malloc` e `free`, le parti del programma
usano `registra_malloc` e `registra_free`, che annotano ogni blocco in un
registro: indirizzo, byte, uso e stato. Un secondo `free` dello stesso
blocco viene segnalato e non eseguito; a fine programma il rapporto mostra
i blocchi che sarebbero andati persi, che il registro libera.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `A byte uso` alloca, `L numero` libera, `R` rapporto, `Q` fine (anche minuscoli) |
| `byte` | `long` | Da 1 a 100000 |
| `uso` | `char[24]` | Descrizione del blocco |
| `numero` | `int` | Numero del blocco (da 1) |

### Output

- `blocco N: B byte per uso`, `Allocazione non riuscita.`,
  `Richiesta non valida.`
- `blocco N liberato`, `blocco N gia' liberato: doppio free evitato`,
  `blocco N inesistente`, `Numero non valido.`
- Rapporto: blocchi allocati, blocchi ancora attivi (o `nessuno`), byte
  attivi.
- A fine programma: il rapporto, l'avviso dei blocchi persi (se ce ne
  sono) e il picco di memoria.

### Vincoli

- Al massimo 20 blocchi registrati.
- Dopo `free` l'indirizzo si azzera e lo stato diventa non attivo: così un
  secondo rilascio si riconosce.
- `byte_attivi` aumenta a ogni allocazione e cala a ogni rilascio; il
  picco è il suo massimo.
- A fine programma `libera_tutto` libera i blocchi ancora attivi.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Voce` | `typedef struct { void *indirizzo; size_t byte; char uso[24]; int attivo; } Voce;` | Un blocco registrato |
| `Registro` | `typedef struct { Voce voci[20]; int n; size_t byte_attivi; size_t picco; } Registro;` | Il registro |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `registro` | `Registro` | Stato delle allocazioni |
| `numero`, `esito` | `int` | Risultati delle funzioni |

| Funzione | Compito |
|----------|---------|
| `registra_malloc(r, byte, uso)` | Alloca e annota; numero del blocco o 0 |
| `registra_free(r, numero)` | 1 liberato, 0 già liberato, −1 inesistente |
| `rapporto(r)` | Stampa i blocchi attivi e li conta |
| `libera_tutto(r)` | Libera i blocchi rimasti |

### Algoritmo in linguaggio naturale

1. Azzerare il registro.
2. Finché il comando non è `Q`: leggere il comando in maiuscolo; allocare,
   liberare o stampare il rapporto; scartare il resto della riga.
3. Stampare il rapporto finale e l'avviso, liberare tutto, stampare il
   picco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Doppio free e blocchi dimenticati

- **Input:** `A 1000 voti`, `a 250 nomi`, `A 0 x`, `A 500000 x`, `L 1`,
  `L 1`, `L 9`, `L x`, `R`, `A 64 buffer`, `X`, `Q`
- **Valori intermedi attesi:** picco 1000 + 250 = 1250 byte; alla fine
  attivi 250 + 64 = 314.
- **Output atteso:**
  ```
    blocco 1: 1000 byte per voti
    blocco 2: 250 byte per nomi
    Richiesta non valida.
    Richiesta non valida.
    blocco 1 liberato
    blocco 1 gia' liberato: doppio free evitato
    blocco 9 inesistente
    Numero non valido.
    Blocchi allocati: 2, ancora attivi:
       2     250 byte  nomi
    Byte attivi: 250
    blocco 3: 64 byte per buffer
    Comando sconosciuto.

  Fine del programma
    Blocchi allocati: 3, ancora attivi:
       2     250 byte  nomi
       3      64 byte  buffer
    Byte attivi: 314
    Il programma avrebbe perso questi blocchi: li libera il registro.
    Picco di memoria: 1250 byte
  ```
