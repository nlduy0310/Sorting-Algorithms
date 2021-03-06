#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>

void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);

#endif