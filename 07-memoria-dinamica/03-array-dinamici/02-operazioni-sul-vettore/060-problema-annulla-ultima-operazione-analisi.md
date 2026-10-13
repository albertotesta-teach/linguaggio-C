# Analisi – 060-problema-annulla-ultima-operazione.c

## 1. Problema

Il docente corregge un voto del registro e vuole poter tornare indietro anche di più passi. Prima di ogni modifica il programma salva il voto vecchio in fondo a un vettore dinamico di double; il comando U toglie l'ultimo valore salvato e lo rimette. Si aggiunge e si toglie sempre dal fondo: l'ultima modifica è la prima annullata.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Storia` | `dati (double *), n, capacita` | voti salvati prima di ogni modifica |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `storia` | `Storia *` | struct + blocco di n double (heap) | Voti precedenti alle modifiche |
| `voto`, `nuovo`, `valore` | `double` | — | Voto attuale, voto proposto, numero letto |
| `comando`, `ok` | `char`, `int` | — | Comando e validità della modifica |

| Funzione | Compito |
|----------|---------|
| `aggiungi(s, valore)` | Salva in fondo, raddoppia se pieno |
| `togli_ultimo(s, &valore)` | Toglie l'ultimo e lo restituisce; 0 se vuota |
| `crea_storia, lunghezza, elemento, distruggi_storia` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Modifiche e annullamenti

**a) Input** – `= 7`, `+ 0.5`, `- 2`, `S`, `U`, `U`, `U`

**b) Output** – voto 7.0, 7.5, 5.5; storia [6.0 7.0 7.5]; annullando 7.5, 7.0, 6.0

**c) Variabili di supporto** – `storia`

**d) Vincoli** – voto tra 1 e 10

**e) Assunzioni** – voto iniziale 6

**f) Algoritmo in linguaggio naturale** – modifica: aggiungi(voto) poi voto = nuovo; U: togli_ultimo(&voto).

### Caso d'uso 2 – Fuori scala

**a) Input** – `+ 6` con voto 5.5, `= 11`

**b) Output** – "modifica non valida: voto invariato"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la modifica non si esegue e non si salva.

### Caso d'uso 3 – Niente da annullare

**a) Input** – `U` con storia vuota

**b) Output** – "niente da annullare"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – togli_ultimo restituisce 0.
