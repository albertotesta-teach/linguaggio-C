# Analisi – 040-problema-orario-settimanale.c

## 1. Problema

L'orario di ogni classe prima è una matrice di Lezione (5 giorni × 4 ore) dentro la struct Classe. Il programma stampa la griglia di una classe, le lezioni settimanali di un docente in tutte le classi e i conflitti tra le due classi: stesso docente o stessa aula nella stessa ora.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Lezione` | `materia, docente, aula` | un'ora di lezione |
| `Classe` | `nome, orario[GIORNI][ORE]` | classe con una matrice di Lezione |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `prime` | `Classe[]` | 2 | Classi con il loro orario |
| `nome` | `char[]` | 10 | Classe o docente letto |
| `classe` | `const Classe *` | — | Classe trovata |

| Funzione | Compito |
|----------|---------|
| `cerca_classe(c, n, nome)` | Puntatore alla classe o NULL |
| `stampa_orario(c)` | Una riga per ora, una colonna per giorno |
| `lezioni_docente(c, n, docente)` | Stampa le lezioni e restituisce le ore |
| `conflitti(a, b)` | Stampa e conta i conflitti |
| `nome_giorno(g)` | Lun ... Ven |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Griglia

**a) Input** – `O 1A`

**b) Output** – la tabella con le materie della 1A

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni ora h e ogni giorno g stampare c->orario[g][h].materia.

### Caso d'uso 2 – Ore di un docente

**a) Input** – `D Rossi`

**b) Output** – otto lezioni, "Rossi: 8 ore settimanali"

**c) Variabili di supporto** – `ore`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – tre cicli: giorno, ora, classe; confronto con strcmp sul docente.

### Caso d'uso 3 – Conflitti

**a) Input** – `C`

**b) Output** – "Mar 2a ora: Rossi in 1A e in 1B"; "Ven 2a ora: aula LabFis occupata da 1A e 1B"

**c) Variabili di supporto** – `trovati`

**d) Vincoli** – —

**e) Assunzioni** – solo due classi

**f) Algoritmo in linguaggio naturale** – confrontare cella per cella docente e aula delle due classi.

### Caso d'uso 4 – Classe inesistente

**a) Input** – `O 3C`

**b) Output** – "Classe 3C inesistente."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca_classe restituisce NULL.
