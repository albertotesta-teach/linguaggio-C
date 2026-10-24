# Analisi – 040-problema-registro-dei-ritardi.c

## 1. Problema

Il collaboratore all'ingresso registra ogni studente che entra in ritardo
con data, nome e minuti. Il numero di ingressi dell'anno non si conosce:
le registrazioni vanno in un vettore dinamico di struct `Ritardo`, che
parte da 4 posti e raddoppia quando è pieno. Il programma legge le righe
`gg/mm nome minuti` fino a `FINE` e stampa gli ingressi per mese (da
settembre a giugno), la data con più ritardi e gli studenti con almeno 3
ritardi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| riga | testo | `gg/mm nome minuti`; `FINE` termina |

### Output

- `riga non valida` per ogni riga scartata.
- `Ingressi in ritardo: N (capacita' C)`.
- Gli ingressi per mese da settembre a giugno.
- `Data con piu' ritardi: gg/mm (K)` (se ci sono ingressi).
- `Avviso alla famiglia (almeno 3 ritardi):` con gli studenti.

### Vincoli

- Vettore `{Ritardo *dati; int n; int capacita;}`: capacità iniziale 4,
  raddoppio con `realloc` in un temporaneo quando `n == capacita`.
- Il `main` usa il vettore solo con le sue funzioni (`aggiungi`,
  `lunghezza`, `capacita`, `elemento`), mai con i campi.
- Data valida: mese di scuola (luglio e agosto esclusi), giorno esistente
  (febbraio fino al 29); minuti positivi.
- A parità vale la prima data con il massimo; ogni studente compare una
  volta sola nell'avviso (alla sua prima registrazione).
- Una riga per ritardo: il resto viene scartato. A fine input il
  programma termina come con `FINE`.

### Assunzioni

- Il nome è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Ritardo` | `typedef struct { int giorno; int mese; char studente[20]; int minuti; } Ritardo;` | Un ingresso in ritardo |
| `Registro` | `typedef struct { Ritardo *dati; int n; int capacita; } Registro;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `registro` | `Registro *` | Il vettore |
| `per_mese` | `int[13]` | Ingressi per mese |
| `ordine` | `const int[10]` | Mesi da settembre a giugno |
| `massimo`, `peggiore` | `int` | Data con più ritardi |

| Funzione | Compito |
|----------|---------|
| `crea_registro`, `distruggi_registro` | Allocazione e liberazione |
| `aggiungi(r, nuovo)` | Aggiunge in fondo, raddoppiando se serve |
| `lunghezza`, `capacita`, `elemento` | Accesso al vettore |
| `data_valida(giorno, mese)` | Controllo della data |
| `conta_studente(r, nome, fino_a)` | Ritardi dello studente tra i primi `fino_a` |
| `conta_data(r, giorno, mese)` | Ritardi in una data |

### Algoritmo in linguaggio naturale

1. Creare il registro.
2. Leggere le righe fino a `FINE`: controllarle e aggiungerle.
3. Contare gli ingressi per mese e trovare la data con più ritardi.
4. Stampare i mesi, la data e gli studenti con almeno 3 ritardi.
5. Distruggere il registro.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Un trimestre

- **Input:** `02/10 Rossi 10`, `02/10 Bianchi 5`, `15/10 Rossi 7`,
  `31/11 Verdi 5`, `20/11 Rossi 12 extra`, `03/12 Verdi 0`,
  `10/07 Neri 5`, `12/01 Bianchi 8`, `02/10 Verdi 3`, `xx`,
  `20/03 Bianchi 4`, `FINE`
- **Valori intermedi attesi:** 7 ingressi validi: la capacità passa da 4
  a 8.
- **Output atteso:**
  ```
  Ritardi (gg/mm nome minuti, FINE per terminare):
    riga non valida
    riga non valida
    riga non valida
    riga non valida

  Ingressi in ritardo: 7 (capacita' 8)
    set  0
    ott  4
    nov  1
    dic  0
    gen  1
    feb  0
    mar  1
    apr  0
    mag  0
    giu  0
  Data con piu' ritardi: 02/10 (3)
  Avviso alla famiglia (almeno 3 ritardi):
    Rossi: 3 ritardi
    Bianchi: 3 ritardi
  ```
