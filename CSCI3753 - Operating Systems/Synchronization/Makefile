all: ThreadReadersWritersNoSync.c ThreadReadersWritersSimple.c ThreadReadersWritersSemaphores.c ThreadReadersWritersNoSync.java ThreadReadersWritersMonitor.java
	clear
	gcc -o ThreadReadersWritersNoSync.exe ThreadReadersWritersNoSync.c -lpthread
	gcc -o ThreadReadersWritersSimple.exe ThreadReadersWritersSimple.c -lpthread
	gcc -o ThreadReadersWritersSemaphores.exe ThreadReadersWritersSemaphores.c -lpthread
	javac ThreadReadersWritersNoSync.java
	javac ThreadReadersWritersMonitor.java
	ls -la *.exe *.class
clean:
	rm -rf *~
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.class
	clear
	ls -la