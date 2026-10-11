# Analisi – 080-problema-ricerca-con-esito.c

## 1. Problema

La rastrelliera della scuola ha 6 posti con lucchetto elettronico. Con `E tessera` la bici occupa il primo posto libero (se la tessera non ne occupa già uno), con `U tessera` il posto si libera. Il programma segnala tessere sconosciute e rastrelliera piena.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `posti` | `int[]` | 6 | Tessera che occupa il posto, 0 se libero |
| `posto` | `int *` | — | Elemento trovato dalla ricerca, `NULL` se nessuno |
| `comando`, `tessera` | `char`, `int` | — | Comando letto |

| Funzione | Compito |
|----------|---------|
| `cerca(v, n, valore, &trovato)` | 1 se trovato e puntatore nel parametro di uscita, 0 e `NULL` altrimenti |
| `stampa(posti, n)` | Mappa della rastrelliera |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ingresso

**a) Input** – `E 3310`

**b) Output** – "Posto 1 assegnato."

**c) Variabili di supporto** – `posto`

**d) Vincoli** – prima si controlla che la tessera non abbia già un posto

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – `cerca(posti, 6, 0, &posto)` trova il primo libero; si scrive `*posto = tessera`.

### Caso d'uso 2 – Uscita

**a) Input** – `U 1877`

**b) Output** – "Posto 4 liberato."

**c) Variabili di supporto** – `posto`

**d) Vincoli** – il posto si ricava con `posto - posti + 1`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cercare la tessera e scrivere 0 tramite il puntatore.

### Caso d'uso 3 – Ricerca senza esito

**a) Input** – `U 9999`; `E 4500` a rastrelliera piena

**b) Output** – "Nessuna bici con la tessera 9999."; "Rastrelliera piena."

**c) Variabili di supporto** – `posto` = `NULL`

**d) Vincoli** – con esito 0 il puntatore non si usa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il valore di ritorno decide; il puntatore si usa solo se l'esito è 1.
