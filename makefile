CC = g++
CFLAGS = -std=c++0x -pthread -I/usr/local/include -L/usr/local/lib
#CFLAGS = -std=c++0x -pthread -I/usr/local/include -L/usr/local/lib -g -DNDEBUG

all: htdetect

htdetect: htdetect.o Hit.o HitControler.o HitModel.o HitList.o HitListControler.o HitListModel.o Blast.o BlastControler.o BlastModel.o Fasta.o FastaThread.o FastaControler.o FastaModel.o Sequence.o Alignement.o ProgressBar.o ProgressBarThread.o
	$(CC) htdetect.o Hit.o  HitControler.o HitModel.o HitList.o HitListControler.o HitListModel.o Blast.o BlastControler.o BlastModel.o Fasta.o FastaThread.o FastaControler.o FastaModel.o Sequence.o Alignement.o ProgressBar.o ProgressBarThread.o -o htdetect $(CFLAGS)
 	
htdetect.o: htdetect.cpp Hit.o HitControler.o HitModel.o HitList.o HitListControler.o HitListModel.o Blast.o BlastControler.o BlastModel.o Fasta.o FastaThread.o FastaControler.o FastaModel.o Sequence.o Alignement.o ProgressBar.o ProgressBarThread.o
	$(CC) -c htdetect.cpp $(CFLAGS)

# Blast
Blast.o: Blast/Blast.cpp BlastControler.o
	$(CC) -c Blast/Blast.cpp $(CFLAGS)

BlastControler.o: Blast/BlastControler.cpp BlastModel.o Alignement.o myThread.o
	$(CC) -c Blast/BlastControler.cpp $(CFLAGS)

BlastModel.o: Blast/BlastModel.cpp HitList.o
	$(CC) -c Blast/BlastModel.cpp $(CFLAGS)

Alignement.o: Alignement/Alignement.cpp HitList.o Fasta.o ProgressBar.o PathWalker.o
	$(CC) -c Alignement/Alignement.cpp $(CFLAGS)

# PathWalker
PathWalker.o: PathWalker/PathWalker.cpp PathWalkerControler.o
	$(CC) -c PathWalker/PathWalker.cpp $(CFLAGS)

PathWalkerControler.o: PathWalker/PathWalkerControler.cpp PathWalkerModel.o
	$(CC) -c PathWalker/PathWalkerControler.cpp $(CFLAGS)

PathWalkerModel.o: PathWalker/PathWalkerModel.cpp Path.o ProgressBar.o
	$(CC) -c PathWalker/PathWalkerModel.cpp $(CFLAGS)

# Path
Path.o: Path/Path.cpp PathControler.o
	$(CC) -c Path/Path.cpp $(CFLAGS)

PathControler.o: Path/PathControler.cpp PathModel.o
	$(CC) -c Path/PathControler.cpp $(CFLAGS)

PathModel.o: Path/PathModel.cpp Hit.o
	$(CC) -c Path/PathModel.cpp $(CFLAGS)

# ProgressBar
ProgressBar.o: ProgressBar/ProgressBar.cpp ProgressBarThread.o
	$(CC) -c ProgressBar/ProgressBar.cpp $(CFLAGS)

ProgressBarThread.o: ProgressBar/ProgressBarThread.cpp
	$(CC) -c ProgressBar/ProgressBarThread.cpp $(CFLAGS)

# Fasta
Fasta.o: Fasta/Fasta.cpp FastaControler.o FastaThread.o
	$(CC) -c Fasta/Fasta.cpp $(CFLAGS)

FastaControler.o: Fasta/FastaControler.cpp FastaModel.o
	$(CC) -c Fasta/FastaControler.cpp $(CFLAGS)

FastaModel.o: Fasta/FastaModel.cpp Sequence.o
	$(CC) -c Fasta/FastaModel.cpp $(CFLAGS)

FastaThread.o: Fasta/FastaThread.cpp Sequence.o
	$(CC) -c Fasta/FastaThread.cpp $(CFLAGS)

Sequence.o: Fasta/Sequence.cpp
	$(CC) -c Fasta/Sequence.cpp $(CFLAGS)

# HitList
HitList.o: HitList/HitList.cpp HitListControler.o
	$(CC) -c HitList/HitList.cpp $(CFLAGS)

HitListControler.o: HitList/HitListControler.cpp HitListModel.o
	$(CC) -c HitList/HitListControler.cpp $(CFLAGS)

HitListModel.o: HitList/HitListModel.cpp Hit.o
	$(CC) -c HitList/HitListModel.cpp $(CFLAGS)

# Hit
Hit.o: Hit/Hit.cpp HitControler.o
	$(CC) -c Hit/Hit.cpp $(CFLAGS)

HitControler.o: Hit/HitControler.cpp HitModel.o
	$(CC) -c Hit/HitControler.cpp $(CFLAGS)

HitModel.o: Hit/HitModel.cpp
	$(CC) -c Hit/HitModel.cpp $(CFLAGS)

myThread.o: myThread/myThread.cpp
	$(CC) -c myThread/myThread.cpp $(CFLAGS)

clean:
	rm -rf *.o htdetect
