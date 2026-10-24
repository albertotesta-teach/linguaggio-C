# Analisi – 080-problema-archivio-dei-sensori.c

## 1. Problema

Nelle aule ci sono sensori di temperatura; ogni sensore ha un blocco con
una lettura per ogni ora del periodo di osservazione. L'array dei sensori
si alloca con `calloc` (blocchi a `NULL`, ore a 0). Quando il periodo
cambia ogni blocco si ridimensiona con `realloc`; le ore nuove valgono
`MANCANTE`. Ogni sensore tiene la sua dimensione, così un fallimento non
rende incoerenti gli altri.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `n` e aule | `int`, parole | Numero di sensori (1-8) e nome dell'aula di ognuno |
| `comando` | `char` | `P ore` periodo, `L aula ora gradi` lettura, `M` riepilogo, `Q` fine (anche minuscoli) |

### Output

- `periodo di H ore: B byte per sensore` (o un avviso per i sensori che
  restano al periodo precedente).
- `aula, ora H: G gradi`, `Periodo non ancora impostato (comando P).`,
  `Ora fuori dal periodo (1-H).`, `Aula sconosciuta.`,
  `Dati non validi.`, `Periodo non valido.`
- `M`: per ogni sensore letture valide su ore e, se ce ne sono, media,
  minimo e massimo.
- `Numero non valido.`, `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- `calloc(n, sizeof *sensori)`: `letture` a `NULL` e `ore` a 0, quindi la
  prima `realloc` equivale a `malloc`.
- `cambia_periodo`: `realloc` in un temporaneo; aggiorna `ore` solo se
  riesce; le ore aggiunte valgono `MANCANTE` (−999), quelle tolte si
  perdono.
- Periodo da 1 a 168 ore.
- Alla fine si libera il blocco di ogni sensore e poi l'array.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- −999 non è mai una temperatura reale.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Sensore` | `typedef struct { char aula[12]; int ore; double *letture; } Sensore;` | Un sensore con il suo blocco |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sensori` | `Sensore *` | Array allocato con `calloc` |
| `trovato` | `int` | Sensore dell'aula indicata |
| `MANCANTE` | `#define` | Valore delle ore senza lettura |

| Funzione | Compito |
|----------|---------|
| `cambia_periodo(s, ore)` | Ridimensiona il blocco del sensore |
| `riepilogo(s)` | Statistiche delle letture valide |

### Algoritmo in linguaggio naturale

1. Leggere n, allocare i sensori con `calloc` e leggere le aule.
2. Finché il comando non è `Q`: con `P` ridimensionare tutti i blocchi;
   con `L` registrare la lettura dopo i controlli; con `M` stampare i
   riepiloghi; scartare il resto della riga.
3. Liberare i blocchi dei sensori e l'array.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Periodo che cambia

- **Input:** `2 A12 LabFis`, `L A12 1 20`, `P 4`, `L A12 1 20.5`,
  `l A12 3 22`, `L LabFis 2 18`, `L A12 5 21`, `L B1 1 20`, `L A12 x`, `M`,
  `P 2`, `M extra`, `P 3`, `M`, `P 0`, `X`, `Q`
- **Valori intermedi attesi:** riducendo a 2 ore si perde la lettura
  dell'ora 3; riportando a 3 l'ora 3 torna `MANCANTE`.
- **Output atteso:**
  ```
    Periodo non ancora impostato (comando P).
    periodo di 4 ore: 32 byte per sensore
    A12, ora 1: 20.5 gradi
    A12, ora 3: 22.0 gradi
    LabFis, ora 2: 18.0 gradi
    Ora fuori dal periodo (1-4).
    Aula sconosciuta.
    Dati non validi.
    A12      letture 2 su 4, media 21.2, min 20.5, max 22.0
    LabFis   letture 1 su 4, media 18.0, min 18.0, max 18.0
    periodo di 2 ore: 16 byte per sensore
    A12      letture 1 su 2, media 20.5, min 20.5, max 20.5
    LabFis   letture 1 su 2, media 18.0, min 18.0, max 18.0
    periodo di 3 ore: 24 byte per sensore
    A12      letture 1 su 3, media 20.5, min 20.5, max 20.5
    LabFis   letture 1 su 3, media 18.0, min 18.0, max 18.0
    Periodo non valido.
    Comando sconosciuto.
  ```
