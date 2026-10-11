# Analisi – 060-problema-conversioni.c

## 1. Problema

La stazione meteo della scuola registra le temperature in gradi Celsius.
Per un progetto con una scuola americana e per il laboratorio di fisica
servono le stesse misure in gradi Fahrenheit e in kelvin, in una tabella
con una riga per unità di misura.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `celsius` | `double[]` | 6 | Misure originali |
| `convertite` | `double[]` | 6 | Risultato della conversione corrente |

| Funzione | Compito |
|----------|---------|
| `converti(in, out, n, formula)` | `out[i] = formula(in[i])` |
| `in_fahrenheit`, `in_kelvin`, `identita` | Formule `double (double)` |
| `stampa_riga(unita, v, n)` | Una riga della tabella |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Fahrenheit

**a) Input** – −2.5 °C

**b) Output** – 27.5 °F

**c) Variabili di supporto** – `p`, `q`

**d) Vincoli** – l'array originale non cambia (`const double *in`)

**e) Assunzioni** – F = C × 9 / 5 + 32

**f) Algoritmo in linguaggio naturale** – due puntatori avanzano insieme:
`*q = formula(*p)`.

### Caso d'uso 2 – Kelvin

**a) Input** – 14.5 °C

**b) Output** – 287.6 K

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la stessa `converti` con un'altra formula

**e) Assunzioni** – K = C + 273.15

**f) Algoritmo in linguaggio naturale** – passare `in_kelvin` al posto di
`in_fahrenheit`.

### Caso d'uso 3 – Riga dei Celsius

**a) Input** – formula `identita`

**b) Output** – i valori originali

**c) Variabili di supporto** – nessuna

**d) Vincoli** – tutte le righe passano per la stessa funzione di stampa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – una formula che restituisce il
valore ricevuto trasforma `converti` in una copia.
