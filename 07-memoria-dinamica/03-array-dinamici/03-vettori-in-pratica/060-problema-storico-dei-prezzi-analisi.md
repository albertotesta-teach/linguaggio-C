# Analisi – 060-problema-storico-dei-prezzi.c

## 1. Problema

Il comitato dei genitori registra ogni mese il prezzo del pasto in mensa.
Le rilevazioni vanno in un vettore dinamico di `Rilevazione`. Il programma
stampa la variazione percentuale mese per mese, costruisce un secondo
vettore con i mesi di aumento (lunghezza non nota in anticipo), indica
l'aumento più forte e la variazione complessiva.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| rilevazioni | testo | `mese prezzo` (prezzo positivo); `FINE` termina |

### Output

- `prezzo non valido per mese` per ogni rilevazione scartata.
- La tabella mese, prezzo e variazione percentuale dal mese precedente.
- `Mesi con aumento: A su N-1` con l'elenco e `Aumento piu' forte: mese
  (+P%)`, oppure `Nessun aumento.`
- `Complessivo primo-ultimo: p1 -> p2 euro (±P%)`.
- `Servono almeno due mesi.`, `Memoria insufficiente.`

### Vincoli

- Vettore `{Rilevazione *dati; int n; int capacita;}` con capacità
  iniziale 4 e raddoppio; il `main` usa solo le funzioni del vettore.
- Variazione = (dopo − prima) / prima × 100.
- `aumenti` crea un vettore nuovo con i soli mesi in cui il prezzo sale
  (prezzo uguale non è un aumento); in caso di errore lo distrugge e
  restituisce `NULL`.
- A parità vale il primo aumento più forte.
- Entrambi i vettori si distruggono alla fine.

### Assunzioni

- I mesi sono inseriti in ordine cronologico.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Rilevazione` | `typedef struct { char mese[8]; double prezzo; } Rilevazione;` | Prezzo di un mese |
| `Storico` | `typedef struct { Rilevazione *dati; int n; int capacita; } Storico;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `storico`, `mesi_aumento` | `Storico *` | Rilevazioni e mesi di aumento |
| `prima`, `ultima` | `Rilevazione` | Estremi del periodo |
| `massimo` | `int` | Mese con l'aumento più forte |

| Funzione | Compito |
|----------|---------|
| `crea_storico`, `distruggi_storico` | Allocazione e liberazione |
| `aggiungi`, `lunghezza`, `elemento` | Uso del vettore |
| `variazione(prima, dopo)`, `variazione_mese(s, i)` | Percentuali |
| `aumenti(s)` | Nuovo vettore con i mesi di aumento |

### Algoritmo in linguaggio naturale

1. Leggere le rilevazioni fino a `FINE`.
2. Con meno di due mesi segnalarlo; altrimenti stampare la tabella,
   costruire il vettore degli aumenti e stamparlo con l'aumento più forte,
   poi la variazione complessiva.
3. Distruggere i vettori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Un anno scolastico

- **Input:** `set 4.80`, `ott 4.80`, `nov 5.00`, `dic 4.90`, `gen 5.30`,
  `feb abc`, `mar -1`, `FINE`
- **Output atteso:**
  ```
  Mese e prezzo (FINE per terminare):
    prezzo non valido per feb
    prezzo non valido per mar

  Mese    Prezzo    Var. %
  set       4.80
  ott       4.80     +0.0%
  nov       5.00     +4.2%
  dic       4.90     -2.0%
  gen       5.30     +8.2%

  Mesi con aumento: 2 su 4
    nov
    gen
  Aumento piu' forte: gen (+8.2%)
  Complessivo set-gen: 4.80 -> 5.30 euro (+10.4%)
  ```

### Test 2 – Pochi dati e nessun aumento

- **Input:** `set 4.80`, `FINE`; poi `set 5`, `ott 4.5`, `FINE`
- **Output atteso:** `Servono almeno due mesi.`; poi `Nessun aumento.` e
  `Complessivo set-ott: 5.00 -> 4.50 euro (-10.0%)`.
