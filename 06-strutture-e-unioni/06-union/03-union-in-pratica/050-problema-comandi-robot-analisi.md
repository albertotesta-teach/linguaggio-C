# Analisi – 050-problema-comandi-robot.c

## 1. Problema

Il robot del laboratorio esegue un programma scritto a righe (MUOVI, RUOTA, DI). In una prima fase ogni riga diventa un Comando, una union etichettata con i dati del suo tipo; le righe sbagliate si scartano. Nella seconda fase uno switch sull'etichetta esegue i comandi aggiornando posizione e orientamento.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Comando` | `tipo, union anonima {muovi {dx, dy}, gradi, testo}` | comando del robot |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `programma` | `Comando[]` | 10 | Comandi validi |
| `riga` | `char[]` | 64 | Riga letta |
| `x`, `y`, `direzione` | `int` | — | Stato del robot |

| Funzione | Compito |
|----------|---------|
| `analizza(riga, &c)` | Riconosce il comando e legge i suoi dati; 0 se la riga non è valida |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Programma valido

**a) Input** – `MUOVI 3 4`, `RUOTA 90`, `DI Buongiorno 3B!`, `MUOVI -1 2`, `RUOTA -180`

**b) Output** – posizione finale (2, 6), orientamento 270 gradi

**c) Variabili di supporto** – `x`, `y`, `direzione`

**d) Vincoli** – al massimo 10 comandi

**e) Assunzioni** – griglia senza limiti

**f) Algoritmo in linguaggio naturale** – prima fase: analizza; seconda fase: switch sul tipo.

### Caso d'uso 2 – Righe scartate

**a) Input** – `RUOTA 45`; `SALTA 2`

**b) Output** – "riga 4 scartata"; "riga 5 scartata"

**c) Variabili di supporto** – —

**d) Vincoli** – gradi multipli di 90

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – analizza restituisce 0.

### Caso d'uso 3 – Orientamento

**a) Input** – `RUOTA -180` da 90

**b) Output** – 270 gradi

**c) Variabili di supporto** – `direzione`

**d) Vincoli** – da 0 a 359

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ((direzione + gradi) % 360 + 360) % 360 evita valori negativi.
