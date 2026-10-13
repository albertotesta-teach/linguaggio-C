# Analisi – 080-problema-statistiche-del-torneo.c

## 1. Problema

Al torneo di calcetto d'istituto il numero di squadre e di partite non è noto. Ogni partita `casa ospite gol gol` si registra due volte, una per squadra dal suo punto di vista, nel vettore di risultati della squadra. Dai risultati si ricavano partite, vittorie, pareggi, sconfitte, gol e punti; il vettore delle squadre si ordina con selection sort per la classifica, e si stampa il cammino della prima.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Risultato` | `avversario[8], fatti, subiti` | una partita dal punto di vista della squadra |
| `Risultati` | `dati (Risultato *), n, capacita` | partite di una squadra |
| `Squadra` | `nome[8], risultati (Risultati *)` | una squadra |
| `Torneo` | `dati (Squadra *), n, capacita` | vettore di squadre |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `torneo` | `Torneo *` | struct + blocco di n Squadra (heap) | Squadre |
| `risultati` di ogni squadra | `Risultati *` | struct + blocco di Risultato (heap) | Partite della squadra |
| `casa`, `ospite` | `char[]` | 8 | Squadre lette |
| `gol_casa`, `gol_ospite`, `letti` | `int` | — | Punteggio e valori letti |
| `r`, `x` | `Risultati *`, `Risultato` | — | Per la stampa |

| Funzione | Compito |
|----------|---------|
| `registra(t, casa, ospite, gol_casa, gol_ospite)` | Crea le squadre se servono e aggiunge il risultato a entrambe |
| `segno(x), conta(r, s)` | 1, 0, -1 e quante partite con quel segno |
| `punti, gol_fatti, gol_subiti` | Statistiche dal vettore dei risultati |
| `prima_in_classifica(a, b)` | Punti, poi differenza reti, poi gol fatti |
| `ordina_classifica(t)` | Selection sort scambiando struct Squadra |
| `distruggi_torneo(t)` | Prima ogni vettore di risultati, poi il resto |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Torneo a quattro

**a) Input** – 8 partite valide, poi `FINE`

**b) Output** – 3B 7 pt (+4), 4A 7 pt (+1), 2D 4 pt, 5C 3 pt; cammino di 3B: P V N V

**c) Variabili di supporto** – `r`

**d) Vincoli** – gol ≥ 0

**e) Assunzioni** – nomi fino a 7 caratteri

**f) Algoritmo in linguaggio naturale** – registra per ogni partita; ordina; stampa.

### Caso d'uso 2 – Parità di punti

**a) Input** – 3B e 4A a 7

**b) Output** – 3B prima per differenza reti

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima_in_classifica.

### Caso d'uso 3 – Partite non valide

**a) Input** – `5C 5C 1 0`, `2D 4A x`

**b) Output** – "partita non valida"

**c) Variabili di supporto** – `letti`

**d) Vincoli** – squadre diverse

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – con meno di 3 valori letti si salta la parola.

### Caso d'uso 4 – Scambio

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – scambiando Squadra si scambiano i puntatori: i vettori di risultati non si spostano.
