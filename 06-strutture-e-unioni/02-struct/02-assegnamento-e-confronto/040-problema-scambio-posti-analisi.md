# Analisi – 040-problema-scambio-posti.c

## 1. Problema

In laboratorio due studenti devono scambiarsi la postazione. Il programma
mostra che scambiare le intere struct (nome compreso) non sposta nessuno,
mentre lo scambio corretto riguarda solo i campi `fila` e `pc`. Due
studenti che risultano già nella stessa postazione vengono segnalati.
Ogni studente è una struct `Postazione`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `primo`, `secondo` | `Postazione` | Nome, fila e numero del pc di ciascuno studente |

### Output

- `Scambio delle schede intere (sbagliato):` con le due schede dopo lo
  scambio delle struct e la nota che nessuno si è spostato.
- `Scambio di fila e pc (corretto):` con le due schede dopo lo scambio dei
  soli campi.
- `I due studenti hanno gia' la stessa postazione: controllare il
  registro.` oppure `Dati non validi.`

### Vincoli

- L'assegnamento tra struct (`temp = sbagliato_primo;`) copia tutti i
  campi, nome compreso.
- Lo scambio corretto usa una variabile `int` di appoggio per ogni campo.
- Fila e pc devono essere positivi.

### Assunzioni

- Il nome è una sola parola di al massimo 19 caratteri.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Postazione` | `typedef struct { char nome[20]; int fila; int pc; } Postazione;` | Uno studente con la sua postazione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sbagliato_primo`, `sbagliato_secondo` | `Postazione` | Copie su cui si mostra lo scambio sbagliato |
| `temp` | `Postazione` | Appoggio per lo scambio di struct |
| `appoggio` | `int` | Appoggio per lo scambio dei campi |

### Algoritmo in linguaggio naturale

1. Leggere i due studenti; se la lettura fallisce rendere non valida la
   fila.
2. Se fila o pc non sono positivi, stampare `Dati non validi.`
3. Se le due postazioni coincidono, segnalarlo.
4. Altrimenti:
   1. copiare le schede, scambiarle intere con `temp` e stamparle;
   2. scambiare fila e pc delle schede originali e stamparle.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Scambio

- **Cosa si verifica:** la differenza tra i due scambi.
- **Input:** `Anna 2 5`, `Luca 3 1`
- **Output atteso:**
  ```
  Scambio delle schede intere (sbagliato):
    Luca     fila 3 pc 1
    Anna     fila 2 pc 5
    ogni nome ha ancora la sua postazione: nessuno si e' spostato

  Scambio di fila e pc (corretto):
    Anna     fila 3 pc 1
    Luca     fila 2 pc 5
  ```

### Test 2 – Stessa postazione

- **Input:** `Anna 2 5`, `Luca 2 5`
- **Output atteso:** `I due studenti hanno gia' la stessa postazione:
  controllare il registro.`

### Test 3 – Dati non validi

- **Input:** `Anna 0 5` `Luca 3 1`; poi `Anna 2 -1` `Luca 3 1`; poi
  `Anna x` `Luca 3 1`
- **Output atteso:** `Dati non validi.` in tutti e tre i casi.
