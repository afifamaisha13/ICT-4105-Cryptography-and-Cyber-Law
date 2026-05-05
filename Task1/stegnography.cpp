#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Convert message to binary + delimiter
string toBinary(const string &message) {
    string binary = "";
    for (char c : message) {
        for (int i = 7; i >= 0; i--) {
            binary += ((c >> i) & 1) ? '1' : '0';
        }
    }
    binary += "11111110"; // end delimiter
    return binary;
}

// Encode message into BMP image
bool encode(const string &inputImage, const string &outputImage, const string &message) {
    ifstream in(inputImage, ios::binary);
    if (!in) {
        cout << "Cannot open input image!\n";
        return false;
    }

    vector<char> buffer((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string binary = toBinary(message);

    if (binary.size() > (buffer.size() - 54)) {
        cout << "Message too large for this image!\n";
        return false;
    }

    int dataIndex = 0;

    // Skip BMP header (first 54 bytes)
    for (int i = 54; i < buffer.size() && dataIndex < binary.size(); i++) {
        buffer[i] = (buffer[i] & 0xFE) | (binary[dataIndex++] - '0');
    }

    ofstream out(outputImage, ios::binary);
    out.write(buffer.data(), buffer.size());
    out.close();

    cout << "Message encoded successfully into: " << outputImage << endl;
    return true;
}

// Decode message from BMP image
void decode(const string &inputImage) {
    ifstream in(inputImage, ios::binary);
    if (!in) {
        cout << "Cannot open image!\n";
        return;
    }

    vector<char> buffer((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string binary = "";

    for (int i = 54; i < buffer.size(); i++) {
        binary += (buffer[i] & 1) ? '1' : '0';
    }

    string message = "";

    for (int i = 0; i + 8 <= binary.size(); i += 8) {
        string byte = binary.substr(i, 8);

        if (byte == "11111110") break;

        char c = 0;
        for (int j = 0; j < 8; j++) {
            c = (c << 1) | (byte[j] - '0');
        }

        message += c;
    }

    cout << "Hidden Message: " << message << endl;
}

// Main menu
int main() {
    int choice;

    cout << "\n==== Steganography Tool ====\n";
    cout << "1. Encode Message\n";
    cout << "2. Decode Message\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string inputImage, outputImage, message;

        cout << "Enter input BMP image (e.g., input.bmp): ";
        cin >> inputImage;

        cout << "Enter output image (e.g., output.bmp): ";
        cin >> outputImage;

        cin.ignore(); // clear buffer
        cout << "Enter secret message: ";
        getline(cin, message);

        encode(inputImage, outputImage, message);
    }
    else if (choice == 2) {
        string inputImage;

        cout << "Enter encoded BMP image: ";
        cin >> inputImage;

        decode(inputImage);
    }
    else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
