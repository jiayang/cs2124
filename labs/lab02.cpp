//Jiayang Chen -- Lab02 Hydrocarbons


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//A hydrocarbon with vector of names, # of carbons, and # of hydrogens
struct Hydrocarbon {
    Hydrocarbon(const string& aName, int numCarbons, int numHydrogens)
        : names{aName}, carbons(numCarbons), hydrogens(numHydrogens) {}
    
    vector<string> names;
    int carbons;
    int hydrogens;

};

size_t findPos(const vector<Hydrocarbon>& formulas, int carbons, int hydrogens);
void addFormula(vector<Hydrocarbon>& formulas, const string& formulaName,
                int carbons, int hydrogens);
void openFile(ifstream& ifs);
void parseStream(ifstream& ifs, vector<Hydrocarbon>& formulas);
bool lessThan(const Hydrocarbon& a, const Hydrocarbon& b);
void sortFormulas(vector<Hydrocarbon>& formulas);
void printVectorOfHydrocarbons(const vector<Hydrocarbon>& formulas);

//Check if there already is an entry with same number of C's and H's in vector
//i = vector.size() means could not find
size_t findPos(const vector<Hydrocarbon>& formulas, int carbons, int hydrogens) {
    size_t i = 0;
    while (i < formulas.size()) {
        const Hydrocarbon& formula = formulas[i];
        //If the carbons match
        if (formula.carbons == carbons && formula.hydrogens == hydrogens) {
            return i;
        }
        ++i;
    }
    //i is equal to formulas.size()
    return i;
}

//Adds a formula to the vector of hydrocarbons
void addFormula(vector<Hydrocarbon>& formulas, const string& formulaName,
                int carbons, int hydrogens) {

    //Get the position to add the information
    size_t i = findPos(formulas, carbons,hydrogens);

    //If we need to add it to the end
    if (i == formulas.size()) {
        Hydrocarbon newHydrocarbon(formulaName, carbons, hydrogens);
        formulas.push_back(newHydrocarbon);
    } else {
        Hydrocarbon& formula = formulas[i];
        formula.names.push_back(formulaName);
    }
    
}

//Asks user for name of file, keep trying until successful
void openFile(ifstream& ifs) {
    string fileName;
    //Ask user for name of file, keep trying until successful
    do {
        cout << "Name of the file?: ";
        cin >> fileName;
        ifs.open(fileName);
    } while (!ifs);
}

//Fills the vector by reading from stream
void parseStream(ifstream& ifs, vector<Hydrocarbon>& formulas) {
    //Keep reading the names of the formulas
    string formulaName;
    int carbons;
    int hydrogens;
    char separator;
    while (ifs >> formulaName) {
        //Move ifs pointer past first character ('C'), then H
        ifs >> separator >> carbons;
        ifs >> separator >> hydrogens;
        addFormula(formulas, formulaName, carbons, hydrogens);
    }

}

//Compares two hydrocarbons, returns true if a belongs before (less than) b
bool lessThan(const Hydrocarbon& a, const Hydrocarbon& b) {
    return (a.carbons != b.carbons && a.carbons > b.carbons)
        || (a.hydrogens > b.hydrogens);

}

//Sorts the vector first by carbon, then by hydrogen
//BUBBLESORT
void sortFormulas(vector<Hydrocarbon>& formulas) {
    //Perform formulas.size() - 1 number of iterations
    for (size_t i = 0; i < formulas.size() - 1; ++i) {
        //Start from beginning and go to end of unsorted region
        for (size_t j = 0; j < formulas.size() - i - 1; ++j) {
            Hydrocarbon& first = formulas[j];
            Hydrocarbon& second = formulas[j+1];
            //If we need to swap,
            if (!lessThan(first,second)) {
                Hydrocarbon temp = formulas[j];
                formulas[j] = second;
                formulas[j+1] = temp;
            }
        }
    }

}

//Prints the vector of hydrocarbons
void printVectorOfHydrocarbons(const vector<Hydrocarbon>& formulas) {
    for (const Hydrocarbon& hydrocarbon : formulas) {
        cout << 'C' << hydrocarbon.carbons
             << 'H' << hydrocarbon.hydrogens << ' ';
        for (const string& name : hydrocarbon.names) {
            cout << name << ' ';
        }
        cout << endl;
    }
    
}

int main() {
    vector<Hydrocarbon> formulas;
    ifstream ifs;
    openFile(ifs);
    
    parseStream(ifs, formulas);

    sortFormulas(formulas);

    printVectorOfHydrocarbons(formulas);
}
