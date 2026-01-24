// This program takes in the user data for: Their name; How many days they birded; How many hours they birded; How many birds they saw; and if it is winter or not.
// This program outputs if the user had a good or bad birding day as well as a table of the user's statistics.

//io stream is for inputs/outputs; string is for strings ; iomanip is to manipulate input/output data; fstream is to send and recieve data from files; windows.h is to help set colors to text.
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>

// namespace is used to remove std:: before statements; hConsole is used to change text color; enum season is a user defined function to figure out what season it is
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
enum season { Winter, Spring, Summer, Fall };

// class for birdtracker is used to store user's name, how many days they went birding, hours they went birding, birds they saw, and the average amount of birds they saw per hour.
// in the private modifier it has the daycheck array and uses setDayCheck to set the days they went birding and getDayCheck is made to display/give that data later on.
class birdtracker {

public:
    struct birdstats {
        string username;
        int daysbirding = 0;
        double hoursbirding;
        int birdsseen;
        double hourlybirds;
        bool winter = false;
    };

    season convertenum(const string& seasonAnswer) const {
        if (seasonAnswer == "Winter")
            return Winter;
        if (seasonAnswer == "Spring")
            return Spring;
        if (seasonAnswer == "Summer")
            return Summer;
        if (seasonAnswer == "Fall")
            return Fall;
        return Winter;
    }

    void setDayCheck(int day, bool wentBirding) {
        if (day >= 0 && day < 7) daycheck[day] = wentBirding;
    }

    bool getDayCheck(int day) const {
        if (day >= 0 && day < 7) return daycheck[day];
        return false;
    }

private:
    bool daycheck[7];

};

class birdtracker;

void printtable(const birdtracker::birdstats& user, const birdtracker& tracker, int week);

int main()
{
    // variables declared at the start of main, such as using the birdtracker class and assigning it to tracker as well as declaring birdstats within birdtracker and assigning it to user.
    birdtracker tracker;
    birdtracker::birdstats user;
    const int week = 7;
    int day;
    string seasonanswer;

    // ********** USER INPUT STATEMENTS **********

    cout << "Welcome! Please input your first name!\n";
    cin >> user.username;

    for (int day = 0; day < week; day++) {
        bool wentBirding;
        cout << "Did you go birding today? Type 1 if Yes Type 0 if No\n";
        cin >> wentBirding;
        tracker.setDayCheck(day, wentBirding);
        user.daysbirding += wentBirding;
    }

    do {
        cout << "How many hours did you go birding?\n";
        cin >> user.hoursbirding;
    } while (user.hoursbirding <= 0 || user.hoursbirding >= 168);

    cout << "How many birds did you see in total?\n";
    cin >> user.birdsseen;
    while (user.birdsseen <= 0) {
        cin.clear();
        cin.ignore(200, '\n');
        cout << "Enter a number: \n";
        cin >> user.birdsseen;
        "\n";
    }

    cout << "Enter the current season (Winter, Spring, Summer, or Fall):\n";
    cin >> seasonanswer;

    // ********** SWITCH STATEMENT **********

    season seasonentered = tracker.convertenum(seasonanswer);

    switch (seasonentered) {
    case Winter:
        user.winter = true;
        break;
    case Spring:
        user.winter = false;
        break;
    case Summer:
        user.winter = false;
        break;
    case Fall:
        user.winter = false;
        break;
    }

    // ********** CALCULATIONS **********

    user.hourlybirds = user.birdsseen / user.hoursbirding;

    cout << fixed << setprecision(2);

    // ********** OUTPUT STATEMENT **********

    if (user.hourlybirds >= 10 && user.winter == true) {
        cout << "You had a good birding day, even though it was winter!" << endl;
    }
    else if (user.hourlybirds <= 10 && user.winter == true) {
        cout << "Winter is a tough time for birding, it's okay." << endl;
    }
    else if (user.hourlybirds >= 10 && user.winter == false) {
        cout << "You had a good birding day!" << endl;
    }
    else if (user.hourlybirds <= 10 && user.winter == false) {
        cout << "You had a bad birding day." << endl;
    }

    // ********** PRINTTABLE FUNCTION **********

    printtable(user, tracker, week);

    // ********** RETURN VALUE **********

    return 0;
}

// ********** PRINTTABLE OUTPUT **********

void printtable(const birdtracker::birdstats& user, const birdtracker& tracker, int week) {

    SetConsoleTextAttribute(hConsole, 13);
    cout << setw(30) << setfill('*') << "" << setfill(' ') << endl;
    SetConsoleTextAttribute(hConsole, 7);
    cout << "   " << setw(1) << "User's Name :" << setw(11) << user.username << endl;
    cout << "   " << setw(1) << "Days Birding :" << setw(10) << user.daysbirding << endl;
    cout << "   " << setw(1) << "Hours Birding :" << setw(9) << user.hoursbirding << endl;
    cout << "   " << setw(1) << "Bird Seen :" << setw(13) << user.birdsseen << endl;
    cout << "   " << setw(1) << "Average Birds :" << setw(9) << user.hourlybirds << endl;
    SetConsoleTextAttribute(hConsole, 13);
    cout << setw(30) << setfill('*') << "" << endl;
    SetConsoleTextAttribute(hConsole, 7);

    for (int day = 0; day < week; day++) {
        cout << "Day: " << day + 1 << " ";
        if (tracker.getDayCheck(day)) {
            cout << "Went Birding\n";
        }
        else {
            cout << "Did Not Go Birding\n";
        }
    }

    // ********** OUTPUT DATA **********

    ofstream outFile;

    outFile.open("report.txt");
    outFile << setw(30) << setfill('*') << "" << setfill(' ') << endl;
    outFile << "   " << setw(1) << "User's Name :" << setw(11) << user.username << endl;
    outFile << "   " << setw(1) << "Days Birding :" << setw(10) << user.daysbirding << endl;
    outFile << "   " << setw(1) << "Hours Birding :" << setw(9) << user.hoursbirding << endl;
    outFile << "   " << setw(1) << "Bird Seen :" << setw(13) << user.birdsseen << endl;
    outFile << "   " << setw(1) << "Average Birds :" << setw(9) << user.hourlybirds << endl;
    outFile << setw(30) << setfill('*') << "" << endl;
    outFile.close();
}
