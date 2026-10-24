# Analisi – 060-problema-misure-ridotte.c

## 1. Problema

Il pluviometro della stazione meteo registra i millimetri di pioggia di
ogni giorno; i valori negativi o sopra 300 mm sono errori. Il programma
toglie le letture errate con un filtro sul posto (due indici, nessun
secondo array), conserva il numero del giorno originale in un array
parallelo e riduce i due blocchi con `realloc`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `n` | `int` | Giorni, da 1 a 366 |
| `pioggia[i]` | `double` | Millimetri di ogni giorno |

### Output

- `giorno G: V scartato` per ogni lettura errata.
- `Letture: L, valide: V`.
- Se ci sono letture valide: `Blocchi ridotti da n a V elementi`, totale
  e media, giorno più piovoso con il numero originale.
- `Numero non valido.`, `Memoria insufficiente.`

### Vincoli

- Filtro sul posto: `i` legge, `j` scrive (j ≤ i), così i valori validi si
  compattano all'inizio dello stesso blocco.
- `realloc` dei due blocchi a `j` elementi, ognuno in un puntatore
  temporaneo; se la riduzione fallisce il blocco vecchio resta valido.
  Con `j == 0` non si chiama `realloc` (mai `realloc(p, 0)`).
- Valida: da 0 a 300 mm compresi.
- Si leggono al massimo n valori; se l'input finisce prima si usano
  quelli letti.
- I due blocchi si liberano alla fine.

### Assunzioni

- A parità vale il primo giorno più piovoso.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `pioggia`, `tmp` | `double *` | Letture e risultato di `realloc` |
| `giorno`, `tmp_giorno` | `int *` | Numero originale del giorno |
| `letti`, `j` | `int` | Letture lette e valide |
| `piovoso`, `totale` | `int`, `double` | Statistiche |

### Algoritmo in linguaggio naturale

1. Leggere n e allocare i due blocchi; leggere le letture.
2. Scorrere le letture: se valida copiarla in posizione `j` con il numero
   del giorno, altrimenti segnalarla.
3. Se ci sono valide: ridurre i blocchi, calcolare totale, media e giorno
   più piovoso.
4. Liberare i blocchi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Una settimana

- **Input:** `7`, `12.5 0 -3 45.2 310 8 0.4`
- **Output atteso:**
  ```
    giorno 3: -3.0 scartato
    giorno 5: 310.0 scartato
  Letture: 7, valide: 5
  Blocchi ridotti da 7 a 5 elementi
  Totale 66.1 mm, media 13.2 mm al giorno
  Giorno piu' piovoso: 4 con 45.2 mm
  ```
  (il giorno più piovoso conserva il numero originale 4).

### Test 2 – Nessuna lettura valida

- **Input:** `2`, `-1 400`
- **Output atteso:** due righe `scartato` e `Letture: 2, valide: 0`.

### Test 3 – Input incompleto

- **Input:** `5`, `3 4`, fine input
- **Output atteso:** `Letture: 2, valide: 2`,
  `Blocchi ridotti da 5 a 2 elementi`, totale 7.0, giorno più piovoso 2.
