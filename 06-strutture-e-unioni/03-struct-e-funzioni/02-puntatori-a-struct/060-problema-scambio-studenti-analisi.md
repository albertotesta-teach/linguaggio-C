# Analisi – 060-problema-scambio-studenti.c

## 1. Problema

Due studenti chiedono di passare l'uno nella sezione dell'altro.
`scambia_studenti` riceve gli indirizzi delle due schede e scambia i nomi,
lasciando ogni scheda nella sua sezione; lo scambio si fa solo se la
seconda lingua è la stessa. Una versione che riceve le struct per valore
mostra che scambiare le copie non cambia nulla.

## 2. Analisi

### Input

Nessun input da tastiera: le schede sono nel sorgente.

| Scheda | Nome | Sezione | Seconda lingua |
|--------|------|---------|----------------|
| `prima` | Lorenzo Fabbri | 1A | 2 (tedesco) |
| `seconda` | Aurora Neri | 1B | 2 (tedesco) |
| `terza` | Mattia Conte | 1B | 1 (francese) |

### Output

- Le schede prima dello scambio, dopo `scambia_copie` (invariate, con la
  riga stampata dentro la funzione) e dopo `scambia_studenti`.
- `Scambio con Mattia Conte rifiutato: seconda lingua diversa.`

### Vincoli

- `scambia_studenti(Scheda *a, Scheda *b)` modifica le schede del
  chiamante; restituisce 1 se lo scambio è possibile.
- Le stringhe si scambiano con `strcpy` e un array di appoggio.
- `scambia_copie(Scheda a, Scheda b)` lavora su copie locali: le schede
  del chiamante non cambiano.
- Lingua 1 = francese, altrimenti tedesco.

### Assunzioni

- I nomi stanno in 23 caratteri.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Scheda` | `typedef struct { char nome[24]; char sezione[4]; int lingua; } Scheda;` | Uno studente nella sua sezione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `prima`, `seconda`, `terza` | `Scheda` | Le schede |
| `nome` (in `scambia_studenti`) | `char[24]` | Appoggio per lo scambio |
| `temp` (in `scambia_copie`) | `Scheda` | Appoggio per lo scambio delle copie |

| Funzione | Compito |
|----------|---------|
| `scambia_studenti(a, b)` | Scambia i nomi se la lingua coincide |
| `scambia_copie(a, b)` | Versione sbagliata per valore |
| `stampa(s)` | Stampa sezione, nome e lingua |

### Algoritmo in linguaggio naturale

1. Stampare `prima` e `seconda`.
2. Chiamare `scambia_copie` e ristampare: nessun cambiamento.
3. Chiamare `scambia_studenti(&prima, &seconda)`: se riesce, ristampare.
4. Chiamare `scambia_studenti(&prima, &terza)`: se non riesce, stampare
   il rifiuto.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** differenza tra passaggio per valore e per
  indirizzo, rifiuto per lingua diversa.
- **Input:** nessuno.
- **Output atteso:**
  ```
  Prima dello scambio:
    1A: Lorenzo Fabbri   tedesco
    1B: Aurora Neri      tedesco
    (dentro scambia_copie la copia a contiene Aurora Neri)

  Dopo scambia_copie (per valore): nessun cambiamento
    1A: Lorenzo Fabbri   tedesco
    1B: Aurora Neri      tedesco

  Dopo scambia_studenti(&prima, &seconda):
    1A: Aurora Neri      tedesco
    1B: Lorenzo Fabbri   tedesco

  Scambio con Mattia Conte rifiutato: seconda lingua diversa.
  ```

### Test 2 – Stessa lingua anche per la terza scheda

- **Procedura:** dare a Mattia Conte la lingua 2.
- **Output atteso:** l'ultima riga non compare (lo scambio riesce senza
  messaggi).
