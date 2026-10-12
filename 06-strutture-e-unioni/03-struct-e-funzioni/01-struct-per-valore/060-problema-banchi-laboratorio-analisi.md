# Analisi – 060-problema-banchi-laboratorio.c

## 1. Problema

Il tecnico del laboratorio di chimica posiziona un nuovo banco sulla pianta della stanza. Il programma controlla che il banco stia nella stanza e che non si sovrapponga ai banchi esistenti; in caso di sovrapposizione stampa l'area in comune. I rettangoli si passano per valore.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Rettangolo` | `x, y, larghezza, profondita` | banco sulla pianta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `stanza` | `Rettangolo` | — | Dimensioni della stanza |
| `banchi` | `Rettangolo[]` | 3 | Banchi esistenti |
| `nuovo` | `Rettangolo` | — | Banco letto |
| `conflitti` | `int` | — | Sovrapposizioni trovate |

| Funzione | Compito |
|----------|---------|
| `area(r)` | Larghezza × profondità |
| `sovrapposti(a, b)` | 1 se si sovrappongono in x e in y |
| `intersezione(a, b)` | Restituisce il rettangolo comune |
| `dentro(stanza, r)` | 1 se r sta nella stanza |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Sovrapposizione

**a) Input** – `200 100 200 200`

**b) Output** – sovrapposto al banco 1 per 4500 cm2 e al banco 2 per 7500 cm2

**c) Variabili di supporto** – `conflitti`

**d) Vincoli** – lati paralleli alle pareti

**e) Assunzioni** – misure in centimetri

**f) Algoritmo in linguaggio naturale** – per ogni banco controllare sovrapposti e stampare l'area dell'intersezione.

### Caso d'uso 2 – Posizione libera

**a) Input** – `400 450 200 100`

**b) Output** – "Posizione libera: banco di 20000 cm2 sistemato."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessun banco si sovrappone.

### Caso d'uso 3 – Fuori dalla stanza

**a) Input** – `800 500 200 200`

**b) Output** – "Il banco esce dalla stanza."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – dentro controlla i quattro lati.
