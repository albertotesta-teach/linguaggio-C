# Analisi – 070-problema-trasforma-testo.c

## 1. Problema

Il club di informatica vuole uno strumento per i messaggi del giornalino:
dato un testo, ne mostra la versione in maiuscolo, quella cifrata con il
cifrario di Cesare (spostamento 3) e quella con le cifre sostituite da
asterischi. Una riga vuota termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `messaggio` | `char[100]` | Testo letto con `fgets`; riga vuota per finire |

### Output

- Per ogni messaggio tre righe: `maiuscolo`, `Cesare +3`, `senza cifre`,
  ciascuna con il testo trasformato.

### Vincoli

- Le tre regole hanno lo stesso prototipo `char (char)`: `trasforma` le
  riceve come puntatore a funzione e le applica a ogni carattere con un
  solo ciclo.
- `mostra` trasforma una copia: il messaggio originale non cambia e ogni
  trasformazione parte dal testo originale.
- Cesare: le lettere si spostano di 3 posizioni; dopo la `z` si ricomincia
  dalla `a` (`% 26`); maiuscole e minuscole restano tali; gli altri
  caratteri non cambiano.
- Un messaggio più lungo del buffer viene troncato e il resto della riga si
  scarta; la fine dell'input termina come la riga vuota.

### Assunzioni

- Alfabeto inglese di 26 lettere, senza lettere accentate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `a_capo` | `char *` | Posizione del `'\n'` da togliere, `NULL` se la riga è troppo lunga |
| `c` | `int` | Carattere scartato da una riga troppo lunga |
| `continua` | `int` | Flag del ciclo |
| `copia` | `char[100]` | In `mostra`: copia su cui si applica la regola |

| Funzione | Compito |
|----------|---------|
| `trasforma(testo, regola)` | Applica `regola` a ogni carattere |
| `mostra(titolo, originale, regola)` | Copia, trasforma e stampa |
| `maiuscolo`, `cesare`, `oscura_cifre` | Regole `char (char)` |

### Algoritmo in linguaggio naturale

1. Finché `continua`: leggere un messaggio (a fine input terminare),
   togliere il `'\n'` o scartare il resto della riga; se è vuoto terminare,
   altrimenti chiamare `mostra` con le tre regole.
2. In `mostra`: copiare l'originale, chiamare `trasforma(copia, regola)`,
   stampare titolo e copia.
3. In `trasforma`: scorrere il testo con un puntatore e sostituire ogni
   carattere con `regola(*p)`.

## 3. Casi di test

Nell'output i messaggi inseriti non compaiono (input da pipe).

### Test 1 – Messaggio con lettere e cifre

- **Input:** `Ciao Zeno, chiamami al 333 1234567`
- **Output atteso:**
  ```
    maiuscolo    CIAO ZENO, CHIAMAMI AL 333 1234567
    Cesare +3    Fldr Chqr, fkldpdpl do 333 1234567
    senza cifre  Ciao Zeno, chiamami al *** *******
  ```

### Test 2 – Giro dell'alfabeto

- **Cosa si verifica:** dopo la z (e la Z) si ricomincia da capo.
- **Input:** `xyz XYZ!`
- **Output atteso:**
  ```
    maiuscolo    XYZ XYZ!
    Cesare +3    abc ABC!
    senza cifre  xyz XYZ!
  ```
