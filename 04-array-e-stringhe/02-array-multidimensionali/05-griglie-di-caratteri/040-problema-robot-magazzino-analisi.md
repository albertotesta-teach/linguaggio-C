# Analisi – 040-problema-robot-magazzino.c

## 1. Problema

In un magazzino automatico un robot deve raccogliere dei pacchi. La pianta è
una griglia di caratteri con scaffali (`#`), corridoi (`.`), pacchi (`P`) e il
robot (`R`). L'operatore guida il robot con i comandi N, S, E, O; il robot non
può uscire dalla mappa né attraversare gli scaffali. Entrando in una cella con
un pacco lo raccoglie. La sessione termina con Q oppure quando tutti i pacchi
sono stati raccolti; alla fine si stampano mosse e pacchi raccolti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `mappa` | `char[][]` | 6 × (10 + 1) | Pianta inizializzata con stringhe; `+1` per il `'\0'` |
| `r_robot`, `c_robot` | `int` | — | Posizione attuale del robot |
| `r_nuova`, `c_nuova` | `int` | — | Cella di arrivo da verificare |
| `dr`, `dc` | `int` | — | Spostamento scelto dal comando (-1, 0, +1) |
| `comando` | `char` | — | Comando letto |
| `raccolti`, `pacchi_rimasti`, `mosse` | `int` | — | Contatori |

| Funzione | Compito |
|----------|---------|
| `stampa_mappa` | Stampa le `COLONNE` celle di ogni riga |
| `conta_pacchi` | Conta le celle `'P'` iniziali |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Spostamento valido con raccolta

**a) Input** – comando che porta il robot su una cella `'P'`

**b) Output** – "Pacco raccolto! (n)"

**c) Variabili di supporto** – `dr`, `dc`, `r_nuova`, `c_nuova`

**d) Vincoli** – la vecchia cella diventa `'.'`, la nuova `'R'`

**e) Assunzioni** – la mappa contiene una sola `'R'`, in posizione (0, 0)

**f) Algoritmo in linguaggio naturale**
1. Con uno `switch` sul comando impostare `dr` e `dc`.
2. Calcolare la cella di arrivo `r_robot + dr`, `c_robot + dc`.
3. Se è dentro la mappa e non è uno scaffale: se contiene un pacco
   incrementare `raccolti` e decrementare `pacchi_rimasti`.
4. Liberare la cella vecchia, scrivere `'R'` nella nuova, aggiornare la
   posizione e il numero di mosse.

### Caso d'uso 2 – Movimento bloccato

**a) Input** – comando verso uno scaffale o oltre il bordo

**b) Output** – "Scaffale: movimento annullato." oppure "Bordo del magazzino…"

**c) Variabili di supporto** – `r_nuova`, `c_nuova`

**d) Vincoli** – il controllo dei limiti va fatto **prima** di leggere
`mappa[r_nuova][c_nuova]`, per non accedere fuori dalla matrice

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la posizione non cambia e la mossa
non viene contata.

### Caso d'uso 3 – Comando sconosciuto

**a) Input** – un carattere diverso da N S E O Q

**b) Output** – "Comando sconosciuto."

**c) Variabili di supporto** – `dr`, `dc` restano 0

**d) Vincoli** – il ramo `default` dello `switch`

**e) Assunzioni** – i comandi sono accettati anche in minuscolo

**f) Algoritmo in linguaggio naturale** – con `dr == 0` e `dc == 0` il blocco
di spostamento non viene eseguito.

### Caso d'uso 4 – Fine sessione

**a) Input** – `Q` oppure raccolta dell'ultimo pacco

**b) Output** – mappa finale, mosse, pacchi raccolti e rimasti;
"Missione completata!" se non resta nessun pacco

**c) Variabili di supporto** – `pacchi_rimasti`

**d) Vincoli** – dopo l'ultimo pacco non si chiede un altro comando

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Il ciclo continua finché il comando non è Q e restano pacchi.
2. Il nuovo comando si legge solo se restano pacchi.
3. Al termine stampare la mappa e il riepilogo.
