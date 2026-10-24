# Analisi – 080-problema-unione-e-intersezione.c

## 1. Problema

Gli studenti si iscrivono ai laboratori di robotica e di fotografia
indicando la matricola, in ordine sparso. Ogni matricola si inserisce in
ordine, senza doppioni. Con i due vettori ordinati l'unione (chi resta il
pomeriggio) e l'intersezione (chi deve scegliere) si calcolano con una
sola passata parallela; ogni risultato è un vettore nuovo che il chiamante
distrugge.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| matricole | `int` | Per ogni laboratorio le matricole (positive) fino a 0 |

### Output

- `M gia' iscritta`, `matricola M non valida`, `matricola non valida` per
  i valori scartati.
- I quattro elenchi ordinati con il numero di elementi: robotica,
  fotografia, almeno un laboratorio, entrambi.
- `Memoria insufficiente.`

### Vincoli

- Vettore `{int *dati; int n; int capacita;}` con capacità iniziale 4 e
  raddoppio; le funzioni di insieme usano solo `lunghezza` ed `elemento`.
- `inserisci_ordinato`: trova la posizione, aggiunge in fondo e sposta
  avanti gli elementi maggiori; 0 se il valore c'era già.
- Unione e intersezione: due indici che avanzano sui due vettori ordinati
  (una sola passata, n + m confronti al massimo); se un'aggiunta fallisce
  il vettore parziale si distrugge e si restituisce `NULL`.
- Tutti i vettori si distruggono alla fine (`distruggi_vettore(NULL)` è
  ammesso).
- Una parola non numerica si scarta; a fine input la lista termina come
  con 0.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Vettore` | `typedef struct { int *dati; int n; int capacita; } Vettore;` | Vettore dinamico di matricole |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `robotica`, `fotografia` | `Vettore *` | Iscrizioni ordinate |
| `tutti`, `entrambi` | `Vettore *` | Unione e intersezione |
| `ok` | `int` | Allocazioni riuscite |

| Funzione | Compito |
|----------|---------|
| `crea_vettore`, `distruggi_vettore` | Allocazione e liberazione |
| `aggiungi`, `inserisci_ordinato` | Inserimenti |
| `lunghezza`, `elemento` | Accesso |
| `unione(a, b)`, `intersezione(a, b)` | Nuovi vettori |
| `leggi_iscrizioni(laboratorio, v)` | Legge le matricole fino a 0 |
| `stampa(titolo, v)` | Stampa un vettore |

### Algoritmo in linguaggio naturale

1. Creare i due vettori e leggere le iscrizioni in ordine.
2. Calcolare unione e intersezione.
3. Stampare i quattro elenchi.
4. Distruggere tutti i vettori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Due laboratori

- **Input:** `1042 1017 1033 1017 -5 abc 1050 0`, `1033 1061 1042 1008 0`
- **Output atteso:**
  ```
    1017 gia' iscritta
    matricola -5 non valida
    matricola non valida

  Robotica (4): 1017 1033 1042 1050
  Fotografia (4): 1008 1033 1042 1061
  Almeno un laboratorio (6): 1008 1017 1033 1042 1050 1061
  Entrambi (devono scegliere) (2): 1033 1042
  ```
