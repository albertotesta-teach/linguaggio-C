# Analisi – 060-problema-registro-presenze.c

## 1. Problema

Il registro di un corso serale contiene, per 6 studenti e 5 giorni, un
carattere: `P` presente, `A` assente, `R` ritardo (che conta come presenza).
Il docente vuole il riepilogo per studente (presenze, assenze, ritardi),
il numero di presenti per giorno, l'elenco di chi supera 1 assenza e il
dettaglio di uno studente scelto da tastiera.

## 2. Analisi

### Input

| Variabile | Tipo  | Descrizione                                  |
|-----------|-------|----------------------------------------------|
| `scelto`  | `int` | Numero dello studente da dettagliare (1–6)   |

Il registro, i nomi degli studenti e le sigle dei giorni sono inizializzati
nel codice.

### Output
- Il registro: per ogni studente le lettere dei cinque giorni, il numero di
  presenze, assenze e ritardi e la nota "<- oltre il limite" se le assenze
  superano il limite;
- il numero di presenti di ogni giorno;
- l'elenco numerato degli studenti e, per lo studente scelto, la situazione
  di ogni giorno (presente, presente con ritardo, assente).

### Vincoli
- Un ritardo conta sia come presenza sia come ritardo
- Il limite è `LIMITE_ASSENZE` (1): è segnalato chi ha **più** di 1 assenza
- Il riepilogo per studente scorre una **riga**, i presenti per giorno una
  **colonna** (presente = qualsiasi lettera diversa da `A`)
- Il numero dello studente si richiede finché non è tra 1 e 6; l'indice di
  riga è `scelto − 1`
- Ogni carattere diverso da `P` e `R` è contato come assenza (ramo
  `default` dello `switch`)
- Un numero di studente non numerico si scarta e si richiede; se l'input
  termina (EOF) prima di una scelta valida il dettaglio non viene stampato

### Assunzioni
- Il registro contiene solo le lettere P, A, R

### Variabili di supporto

| Variabile   | Tipo       | Dimensione | Descrizione                                 |
|-------------|------------|------------|---------------------------------------------|
| `registro`  | `char[][]` | 6 × 5      | Una lettera per studente e giorno           |
| `studenti`  | `char[][]` | 6 × 16     | Nomi, paralleli alle righe                  |
| `giorni`    | `char[][]` | 5 × 4      | Sigle, parallele alle colonne               |
| `presenze`, `assenze`, `ritardi` | `int` | — | Contatori della riga corrente     |
| `presenti_giorno` | `int` | —         | Contatore della colonna corrente            |
| `STUDENTI`, `GIORNI`, `LIMITE_ASSENZE` | `#define` | — | 6, 5, 1            |

### Algoritmo in linguaggio naturale
1. Per ogni studente stampare il nome e le lettere; con uno `switch` contare
   P come presenza, R come presenza e ritardo, altro come assenza; stampare
   i contatori e la nota se le assenze superano il limite.
2. Per ogni giorno contare le lettere diverse da `A` nella colonna e
   stampare il risultato.
3. Stampare l'elenco degli studenti; leggere il numero finché non è valido.
4. Per ogni giorno stampare la situazione dello studente scelto.

## 3. Casi di test

Il registro è fisso nel codice; l'unico dato letto è lo studente da
dettagliare.

### Test 1 – Riepilogo e presenti per giorno
- **Input:** qualsiasi studente valido (es. 1)
- **Output atteso:**
```
  Amato Elena         P    P    P    P    P       5    0    0
  Bruno Paolo         P    A    P    R    P       4    1    1
  Costa Marta         A    A    P    P    R       3    2    1  <- oltre il limite
  De Luca Ivan        P    P    R    R    P       5    0    2
  Fontana Rita        P    P    P    A    P       4    1    0
  Greco Omar          A    P    A    P    A       2    3    0  <- oltre il limite

  Presenti            4    4    5    5    5
```
- **Osservazione:** Bruno Paolo e Fontana Rita hanno 1 assenza, pari al
  limite, e non sono segnalati

### Test 2 – Dettaglio con numero non valido
- **Cosa si verifica:** la validazione del numero e il ritardo nel dettaglio
- **Input:** `0`, `9` (rifiutati), poi `3`
- **Output atteso:** la richiesta ripetuta due volte, poi
```
Presenze di Costa Marta:
  Lun: assente
  Mar: assente
  Mer: presente
  Gio: presente
  Ven: presente (ritardo)
```

### Test 3 – Scelta non numerica e fine dell'input
- **Cosa si verifica:** la chiusura senza ciclo infinito
- **Input:** `due`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Numero dello studente (1-6): Numero dello studente (1-6): 

Input terminato: nessuno studente scelto.
```
