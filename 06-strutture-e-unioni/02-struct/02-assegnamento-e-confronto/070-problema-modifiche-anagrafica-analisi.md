# Analisi – 070-problema-modifiche-anagrafica.c

## 1. Problema

La segreteria aggiorna telefono, email e classe di uno studente. Le
modifiche si fanno su una copia della scheda (`modificata = originale`);
premendo solo Invio un campo resta invariato. Il programma elenca i campi
cambiati e, con la conferma, copia la scheda modificata su quella
ufficiale con un solo assegnamento. La scheda è una struct `Anagrafica`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| telefono, email | righe di testo | Nuovo valore; riga vuota = invariato |
| classe | riga di testo | Una cifra da 1 a 5; riga vuota = invariata |
| conferma | riga di testo | `S`/`s` per confermare |
| `originale` | `Anagrafica` | Scheda iniziale (nel sorgente): Marino Chiara, 0131 555 1234, famiglia.marino@posta.it, classe 3 |

### Output

- Le richieste con il valore attuale tra parentesi quadre.
- `Modifiche:` con l'elenco `campo: vecchio -> nuovo` oppure `nessuna`.
- Se ci sono modifiche: `Confermi N modifiche? (S/N):` (`modifica` al
  singolare) e `Scheda aggiornata.` o `Modifiche scartate.`
- La scheda ufficiale finale.

### Vincoli

- Le stringhe si confrontano con `strcmp`, la classe con `!=`.
- Un valore troppo lungo per il campo (telefono oltre 15 caratteri, email
  oltre 39) viene ignorato: il campo resta invariato.
- Una classe non valida (non una sola cifra da 1 a 5) lascia la classe
  invariata.
- Le righe si leggono con `fgets`; di una riga più lunga del buffer si
  scarta il resto. A fine input una riga vale come vuota.

### Assunzioni

- Cognome e nome non si modificano.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Anagrafica` | `typedef struct { char cognome[20]; char nome[20]; char telefono[16]; char email[40]; int classe; } Anagrafica;` | Scheda dello studente |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `modificata` | `Anagrafica` | Copia su cui si lavora |
| `riga` | `char[80]` | Riga letta |
| `cambiati` | `int` | Numero di campi modificati |

| Funzione | Compito |
|----------|---------|
| `leggi_riga(riga, lunghezza)` | Legge una riga, toglie l'a capo, scarta il resto di una riga troppo lunga |

### Algoritmo in linguaggio naturale

1. Copiare la scheda ufficiale in `modificata`.
2. Per telefono, email e classe: leggere una riga e, se non vuota e
   valida, aggiornare il campo di `modificata`.
3. Confrontare i campi delle due schede, stampare quelli cambiati e
   contarli.
4. Se non ce ne sono stampare `nessuna`; altrimenti chiedere conferma e,
   con `S`, eseguire `originale = modificata`.
5. Stampare la scheda ufficiale.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Due modifiche confermate

- **Input:** `333 1234567`, riga vuota, `4`, `S`
- **Output atteso:**
  ```
  Scheda di Marino Chiara (Invio per lasciare invariato)
  Telefono [0131 555 1234]: Email [famiglia.marino@posta.it]: Classe [3]: 
  Modifiche:
    telefono: 0131 555 1234 -> 333 1234567
    classe:   3 -> 4
  Confermi 2 modifiche? (S/N): Scheda aggiornata.
  Scheda ufficiale: Marino Chiara, 333 1234567, famiglia.marino@posta.it, classe 4
  ```

### Test 2 – Nessuna modifica

- **Input:** tre righe vuote
- **Output atteso:** `Modifiche:`, `nessuna` e la scheda invariata.

### Test 3 – Modifica scartata e classe non valida

- **Input:** riga vuota, `nuova@mail.it`, `7`, `n`
- **Output atteso:**
  ```
  Modifiche:
    email:    famiglia.marino@posta.it -> nuova@mail.it
  Confermi 1 modifica? (S/N): Modifiche scartate.
  Scheda ufficiale: Marino Chiara, 0131 555 1234, famiglia.marino@posta.it, classe 3
  ```

### Test 4 – Valore troppo lungo

- **Input:** un telefono di 61 cifre, due righe vuote
- **Output atteso:** `nessuna`: il telefono resta invariato.
