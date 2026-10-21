# Analisi – 040-problema-dizionario.c

## 1. Problema

Per un'attività di inglese serve un piccolo dizionario: l'utente scrive una
parola, in italiano o in inglese, e il programma la traduce nell'altra
lingua. Se la parola non c'è, suggerisce le voci che iniziano con le stesse
due lettere. Maiuscole e minuscole non contano. Le ricerche continuano fino
a una riga vuota.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `parola` | `char[30]` | Parola cercata, letta da tastiera; una riga vuota termina |
| `italiano` | `char[10][16]` | Voci in italiano, in minuscolo (nel sorgente) |
| `inglese` | `char[10][16]` | Traduzioni (parallelo a `italiano`) |

### Output

- `IT -> EN: <italiano> = <inglese>` oppure `EN -> IT: <inglese> = <italiano>`.
- Se la parola non c'è: `"<parola>" non e' nel dizionario.` seguito da una
  riga `Forse cercavi: <voce> (<traduzione>)` per ogni suggerimento,
  oppure `Nessun suggerimento.`

### Vincoli

- La parola si converte in minuscolo prima della ricerca.
- Si cerca nell'inglese solo se la ricerca nell'italiano fallisce.
- I suggerimenti sono le voci (di entrambe le lingue) che iniziano con le
  stesse due lettere della parola (`strncmp(voce, parola, 2)`); si cercano
  solo se la parola ha almeno 2 lettere.

### Assunzioni

- Le voci del dizionario sono già in minuscolo e senza accenti.
- Nessuna parola compare in entrambe le lingue.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `letta` | `int` | 1 se la lettura è riuscita |
| `k` | `int` | Indice della voce trovata (-1 se assente) |
| `suggerimenti` | `int` | Voci suggerite nelle due lingue |
| `trovate` | `int` | In `suggerisci`: voci suggerite in un elenco |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `in_minuscolo` | `tolower` su ogni carattere |
| `cerca` | Indice della parola in un elenco con `strcmp`, oppure -1 |
| `suggerisci` | Stampa le voci con le stesse prime due lettere e restituisce quante sono |

### Algoritmo in linguaggio naturale

1. Leggere una parola.
2. Finché la lettura riesce e la parola non è vuota:
   1. convertirla in minuscolo;
   2. cercarla nell'italiano: se c'è stampare la traduzione inglese;
   3. altrimenti cercarla nell'inglese: se c'è stampare la traduzione italiana;
   4. altrimenti segnalare che non c'è, stampare i suggerimenti
      dell'italiano e dell'inglese e, se sono zero, `Nessun suggerimento.`;
   5. leggere la parola successiva.

## 3. Casi di test

### Test 1 – Parola italiana con maiuscola

- **Cosa si verifica**: conversione in minuscolo e traduzione IT → EN.
- **Input**: `Scuola`, poi riga vuota.
- **Valori intermedi attesi**: `parola` = `scuola`, `k` = 1 in `italiano`.
- **Output atteso**:
  ```
    IT -> EN: scuola = school
  ```

### Test 2 – Parola inglese

- **Cosa si verifica**: ricerca nell'inglese dopo il fallimento nell'italiano.
- **Input**: `BOOK`, poi riga vuota.
- **Output atteso**:
  ```
    EN -> IT: book = libro
  ```

### Test 3 – Parola sconosciuta con suggerimento

- **Cosa si verifica**: suggerimenti nell'italiano e nell'inglese.
- **Input**: `quadro`, `teach`, poi riga vuota.
- **Output atteso**:
  ```
    "quadro" non e' nel dizionario.
    Forse cercavi: quaderno (notebook)
    "teach" non e' nel dizionario.
    Forse cercavi: teacher (insegnante)
  ```

### Test 4 – Suggerimenti in entrambe le lingue

- **Cosa si verifica**: `suggerimenti` somma i risultati delle due chiamate.
- **Input**: `pe`, poi riga vuota.
- **Valori intermedi attesi**: `suggerimenti` = 1 + 1 = 2.
- **Output atteso**:
  ```
    "pe" non e' nel dizionario.
    Forse cercavi: penna (pen)
    Forse cercavi: pen (penna)
  ```

### Test 5 – Nessun suggerimento

- **Cosa si verifica**: parola senza voci simili e parola di una sola lettera.
- **Input**: `gatto`, `c`, poi riga vuota.
- **Valori intermedi attesi**: per `c` `suggerisci` non confronta nulla
  (lunghezza < 2), anche se esistono voci che iniziano per `c`.
- **Output atteso**:
  ```
    "gatto" non e' nel dizionario.
    Nessun suggerimento.
    "c" non e' nel dizionario.
    Nessun suggerimento.
  ```
