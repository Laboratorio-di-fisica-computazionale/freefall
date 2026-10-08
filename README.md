# Esercitazione 1 — Quanto puoi fidarti di una caduta simulata?

Lavorate **in gruppi di due**, con un unico repository e una relazione comune. Ricevete un programma C già organizzato: dovrete implementare le conversioni degli argomenti, il passo numerico e il calcolo del tempo.

## Accettare l'esercitazione in Classroom 50

Entrambi dovete essere iscritti alla classroom e aver accettato l'invito all'organizzazione GitHub del corso. Il docente vi assegna allo stesso gruppo. Aprite il link dell'esercitazione e premete **Accept assignment**: il primo
componente che accetta crea il repository, il secondo accede allo stesso. Se non risultate in un gruppo, avvisate il docente prima di procedere.

Da **Open repository**, copiate l'URL e clonate ciascuno il repository del gruppo sul proprio computer. Non clonate il template del docente. Se decidete di lavorare a casa (o avete due computer in laboratorio), verificate con `git remote -v` che entrambi state usando lo stesso repository remoto. In questa modalità "separata", prima di lavorare ricordate sempre di eseguire `git pull`; concordate chi modifica ciascun file e condividete gli avanzamenti con commit e push. Alternate chi scrive e chi controlla: entrambi devono saper spiegare codice e prove.

## Il sistema

L'asse $Y$ è orientato verso l'alto. Trascuriamo la resistenza dell'aria:

$$
y'=v,\qquad v' =a = -g,\qquad
y_0=100 \mathrm m,\quad v_0=0,\quad g=9.81 \mathrm{m s^{-2}}.
$$

Il riferimento analitico è

$$
y(t)=y_0+v_0t-\tfrac12gt^2,\qquad v(t)=v_0-gt.
$$

## Step 1 — Un algoritmo da mettere alla prova

In `freefall.c` trovate diversi "segnaposto": sono commenti che cominciano con l'espressione `TODO` e indicano parti da codice da modificare e/o completare. 

Il template compila già, ma non fa nulla di utile. Inoltre, se compilate con `-Wall` (come dovreste!) il compilatore vi potrebbe dare alcuni *warning* (avvisi).

Completate poi `euler_step(double dt, double *y, double *v)` con il metodo di Eulero presentato a lezione. La funzione modifica direttamente posizione e velocità tramite i puntatori, e deve restituire `1` quando il passo è implementato. Per calcolare entrambi gli aggiornamenti usate lo stato all'inizio del passo: fate attenzione
a non usare un valore già aggiornato. Il segnaposto restituisce `0`, quindi
il programma segnala che il passo è incompleto e termina con un errore.

Completate anche il calcolo di `t` nel ciclo di `main`, sostituendo il valore provvisorio `-1.`. La stampa avviene **dopo** il passo numerico: quando `step` vale zero, il sistema è già avanzato di un intervallo `dt`. Il tempo deve corrispondere allo stato appena calcolato, così da confrontarlo con la soluzione esatta allo stesso istante.

Prima di eseguire il codice, scrivete una previsione di ciò che vi aspettate di simulare in `relazione.md`.

- Quali informazioni sul moto possiedi all'inizio di un intervallo? Come  potrebbero permetterti di stimare lo stato alla fine?
- Che cosa ti aspetti dopo il primo passo, partendo da fermo? La posizione calcolata dal metodo deve coincidere con quella esatta?
- Il confronto con la soluzione esatta dà lo stesso esito per posizione e velocità? Come potresti spiegarlo?
- Se usassi una velocità appena aggiornata per calcolare la posizione, avresti ancora lo stesso algoritmo? Quale prova distinguerebbe i due casi?

Registrate il commit, consegnate (vedi sotto) e, se c'è ancora tempo, provate a fare il passo 2 (vedi più sotto).

## Interfaccia comune

Lavorate in locale nella copia clonata del repository del gruppo.

Una volta completate le funzioni richieste compilate ed eseguite il codice:

```sh
gcc -o freefall freefall.c -Wall
./freefall 0.1 10
./freefall 0.1 10 > traiettoria.dat
```

