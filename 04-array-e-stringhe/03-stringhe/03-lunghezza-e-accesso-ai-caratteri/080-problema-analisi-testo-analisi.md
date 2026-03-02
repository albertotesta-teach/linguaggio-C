# Analisi – 080-problema-analisi-testo.c

## 1. Problema

Un editor di testo minimalista deve mostrare le statistiche di un testo
inserito dall'utente: numero di caratteri totali, parole, spazi e caratteri
rimanenti rispetto a un limite massimo di 280. Le parole vengono conteggiate
rilevando le transizioni da spazio a non-spazio con una variabile di stato.

---

## 2. Analisi generale e struttura dati

| Variabile               | Tipo     | Dimensione | Motivazione                                              |
|-------------------------|----------|------------|----------------------------------------------------------|
| `testo`                 | `char[]` | 283        | 280 caratteri + 1 per `'\n'` fgets + 1 per `'\0'`       |
| `num_caratteri`         | `int`    | —          | Contatore totale caratteri (spazi inclusi)               |
| `num_parole`            | `int`    | —          | Contatore parole (transizioni spazio→non-spazio)         |
| `num_spazi`             | `int`    | —          | Contatore spazi                                          |
| `precedente_era_spazio` | `int`    | —          | Variabile di stato: 1 = il carattere precedente era spazio|
| `c`                     | `char`   | —          | Carattere corrente                                       |
| `i`                     | `int`    | —          | Indice per scorrere il testo                             |
| `rimanenti`             | `int`    | —          | LIMITE_MAX - num_caratteri                               |
| `LIMITE_MAX`            | `#define`| —          | Costante: 280 caratteri massimi                          |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura del testo

**a) Input**
Testo libero con spazi, max 280 caratteri visibili.

**b) Output**
Nessun output diretto: testo memorizzato senza `'\n'`.

**c) Variabili di supporto**
- `i` (`int`): indice per rimozione `'\n'`.

**d) Vincoli**
- `fgets` con dimensione 283 per gestire il caso limite (280 char + `'\n'` + `'\0'`).
- Il `'\n'` va rimosso prima della scansione.

**e) Assunzioni**
- Il testo può contenere qualsiasi carattere ASCII stampabile.

**f) Algoritmo in linguaggio naturale**
```
1. Leggere il testo con fgets(testo, 283, stdin).
2. Rimuovere '\n' con ciclo while.
```

---

### Caso d'uso 2 – Scansione e calcolo statistiche

**a) Input**
La stringa `testo` dopo la pulizia.

**b) Output**
Nessun output diretto: aggiorna `num_caratteri`, `num_parole`, `num_spazi`.

**c) Variabili di supporto**
- `precedente_era_spazio` (`int`): variabile di stato inizializzata a 1
  (simula uno spazio virtuale prima dell'inizio del testo).
- `c` (`char`): carattere corrente.

**d) Vincoli**
- Il ciclo usa un unico `while` per tutti i contatori.
- `precedente_era_spazio` è aggiornato a ogni iterazione per riflettere
  il tipo del carattere appena elaborato.

**e) Assunzioni**
- Spazi multipli consecutivi non generano parole vuote
  (la condizione `if (precedente_era_spazio)` si attiva solo alla
  prima lettera dopo uno o più spazi).
- Il testo non inizia con spazi (assunzione semplificativa).

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare precedente_era_spazio = 1, tutti i contatori a 0, i a 0.
2. Finché testo[i] non è '\0':
   a. c = testo[i]; incrementare num_caratteri.
   b. Se c è ' ':
      - Incrementare num_spazi.
      - Impostare precedente_era_spazio a 1.
   c. Altrimenti:
      - Se precedente_era_spazio è 1: incrementare num_parole.
      - Impostare precedente_era_spazio a 0.
   d. Incrementare i.
```

---

### Caso d'uso 3 – Output statistiche e barra di utilizzo

**a) Input**
`num_caratteri`, `num_parole`, `num_spazi`, `rimanenti`, `LIMITE_MAX`.

**b) Output**
```
════════════════════════════════════════════
  STATISTICHE TESTO
════════════════════════════════════════════
  Caratteri totali  : 47 / 280
  Parole            : 9
  Spazi             : 8
  Caratteri rimasti : 233

  Utilizzo: [###.................] 16%
════════════════════════════════════════════

  Testo nel limite consentito.
```

**c) Variabili di supporto**
- `rimanenti` (`int`): `LIMITE_MAX - num_caratteri`.
- `i` (`int`): riutilizzato per il ciclo della barra di utilizzo.

**d) Vincoli**
- La barra ha sempre 20 celle; la divisione `(num_caratteri * 20) / LIMITE_MAX`
  determina quante celle sono `'#'`.
- Se `rimanenti` è negativo, si segnala il superamento del limite.

**e) Assunzioni**
- La divisione per `LIMITE_MAX` non può causare divisione per zero
  poiché `LIMITE_MAX` è una costante positiva.

**f) Algoritmo in linguaggio naturale**
```
1. Calcolare rimanenti = LIMITE_MAX - num_caratteri.
2. Stampare i contatori.
3. Stampare la barra di utilizzo con ciclo while su 20 celle.
4. Stampare la percentuale.
5. Se rimanenti < 0: segnalare eccesso.
6. Se rimanenti >= 0: confermare che il testo è nel limite.
```
