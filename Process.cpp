#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

int tests, AC, WA, failed;
long double scores;
const string compileFlags = "-std=c++14 -pipe -O2 -s -static -lm -x c++ -DTHEMIS -Wl,-z,stack-size=66060288";

int Compile() {
    if (system(("g++ InputGen.cpp -o InputGen " + compileFlags).c_str()) != 0) {
        cout << RED << "InputGen is not compiled (compile failed)" << RESET << '\n';
        return 1;
    } else {
        cout << GREEN << "Compiled input generating file!" << RESET << '\n';
    }

    if (system(("g++ AC.cpp -o AC " + compileFlags).c_str()) != 0) {
        cout << RED << "AC code is not compiled (compile failed)" << RESET << '\n';
        return 1;
    } else {
        cout << GREEN << "Compiled AC file!" << RESET << '\n';
    }

    if (system(("g++ WA.cpp -o WA " + compileFlags).c_str()) != 0) {
        cout << RED << "WA code is not compiled (compile failed)" << RESET << '\n';
        return 1;
    } else {
        cout << GREEN << "Compiled WA file!" << RESET << '\n';
    }

    return 0;
}

void Run(const int& testCase) {
    #ifdef WIN32
    if (system(".\\InputGen > Input.inp") != 0) {
        cout << RED << testCase << ". InputGen is RTE" << RESET << '\n';
        ++failed;
        return;
    }

    if (system(".\\AC < Input.inp > AC.ans") != 0) {
        cout << RED << testCase << ". AC is RTE" << RESET << '\n';
        ++failed;
        return;
    }

    if (system(".\\WA < Input.inp > Output.out") != 0) {
        cout << RED << testCase << ". WA is RTE" << RESET << '\n';
        ++failed;
        return;
    }
    #else
    if (system("./InputGen > Input.inp") != 0) {
        cout << RED << testCase << ". InputGen is RTE" << RESET << '\n';
        ++failed;
        return;
    }

    if (system("./AC < Input.inp > AC.ans") != 0) {
        cout << RED << testCase << ". AC is RTE" << RESET << '\n';
        ++failed;
        return;
    }

    if (system("./WA < Input.inp > Output.out") != 0) {
        cout << RED << testCase << ". WA is RTE" << RESET << '\n';
        ++failed;
        return;
    }
    #endif

    #ifdef WIN32
    if (system("fc /W AC.ans Output.out > nul 2>&1") == 0) {
    #else
    if (system("diff -wB AC.ans Output.out > /dev/null 2>&1") == 0) {
    #endif
        cout << GREEN << testCase << ". AC" << RESET << '\n';
        AC++;
        scores += 100.0 / tests;
    } else {
        cout << RED << testCase << ". WA" << RESET << '\n';
        ++WA;
        ofstream outFile("WA.txt", ios::app);
        outFile << "Test case #" << testCase << "\n";
        ifstream inFile("Input.inp");
        outFile << inFile.rdbuf();
        outFile << "\n\n";

        outFile << "Answer:\n";
        ifstream ansFile("AC.ans");
        outFile << ansFile.rdbuf();
        outFile << "\n\n";
    }
}

void CleanUp() {
    #ifdef WIN32
    if (system("del InputGen.exe AC.exe WA.exe Input.inp Output.out AC.ans") != 0)
    #else
    if (system("rm InputGen AC WA Input.inp Output.out AC.ans") != 0)
    #endif
        cout << YELLOW << "Can't delete build and input files" << RESET << '\n';
}

signed main() {
    cout << BLUE << "Enter number of test cases: " << RESET;
    cin >> tests;

    if (Compile() != 0) {
        cout << RED << "Compilation failed, no more operation to do" << RESET << '\n';
        return 1;
    }

    // Flash the wrong answer file record.
    ofstream outFile("WA.txt");
    outFile.close();

    for (int _ = 1; _ <= tests; _++)
        Run(_);

    cout << YELLOW << "Scores: " << fixed << setprecision(2) << scores << "/100" << RESET << '\n';
    cout << GREEN << "Total AC: " << AC << RESET << '\n';
    cout << RED << "Total WA: " << WA << RESET << '\n';
    cout << YELLOW << "Failed Process(es): " << failed << RESET << '\n';
    CleanUp();
    return 0;
}
