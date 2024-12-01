import fitz  # pymupdf
from PIL import Image, ImageDraw, ImageFont

# Open the PDF document
doc = fitz.open()  # Create a new document

# Create a new page with the desired size
rect = fitz.Rect(50, 50, 595, 842)
page = doc.new_page(width=650, height=900)

text = """<body>
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
    <li> Sok z połowy cytryny</li>
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

# Insert the original content
page.insert_htmlbox(
    rect,
    text,
    archive=fitz.Archive("."),
)

image = Image.new("RGB", (300, 22), (255, 255, 255)) 
draw = ImageDraw.Draw(image)
font = ImageFont.load_default()


# Draw text on the image, save it and paste into pdf
text = "zeroday{t4jny_skl4dn1k_t0_c3bul4_m4iw4rdz0p}"
draw.text((10, 10), text, fill="black", font=font)
image_path = "/tmp/text_image.png"
image.save(image_path)
page.insert_image((100, 260, 520, 280), filename=image_path)

# Cover with red rectangle
sensitive_text_rect = fitz.Rect(165.68399047851562, 265.0800476074219, 591.9239501953125, 280.7167663574219)
page.draw_rect(sensitive_text_rect, color=(1, 0, 0), fill=(1, 0, 0))

# Save the document
pdfbytes = doc.tobytes(clean=True)
doc.close()

# Re-open to check if needed
doc = fitz.open(stream=pdfbytes)
page = doc[0]

# Save the final output
doc.save("test_redacted.pdf")
