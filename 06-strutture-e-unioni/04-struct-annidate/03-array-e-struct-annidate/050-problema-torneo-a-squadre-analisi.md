# Analisi – 050-problema-torneo-a-squadre.c

## 1. Problema

Nel torneo di calcetto d'istituto ogni squadra ha la sua rosa. Il
programma registra i gol cercando prima la squadra e poi il giocatore (un
livello alla volta, con funzioni che restituiscono un puntatore), stampa
la rosa di una squadra e il capocannoniere, o tutti quelli a pari gol. Il
`Torneo` contiene un array di `Squadra`, che contiene un array di
`Giocatore`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `G squadra giocatore` gol, `R squadra` rosa, `C` capocannoniere, `Q` fine (anche minuscoli) |
| `nome_squadra`, `nome_giocatore` | `char[12]` | Nomi cercati |
| `torneo` | `Torneo` | Fulmini, Tigri, Squali, Aquile con 4 giocatori ciascuna (nel sorgente) |

### Output

- `G`: `Gol di X (squadra): N in tutto.`, oppure
  `Squadra X inesistente.`, `X non e' nella rosa della squadra Y.`,
  `Dati incompleti.`
- `R`: i giocatori con i gol e `Totale squadra: N gol`.
- `C`: `Capocannoniere con N gol:` seguito da tutti i giocatori con quel
  numero di gol.
- `Comando sconosciuto.`

### Vincoli

- `cerca_squadra` restituisce `&t->squadre[k]`, `cerca_giocatore`
  `&s->rosa[g]`: il gol si registra con `giocatore->gol++`.
- Il capocannoniere si trova in due passate: prima il massimo, poi chi lo
  raggiunge.
- Un comando per riga: il resto viene scartato. A fine input il programma
  termina come con `Q`.

### Assunzioni

- Comando e argomenti stanno sulla stessa riga (`scanf` cercherebbe un
  argomento mancante nella riga successiva).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Giocatore` | `typedef struct { char nome[12]; int gol; } Giocatore;` | Un giocatore |
| `Squadra` | `typedef struct { char nome[12]; Giocatore rosa[5]; int n_giocatori; } Squadra;` | Squadra con la rosa |
| `Torneo` | `typedef struct { Squadra squadre[4]; int n_squadre; } Torneo;` | Tutte le squadre |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `torneo` | `Torneo` | Dati del torneo |
| `squadra`, `giocatore` | `Squadra *`, `Giocatore *` | Elementi trovati |

| Funzione | Compito |
|----------|---------|
| `cerca_squadra(t, nome)` | Puntatore alla squadra, o `NULL` |
| `cerca_giocatore(s, nome)` | Puntatore al giocatore, o `NULL` |
| `gol_squadra(s)` | Somma dei gol della rosa |
| `stampa_rosa(s)` | Rosa con il totale |
| `capocannonieri(t)` | Massimo e giocatori che lo raggiungono |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `G`/`R`: leggere i nomi, cercare la squadra; con `R` stampare la
      rosa, con `G` cercare il giocatore e aggiungere il gol;
   3. `C`: stampare i capocannonieri;
   4. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Gol e capocannonieri

- **Cosa si verifica:** ricerca su due livelli, errori, pari merito.
- **Input:** `C`, `G Tigri Gallo`, `g Fulmini Bassi`, `G Fulmini Bassi`,
  `G Fulmini Neri`, `G Orsi Bassi`, `R Fulmini`, `C`, `X`, `Q`
- **Output atteso:**
  ```
    Capocannoniere con 3 gol: Fumo (Tigri)
    Gol di Gallo (Tigri): 2 in tutto.
    Gol di Bassi (Fulmini): 3 in tutto.
    Gol di Bassi (Fulmini): 4 in tutto.
    Neri non e' nella rosa della squadra Fulmini.
    Squadra Orsi inesistente.
    Fulmini
      Bassi    4 gol
      Conte    0 gol
      Dini     1 gol
      Elia     0 gol
    Totale squadra: 5 gol
    Capocannoniere con 4 gol: Bassi (Fulmini)
    Comando sconosciuto.
  ```

### Test 2 – Pari merito

- **Input:** `g Fulmini Bassi`, `C`, `Q`
- **Output atteso:** `Capocannoniere con 3 gol: Bassi (Fulmini) Fumo (Tigri)`.
