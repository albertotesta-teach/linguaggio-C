# Analisi – 040-problema-registro-dei-ritardi.c

## 1. Problema

Il collaboratore all'ingresso registra ogni studente che entra in ritardo con data, nome e minuti. Il numero di ingressi dell'anno non si conosce: le registrazioni vanno in un vettore dinamico di struct `Ritardo`, che parte da 4 posti e raddoppia quando è pieno. Il programma legge le righe `gg/mm nome minuti` fino a FINE e stampa gli ingressi per mese (da settembre a giugno), la data con più ritardi e gli studenti con almeno 3 ritardi.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Ritardo` | `giorno, mese, studente[20], minuti` | un ingresso in ritardo |
| `Registro` | `dati (Ritardo *), n, capacita` | vettore dinamico di Ritardo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `registro` | `Registro *` | struct + blocco di n Ritardo (heap) | Tutte le registrazioni, crescita a raddoppio |
| `r` | `Ritardo` | — | Riga letta, poi copia dell'elemento i |
| `parola` | `char[]` | 16 | Prima parola: data o FINE |
| `per_mese` | `int[]` | 13 | Ingressi per mese (indice 1-12) |
| `massimo`, `peggiore` | `int` | — | Data con più ingressi |
| `conta` | `int` | — | Ritardi di una data o di uno studente |

| Funzione | Compito |
|----------|---------|
| `crea_registro(capacita)` | Alloca struct e blocco; NULL se manca memoria |
| `aggiungi(r, nuovo)` | Raddoppia con realloc se pieno, poi scrive in fondo; 0 se manca memoria |
| `lunghezza, capacita, elemento` | Accesso al registro senza toccare i campi |
| `data_valida(giorno, mese)` | Giorno esistente, mese di scuola (no luglio e agosto) |
| `conta_studente(r, nome, fino_a)` | Ritardi dello studente tra i primi fino_a elementi |
| `conta_data(r, giorno, mese)` | Ingressi in quella data |
| `distruggi_registro(r)` | Libera blocco e struct |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Un trimestre

**a) Input** – 11 righe da `15/09 Rossi 10` a `18/12 Verdi 25`, poi `FINE`

**b) Output** – 10 ingressi (capacità 16); ott 4; data peggiore 02/10 (3); avviso a Rossi (4) e Verdi (3)

**c) Variabili di supporto** – `per_mese`, `conta`

**d) Vincoli** – minuti ≥ 1

**e) Assunzioni** – date dello stesso anno scolastico

**f) Algoritmo in linguaggio naturale** – aggiungi per ogni riga valida; poi un ciclo su elemento(i) per i conteggi.

### Caso d'uso 2 – Data inesistente

**a) Input** – `31/11 Verdi 5`

**b) Output** – "riga non valida"

**c) Variabili di supporto** – —

**d) Vincoli** – giorno entro i giorni del mese

**e) Assunzioni** – febbraio fino a 29

**f) Algoritmo in linguaggio naturale** – la riga si scarta fino al fine riga.

### Caso d'uso 3 – Avviso una volta sola

**a) Input** – Rossi compare 4 volte

**b) Output** – una sola riga "Rossi: 4 ritardi"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – si stampa solo alla prima comparsa: conta_studente(nome, i) == 0.

### Caso d'uso 4 – Nessun ingresso

**a) Input** – `FINE`

**b) Output** – 0 ingressi, tutti i mesi a 0, nessuna data

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – peggiore resta -1.
