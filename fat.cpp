/**
 * FAT - file augment tool
 *
 * Miloslav Číž, 2015
 *
 * tool for file enlargement
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define EXPANSION_RATIO 10   // how many times the output will be bigger

int main(int argc, char **argv)
  {
    if (argc != 2)
      {
        cerr << "error: bad number of arguments.";
        return 1;
      }

    string argument = argv[1];

    if (argument.compare("-h") == 0 || argument.compare("--help") == 0)
      {
        cout << "fat - file augment tool\n";
        cout << "usage: fat filename\n";
        cout << "Miloslav Ciz, 2015\n";
        return 0;
      }

    bool expand = !(argument.length() >= 4 &&
        argument.substr(argument.length() - 4).compare(".fat") == 0);

    string input_name, output_name;

    if (expand)
      {
        input_name = argument;
        output_name = argument + ".fat";
      }
    else
      {
        input_name = argument;
        output_name = argument.substr(0,argument.length() - 4);
      }

    ifstream input_file(input_name,ios::binary);

    if (!input_file.is_open())
      {
        cerr << "error: the input file couldn't be opened.\n";
        return 1;
      }

    ofstream output_file(output_name,ios::binary);

    if (!output_file.is_open())
      {
        cerr << "error: couldn't create a new file.\n";
        input_file.close();
        return 1;
      }

    char buffer[512];
    int i, j;

    if (expand)
      {
        // expand:
        unsigned char random_byte;

        while (true)
          {
            if (!input_file)
              break;

            input_file.read(buffer,sizeof(buffer));

            for (i = 0; i < input_file.gcount(); i++)
              {
                output_file << buffer[i];

                for (j = 0; j < EXPANSION_RATIO - 1; j++) // random fill
                  {
                    random_byte = rand() % 256;
                    output_file.write((const char *) &random_byte,1);
                  }
              }
          }
      }
    else
      {
        // unexpand:
        int counter = 0;

         while (true)
          {
            if (!input_file)
              break;

            input_file.read(buffer,sizeof(buffer));

            for (i = 0; i < input_file.gcount(); i++)
              {
                if (counter == 0)
                  {
                    output_file.write((const char *) &buffer[i],1);
                    counter++;
                  }
                else
                  {
                    if (counter >= EXPANSION_RATIO - 1)
                      counter = 0;
                    else
                      counter++;
                  }
              }
          }
      }

    input_file.close();
    output_file.close();

    return 0;
  }
