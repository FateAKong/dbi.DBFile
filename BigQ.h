/*
 * BigQ.h
 *
 *  Created on: Feb 13, 2013
 *      Author: Fate.AKong
 */

#ifndef BIGQ_H_
#define BIGQ_H_

#include <list>
#include <vector>
#include  <queue>
#include <pthread.h>
#include "Pipe.h"

class BigQ {
private:
	pthread_t workerThrd;		// worker thread
	void *workerFunc();		// worker function
	static void *workerHelper(void *);		// helper function to cast a member function to the type that pthread could use
	void exportSortedRun();

	Pipe& inputPipe;
	Pipe& outputPipe;
	OrderMaker& sortOrder;

	// TODO initial the buffer
//	Page buffer[my_runLength];
	int runLenInBytes;
	Page pageBuf;
	list<Record> listBuf;
	vector<int> runStartPage;
	File sortedRuns;
//	buf.reserve(1024);
public:
	BigQ(Pipe &inputPipe, Pipe &outputPipe, OrderMaker	&sortOrder, int runLength);
};

#endif /* BIGQ_H_ */