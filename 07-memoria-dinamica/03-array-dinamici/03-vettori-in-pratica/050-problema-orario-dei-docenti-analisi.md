# Analisi – 050-problema-orario-dei-docenti.c

## 1. Problema

Il coordinatore cerca le ore in cui tutti i docenti del consiglio di classe sono liberi per una riunione. Le lezioni arrivano come `docente giorno ora`. Ogni docente ha un proprio vettore dinamico di ore occupate (codice giorno × 10 + ora) che cresce indipendentemente dagli altri; un'ora è libera per tutti se nessun vettore la contiene.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Ore` | `dati (int *), n, capacita` | ore occupate di un docente |
| `Docente` | `nome[20], ore (Ore *)` | un docente e il suo vettore |
| `Consiglio` | `dati (Docente *), n, capacita` | vettore di docenti |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `consiglio` | `Consiglio *` | struct + blocco di n Docente (heap) | Docenti, ognuno con il suo vettore |
| `ore` di ogni docente | `Ore *` | struct + blocco di int (heap) | Ore occupate |
| `nome`, `giorno` | `char[]` | 20, 8 | Dati letti |
| `ora`, `g`, `indice`, `letti` | `int` | — | Ora, giorno 1-5, docente, valori letti |
| `libere`, `libere_giorno` | `int` | — | Ore libere comuni |

| Funzione | Compito |
|----------|---------|
| `aggiungi_docente(c, nome)` | Nuovo docente con vettore di ore vuoto; indice o -1 |
| `contiene(v, codice)` | 1 se l'ora è nel vettore |
| `numero_giorno(giorno)` | Da lun-ven a 1-5; 0 se non valido |
| `libera_per_tutti(c, codice)` | Nessun docente contiene il codice |
| `distruggi_consiglio(c)` | Prima ogni vettore di ore, poi il blocco dei docenti |
| `crea_ore, aggiungi, lunghezza, capacita, crea_consiglio, cerca_docente, nome_docente, ore_docente` | Funzioni dei due vettori |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tre docenti

**a) Input** – lezioni di Rossi (5), Bianchi (7), Verdi (9), poi `FINE`

**b) Output** – capacità 8, 8, 16; ore libere: gio 1 2 3 5 6, ven 1 2 3 4 5; totale 10 su 30

**c) Variabili di supporto** – `libere`

**d) Vincoli** – giorni lun-ven, ore 1-6

**e) Assunzioni** – una lezione per ora per docente

**f) Algoritmo in linguaggio naturale** – doppio ciclo giorno/ora con libera_per_tutti.

### Caso d'uso 2 – Lezione ripetuta

**a) Input** – `Rossi lun 1` due volte

**b) Output** – "Rossi lun 1 gia' inserita"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – contiene prima di aggiungere.

### Caso d'uso 3 – Dati errati

**a) Input** – `Neri sab 2`, `Neri gio x`

**b) Output** – "lezione non valida per Neri"

**c) Variabili di supporto** – `letti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se l'ora non è un numero si salta la parola.

### Caso d'uso 4 – Nessuna lezione

**a) Input** – `FINE`

**b) Output** – "Nessuna lezione inserita."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – numero_docenti == 0.
