make:
	g++ -o playground.exe playground.cpp

clean:
	rm -f playground.exe
	if [ -e data.bin ]; then rm data.bin; fi
	if [ -e data.txt ]; then rm data.txt; fi
	if [ -e a.out ]; then rm a.out; fi
	if [ -e *.csfr ]; then rm data.bin; fi
