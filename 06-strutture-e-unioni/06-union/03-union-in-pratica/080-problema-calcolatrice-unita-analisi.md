# Analisi – 080-problema-calcolatrice-unita.c

## 1. Problema

Nel laboratorio di scienze si convertono lunghezze, masse e temperature.
L'unità è una union etichettata dalla dimensione: ogni dimensione ha il
suo `enum` di unità. Una tabella associa sigla, unità e fattore verso
l'unità base; le temperature passano per i gradi Celsius.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| richiesta | una riga | `valore sigla in sigla`; `FINE` termina |

Sigle: `mm`, `cm`, `m`, `km`, `in`, `mi`; `g`, `kg`, `lb`; `C`, `F`, `K`.

### Output

- `V da = R a` (risultato con al massimo 6 cifre significative).
- `Non si converte una X in una Y.`, `Unita' sconosciuta: s`,
  `Richiesta non valida.`

### Vincoli

- Lunghezze e masse: valore × fattore(da) / fattore(a), con unità base
  metro e chilogrammo.
- Temperature: da → Celsius → a; F = C × 9 / 5 + 32, K = C + 273.15.
- Si convertono solo unità della stessa dimensione.
- Una conversione per riga; una riga non valida non interrompe il
  programma. A fine input termina come con `FINE`.

### Assunzioni

- Le sigle sono sensibili alle maiuscole (`C` grado Celsius, `cm`
  centimetro).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Dimensione` | `typedef enum { LUNGHEZZA, MASSA, TEMPERATURA } Dimensione;` | Etichetta |
| `UnitaLunghezza`, `UnitaMassa`, `UnitaTemperatura` | enum | Unità di ogni dimensione |
| `Unita` | struct con `dimensione` e union anonima delle tre unità | Unità etichettata |
| `Voce` | `typedef struct { const char *sigla; Unita unita; double fattore; } Voce;` | Riga della tabella |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `tabella` | `Voce[12]` | Sigle riconosciute |
| `i`, `j` | `int` | Posizioni delle due sigle (−1 = sconosciuta) |
| `valore`, `risultato` | `double` | Conversione |

| Funzione | Compito |
|----------|---------|
| `cerca(tabella, sigla)` | Posizione della sigla |
| `in_celsius(v, u)`, `da_celsius(v, u)` | Conversioni di temperatura |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina: leggere la prima parola (con `FINE` o a fine
   input terminare); convertirla in numero e leggere `sigla in sigla`;
   cercare le sigle; controllare la dimensione; calcolare con uno
   `switch` sulla dimensione; stampare; scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Conversioni

- **Input:** `2.5 km in m`, `12 in in cm`, `1 mi in km`, `5 lb in kg`,
  `100 C in F`, `0 K in C`, `98.6 F in K`, `3 kg in m`, `5 ft in m`,
  `abc kg in g`, `3 kg a g`, `1500 g in kg`, `FINE`
- **Output atteso:**
  ```
    2.5 km = 2500 m
    12 in = 30.48 cm
    1 mi = 1.60934 km
    5 lb = 2.26796 kg
    100 C = 212 F
    0 K = -273.15 C
    98.6 F = 310.15 K
    Non si converte una massa in una lunghezza.
    Unita' sconosciuta: ft
    Richiesta non valida.
    Richiesta non valida.
    1500 g = 1.5 kg
  ```
