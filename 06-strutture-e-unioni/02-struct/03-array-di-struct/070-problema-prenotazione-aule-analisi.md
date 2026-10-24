# Analisi – 070-problema-prenotazione-aule.c

## 1. Problema

Tre aule informatiche si prenotano ora per ora, per sei ore. Il programma
accetta una prenotazione se l'aula è libera in quell'ora e ha abbastanza
postazioni, elenca le aule libere in un'ora e stampa la tabella della
giornata. Le aule sono un array di struct `Aula`; ogni struct contiene a
sua volta un array con la classe che ha prenotato ogni ora.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `P aula ora classe studenti`, `L ora`, `T` tabella, `Q` fine (anche minuscoli) |
| `a`, `ora` | `int` | Aula da 1 a 3, ora da 1 a 6 |
| `classe` | `char[4]` | Classe che prenota (es. `2B`) |
| `studenti` | `int` | Numero di studenti, positivo |
| `aule` | `Aula[3]` | Situazione iniziale (nel sorgente): Lab Alfa 28 postazioni (3A alla 1a, 4B alla 4a), Lab Beta 24 (5C alla 2a e 3a), Lab Gamma 16 (libero) |

### Output

- `Prenotato: <aula>, Na ora, <classe>.`, oppure
  `<aula> alla Na ora e' gia' della <classe>.`,
  `<aula> ha solo N postazioni.`, `Dati non validi.`
- Per `L`: le aule libere con le postazioni e
  `Aule libere alla Na ora: N`, oppure `Ora non valida.`
- Per `T`: la tabella aule × ore, con `--` per le ore libere.
- `Comando sconosciuto.`

### Vincoli

- Un'ora è libera se la stringa `prenotata[ora - 1]` è vuota.
- Il controllo dell'aula occupata precede quello delle postazioni.
- Aula e ora sono numerate da 1 per l'utente, da 0 negli array.
- Dati non validi non interrompono il programma; un comando per riga (il
  resto viene scartato). A fine input il programma termina come con `Q`.

### Assunzioni

- La classe è una sigla di al massimo 3 caratteri.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Aula` | `typedef struct { char nome[12]; int postazioni; char prenotata[6][4]; } Aula;` | Un'aula con le prenotazioni della giornata |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `aule` | `Aula[3]` | Array di struct |
| `libere` | `int` | Aule libere in un'ora |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) e convertirlo in maiuscolo;
   2. `P`: leggere i quattro dati; se non validi segnalarlo; se l'aula è
      occupata o troppo piccola segnalarlo; altrimenti copiare la classe
      nella casella dell'ora;
   3. `L`: leggere l'ora; se valida stampare e contare le aule con la
      casella vuota;
   4. `T`: stampare la tabella;
   5. altro diverso da `Q`: comando sconosciuto;
   6. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Giornata di prenotazioni

- **Cosa si verifica:** aula occupata, postazioni insufficienti,
  prenotazioni riuscite, dati e ore non validi, tabella aggiornata.
- **Input:** `T`, `P 1 1 2B 20`, `P 3 2 1A 22`, `P 3 2 1A 16`,
  `P 2 2 4A 20`, `p 1 2 4A 26`, `P 4 1 1A 10`, `P 1 7 1A 10`, `P 1 x`,
  `L 2`, `l 9`, `L abc`, `T`, `Q`
- **Output atteso:**
  ```
    Aula        1a  2a  3a  4a  5a  6a
    Lab Alfa    3A   --   --   4B   --   -- 
    Lab Beta    --   5C   5C   --   --   -- 
    Lab Gamma   --   --   --   --   --   -- 
    Lab Alfa alla 1a ora e' gia' della 3A.
    Lab Gamma ha solo 16 postazioni.
    Prenotato: Lab Gamma, 2a ora, 1A.
    Lab Beta alla 2a ora e' gia' della 5C.
    Prenotato: Lab Alfa, 2a ora, 4A.
    Dati non validi.
    Dati non validi.
    Dati non validi.
    Aule libere alla 2a ora: 0
    Ora non valida.
    Ora non valida.
    Aula        1a  2a  3a  4a  5a  6a
    Lab Alfa    3A   4A   --   4B   --   -- 
    Lab Beta    --   5C   5C   --   --   -- 
    Lab Gamma   --   1A   --   --   --   -- 
  ```

### Test 2 – Aule libere

- **Input:** `L 5`, `Q`
- **Output atteso:**
  ```
    Lab Alfa (28 postazioni)
    Lab Beta (24 postazioni)
    Lab Gamma (16 postazioni)
    Aule libere alla 5a ora: 3
  ```
