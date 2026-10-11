# Analisi – 060-problema-registro-presenze.c

## 1. Problema

Il registro di un corso serale contiene, per 6 studenti e 5 giorni, un
carattere: `P` presente, `A` assente, `R` ritardo (che conta come presenza).
Il docente vuole il riepilogo per studente (presenze, assenze, ritardi),
il numero di presenti per giorno, l'elenco di chi supera 1 assenza e il
dettaglio di uno studente scelto da tastiera.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `registro` | `char[][]` | 6 × 5 | Una lettera per studente e giorno |
| `studenti` | `char[][]` | 6 × 16 | Nomi, paralleli alle righe |
| `giorni` | `char[][]` | 5 × 4 | Sigle, parallele alle colonne |
| `presenze`, `assenze`, `ritardi` | `int` | — | Contatori della riga corrente |
| `presenti_giorno` | `int` | — | Contatore della colonna corrente |
| `scelto` | `int` | — | Studente richiesto (da 1 a 6) |

Una matrice può contenere qualsiasi tipo: qui `char`, interpretati con uno
`switch`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Riepilogo per studente

**a) Input** – matrice `registro`

**b) Output** – tabella con le lettere, le tre colonne di conteggio e
"<- oltre il limite" per Costa Marta e Greco Omar

**c) Variabili di supporto** – `presenze`, `assenze`, `ritardi`

**d) Vincoli** – il ritardo incrementa sia `presenze` sia `ritardi`

**e) Assunzioni** – qualsiasi carattere diverso da `P` e `R` è un'assenza

**f) Algoritmo in linguaggio naturale**
1. Per ogni studente: azzerare i contatori e stampare il nome.
2. Per ogni giorno: stampare la lettera e aggiornare i contatori con uno `switch`.
3. Stampare i contatori; se le assenze superano 1, segnalarlo.

### Caso d'uso 2 – Presenti per giorno

**a) Input** – matrice `registro`

**b) Output** – riga "Presenti" con 4, 4, 5, 5, 5

**c) Variabili di supporto** – `presenti_giorno`

**d) Vincoli** – scorrimento per colonne; presente significa "diverso da `A`"

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni giorno contare le celle della
colonna diverse da `A` e stampare il conteggio.

### Caso d'uso 3 – Dettaglio di uno studente

**a) Input** – numero dello studente, es. 3

**b) Output** – presenze di Costa Marta giorno per giorno

**c) Variabili di supporto** – `scelto`

**d) Vincoli** – il numero viene richiesto finché non è tra 1 e 6; poi si
scorre una sola riga

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Stampare l'elenco numerato degli studenti.
2. Leggere il numero con validazione; calcolare l'indice `scelto - 1`.
3. Per ogni giorno stampare la sigla e il significato della lettera.
