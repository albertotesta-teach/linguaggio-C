# Analisi – 060-problema-disegno-forme.c

## 1. Problema
Un programma didattico deve disegnare tre forme geometriche usando caratteri
ASCII: un rettangolo pieno, un triangolo rettangolo e una cornice (rettangolo
vuoto). Le dimensioni sono definite come costanti e condivise da tutte le
funzioni. L'obiettivo è mostrare come le funzioni void possano incapsulare
algoritmi di disegno autonomi e richiamabili in qualunque ordine.

## 2. Analisi

### Input
Nessuno: le dimensioni sono costanti `#define`.

| Costante | Valore | Descrizione |
|---|---|---|
| `LARGHEZZA` | 8 | Numero di colonne (usato da rettangolo e cornice) |
| `ALTEZZA` | 5 | Numero di righe (usato da tutte e tre le forme) |

### Output
Il titolo "Galleria di forme ASCII" e le tre forme, ciascuna preceduta da
una riga con nome e dimensioni e separata dalla successiva da una riga vuota:
- rettangolo pieno di `ALTEZZA` righe da `LARGHEZZA` asterischi;
- triangolo rettangolo in cui la riga i ha i asterischi;
- cornice: prima e ultima riga piene, righe intermedie con un asterisco
  solo nella prima e nell'ultima colonna.

### Vincoli
- `LARGHEZZA` e `ALTEZZA` sono maggiori di 0
- Per una cornice visibile servono `ALTEZZA` ≥ 2 e `LARGHEZZA` ≥ 2
- Modificando le costanti cambiano tutte le forme insieme

### Assunzioni
- Il terminale usa un carattere a larghezza fissa
- Le dimensioni restano fisse; renderle configurabili richiede i parametri
  (sezione 02)

### Variabili di supporto

| Variabile | Tipo | Ruolo |
|---|---|---|
| `riga` | int | Contatore della riga corrente (ciclo esterno), locale a ogni funzione |
| `colonna` | int | Contatore della colonna corrente (ciclo interno), locale a ogni funzione |

| Funzione | Tipo | Descrizione |
|---|---|---|
| `disegna_rettangolo` | void | Rettangolo pieno di asterischi |
| `disegna_triangolo` | void | Triangolo rettangolo con base in basso |
| `disegna_cornice` | void | Solo bordo esterno del rettangolo |
| `disegna_tutte_le_forme` | void | Chiama le tre funzioni con spaziatura |

### Algoritmo in linguaggio naturale
Rettangolo:
1. Per ogni riga da 0 a `ALTEZZA − 1`: stampare `LARGHEZZA` asterischi e
   andare a capo.

Triangolo:
1. Per ogni riga da 1 ad `ALTEZZA`: stampare tanti asterischi quanto vale
   la riga e andare a capo.

Cornice:
1. Per ogni riga da 0 a `ALTEZZA − 1` e ogni colonna da 0 a `LARGHEZZA − 1`:
   - se è la prima o l'ultima riga stampare `*`;
   - altrimenti, se è la prima o l'ultima colonna stampare `*`;
   - altrimenti stampare uno spazio.
2. Alla fine di ogni riga andare a capo.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si controlla quanto
stampato. I primi tre test riguardano la stessa esecuzione.

### Test 1 – Rettangolo pieno
- **Output atteso:**
```
Rettangolo (8x5):
********
********
********
********
********
```

### Test 2 – Triangolo rettangolo
- **Cosa si verifica:** la riga i ha esattamente i asterischi
- **Output atteso:**
```
Triangolo rettangolo (base 5):
*
**
***
****
*****
```

### Test 3 – Cornice
- **Cosa si verifica:** le righe intermedie hanno l'asterisco solo sui bordi
- **Output atteso:**
```
Cornice (8x5):
********
*      *
*      *
*      *
********
```

### Test 4 – Dimensioni diverse
- **Cosa si verifica:** le forme dipendono solo dalle costanti
- **Procedura:** porre `LARGHEZZA` 4 e `ALTEZZA` 3, ricompilare ed eseguire
- **Output atteso:** rettangolo 4×3, triangolo di 3 righe, cornice 4×3 con
  una sola riga intermedia `*  *`
