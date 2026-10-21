# Analisi – 050-problema-cambio-password.c

## 1. Problema

Il portale del registro elettronico permette di cambiare la password. Prima
si verifica quella attuale (al massimo 3 tentativi), poi si chiede la nuova:
deve avere da 8 a 20 caratteri ed essere diversa dall'attuale. La nuova
password va riscritta per conferma; se le due versioni non coincidono si
ricomincia. Alla fine la nuova password sostituisce la vecchia.

## 2. Analisi

### Input

| Variabile  | Tipo     | Dimensione | Descrizione                         |
|------------|----------|------------|-------------------------------------|
| `inserita` | `char[]` | 40         | Tentativo di password attuale       |
| `nuova`    | `char[]` | 40         | Nuova password                      |
| `conferma` | `char[]` | 40         | Ripetizione della nuova password    |

La password memorizzata è inizializzata nel codice: `Sole2024`.

### Output
- Per ogni tentativo sbagliato "Password errata (n di 3 tentativi).";
- per ogni nuova password rifiutata il motivo: lunghezza non valida (con il
  numero di caratteri), uguale all'attuale, conferma diversa;
- alla fine "Password cambiata (N caratteri)." oppure "Troppi tentativi
  errati: procedura annullata.".

### Vincoli
- Le stringhe si confrontano con `strcmp` (0 = uguali), che distingue le
  maiuscole; la lunghezza si misura con `strlen`
- La password attuale ha al massimo `TENTATIVI` (3) tentativi
- La nuova password deve avere da 8 a 20 caratteri (estremi compresi) ed
  essere diversa dall'attuale
- Se la conferma non coincide si ricomincia dalla richiesta della nuova
  password
- La nuova password sostituisce la vecchia con `strcpy` solo dopo la
  conferma
- I due cicli sono governati da flag (`autenticato`, `cambiata`,
  `fine_input`), senza `break`
- Se l'input termina (`leggi_riga` restituisce 0) la procedura si annulla
  con il messaggio `Input terminato: procedura annullata.`

### Assunzioni
- Le password non contengono spazi iniziali o finali significativi

### Variabili di supporto

| Variabile     | Tipo  | Descrizione                                  |
|---------------|-------|----------------------------------------------|
| `password`    | `char[]` (40) | Password memorizzata                 |
| `errori`      | `int` | Tentativi sbagliati                          |
| `autenticato`, `cambiata` | `int` | Flag dei due cicli               |
| `fine_input`  | `int` | 1 se l'input è terminato                     |
| `lung`        | `int` | Lunghezza della nuova password               |

### Algoritmo in linguaggio naturale
1. Finché non autenticato, i tentativi sono meno di 3 e l'input non è
   terminato: leggere la password; se la lettura fallisce porre
   `fine_input = 1`; se coincide porre `autenticato = 1`, altrimenti
   contare l'errore e segnalarlo.
2. Finché autenticato, non ancora cambiata e l'input non è terminato:
   a. leggere la nuova password (se la lettura fallisce porre
      `fine_input = 1`) e misurarla;
   b. se la lunghezza non è tra 8 e 20, oppure è uguale all'attuale,
      segnalarlo;
   c. altrimenti leggere la conferma (se la lettura fallisce porre
      `fine_input = 1`): se diversa segnalarlo, altrimenti copiare la nuova
      password e porre `cambiata = 1`.
3. Stampare l'esito: password cambiata, input terminato oppure troppi
   tentativi errati.

## 3. Casi di test

Si inseriscono le password nell'ordine richiesto.

### Test 1 – Cambio riuscito dopo tre rifiuti
- **Input:** `Sole2024` (attuale), `corta`, `Sole2024`, `Luna2025!` con
  conferma `Luna2025?`, poi `Luna2025!` con conferma `Luna2025!`
- **Output atteso:** `Lunghezza non valida: 5 caratteri.`,
  `La nuova password deve essere diversa da quella attuale.`,
  `Le due password non coincidono, ricomincia.` e infine
  `Password cambiata (9 caratteri).`

### Test 2 – Tre tentativi sbagliati
- **Input:** `a`, `b`, `c`
- **Output atteso:**
```
  Password errata (1 di 3 tentativi).
  Password errata (2 di 3 tentativi).
  Password errata (3 di 3 tentativi).
Troppi tentativi errati: procedura annullata.
```

### Test 3 – Maiuscole
- **Cosa si verifica:** `strcmp` distingue le maiuscole
- **Input:** `sole2024`
- **Output atteso:** `Password errata (1 di 3 tentativi).`

### Test 4 – Fine dell'input durante la procedura
- **Cosa si verifica:** se l'input termina, la procedura si chiude invece
  di ripetere la richiesta all'infinito
- **Input:** `Sole2024` e poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Password attuale: Nuova password (8-20 caratteri): 
Input terminato: procedura annullata.
```
