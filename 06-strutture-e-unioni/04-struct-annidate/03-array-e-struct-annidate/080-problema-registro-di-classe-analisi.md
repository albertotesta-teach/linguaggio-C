# Analisi – 080-problema-registro-di-classe.c

## 1. Problema

Il registro elettronico di una classe contiene gli studenti, ognuno con i
suoi voti; ogni voto ha valore, data e materia. Il programma registra
nuovi voti e calcola le medie per materia o per periodo con una sola
funzione a due filtri facoltativi: un puntatore `NULL` significa "nessun
filtro". Il `Registro` contiene un array di `Studente`, che contiene un
array di `Voto`, che contiene una `Data`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `V studente materia voto gg/mm/aaaa` nuovo voto, `M materia` medie per materia, `P gg/mm/aaaa gg/mm/aaaa` medie in un periodo, `Q` fine (anche minuscoli) |
| `registro` | `Registro` | Classe 3B: Bassi, Conte, Dini con voti di matematica e inglese (nel sorgente) |

Voti iniziali: Bassi 7 Mat (2/10), 8 Ing (15/10), 6 Mat (20/11); Conte 5
Mat (2/10), 6 Ing (15/10), 7 Mat (20/11), 7 Ing (3/12); Dini 9 Mat (2/10),
8 Ing (3/12). Anno 2025.

### Output

- `V`: `Registrato: <studente>, <materia> <voto>`, oppure
  `X non e' nella 3B.`, `Voto non valido.`, `Data non valida.`,
  `Spazio esaurito per i voti di X.`, `Dati non validi.`
- `M`/`P`: per ogni studente la media con due decimali e il numero di voti
  (`voto`/`voti`), oppure `nessun voto`; `Periodo non valido.`
- `Comando sconosciuto.`

### Vincoli

- `media(s, materia, da, a, &quanti)`: ogni filtro `NULL` è ignorato; il
  periodo comprende gli estremi.
- Le date si confrontano come numero `aaaammgg`.
- Voto da 1 a 10; al massimo 8 voti per studente.
- Data del voto: mese 1-12, giorno 1-31.
- Un comando per riga (il resto viene scartato); i dati non validi non
  interrompono il programma. A fine input termina come con `Q`.

### Assunzioni

- Le materie si scrivono sempre con la stessa grafia (`strcmp`).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Data` | `typedef struct { int giorno; int mese; int anno; } Data;` | Data del voto |
| `Voto` | `typedef struct { int valore; Data data; char materia[12]; } Voto;` | Un voto |
| `Studente` | `typedef struct { char nome[12]; Voto voti[8]; int n_voti; } Studente;` | Studente con i voti |
| `Registro` | `typedef struct { char classe[4]; Studente studenti[4]; int n_studenti; } Registro;` | Il registro della classe |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `studente` | `Studente *` | Studente trovato |
| `nuovo` | `Voto` | Voto letto |
| `da`, `a` | `Data` | Estremi del periodo |

| Funzione | Compito |
|----------|---------|
| `confronta_date(a, b)` | Negativo, zero o positivo |
| `cerca(r, nome)` | Puntatore allo studente, o `NULL` |
| `aggiungi_voto(s, v)` | Aggiunge il voto se c'è spazio |
| `media(s, materia, da, a, quanti)` | Media con i filtri facoltativi |
| `stampa_medie(r, materia, da, a)` | Medie di tutti gli studenti |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `V`: leggere i dati, cercare lo studente, controllare voto e data,
      aggiungere il voto;
   3. `M`: medie con filtro sulla materia (`NULL`, `NULL` per il periodo);
   4. `P`: se il periodo è corretto, medie con filtro sulle date (`NULL`
      per la materia);
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Medie e nuovi voti

- **Cosa si verifica:** i due filtri, gli estremi del periodo, gli errori
  e l'effetto di un voto aggiunto.
- **Input:** `M Matematica`, `m Inglese`, `P 1/10/2025 31/10/2025`,
  `P 1/12/2025 31/12/2025`, `P 1/12/2025 1/10/2025`,
  `V Dini Inglese 6 10/12/2025`, `V Rossi Inglese 6 10/12/2025`,
  `V Dini Inglese 11 10/12/2025`, `V Dini Inglese 6 40/12/2025`,
  `V Dini Inglese sei`, `M Fisica`, `X`, `M Inglese`, `Q`
- **Output atteso:**
  ```
    Bassi    6.50 (2 voti)
    Conte    6.00 (2 voti)
    Dini     9.00 (1 voto)
    Bassi    8.00 (1 voto)
    Conte    6.50 (2 voti)
    Dini     8.00 (1 voto)
    Bassi    7.50 (2 voti)
    Conte    5.50 (2 voti)
    Dini     9.00 (1 voto)
    Bassi    nessun voto
    Conte    7.00 (1 voto)
    Dini     8.00 (1 voto)
    Periodo non valido.
    Registrato: Dini, Inglese 6
    Rossi non e' nella 3B.
    Voto non valido.
    Data non valida.
    Dati non validi.
    Bassi    nessun voto
    Conte    nessun voto
    Dini     nessun voto
    Comando sconosciuto.
    Bassi    8.00 (1 voto)
    Conte    6.50 (2 voti)
    Dini     7.00 (2 voti)
  ```
