# Analisi – 070-problema-magazzino-del-laboratorio.c

## 1. Problema

Il tecnico del laboratorio di elettronica tiene il conto del materiale:
ogni articolo ha quantità e scorta minima. Il magazzino è un vettore
dinamico di `Articolo`; carico e scarico modificano l'articolo tramite il
puntatore restituito da `trova`. L'elenco da riordinare è un secondo
vettore, creato da `sotto_scorta` con le copie degli articoli sotto la
scorta: una fotografia del momento, distrutta dopo la stampa.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `N nome quantita scorta` nuovo articolo, `C nome q` carico, `S nome q` scarico, `R` riordino, `E` elenco, `Q` fine (anche minuscoli) |

### Output

- `nuovo articolo: nome`, `nome esiste gia'.`, `Dati non validi.`
- `nome: disponibili Q` (con `(sotto scorta)` dopo uno scarico),
  `nome: disponibili solo Q`,
  `Articolo inesistente o quantita' non valida.`
- `R`: `Da riordinare: N` con la tabella, oppure `Niente da riordinare.`
- `E`: la tabella di tutti gli articoli.
- `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- Vettore `{Articolo *dati; int n; int capacita;}` con capacità iniziale 2
  e raddoppio; il `main` usa solo le funzioni del magazzino.
- Il puntatore di `trova` si usa subito, prima di altre aggiunte.
- Sotto scorta: quantità strettamente minore della scorta.
- Il vettore del riordino contiene copie: modificarlo non cambia il
  magazzino; si distrugge subito dopo la stampa.
- Quantità e scorta non negative; carico e scarico positivi; lo scarico
  non può superare la disponibilità.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Il nome dell'articolo è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Articolo` | `typedef struct { char nome[20]; int quantita; int scorta; } Articolo;` | Un articolo |
| `Magazzino` | `typedef struct { Articolo *dati; int n; int capacita; } Magazzino;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `magazzino`, `riordino` | `Magazzino *` | Magazzino e fotografia del riordino |
| `p` | `Articolo *` | Articolo da modificare |

| Funzione | Compito |
|----------|---------|
| `crea_magazzino`, `distruggi_magazzino` | Allocazione e liberazione |
| `aggiungi`, `lunghezza`, `elemento`, `trova` | Uso del vettore |
| `sotto_scorta(m)` | Nuovo vettore con le copie sotto scorta |
| `stampa(m)` | Tabella degli articoli |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; eseguire
   nuovo articolo, carico, scarico, riordino (crea, stampa, distruggi) o
   elenco; scartare il resto della riga.
2. Distruggere il magazzino.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Movimenti e riordino

- **Input:** `N resistenze 100 50`, `n led 20 30`, `N breadboard 5 5`,
  `N led 1 1`, `N cavi x 3`, `E`, `S resistenze 60`, `S led 25`,
  `C led 15`, `s breadboard 1`, `C diodi 3`, `R extra`, `E`, `X`, `Q`
- **Output atteso:**
  ```
    nuovo articolo: resistenze
    nuovo articolo: led
    nuovo articolo: breadboard
    led esiste gia'.
    Dati non validi.
    Articolo         Quantita  Scorta
    resistenze            100      50
    led                    20      30
    breadboard              5       5
    resistenze: disponibili 40  (sotto scorta)
    led: disponibili solo 20
    led: disponibili 35
    breadboard: disponibili 4  (sotto scorta)
    Articolo inesistente o quantita' non valida.
    Da riordinare: 2
    Articolo         Quantita  Scorta
    resistenze             40      50
    breadboard              4       5
    Articolo         Quantita  Scorta
    resistenze             40      50
    led                    35      30
    breadboard              4       5
    Comando sconosciuto.
  ```
