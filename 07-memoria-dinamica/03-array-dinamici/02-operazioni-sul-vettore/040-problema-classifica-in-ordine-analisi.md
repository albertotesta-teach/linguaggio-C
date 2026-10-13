# Analisi – 040-problema-classifica-in-ordine.c

## 1. Problema

Al traguardo della corsa campestre i giudici comunicano i tempi, non sempre nell'ordine di arrivo. La classifica è un vettore dinamico di `Arrivo` tenuto sempre ordinato per tempo: ogni nuovo tempo si inserisce nella sua posizione e un atleta squalificato si rimuove. La classifica è pronta in ogni momento, con il distacco dal primo.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Arrivo` | `nome[20], secondi` | un atleta e il suo tempo |
| `Classifica` | `dati (Arrivo *), n, capacita` | vettore ordinato per tempo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `classifica` | `Classifica *` | struct + blocco di n Arrivo (heap) | Arrivi ordinati per tempo |
| `a`, `primo` | `Arrivo` | — | Arrivo letto; elemento stampato e primo in classifica |
| `minuti`, `secondi` | `int` | — | Tempo letto come mm:ss |
| `posizione` | `int` | — | Dove inserire o chi rimuovere |
| `nome`, `comando` | `char[]`, `char` | 20 | Comando e atleta |

| Funzione | Compito |
|----------|---------|
| `inserisci(c, posizione, a)` | Fa posto spostando a destra, raddoppia se pieno; 0 se fallisce |
| `rimuovi(c, posizione)` | Sposta a sinistra i successivi |
| `posizione_per_tempo(c, secondi)` | Primo atleta con tempo maggiore (a parità il nuovo va dopo) |
| `cerca(c, nome)` | Indice dell'atleta o -1 |
| `crea_classifica, lunghezza, elemento, distruggi_classifica` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Arrivi in ordine sparso

**a) Input** – `A Rossi 12:40`, `A Bianchi 11:55`, `A Verdi 13:10`, `A Neri 12:40`, `A Gialli 11:20`

**b) Output** – posizioni 1, 1, 3, 3, 1; classifica Gialli, Bianchi, Rossi, Neri, Verdi

**c) Variabili di supporto** – `posizione`

**d) Vincoli** – secondi 0-59

**e) Assunzioni** – tempi uguali: prima chi è arrivato prima in classifica

**f) Algoritmo in linguaggio naturale** – posizione_per_tempo, poi inserisci.

### Caso d'uso 2 – Doppio tempo e dati errati

**a) Input** – `A Rossi 12:00`, `A Russo 12:61`

**b) Output** – "Rossi ha gia' un tempo.", "Dati non validi."

**c) Variabili di supporto** – —

**d) Vincoli** – un tempo per atleta

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca prima di inserire.

### Caso d'uso 3 – Squalifica

**a) Input** – `S Bianchi`, `C`

**b) Output** – Rossi sale al 2° posto con +80 s

**c) Variabili di supporto** – —

**d) Vincoli** – atleta in classifica

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – rimuovi alla posizione trovata.

### Caso d'uso 4 – Distacco

**a) Input** – `C`

**b) Output** – +0 s per il primo, poi differenze in secondi

**c) Variabili di supporto** – `primo`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – a.secondi - elemento(0).secondi.
