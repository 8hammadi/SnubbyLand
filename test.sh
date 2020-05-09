echo "...... this is test server ......";

if c++ -o ../bin/test test.cpp  -I/home/run/boost -L/home/run/boost/stage/lib   -pthread ;then
	echo "Compiling succeeded"
	./../bin/test $id
else
	echo "Compiling failed"
fi
