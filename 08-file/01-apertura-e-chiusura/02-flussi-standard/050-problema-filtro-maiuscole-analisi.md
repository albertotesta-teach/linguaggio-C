# Analisi – 050-problema-filtro-maiuscole.c

## 1. Problema

I cartelli dell'open day si stampano in maiuscolo. Il filtro legge `stdin`
carattere per carattere, converte le minuscole con `toupper` e scrive su
`stdout`. Non apre file: si usa con la redirezione (`< testo.txt
> stampa.txt`). Il resoconto e l'avviso sulle lettere accentate vanno su
`stderr`, così su `stdout` esce solo il testo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| testo | flusso `stdin` | Qualunque testo, fino alla fine dell'input |

### Output

- Su `stdout` lo stesso testo con le lettere minuscole in maiuscolo.
- Su `stderr`: `[filtro] caratteri letti: N, lettere convertite: K` e, se
  ci sono, `[filtro] attenzione: B byte non ASCII (lettere accentate?) non
  convertiti`.

### Vincoli

- Si usano solo i flussi standard: `fgetc(stdin)`, `fputc(c, stdout)`,
  `fprintf(stderr, ...)`.
- `c` è `int` per distinguere `EOF`; i valori letti vanno da 0 a 255 e si
  possono passare a `islower`/`toupper`.
- I byte maggiori di 127 (le lettere accentate in UTF-8) si copiano senza
  modifiche e si contano.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `c` | `int` | Carattere letto, può valere `EOF` |
| `letti`, `convertite`, `non_ascii` | `int` | Contatori del resoconto |

### Algoritmo in linguaggio naturale

1. Leggere un carattere alla volta da `stdin` fino a `EOF`.
2. Se è minuscolo convertirlo e contarlo; se è un byte non ASCII contarlo.
3. Scriverlo su `stdout`.
4. A fine input scrivere il resoconto su `stderr`.

## 3. Casi di test

### Test 1 – Testo del cartello

- **Input:** `Open day: sabato 14 dicembre, ore 9-13`,
  `Laboratori di informatica e di robotica` (con a capo finale)
- **Valori intermedi attesi:** 38 + 39 caratteri e 2 a capo = 79; 56
  minuscole.
- **Output atteso:**
  ```
  OPEN DAY: SABATO 14 DICEMBRE, ORE 9-13
  LABORATORI DI INFORMATICA E DI ROBOTICA
  [filtro] caratteri letti: 79, lettere convertite: 56
  ```
- **Procedura:** `printf '...' | ./050-problema-filtro-maiuscole`.

### Test 2 – Redirezione del diario

- **Cosa si verifica:** su `stampa.txt` va solo il testo, il resoconto
  resta a video.
- **Input:** `diario.txt` di 3 righe (98 caratteri) creato da
  `01-aprire-e-chiudere/040`
- **Output atteso:** a video
  `[filtro] caratteri letti: 98, lettere convertite: 63`; `stampa.txt`
  contiene le tre righe in maiuscolo (`12/10 MUSEO EGIZIO DI TORINO`, ...).
- **Procedura:** `./050-problema-filtro-maiuscole < diario.txt > stampa.txt`.

### Test 3 – Lettere accentate

- **Input:** `città` e a capo
- **Valori intermedi attesi:** `à` in UTF-8 sono 2 byte; 7 caratteri
  letti, 4 convertiti.
- **Output atteso:**
  ```
  CITTà
  [filtro] caratteri letti: 7, lettere convertite: 4
  [filtro] attenzione: 2 byte non ASCII (lettere accentate?) non convertiti
  ```
