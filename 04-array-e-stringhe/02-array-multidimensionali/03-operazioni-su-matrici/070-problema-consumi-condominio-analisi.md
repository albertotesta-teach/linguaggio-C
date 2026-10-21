# Analisi – 070-problema-consumi-condominio.c

## 1. Problema

L'amministratore di un condominio ha i consumi mensili di riscaldamento
(kWh) di 6 appartamenti da ottobre a marzo. Vuole il consumo stagionale di
ogni appartamento e la sua quota, il totale di ogni mese con il mese di
picco, gli appartamenti oltre il 120% della media e il mese di massimo
consumo di ciascuno.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                 |
|-----------|------------|------------|---------------------------------------------|
| `consumi` | `int[][]`  | 6 × 6      | Riga = appartamento, colonna = mese (kWh)   |
| `interni` | `int[]`    | 6          | Numero di interno, parallelo alle righe     |
| `mesi`    | `char[][]` | 6 × 4      | Sigla del mese, parallela alle colonne      |

### Output
- La tabella dei consumi con il totale stagionale di ogni appartamento;
- la riga dei totali mensili con il totale del condominio, e il mese di
  picco;
- il consumo medio per appartamento e la soglia di attenzione (120% della
  media);
- per ogni appartamento la quota sul totale, il mese di massimo consumo e
  l'avviso "<- consumo elevato" se supera la soglia.

### Vincoli
- I totali stagionali (righe) si calcolano una volta e si salvano in
  `stagione`, perché servono per il totale, per le quote e per la soglia
- I totali mensili si calcolano per **colonna**
- Quota = consumo stagionale / totale del condominio × 100
- Un appartamento è segnalato se il consumo è **strettamente** maggiore del
  120% della media; il confronto `stagione × 100 > media × 120` evita di
  dividere
- A parità vince il primo mese trovato, sia per il picco sia per il massimo
  di ogni appartamento

### Assunzioni
- I consumi sono non negativi e il totale del condominio è positivo

### Variabili di supporto

| Variabile           | Tipo     | Dimensione | Descrizione                            |
|---------------------|----------|------------|----------------------------------------|
| `stagione`          | `int[]`  | 6          | Totale di ogni riga                    |
| `totale_condominio` | `int`    | —          | Totale generale                        |
| `totale_mese`       | `int`    | —          | Totale della colonna corrente          |
| `max_mese`, `m_picco` | `int`  | —          | Mese con il totale più alto            |
| `m_max_app`         | `int`    | —          | Mese di massimo della riga corrente    |
| `media`             | `double` | —          | Consumo medio stagionale               |
| `SOGLIA_PERCENTO`   | `#define`| 120        | Soglia di attenzione in percentuale    |

### Algoritmo in linguaggio naturale
1. Per ogni appartamento stampare i consumi, calcolare e stampare il totale
   stagionale e sommarlo al totale del condominio.
2. Per ogni mese sommare la colonna, stamparla e aggiornare il picco;
   stampare il totale del condominio e il mese di picco.
3. Calcolare la media e la soglia e stamparle.
4. Per ogni appartamento cercare il mese di massimo nella riga, stampare
   quota e mese, e aggiungere l'avviso se il consumo supera la soglia.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Totali e mese di picco
- **Output atteso:**
```
        1   310   520   780   820   650   400      3480
        2   280   450   700   760   590   350      3130
        3   450   690   980  1050   860   560      4590
        4   150   260   450   430   330   200      1820
        5   300   500   750   800   620   390      3360
        6   200   360   540   560   610   270      2540
  Totale   1690  2780  4200  4420  3660  2170     18920

Mese di picco: Gen (4420 kWh)
```

### Test 2 – Quote, soglia e mese di massimo
- **Cosa si verifica:** l'interno 4 ha il massimo a dicembre e l'interno 6 a
  febbraio, diversamente dal picco del condominio; solo l'interno 3 supera
  la soglia
- **Output atteso:**
```
Consumo medio per appartamento: 3153 kWh
Soglia di attenzione (120% della media): 3784 kWh

  Interno   Quota   Mese max
        1   18.4%   Gen
        2   16.5%   Gen
        3   24.3%   Gen   <- consumo elevato
        4    9.6%   Dic
        5   17.8%   Gen
        6   13.4%   Feb
```
