of = output\output
exeDebug = executable\Debug\MPI_task
exeRelease = executable\Release\MPI_task
exe = $(exeDebug)
n = 4
numberofprocess=$(n)
run = mpiexec -n $(numberofprocess)

all: mkdir task1 task2 task2

mkdir:
	IF exist output ( echo output exists ) ELSE ( mkdir output && echo output created)
	
task1: mkdir task1.cpp
	$(run) $(exe)1.exe > $(of)1.txt

task2: mkdir task2.cpp
	$(run) $(exe)2.exe > $(of)2.txt

task3: mkdir task3.cpp
	$(run) $(exe)3.exe > $(of)3.txt

task4: mkdir task4.cpp
	$(run) $(exe)4.exe > $(of)4.txt