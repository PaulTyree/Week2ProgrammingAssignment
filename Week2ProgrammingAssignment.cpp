// This program takes in the user data for: Their name; How many days they birded; How many hours they birded; How many birds they saw; and if it is winter or not.
// This program outputs if the user had a good or bad birding day as well as a table of the user's statistics.
#ifdef _DEBUG
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#endif

// ********** INCLUDE STATEMENTS **********
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>

// namespace is used to remove std:: before statements; hConsole is used to change text color; enum season is a user defined function to figure out what season it is
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
enum season { Winter, Spring, Summer, Fall };

class birdtracker {
public:
    // struct in order to declare variables
    struct birdstats {
        string username;
        int daysbirding = 0;
        double hoursbirding = 0;
        int birdsseen = 0;
        double hourlybirds = 0;
        bool winter = false;
    };

    // convert the string "seasonanswer" to an enum
    season convertenum(const string& seasonAnswer) const {
        if (seasonAnswer == "Winter") return Winter;
        if (seasonAnswer == "Spring") return Spring;
        if (seasonAnswer == "Summer") return Summer;
        if (seasonAnswer == "Fall") return Fall;
        return Winter;
    }

    // tracker for days went birding
    void setDayCheck(int day, bool wentBirding) {
        if (day >= 0 && day < 7) daycheck[day] = wentBirding;
    }

    // way to display the days going birding
    bool getDayCheck(int day) const {
        if (day >= 0 && day < 7) return daycheck[day];
        return false;
    }

    // reworked to allow testing in doctest
    double calculateHourlyBirds(const birdstats& stats) const {
        if (stats.hoursbirding <= 0) return 0;
        return stats.birdsseen / stats.hoursbirding;
    }

    // if hourlybirds is greater than or equal to 10, then the user had a good birding day
    bool hadGoodDay(const birdstats& stats) const {
        return stats.hourlybirds >= 10;
    }

    // used in order to test in doctest
    void addSession(birdstats& stats, double hours, int birds) {
        stats.daysbirding += 1;
        stats.hoursbirding += hours;
        stats.birdsseen += birds;
        stats.hourlybirds = calculateHourlyBirds(stats);
    }

    // sets all of daycheck to false so it can be tested in doctest
private:
    bool daycheck[7]{ false };
};

// ********** PRINTTABLE FUNCTION + TESTING **********
void printtable(const birdtracker::birdstats& user, const birdtracker& tracker, int week) {

    // ********** DEBUG SKIP + PRINTTABLE OUTPUTS **********
#ifdef _DEBUG
    // void to skip printing the table in debug mode
#else 
    SetConsoleTextAttribute(hConsole, 13);
    cout << setw(30) << setfill('*') << "" << setfill(' ') << endl;
    SetConsoleTextAttribute(hConsole, 7);
    cout << "   User's Name :" << setw(11) << user.username << endl;
    cout << "   Days Birding :" << setw(10) << user.daysbirding << endl;
    cout << "   Hours Birding :" << setw(9) << user.hoursbirding << endl;
    cout << "   Birds Seen :" << setw(13) << user.birdsseen << endl;
    cout << "   Average Birds :" << setw(9) << user.hourlybirds << endl;
    SetConsoleTextAttribute(hConsole, 13);
    cout << setw(30) << setfill('*') << "" << endl;
    SetConsoleTextAttribute(hConsole, 7);

    for (int day = 0; day < week; day++) {
        cout << "Day: " << day + 1 << " ";
        cout << (tracker.getDayCheck(day) ? "Went Birding\n" : "Did Not Go Birding\n");
    }

    ofstream outFile("report.txt");
    outFile << setw(30) << setfill('*') << "" << setfill(' ') << endl;
    outFile << "   User's Name :" << setw(11) << user.username << endl;
    outFile << "   Days Birding :" << setw(10) << user.daysbirding << endl;
    outFile << "   Hours Birding :" << setw(9) << user.hoursbirding << endl;
    outFile << "   Birds Seen :" << setw(13) << user.birdsseen << endl;
    outFile << "   Average Birds :" << setw(9) << user.hourlybirds << endl;
    outFile << setw(30) << setfill('*') << "" << endl;
    outFile.close();
#endif

}

// ********** TEST CASES + MAIN FUNCTION **********
#ifdef _DEBUG
TEST_CASE("Calculations") {
    birdtracker tracker;
    birdtracker::birdstats stats{ "Annabelle", 1, 5, 50, 0, false }; // name: Annabelle, daysbirding: 1, hoursbirding: 5, birdsseen: 50, hourlybirds: 0, winter: false
    CHECK(tracker.calculateHourlyBirds(stats) == doctest::Approx(10));
    stats.hoursbirding = 2; stats.birdsseen = 10;
    CHECK(tracker.calculateHourlyBirds(stats) == doctest::Approx(5));
    stats.hoursbirding = 0;
    CHECK(tracker.calculateHourlyBirds(stats) == doctest::Approx(0));
    stats.hoursbirding = 3; stats.birdsseen = 15;
    CHECK(tracker.calculateHourlyBirds(stats) == doctest::Approx(5));
}

TEST_CASE("Enum decision logic") {
    birdtracker tracker;
    CHECK(tracker.convertenum("Winter") == Winter);
    CHECK(tracker.convertenum("Spring") == Spring);
    CHECK(tracker.convertenum("Summer") == Summer);
    CHECK(tracker.convertenum("Fall") == Fall);
}

TEST_CASE("Struct/array processing") {
    birdtracker tracker;
    birdtracker::birdstats stats{};
    tracker.addSession(stats, 2, 20);
    CHECK(stats.daysbirding == 1);
    CHECK(stats.hoursbirding == doctest::Approx(2));
    CHECK(stats.birdsseen == 20);
    CHECK(stats.hourlybirds == doctest::Approx(10));

    tracker.setDayCheck(0, true);
    tracker.setDayCheck(6, false);
    CHECK(tracker.getDayCheck(0) == true);
    CHECK(tracker.getDayCheck(6) == false);
}

TEST_CASE("Class methods") {
    birdtracker tracker;
    birdtracker::birdstats stats{};
    tracker.addSession(stats, 3, 30);
    CHECK(stats.hourlybirds == doctest::Approx(10));
}


#else
int main() {
    birdtracker tracker;
    birdtracker::birdstats user;
    const int week = 7;
    string seasonanswer;

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
    }

    cout << "Enter the current season (Winter, Spring, Summer, or Fall):\n";
    cin >> seasonanswer;

    season seasonentered = tracker.convertenum(seasonanswer);
    user.winter = (seasonentered == Winter);

    user.hourlybirds = tracker.calculateHourlyBirds(user);

    cout << fixed << setprecision(2);
    if (user.hourlybirds >= 10 && user.winter)
        cout << "You had a good birding day, even though it was winter!" << endl;
    else if (user.hourlybirds <= 10 && user.winter)
        cout << "Winter is a tough time for birding, it's okay." << endl;
    else if (user.hourlybirds >= 10 && !user.winter)
        cout << "You had a good birding day!" << endl;
    else
        cout << "You had a bad birding day." << endl;

    printtable(user, tracker, week);

    return 0;
}

#endif