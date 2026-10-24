# Analisi – 050-problema-giorni-di-lezione.c

## 1. Problema

Il coordinatore inserisce le ore di lezione di una classe dal lunedì al
sabato. Il programma richiede i valori non validi, poi stampa il totale
(il biennio prevede 32 ore), il giorno con più ore e i giorni liberi. I
giorni sono un `enum` usato come indice dell'array delle ore.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `ore[g]` | `int` | Ore di lezione di ogni giorno, da 0 a 8 |

### Output

- `Scrivi un numero.` o `Da 0 a 8 ore.` per i valori da ripetere.
- `Totale: N ore (corretto)` oppure `(il biennio ne prevede 32)`.
- `Giorno piu' lungo: G con N ore`.
- `Giorni liberi:` con i giorni a 0 ore, oppure `nessuno`.

### Vincoli

- `typedef enum { LUNEDI, ..., SABATO, NUM_GIORNI } Giorno;` e il ciclo
  `for (g = LUNEDI; g < NUM_GIORNI; g++)`.
- Un valore non numerico viene scartato con il resto della riga e
  richiesto di nuovo; un valore fuori intervallo viene richiesto di nuovo.
- A parità vale il primo giorno con il massimo.
- A fine input i giorni mancanti valgono 0.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Giorno` | `typedef enum { LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, NUM_GIORNI } Giorno;` | Giorno della settimana |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi` | `const char *[6]` | Nomi indicizzati dal giorno |
| `ore` | `int[6]` | Ore indicizzate dal giorno (−1 = da leggere) |
| `letto` | `int` | Valore restituito da `scanf` |
| `massimo` | `Giorno` | Giorno con più ore |
| `totale`, `liberi` | `int` | Somma e giorni liberi |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Per ogni giorno: finché il valore non è valido, leggerlo (fine input →
   0; testo → messaggio; fuori intervallo → messaggio); sommarlo e
   aggiornare il massimo.
2. Stampare il totale con il controllo delle 32 ore e il giorno più lungo.
3. Stampare i giorni con 0 ore o `nessuno`.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Valori da ripetere e giorno libero

- **Input:** `6`, `6`, `abc def`, `9`, `6`, `0`, `6`, `8`
- **Output atteso:**
  ```
    Scrivi un numero.
    Da 0 a 8 ore.

  Totale: 32 ore (corretto)
  Giorno piu' lungo: sabato con 8 ore
  Giorni liberi: giovedi
  ```
  (`abc def` produce un solo messaggio: la riga è scartata per intero).

### Test 2 – Nessun giorno libero

- **Input:** `5`, `5`, `6`, `6`, `5`, `5`
- **Output atteso:** `Totale: 32 ore (corretto)`,
  `Giorno piu' lungo: mercoledi con 6 ore`, `Giorni liberi: nessuno`.

### Test 3 – Totale errato

- **Input:** `6`, `6`, `6`, `6`, `6`, `0`
- **Output atteso:** `Totale: 30 ore (il biennio ne prevede 32)`,
  `Giorno piu' lungo: lunedi con 6 ore`, `Giorni liberi: sabato`.
