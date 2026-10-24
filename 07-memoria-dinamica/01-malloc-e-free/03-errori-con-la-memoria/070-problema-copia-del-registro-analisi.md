# Analisi – 070-problema-copia-del-registro.c

## 1. Problema

Prima dello scrutinio il coordinatore prova delle modifiche ai voti su una
copia del registro. La struct `Registro` contiene un puntatore all'array
dei voti: l'assegnamento tra struct copia il puntatore (copia
superficiale) e le due struct condividono i voti; `duplica` alloca un
nuovo blocco e copia i voti (copia profonda). Il programma applica le
stesse modifiche alle due copie e mostra l'effetto sull'originale.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `classe`, `originale.n` | `char[8]`, `int` | Classe (al massimo 3 caratteri) e numero di voti (1-30) |
| voti | `double` | Gli n voti |
| modifiche | una riga ciascuna | `posizione voto` (voto da 1 a 10); `FINE` termina, al massimo 10 |

### Output

- `modifica non valida` per ogni modifica scartata.
- L'originale; per la copia profonda i due indirizzi (diversi), la copia
  modificata e l'originale invariato; per la copia superficiale i due
  indirizzi (uguali), la copia e l'originale entrambi modificati.
- `Dati non validi.`, `Voti mancanti.`, `Memoria insufficiente.`

### Vincoli

- `originale.voti = malloc(n * sizeof *originale.voti)`.
- `duplica`: `*a = *da`, poi un nuovo blocco per `a->voti` e la copia
  degli elementi.
- La copia profonda si libera con il suo `free`; il blocco condiviso
  dalla copia superficiale si libera **una sola volta** (liberarlo due
  volte sarebbe un errore).
- Gli indirizzi stampati con `%p` cambiano a ogni esecuzione.
- Una modifica per riga. A fine input le modifiche terminano come con
  `FINE`.

### Assunzioni

- I voti iniziali sono validi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Registro` | `typedef struct { char classe[4]; int n; double *voti; } Registro;` | Registro con l'array dinamico dei voti |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `originale`, `superficiale`, `profonda` | `Registro` | Le tre struct |
| `posizioni`, `nuovi` | `int[10]`, `double[10]` | Modifiche da applicare |
| `modifiche`, `letti` | `int` | Contatori |

| Funzione | Compito |
|----------|---------|
| `duplica(da, a)` | Copia profonda; 0 se manca memoria |
| `applica(r, posizioni, nuovi, quante)` | Applica le modifiche |
| `stampa(titolo, r)` | Stampa i voti |

### Algoritmo in linguaggio naturale

1. Leggere classe e n, allocare e leggere i voti.
2. Leggere le modifiche valide.
3. Stampare l'originale; duplicarlo, modificare la copia e stampare
   entrambi; liberare la copia.
4. Assegnare l'originale a una seconda struct, modificarla e stampare
   entrambe.
5. Liberare il blocco dell'originale.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe); gli indirizzi
sono sostituiti da `<indirizzo>`.

### Test 1 – Due modifiche valide

- **Input:** `3B 5`, `6 7 5.5 8 4`, `3 6`, `1 x`, `9 7`, `5 11`, `5 6.5`,
  `FINE`
- **Output atteso:**
  ```
    modifica non valida
    modifica non valida
    modifica non valida
     originale  3B:  6.0  7.0  5.5  8.0  4.0

  1. Copia profonda: duplica(&originale, &copia)
     blocco dell'originale <indirizzo>, della copia <indirizzo>
     copia      3B:  6.0  7.0  6.0  8.0  6.5
     originale  3B:  6.0  7.0  5.5  8.0  4.0
     L'originale non cambia.

  2. Copia superficiale: copia = originale
     blocco dell'originale <indirizzo>, della copia <indirizzo>
     copia      3B:  6.0  7.0  6.0  8.0  6.5
     originale  3B:  6.0  7.0  6.0  8.0  6.5
     Anche l'originale e' cambiato: il blocco dei voti e' lo stesso.
  ```
  (nella copia profonda i due indirizzi sono diversi, nella superficiale
  uguali).

### Test 2 – Dati non validi

- **Input:** `QUARTA 5`
- **Output atteso:** `Dati non validi.`
