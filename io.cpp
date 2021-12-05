#include "io.h"

#include <iostream>
#include <fstream>

using namespace std;

bool Exporter::Export(string file_path, int array[], int size, int mode)
{
    try
    {
        ofstream out_file(file_path, ios_base::out);

        if (out_file.is_open() && out_file.good())
        {
            if (array && size > 0)
            {
                if (mode == 1)
                    out_file << size << endl;

                for (int i = 0; i < size; i++)
                    out_file << array[i] << " ";

                out_file << endl;
            }
            else
                throw invalid_argument("Loi khi truy cap mang");

            out_file.close();
        }
        else
            throw invalid_argument("Loi khi mo file: filename=" + file_path);
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}

bool Reader::Read(string file_path, int *&array, int &size)
{
    if (array)
    {
        delete[] array;
        array = nullptr;
    }

    try
    {
        ifstream in_file(file_path, ios_base::in);
        if (!in_file.is_open() || in_file.bad())
            throw invalid_argument("Loi khi mo file: filename=" + file_path);

        in_file >> size;
        if (size <= 0)
            throw invalid_argument("Loi khi doc file " + file_path + ", kich thuoc mang khong hop le: size=" + to_string(size));

        array = new int[size];
        if (!array)
            throw runtime_error("Loi khi cap phat vung nho");

        for (int i = 0; i < size; i++)
            in_file >> array[i];

        in_file.close();
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}