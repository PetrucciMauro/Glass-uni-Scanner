README - LATEX


Per creare un documento, nella cartella Template/template_NoInclude c'è un file documento.tex. Copiare quel file in un'altra cartella fuori da Template 
(es. voglio fare l'Analisi dei Requisiti allora creo la cartella corrispondente e lo ficco lì).

Entrando nella cartella Template ci sono i file:
-format.sty: al suo interno ci sono tutte le formattazioni e variabili che valgono per ogni documento
-firstpage.tex: serve per creare la prima pagina. Vale per ogni documento
-sommario.tex: serve per creare il sommario di ogni documento

All'interno di template_NoInclude ci sono:
-documento.tex: è la base da cui si può creare un documento. (FILE DA NON MODIFICARE)
-parti.tex: al suo interno ci sono i metodi con cui scrivere le varie parti di ogni documento. Ci sono un insieme di comandi di esempio per 
far vedere come scrivere tutto. Se qualcuno trova nuovi comandi è utile riportarli qui così tutti possono vedere velocemente cosa fanno quei comandi.
-registroMod.tex: è la base da cui creare il registro delle modifiche (versionamento) del documento. (FILE DA NON MODIFICARE)

----------------------------

Al momento ho fatto un documento di esempio (ovviamente non c'è scritto quasi niente).
Aprite Norme di Progetto/NormeDiProgetto-v.1.tex per vedere come vengono richiamate tutte le varie parti e come vengono messe insieme.