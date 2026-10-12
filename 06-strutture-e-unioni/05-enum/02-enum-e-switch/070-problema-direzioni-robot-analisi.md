# Analisi – 070-problema-direzioni-robot.c

## 1. Problema

Il robot del laboratorio si muove su una griglia 8 x 8 partendo da (0, 0) verso nord. Le direzioni sono in ordine orario, così girare è un calcolo modulo NUM_DIREZIONI; uno switch sulla direzione dà lo spostamento di ogni passo.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Direzione` | `NORD, EST, SUD, OVEST, NUM_DIREZIONI` | verso del robot |
| `Robot` | `x, y, verso` | stato del robot |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `robot` | `Robot` | — | Posizione e direzione |
| `passi`, `fatti` | `int` | — | Passi richiesti e fatti |

| Funzione | Compito |
|----------|---------|
| `avanza(r, passi)` | Si ferma al bordo; restituisce i passi fatti |
| `gira(r, lato)` | (verso + 1) o (verso + 3) modulo 4 |
| `nome(d)` | Tabella dei nomi |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Avanti

**a) Input** – `A 3`

**b) Output** – "Robot in (0, 3) verso nord"

**c) Variabili di supporto** – `robot.y`

**d) Vincoli** – griglia da 0 a 7

**e) Assunzioni** – partenza in (0, 0)

**f) Algoritmo in linguaggio naturale** – switch: NORD dy = 1, EST dx = 1, SUD dy = -1, OVEST dx = -1.

### Caso d'uso 2 – Bordo

**a) Input** – `D`, `A 10`

**b) Output** – "Bordo raggiunto dopo 7 passi.", robot in (7, 3)

**c) Variabili di supporto** – `fatti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo continua solo se la casella successiva è nella griglia.

### Caso d'uso 3 – Girare

**a) Input** – `S`, `S`

**b) Output** – nord, poi ovest

**c) Variabili di supporto** – `robot.verso`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – a sinistra si aggiunge NUM_DIREZIONI - 1 per evitare valori negativi.
