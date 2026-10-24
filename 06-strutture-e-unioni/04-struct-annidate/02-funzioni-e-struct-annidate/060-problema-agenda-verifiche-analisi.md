# Analisi – 060-problema-agenda-verifiche.c

## 1. Problema

Il coordinatore tiene l'agenda delle verifiche scritte: una classe non può
avere due verifiche nello stesso giorno e le verifiche si fanno tra le
8:00 e le 13:00. Il comando S sposta una verifica: `sposta` modifica solo
`v->giorno` e `v->ora`, lasciando classe e materia. La struct `Verifica`
contiene una `Data` e un `Orario`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `E` elenco, `S n gg/mm/aaaa hh:mm` sposta, `C classe` verifiche di una classe, `Q` fine (anche minuscoli) |
| agenda | nel sorgente | 0: 3B Matematica 10/2; 1: 3B Inglese 12/2; 2: 3B Storia 13/2; 3: 4A Matematica 12/2; 4: 4A Fisica 16/2 (2026) |

### Output

- `E`: le verifiche numerate; `C`: le verifiche della classe.
- `S`: `Spostata: ...` oppure `La X ha gia' <materia> quel giorno.`,
  `Le verifiche si fanno tra le 8:00 e le 13:00.`, `Data non valida.`,
  `Verifica N inesistente.`, `Dati non validi.`
- `Comando sconosciuto.`

### Vincoli

- Ordine dei controlli: numero della verifica, data, orario, conflitto.
- Data valida: anno dal 2025, mese 1-12, giorno compatibile (bisestili
  compresi).
- Orario da 8:00 a 13:00 compresi, minuti 0-59.
- Conflitto: un'altra verifica (esclusa quella da spostare) della stessa
  classe nello stesso giorno.
- `sposta` assegna intere struct annidate (`v->giorno = *giorno`).
- Un comando per riga; i dati non validi non interrompono il programma. A
  fine input termina come con `Q`.

### Assunzioni

- I numeri delle verifiche partono da 0.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Data` | `typedef struct { int giorno; int mese; int anno; } Data;` | Una data |
| `Orario` | `typedef struct { int ore; int minuti; } Orario;` | Un orario |
| `Verifica` | `typedef struct { char classe[4]; char materia[12]; Data giorno; Orario ora; } Verifica;` | Una verifica |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `agenda` | `Verifica[5]` | L'agenda |
| `giorno`, `ora` | `Data`, `Orario` | Nuova collocazione |
| `n`, `altra` | `int` | Verifica da spostare, verifica in conflitto |

| Funzione | Compito |
|----------|---------|
| `data_valida(d)`, `orario_valido(o)` | Controlli |
| `stessa_data(a, b)` | Confronto campo per campo |
| `conflitto(v, n, escluso, classe, giorno)` | Indice della verifica in conflitto, o −1 |
| `sposta(v, giorno, ora)` | Aggiorna data e ora |
| `stampa(v)` | Riga della verifica |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `E`: stampare l'agenda numerata;
   3. `S`: leggere i dati e fare i controlli nell'ordine; se non c'è
      conflitto spostare e stampare;
   4. `C`: leggere la classe e stamparne le verifiche;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Spostamenti

- **Cosa si verifica:** conflitto, spostamento riuscito, orario, data e
  numero non validi, ricerca per classe.
- **Input:** `E`, `S 0 12/2/2026 9:00`, `s 0 11/2/2026 9:00`,
  `S 4 10/2/2026 13:30`, `S 4 30/2/2026 10:00`, `S 7 10/2/2026 10:00`,
  `S 4 abc`, `C 3B`, `c 4A`, `X`, `Q`
- **Output atteso** (dopo l'elenco):
  ```
    La 3B ha gia' Inglese quel giorno.
    Spostata: 3B  Matematica  11/02/2026  09:00
    Le verifiche si fanno tra le 8:00 e le 13:00.
    Data non valida.
    Verifica 7 inesistente.
    Dati non validi.
    3B  Matematica  11/02/2026  09:00
    3B  Inglese     12/02/2026  10:00
    3B  Storia      13/02/2026  11:00
    4A  Matematica  12/02/2026  09:00
    4A  Fisica      16/02/2026  08:00
    Comando sconosciuto.
  ```
