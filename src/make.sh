id="@abdellatif_aithammadi";
echo "...... Welcome to snubbyland ......";
if [ $# -eq 0 ] ;then echo "testing ..";./../bin/game $id ;
else
	if g++ -o ../bin/game main.cpp -lSDL2  -lSDL2_image  -lm -lboost_serialization -lSDL2_ttf  ;then
		echo "Compiling succeeded"
		./../bin/game $id
	else
		echo "Compiling failed"
	fi
fi

# c++ -o test test.cpp  -I/home/run/boost -L/home/run/boost/stage/lib   -pthread