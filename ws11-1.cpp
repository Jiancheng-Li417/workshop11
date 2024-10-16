#include <iostream>  
#include <fstream>  
#include <string>  
#include <vector>  
#include <stdexcept> // for std::runtime_error  
using namespace std;

// vector of int.  
// used to store the records  
typedef vector<int> Records;

// https://www.cplusplus.com/doc/tutorial/files/  
class RecordsManager {
private:
    fstream _file;
    string _filename;

public:
    RecordsManager(string filename) : _filename(filename) {}
    void read(Records& records) {
        _file.open(_filename, ios::in);
        if (_file.is_open()) {
            string line;
            try {
                while (std::getline(_file, line)) {
                    try {
                        records.push_back(stoi(line));
                    }
                    catch (const invalid_argument& e) {
                        _file.close();
                        throw runtime_error("Invalid argument when reading the file: " + line + ". Error: " + e.what());
                    }
                    catch (const out_of_range& e) {
                        _file.close();
                        throw runtime_error("Out of range when reading the file: " + line + ". Error: " + e.what());
                    }
                }
            }
            catch (...) {
                _file.close();
                throw; 
            }
            _file.close();
        }
        else {
            throw runtime_error("Unable to open file: " + _filename);
        }
    }
};

int main() {
    try {
        // Uncomment one of the following lines to test with different files  
        //RecordsManager receordM("test_clean.txt");
         //RecordsManager receordM("test_corrupt1.txt");  
         RecordsManager receordM("test_corrupt2.txt");  

        Records myRecords;
 
        // reads records  
        receordM.read(myRecords);

        // calculate and print out the sum  
        int sum = 0;
        for (int i = 0; i < myRecords.size(); i++) {
            sum += myRecords[i];
        }
        cout << sum << endl;
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}