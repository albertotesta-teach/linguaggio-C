# Analisi – 080-problema-distanze-citta.c

## 1. Problema

Una tabella a doppia entrata riporta le distanze stradali tra 6 città.
Il programma deve verificare che la tabella sia coerente (diagonale nulla e
simmetria), trovare per ogni città la più vicina, la coppia più lontana e la
lunghezza di un itinerario indicato come sequenza di città.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `distanze` | `int[][]` | 6 × 6 | Km tra la città riga e la città colonna |
| `citta` | `char[][]` | 6 × 14 | Nomi: valgono sia per le righe sia per le colonne |
| `itinerario` | `int[]` | 5 | Indici delle città nell'ordine di visita |
| `coerente` | `int` (0/1) | — | Esito della verifica |
| `piu_vicina` | `int` | — | Colonna del minimo nella riga corrente |
| `i_max`, `j_max` | `int` | — | Coppia più lontana |
| `km_totali` | `int` | — | Lunghezza dell'itinerario |

In una matrice quadrata di relazioni tra gli stessi elementi, un solo array
di nomi descrive sia righe sia colonne.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Verifica della tabella

**a) Input** – `distanze`

**b) Output** – "Diagonale nulla e simmetria: verificate", oppure i messaggi
di errore con le coppie non simmetriche

**c) Variabili di supporto** – `coerente`

**d) Vincoli** – la simmetria si controlla solo per j > i

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni i: controllare `[i][i] == 0`;
per ogni j > i controllare `[i][j] == [j][i]`.

### Caso d'uso 2 – Città più vicina e coppia più lontana

**a) Input** – `distanze`, `citta`

**b) Output** – per ogni città la più vicina (es. Milano → Pavia 38 km);
"Coppia piu' lontana: Genova - Torino (170 km)"

**c) Variabili di supporto** – `piu_vicina`, `i_max`, `j_max`

**d) Vincoli** – il minimo di riga esclude la diagonale: l'ipotesi iniziale è
una colonna diversa da i; la coppia più lontana si cerca sopra la diagonale

**e) Assunzioni** – in caso di parità vale la prima trovata

**f) Algoritmo in linguaggio naturale**
1. Per ogni riga: ipotesi `piu_vicina` = 1 se i = 0, altrimenti 0; per ogni
   j ≠ i, se la distanza è minore aggiornare.
2. Per i < j: se la distanza supera quella di (`i_max`, `j_max`), aggiornare.

### Caso d'uso 3 – Lunghezza di un itinerario

**a) Input** – `itinerario` = Alessandria, Pavia, Milano, Asti, Torino

**b) Output** – i quattro tratti e "Totale: 286 km"

**c) Variabili di supporto** – `km_totali`

**d) Vincoli** – un itinerario di 5 tappe ha 4 tratti: il ciclo va fino a `TAPPE - 1`

**e) Assunzioni** – gli indici dell'itinerario sono validi

**f) Algoritmo in linguaggio naturale** – per ogni t da 0 a TAPPE - 2 sommare
`distanze[itinerario[t]][itinerario[t + 1]]`.
