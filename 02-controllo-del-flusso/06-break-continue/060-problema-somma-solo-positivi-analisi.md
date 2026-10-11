# Analisi – 060-problema-somma-solo-positivi.c

## 1. Problema

Un contatore elettrico invia ogni ora il consumo in wattora. Per un guasto
del sensore alcune letture sono negative: vanno scartate, contate e
segnalate. L'operatore inserisce le letture della giornata e termina con
-999. Il programma calcola il consumo totale, il consumo medio sulle letture
valide, la lettura massima e il numero di letture scartate.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `lettura` | `int` | Valore in Wh |
| `numero_lettura` | `int` | Contatore di tutte le letture ricevute |
| `valide`, `scartate` | `int` | Contatori separati |
| `totale` | `int` | Accumulatore delle letture valide |
| `massima` | `int` | Lettura valida più alta |

Costante: `FINE_DATI` = -999 (sentinella). Lo zero è una lettura valida.

Il ciclo usa la lettura anticipata (sentinella, sezione 04). Le letture
anomale sono gestite nel ramo `else`, senza `continue`: così esiste un solo
punto in cui si legge il valore successivo, alla fine del corpo.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Giornata con letture anomale

**a) Input** – 420, 380, -15, 0, 510, -3, 465, -999

**b) Output** – segnalazione delle letture 3 e 6; 7 ricevute, 5 valide,
2 scartate; totale 1775 Wh (1,775 kWh); media 355,0 Wh; massima 510 Wh

**c) Variabili di supporto** – contatori e accumulatore

**d) Vincoli** – la media si calcola solo sulle letture valide

**e) Assunzioni** – le letture sono intere

**f) Algoritmo in linguaggio naturale**
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

### Caso d'uso 2 – Nessuna lettura valida

**a) Input** – -5, -8, -999

**b) Output** – 2 scartate e "Nessuna lettura valida: impossibile calcolare
i consumi."

**c) Variabili di supporto** – `valide` resta 0

**d) Vincoli** – il controllo `valide > 0` evita la divisione per zero

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Sentinella come primo valore

**a) Input** – -999

**b) Output** – 0 letture ricevute, nessun consumo calcolabile

**c) Variabili di supporto** – nessuna

**d) Vincoli** – il corpo del ciclo non viene eseguito

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.
