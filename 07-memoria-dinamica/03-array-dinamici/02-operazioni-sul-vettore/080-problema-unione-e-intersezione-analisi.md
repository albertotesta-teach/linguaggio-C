# Analisi – 080-problema-unione-e-intersezione.c

## 1. Problema

Gli studenti si iscrivono ai laboratori di robotica e di fotografia indicando la matricola, in ordine sparso. Ogni matricola si inserisce in ordine, senza doppioni. Con i due vettori ordinati l'unione (chi resta il pomeriggio) e l'intersezione (chi deve scegliere) si calcolano con una sola passata parallela; ogni risultato è un vettore nuovo che il chiamante distrugge.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Vettore` | `dati (int *), n, capacita` | vettore dinamico di matricole |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `robotica`, `fotografia` | `Vettore *` | struct + blocco di n int (heap) | Iscrizioni ordinate |
| `tutti`, `entrambi` | `Vettore *` | creati da unione e intersezione | Risultati, da distruggere |
| `matricola`, `esito` | `int` | — | Valore letto ed esito dell'inserimento |
| `i`, `j` | `int` | — | Indici della passata parallela |

| Funzione | Compito |
|----------|---------|
| `inserisci_ordinato(v, valore)` | 1 inserito, 0 già presente, -1 memoria |
| `unione(a, b)` | Vettore nuovo con gli elementi di a o di b; NULL se manca memoria |
| `intersezione(a, b)` | Vettore nuovo con gli elementi comuni |
| `leggi_iscrizioni(laboratorio, v)` | Matricole fino a 0; 0 se manca memoria |
| `crea_vettore, aggiungi, lunghezza, elemento, distruggi_vettore` | Funzioni del vettore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Due laboratori

**a) Input** – `1042 1007 1100 1015 1007 -3 1088 0`, `1100 1003 1042 1120 1015 0`

**b) Output** – robotica (5), fotografia (5); unione (7): 1003 1007 1015 1042 1088 1100 1120; entrambi (3): 1015 1042 1100

**c) Variabili di supporto** – `i`, `j`

**d) Vincoli** – matricole positive

**e) Assunzioni** – 0 chiude l'elenco

**f) Algoritmo in linguaggio naturale** – fusione: si avanza sull'elemento minore; se uguali si avanza su entrambi.

### Caso d'uso 2 – Doppione e valore errato

**a) Input** – `1007` due volte, `-3`

**b) Output** – "1007 gia' iscritta", "matricola -3 non valida"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – inserisci_ordinato restituisce 0.

### Caso d'uso 3 – Quattro vettori

**a) Input** – —

**b) Output** – —

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – distruggi_vettore su tutti, anche NULL.
