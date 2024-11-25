#!/bin/python3

import pymupdf


doc = pymupdf.open()  # make a new PDF
# also give it a page - a bit larger than the rectangle
rect = pymupdf.Rect(50, 50, 595, 842)
page = doc.new_page(-1, width=650, height=900)


text_en = """<body>
<h1> Magiczny przepis </h1>

<h2> Potrzebne składniki</h2>
<ol>
<li> 1 litr wody źródlanej </li>
<li>5 listków świeżej mięty</li>
<li>1 łyżka suszonych kwiatów rumianku </li>
<li>3 plasterki świeżego imbiru</li>
<li>1 szczypta cynamonu</li>
<li> 2 łyżki miodu</li>
<li> 1 kropla wody różanej</li>
<li> Sok z połowy cytryby</li>
<li>Tajny składnik</li>
</ol>

<h2> Sposób przygotowania </h2>

<ol>
<li> W garnku zagotuj wodę źródlaną na średnim ogniu. Gdy zacznie wrzeć, zmniejsz ogień.</li>
<li> Dodaj listki mięty, suszone kwiaty rumianku i plasterki imbiru. Mieszaj delikatnie, wizualizując spokój i energię, które chcesz przywołać.</li>
<li> Po około 5 minutach gotowania dodaj cynamon i pozwól napojowi delikatnie pyrkać przez kolejne 2-3 minuty.</li>
<li> Zdejmij napój z ognia i przecedź go przez sitko, aby pozbyć się ziół i przypraw.</li>
<li> Gdy płyn lekko ostygnie (nie może być wrzący), dodaj miód i dokładnie wymieszaj, myśląc o dobroci, którą chcesz obdarować siebie i innych.</li>
<li> Dodaj kroplę wody różanej oraz sok z cytryny.</li>
<li> Całość zmieszaj z paroma warstwami tajnego składnika</li>
<li> Przelej napój do ulubionego kubka lub karafki, podawaj ciepły lub schłodzony, według uznania. </li>
</ol>
</body>"""

text_de = """<body>
<h1> Magiczny przepis </h1>

<h2> Potrzebne składniki</h2>
<ol>
<li> 1 litr wody źródlanej </li>
<li>5 listków świeżej mięty</li>
<li>1 łyżka suszonych kwiatów rumianku </li>
<li>3 plasterki świeżego imbiru</li>
<li>1 szczypta cynamonu</li>
<li> 2 łyżki miodu</li>
<li> 1 kropla wody różanej</li>
<li> Sok z połowy cytryby</li>
<li>Tajny składnik: emVyb2RheXt0NGpueV9za2w0ZG4xa190MF9jM2J1bDRfbTRpdzRyZHowcH0=</li>
</ol>

<h2> Sposób przygotowania </h2>

<ol>
<li> W garnku zagotuj wodę źródlaną na średnim ogniu. Gdy zacznie wrzeć, zmniejsz ogień.</li>
<li> Dodaj listki mięty, suszone kwiaty rumianku i plasterki imbiru. Mieszaj delikatnie, wizualizując spokój i energię, które chcesz przywołać.</li>
<li> Po około 5 minutach gotowania dodaj cynamon i pozwól napojowi delikatnie pyrkać przez kolejne 2-3 minuty.</li>
<li> Zdejmij napój z ognia i przecedź go przez sitko, aby pozbyć się ziół i przypraw.</li>
<li> Gdy płyn lekko ostygnie (nie może być wrzący), dodaj miód i dokładnie wymieszaj, myśląc o dobroci, którą chcesz obdarować siebie i innych.</li>
<li> Dodaj kroplę wody różanej oraz sok z cytryny.</li>
<li> Całość zmieszaj z paroma warstwami tajnego składnika</li>
<li> Przelej napój do ulubionego kubka lub karafki, podawaj ciepły lub schłodzony, według uznania. </li>
</ol>
</body>"""

oc_bs = doc.add_ocg("REDACTED")
oc_fl = doc.set_ocmd(ocgs=[oc_bs], policy="AllOff")

page.insert_htmlbox(
    rect,
    text_en,  
    archive=pymupdf.Archive("."),
    oc=oc_bs,  
)


page.insert_htmlbox(
    rect,
    text_de,  
    archive=pymupdf.Archive("."),
    oc=oc_fl,  
)

pdfbytes = doc.tobytes(clean=True)
doc.close()
doc=pymupdf.open(stream=pdfbytes)
page=doc[0]

doc.save("test.pdf") 
