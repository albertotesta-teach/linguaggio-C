# Analisi – 060-problema-conversioni.c

## 1. Problema

La stazione meteo della scuola registra le temperature in gradi Celsius.
Per un progetto con una scuola americana e per il laboratorio di fisica
servono le stesse misure in gradi Fahrenheit e in kelvin, in una tabella
con una riga per unità di misura.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `celsius` | `double[6]` | −2.5, 1.0, 6.5, 12.0, 14.5, 9.0 °C (ore 8, 10, 12, 14, 16, 18) |

### Output

- L'intestazione con le ore.
- Tre righe: Celsius, Fahrenheit, Kelvin, con un decimale.

### Vincoli

- `converti` riceve la formula come puntatore a funzione
  `double (*)(double)` e scrive `out[i] = formula(in[i])`.
- L'array originale non cambia: `converti` lo riceve come `const double *`.
- Formule: F = C × 9 / 5 + 32; K = C + 273.15.
- La riga dei Celsius passa per la stessa `converti` con la funzione
  `identita`, che restituisce il valore invariato: tutte le righe usano lo
  stesso percorso.

### Assunzioni

- Valori stampati con un decimale (`%6.1f`).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `convertite` | `double[6]` | Risultato della conversione corrente |
| `p`, `q` | `const double *`, `double *` | In `converti`: scorrimento di ingresso e uscita |

| Funzione | Compito |
|----------|---------|
| `converti(in, out, n, formula)` | `out[i] = formula(in[i])` |
| `in_fahrenheit`, `in_kelvin`, `identita` | Formule `double (double)` |
| `stampa_riga(unita, v, n)` | Una riga della tabella |

### Algoritmo in linguaggio naturale

1. Stampare l'intestazione.
2. Per ciascuna formula (`identita`, `in_fahrenheit`, `in_kelvin`):
   convertire `celsius` in `convertite` e stampare la riga.
3. In `converti`: scorrere ingresso e uscita con due puntatori e scrivere
   in uscita il risultato della formula.

## 3. Casi di test

### Test 1 – Tabella completa

- **Input:** nessuno.
- **Valori intermedi attesi:** −2.5 × 9 / 5 + 32 = 27.5;
  14.5 + 273.15 = 287.65 (stampato 287.6).
- **Output atteso:**
  ```
  Ore          08:00   10:00   12:00   14:00   16:00   18:00
  Celsius       -2.5     1.0     6.5    12.0    14.5     9.0
  Fahrenheit    27.5    33.8    43.7    53.6    58.1    48.2
  Kelvin       270.6   274.1   279.6   285.1   287.6   282.1
  ```
- **Nota:** i valori in kelvin terminano in .65 e vengono stampati con un
  decimale: il `double` non rappresenta esattamente .65 e l'arrotondamento
  dà .6.
