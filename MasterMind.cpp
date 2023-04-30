/*
    Number guessing game implementation in C++
*/

#include <iostream> 
#include <string> // necessary for stoi, to_string, getline

using namespace std;

// functions prototypes
bool valLen(string len);
string gengoal(int len);
bool valguess(int len, string& guess);
bool chkguess(string guess, string goal, int len);

// validates user length
bool valLen(string len) {
    /*
        if user length contain anything non numeric, find_first_not_of returns positon of
        first non numeric character.
        else if user length contain only numbers, first_find_not_of returns string::npos.
        string::npos indicates no matches until the end of the string.
    */
    // check user length to be numeric and have 1 or 2 digits.
    if (len.find_first_not_of("0123456789") != string::npos || (len.size() != 1 && len.size() != 2)) {
        cerr << "Please enter a valid number." << endl;
        return false;
    }
    // check length to be between 2 and 20. converting to int is safe here.
    if (stoi(len) < 2 || stoi(len) > 20) {
        cerr << "Please enter a number between 2 & 20." << endl;
        return false;
    }
    return true;
}

// generates a random number with a defined length
string gengoal(int len) {
    //srand(time(0));
    string digits;
    for (int i = 0; i < len; i++) {
        digits += to_string(rand() % 10);
    }
    /*
        char variable receive ascii codes. so it is necessary to add '0' to random digit
        so C++ converts random digit to ascii code.
    */
    // check first digit of random number to not be zero
    //while (digits[0] == '0') {
    //    digits[0] = (rand() % 10) + '0';
    //}
    return digits;
}

// validates user guesses, guess string is called by reference so changes will be applied.
bool valguess(int len, string &guess) {
    /*
        guesses should have space after each digit. this loop checks spaces are in their postion or not.
        if spaces were ok, they get removed from string. otherwise, error appears.
    */
    for (int i = 1; i < guess.length(); i++, i++) {
        if (guess[i] == ' ') {
            guess.erase(guess.begin() + i);
            i--;
        }
        else if (guess[i] != ' ') {
            cerr << "Please enter your guess in correct format." << endl;
            return false;
        }
    }
    // same as checking length. also checks guess length after removal of spaces, to match given length.
    if (guess.find_first_not_of("0123456789") == string::npos && guess.length() == len) {
            return true;
    }
    else { cerr << "Please enter a valid number." << endl; return false; }
}

// check guesses to be true and generates #X.
bool chkguess(string guess, string goal, int len) {
    string result;
    for (int i = 0; i < len; i++) {
        if (guess[i] == goal[i]) {
            result += "# ";
        }
        else { result += "X "; }
    }
    cout << result << endl;
    if (guess == goal)  return true;
    else  return false;
}

int main()
{
    // main variables
    string name, strLen, goal, guess, rerun;
    int length;
    bool validate, result = false;

    cout << "Welcome to the \"Guess the Number\" game. Please enter your name:" << endl;
    /*
        one might wonder, why we used getline instead of cin?
        because cin consider input spaces as enter for next command,
        but getline receives spaces without any problem.
    */
    getline(cin >> ws, name);
    cout << "Hello " + name + "!" << endl;

    // this loop let user play the game again.
    do {

        cout << "Please enter the length of number:" << endl;

        /*
        this loop validates length with aforementioned fuction.
        as getline only works with strings, we should receive length as string.
        */
        do {
            /*
                changing length string to null for each validation
                don't let user to use previous value of length by
                entering null (CTRL+Z).
            */
            strLen = "";
            /*
                cin.clear clears cin cache and don't let program end up in an infinite loop
                when user enters null as length.
            */
            cin.clear();
            getline(cin >> ws, strLen);
            validate = valLen(strLen);
        } while (!validate);

        cout << "So, you have " + strLen + " chances!" << endl;
        cout << "You'r guess digits should be seperated by space." << endl;
        
        // now we convert length string to int, because gengoal function only accepts int as input
        length = stoi(strLen);

        // a random number generates and returns to string goal
        goal = gengoal(length);

        // this loop runs as long as user have chance to guess
        for (int chances = length; chances > 0; chances--) {
            cout << "Enter your guess:" << endl;

            /*
                this loop validates each guess, cin.clear used for aforementioned reason.
                user guess already changed here (spaces are removed by valguess function)
                so we don't need to set its value to null.
            */
            do {
                cin.clear();
                getline(cin >> ws, guess);
                validate = valguess(length, guess);
            } while (!validate);

            // now we can check user guess with chkguess function. result returns to bool result.
            result = chkguess(guess, goal, length);

            // if chkguess return true, user wins and loop breaks.
            if (result) {
                cout << "You Won!" << endl;
                break;
            }
        }

        /*
            now user chances are finished. so, if result is yet false, user loses.
            why we check bool result to be false?
            because we don't want to cout Game Over if user has won.
        */
        if (!result) {
            cout << "Game Over!" << endl;
            cout << "Goal was: " + goal << endl;
        }

        cout << "Do you want to play the game again, " + name + "? (Enter 'y' for yes, or anything else for exit.)" << endl;

        // rerun string sets to null, so user can not use its previous value by entering null.
        rerun = "";
        cin >> rerun;

    } while (rerun == "y");
}
