# Analisi – 040-problema-primo-divisore.c

## 1. Problema

Dato un intero n ≥ 2, trovare il suo divisore più piccolo maggiore di 1
(se coincide con n, il numero è primo) e scomporre n in fattori primi con
gli esponenti, nella forma `360 = 2^3 x 3^2 x 5`.

La ricerca del primo divisore è il caso tipico in cui si userebbe `break`:
il programma mostra come sostituirlo con un flag nella condizione.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato        |
|-----------|-------|--------------------|
| `n`       | `int` | Numero inserito    |

### Output
- Il primo divisore maggiore di 1 e la scomposizione in due fattori
  ("360 = 2 x 180"), oppure "n e' un numero primo.";
- la scomposizione in fattori primi con gli esponenti
  ("Scomposizione: 360 = 2^3 x 3^2 x 5").

### Vincoli
- `n >= 2`: la richiesta si ripete finché non è rispettato
- La ricerca del divisore si ferma tramite la condizione
  `d * d <= n && !trovato`, senza `break`
- Nella scomposizione l'esponente si stampa solo se è maggiore di 1, e
  " x " solo tra due fattori

### Assunzioni
- L'utente inserisce un numero intero

### Variabili di supporto

| Variabile                | Tipo        | Significato                                         |
|--------------------------|-------------|-----------------------------------------------------|
| `d`                      | `int`       | Possibile divisore                                  |
| `trovato`                | `int` (0/1) | Flag che ferma la ricerca                           |
| `divisore`               | `int`       | Primo divisore; vale n se non se ne trovano altri   |
| `resto_da_scomporre`     | `int`       | Parte di n non ancora scomposta                     |
| `fattore`                | `int`       | Fattore in prova                                    |
| `esponente`              | `int`       | Quante volte il fattore divide il numero            |
| `primo_fattore_stampato` | `int` (0/1) | Serve a stampare " x " solo tra due fattori         |

### Algoritmo in linguaggio naturale
1. Leggere n ripetendo finché è minore di 2.
2. Porre `trovato = 0`, `divisore = n`, `d = 2`.
3. Finché `d * d <= n` e non trovato: se n è divisibile per d, porre
   `trovato = 1` e `divisore = d`; altrimenti incrementare d.
4. Stampare il divisore; se è n il numero è primo, altrimenti stampare
   `n = divisore x (n / divisore)`.
5. Porre `resto_da_scomporre = n`, `fattore = 2`.
6. Finché `resto_da_scomporre > 1`:
   a. dividere per `fattore` finché è divisibile, contando l'esponente;
   b. se l'esponente è positivo stampare il fattore (preceduto da " x " se
      non è il primo) e, se maggiore di 1, l'esponente;
   c. passare al fattore successivo.

### Osservazione

Nella scomposizione i fattori trovati sono sempre primi senza bisogno di
verificarlo: quando si prova un fattore, tutti i fattori minori sono già
stati eliminati dal numero.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Numero composto con fattori ripetuti
- **Cosa si verifica:** la stampa degli esponenti maggiori di 1
- **Input:** 360
- **Output atteso:** "Primo divisore maggiore di 1: 2", "360 = 2 x 180",
  "Scomposizione: 360 = 2^3 x 3^2 x 5"

### Test 2 – Numero primo
- **Cosa si verifica:** `trovato` resta 0 e la ricerca si ferma a d = 10,
  perché 10 × 10 > 97
- **Input:** 97
- **Output atteso:** "97 e' un numero primo." e "Scomposizione: 97 = 97"

### Test 3 – Prodotto di primi distinti
- **Cosa si verifica:** i fattori che non dividono il numero (esponente 0)
  non vengono stampati
- **Input:** 1001
- **Output atteso:** "Scomposizione: 1001 = 7 x 11 x 13"

### Test 4 – Valore minore di 2
- **Input:** 1
- **Output atteso:** la richiesta viene ripetuta
