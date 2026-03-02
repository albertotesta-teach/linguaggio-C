# Analisi – 050-problema-conta-occorrenze.c

## 1. Problema

Un correttore ortografico di base deve analizzare un testo inserito
dall'utente e contare quante volte compare una determinata lettera,
distinguendo tra maiuscole e minuscole e fornendo anche il totale
case-insensitive.

---

## 2. Analisi generale e struttura dati

| Variabile               | Tipo     | Dimensione | Motivazione                                              |
|-------------------------|----------|------------|----------------------------------------------------------|
| `testo`                 | `char[]` | 201        | Testo con spazi, max 200 caratteri + `'\0'`              |
| `lettera`               | `char`   | —          | Lettera da cercare, letta con `scanf`                    |
| `lettera_maiuscola`     | `char`   | —          | Versione maiuscola della lettera cercata                 |
| `lettera_minuscola`     | `char`   | —          | Versione minuscola della lettera cercata                 |
| `occorrenze_esatte`     | `int`    | —          | Contatore occorrenze con stesso case dell'input          |
| `occorrenze_maiuscola`  | `int`    | —          | Contatore occorrenze della versione maiuscola            |
| `occorrenze_minuscola`  | `int`    | —          | Contatore occorrenze della versione minuscola            |
| `c`                     | `char`   | —          | Carattere corrente durante la scansione                  |
| `i`                     | `int`    | —          | Indice per scorrere il testo                             |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura del testo e della lettera

**a) Input**
Testo con spazi (max 200 caratteri) e una singola lettera da tastiera.

**b) Output**
Nessun output diretto: i valori sono memorizzati in `testo` e `lettera`.

**c) Variabili di supporto**
- `i` (`int`): indice per la rimozione del `'\n'` da `fgets`.

**d) Vincoli**
- Il testo viene letto con `fgets` per permettere spazi.
- La lettera viene letta con `scanf(" %c", &lettera)`: lo spazio
  prima di `%c` scarta il `'\n'` residuo nel buffer.
- Il `'\n'` lasciato da `fgets` nel testo va rimosso prima della scansione.

**e) Assunzioni**
- La lettera è un singolo carattere ASCII stampabile.
- Non sono gestite lettere accentate.

**f) Algoritmo in linguaggio naturale**
```
1. Leggere il testo con fgets; rimuovere '\n'.
2. Leggere la lettera con scanf(" %c", &lettera).
```

---

### Caso d'uso 2 – Calcolo delle varianti maiuscola/minuscola

**a) Input**
La variabile `lettera`.

**b) Output**
Nessun output diretto: popola `lettera_maiuscola` e `lettera_minuscola`.

**c) Variabili di supporto**
- `lettera_maiuscola`, `lettera_minuscola` (`char`): derivate da `lettera`.

**d) Vincoli**
- La conversione usa la differenza ASCII di 32 tra maiuscole e minuscole,
  valida solo per le lettere dell'alfabeto latino non accentato.

**e) Assunzioni**
- Se la lettera non è alfabetica, maiuscola e minuscola coincidono con la lettera stessa.

**f) Algoritmo in linguaggio naturale**
```
1. Se lettera è tra 'a' e 'z':
   - lettera_minuscola = lettera
   - lettera_maiuscola = lettera - 32
2. Altrimenti se lettera è tra 'A' e 'Z':
   - lettera_maiuscola = lettera
   - lettera_minuscola = lettera + 32
3. Altrimenti:
   - lettera_maiuscola = lettera_minuscola = lettera
```

---

### Caso d'uso 3 – Scansione e conteggio occorrenze

**a) Input**
`testo`, `lettera`, `lettera_maiuscola`, `lettera_minuscola`.

**b) Output**
Nessun output diretto: aggiorna i tre contatori.

**c) Variabili di supporto**
- `c` (`char`): carattere corrente.
- `i` (`int`): indice di scansione.
- `occorrenze_esatte`, `occorrenze_maiuscola`, `occorrenze_minuscola` (`int`).

**d) Vincoli**
- Il ciclo si ferma al `'\0'` terminatore.
- Un singolo carattere può incrementare al massimo due contatori
  (es. se `lettera` è `'a'`, un `'a'` nel testo incrementa sia
  `occorrenze_esatte` che `occorrenze_minuscola`).

**e) Assunzioni**
- I contatori sono inizializzati a 0 prima del ciclo.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare i a 0.
2. Finché testo[i] non è '\0':
   a. c = testo[i].
   b. Se c == lettera: incrementare occorrenze_esatte.
   c. Se c == lettera_maiuscola: incrementare occorrenze_maiuscola.
   d. Se c == lettera_minuscola: incrementare occorrenze_minuscola.
   e. Incrementare i.
```

---

### Caso d'uso 4 – Stampa risultati

**a) Input**
Tutti i contatori e le variabili di input.

**b) Output**
```
════════════════════════════════════
  RISULTATI ANALISI
════════════════════════════════════
  Testo     : "Il mare è calmo e limpido"
  Lettera   : 'a'
────────────────────────────────────
  Occorrenze esatte ('a')   : 3
  Occorrenze maiuscola ('A'): 0
  Occorrenze minuscola ('a'): 3
  Totale (case-insensitive)  : 3
════════════════════════════════════
```

**c) Variabili di supporto**
Nessuna variabile aggiuntiva.

**d) Vincoli**
- Il totale case-insensitive è la somma di maiuscole e minuscole,
  non di `occorrenze_esatte` (che potrebbe già essere inclusa in una delle due).

**e) Assunzioni**
- Il testo non è vuoto (nessuna verifica esplicita in questa versione).

**f) Algoritmo in linguaggio naturale**
```
1. Stampare testo e lettera cercata.
2. Stampare occorrenze esatte.
3. Stampare occorrenze maiuscola e minuscola separatamente.
4. Stampare il totale come somma di maiuscole e minuscole.
```
