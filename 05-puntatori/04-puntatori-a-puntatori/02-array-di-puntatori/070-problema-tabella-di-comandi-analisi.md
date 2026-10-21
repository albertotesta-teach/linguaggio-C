# Analisi – 070-problema-tabella-di-comandi.c

## 1. Problema

Un piccolo robot si muove su una griglia ricevendo sequenze di lettere: A
avanti, I indietro, D gira a destra, S gira a sinistra. Le lettere
sconosciute vengono ignorate. Dopo ogni sequenza il programma mostra
posizione e direzione. Una riga vuota termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `sequenza` | `char[80]` | Sequenza di comandi letta con `fgets`; riga vuota per finire |

### Output

- La posizione iniziale (0, 0) verso nord.
- `'c' ignorato` per ogni carattere sconosciuto.
- Dopo ogni sequenza: `Robot in (x, y) verso <direzione>`.

### Vincoli

- `comandi` è un array di puntatori a funzione con lo stesso prototipo
  `void (int *, int *, int *)`; la posizione della lettera in `"AIDS"`
  (trovata con `strchr`, `trovata − lettere`) è l'indice della funzione da
  chiamare.
- Un puntatore a funzione si chiama solo con un indice valido: se la
  lettera non c'è, `strchr` restituisce `NULL` e il carattere si ignora.
- Le rotazioni non usano `x` e `y` ma devono riceverli per avere lo stesso
  prototipo (`(void) x;` evita l'avviso del compilatore).
- Direzioni in senso orario: 0 nord, 1 est, 2 sud, 3 ovest; destra = +1,
  sinistra = +3 (mod 4).
- Avanti verso nord aumenta `y`, verso est aumenta `x`.
- Una riga più lunga del buffer viene troncata e il resto si scarta; la fine
  dell'input termina il programma.

### Assunzioni

- Griglia senza limiti; i comandi sono lettere maiuscole (le minuscole e
  gli spazi vengono ignorati).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `comandi` | `void (*[4])(int *, int *, int *)` | Tabella di puntatori a funzione |
| `lettere` | `const char[]` | `"AIDS"`: la posizione della lettera è l'indice del comando |
| `direzioni` | `const char *[4]` | Nomi delle direzioni |
| `x`, `y`, `dir` | `int` | Posizione e direzione |
| `c`, `trovata` | `const char *` | Carattere esaminato, lettera trovata con `strchr` |
| `a_capo`, `resto`, `continua` | `char *`, `int`, `int` | Lettura della riga |

| Funzione | Compito |
|----------|---------|
| `avanti`, `indietro`, `destra`, `sinistra` | Aggiornano posizione o direzione, stesso prototipo |

### Algoritmo in linguaggio naturale

1. Stampare la posizione iniziale.
2. Finché `continua`: leggere una sequenza (a fine input terminare);
   togliere il `'\n'` o scartare il resto; una riga vuota termina.
3. Per ogni carattere: cercarlo in `"AIDS"`; se non c'è segnalarlo,
   altrimenti chiamare `comandi[indice](&x, &y, &dir)`.
4. Stampare posizione e direzione.

## 3. Casi di test

Nell'output le sequenze inserite non compaiono (input da pipe).

### Test 1 – Sequenze successive

- **Input:** `AADA`, `SS`, `X`, `II`, riga vuota
- **Valori intermedi attesi:** `AADA`: (0,1), (0,2), gira a est, (1,2);
  `SS`: da est a nord a ovest; `II` verso ovest aumenta `x` di 2.
- **Output atteso:**
  ```
  Robot in (0, 0) verso nord
    Robot in (1, 2) verso est
    Robot in (1, 2) verso ovest
    'X' ignorato
    Robot in (1, 2) verso ovest
    Robot in (3, 2) verso ovest
  ```
