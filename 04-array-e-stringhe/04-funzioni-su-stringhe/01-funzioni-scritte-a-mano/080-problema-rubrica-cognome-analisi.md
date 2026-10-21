# Analisi – 080-problema-rubrica-cognome.c

## 1. Problema

La rubrica di un ufficio contiene cognomi, nomi e numeri di telefono. Per
trovare un collega basta scrivere l'inizio del cognome, senza badare alle
maiuscole: il programma mostra tutti i contatti il cui cognome comincia con
quel testo e segnala le corrispondenze esatte. Le ricerche si ripetono
finché l'utente non scrive "fine".

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                                     |
|-----------|----------|------------|-------------------------------------------------|
| `ricerca` | `char[]` | 30         | Cognome o sua parte iniziale; "fine" termina    |

La rubrica (cognomi, nomi, telefoni) è inizializzata nel codice in tre array
paralleli.

### Output
- Per ogni ricerca i contatti trovati (cognome, nome, telefono), con
  "(esatto)" se il testo coincide con l'intero cognome, e il numero di
  contatti ("contatto" al singolare);
- "Nessun contatto trovato." oppure, per una riga vuota, "Scrivi almeno
  una lettera.";
- "Arrivederci." alla fine.

### Vincoli
- Un contatto corrisponde se il cognome **inizia** con il testo cercato;
  maiuscole e minuscole sono indifferenti
- Si mostrano **tutti** i contatti che corrispondono, nell'ordine della
  rubrica
- La corrispondenza esatta richiede che il testo coincida con il cognome
  intero
- `inizia_con` si ferma alla fine del prefisso o al primo carattere
  diverso: il prefisso è trovato se è stato percorso tutto
- "fine" termina in qualsiasi combinazione di maiuscole e minuscole
- I telefoni sono stringhe: contengono uno spazio e lo zero iniziale, che
  un numero perderebbe

### Assunzioni
- I cognomi non contengono lettere accentate

### Variabili di supporto

| Variabile  | Tipo       | Dimensione | Descrizione                          |
|------------|------------|------------|--------------------------------------|
| `cognomi`, `nomi`, `telefoni` | `char[][]` | 8 × 20 | Rubrica       |
| `letta`    | `int`      | —          | 0 se l'input è terminato             |
| `trovati`  | `int`      | —          | Contatti della ricerca corrente      |

| Funzione | Descrizione |
|---|---|
| `int leggi_riga(char s[], int dim)` | `fgets` e rimozione del `'\n'` |
| `int inizia_con(const char s[], const char prefisso[])` | 1 se s comincia con prefisso |
| `int uguali_ignorando_maiuscole(const char a[], const char b[])` | Uguaglianza senza maiuscole |
| `char minuscola(char c)` | Conversione del carattere |

### Algoritmo in linguaggio naturale
1. Leggere il testo da cercare.
2. Finché l'input non è terminato e il testo non è "fine":
   a. se il testo è vuoto chiedere almeno una lettera;
   b. altrimenti per ogni contatto il cui cognome inizia con il testo,
      stamparlo (con "(esatto)" se coincide) e contarlo; stampare il
      numero di contatti o il messaggio di nessun risultato;
   c. leggere il testo successivo.
3. Stampare il saluto.

## 3. Casi di test

Si inserisce una sequenza di ricerche, una per riga.

### Test 1 – Ricerche di vario tipo
- **Input:** `ross`, `Rossi`, `BIANC`, `z`, riga vuota, `FINE`
- **Output atteso:**
  - `ross` → Rossi Mario, Rossetti Paolo, Rossi Anna; `3 contatti`
  - `Rossi` → i due Rossi con `(esatto)`, Rossetti escluso; `2 contatti`
  - `BIANC` (maiuscolo) → Bianchi Lucia, Bianco Stefano, Bianchini Davide;
    `3 contatti`
  - `z` → `Nessun contatto trovato.`
  - riga vuota → `Scrivi almeno una lettera.`
  - `FINE` → `Arrivederci.`
- **Esempio di output:**
```
  Rossi      Mario    0131 220145  (esatto)
  Rossi      Anna     0131 220133  (esatto)
  2 contatti
```
