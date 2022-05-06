#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

// Define a prototype functions
void parity(int[]);
void case_1(int[], int[], string);
void case_2(int[], int[], int[], int, int, int, string);
void menu_interface(string);
// Beginning of main function
int main()
{
    // Array for the data to be sent
    int a[12];
    // Temp Array, for get copy from Array a[]
    int t[12];
    // For menu
    int i;
    // Counter variable for array PH[]
    int j = 0;
    // Counter for parity Array PH[]
    int x = 0;
    // For saving the corrupt bit
    int sum = 0;
    // For saving the corrupt parity bits
    int PH[4] = {0, 0, 0, 0};

    string menu = "***Menu***\n1.calculate parity code \n2.change a bit \n3.Exit";
    cout << menu << "\n\n"
         << "choose a number: ";
    // Menu section
    // Infinite loop
    while (1)
    {
        while (!(cin >> i))
        {
            // Menu interface
            system("CLS");
            string menu = "***Menu***\n1.calculate parity code \n2.change a bit \n3.Exit";
            cout << "Try again!!!\n"
                 << menu << "\n\n"
                 << "choose a number: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        // Switch case for menu interface
        switch (i)
        {
        // Get the data to be sent
        case 1:
            case_1(a, t, menu);
            break; // end of Case 1

        // Changing a bit for make corruption in transmitted data
        case 2:
            case_2(a, t, PH, j, x, sum, menu);
            break; // end of Case 2
        case 3:
            exit(0);
            break;
        default:
            system("CLS");
            cout << "Try again!!!\n";
            menu_interface(menu);
            cin.clear();
            cin.ignore();
            break;
        }
    }
    getch();
} // end of main function

// Calculating parity bits by XOR
// Save parity bits in array
void parity(int x[12])
{
    x[0] = x[2] ^ x[4] ^ x[6] ^ x[8] ^ x[10];
    x[1] = x[2] ^ x[5] ^ x[6] ^ x[9] ^ x[10];
    x[3] = x[4] ^ x[5] ^ x[6] ^ x[11];
    x[7] = x[8] ^ x[9] ^ x[10] ^ x[11];
    cout << ">>>Your parity code is: " << endl;
    cout << '\t' << '\t' << '\t' << "P1: " << x[0] << '\t' << "P2: " << x[1] << '\t' << "P4: " << x[3] << '\t' << "P8: " << x[7] << endl
         << endl;
} // end of parity function

void case_1(int a[12], int t[12], string menu)
{
    cout << "\n************************************************************\n";
    cout << ">>>Enter 8 digits: ";
    cin >> a[2] >> a[4] >> a[5] >> a[6] >> a[8] >> a[9] >> a[10] >> a[11];
    // Calculate parity bits
    parity(a);
    // Print transmitted data for receiver by for loop
    cout << "Transmitted Data: ";
    for (int i = 0; i <= 11; i++)
    {
        cout << a[i];
        // Copy Array a(transmitted data) in Array t
        t[i] = a[i];
        // Print the star next to the parity bits for easier identification
        if (i == 0 || i == 1 || i == 3 || i == 7)
            cout << "*";
        // Print space between bits for the beauty of output
        cout << "  ";
    }
    cout << endl
         << endl
         << endl;
    menu_interface(menu);
}

void case_2(int a[12], int t[12], int PH[], int j, int x, int sum, string menu)
{
    // just For beauty and readability
    cout << "\n************************************************************\n";
    // To get the bit that is going to change
    int bit;

    cout << "Enter the bit you want to change: ";
    cin >> bit;
    // Loop for find and change the exactly bit what you want in Array a[]
    for (int i = 1; i <= 12; i++)
    {
        // Matching the bit what you call in Array a[]
        if (i == bit)
        {
            // Get a zero or one to change the contents of the bit
            cout << "Enter your number[1 or 0]: ";
            cin >> a[i - 1];
            //‌‌Break for not going through all of the array after the bit you want to change
            break;
        }
    }
    // Recalculate parity bits after a change in the transmitted data
    parity(a);
    // Print the transferred data after recalculation
    cout << "Transmitted Data: ";
    for (int i = 0; i <= 11; i++)
    {
        cout << a[i];
        if (i == 0 || i == 1 || i == 3 || i == 7)
            // Again for Specify the position of the parity bits
            cout << "*";
        // Print space between bits
        cout << "  ";
    }
    cout << endl
         << endl;

    // To print parity bits before and after change
    for (int i = 1; i <= 12; i++)
    {
        // Find every bit of parity
        if (i == 1 || i == 2 || i == 4 || i == 8)
        {
            // Print parity bits in Array t[] and Array a[]
            cout << "First-P" << i << ": " << t[i - 1] << "   "
                 << "Second-P" << i << ": " << a[i - 1] << endl;
            // Compare parity bits one by one to find variations
            if (t[i - 1] != a[i - 1])
            {
                // Find the bit that caused the data to crash
                sum += i;
                // To find corrupted parity bits and save them in the Array PH[]
                PH[j] = i;
                // Increases the counter a number
                j++;
            }
        }
    }
    // Print corrupt bit, that user changed it
    cout << endl
         << "your Corrupt bit is " << sum << endl;
    // Print parity bits which are changed
    for (j = 0; j <= 3; j++)
    {
        // If array has a column with value of zero skip it
        if (PH[j] == 0)
        {
            continue;
        }
        // print corrupt parity bits
        cout << "Corrupt Parity bit: " << PH[j] << endl;
    }

    cout << endl;

    // Loop for locate corrupt non-parity bit
    for (int i = 1; i <= 12; i++)
    {
        if (i == sum)
        {
            // If the user changes the bit to 0, it becomes 1, or if the bit changes to 1, it becomes 0
            if (a[i - 1] == 0)
                a[i - 1] = 1;
            else
                a[i - 1] = 0;
        }
        // When the loop reaches the parity bits
        if (i == 1 || i == 2 || i == 4 || i == 8)
        {
            // When i was equal to the contents of the array PH[] column
            if (i == PH[x])
            {
                // If it's changes to 0, it becomes 1, or if changes to 1, it becomes 0
                if (a[i - 1] == 0)
                    a[i - 1] = 1;
                else
                    a[i - 1] = 0;
                // Increase counter a number
                x++;
            }
        }
    } // end of for loop (correction for loop)

    // Print the corrected data
    cout << "The error was corrected: ";
    for (int i = 1; i <= 12; i++)
    {
        cout << a[i - 1];
        if (i == 1 || i == 2 || i == 4 || i == 8)
            cout << "*";
        cout << "  ";
    }
    cout << endl
         << endl
         << endl;
    menu_interface(menu);
}

void menu_interface(string menu)
{

    cout << menu << "\n\n"
         << "choose a number: ";
}
