# Analisi – 070-problema-bancomat.c

## 1. Problema

Simulare uno sportello bancomat con un menu ripetuto: saldo, prelievo,
versamento e uscita. Il prelievo è consentito solo per importi multipli di
10 euro, non superiori al saldo e entro un limite giornaliero di 500 euro.
All'uscita si stampa il numero di operazioni eseguite e il saldo finale.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `saldo` | `int` | Euro interi: il bancomat eroga banconote |
| `prelevato_oggi` | `int` | Somma dei prelievi della sessione |
| `scelta` | `int` | Voce del menu |
| `importo` | `int` | Importo richiesto |
| `operazioni` | `int` | Contatore delle operazioni riuscite |

Costanti: `LIMITE_GIORNALIERO` = 500, `TAGLIO_MINIMO` = 10.

Struttura: un `do-while` che contiene uno `switch` sulla scelta. Il `break`
di ogni `case` chiude il `case`, non il ciclo; il ciclo termina solo quando
la condizione `scelta != 0` diventa falsa.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Consultazione del saldo

**a) Input** – scelta 1

**b) Output** – "Saldo disponibile: 1250 euro"

**c) Variabili di supporto** – `operazioni`

**d) Vincoli** – il saldo non cambia

**e) Assunzioni** – saldo iniziale 1250 euro

**f) Algoritmo in linguaggio naturale**
1. Ripetere: mostrare il menu, leggere la scelta ed eseguire il ramo
   corrispondente dello `switch`; continuare finché la scelta è diversa da 0.
2. Ramo 1: stampare il saldo e contare l'operazione.

### Caso d'uso 2 – Prelievo

**a) Input** – scelta 2 e un importo

**b) Output** – conferma con il nuovo saldo, oppure il motivo del rifiuto

**c) Variabili di supporto** – `prelevato_oggi`

**d) Vincoli** – i controlli seguono un ordine: importo valido, poi saldo,
poi limite giornaliero; ognuno ha un messaggio specifico

**e) Assunzioni** – il limite vale per l'intera sessione

**f) Algoritmo in linguaggio naturale**
1. Leggere l'importo.
2. Se non è positivo o non è multiplo di 10: messaggio di importo non valido.
3. Altrimenti, se supera il saldo: saldo insufficiente.
4. Altrimenti, se `prelevato_oggi + importo` supera 500: limite superato,
   con l'importo ancora prelevabile.
5. Altrimenti aggiornare saldo e `prelevato_oggi`, contare l'operazione,
   stampare la conferma.

### Caso d'uso 3 – Versamento

**a) Input** – scelta 3 e un importo

**b) Output** – nuovo saldo, oppure "Importo non valido."

**c) Variabili di supporto** – `operazioni`

**d) Vincoli** – l'importo deve essere positivo

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – se l'importo è positivo sommarlo al
saldo e contare l'operazione, altrimenti segnalare l'errore.

### Caso d'uso 4 – Scelta non valida e uscita

**a) Input** – una scelta non prevista (es. 7), poi 0

**b) Output** – "Scelta non valida." e, con 0, il riepilogo finale

**c) Variabili di supporto** – `operazioni`

**d) Vincoli** – il ciclo termina solo tramite la sua condizione, mai con
un'uscita anticipata

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – ramo `default`: messaggio di errore;
ramo 0: stampa del riepilogo, poi la condizione del `do-while` diventa falsa.
