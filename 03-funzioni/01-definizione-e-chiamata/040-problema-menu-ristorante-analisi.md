# Analisi – 040-problema-menu-ristorante.c

## 1. Problema
Un ristorante vuole stampare il proprio menu a schermo in modo ordinato e
facilmente aggiornabile. Il menu è suddiviso in sezioni fisse (antipasti,
primi, secondi, dolci) ciascuna con i propri piatti e prezzi. L'obiettivo
è organizzare il codice in modo che modificare una sezione richieda di
intervenire in un solo punto.

## 2. Analisi generale e struttura dati

Non sono necessarie variabili di stato: tutti i dati (nomi dei piatti,
prezzi) sono costanti testuali incorporate direttamente nelle funzioni
di stampa. La struttura dati è implicita nell'organizzazione delle funzioni.

| Funzione | Tipo | Descrizione |
|---|---|---|
| `stampa_intestazione_menu` | void | Nome, indirizzo e telefono del locale |
| `stampa_antipasti` | void | Sezione antipasti con prezzi |
| `stampa_primi` | void | Sezione primi piatti con prezzi |
| `stampa_secondi` | void | Sezione secondi piatti con prezzi |
| `stampa_dolci` | void | Sezione dolci con prezzi |
| `stampa_piede_menu` | void | Informazioni su coperto e orari |
| `stampa_menu_completo` | void | Chiama le funzioni in sequenza |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Stampa del menu completo

**a) Input** – nessuno (i dati sono incorporati nelle funzioni)

**b) Output** – menu formattato con intestazione, quattro sezioni e piede

**c) Variabili di supporto** – nessuna

**d) Vincoli**
- Ogni sezione deve essere chiaramente separata visivamente
- I prezzi devono essere allineati

**e) Assunzioni**
- I dati del menu non cambiano a runtime
- La larghezza dello schermo è sufficiente per la formattazione

**f) Algoritmo in linguaggio naturale**
1. Stampa intestazione con nome e recapiti del locale
2. Stampa sezione antipasti (titolo + voci con prezzi)
3. Stampa sezione primi piatti
4. Stampa sezione secondi piatti
5. Stampa sezione dolci
6. Stampa piede con informazioni aggiuntive

### Caso d'uso 2 – Aggiornamento di una sezione

**a) Input** – modifica nel codice sorgente di una funzione specifica

**b) Output** – menu aggiornato alla successiva esecuzione

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la modifica deve riguardare una sola funzione

**e) Assunzioni** – chi modifica conosce la struttura del codice

**f) Algoritmo in linguaggio naturale**
1. Identificare la funzione corrispondente alla sezione da aggiornare
2. Modificare i `printf` all'interno di quella sola funzione
3. Ricompilare ed eseguire

### Caso d'uso 3 – Stampa di una sola sezione

**a) Input** – chiamata diretta a una funzione di sezione

**b) Output** – solo la sezione richiesta

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la funzione deve funzionare anche se chiamata isolatamente

**e) Assunzioni** – il chiamante si occupa del contesto (intestazione, piede)

**f) Algoritmo in linguaggio naturale**
1. Chiamare direttamente `stampa_antipasti()` (o altra sezione)
2. La funzione stampa solo la propria sezione senza dipendenze esterne
