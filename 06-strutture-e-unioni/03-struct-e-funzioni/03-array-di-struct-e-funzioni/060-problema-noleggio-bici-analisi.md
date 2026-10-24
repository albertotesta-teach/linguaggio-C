# Analisi – 060-problema-noleggio-bici.c

## 1. Problema

Il bike sharing comunale presta bici agli studenti con la tessera. Le
funzioni di ricerca restituiscono il puntatore alla prima bici libera o
alla bici di una tessera; `noleggia` e `restituisci` lavorano su una sola
bici tramite il suo indirizzo. I primi 30 minuti sono gratuiti, poi si
pagano 0.50 euro per ogni mezz'ora iniziata.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `N tessera hh:mm` noleggio, `R tessera hh:mm` restituzione, `S` stato, `Q` fine (anche minuscoli) |
| `tessera` | `int` | Numero della tessera |
| `ore:minuti` | `int` | Orario dell'operazione |
| parco | nel sorgente | Bici B-01 ... B-04, tutte libere |

### Output

- `Bici X alla tessera T.`, `La tessera T ha gia' una bici.`,
  `Nessuna bici libera.`
- `Bici X restituita: M minuti, C euro.`, `La tessera T non ha bici.`,
  `Orario precedente all'inizio del noleggio.`
- `Dati non validi.`, `Comando sconosciuto.`
- Con `S`: per ogni bici lo stato e i minuti di uso totali.

### Vincoli

- Una tessera può avere una sola bici alla volta.
- Costo: 0 fino a 30 minuti; oltre, 0.50 × ⌈(minuti − 30) / 30⌉.
- La restituzione con un orario precedente all'inizio è rifiutata e la
  bici resta noleggiata.
- Ore 0-23, minuti 0-59.
- Un comando per riga (il resto viene scartato); i dati non validi non
  interrompono il programma. A fine input termina come con `Q`.

### Assunzioni

- Noleggio e restituzione nella stessa giornata.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Bici` | `typedef struct { char codice[6]; int noleggiata; int tessera; int inizio; int minuti_totali; } Bici;` | Una bici del parco |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `parco` | `Bici[4]` | Array di struct |
| `bici` | `Bici *` | Bici trovata |
| `uso` | `int` | Minuti del noleggio (−1 se orario errato) |
| `GRATIS` | `#define` | 30 minuti |

| Funzione | Compito |
|----------|---------|
| `prima_libera(b, n)` | Puntatore alla prima bici libera, o `NULL` |
| `bici_di(b, n, tessera)` | Puntatore alla bici della tessera, o `NULL` |
| `noleggia(b, tessera, ora)` | Assegna la bici; 1 se riuscito |
| `restituisci(b, ora)` | Libera la bici e somma l'uso; restituisce i minuti o −1 |
| `costo(minuti)` | Tariffa del noleggio |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) in maiuscolo;
   2. `N`/`R`: leggere tessera e orario e controllarli;
   3. `N`: se la tessera ha già una bici segnalarlo; altrimenti prendere
      la prima libera (se c'è) e noleggiarla;
   4. `R`: trovare la bici della tessera e restituirla, stampando minuti e
      costo, oppure segnalare l'orario errato;
   5. `S`: stampare lo stato delle bici;
   6. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Mattina di noleggi

- **Cosa si verifica:** tutte le situazioni del noleggio e della
  restituzione, il costo, i dati non validi.
- **Input:** `N 101 8:00`, `N 102 8:05`, `N 101 8:10`, `N 103 8:15`,
  `N 104 8:20`, `N 105 8:25`, `R 102 8:30`, `R 101 9:15`, `R 103 8:00`,
  `R 103 10:16`, `R 999 9:00`, `N 106 25:00`, `N abc`, `S`, `Q`
- **Valori intermedi attesi:** 75 minuti → ⌈45 / 30⌉ = 2 mezz'ore =
  1.00 euro; 121 minuti → ⌈91 / 30⌉ = 4 → 2.00 euro.
- **Output atteso:**
  ```
    Bici B-01 alla tessera 101.
    Bici B-02 alla tessera 102.
    La tessera 101 ha gia' una bici.
    Bici B-03 alla tessera 103.
    Bici B-04 alla tessera 104.
    Nessuna bici libera.
    Bici B-02 restituita: 25 minuti, 0.00 euro.
    Bici B-01 restituita: 75 minuti, 1.00 euro.
    Orario precedente all'inizio del noleggio.
    Bici B-03 restituita: 121 minuti, 2.00 euro.
    La tessera 999 non ha bici.
    Dati non validi.
    Dati non validi.
    B-01  libera     uso totale 75 min
    B-02  libera     uso totale 25 min
    B-03  libera     uso totale 121 min
    B-04  noleggiata uso totale 0 min
  ```
