# Analisi – 040-problema-orario-settimanale.c

## 1. Problema

L'orario di ogni classe prima è una matrice di `Lezione` (5 giorni × 4
ore) dentro la struct `Classe`. Il programma stampa la griglia di una
classe, le lezioni settimanali di un docente in tutte le classi e i
conflitti tra le due classi: stesso docente o stessa aula nella stessa
ora.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `O classe` orario, `D docente` lezioni di un docente, `C` conflitti, `Q` fine (anche minuscoli) |
| `nome` | `char[10]` | Nome della classe o del docente |
| `prime` | `Classe[2]` | Orari di 1A e 1B (nel sorgente) |

### Output

- `O`: la griglia ore × giorni con le materie, oppure
  `Classe X inesistente.`
- `D`: una riga per lezione (giorno, ora, classe, aula, materia) e
  `<docente>: N ore settimanali`.
- `C`: una riga per conflitto e `Conflitti: N`.
- `Comando sconosciuto.`

### Vincoli

- Si accede a un campo con tre livelli: `c[k].orario[g][h].docente`.
- La griglia si stampa con una riga per ora e una colonna per giorno
  (l'inverso dell'ordine degli indici).
- Un conflitto è una cella con lo stesso docente o la stessa aula nelle
  due classi; se coincidono entrambi si contano due conflitti.
- I nomi si confrontano con `strcmp` (maiuscole e minuscole contano).
- Un comando per riga: il resto viene scartato. A fine input il programma
  termina come con `Q`.

### Assunzioni

- Comando e argomento stanno sulla stessa riga (`scanf` cercherebbe un
  argomento mancante nella riga successiva).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Lezione` | `typedef struct { char materia[12]; char docente[10]; char aula[8]; } Lezione;` | Una cella dell'orario |
| `Classe` | `typedef struct { char nome[4]; Lezione orario[5][4]; } Classe;` | Classe con la matrice dell'orario |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `prime` | `Classe[2]` | Le due classi |
| `classe` | `const Classe *` | Classe trovata |
| `ore`, `trovati` | `int` | Risultati di `D` e `C` |

| Funzione | Compito |
|----------|---------|
| `cerca_classe(c, n, nome)` | Puntatore alla classe, `NULL` se assente |
| `stampa_orario(c)` | Griglia della classe |
| `lezioni_docente(c, n, docente)` | Stampa e conta le lezioni del docente |
| `conflitti(a, b)` | Stampa e conta i conflitti tra due classi |
| `nome_giorno(g)` | Abbreviazione del giorno |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `O`: cercare la classe e stamparne la griglia;
   3. `D`: scorrere giorni, ore e classi stampando le lezioni del
      docente, poi il totale;
   4. `C`: confrontare cella per cella le due classi;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Orario, docente e conflitti

- **Input:** `O 1A`, `o 1C`, `D Neri`, `d Preside`, `C`, `X`, `Q`
- **Output atteso:**
  ```
    1A   Lun         Mar         Mer         Gio         Ven        
    1a   Matematica  Fisica      Informatica Italiano    Inglese    
    2a   Italiano    Matematica  Informatica Ed. fisica  Fisica     
    3a   Inglese     Storia      Matematica  Ed. fisica  Italiano   
    4a   Informatica Italiano    Inglese     Matematica  Storia     
    Classe 1C inesistente.
    Lun 4a ora  1A  LabInf   Informatica
    Mer 1a ora  1A  LabInf   Informatica
    Mer 2a ora  1A  LabInf   Informatica
    Mer 3a ora  1B  LabInf   Informatica
    Mer 4a ora  1B  LabInf   Informatica
    Neri: 5 ore settimanali
    Preside: 0 ore settimanali
    Mar 2a ora: Rossi in 1A e in 1B
    Ven 2a ora: aula LabFis occupata da 1A e 1B
    Conflitti: 2
    Comando sconosciuto.
  ```
