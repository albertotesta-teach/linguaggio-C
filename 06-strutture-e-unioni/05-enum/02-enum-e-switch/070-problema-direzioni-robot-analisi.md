# Analisi – 070-problema-direzioni-robot.c

## 1. Problema

Il robot del laboratorio si muove su una griglia 8 × 8 partendo da (0, 0)
verso nord. Le direzioni sono un `enum` in ordine orario, così girare è un
calcolo modulo `NUM_DIREZIONI`; uno `switch` sulla direzione dà lo
spostamento di ogni passo. Il robot si ferma al bordo della griglia.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `A n` avanza di n passi, `S` gira a sinistra, `D` gira a destra, `P` posizione, `Q` fine (anche minuscoli) |
| `passi` | `int` | Passi da fare, non negativi |

### Output

- Dopo ogni comando (tranne `Q`): `Robot in (x, y) verso direzione`.
- `Bordo raggiunto dopo N passi.` (`passo` al singolare) se il robot si
  ferma prima.
- `Numero di passi non valido.`, `Comando sconosciuto.`

### Vincoli

- `typedef enum { NORD, EST, SUD, OVEST, NUM_DIREZIONI } Direzione;`:
  destra = `(verso + 1) % 4`, sinistra = `(verso + 3) % 4`.
- Nord aumenta y, est aumenta x; coordinate da 0 a 7.
- `avanza` riceve `Robot *` e restituisce i passi effettivamente fatti.
- Un comando per riga; un dato non valido non interrompe il programma. A
  fine input termina come con `Q`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Direzione` | `typedef enum { NORD, EST, SUD, OVEST, NUM_DIREZIONI } Direzione;` | Verso del robot |
| `Robot` | `typedef struct { int x; int y; Direzione verso; } Robot;` | Posizione e verso |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `robot` | `Robot` | Stato del robot, inizialmente (0, 0) nord |
| `passi`, `fatti` | `int` | Passi richiesti e fatti |

| Funzione | Compito |
|----------|---------|
| `avanza(r, passi)` | Sposta il robot fino ai passi richiesti o al bordo |
| `gira(r, lato)` | Cambia il verso |
| `nome(d)` | Nome della direzione |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `A`: leggere i passi e avanzare, segnalando il bordo;
   3. `S`/`D`: girare;
   4. se non è `Q`, stampare la posizione;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Percorso con il bordo

- **Input:** `A 3`, `D`, `a 10`, `S`, `S`, `A 2`, `P`, `A -1`, `A x`, `X`,
  `s`, `Q`
- **Output atteso:**
  ```
    Robot in (0, 3) verso nord
    Robot in (0, 3) verso est
    Bordo raggiunto dopo 7 passi.
    Robot in (7, 3) verso est
    Robot in (7, 3) verso nord
    Robot in (7, 3) verso ovest
    Robot in (5, 3) verso ovest
    Robot in (5, 3) verso ovest
    Numero di passi non valido.
    Robot in (5, 3) verso ovest
    Numero di passi non valido.
    Robot in (5, 3) verso ovest
    Comando sconosciuto.
    Robot in (5, 3) verso ovest
    Robot in (5, 3) verso sud
  ```

### Test 2 – Fermo al bordo

- **Input:** `A 7`, `A 2`, `S`, `A 1`, `Q`
- **Output atteso:** `(0, 7)` verso nord; `Bordo raggiunto dopo 0 passi.`;
  verso ovest; `Bordo raggiunto dopo 0 passi.` (x non può scendere sotto
  0).
