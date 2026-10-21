# Analisi – 060-problema-somma-solo-positivi.c

## 1. Problema

Un contatore elettrico invia ogni ora il consumo in wattora. Per un guasto
del sensore alcune letture sono negative: vanno scartate, contate e
segnalate. L'operatore inserisce le letture della giornata e termina con
-999. Il programma calcola il consumo totale, il consumo medio sulle letture
valide, la lettura massima e il numero di letture scartate.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                                     |
|-----------|-------|-------------------------------------------------|
| `lettura` | `int` | Valore in Wh; la sequenza termina con -999      |

### Output
La segnalazione di ogni lettura scartata (con il suo numero d'ordine); poi
il numero di letture ricevute, valide e scartate; infine il consumo totale
(in Wh e kWh), il consumo medio e la lettura massima, oppure il messaggio
"Nessuna lettura valida: impossibile calcolare i consumi."

### Vincoli
- Una lettura è valida se è maggiore o uguale a 0 (lo zero è valido)
- -999 è la sentinella: chiude la sequenza e non è una lettura
- La media si calcola solo sulle letture valide e solo se ce n'è almeno
  una, per evitare la divisione per zero
- La lettura successiva si legge in un solo punto, alla fine del corpo del
  ciclo: le letture anomale si gestiscono nel ramo `else`, senza `continue`

### Assunzioni
- Le letture sono intere
- L'operatore inserisce numeri interi

### Variabili di supporto

| Variabile        | Tipo  | Significato                              |
|------------------|-------|------------------------------------------|
| `numero_lettura` | `int` | Contatore di tutte le letture ricevute   |
| `valide`         | `int` | Contatore delle letture valide           |
| `scartate`       | `int` | Contatore delle letture scartate         |
| `totale`         | `int` | Accumulatore delle letture valide        |
| `massima`        | `int` | Lettura valida più alta                  |

Costante: `FINE_DATI` = -999 (sentinella). Il ciclo usa la lettura
anticipata vista nella sezione 04.

### Algoritmo in linguaggio naturale
1. Leggere la prima lettura.
2. Finché la lettura è diversa da -999:
   a. incrementare `numero_lettura`;
   b. se la lettura è maggiore o uguale a 0: contarla come valida,
      sommarla al totale, aggiornare il massimo (la prima valida lo
      inizializza);
   c. altrimenti contarla come scartata e segnalarla;
   d. leggere la lettura successiva.
3. Stampare i contatori; se ci sono letture valide stampare totale, media e
   massimo, altrimenti un messaggio.

## 3. Casi di test

Per ogni caso si esegue il programma con la sequenza di input indicata e si
confronta quanto stampato con l'output atteso.

### Test 1 – Giornata con letture anomale
- **Cosa si verifica:** scarto delle negative, zero considerato valido
- **Input:** 420, 380, -15, 0, 510, -3, 465, -999
- **Output atteso:** segnalazione delle letture 3 e 6; 7 ricevute, 5 valide,
  2 scartate; totale 1775 Wh (1,775 kWh); media 355,0 Wh; massima 510 Wh

### Test 2 – Nessuna lettura valida
- **Cosa si verifica:** il controllo `valide > 0` evita la divisione per zero
- **Input:** -5, -8, -999
- **Output atteso:** 2 scartate e "Nessuna lettura valida: impossibile
  calcolare i consumi."

### Test 3 – Sentinella come primo valore
- **Cosa si verifica:** il corpo del ciclo non viene eseguito
- **Input:** -999
- **Output atteso:** 0 letture ricevute, nessun consumo calcolabile
