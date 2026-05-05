#include <iostream>
using namespace std;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;

    cout << "GCD = " << gcd(a, b) << endl;
    return 0;
}


Input:
Enter two integers: 161 28

Output:
GCD = 7
