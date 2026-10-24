# Analisi – 080-problema-esito-prenotazione.c

## 1. Problema

Le classi prenotano l'aula magna per un'ora della settimana. `prenota`
controlla giorno, ora, posti, ora occupata e prenotazione già fatta dalla
classe, e restituisce un `Esito` con un valore per ogni motivo; il `main`
stampa il messaggio con uno `switch`, senza conoscere le regole. Alla fine
si stampa la tabella della settimana.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `classe` | `char[8]` | Sigla della classe (al massimo 3 caratteri); `FINE` termina |
| `studenti` | `int` | Partecipanti, positivo |
| `giorno`, `ora` | `int` | Giorno 1-5 (lunedì-venerdì), ora 1-6 |

### Output

- Per ogni richiesta il messaggio dell'esito: `Prenotazione registrata.`,
  `Giorno non valido: ...`, `Ora non valida: ...`,
  `L'aula magna ha solo 120 posti.`, `Ora gia' occupata da un'altra
  classe.`, `La classe ha gia' una prenotazione questa settimana.`;
  oppure `Classe X non valida.`, `Richiesta non valida.`
- La tabella ore × giorni con le classi (`-` se libera).

### Vincoli

- Controlli nell'ordine: giorno, ora, posti (al massimo 120), ora
  occupata, classe già prenotata.
- Ogni classe può avere una sola prenotazione alla settimana.
- L'aula è un array `char [5][6][4]`: una stringa per giorno e ora.
- Una prenotazione per riga; una riga non valida non interrompe il
  programma. A fine input termina come con `FINE`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Esito` | `typedef enum { PRENOTATA, GIORNO_NON_VALIDO, ORA_NON_VALIDA, POSTI_INSUFFICIENTI, GIA_OCCUPATA, CLASSE_GIA_PRENOTATA } Esito;` | Risultato della richiesta |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `aula` | `char[5][6][4]` | Classe che occupa ogni ora (stringa vuota = libera) |
| `giorni` | `const char *[5]` | Intestazioni della tabella |
| `finito` | `int` | Flag di uscita |

| Funzione | Compito |
|----------|---------|
| `prenota(aula, classe, studenti, giorno, ora)` | Controlli, registrazione, esito |
| `messaggio(e)` | Testo dell'esito con `switch` |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché non si termina:
   1. leggere la classe; con `FINE` o a fine input terminare;
   2. leggere studenti, giorno e ora; se mancano o gli studenti non sono
      positivi, richiesta non valida;
   3. se la classe è troppo lunga segnalarla;
   4. altrimenti stampare `messaggio(prenota(...))`;
   5. scartare il resto della riga.
2. Stampare la tabella.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Settimana di prenotazioni

- **Cosa si verifica:** ogni valore dell'enum `Esito` e gli errori di
  lettura.
- **Input:** `3A 25 1 2`, `4B 30 1 2`, `3A 25 2 3`, `5C 130 3 1`,
  `5C 28 6 1`, `5C 28 3 7`, `5C 28 3 1`, `2D abc`, `2D 0 1 1`,
  `PRIMA 20 1 1`, `1A 22 5 6`, `FINE`
- **Output atteso:**
  ```
    Prenotazione registrata.
    Ora gia' occupata da un'altra classe.
    La classe ha gia' una prenotazione questa settimana.
    L'aula magna ha solo 120 posti.
    Giorno non valido: da 1 (lunedi') a 5 (venerdi').
    Ora non valida: dalla 1a alla 6a.
    Prenotazione registrata.
    Richiesta non valida.
    Richiesta non valida.
    Classe PRIMA non valida.
    Prenotazione registrata.

        lun  mar  mer  gio  ven 
    1a  -    -    5C   -    -   
    2a  3A   -    -    -    -   
    3a  -    -    -    -    -   
    4a  -    -    -    -    -   
    5a  -    -    -    -    -   
    6a  -    -    -    -    1A  
  ```
