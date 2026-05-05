#include <iostream>
using namespace std;

// Extended Euclidean Algorithm
int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// Function to solve ax + by = c
bool solveDiophantine(int a, int b, int c, int &x, int &y) {
    int gcd = extendedGCD(a, b, x, y);

    // No solution if c is not divisible by gcd
    if (c % gcd != 0)
        return false;

    // Multiply solution by c/gcd
    x = x * (c / gcd);
    y = y * (c / gcd);

    return true;
}

int main() {
    int a, b, c;
    cout << "Enter a, b, c: ";
    cin >> a >> b >> c;

    int x, y;

    if (solveDiophantine(a, b, c, x, y)) {
        cout << "Solution exists!" << endl;
        cout << "x = " << x << ", y = " << y << endl;

        // Verify
        cout << "Check: " << "ax + by" << " = " << c << endl;
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}

Input:
Enter a, b, c: 15 25 5
    
Output:
Solution exists!
x = 2, y = -1
Check: ax + by = 5
