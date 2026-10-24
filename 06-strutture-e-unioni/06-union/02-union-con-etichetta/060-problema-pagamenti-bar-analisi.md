# Analisi – 060-problema-pagamenti-bar.c

## 1. Problema

Il bar della scuola accetta contanti, carta e buoni pasto; ogni metodo ha
dati diversi (somma consegnata, ultime 4 cifre della carta, codice del
buono), raccolti in una `union` dentro la struct `Pagamento`. Il programma
controlla ogni pagamento con uno `switch` sul metodo, stampa la ricevuta e
alla fine i totali per metodo con array indicizzati dall'`enum`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| pagamento | una riga | `C importo consegnato`, `K importo cifre`, `B importo codice`; `FINE` termina |

### Output

- Ricevuta: `I euro in contanti, resto R`, `I euro con carta **** NNNN`,
  `I euro con buono CODICE (non da' resto)`.
- `Pagamento rifiutato.`, `Pagamento non riconosciuto.`,
  `Dati mancanti.`
- Alla fine: per ogni metodo numero di pagamenti e totale.

### Vincoli

- Importo positivo per tutti i metodi.
- Contanti: consegnato ≥ importo. Carta: esattamente 4 cifre. Buono:
  importo al massimo 5.00 euro e codice che inizia con `BU-`.
- Si legge solo il membro della union corrispondente al metodo.
- Un pagamento per riga: il resto viene scartato. A fine input il
  programma termina come con `FINE`.

### Assunzioni

- Tutti i dati di un pagamento stanno sulla stessa riga.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Metodo` | `typedef enum { CONTANTI, CARTA, BUONO, NUM_METODI } Metodo;` | Metodo di pagamento |
| `Pagamento` | `typedef struct { Metodo metodo; double importo; union { double consegnato; char ultime_cifre[5]; char codice_buono[8]; } dati; } Pagamento;` | Un pagamento |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `totali`, `quanti` | `double[3]`, `int[3]` | Incassi per metodo |
| `esito` | `int` | 1 letto, 0 fine, −1 metodo sconosciuto, −2 dati mancanti |
| `VALORE_BUONO` | `#define` | 5.00 euro |

| Funzione | Compito |
|----------|---------|
| `leggi_pagamento(p)` | Legge metodo e dati |
| `valido(p)` | Controlli con `switch` sul metodo |
| `ricevuta(p)` | Stampa con `switch` sul metodo |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina: leggere il pagamento e scartare il resto della
   riga; segnalare metodo sconosciuto, dati mancanti o pagamento
   rifiutato; altrimenti stampare la ricevuta e aggiornare i totali del
   metodo.
2. Stampare gli incassi per metodo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Giornata al bar

- **Input:** `C 3.50 5`, `K 4.20 1234`, `B 4.80 BU-0042`, `C 3 2`,
  `K 2 12345`, `K 2 12a4`, `B 6 BU-1`, `B 3 XX-1`, `Z 3`, `C 2 abc`,
  `C 1.5 2`, `FINE`
- **Output atteso:**
  ```
    3.50 euro in contanti, resto 1.50
    4.20 euro con carta **** 1234
    4.80 euro con buono BU-0042 (non da' resto)
    Pagamento rifiutato.
    Pagamento rifiutato.
    Pagamento rifiutato.
    Pagamento rifiutato.
    Pagamento rifiutato.
    Pagamento non riconosciuto.
    Dati mancanti.
    1.50 euro in contanti, resto 0.50

  Incassi del giorno
    contanti  pagamenti  2     5.00 euro
    carta     pagamenti  1     4.20 euro
    buono     pagamenti  1     4.80 euro
  ```
