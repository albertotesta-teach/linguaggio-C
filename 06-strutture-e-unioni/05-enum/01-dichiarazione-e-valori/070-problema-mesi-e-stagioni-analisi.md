# Analisi – 070-problema-mesi-e-stagioni.c

## 1. Problema

Per il calendario delle attività all'aperto il programma legge mese e
anno e stampa il nome del mese, i giorni (con febbraio bisestile) e la
stagione meteorologica. L'enum `Mese` parte da `GENNAIO = 1` come il
numero scritto dall'utente; il numero si controlla prima di assegnarlo a
una variabile `Mese`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `numero` | `int` | Mese da 1 a 12; 0 termina |
| `anno` | `int` | Anno (serve per febbraio) |

### Output

- `nome anno: N giorni, stagione` per ogni coppia valida.
- `X non e' un mese.` oppure `Dati non validi.`

### Vincoli

- `GENNAIO = 1`: le costanti successive valgono 2, 3, ...; l'indice nei
  nomi è `mese - GENNAIO`.
- Bisestile: divisibile per 4 ma non per 100, oppure divisibile per 400.
- 30 giorni ad aprile, giugno, settembre, novembre; 31 negli altri mesi.
- Stagioni meteorologiche: inverno dicembre-febbraio, primavera
  marzo-maggio, estate giugno-agosto, autunno settembre-novembre; i
  confronti `mese <= MAGGIO` sfruttano l'ordine delle costanti.
- Un dato non numerico viene scartato con il resto della riga; a fine
  input il programma termina come con 0.

### Assunzioni

- Calendario gregoriano.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Mese` | `typedef enum { GENNAIO = 1, FEBBRAIO, ..., DICEMBRE } Mese;` | Mese dell'anno |
| `Stagione` | `typedef enum { INVERNO, PRIMAVERA, ESTATE, AUTUNNO, NUM_STAGIONI } Stagione;` | Stagione meteorologica |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi_mesi`, `nomi_stagioni` | `const char *[]` | Nomi |
| `numero` | `int` | Valore letto, controllato prima di diventare `Mese` |
| `mese`, `stagione` | `Mese`, `Stagione` | Valori calcolati |
| `giorni` | `int` | Giorni del mese |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché il mese non è 0:
   1. leggere il mese (fine input → 0; testo → non valido);
   2. se diverso da 0 leggere l'anno (testo → non valido);
   3. se il numero non è tra 1 e 12 segnalarlo;
   4. altrimenti calcolare giorni e stagione e stamparli.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Mesi e anni

- **Cosa si verifica:** le regole dei bisestili, i mesi da 30 giorni, le
  quattro stagioni, gli errori.
- **Input:** `2 2024`, `2 2025`, `2 1900`, `2 2000`, `4 2026`, `12 2026`,
  `6 2026`, `10 2026`, `13 2026`, `abc`, `3 x`, `0`
- **Output atteso:**
  ```
    febbraio 2024: 29 giorni, inverno
    febbraio 2025: 28 giorni, inverno
    febbraio 1900: 28 giorni, inverno
    febbraio 2000: 29 giorni, inverno
    aprile 2026: 30 giorni, primavera
    dicembre 2026: 31 giorni, inverno
    giugno 2026: 30 giorni, estate
    ottobre 2026: 31 giorni, autunno
    13 non e' un mese.
    Dati non validi.
    Dati non validi.
  ```
