# Analisi – 080-problema-archivio-foto.c

## 1. Problema

L'archivio fotografico del giornalino contiene foto con anno, autore e
didascalia. Ogni foto è una struct allocata e la didascalia è un secondo
blocco della lunghezza esatta. Si libera prima la didascalia e poi la
struct; per cambiare una didascalia si alloca il blocco nuovo prima di
liberare il vecchio; per eliminare una foto si spostano indietro i
puntatori.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `A anno autore didascalia`, `C numero didascalia`, `D numero`, `M` mostra, `Q` fine (anche minuscoli) |

### Output

- `foto N aggiunta (didascalia di B byte)`, `Dati non validi.`,
  `Manca la didascalia.`, `Archivio pieno.`
- `didascalia della foto N cambiata`,
  `Memoria insufficiente: didascalia invariata.`, `Foto inesistente.`
- `foto N eliminata`.
- `M`: le foto numerate oppure `archivio vuoto`.
- Alla fine: `Archivio chiuso: foto liberate N, blocchi liberati 2N`.

### Vincoli

- `crea_foto`: struct e didascalia; se la seconda allocazione fallisce si
  libera la prima (nessuna perdita).
- `distruggi_foto`: prima `free(f->didascalia)`, poi `free(f)`: dopo aver
  liberato la struct il campo non sarebbe più leggibile.
- `cambia_didascalia`: nuovo blocco, poi `free` del vecchio; se manca
  memoria la didascalia resta quella di prima.
- Anno da 1900 a 2100; la didascalia è il resto della riga senza spazi
  iniziali e finali (al massimo 79 caratteri).
- Al massimo 10 foto. Un comando per riga. A fine input il programma
  termina come con `Q`.

### Assunzioni

- L'autore è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Foto` | `typedef struct { int anno; char autore[16]; char *didascalia; } Foto;` | Una foto con la didascalia nello heap |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `archivio`, `n` | `Foto *[10]`, `int` | Foto presenti |
| `testo` | `char[80]` | Didascalia letta |

| Funzione | Compito |
|----------|---------|
| `copia_testo(testo)` | Blocco con una copia del testo |
| `crea_foto`, `distruggi_foto` | Allocazione e liberazione nell'ordine giusto |
| `cambia_didascalia(f, nuova)` | Sostituzione sicura |
| `leggi_resto(testo)` | Resto della riga senza spazi ai bordi |
| `mostra(archivio, n)` | Elenco |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; eseguire
   aggiunta, cambio, eliminazione (spostando indietro i puntatori) o
   elenco; scartare il resto della riga.
2. Distruggere le foto rimaste e stampare il riepilogo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Archivio

- **Input:** `A 2024 Rossi Festa di fine anno`,
  `a 2023 Bianchi   Gita a Torino  `, `A 1800 Verdi Vecchia`,
  `A 2025 Neri`, `M`, `C 1 Festa di fine anno 2024`, `C 5 xx`, `D 2`,
  `d 9`, `M extra`, `X`, `Q`
- **Output atteso:**
  ```
    foto 1 aggiunta (didascalia di 19 byte)
    foto 2 aggiunta (didascalia di 14 byte)
    Dati non validi.
    Manca la didascalia.
    1. [2024, Rossi] Festa di fine anno
    2. [2023, Bianchi] Gita a Torino
    didascalia della foto 1 cambiata
    Foto inesistente.
    foto 2 eliminata
    Foto inesistente.
    1. [2024, Rossi] Festa di fine anno 2024
    Comando sconosciuto.
  Archivio chiuso: foto liberate 1, blocchi liberati 2
  ```
