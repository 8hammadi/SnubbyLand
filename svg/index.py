import svgwrite
from random import random

svg_document = svgwrite.Drawing(filename = "9.svg",size = ("1024px", "200px"))
svg_document.add(svg_document.rect(insert=(0, 0), size=('100%', '100%'), rx=None, ry=None, fill='#f8c291'))


B=[
[{
	"x":10,
	"y":10,
	"w":250,
	"h":70,
	"text":"C -> Continue",
},
{
	"x":10,
	"y":100,
	"w":250,
	"h":70,
	"text":"--",
},

{
	"x":260,
	"y":10,
	"w":250,
	"h":70,
	"text":"--",
}],
[{
	"x":260,
	"y":100,
	"w":250,
	"h":70,
	"text":"L -> Levels",
},


{
	"x":800,
	"y":10,
	"w":250,
	"h":70,
	"text":"0 -> Home",
},
{
	"x":800,
	"y":100,
	"w":250,
	"h":70,
	"text":"Alt+4 -> Quit",
},]

]

h=(200-30)/2
w=(1024-4*10)/3
for i in range(3):
	for j in range(2):
		B[j][i]["x"]=10*(i+1)+i*w
		B[j][i]["y"]=10*(j+1)+j*h
		B[j][i]["w"]=w
		B[j][i]["h"]=h
svg_document.add(svg_document.rect(insert=(0,0), size=("%dpx"%(1024),"%dpx"%(200)), rx="10px", ry="10px", fill='rgb(0,0,0)'))
svg_document.add(svg_document.rect(insert=(3,3), size=("%dpx"%(1024-6),"%dpx"%(200-6)), rx="10px", ry="10px", fill='rgb(%d,%d,%d)'%(255*random(),255*random(),255*random())))

for i in range(3):
	for j in range(2):
		b=B[j][i]
		svg_document.add(svg_document.rect(insert=(b["x"]-3,b["y"]-3), size=("%dpx"%(b["w"]+6),"%dpx"%(b["h"]+6)), rx="10px", ry="10px", fill='rgb(0,0,0)'))
		svg_document.add(svg_document.rect(insert=(b["x"],b["y"]), size=("%dpx"%(b["w"]),"%dpx"%(b["h"])), rx="10px", ry="10px", fill='rgb(%d,%d,%d)'%(255*random(),255*random(),255*random())))
		svg_document.add(svg_document.text(b["text"],
									insert = (10+b["x"],b["y"]+b["h"]/2),
									fill = "rgb(0,0,0)",
									stroke_opacity="1",
									stroke_width=50,
									style = "font-size:20px; font-family:Arial"))





svg_document.save("test.svg")