Se non avete modificato l'interfaccia, la sintassi è `./freefall DT N`: `DT` è il passo temporale positivo, `N` il numero intero positivo di passi. Se una conversione restituisce `0` oppure `dt <= 0.0` o `steps <= 0`, `main` termina con codice `1`. Se `euler_step` restituisce `0`, il programma termina con un errore.
Non usate nell'analisi i dati di un'esecuzione interrotta. Per le simulazioni usate valori finiti: non sono previsti controlli specifici su `nan`, `inf` o sugli overflow durante il calcolo.

Mantenete nome del programma, costanti e formato dell'output:

```text
# t y_euler v_euler y_exact v_exact error_y
```

Una volta completati i TODO, seguono `N` righe, una dopo ciascun passo: la prima è a `t = DT`, l'ultima a `t = N * DT`. Lo stato iniziale a `t = 0` non viene stampato e non c'è una riga riassuntiva separata.
`error_y`, nella sesta colonna, è l'errore assoluto sulla posizione in metri. Per l'errore al tempo finale leggete la sesta colonna dell'ultima riga. I valori hanno sei cifre decimali, quindi un errore stampato come zero potrebbe in realtà corrispondere a un numero più piccolo di questa risoluzione: come correggeresti?

Quando vi siete convinti che il programma funziona, usate il metodo che preferite (consiglio Python) per fare un grafico della traiettoria $(t, y)$ e salvarlo in `plot.png`.

## Consegna

Consegnate `freefall.c`, `relazione.md` e `plot.png`, più gli eventuali script e dati necessari alle vostre prove aggiuntive. Indicate nella relazione nomi e username GitHub di entrambi e il contributo di ciascuno. La consegna è **una sola per gruppo**, dopo entrambi gli step.
Prima della consegna, riunite tutti i contributi nel branch predefinito e verificate insieme il commit finale. Un componente esegue:

```sh
git status
git diff
git add freefall.c relazione.md plot.png
git commit -m "commento"
git push
```

Includete nel commit anche gli eventuali script e dati aggiuntivi; per i file ignorati seguite le indicazioni dello step 2.

L'assignment usa **A tagged commit**: il push ordinario condivide il lavoro, la consegna richiede un tag (cfr. esercitazione 0). Dopo il push che corrisponde al commit che volete consegnare, eseguite:

```sh
submission_tag="submit/$(date -u +%Y%m%dT%H%M%SZ)"
git tag "$submission_tag"
git push origin "$submission_tag"
```

Il tag include solo modifiche già registrate in un commit. Per una correzione, fate un nuovo commit, push e un nuovo tag: non spostate quello precedente.

Entrambi controllate **Group submission** in Classroom 50 e verificate su GitHub che il tag punti al commit concordato. Gli eventuali test automatici sono configurati dal docente; compilare non certifica il risultato fisico.

Riferimento: [guida studenti di Classroom 50](https://github.com/foundation50/classroom50/wiki/Web-Student-Guide).

# Step 2 (estensione opzionale) — Che cosa significa migliorare la previsione?

Ripartite dall'ultimo commit. Ora dovete sostenere con dati una risposta alla domanda: **come cambia l'affidabilità della previsione quando cambi il passo temporale?**

## Domande stimolo

- Due simulazioni con passi diversi stanno necessariamente rispondendo alla stessa domanda fisica? Che cosa devi tenere invariato per confrontarle?
- Quale misura distinguerebbe un errore piccolo da un accordo solo apparente nel grafico delle traiettorie?
- Quale dipendenza dell'errore dal passo prevedi? Che rappresentazione dei dati ti permetterebbe di distinguere previsioni diverse?
- Una sola coppia di simulazioni basta? Quale dato aggiuntivo renderebbe più convincente o smentirebbe la tua conclusione?
- Ridurre indefinitamente il passo è sempre utile? Come riconosceresti un limite della stampa dei numeri rispetto a un limite del metodo?

## Progettare e realizzare il confronto

Concordate nella coppia il confronto e annotatelo in `relazione.md` prima di eseguire le simulazioni. Scegliete un tempo finale comune e almeno quattro passi temporali; per ogni passo scegliete un numero intero di iterazioni che
raggiunga il tempo scelto. Documentate i comandi utilizzati.
