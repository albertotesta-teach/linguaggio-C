# Analisi – 060-problema-menu-ristorante.c

## 1. Problema

Una trattoria vuole un programma per prendere le ordinazioni. Il menu va
stampato raggruppato per categoria; poi il cameriere scrive i piatti ordinati
(senza badare alle maiuscole) uno per riga e chiude con "conto". Il
programma conta le porzioni, ignora i piatti non presenti nel menu e stampa
il conto con il coperto.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `piatti` | `char[][]` | 8 × 26 | Nomi dei piatti |
| `categoria` | `char[][]` | 8 × 26 | Categoria di ogni piatto (parallelo) |
| `prezzi` | `int[]` | 8 | Prezzo in centesimi (parallelo) |
| `porzioni` | `int[]` | 8 | Porzioni ordinate (parallelo) |
| `categorie` | `char[][]` | 4 × 26 | Ordine di stampa delle categorie |
| `coperti` | `int` | — | Persone al tavolo |
| `totale` | `int` | — | Conto in centesimi |

| Funzione | Compito |
|----------|---------|
| `uguali_senza_maiuscole` | Confronto con `tolower` |
| `cerca_piatto` | Indice del piatto, ignorando le maiuscole, oppure -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Menu per categoria

**a) Input** – array del menu

**b) Output** – Primi, Secondi, Contorni, Dolci con i rispettivi piatti

**c) Variabili di supporto** – `c`, `k`

**d) Vincoli** – l'ordine delle categorie è quello di `categorie`, non quello dei piatti

**e) Assunzioni** – ogni piatto ha una categoria presente in `categorie`

**f) Algoritmo in linguaggio naturale** – per ogni categoria stampare il nome
e poi i piatti con `strcmp(categoria[k], categorie[c]) == 0`.

### Caso d'uso 2 – Ordinazione

**a) Input** – `agnolotti al sugo`, `BONET`, `Tiramisu`, …

**b) Output** – "+ Agnolotti al sugo", "+ Bonet", "Tiramisu non è nel menu."

**c) Variabili di supporto** – `porzioni`

**d) Vincoli** – il ciclo termina con "conto" (in qualsiasi forma) o a fine input

**e) Assunzioni** – il nome del piatto è scritto per intero

**f) Algoritmo in linguaggio naturale** – per ogni riga cercare il piatto: se
c'è incrementare `porzioni[k]`, altrimenti segnalarlo.

### Caso d'uso 3 – Conto

**a) Input** – porzioni ordinate, 2 coperti

**b) Output** – righe con quantità e importo, coperto, totale 53.00

**c) Variabili di supporto** – `totale`

**d) Vincoli** – si stampano solo i piatti con almeno una porzione

**e) Assunzioni** – coperto di 2.50 euro a persona

**f) Algoritmo in linguaggio naturale** – totale = coperti × coperto + somma di
porzioni × prezzo per ogni piatto ordinato.
