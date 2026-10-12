# Analisi – 050-problema-orari-treni.c

## 1. Problema

Per quattro treni regionali usati dagli studenti il programma legge il ritardo, calcola l'orario di arrivo e l'orario di arrivo a scuola (12 minuti a piedi) e controlla se è prima della campanella delle 8:00. Le funzioni sugli orari ricevono e restituiscono Orario per valore.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Orario` | `ore, minuti` | ora del giorno |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `partenze` | `Orario[]` | 4 | Orari di partenza |
| `durate` | `int[]` | 4 | Minuti di viaggio |
| `arrivo`, `a_scuola` | `Orario` | — | Orari calcolati |
| `ritardo` | `int` | — | Minuti di ritardo letti |

| Funzione | Compito |
|----------|---------|
| `crea_orario(ore, minuti)` | Costruisce un Orario |
| `aggiungi_minuti(o, minuti)` | Restituisce un nuovo Orario, anche oltre la mezzanotte |
| `differenza(da, a)` | Minuti tra due orari |
| `stampa(o)` | Formato hh:mm |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – In orario

**a) Input** – ritardo `0` per Acqui Terme

**b) Output** – arrivo 07:40, a scuola 07:52, 8 min di margine

**c) Variabili di supporto** – `arrivo`, `a_scuola`

**d) Vincoli** – campanella alle 8:00

**e) Assunzioni** – 12 minuti di cammino

**f) Algoritmo in linguaggio naturale** – aggiungi_minuti(partenza, durata + ritardo), poi altri 12 minuti.

### Caso d'uso 2 – In ritardo

**a) Input** – ritardo `12` per Novi Ligure

**b) Output** – a scuola 08:06: "RITARDO di 6 min"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – differenza negativa tra arrivo a scuola e campanella.

### Caso d'uso 3 – Fine

**a) Input** – ritardo negativo

**b) Output** – il programma termina

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo si ferma prima dell'ultimo treno.
