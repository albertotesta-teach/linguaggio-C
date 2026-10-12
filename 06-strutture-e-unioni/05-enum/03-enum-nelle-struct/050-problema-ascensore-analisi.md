# Analisi – 050-problema-ascensore.c

## 1. Problema

L'ascensore della scuola serve i piani da 0 a 3. È una macchina a stati: passo fa avanzare l'ascensore di un passo con uno switch sullo stato (porte aperte, porte chiuse, in salita, in discesa). Per ogni chiamata il programma stampa i passi fino all'apertura delle porte al piano chiamato.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Stato` | `PORTE_APERTE, PORTE_CHIUSE, IN_SALITA, IN_DISCESA` | stato dell'ascensore |
| `Ascensore` | `piano, destinazione, stato` | ascensore |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ascensore` | `Ascensore` | — | Piano, destinazione e stato |
| `chiamata` | `int` | — | Piano letto |
| `passi` | `int` | — | Passi della corsa |

| Funzione | Compito |
|----------|---------|
| `passo(a)` | Un passo della macchina a stati |
| `nome(s)` | Testo dello stato |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Salita

**a) Input** – `2` dal piano 0

**b) Output** – porte chiuse, in salita, piano 1, piano 2 porte aperte: 4 passi

**c) Variabili di supporto** – `ascensore.stato`

**d) Vincoli** – —

**e) Assunzioni** – partenza al piano 0 con porte aperte

**f) Algoritmo in linguaggio naturale** – ripetere passo finché non è al piano con le porte aperte.

### Caso d'uso 2 – Discesa

**a) Input** – `0` dal piano 2

**b) Output** – porte chiuse, in discesa ... porte aperte

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – in IN_DISCESA il piano diminuisce; arrivato, le porte si aprono.

### Caso d'uso 3 – Già al piano

**a) Input** – `3` quando è al 3 con le porte aperte

**b) Output** – "Gia' al piano 3 con le porte aperte."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo non esegue passi.

### Caso d'uso 4 – Piano inesistente

**a) Input** – `5`

**b) Output** – "Il piano 5 non esiste."

**c) Variabili di supporto** – —

**d) Vincoli** – piani da 0 a 3

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la chiamata si scarta.
