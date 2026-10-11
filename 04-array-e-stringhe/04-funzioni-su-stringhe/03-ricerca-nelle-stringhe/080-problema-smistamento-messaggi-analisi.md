# Analisi – 080-problema-smistamento-messaggi.c

## 1. Problema

Le richieste dei genitori arrivano allo sportello online della scuola e
devono essere inoltrate all'ufficio giusto (Didattica, Amministrazione,
Servizi). Ogni ufficio ha alcune parole chiave: il messaggio va all'ufficio
di cui contiene più parole chiave. Se non ne contiene nessuna, o se due
uffici sono a pari merito, va alla Segreteria generale. Alla fine si conta
quanti messaggi ha ricevuto ogni ufficio.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `uffici` | `char[][]` | 4 × 24 | Nomi degli uffici; l'ultimo è la Segreteria generale |
| `parole` | `char[][]` | 11 × 14 | Parole chiave (anche solo radici: "pagell", "assenz") |
| `ufficio_di` | `int[]` | 11 | Ufficio di ogni parola (parallelo a `parole`) |
| `messaggi` | `char[][]` | 6 × 80 | Richieste arrivate |
| `punteggi` | `int[]` | 4 | Parole trovate per ufficio nel messaggio corrente |
| `ricevuti` | `int[]` | 4 | Messaggi assegnati a ogni ufficio |
| `testo` | `char[]` | 80 | Messaggio in minuscolo |

| Funzione | Compito |
|----------|---------|
| `in_minuscolo` | Copia in minuscolo |
| `scegli_ufficio` | Ufficio con il punteggio massimo, oppure la Segreteria generale |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Un ufficio prevale

**a) Input** – "Vorrei prenotare un colloquio per parlare dei voti di mio figlio"

**b) Output** – didattica 2 → Didattica

**c) Variabili di supporto** – `punteggi`

**d) Vincoli** – i punteggi vanno azzerati a ogni messaggio

**e) Assunzioni** – le parole chiave sono in minuscolo

**f) Algoritmo in linguaggio naturale**
1. Convertire il messaggio in minuscolo e azzerare i punteggi.
2. Per ogni parola chiave presente (`strstr != NULL`) incrementare il
   punteggio del suo ufficio (`ufficio_di[p]`).
3. Scegliere l'ufficio con il punteggio massimo.

### Caso d'uso 2 – Radice di una parola

**a) Input** – "Quando escono le pagelle del primo quadrimestre?"

**b) Output** – Didattica

**c) Variabili di supporto** – parola chiave "pagell"

**d) Vincoli** – "pagella" non sarebbe contenuta in "pagelle": si usa la radice

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Pareggio o nessuna parola

**a) Input** – "Chiedo il rimborso della mensa per i giorni di assenza"; "Buongiorno, a chi posso chiedere informazioni?"

**b) Output** – Segreteria generale in entrambi i casi

**c) Variabili di supporto** – `migliore`, `pari`

**d) Vincoli** – una sola `return` in `scegli_ufficio`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Trovare il punteggio massimo e contare quanti uffici lo raggiungono.
2. Se il massimo è 0 o è raggiunto da più uffici scegliere la Segreteria
   generale, altrimenti l'ufficio con il massimo.
