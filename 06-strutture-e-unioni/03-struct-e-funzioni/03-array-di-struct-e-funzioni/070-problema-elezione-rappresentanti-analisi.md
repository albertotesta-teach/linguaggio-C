# Analisi – 070-problema-elezione-rappresentanti.c

## 1. Problema

Lo spoglio delle schede per i rappresentanti d'istituto conta le schede
valide, bianche e nulle. Ogni voto valido incrementa il campo `voti` del
candidato trovato con un puntatore. Una funzione trova i due più votati
senza ordinare l'array di struct `Candidato`; se il secondo posto è
conteso serve il ballottaggio.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `scheda` | `int` | Numero del candidato votato; 0 scheda bianca; −1 fine dello spoglio |
| lista | nel sorgente | 1 Rossi Elena 4A, 2 Marchetti Luca 5B, 3 Sanna Giulia 3C, 4 Ferri Omar 4B, 5 Leone Chiara 5A |

### Output

- `Inserimento non valido, ripetere.` per una scheda non numerica.
- `Schede valide V, bianche B, nulle N` e la lista con i voti.
- `Primo eletto: ...` e `Secondo eletto: ...`, oppure
  `Secondo posto: X e un altro / altri K a pari voti (V): serve il
  ballottaggio`.
- Senza voti validi: `Nessun voto valido: nessun eletto.`

### Vincoli

- Un numero che non corrisponde a un candidato rende la scheda nulla.
- `cerca` restituisce l'indirizzo del candidato: il voto si registra con
  `votato->voti++`.
- `classifica_primi` restituisce i due indici nei parametri di uscita; a
  parità vale l'ordine di lista.
- Pari merito: altri candidati (oltre a primo e secondo) con gli stessi
  voti del secondo.
- A fine input lo spoglio termina come con −1.

### Assunzioni

- I candidati sono almeno due.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Candidato` | `typedef struct { int numero; char nome[20]; char classe[4]; int voti; } Candidato;` | Un candidato con i suoi voti |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `lista` | `Candidato[5]` | Array di struct |
| `votato` | `Candidato *` | Candidato trovato |
| `valide`, `bianche`, `nulle` | `int` | Contatori delle schede |
| `primo`, `secondo` | `int` | Indici dei più votati |
| `pari_merito` | `int` | Candidati a pari voti con il secondo |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `cerca(c, n, numero)` | Puntatore al candidato, `NULL` se il numero non esiste |
| `classifica_primi(c, n, &primo, &secondo)` | Indici dei due più votati |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché la scheda non è −1:
   1. leggere la scheda (fine input → −1; testo → ripetere);
   2. 0: bianca; altrimenti cercare il candidato: se non esiste nulla,
      altrimenti un voto in più e una valida.
2. Stampare i conteggi e la lista.
3. Se non ci sono voti validi, nessun eletto; altrimenti trovare primo e
   secondo, contare i pari merito con il secondo e stampare gli eletti o
   il ballottaggio.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Spoglio regolare

- **Cosa si verifica:** schede bianche, nulle, non numeriche e due eletti.
- **Input:** `1`, `2`, `1`, `3`, `0`, `7`, `1`, `abc`, `4`, `2`, `-1`
- **Output atteso:**
  ```
    Inserimento non valido, ripetere.

  Schede valide 7, bianche 1, nulle 1
    1. Rossi Elena     4A  voti  3
    2. Marchetti Luca  5B  voti  2
    3. Sanna Giulia    3C  voti  1
    4. Ferri Omar      4B  voti  1
    5. Leone Chiara    5A  voti  0

  Primo eletto:   Rossi Elena (voti 3)
  Secondo eletto: Marchetti Luca (voti 2)
  ```

### Test 2 – Ballottaggio con un altro candidato

- **Input:** `1`, `2`, `3`, `1`, `2`, `3`, poi fine input
- **Output atteso:** `Secondo posto: Marchetti Luca e un altro a pari voti
  (2): serve il ballottaggio`.

### Test 3 – Ballottaggio con più candidati

- **Input:** `1`, `1`, `2`, `3`, `4`, poi fine input
- **Output atteso:** `Secondo posto: Marchetti Luca e altri 2 a pari voti
  (1): serve il ballottaggio`.

### Test 4 – Nessun voto valido

- **Input:** `0`, `9`, `-1`
- **Output atteso:** `Schede valide 0, bianche 1, nulle 1` e
  `Nessun voto valido: nessun eletto.`
