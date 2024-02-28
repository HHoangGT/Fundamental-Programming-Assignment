#include "study_in_pink1.h"

bool readFile(
        const string &filename,
        int &HP1,
        int &HP2,
        int &EXP1,
        int &EXP2,
        int &M1,
        int &M2,
        int &E1,
        int &E2,
        int &E3) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
        return true;
    } else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Used functions in the assignment

// Check if E is in the range valid
bool checkValidE(int e) {
    if (e >= 0 && e <= 99) {
        return true;
    } else {
        return false;
    }
}

// Changing the value of EXP to be in the valid range after calculating
void validateExp(int &exp) {
    if (exp < 0) {
        exp = 0;
    } else if (exp > 600) {
        exp = 600;
    }
}

// Changing the value of HP to be in the valid range after calculating
void validateHP(int &HP) {
    if (HP < 0) {
        HP = 0;
    } else if (HP > 666) {
        HP = 666;
    }
}

// Changing the value of M to be in the valid range after calculating
void validateM(int &M) {
    if (M < 0) {
        M = 0;
    } else if (M > 3000) {
        M = 3000;
    }
}


bool isEven(int num) { return num % 2 == 0; }

// used to round up for HP, EXP and M
int roundedUp(double number) { return static_cast<int >(ceil(number)); }

// find the nearest perfect square number of given integer
int nearestPerfectSquare(int num) {
    // first perfect square
    int sq = 1;
    // increase the perfect square
    while (sq * sq <= num) {
        sq += 1;
    }
    // distance of lower and upper perfect square to the given number
    int distToLower = sq * sq - num;
    int distToUpper = num - (sq - 1) * (sq - 1);
    // return the closer perfect square number
    return (distToLower <= distToUpper) ? sq * sq : (sq - 1) * (sq - 1);
}

// check if expense higher than 50% of current money
bool checkInvalidExpense(int currentMoney, int expense, double percent) {
    return static_cast<double >(expense) > (static_cast<double >(currentMoney) * percent);
}

// activities update in action 2 way 2
void activityWay2(int &HP1, int &EXP1, int &M1, int &expense, const int orgMoney, bool odd) {
    // Event 1
    if (HP1 < 200) {
        HP1 = roundedUp(static_cast<double >(HP1) * 130 / 100);
        expense += 150;
        M1 -= 150;
    } else {
        HP1 = roundedUp(static_cast<double >(HP1) * 110 / 100);
        expense += 70;
        M1 -= 70;
    }
    validateHP(HP1);    // validate HP1 after event 1
    validateM(M1);      // validate M1 after event 1
    if (odd) { if (checkInvalidExpense(orgMoney, expense, static_cast<double >(50) / 100)) { return; }}
    if (!odd && M1 == 0) { return; }
    // Event 2
    if (EXP1 < 400) {
        expense += 200;
        M1 -= 200;
    } else {
        expense += 120;
        M1 -= 120;
    }
    EXP1 = roundedUp(static_cast<double >(EXP1) * 113 / 100);
    validateExp(EXP1);
    validateM(M1);
    if (odd) { if (checkInvalidExpense(orgMoney, expense, static_cast<double >(50) / 100)) { return; }}
    if (!odd && M1 == 0) { return; }
    // Event 3
    if (EXP1 < 300) {
        expense += 100;
        M1 -= 100;
    } else {
        expense += 120;
        M1 -= 120;
    }
    EXP1 = roundedUp(static_cast<double >(EXP1) * 90 / 100);
    validateExp(EXP1);
    validateM(M1);
    if (odd) { if (checkInvalidExpense(orgMoney, expense, static_cast<double >(50) / 100)) { return; }}
    if (!odd && M1 == 0) { return; }
}

// Print out the matrix of mission 3
void printMatrix(int matrix[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        // Move to a new line after each row
        cout << endl;
    }
}

// Extract username from the email address
string extractUsername(const string &email) {
    string::size_type index = email.find('@');
    return email.substr(0, index);
}

// find consecutive character in the string
int findConsecutiveChars(const string &str) {
    for (int i = 2; i < str.size(); i++) {
        if (str[i] == str[i - 1] && str[i] == str[i - 2]) {
            return i - 2;
        }
    }
    return -1;
}

// Check string does not contain special chars
bool doesNotContainSpecialChars(const string &str) {
    const string special_chars = "@#%$!";
    for (char c: special_chars) {
        if (str.find(c) != string::npos) {
            return false;
        }
    }
    return true;
}

// find first invalid character
int findFirstInvalidCharacter(const string &str) {
    const string special_chars = "@#%$!";
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') continue;
        if (c >= 'a' && c <= 'z') continue;
        if (c >= 'A' && c <= 'Z') continue;
        if (special_chars.find(c) != string::npos) continue;
        return static_cast<int >(i);
    }
    return -1;
}

