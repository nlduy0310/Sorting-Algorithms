#include "parser.h"
#include "caller.h"
#include "generator.h"
#include "io.h"
#include "constant.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

const string split = "----------------------------------------------------------------------------------";

void Parser::Init(int argc, char **argv)
{
    if (argc > 0)
        for (int i = 0; i < argc; i++)
            this->arguments_.push_back(string{argv[i]});
}

Parser::Parser(int argc, char **argv)
{
    Parser::Init(argc, argv);
}

void Parser::Parse()
{
    try
    {
        if (this->arguments_.empty() || this->arguments_.size() < 5)
            throw invalid_argument("More arguments expected");

        if (this->arguments_[1] == "-a")
        {
            // ALGORITHM MODE
            cout << "\n"
                 << split << "\n"
                 << endl;
            cout << "ALGORITHM MODE" << endl;
            string algorithm = this->arguments_[2];
            cout << "Algorithm: " << algorithm << endl;

            int *array = nullptr, size = 0;
            unsigned long long comps = 0;
            bool show_time = false, show_comps = false;
            chrono::duration<double, milli> run_time;

            if (this->arguments_[3].find(".") != string::npos)
            {
                // READ INPUT FILE
                string ifile_path = this->arguments_[3];
                cout << "Input File: " << ifile_path << endl;
                for (int i = 4; i < this->arguments_.size(); i++)
                {
                    if (this->arguments_[i] == "-both")
                        show_time = show_comps = true;
                    else if (this->arguments_[i] == "-time")
                        show_time = true;
                    else if (this->arguments_[i] == "-comp")
                        show_comps = true;
                }

                if (!Reader::Read(ifile_path, array, size))
                    throw runtime_error("Can't read input file");

                cout << "Input Size: " << size << endl;

                if (!FunctionCaller::Find(algorithm))
                    throw invalid_argument("Invalid algorithm");

                cout << split << endl;
                auto start = chrono::high_resolution_clock::now();
                FunctionCaller::Run(algorithm, array, size, comps);
                auto end = chrono::high_resolution_clock::now();

                run_time = end - start;
                if (show_time)
                    cout << "Run Time: " << run_time.count() << " ms" << endl;
                if (show_comps)
                    cout << "Comparisions: " << comps << endl;

                Exporter::Export("output.txt", array, size, 1);

                if (array)
                    delete[] array;
            }
            else
            {
                // GENERATE DATA

                // get input size
                size = stoi(this->arguments_[3]);
                if (size <= 0)
                    throw invalid_argument("Invalid size");
                cout << "\nInput Size: " << size << endl;

                // get input order(s)
                auto cit = find(kInputOrders.begin(), kInputOrders.end(), this->arguments_[4]);
                vector<int> input_order;
                if (cit != kInputOrders.end())
                    input_order.push_back((int)(cit - kInputOrders.begin()));
                else
                {
                    input_order.push_back(0);
                    input_order.push_back(1);
                    input_order.push_back(2);
                    input_order.push_back(3);
                }

                // get output params
                for (int i = 4; i < this->arguments_.size(); i++)
                {
                    if (this->arguments_[i] == "-both")
                        show_time = show_comps = true;
                    else if (this->arguments_[i] == "-time")
                        show_time = true;
                    else if (this->arguments_[i] == "-comp")
                        show_comps = true;
                }

                // generate array
                for (int i = 0; i < input_order.size(); i++)
                {
                    cout << "\nInput Order: " << kInputOrders[input_order[i]] << endl;

                    // allocate array
                    array = new int[size];
                    if (!array)
                        throw runtime_error("Failed to allocate memory");

                    GenerateData(array, size, input_order[i]);

                    // export generated input
                    if (input_order.size() == 1)
                        Exporter::Export("input.txt", array, size, 1);
                    else
                        switch (input_order[i])
                        {
                        case 0:
                            Exporter::Export("input_1.txt", array, size, 1);
                            break;
                        case 1:
                            Exporter::Export("input_3.txt", array, size, 1);
                            break;
                        case 2:
                            Exporter::Export("input_4.txt", array, size, 1);
                            break;
                        case 3:
                            Exporter::Export("input_2.txt", array, size, 1);
                            break;
                        default:
                            break;
                        }

                    if (!FunctionCaller::Find(algorithm))
                        throw invalid_argument("Invalid algorithm");

                    // sort the array
                    cout << split << endl;
                    auto start = chrono::high_resolution_clock::now();
                    FunctionCaller::Run(algorithm, array, size, comps);
                    auto end = chrono::high_resolution_clock::now();

                    if (input_order.size() == 1)
                        Exporter::Export("output.txt", array, size, 1);

                    // show time and comps
                    run_time = end - start;
                    if (show_time)
                        cout << "Run Time: " << run_time.count() << " ms" << endl;
                    if (show_comps)
                        cout << "Comparisions: " << comps << endl;

                    comps = 0;
                    delete[] array;
                }
            }
        }
        else if (this->arguments_[1] == "-c")
        {
            // COMPARE MODE
            cout << "COMPARE MODE" << endl;
            int *array1 = nullptr, size1 = 0;
            int *array2 = nullptr, size2 = 0;
            unsigned long long comps1 = 0, comps2 = 0;
            chrono::duration<double, milli> time1, time2;

            // get algorithm names
            string algorithm1 = this->arguments_[2], algorithm2 = this->arguments_[3];
            if (!FunctionCaller::Find(algorithm1) || !FunctionCaller::Find(algorithm2))
                throw invalid_argument("Invalid algorithm(s)");

            cout << "Algorithms: " << algorithm1 << " | " << algorithm2 << endl;

            // check input mode
            if (arguments_[4].find(".") != string::npos)
            {
                // read from file
                string ifile_path = arguments_[4];
                cout << "File Path: " << ifile_path << endl;

                if (!Reader::Read(ifile_path, array1, size1) || !Reader::Read(ifile_path, array2, size2))
                {
                    if (array1)
                        delete[] array1;
                    if (array2)
                        delete[] array2;
                    throw runtime_error("Can't read input file");
                }

                cout << "Input Size: " << size1 << "\n"
                     << split << endl;

                // begin sorting
                auto start = chrono::high_resolution_clock::now();
                FunctionCaller::Run(algorithm1, array1, size1, comps1);
                auto end = chrono::high_resolution_clock::now();
                time1 = end - start;

                start = chrono::high_resolution_clock::now();
                FunctionCaller::Run(algorithm2, array2, size2, comps2);
                end = chrono::high_resolution_clock::now();
                time2 = end - start;

                delete[] array1;
                delete[] array2;
            }
            else
            {
                // generate data

                // get input size
                size1 = stoi(this->arguments_[4]);
                if (size1 <= 0)
                    throw invalid_argument("Invalid input size");
                size2 = size1;
                cout << "Input Size: " << size1 << endl;

                // get input order
                if (this->arguments_.size() <= 5)
                    throw invalid_argument("Missing input order");
                auto cit = find(kInputOrders.begin(), kInputOrders.end(), this->arguments_[5]);
                if (cit == kInputOrders.end())
                    throw invalid_argument("Invalid input order");
                int input_order = (int)(cit - kInputOrders.begin());
                cout << "Input Order: " << kInputOrders[input_order] << "\n"
                     << split << endl;

                // allocate memory
                array1 = new int[size1];
                array2 = new int[size2];
                if (!array1 || !array2)
                {
                    if (array1)
                        delete[] array1;
                    if (array2)
                        delete[] array2;
                    throw runtime_error("Failed to allocate memory");
                }

                // generate data
                GenerateData(array1, size1, input_order);
                for (int i = 0; i < size2; i++)
                    array2[i] = array1[i];

                // export generated data
                Exporter::Export("input.txt", array1, size1, 1);

                auto start = chrono::high_resolution_clock::now();
                FunctionCaller::Run(algorithm1, array1, size1, comps1);
                auto end = chrono::high_resolution_clock::now();
                time1 = end - start;

                start = chrono::high_resolution_clock::now();
                FunctionCaller::Run(algorithm2, array2, size2, comps2);
                end = chrono::high_resolution_clock::now();
                time2 = end - start;

                delete[] array1;
                delete[] array2;
            }

            cout << "Run time: " << time1.count() << " | " << time2.count() << " (ms)" << endl;
            cout << "Comparisions: " << comps1 << " | " << comps2 << endl;
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
        return;
    }
}
