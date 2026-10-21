# Analisi – 050-problema-verifica-pin.c

## 1. Problema

Un terminale di pagamento chiede il PIN di 5 cifre della carta. L'utente ha
al massimo 3 tentativi: al terzo errore la carta viene bloccata. Un valore
che non ha 5 cifre è un errore di digitazione: viene segnalato e non consuma
un tentativo.

## 2. Analisi

### Input

| Variabile      | Tipo  | Significato                                    |
|----------------|-------|------------------------------------------------|
| `pin_inserito` | `int` | Valore digitato, letto a ogni tentativo        |

### Output
Dopo ogni inserimento: l'avviso di formato non valido, oppure "PIN errato"
con i tentativi rimasti. Al termine: "PIN corretto. Pagamento autorizzato."
oppure "Carta BLOCCATA: troppi tentativi errati."

### Vincoli
- Un PIN valido nel formato ha 5 cifre: è compreso tra 10000 e 99999
- I tentativi validi sono al massimo 3; un formato errato non incrementa
  `tentativi`
- Il ciclo termina per due motivi, entrambi nella condizione:
  `!pin_corretto && tentativi < MAX_TENTATIVI`
- L'esito si decide guardando il flag e non il numero di tentativi: con il
  PIN corretto al terzo tentativo `tentativi` vale 3 come quando la carta
  viene bloccata

### Assunzioni
- L'utente inserisce numeri interi
- Il PIN della carta è fissato nel programma

### Variabili di supporto

| Variabile      | Tipo        | Significato                 |
|----------------|-------------|-----------------------------|
| `tentativi`    | `int`       | Tentativi validi usati      |
| `pin_corretto` | `int` (0/1) | Flag di successo            |

Costanti: `PIN_CARTA`, `MAX_TENTATIVI`, `PIN_MIN` e `PIN_MAX`.

### Algoritmo in linguaggio naturale
1. Porre `tentativi = 0` e `pin_corretto = 0`.
2. Finché il PIN non è corretto e i tentativi sono meno di 3:
   a. leggere il PIN;
   b. se non è tra 10000 e 99999, segnalare il formato errato;
   c. altrimenti incrementare `tentativi`; se il PIN coincide porre
      `pin_corretto = 1`, altrimenti stampare i tentativi rimasti.
3. Se `pin_corretto` vale 1 autorizzare il pagamento, altrimenti bloccare
   la carta.

## 3. Casi di test

Per ogni caso si esegue il programma con la sequenza di input indicata e si
confronta quanto stampato con l'output atteso. Il PIN della carta è 27183.

### Test 1 – PIN corretto dopo un formato errato e un errore
- **Cosa si verifica:** il formato errato non consuma un tentativo
- **Input:** 1234 (formato errato), 11111 (errato), 27183 (corretto)
- **Output atteso:** "Formato non valido", "PIN errato. Tentativi rimasti: 2",
  "PIN corretto. Pagamento autorizzato."

### Test 2 – Tre errori
- **Cosa si verifica:** il ciclo termina perché `tentativi` raggiunge 3
- **Input:** 11111, 22222, 33333
- **Output atteso:** due messaggi di PIN errato con i tentativi rimasti, poi
  "Carta BLOCCATA: troppi tentativi errati."

### Test 3 – PIN corretto al terzo tentativo
- **Cosa si verifica:** l'esito dipende dal flag, non dal numero di tentativi
- **Input:** 11111, 22222, 27183
- **Output atteso:** "PIN corretto. Pagamento autorizzato."
