# Analisi – 060-problema-correzione-errori.c

## 1. Problema

Il programma di una palestra calcola il prezzo dell'abbonamento in base
agli anni di iscrizione del socio: sconto del 10% da 2 anni, del 20% da 5
anni, ulteriori 15 euro di promozione da 10 anni; chi non è ancora socio
paga il prezzo pieno. La versione dello studente conteneva quattro errori
con i puntatori, che vanno riconosciuti e corretti.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `anni` | `int` | Anni di iscrizione, letti con `scanf` |

### Output

- `Socio da N anni: sconto S%, prezzo P euro` (con `anno` al singolare per 1).
- Da 10 anni in su: `(compresa la promozione fedelta' di 15 euro)`.

### Vincoli

- Prezzo base 400 euro; sconto 10% da 2 anni, 20% da 5 anni; promozione
  di 15 euro da 10 anni; con 0 anni nessuno sconto.
- I quattro errori corretti:
  1. a `scanf` si passa l'indirizzo `&anni`, non il valore;
  2. un puntatore va inizializzato (`percentuale = &sconto`) prima di
     scrivere con `*percentuale`;
  3. `da_applicare` resta `NULL` per chi non è socio e si dereferenzia solo
     dopo aver controllato che non sia `NULL`;
  4. non si usa l'indirizzo di una variabile dichiarata in un blocco `{ }`
     dopo la fine del blocco.
- Un input non numerico o negativo vale 0 anni.

### Assunzioni

- Gli importi sono euro interi: lo sconto si calcola con la divisione
  intera.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sconto` | `int` | Percentuale di sconto |
| `prezzo` | `int` | Prezzo finale in euro |
| `percentuale` | `int *` | Punta a `sconto` |
| `da_applicare` | `int *` | Sconto da applicare, `NULL` per chi non è socio |
| `PREZZO_BASE` | `#define` | 400 euro |

### Algoritmo in linguaggio naturale

1. Leggere gli anni; se la lettura fallisce o il valore è negativo usare 0.
2. Far puntare `percentuale` a `sconto` e scrivervi 20 (≥ 5 anni) o 10
   (≥ 2 anni).
3. Se gli anni sono > 0 far puntare `da_applicare` a `sconto`.
4. Se `da_applicare` non è `NULL` calcolare
   `prezzo = 400 − 400 × (*da_applicare) / 100`, altrimenti `prezzo = 400`.
5. Da 10 anni sottrarre 15 euro di promozione.
6. Stampare anni, sconto e prezzo, e la nota sulla promozione.

## 3. Casi di test

### Test 1 – Sconto del 10%

- **Input:** `3`
- **Output atteso:** `Socio da 3 anni: sconto 10%, prezzo 360 euro`

### Test 2 – Non ancora socio

- **Cosa si verifica:** `da_applicare` resta `NULL` e non si dereferenzia.
- **Input:** `0`
- **Output atteso:** `Socio da 0 anni: sconto 0%, prezzo 400 euro`

### Test 3 – Promozione fedeltà

- **Input:** `12`
- **Valori intermedi attesi:** 400 − 80 = 320, poi 320 − 15 = 305.
- **Output atteso:**
  ```
  Socio da 12 anni: sconto 20%, prezzo 305 euro
  (compresa la promozione fedelta' di 15 euro)
  ```

### Test 4 – Soglie esatte

- **Cosa si verifica:** i confronti con `>=`.
- **Input:** `2`, `5`, `10` (tre esecuzioni)
- **Output atteso:** sconto 10% (360 euro), sconto 20% (320 euro), sconto
  20% e promozione (305 euro).

### Test 5 – Un anno e input non valido

- **Input:** `1`; in una seconda esecuzione `abc`
- **Output atteso:** `Socio da 1 anno: sconto 0%, prezzo 400 euro`;
  `Socio da 0 anni: sconto 0%, prezzo 400 euro`
