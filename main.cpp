#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int Get_Count(vector<string> lines, int part) {
    string line;
    char chr;
    map<char, int> yes;
    vector<char> keys;
    char key;
    int yeses = 0;  //number of yeses for part 2

    for (int l = 0; l < lines.size(); l++) {
        line = lines[l];
        for (int c = 0; c < line.size(); c++) {
            chr = line[c];

            //part 1
            if (part == 1) {
                yes[chr] = 1;    //(counts each letter only once)
            }
            //part 2
            else {
                if (!yes[chr]) {
                    keys.push_back(chr);    //store the char for later
                    yes[chr] = 1;
                }
                else {
                    yes[chr] += 1;
                }
            }
        }
    }

    //more part 1
    if (part == 1) {
        return yes.size();
    }

    //more part 2
    else {
        for (int k = 0; k < keys.size(); k++) {
            key = keys[k];
            //only count the char if it was in every line
            if (yes[key] == lines.size()) {
                yeses++;
            }
        }

        return yeses;
    }

}

///Gets the total amount of yeses and stores it in 'yes'
void Get_Yes(int *yes, int part = 1) {
    ifstream file;
    string line;
    vector<string> lines;
    int single = 0; //holds the yes count for each group

    file.open("yes.txt");

    getline(file, line);
    while (file) {
        if (line == "") {
            (*yes) += Get_Count(lines, part);
            lines.clear();
        }
        else {
            lines.push_back(line);  //add the line for the current group
        }

        getline(file, line);
    }
    //gets the last yes count
    (*yes) += Get_Count(lines, part);

    file.close();

    return;
}

int main()
{
    int yes_count = 0;

    Get_Yes(&yes_count);

    cout << "Part 1 Total Yes Count: " << yes_count << endl;

    yes_count = 0;
    Get_Yes(&yes_count, 2);

    cout << "Part 2 Total Yes Count: " << yes_count << endl;

    return 0;
}
