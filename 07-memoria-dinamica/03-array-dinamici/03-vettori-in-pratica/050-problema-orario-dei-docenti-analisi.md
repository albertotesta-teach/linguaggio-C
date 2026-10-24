# Analisi – 050-problema-orario-dei-docenti.c

## 1. Problema

Il coordinatore cerca le ore in cui tutti i docenti del consiglio di
classe sono liberi per una riunione. Le lezioni arrivano come `docente
giorno ora`. Ogni docente ha un proprio vettore dinamico di ore occupate
(codice giorno × 10 + ora) che cresce indipendentemente dagli altri; un'ora
è libera per tutti se nessun vettore la contiene. Anche il consiglio è un
vettore dinamico di docenti.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| lezioni | testo | `docente giorno ora` con giorno `lun`...`ven` e ora 1-6; `FINE` termina |

### Output

- `lezione non valida per nome`, `nome giorno ora gia' inserita`.
- `Carico dei docenti:` con ore e capacità del vettore di ognuno.
- `Ore libere per tutti:` giorno per giorno (o `nessuna`) e il totale su
  30.
- `Nessuna lezione inserita.`, `Memoria insufficiente.`

### Vincoli

- Due vettori annidati: `Consiglio` contiene `Docente`, ognuno con un
  `Ore *` creato da `crea_ore(4)` e raddoppiato quando serve.
- `aggiungi_docente` crea prima il vettore delle ore; se il consiglio non
  può crescere lo distrugge e restituisce −1.
- `distruggi_consiglio` libera i vettori di ogni docente, poi l'array,
  poi la struct.
- Il `main` usa solo le funzioni dei due vettori.
- I giorni si scrivono in minuscolo.

### Assunzioni

- I nomi dei docenti sono una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Ore` | `typedef struct { int *dati; int n; int capacita; } Ore;` | Ore occupate di un docente |
| `Docente` | `typedef struct { char nome[20]; Ore *ore; } Docente;` | Un docente |
| `Consiglio` | `typedef struct { Docente *dati; int n; int capacita; } Consiglio;` | Vettore dei docenti |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `consiglio` | `Consiglio *` | I docenti |
| `indice`, `g` | `int` | Docente e giorno della lezione |
| `libere`, `libere_giorno` | `int` | Contatori |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `crea_ore`, `aggiungi`, `lunghezza`, `capacita`, `contiene`, `distruggi_ore` | Vettore delle ore |
| `crea_consiglio`, `cerca_docente`, `aggiungi_docente`, `numero_docenti`, `nome_docente`, `ore_docente`, `distruggi_consiglio` | Vettore dei docenti |
| `numero_giorno(giorno)` | `lun`...`ven` → 1-5, 0 se non valido |
| `libera_per_tutti(c, codice)` | 1 se nessun docente ha lezione |

### Algoritmo in linguaggio naturale

1. Leggere le lezioni fino a `FINE`: controllarle; trovare o aggiungere
   il docente; aggiungere il codice dell'ora se non c'è già.
2. Stampare il carico di ogni docente.
3. Per ogni giorno e ora controllare se è libera per tutti e stamparla;
   stampare il totale.
4. Distruggere il consiglio.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Tre docenti

- **Input:** `Rossi lun 1`, `Rossi lun 2`, `Bianchi lun 1`,
  `Bianchi mar 3`, `Rossi mar 4`, `Verdi mer 1`, `Verdi sab 2`,
  `Verdi mer 9`, `Rossi lun 2`, `Rossi gio 1`, `Rossi gio 2`,
  `Rossi ven 6`, `Neri lun x`, `FINE`
- **Valori intermedi attesi:** Rossi ha 6 ore: il suo vettore passa da 4 a
  8; 8 ore distinte occupate, 22 libere.
- **Output atteso:**
  ```
  Lezioni: docente giorno ora (FINE per terminare)
    lezione non valida per Verdi
    lezione non valida per Verdi
    Rossi lun 2 gia' inserita
    lezione non valida per Neri

  Carico dei docenti:
    Rossi      ore  6  (capacita del vettore 8)
    Bianchi    ore  2  (capacita del vettore 4)
    Verdi      ore  1  (capacita del vettore 4)

  Ore libere per tutti:
    lun: 3 4 5 6
    mar: 1 2 5 6
    mer: 2 3 4 5 6
    gio: 3 4 5 6
    ven: 1 2 3 4 5
  Totale ore libere comuni: 22 su 30
  ```

### Test 2 – Nessuna lezione

- **Input:** `FINE`
- **Output atteso:** `Nessuna lezione inserita.`
