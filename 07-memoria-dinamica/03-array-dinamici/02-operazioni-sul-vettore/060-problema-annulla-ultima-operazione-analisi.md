# Analisi – 060-problema-annulla-ultima-operazione.c

## 1. Problema

Il docente corregge un voto del registro e vuole poter tornare indietro
anche di più passi. Prima di ogni modifica il programma salva il voto
vecchio in fondo a un vettore dinamico di `double`; il comando U toglie
l'ultimo valore salvato e lo rimette. Si aggiunge e si toglie sempre dal
fondo: l'ultima modifica è la prima annullata.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `= v` imposta, `+ v` aumenta, `- v` diminuisce, `U` annulla, `S` stato, `Q` fine (anche minuscoli) |
| `valore` | `double` | Argomento della modifica |

### Output

- `Voto iniziale: 6.0`.
- `voto V` dopo una modifica, oppure
  `modifica non valida: voto invariato V`.
- `annullata: voto V`, `niente da annullare`.
- `S`: il voto e la storia dei valori salvati.
- `Memoria insufficiente: modifica non eseguita.`,
  `Comando sconosciuto.`

### Vincoli

- Vettore `{double *dati; int n; int capacita;}` con capacità iniziale 2 e
  raddoppio; il `main` usa solo le funzioni del vettore.
- Il voto vecchio si salva prima della modifica; se il salvataggio non
  riesce la modifica non si fa.
- Il nuovo voto deve stare tra 1 e 10.
- `togli_ultimo` riduce n e restituisce l'ultimo valore (comportamento a
  pila).
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Il voto iniziale è 6.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Storia` | `typedef struct { double *dati; int n; int capacita; } Storia;` | Vettore dei voti precedenti |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `storia` | `Storia *` | Il vettore |
| `voto`, `nuovo`, `valore` | `double` | Voto corrente, calcolato, letto |
| `ok` | `int` | Modifica valida |

| Funzione | Compito |
|----------|---------|
| `crea_storia`, `distruggi_storia` | Allocazione e liberazione |
| `aggiungi(s, valore)` | Salva in fondo |
| `togli_ultimo(s, &valore)` | Toglie dal fondo; 0 se vuota |
| `lunghezza`, `elemento` | Accesso |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando; per `=`, `+`, `-`
   calcolare il nuovo voto, controllarlo, salvare il vecchio e
   applicarlo; per `U` riprendere l'ultimo salvato; per `S` stampare;
   scartare il resto della riga.
2. Distruggere la storia.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Modifiche e annullamenti

- **Input:** `S`, `= 7`, `+ 1.5`, `- 3`, `+ 5`, `= abc`, `S`, `U`, `u`,
  `U extra`, `U`, `U`, `S`, `X`, `Q`
- **Output atteso:**
  ```
  Voto iniziale: 6.0
    voto 6.0, storia [ ]
    voto 7.0
    voto 8.5
    voto 5.5
    modifica non valida: voto invariato 5.5
    modifica non valida: voto invariato 5.5
    voto 5.5, storia [ 6.0 7.0 8.5 ]
    annullata: voto 8.5
    annullata: voto 7.0
    annullata: voto 6.0
    niente da annullare
    niente da annullare
    voto 6.0, storia [ ]
    Comando sconosciuto.
  ```
  (5.5 + 5 = 10.5 supera 10).
