#include <iostream>
using namespace std;

// Function to compute gcd and coefficients x, y
int extendedGCD(int a, int b, int &x, int &y) {
    // Base case
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);

    // Update x and y
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    int a, b, x, y;

    cout << "Enter two numbers (a and b): ";
    cin >> a >> b;

    int gcd = extendedGCD(a, b, x, y);

    cout << "GCD = " << gcd << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    // Verify result
    cout << "Verification: " << a << "(" << x << ") + "
         << b << "(" << y << ") = " << a*x + b*y << endl;

    return 0;
}

Input:
Enter two numbers (a and b): 161 28

Output:
x = -1
y = 6
Verification: 161(-1) + 28(6) = 7
