# Analisi – 080-problema-turni-lavoro.c

## 1. Problema

Il titolare di un bar ha pianificato le ore di 5 dipendenti per i 7 giorni
della settimana. Deve verificare che ognuno lavori le ore del contratto,
abbia almeno un giorno di riposo, e che ogni giorno ci siano almeno 3
persone in servizio.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ore` | `int[][]` | 5 × 7 | Ore previste; 0 = riposo |
| `nomi` | `char[][]` | 5 × 12 | Nomi, paralleli alle righe |
| `contratto` | `int[]` | 5 | Ore settimanali da contratto, parallele alle righe |
| `giorni` | `char[][]` | 7 × 4 | Sigle, parallele alle colonne |

| Funzione | Lavora su | Restituisce |
|----------|-----------|-------------|
| `ore_settimanali(ore, d)` | riga d | somma |
| `giorni_riposo(ore, d)` | riga d | numero di zeri |
| `persone_in_servizio(ore, g)` | colonna g | celle non nulle |
| `ore_giorno(ore, g)` | colonna g | somma |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Verifica per dipendente

**a) Input** – `ore`, `nomi`, `contratto`

**b) Output** – per ognuno: in linea, straordinario o ore mancanti, e giorni
di riposo; Sofia è segnalata con "NESSUN RIPOSO"

**c) Variabili di supporto** – `totale`, `riposi`

**d) Vincoli** – almeno `MIN_RIPOSI` giorni di riposo

**e) Assunzioni** – il riposo è un giorno con 0 ore

**f) Algoritmo in linguaggio naturale** – per ogni dipendente calcolare ore e
riposi con le funzioni di riga, confrontare le ore con il contratto e
segnalare l'assenza di riposi.

### Caso d'uso 2 – Copertura giornaliera

**a) Input** – `ore`, `giorni`

**b) Output** – persone e ore di ogni giorno; il venerdì (2 persone) è
segnalato come "SCOPERTO"

**c) Variabili di supporto** – `persone`

**d) Vincoli** – almeno `MIN_PERSONE` dipendenti con ore maggiori di 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni giorno contare con
`persone_in_servizio` e sommare con `ore_giorno`; segnalare i giorni sotto il minimo.
