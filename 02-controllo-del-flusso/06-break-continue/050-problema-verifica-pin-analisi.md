# Analisi – 050-problema-verifica-pin.c

## 1. Problema

Un terminale di pagamento chiede il PIN di 5 cifre della carta. L'utente ha
al massimo 3 tentativi: al terzo errore la carta viene bloccata. Un valore
che non ha 5 cifre è un errore di digitazione: viene segnalato e non consuma
un tentativo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `pin_inserito` | `int` | Valore digitato |
| `tentativi` | `int` | Tentativi validi usati |
| `pin_corretto` | `int` (0/1) | Flag di successo |

Costanti: `PIN_CARTA`, `MAX_TENTATIVI`, `PIN_MIN` e `PIN_MAX`
(un PIN di 5 cifre sta tra 10000 e 99999).

Il ciclo termina per due motivi, entrambi nella condizione:
`!pin_corretto && tentativi < MAX_TENTATIVI`. Dopo il ciclo il flag dice
quale dei due motivi si è verificato.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – PIN corretto dopo un errore

**a) Input** – 1234 (formato errato), 11111 (errato), 27183 (corretto)

**b) Output** – "Formato non valido", "PIN errato. Tentativi rimasti: 2",
"PIN corretto. Pagamento autorizzato."

**c) Variabili di supporto** – `tentativi`, `pin_corretto`

**d) Vincoli** – il formato errato non incrementa `tentativi`

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Porre `tentativi = 0` e `pin_corretto = 0`.
2. Finché il PIN non è corretto e i tentativi sono meno di 3:
   a. leggere il PIN;
   b. se non è tra 10000 e 99999, segnalare il formato errato;
   c. altrimenti incrementare `tentativi`; se il PIN coincide porre
      `pin_corretto = 1`, altrimenti stampare i tentativi rimasti.
3. Se `pin_corretto` vale 1 autorizzare il pagamento, altrimenti bloccare
   la carta.

### Caso d'uso 2 – Tre errori

**a) Input** – 11111, 22222, 33333

**b) Output** – due messaggi di PIN errato con i tentativi rimasti, poi
"Carta BLOCCATA: troppi tentativi errati."

**c) Variabili di supporto** – come nel caso 1

**d) Vincoli** – il ciclo termina perché `tentativi` raggiunge 3

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – PIN corretto al terzo tentativo

**a) Input** – 11111, 22222, 27183

**b) Output** – "PIN corretto. Pagamento autorizzato."

**c) Variabili di supporto** – `pin_corretto`

**d) Vincoli** – al termine `tentativi` vale 3 come nel caso 2: per questo
l'esito si decide guardando il flag e non il numero di tentativi

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.
