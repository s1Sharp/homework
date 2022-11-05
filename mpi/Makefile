of = output\output
exeDebug = executable\Debug\MPI_task
exeRelease = executable\Release\MPI_task
exe = $(exeRelease)
n = 4
numberofprocess=$(n)
run = mpiexec -n $(numberofprocess)

# mpiexec -n 4 -debug 1 executable\Debug\MPI_task3.exe

all: mkdir task1 task2 task3 task4 task5 task6

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

task5: mkdir task5.cpp
	$(run) $(exe)5.exe > $(of)5.txt

task6: mkdir task6.cpp
	mpiexec -n 3 $(exe)6.exe > $(of)6.txt

task7: mkdir task7.cpp
	$(run) $(exe)7.exe > $(of)7.txt

task8: mkdir task8.cpp
	$(run) $(exe)8.exe > $(of)8.txt

task9: mkdir task9.cpp
	$(run) $(exe)9.exe > $(of)9.txt

task10: mkdir task10.cpp
	mpiexec -n 10 $(exe)10.exe > $(of)10.txt
