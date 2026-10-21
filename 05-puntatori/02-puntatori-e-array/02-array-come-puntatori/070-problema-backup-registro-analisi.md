# Analisi – 070-problema-backup-registro.c

## 1. Problema

Prima che il docente corregga i voti di una verifica, il registro ne fa una
copia di sicurezza. Il docente inserisce le correzioni (numero dello
studente e nuovo voto) fino a `0 0`; il programma mostra i voti cambiati
rispetto alla copia e chiede conferma. Senza conferma i voti si ripristinano
dalla copia.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `studente`, `voto` | `int` | Correzione: numero dello studente (1-8) e nuovo voto (1-10); `0 0` per finire |
| `risposta` | `char` | Conferma `S`/`N` |
| `nomi`, `voti` | `char[8][12]`, `int[8]` | Registro iniziale (nel sorgente): voti 6, 7, 5, 8, 4, 9, 6, 7 |

### Output

- Il registro iniziale.
- Per ogni correzione non valida: `Studente inesistente.` oppure
  `Il voto deve essere tra 1 e 10.`
- Le modifiche rispetto alla copia (`nome  vecchio -> nuovo`) oppure
  `Nessuna modifica.`; se ci sono modifiche la domanda di conferma e
  `Modifiche confermate.` oppure `Modifiche annullate: voti ripristinati
  dalla copia.`
- Il registro finale.

### Vincoli

- `copia_blocco` copia `n` interi con due puntatori che avanzano insieme;
  la stessa funzione fa il backup (`voti` → `backup`) e il ripristino
  (`backup` → `voti`), con gli argomenti scambiati.
- `mostra_differenze` scorre i due array con due puntatori in parallelo; il
  nome dello studente si ricava dall'indice `a − attuali`.
- Un indice fuori dall'array non si usa mai: lo studente deve essere tra 1 e 8.
- Più correzioni dello stesso studente: vale l'ultima, e il confronto è
  sempre con la copia iniziale.
- Una correzione che non contiene due numeri è uno studente inesistente
  (la riga si scarta); a fine input l'inserimento termina come con `0 0`
  e, se serve la conferma, la risposta mancante vale `N`.
- Ogni risposta diversa da `S`/`s` annulla le modifiche.

### Assunzioni

- I voti sono interi da 1 a 10.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `backup` | `int[8]` | Copia di sicurezza |
| `cambiati` | `int` | Numero di voti modificati |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `copia_blocco(dest, sorgente, n)` | Copia `n` interi con due puntatori |
| `mostra_differenze(attuali, backup, n, nomi)` | Stampa e conta i voti cambiati |
| `stampa_registro(voti, n, nomi)` | Elenco numerato dei voti |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Copiare `voti` in `backup` e stampare il registro.
2. Finché lo studente non è 0: leggere studente e voto (a fine input
   porre 0; se non sono due numeri scartare la riga e considerare lo
   studente inesistente); controllare studente e voto e, se validi,
   scrivere il voto.
3. Mostrare le differenze rispetto alla copia; se ce ne sono, chiedere
   conferma: senza `S`/`s` ripristinare i voti dalla copia.
4. Stampare il registro finale.

## 3. Casi di test

Nell'output le correzioni inserite non compaiono (input da pipe).

### Test 1 – Correzioni confermate

- **Cosa si verifica:** la seconda correzione dello studente 3 sostituisce
  la prima; il confronto è con la copia.
- **Input:** `3 8`, `6 5`, `3 7`, `0 0`, `S`
- **Output atteso:**
  ```
  === MODIFICHE RISPETTO ALLA COPIA ===
    Ferrari     5 ->  7
    Ricci       9 ->  5
  Voti modificati: 2. Confermi? (S/N): Modifiche confermate.
  ```
  e nel registro finale Ferrari 7 e Ricci 5.

### Test 2 – Correzioni annullate

- **Input:** `1 4`, `0 0`, `N`
- **Output atteso:**
  ```
    Bianchi     6 ->  4
  Voti modificati: 1. Confermi? (S/N): Modifiche annullate: voti ripristinati dalla copia.
  ```
  e il registro finale uguale a quello iniziale.

### Test 3 – Correzioni non valide

- **Input:** `9 6`, `2 11`, `abc`, `0 0`
- **Output atteso:**
  ```
    Studente inesistente.
    Il voto deve essere tra 1 e 10.
    Studente inesistente.
  ...
    Nessuna modifica.
  ```

### Test 4 – Fine dell'input

- **Cosa si verifica:** senza `0 0` e senza risposta le modifiche vengono
  annullate.
- **Input:** `2 9`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
  ```
    Colombo     7 ->  9
  Voti modificati: 1. Confermi? (S/N): Modifiche annullate: voti ripristinati dalla copia.
  ```
