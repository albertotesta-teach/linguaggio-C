# Analisi – 070-problema-bancomat.c

## 1. Problema

Simulare uno sportello bancomat con un menu ripetuto: saldo, prelievo,
versamento e uscita. Il prelievo è consentito solo per importi multipli di
10 euro, non superiori al saldo e entro un limite giornaliero di 500 euro.
All'uscita si stampa il numero di operazioni eseguite e il saldo finale.

## 2. Analisi

### Input

| Variabile | Tipo  | Significato                                              |
|-----------|-------|----------------------------------------------------------|
| `scelta`  | `int` | Voce del menu: 1 saldo, 2 prelievo, 3 versamento, 0 uscita |
| `importo` | `int` | Importo richiesto, solo per prelievo e versamento        |

### Output
A ogni giro il menu e l'esito dell'operazione scelta: il saldo, la
conferma con il nuovo saldo oppure il motivo del rifiuto, "Scelta non
valida." per le voci non previste. All'uscita il riepilogo con il numero
di operazioni riuscite e il saldo finale.

### Vincoli
- Prelievo: importo positivo e multiplo di 10, non superiore al saldo e
  tale che `prelevato_oggi + importo` non superi 500
- I controlli del prelievo seguono un ordine (importo valido, poi saldo,
  poi limite giornaliero) e ognuno ha un messaggio specifico
- Versamento: importo positivo
- Il ciclo termina solo tramite la sua condizione (`scelta != 0`), mai con
  un'uscita anticipata; il `break` di ogni `case` chiude il `case`, non il ciclo
- Si contano solo le operazioni riuscite

### Assunzioni
- Il saldo iniziale è 1250 euro
- Il limite giornaliero vale per l'intera sessione
- L'utente inserisce numeri interi

### Variabili di supporto

| Variabile        | Tipo  | Significato                                 |
|------------------|-------|---------------------------------------------|
| `saldo`          | `int` | Euro interi: il bancomat eroga banconote    |
| `prelevato_oggi` | `int` | Somma dei prelievi della sessione           |
| `operazioni`     | `int` | Contatore delle operazioni riuscite         |

Costanti: `LIMITE_GIORNALIERO` = 500, `TAGLIO_MINIMO` = 10.

Struttura: un `do-while` che contiene uno `switch` sulla scelta.

### Algoritmo in linguaggio naturale
1. Ripetere: mostrare il menu, leggere la scelta ed eseguire il ramo
   corrispondente dello `switch`; continuare finché la scelta è diversa da 0.
2. Ramo 1 (saldo): stampare il saldo e contare l'operazione.
3. Ramo 2 (prelievo):
   a. leggere l'importo;
   b. se non è positivo o non è multiplo di 10: messaggio di importo non valido;
   c. altrimenti, se supera il saldo: saldo insufficiente;
   d. altrimenti, se `prelevato_oggi + importo` supera 500: limite superato,
      con l'importo ancora prelevabile;
   e. altrimenti aggiornare saldo e `prelevato_oggi`, contare l'operazione,
      stampare la conferma.
4. Ramo 3 (versamento): leggere l'importo; se è positivo sommarlo al saldo
   e contare l'operazione, altrimenti segnalare l'errore.
5. Ramo 0 (uscita): stampare il riepilogo; la condizione del `do-while`
   diventa falsa.
6. Ramo `default`: stampare "Scelta non valida."

## 3. Casi di test

Il programma è interattivo: ogni test è una sequenza di scelte eseguita in
una nuova sessione, che parte dal saldo iniziale di 1250 euro e si chiude
con la scelta 0.

### Test 1 – Consultazione del saldo
- **Input:** scelta 1, poi 0
- **Output atteso:** "Saldo disponibile: 1250 euro", poi
  "Operazioni eseguite: 1. Saldo finale: 1250 euro. Arrivederci."

### Test 2 – Prelievo accettato
- **Input:** scelta 2 con importo 200, poi 0
- **Output atteso:** "Ritirare 200 euro. Nuovo saldo: 1050 euro"

### Test 3 – Prelievo con importo non valido
- **Cosa si verifica:** il primo controllo del prelievo
- **Input:** scelta 2 con importo 25 (non multiplo di 10), oppure -10
- **Output atteso:** "Importo non valido: multipli di 10 euro."; saldo invariato

### Test 4 – Prelievo oltre il saldo
- **Cosa si verifica:** il secondo controllo del prelievo
- **Input:** scelta 2 con importo 1300
- **Output atteso:** "Saldo insufficiente."

### Test 5 – Prelievo oltre il limite giornaliero
- **Cosa si verifica:** il limite vale per la somma dei prelievi della sessione
- **Input:** scelta 2 con importo 400, poi scelta 2 con importo 200
- **Output atteso:** "Ritirare 400 euro. Nuovo saldo: 850 euro", poi
  "Limite giornaliero superato: puoi prelevare ancora 100 euro."

### Test 6 – Versamento
- **Input:** scelta 3 con importo 100, poi scelta 3 con importo 0
- **Output atteso:** "Versamento eseguito. Nuovo saldo: 1350 euro", poi
  "Importo non valido."

### Test 7 – Scelta non valida e uscita
- **Cosa si verifica:** il ramo `default` e il conteggio delle sole
  operazioni riuscite
- **Input:** scelta 7, poi scelta 0
- **Output atteso:** "Scelta non valida.", poi
  "Operazioni eseguite: 0. Saldo finale: 1250 euro. Arrivederci."
