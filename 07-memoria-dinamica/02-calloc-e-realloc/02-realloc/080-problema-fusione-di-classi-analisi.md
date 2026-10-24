# Analisi – 080-problema-fusione-di-classi.c

## 1. Problema

La 4A e la 4B vengono accorpate. Il programma legge i due elenchi in
ordine alfabetico, ingrandisce con `realloc` il blocco della 4A fino a
contenere anche la 4B e fonde i due elenchi partendo dal fondo, senza un
terzo array e senza ordinare da capo.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| per ogni classe | numero e cognomi | Numero di studenti (1-30) seguito dai cognomi in ordine alfabetico |

### Output

- `Blocco della 4A: N studenti, B byte`.
- `Blocco ingrandito: T studenti, B' byte` e la nuova 4A con la classe di
  provenienza.
- `X non e' in ordine dopo Y` ed `Elenco della 4X non valido.`;
  `Memoria insufficiente.`

### Vincoli

- `leggi_classe` riceve `Studente **` per allocare e restituire il blocco
  al chiamante.
- `fondi`: `realloc(*a, (n_a + n_b) * sizeof *tmp)` in un temporaneo;
  fusione dal fondo con tre indici (i sulla 4A, j sulla 4B, k sulla
  destinazione): gli elementi della 4A non ancora copiati non vengono mai
  sovrascritti.
- A parità di cognome viene prima lo studente della 4A.
- I due blocchi si liberano alla fine.

### Assunzioni

- I cognomi sono una parola e si confrontano con `strcmp` (maiuscole
  prima delle minuscole).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Studente` | `typedef struct { char cognome[20]; char classe[4]; } Studente;` | Uno studente con la classe di provenienza |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `quarta_a`, `quarta_b` | `Studente *` | I due blocchi |
| `n_a`, `n_b` | `int` | Dimensioni |

| Funzione | Compito |
|----------|---------|
| `leggi_classe(elenco, n, classe)` | Alloca e legge una classe controllando l'ordine |
| `fondi(a, n_a, b, n_b)` | Ingrandisce la prima e vi fonde la seconda |

### Algoritmo in linguaggio naturale

1. Leggere le due classi; se una non è valida fermarsi.
2. Stampare la dimensione del blocco della 4A, fondere, stampare la nuova
   dimensione e l'elenco.
3. Liberare i blocchi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Fusione

- **Input:** `3 Bianchi Gallo Rossi`, `4 Amato Ferri Neri Villa`
- **Valori intermedi attesi:** `Studente` di 24 byte: 72 byte, poi 168.
- **Output atteso:**
  ```
  Blocco della 4A: 3 studenti, 72 byte
  Blocco ingrandito: 7 studenti, 168 byte

  Nuova 4A:
     1. Amato        (da 4B)
     2. Bianchi      (da 4A)
     3. Ferri        (da 4B)
     4. Gallo        (da 4A)
     5. Neri         (da 4B)
     6. Rossi        (da 4A)
     7. Villa        (da 4B)
  ```

### Test 2 – Elenco non in ordine

- **Input:** `3 Rossi Bianchi Gallo`
- **Output atteso:**
  ```
    Bianchi non e' in ordine dopo Rossi
  Elenco della 4A non valido.
  ```
