# Analisi – 060-problema-pagella-classe.c

## 1. Problema

Allo scrutinio finale ogni studente riceve un esito in base al numero di
insufficienze: nessuna → ammesso, 1 o 2 → sospensione del giudizio, 3 o più
→ non ammesso. Il programma deve stampare la pagella di 6 studenti in 5
materie con media ed esito, le statistiche per materia e lo studente con la
media più alta, organizzando i calcoli in funzioni.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voti` | `int[][]` | 6 × 5 | Riga = studente, colonna = materia |
| `studenti` | `char[][]` | 6 × 16 | Nomi, paralleli alle righe |
| `materie` | `char[][]` | 5 × 16 | Nomi, paralleli alle colonne |
| `migliore` | `int` | — | Studente con la media più alta |

| Funzione | Lavora su | Restituisce |
|----------|-----------|-------------|
| `media_studente(voti, s)` | riga s | media (double) |
| `insufficienze_studente(voti, s)` | riga s | conteggio |
| `media_materia(voti, n, m)` | colonna m | media (double) |
| `insufficienze_materia(voti, n, m)` | colonna m | conteggio |
| `stampa_esito(insufficienze)` | — | stampa l'esito |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Pagelle ed esiti

**a) Input** – matrici `voti`, `studenti`, `materie`

**b) Output** – per ogni studente voti, media ed esito (es. Colombo Luca 5.60
SOSPENSIONE (2), Ferri Matteo NON AMMESSO)

**c) Variabili di supporto** – nessuna oltre agli indici

**d) Vincoli** – l'esito dipende solo dal numero di insufficienze

**e) Assunzioni** – voti interi da 1 a 10

**f) Algoritmo in linguaggio naturale**
1. Stampare l'intestazione con le prime tre lettere di ogni materia (`%4.3s`).
2. Per ogni studente: stampare nome e voti, la media della riga e l'esito
   ottenuto dal conteggio delle insufficienze.
3. Aggiornare `migliore` se la media supera quella del migliore finora.

### Caso d'uso 2 – Statistiche per materia

**a) Input** – matrice `voti`

**b) Output** – media e insufficienze di ogni materia (es. Matematica 5.67, 3)

**c) Variabili di supporto** – nessuna

**d) Vincoli** – le funzioni di colonna ricevono anche il numero di righe `n`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni materia chiamare
`media_materia` e `insufficienze_materia` e stampare i risultati.

### Caso d'uso 3 – Studente migliore

**a) Input** – risultati di `media_studente`

**b) Output** – "Media piu' alta: Esposito Ilaria (8.60)"

**c) Variabili di supporto** – `migliore`

**d) Vincoli** – in caso di parità resta il primo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ricerca del massimo sulle medie, svolta
durante la stampa delle pagelle.
