# Analisi – 080-problema-media-pesata.c

## 1. Problema

Nel registro di informatica ogni voto ha un peso percentuale (verifica
100, interrogazione 50, laboratorio 25). Il programma legge coppie
"voto peso" fino a `0 0`, scarta quelle non valide e stampa la media
semplice, la media pesata e l'esito. I tipi `Voto` e `Peso` separano i due
ruoli.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `voto` | `Voto` | Voto da 1 a 10, anche con il mezzo voto |
| `peso` | `Peso` | Peso percentuale da 1 a 100 |

La coppia `0 0` (o la fine dell'input) termina l'inserimento.

### Output

- Per ogni coppia non valida: `Coppia non valida, scartata.`
- Il numero di voti inseriti, la media semplice, la media pesata (due
  decimali) e l'esito `sufficiente` / `insufficiente`.
- Senza voti: `Nessun voto inserito.`

### Vincoli

- `Voto` è `typedef double Voto;`, `Peso` è `typedef int Peso;`; in
  `scanf` il voto si legge con `%lf`, il formato del tipo originale.
- Al massimo 20 voti.
- Media pesata = somma(voto × peso) / somma(peso).
- Sufficiente da 6 in su.
- Una coppia non numerica viene scartata (resto della riga) e segnalata.

### Assunzioni

- Voto e peso si inseriscono sulla stessa riga.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Voto` | `typedef double Voto;` | Voti e medie |
| `Peso` | `typedef int Peso;` | Pesi percentuali |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `voti`, `pesi` | `Voto[20]`, `Peso[20]` | Coppie valide |
| `voto`, `peso` | `Voto`, `Peso` | Coppia letta; inizializzate a 1 per entrare nel ciclo |
| `letti` | `int` | Valore restituito da `scanf` |
| `n` | `int` | Numero di voti validi |
| `finale` | `Voto` | Media pesata |

| Funzione | Compito |
|----------|---------|
| `media_pesata(voti, pesi, n)` | Somma dei prodotti diviso somma dei pesi |
| `media_semplice(voti, n)` | Media aritmetica dei voti |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché ci sono meno di 20 voti e non è stato inserito `0 0`:
   1. leggere voto e peso (a fine input come `0 0`; testo → coppia non
      valida, riga scartata);
   2. se voto e peso sono negli intervalli, memorizzare la coppia;
   3. altrimenti, se non è `0 0`, segnalarla.
2. Senza voti stampare `Nessun voto inserito.`
3. Altrimenti calcolare e stampare le due medie e l'esito.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Voti con pesi diversi e coppie scartate

- **Cosa si verifica:** calcolo delle due medie e scarto delle coppie non
  valide.
- **Input:** `7 100`, `5.5 50`, `11 50`, `x y`, `8 25`, `9 25`, `0 0`
- **Valori intermedi attesi:** somma prodotti 700 + 275 + 200 + 225 =
  1400, somma pesi 200; media pesata 7.00; media semplice 29.5 / 4 = 7.375.
- **Output atteso:**
  ```
    Coppia non valida, scartata.
    Coppia non valida, scartata.

  Voti inseriti: 4
  Media semplice: 7.38
  Media pesata:   7.00  -> sufficiente
  ```

### Test 2 – Esito insufficiente

- **Cosa si verifica:** la media pesata può essere insufficiente anche con
  una media semplice sufficiente.
- **Input:** `4 100`, `8 25`, `8 25`, `0 0`
- **Valori intermedi attesi:** (400 + 200 + 200) / 150 = 5.33; media
  semplice 6.67.
- **Output atteso:** `Media semplice: 6.67` e
  `Media pesata:   5.33  -> insufficiente`.

### Test 3 – Nessun voto

- **Cosa si verifica:** nessuna divisione per zero.
- **Input:** `0 0`
- **Output atteso:**
  ```
  Nessun voto inserito.
  ```

### Test 4 – Fine input senza 0 0

- **Cosa si verifica:** la fine dell'input chiude l'inserimento.
- **Input:** `4 100`, poi fine input.
- **Output atteso:** `Voti inseriti: 1` e
  `Media pesata:   4.00  -> insufficiente`.
