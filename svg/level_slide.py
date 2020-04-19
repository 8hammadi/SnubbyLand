import svgwrite
from random import random

svg_document = svgwrite.Drawing(filename = "level.svg",
	  
									size = ("1024px", "3000px"))
svg_document.add(svg_document.rect(insert=(0, 0), size=('100%', '100%'), rx=None, ry=None, fill='#f8c291'))

# 100-250-37-250-37-250-100
for j in range(3):
	for i in range(20):
		x=40+(j)*288+(j)*40
		y=40+(i)*150+(i)*40

		svg_document.add(svg_document.rect(insert=(x,y), size=("288px", "150px"), rx="10px", ry="10px", fill='rgb(%d,%d,%d)'%(255*random(),255*random(),255*random())))
		print(100+j*250+(j-1)*37, 100+i*250+(i-1)*37)

svg_document.save("test.svg")

# for i in range(n-1):
# 	for j1 in range(N[i]):
# 		for j2 in range(N[i]):
# 			p=random.random()
# 			svg_document.add(svg_document.polyline(
# 				points=[(X[i],Y[j1]-400),(X[i+1],Y[j2]-400)],
# 				stroke="#130f40",
# 				stroke_opacity=str(p),
# 				fill="none",
# 				stroke_width=10,
# 				stroke_linejoin="round",
# 				stroke_linecap="round",
# 				# id="w"+str(i)+"-"+str(j)
# 			))

# for i in range(n):
# 	for j in range(N[i]):
# 		svg_document.add(svg_document.circle(
# 							center=(X[i],Y[j]-400),
# 							r=15,
# 							fill="rgb(255,0,0)",
# 						))
# 		svg_document.add(svg_document.circle(
# 							center=(X[i],Y[j]-400),
# 							r=10,
# 							fill="#e056fd",
# 							id="C"+str(i)+"-"+str(j)
# 						))


