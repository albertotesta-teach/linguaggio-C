# Analisi – 050-problema-backup-impostazioni.c

## 1. Problema

La LIM dell'aula ha luminosità, volume, ingresso video e tempo di
spegnimento. Il programma permette di modificarli, salvarne un backup,
ripristinarlo o tornare ai valori di fabbrica, ognuno con un solo
assegnamento tra struct. All'uscita confronta campo per campo le
impostazioni in uso con il backup e avvisa delle modifiche non salvate.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `L n` luminosità, `V n` volume, `I nome` ingresso, `B` backup, `R` ripristino, `F` fabbrica, `S` stato, `Q` fine (anche minuscoli) |
| `valore` | `int` | Luminosità o volume, da 0 a 100 |
| `nome` | `char[8]` | Ingresso: `HDMI1`, `HDMI2` o `PC` |

### Output

- Per ogni comando una conferma (`Luminosita' 85.`, `Impostazioni
  salvate.`, ...), lo stato completo con `S`, oppure `Valore tra 0 e
  100.`, `Ingressi: HDMI1, HDMI2, PC.`, `Comando sconosciuto.`
- All'uscita: `Nessuna modifica da salvare.` oppure
  `Attenzione: ci sono modifiche non salvate.`

### Vincoli

- Valori di fabbrica: luminosità 70, volume 40, ingresso HDMI1,
  spegnimento 30 minuti (`const Impostazioni predefinite`).
- Backup, ripristino e fabbrica sono assegnamenti tra struct.
- Le struct non si confrontano con `==`: si confrontano i campi, la
  stringa con `strcmp`.
- Un comando per riga: il resto della riga viene scartato, così un
  valore non numerico non viene letto come altri comandi.
- A fine input il programma termina come con `Q`.

### Assunzioni

- Il tempo di spegnimento non si modifica da questo menu.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Impostazioni` | `typedef struct { int luminosita; int volume; char ingresso[8]; int spegnimento; } Impostazioni;` | Le impostazioni della LIM |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `predefinite` | `const Impostazioni` | Valori di fabbrica |
| `corrente`, `salvate` | `Impostazioni` | In uso e backup |
| `uguali` | `int` | Esito del confronto campo per campo |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Partire con impostazioni in uso e backup uguali ai valori di fabbrica.
2. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) e convertirlo in maiuscolo;
   2. `L`/`V`: leggere il valore e, se tra 0 e 100, impostarlo;
   3. `I`: leggere il nome e, se è un ingresso ammesso, copiarlo;
   4. `B`: `salvate = corrente`; `R`: `corrente = salvate`;
      `F`: `corrente = predefinite`; `S`: stampare lo stato;
   5. altrimenti comando sconosciuto;
   6. scartare il resto della riga.
3. Confrontare i campi di `corrente` e `salvate` e stampare l'avviso.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Cosa si verifica:** modifiche, valori non validi, backup, ripristino,
  fabbrica e avviso finale.
- **Input:** `S`, `L 85`, `v 120`, `V abc`, `I PC`, `I VGA`, `B`, `V 10`,
  `S`, `R`, `S`, `X`, `F`, `S`, `Q`
- **Output atteso:**
  ```
    luminosita' 70, volume 40, ingresso HDMI1, spegnimento dopo 30 min
    Luminosita' 85.
    Valore tra 0 e 100.
    Valore tra 0 e 100.
    Ingresso PC.
    Ingressi: HDMI1, HDMI2, PC.
    Impostazioni salvate.
    Volume 10.
    luminosita' 85, volume 10, ingresso PC, spegnimento dopo 30 min
    Backup ripristinato.
    luminosita' 85, volume 40, ingresso PC, spegnimento dopo 30 min
    Comando sconosciuto.
    Valori di fabbrica.
    luminosita' 70, volume 40, ingresso HDMI1, spegnimento dopo 30 min
  Attenzione: ci sono modifiche non salvate.
  ```

### Test 2 – Nessuna modifica

- **Input:** `L 50`, `B`, `Q`
- **Output atteso:** `Nessuna modifica da salvare.`

### Test 3 – Fine input con modifiche

- **Input:** `B`, `L 50`, poi fine input.
- **Output atteso:** `Attenzione: ci sono modifiche non salvate.`
