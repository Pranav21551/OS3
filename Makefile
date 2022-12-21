make :
	gcc -o 1_1 SOCKETProc1.c
	gcc -o 1_2 SOCKETProc2.c
	gcc -o 2_1 FIFOProc1.c
	gcc -o 2_2 FIFOProc2.c
	gcc -o 3_1 SharedMemoryProc1.c
	gcc -o 3_2 SharedMemoryProc2.c
		
