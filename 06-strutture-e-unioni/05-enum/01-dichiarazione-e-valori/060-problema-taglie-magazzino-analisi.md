# Analisi – 060-problema-taglie-magazzino.c

## 1. Problema

Il comitato studentesco vende le magliette della scuola. Le taglie sono un enum, le scorte un array indicizzato dalla taglia. La sigla scritta dall'utente si cerca nella tabella delle sigle: la sua posizione è la costante dell'enum, NUM_TAGLIE indica una sigla inesistente.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Taglia` | `XS, S, M, L, XL, XXL, NUM_TAGLIE` | taglia della maglietta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `scorte` | `int[]` | NUM_TAGLIE | Magliette per taglia |
| `sigle` | `const char *[]` | NUM_TAGLIE | XS, S, M, L, XL, XXL |
| `t` | `Taglia` | — | Taglia trovata |
| `sigla`, `quantita` | `char[]`, `int` | 8, — | Argomenti del comando |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Stato

**a) Input** – `S`

**b) Output** – XS 4 "da riordinare", XXL 0 "ESAURITA"

**c) Variabili di supporto** – —

**d) Vincoli** – riordino sotto 5 magliette

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni taglia stampare la scorta e l'avviso.

### Caso d'uso 2 – Vendita e carico

**a) Input** – `V M 3`; `C XXL 10`

**b) Output** – "ne restano 17"; "Taglia XXL: 10 magliette."

**c) Variabili di supporto** – `scorte[t]`

**d) Vincoli** – la vendita non supera la scorta

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cercare la sigla, controllare la quantità, aggiornare scorte[t].

### Caso d'uso 3 – Errori

**a) Input** – `V XS 5`; `V XXL 1`; `V XXXL 2`; `V L 0`

**b) Output** – "ne restano solo 4"; "esaurita"; "inesistente"; "Quantita' non valida"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – t == NUM_TAGLIE dopo la ricerca indica una sigla sconosciuta.
