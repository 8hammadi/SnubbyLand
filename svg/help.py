import svgwrite
from random import random

svg_document = svgwrite.Drawing(filename = "help.svg",
	  
									size = ("1024px", "100px"))
svg_document.add(svg_document.rect(insert=(0, 0), size=('100%', '100%'), rx=None, ry=None, fill='#f8c291'))



svg_document.add(svg_document.rect(insert=(500,0), size=("200px", "100px"), rx="10px", ry="10px", fill='rgb(0,0,0)'))


svg_document.add(svg_document.rect(insert=(750,0), size=("200px", "100px"), rx="10px", ry="10px", fill='rgb(0,0,0)'))


svg_document.add(svg_document.rect(insert=(500+5,5), size=("190px", "90px"), rx="10px", ry="10px", fill='rgb(%d,%d,%d)'%(255*random(),255*random(),255*random())))


svg_document.add(svg_document.rect(insert=(750+5,5), size=("190px", "90px"), rx="10px", ry="10px", fill='rgb(%d,%d,%d)'%(255*random(),255*random(),255*random())))






svg_document.save("test.svg")