// Task 1
int firstMeet(int &exp1, int &exp2, int e1) {
    // TODO: Complete this function
    // Validating if input E and exp is valid
    if (!checkValidE(e1)) { return -99; }
    validateExp(exp1);
    validateExp(exp2);
    // Sherlock's decision
    int D = 0;
    // case 1: e1 in [0,3]
    if (e1 <= 3) {
        switch (e1) {
            case 0:
                exp2 += 29;
                break;
            case 1:
                exp2 += 45;
                break;
            case 2:
                exp2 += 75;
                break;
            case 3:
                exp2 += 29 + 45 + 75;
                break;
            default:
                break;
        }
        // validate Exp2 after calculating
        validateExp(exp2);

        D = e1 * 3 + exp1 * 7;
        if (isEven(D)) {
            exp1 = roundedUp(static_cast<double >(exp1) + (static_cast<double >(D) / 200));
        } else {
            exp1 = roundedUp(static_cast<double >(exp1) - (static_cast<double >(D) / 100));
        }
        // Validate Exp1 after calculating
        validateExp(exp1);
    } else {
        // case 2: e1 in [4,99]
        if (e1 >= 4 && e1 <= 19) {
            // Information 1
            exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 4 + 19);
            validateExp(exp2);
        } else if (e1 >= 20 && e1 <= 49) {
            // Information 2
            exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 9 + 21);
            validateExp(exp2);
        } else if (e1 >= 50 && e1 <= 65) {
            // Information 3
            exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 16 + 17);
            validateExp(exp2);
        } else if (e1 >= 66 && e1 <= 79) {
            // case 4: explain info 1 and check condition, then explain info 2
            exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 4 + 19);
            validateExp(exp2);
            if (exp2 > 200) {
                // Explain information 1 and 2
                exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 9 + 21);
                validateExp(exp2);
            }
        } else {
            // case 5: explain info 1, 2 and check condition, then explain info 3
            exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 4 + 19);
            validateExp(exp2);
            exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 9 + 21);
            validateExp(exp2);
            if (exp2 > 400) {
                // explain info 3
                exp2 = roundedUp(static_cast<double >(exp2) + static_cast<double >(e1) / 16 + 17);
                validateExp(exp2);
                // bonus for explaining all information
                exp2 = roundedUp(static_cast<double >(exp2) * 115 / 100);
                validateExp(exp2);
            }
        }
        // validate Exp2 after calculating
        validateExp(exp2);
        // Reducing Exp1
        exp1 -= e1;
        validateExp(exp1);
    }
    return exp1 + exp2;
}

// Task 2
int traceLuggage(int &HP1, int &EXP1, int &M1, int E3) {
    // TODO: Complete this function
    // Validating if input E, HP1, EXP1 and M1 are valid
    if (!checkValidE(E3)) { return -99; }
    validateHP(HP1);
    validateExp(EXP1);
    validateM(M1);
    // Probability of Three ways
    double P1, P2, P3 = 0;
    // WAY 1
    // Nearest perfect square of EXP1
    int S = nearestPerfectSquare(EXP1);
    // Calculating probability of way 1
    P1 = (EXP1 >= S) ? 1 : (static_cast<double >(EXP1) / static_cast<double >(S) + 80) / 123;
    // WAY 2
    int expense = 0;
    int orgM1 = M1; // variable to store the M1 when starting route 2
    if (!isEven(E3)) {
        // Case: E2 is an odd number
        while (!checkInvalidExpense(orgM1, expense, static_cast<double >(50) / 100)) {
            activityWay2(HP1, EXP1, M1, expense, orgM1, true);
        }
    } else {
        // Case: E2 is an even number
        activityWay2(HP1, EXP1, M1, expense, orgM1, false);
    }
    // Update HP1 and EXP1 at the end of WAY 2
    HP1 = roundedUp(static_cast<double >(HP1) * 83 / 100);
    EXP1 = roundedUp(static_cast<double >(EXP1) * 117 / 100);
    validateHP(HP1);    // validate HP1
    validateExp(EXP1);  // validate EXP1
    // Calculating the probability of way 2
    S = nearestPerfectSquare(EXP1);
    P2 = (EXP1 >= S) ? 1 : (static_cast<double >(EXP1) / static_cast<double >(S) + 80) / 123;
    // WAY 3
    double p_array[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    int i = (E3 < 10) ? E3 : (E3 / 10 + E3 % 10) % 10;
    P3 = p_array[i];
    P3 /= 100;
    // Final Updated after finish three ways
    if (P1 == P2 == P3 == 1) {
        EXP1 = roundedUp(static_cast<double >(EXP1) * 75 / 100);
        validateExp(EXP1);
    } else {
        double avgP = (P1 + P2 + P3) / 3;
        if (avgP < 0.5) {
            HP1 = roundedUp(static_cast<double >(HP1) * 85 / 100);
            EXP1 = roundedUp(static_cast<double >(EXP1) * 115 / 100);
        } else {
            HP1 = roundedUp(static_cast<double >(HP1) * 90 / 100);
            EXP1 = roundedUp(static_cast<double >(EXP1) * 120 / 100);
        }
        validateHP(HP1);
        validateExp(EXP1);
    }
    // Final calculation
    return HP1 + EXP1 + M1;
}

// Task 3
int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3) {
    // TODO: Complete this function
    // validating input
    if (!checkValidE(E3)) { return -99; }
    validateHP(HP1);
    validateHP(HP2);
    validateExp(EXP1);
    validateExp(EXP2);
    // Initialization of 10x10 matrix
    int mapMatrixScore[10][10];
    memset(mapMatrixScore, 0, sizeof(mapMatrixScore));
    // return nothing
    return -1;
}

// Task 4
int checkPassword(const char *s, const char *email) {
    // TODO: Complete this function
    string myS(s);
    string myEmail(email);
    int result = -10;
    string se = extractUsername(myEmail);
    if (!(strlen(s) >= 8 && strlen(s) <= 20))
        return strlen(s) < 8 ? -1 : -2;
    if (myS.find(se) != string::npos) {
        string::size_type sci = myS.find(se);
        return -(300 + static_cast<int >(sci));
    }
    if (findConsecutiveChars(myS) != -1)
        return -(400 + findConsecutiveChars(myS));
    if (doesNotContainSpecialChars(myS))
        return -5;
    if (findFirstInvalidCharacter(myS) != -1)
        return findFirstInvalidCharacter(myS);
    return result;
}

// Task 5
int findCorrectPassword(const char *arr_pwds[], int num_pwds) {
    // TODO: Complete this function

    return -1;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////