// This program takes in the user data for: Their name; How many hours they birded; How many birds they saw; and Outputs the average amount of birds seen per hour.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    ofstream outFile;
    string username;
    double hoursbirding;
    int birdsseen;
    double hourlybirds;

    // ********** USER INPUT STATEMENTS **********

    cout << "Welcome! Please input your first name!\n";
    cin >> username;
    cout << "How many hours did you spend birding this week?\n";
    cin >> hoursbirding;
    if (hoursbirding <= 0) {
        cin.clear();
        cin.ignore(200, '\n');
        cout << "Enter a number: \n";
        cin >> hoursbirding;
        "\n";
    }
    else {
        "\n";
    }
    cout << "How many birds did you see in total?\n";
    cin >> birdsseen;
    if (birdsseen <= 0) {
        cin.clear();
        cin.ignore(200, '\n'); 
        cout << "Enter a number: \n";
        cin >> birdsseen;
        "\n";
    }
    else {
        "\n";
    }

    // ********** CALCULATIONS **********

    hourlybirds = birdsseen / hoursbirding;

    // ********** OUTPUT STATEMENT **********

    cout << setprecision(3);
    cout << "\nYou saw " << hourlybirds << " birds on average each hour this week! Congrats " << username << "!\n" << endl;

    // ********** TABLE PRINTOUT **********
    
    cout << setw(30) << setfill('*') << "" << setfill(' ') << endl;
    cout << "   " << setw(1) << "User's Name :" << setw(11) << username << endl;
    cout << "   " << setw(1) << "Hours Birded :" << setw(10) << hoursbirding << endl;
    cout << "   " << setw(1) << "Bird Seen :" << setw(13) << birdsseen << endl;
    cout << "   " << setw(1) << "Average Birds :" << setw(9) << hourlybirds << endl;
    cout << setw(30) << setfill('*') << "" << endl;
    
    // ********** OUTPUT DATA **********

    outFile.open("report.txt");
    outFile << setw(30) << setfill('*') << "" << setfill(' ') << endl;
    outFile << "   " << setw(1) << "User's Name :" << setw(11) << username << endl;
    outFile << "   " << setw(1) << "Hours Birded :" << setw(10) << hoursbirding << endl;
    outFile << "   " << setw(1) << "Bird Seen :" << setw(13) << birdsseen << endl;
    outFile << "   " << setw(1) << "Average Birds :" << setw(9) << hourlybirds << endl;
    outFile << setw(30) << setfill('*') << "" << endl;
    outFile.close();

    // ********** RETURN VALUE **********

    return 0;
}
