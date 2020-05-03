import svgwrite
from random import random

svg_document = svgwrite.Drawing(filename = "online.svg",
	  
									size = ("1024px", "768px"))

svg_document.add(svg_document.rect(insert=(0, 0), size=('100%', '100%'), rx=None, ry=None, fill='#dfe6e9'))

svg_document.add(svg_document.text("Snubby Land",
							insert = (100,180),
							fill = "#2d3436",
							stroke_opacity="50",
							stroke_width=50,
							style = "font-size:150px; font-family:Arial"))



def button(x,y,w,h,text="",police=50,color1="#636e72",color2="#b2bec3",textcolor="#2d3436"):
	svg_document.add(svg_document.rect(insert=(x,y), size=(str(w)+"px", str(h)+"px"), rx="20px", ry="20px", fill=color1))
	svg_document.add(svg_document.rect(insert=(x+h/10,y+h/10), size=(str(w-h/5)+"px", str(h-h/5)), rx="20px", ry="20px", fill=color2))
	svg_document.add(svg_document.text(text,
								insert = (x+w/5-50,y+h-h/5),
								fill = textcolor,
								stroke_opacity="50",
								stroke_width=50,
								style = "font-size:%dpx; font-family:Arial"%(police)))


button(156,220,700,100,text="ONE PLAYER OFFLINE")
button(156,340,700,100,	text="TWO PLAYER ONLINE")
button(156,460,700,100,text="GENETIC ALGORITHM")
button(156,580,700,100,text="CREATE NEW LEVEL")

svg_document.add(svg_document.text("ID :",
							insert = (0,40),
							fill = "#2d3436",
							stroke_opacity="50",
							stroke_width=30,
							style = "font-size:20px; font-family:Arial"))

svg_document.add(svg_document.text("STATUS :",
							insert = (120,40),
							fill = "#2d3436",
							stroke_opacity="50",
							stroke_width=30,
							style = "font-size:20px; font-family:Arial"))


svg_document.add(svg_document.text("ONLINE PLAYERS :",
							insert = (300,40),
							fill = "#2d3436",
							stroke_opacity="50",
							stroke_width=30,
							style = "font-size:20px; font-family:Arial"))

svg_document.add(svg_document.text("MUSIC :",
							insert = (580,40),
							fill = "#2d3436",
							stroke_opacity="50",
							stroke_width=30,
							style = "font-size:20px; font-family:Arial"))

svg_document.add(svg_document.text("REACTION SOUND :",
							insert = (750,40),
							fill = "#2d3436",
							stroke_opacity="50",
							stroke_width=30,
							style = "font-size:20px; font-family:Arial"))


svg_document.save()


