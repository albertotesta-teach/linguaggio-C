# Analisi – 050-problema-contatore-caratteri.c

## 1. Problema

Un programma di analisi testuale deve contare le occorrenze di ogni lettera
dell'alfabeto in un testo, visualizzare la distribuzione con percentuale e
istogramma, identificare la lettera più e meno frequente e contare quante
lettere distinte sono presenti.

---

## 2. Analisi

### Input
Nessun input da tastiera: il testo è una stringa fissa nel codice.

| Variabile | Tipo     | Descrizione                                  |
|-----------|----------|----------------------------------------------|
| `testo`   | `char[]` | Testo da analizzare, terminato da `'\0'`     |

### Output
- Una tabella con, per ogni lettera presente, il numero di occorrenze, la
  percentuale sul totale delle lettere e un istogramma (un asterisco per
  occorrenza);
- il totale delle lettere analizzate;
- la lettera più frequente e la meno frequente tra quelle presenti;
- il numero di lettere distinte usate.

### Vincoli
- Si contano solo le lettere: spazi, cifre e punteggiatura sono ignorati
- Le maiuscole sono convertite in minuscole (aggiungendo 32) e contate
  insieme
- La tabella mostra solo le lettere con almeno un'occorrenza
- La lettera meno frequente si cerca solo tra quelle presenti, altrimenti
  sarebbe sempre una lettera assente con 0 occorrenze
- In caso di parità si sceglie la lettera che viene prima nell'alfabeto
- Le percentuali si calcolano sul totale delle lettere, non dei caratteri

### Assunzioni
- La codifica è ASCII: le lettere minuscole hanno codici consecutivi
- Il testo non contiene lettere accentate (verrebbero ignorate)
- Il testo contiene almeno una lettera

### Variabili di supporto

Il punto chiave è la **conversione carattere → indice**: sottraendo `'a'` da
una lettera minuscola si ottiene un indice tra 0 e 25.

```
  Carattere:  'a'   'b'   'c'  ...  'z'
  Indice:      0     1     2   ...   25      (c - 'a')
```

| Variabile          | Tipo      | Dimensione | Descrizione                                     |
|--------------------|-----------|------------|-------------------------------------------------|
| `frequenze`        | `int[]`   | 26         | `frequenze[i]` = occorrenze della lettera `'a'+i` |
| `totale_lettere`   | `int`     | —          | Lettere trovate nel testo                       |
| `indice_max`       | `int`     | —          | Lettera più frequente                           |
| `indice_min`       | `int`     | —          | Lettera meno frequente (-1 finché nessuna)      |
| `lettere_distinte` | `int`     | —          | Numero di celle con frequenza > 0               |
| `LETTERE`          | `#define` | 26         | Lettere dell'alfabeto                           |

### Algoritmo in linguaggio naturale
1. Scorrere il testo fino a `'\0'`; per ogni carattere: se è maiuscolo
   convertirlo in minuscolo; se è una lettera incrementare
   `frequenze[c - 'a']` e `totale_lettere`.
2. Per ogni lettera con frequenza positiva stampare lettera, frequenza,
   percentuale e asterischi; stampare il totale.
3. Scorrere le 26 lettere aggiornando l'indice del massimo e, tra le sole
   lettere presenti, quello del minimo (partendo da -1).
4. Stampare le lettere più e meno frequenti.
5. Contare e stampare le lettere distinte.

---

## 3. Casi di test

Il testo è fisso nel codice: il Test 2 richiede di sostituirlo e ricompilare.

### Test 1 – Testo del programma
- **Valori intermedi attesi:** 129 lettere su 17 lettere diverse
- **Output atteso (righe finali):**
```
Totale lettere analizzate: 129

Lettera piu' frequente : 'a'  (21 occorrenze)
Lettera meno frequente : 'v'  (1 occorrenza/e)
Lettere distinte usate : 17 su 26
```
- **Osservazione:** anche la 'z' ha 1 occorrenza, ma vince la 'v' perché
  viene prima nell'alfabeto

### Test 2 – Maiuscole, cifre e punteggiatura
- **Cosa si verifica:** la conversione in minuscolo, i caratteri ignorati e
  la parità tra tutte le lettere
- **Procedura:** sostituire il testo con `"Ciao, CIAO! 123 "`
- **Output atteso:**
```
    a     |    2  |   25.0%     | **
    c     |    2  |   25.0%     | **
    i     |    2  |   25.0%     | **
    o     |    2  |   25.0%     | **

Totale lettere analizzate: 8

Lettera piu' frequente : 'a'  (2 occorrenze)
Lettera meno frequente : 'a'  (2 occorrenza/e)
Lettere distinte usate : 4 su 26
```
