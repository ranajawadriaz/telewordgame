#include <iostream>
#include <Windows.h>                                                                                                             //for colours
#include <conio.h>                                                                                                               // For using getch() function
#include <chrono>                                                                                                                //for time
#include <fstream>                                                                                                               //for file input/output
void input(char array1[]);                                                                                                       // input from file and storing in array1
void store1(char array1[], char array2[15][15], int &temp);                                                                      // Storing of Grid in array for display
void store2(char array1[], char array3[], int temp);                                                                             // Storing of words in array for dislay
void store3(char array3[], char array4[], int &max, int &min, float &avg);                                                       // Storing of Capital letters word
void display(char array2[15][15], char array3[], int array5[15][15], int mingle);                                                // To display on console
void scan(char array2[15][15], char array4[], char array3[], int array5[15][15], int array6[], char aa, int arr1[], int arr2[]); // searching function
void Teleword(char array2[15][15], int array5[15][15], int &teleword_scatter);                                                   // Teleword printing and teleword scatter
void Heaviest_Check(int arr1[], int arr2[], int &row1, int &col1);                                                               // returning heaviest row and column

using namespace std;
using namespace std::chrono;
int main()
{
    int temp = 0, mingle = 0, teleword_scatter = 0, max = 0, min = 16, row1 = 0, col1 = 0;
    int arr1[15], arr2[15];
    float avg = 0.0;
    char aa;
    char array1[900];
    char array2[15][15];
    char array3[700];
    char array4[700];
    int array5[15][15];
    int array6[9];

    for (int i = 0; i < 15; i++)
    {
        arr1[i] = 0;
        arr2[i] = 0;
    }

    input(array1);
    store1(array1, array2, temp);
    store2(array1, array3, temp);
    display(array2, array3, array5, mingle);
    store3(array3, array4, max, min, avg);

    cout << endl
         << endl
         << "Press S to solve the puzzle at once" << endl;
    cout << "Press T to solve the puzzle step by step" << endl;
    cout << "Press X to print puzzle statistics: ";
    cin >> aa;

    if (aa == 's' || aa == 'S' || aa == 'T' || aa == 't' || aa == 'x' || aa == 'X')
    {
        auto volunteer = high_resolution_clock::now();
        scan(array2, array4, array3, array5, array6, aa, arr1, arr2);
        auto stop = high_resolution_clock::now();
        Teleword(array2, array5, teleword_scatter);

        auto time_taken = duration_cast<microseconds>(stop - volunteer);

        Heaviest_Check(arr1, arr2, row1, col1);

        if (aa == 'X' || aa == 'x')
        {
            cout << endl
                 << "Time Taken: " << time_taken.count() << " microseconds" << endl;
            cout << "Longest Word Length: " << max;
            cout << endl
                 << "Shortest Word Length: " << min;
            cout << endl
                 << "Average Word Length: " << avg;
            cout << endl
                 << "Word Distribution:  Horizontal: " << array6[0] << " (" << array6[1] << ", " << array6[2] << "), Vertical: " << array6[3];
            cout << " (" << array6[5] << ", " << array6[4] << "), Diagonal: " << array6[6] << " (" << array6[7] << ", " << array6[8] << ")" << endl;
            cout << "Teleword Scatter: " << teleword_scatter << endl;
            cout << "Heaviest Row: " << row1 << endl;
            cout << "Heaviest Column: " << col1;
        }
    }
    else
    {
        cout << endl
             << "Invalid Character Entered!" << " Press Any Key to Continue.....";
        _getch();
        system("CLS");
        main();
    }

    cout << endl
         << "PRESS ANY KEY TO PLAY AGAIN......" << endl; // To play again
    _getch();

    system("CLS");
    main();

    return 0;
}

void input(char array1[]) // input from file and storing in array1
{
    ifstream Sa;
    Sa.open("telewordfile1.txt");

    for (int i = 0; !Sa.eof(); i++)
    {
        Sa >> array1[i];
    }

    Sa.close();

    for (int i = 0; array1[i] != '\0'; i++)
    {
        if (array1[i] == '.')
        {
            array1[i + 1] = '\0';
            break;
        }
    }
}

void store1(char array1[], char array2[15][15], int &temp) // Storing of Grid in array for display
{

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (array1[temp] != ' ' && array1[temp] != ',' && array1[temp] != '.')
            {
                array2[i][j] = array1[temp];
                temp++;
            }
        }
    }
}

void store2(char array1[], char array3[], int temp) // Storing of words in array for dislay
{

    int pmi = 0;

    for (int i = temp; array1[i] != '\0'; i++)
    {

        if (array1[i] == '.')
        {
            array3[pmi] = '\0';
            break;
        }

        if (array1[i] != ',')
        {
            array3[pmi] = array1[i];
            pmi++;
        }
        else
        {
            array3[pmi] = ' ';
            pmi++;
        }
    }
}

void display(char array2[15][15], char array3[], int array5[15][15], int mingle) // To display on console
{

    HANDLE calories = GetStdHandle(STD_OUTPUT_HANDLE); // To handle colours on console screen

    system("CLS");
    cout << endl;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (array5[i][j] == -1)
            {
                SetConsoleTextAttribute(calories, 7);
            }
            else if (array5[i][j] == 1)
            {
                SetConsoleTextAttribute(calories, 6);
            }
            else if (array5[i][j] == 2)
            {
                SetConsoleTextAttribute(calories, 1);
            }
            else if (array5[i][j] == 3)
            {
                SetConsoleTextAttribute(calories, 4);
            }

            cout << array2[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;
    SetConsoleTextAttribute(calories, 7);

    if (mingle == 0)
    {
        for (int i = 0; array3[i] != '\0'; i++)
        {
            if (array3[i] != ' ')
            {
                cout << array3[i];
            }
            else
            {
                cout << ", ";
            }
        }

        cout << ".";
    }

    mingle++;
}

void store3(char array3[], char array4[], int &max, int &min, float &avg) // Storing of Capital letters word and returning average of words for statistics
{
    int count1 = 0;
    float sum = 0, count2 = 0;

    for (int i = 0; array3[i - 1] != '\0'; i++)
    {
        if (array3[i] == '\0')
        {
            array4[i] = ' ';
            array4[i + 1] = '\0';
            break;
        }

        if (array3[i] >= 97 && array3[i] <= 122)
        {
            array4[i] = array3[i] - 32;
        }
        else
        {
            array4[i] = array3[i];
        }
    }

    for (int i = 0; array4[i] != '\0'; i++) // loop to find largest,smallest and average word length
    {
        if (array4[i] != ' ')
        {
            count1++;
        }
        else
        {
            if (count1 > max)
            {
                max = count1;
            }
            if (count1 < min)
            {
                min = count1;
            }

            sum = sum + count1;
            count2++;

            count1 = 0;
        }
    }

    avg = sum / count2;
}

void scan(char array2[15][15], char array4[], char array3[], int array5[15][15], int array6[], char aa, int arr1[], int arr2[]) // searching function
{
    int iii = 0;

    for (int pico = 0; pico < 15; pico++) // turning all values of array5 to -1
    {
        for (int lico = 0; lico < 15; lico++)
        {
            array5[pico][lico] = -1;
        }
    }

    for (int ii = 0; array4[ii] != '\0'; ii++) // for counting total number of words
    {
        if (array4[ii] == ' ')
        {
            iii++;
        }
    }

    for (int i = 0; i < 9; i++) // for words distribution
    {
        array6[i] = 0;
    }

    char sus[20];
    int tmp = 0, jmp = 0, dmp = 0, gmp = 0, imp = 75, lili = 0;

    for (int i = 0; i < iii; i++) // loop to scan a specific number of words
    {
        gmp = 0;
        dmp = 0;
        lili = 0;
        for (int j = 0; true; j++)
        {
            if (array4[tmp] == ' ')
            {
                sus[j] = '\0';
                tmp++;
                jmp = j;
                break;
            }
            else
            {
                sus[j] = array4[tmp];
                tmp++;
            }
        }

        for (int l = 0; l < 15; l++)
        {
            dmp = 0;
            gmp = 0;
            for (int m = 0; m < 15; m++)
            {
                dmp = 0;
                gmp = 0;

                if (array2[l][m] == sus[0]) // 1st module  for horizontal right
                {
                    for (int n = m; n < m + jmp; n++)
                    {
                        if (array2[l][n] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -1;
                            gmp = -1;
                            break;
                        }
                    }
                }

                if (dmp == jmp)
                {
                    for (int o = m; o < m + jmp; o++)
                    {
                        arr2[o]++;
                        for (int q = 0; q < 15; q++)
                        {
                            for (int r = 0; r < 15; r++)
                            {
                                if (q == l && r == o)
                                {
                                    if (array5[q][r] == -1)
                                    {
                                        array5[q][r] = 1;
                                    }
                                    else if (array5[q][r] == 1)
                                    {
                                        array5[q][r] = 2;
                                    }
                                    else if (array5[q][r] == 2)
                                    {
                                        array5[q][r] = 3;
                                    }
                                    else if (array5[q][r] == 3)
                                    {
                                        array5[q][r] = 3;
                                    }

                                    break;
                                }
                            }
                        }
                    }

                    array6[0]++;
                    array6[1]++;
                    arr1[l]++;

                    display(array2, array3, array5, 5);
                    lili = -1;
                    break;
                }
                if (dmp == -1 && gmp == -1) //    second module   for horizontal left
                {
                    dmp = 0;
                    gmp = 0;

                    for (int t = m; t > m - jmp; t--)
                    {
                        if (array2[l][t] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -2;
                            gmp = -2;
                            break;
                        }
                    }

                    if (dmp == jmp)
                    {
                        for (int oo = m; oo > m - jmp; oo--)
                        {
                            arr2[oo]++;
                            for (int qq = 0; qq < 15; qq++)
                            {
                                for (int rr = 0; rr < 15; rr++)
                                {
                                    if (qq == l && rr == oo)
                                    {
                                        if (array5[qq][rr] == -1)
                                        {
                                            array5[qq][rr] = 1;
                                        }
                                        else if (array5[qq][rr] == 1)
                                        {
                                            array5[qq][rr] = 2;
                                        }
                                        else if (array5[qq][rr] == 2)
                                        {
                                            array5[qq][rr] = 3;
                                        }
                                        else if (array5[qq][rr] == 3)
                                        {
                                            array5[qq][rr] = 3;
                                        }

                                        break;
                                    }
                                }
                            }
                        }

                        array6[0]++;
                        array6[2]++;
                        arr1[l]++;

                        display(array2, array3, array5, 5);
                        lili = -1;
                        break;
                    }
                }
                if (dmp == -2 && gmp == -2) // 3rd module for vertical up
                {
                    dmp = 0;
                    gmp = 0;

                    for (int tt = l; tt > l - jmp; tt--)
                    {
                        if (array2[tt][m] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -3;
                            gmp = -3;
                            break;
                        }
                    }

                    if (dmp == jmp)
                    {
                        for (int ooo = l; ooo > l - jmp; ooo--)
                        {
                            arr1[ooo]++;
                            for (int qqq = 0; qqq < 15; qqq++)
                            {
                                for (int rrr = 0; rrr < 15; rrr++)
                                {
                                    if (qqq == ooo && rrr == m)
                                    {
                                        if (array5[qqq][rrr] == -1)
                                        {
                                            array5[qqq][rrr] = 1;
                                        }
                                        else if (array5[qqq][rrr] == 1)
                                        {
                                            array5[qqq][rrr] = 2;
                                        }
                                        else if (array5[qqq][rrr] == 2)
                                        {
                                            array5[qqq][rrr] = 3;
                                        }
                                        else if (array5[qqq][rrr] == 3)
                                        {
                                            array5[qqq][rrr] = 3;
                                        }

                                        break;
                                    }
                                }
                            }
                        }

                        array6[3]++;
                        array6[4]++;
                        arr2[m]++;

                        display(array2, array3, array5, 5);
                        lili = -1;
                        break;
                    }
                }
                if (dmp == -3 && gmp == -3) // 4th module for vertical down
                {
                    dmp = 0;
                    gmp = 0;

                    for (int ttt = l; ttt < l + jmp; ttt++)
                    {

                        if (array2[ttt][m] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -4;
                            gmp = -4;
                            break;
                        }
                    }

                    if (dmp == jmp)
                    {
                        for (int oooo = l; oooo < l + jmp; oooo++)
                        {
                            arr1[oooo]++;
                            for (int qqqq = 0; qqqq < 15; qqqq++)
                            {
                                for (int rrrr = 0; rrrr < 15; rrrr++)
                                {
                                    if (qqqq == oooo && rrrr == m)
                                    {
                                        if (array5[qqqq][rrrr] == -1)
                                        {
                                            array5[qqqq][rrrr] = 1;
                                        }
                                        else if (array5[qqqq][rrrr] == 1)
                                        {
                                            array5[qqqq][rrrr] = 2;
                                        }
                                        else if (array5[qqqq][rrrr] == 2)
                                        {
                                            array5[qqqq][rrrr] = 3;
                                        }
                                        else if (array5[qqqq][rrrr] == 3)
                                        {
                                            array5[qqqq][rrrr] = 3;
                                        }

                                        break;
                                    }
                                }
                            }
                        }

                        array6[3]++;
                        array6[5]++;
                        arr2[m]++;

                        display(array2, array3, array5, 5);
                        lili = -1;
                        break;
                    }
                }
                if (dmp == -4 && gmp == -4) // 5th module for left upward
                {
                    dmp = 0;
                    gmp = 0;

                    for (int s1l = l, s1m = m; s1l > l - jmp, s1m > m - jmp; s1l--, s1m--)
                    {
                        if (array2[s1l][s1m] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -5;
                            gmp = -5;
                            break;
                        }
                    }

                    if (dmp == jmp)
                    {
                        for (int s11l = l, s11m = m; s11l > l - jmp, s11m > m - jmp; s11l--, s11m--)
                        {
                            arr1[s11l]++;
                            arr2[s11m]++;
                            for (int q1 = 0; q1 < 15; q1++)
                            {
                                for (int r1 = 0; r1 < 15; r1++)
                                {
                                    if (q1 == s11l && r1 == s11m)
                                    {
                                        if (array5[q1][r1] == -1)
                                        {
                                            array5[q1][r1] = 1;
                                        }
                                        else if (array5[q1][r1] == 1)
                                        {
                                            array5[q1][r1] = 2;
                                        }
                                        else if (array5[q1][r1] == 2)
                                        {
                                            array5[q1][r1] = 3;
                                        }
                                        else if (array5[q1][r1] == 3)
                                        {
                                            array5[q1][r1] = 3;
                                        }

                                        break;
                                    }
                                }
                            }
                        }

                        array6[6]++;
                        array6[8]++;

                        display(array2, array3, array5, 5);
                        lili = -1;
                        break;
                    }
                }
                if (dmp == -5 && gmp == -5) // 6th module for right downward
                {
                    dmp = 0;
                    gmp = 0;

                    for (int s2l = l, s2m = m; s2l < l + jmp, s2m < m + jmp; s2l++, s2m++)
                    {
                        if (array2[s2l][s2m] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -6;
                            gmp = -6;
                            break;
                        }
                    }

                    if (dmp == jmp)
                    {
                        for (int s22l = l, s22m = m; s22l < l + jmp, s22m < m + jmp; s22l++, s22m++)
                        {
                            arr1[s22l]++;
                            arr2[s22m]++;
                            for (int q2 = 0; q2 < 15; q2++)
                            {
                                for (int r2 = 0; r2 < 15; r2++)
                                {
                                    if (q2 == s22l && r2 == s22m)
                                    {
                                        if (array5[q2][r2] == -1)
                                        {
                                            array5[q2][r2] = 1;
                                        }
                                        else if (array5[q2][r2] == 1)
                                        {
                                            array5[q2][r2] = 2;
                                        }
                                        else if (array5[q2][r2] == 2)
                                        {
                                            array5[q2][r2] = 3;
                                        }
                                        else if (array5[q2][r2] == 3)
                                        {
                                            array5[q2][r2] = 3;
                                        }

                                        break;
                                    }
                                }
                            }
                        }

                        array6[6]++;
                        array6[7]++;

                        display(array2, array3, array5, 5);
                        lili = -1;
                        break;
                    }
                }
                if (dmp == -6 && gmp == -6) // 7th module for diagonal right upward
                {
                    dmp = 0;
                    gmp = 0;

                    for (int s3l = l, s3m = m; s3l > l - jmp, s3m < m + jmp; s3l--, s3m++)
                    {
                        if (array2[s3l][s3m] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -7;
                            gmp = -7;
                            break;
                        }
                    }

                    if (dmp == jmp)
                    {
                        for (int s33l = l, s33m = m; s33l > l - jmp, s33m < m + jmp; s33l--, s33m++)
                        {
                            arr1[s33l]++;
                            arr2[s33m]++;
                            for (int q3 = 0; q3 < 15; q3++)
                            {
                                for (int r3 = 0; r3 < 15; r3++)
                                {
                                    if (q3 == s33l && r3 == s33m)
                                    {
                                        if (array5[q3][r3] == -1)
                                        {
                                            array5[q3][r3] = 1;
                                        }
                                        else if (array5[q3][r3] == 1)
                                        {
                                            array5[q3][r3] = 2;
                                        }
                                        else if (array5[q3][r3] == 2)
                                        {
                                            array5[q3][r3] = 3;
                                        }
                                        else if (array5[q3][r3] == 3)
                                        {
                                            array5[q3][r3] = 3;
                                        }

                                        break;
                                    }
                                }
                            }
                        }

                        array6[6]++;
                        array6[7]++;

                        display(array2, array3, array5, 5);
                        lili = -1;
                        break;
                    }
                }
                if (dmp == -7 && gmp == -7) // 8th module for diagonal left downward
                {
                    dmp = 0;
                    gmp = 0;

                    for (int s4l = l, s4m = m; s4l<l + jmp, s4m> m - jmp; s4l++, s4m--)
                    {
                        if (array2[s4l][s4m] == sus[gmp])
                        {
                            dmp++;
                            gmp++;
                        }
                        else
                        {
                            dmp = -8;
                            gmp = -8;
                            break;
                        }
                    }

                    if (dmp == jmp)
                    {
                        for (int s44l = l, s44m = m; s44l<l + jmp, s44m> m - jmp; s44l++, s44m--)
                        {
                            arr1[s44l]++;
                            arr2[s44m]++;
                            for (int q4 = 0; q4 < 15; q4++)
                            {
                                for (int r4 = 0; r4 < 15; r4++)
                                {
                                    if (q4 == s44l && r4 == s44m)
                                    {
                                        if (array5[q4][r4] == -1)
                                        {
                                            array5[q4][r4] = 1;
                                        }
                                        else if (array5[q4][r4] == 1)
                                        {
                                            array5[q4][r4] = 2;
                                        }
                                        else if (array5[q4][r4] == 2)
                                        {
                                            array5[q4][r4] = 3;
                                        }
                                        else if (array5[q4][r4] == 3)
                                        {
                                            array5[q4][r4] = 3;
                                        }

                                        break;
                                    }
                                }
                            }
                        }

                        array6[6]++;
                        array6[8]++;

                        display(array2, array3, array5, 5);
                        lili = -1;
                        break;
                    }
                }
            }

            if (lili == -1)
            {
                if (aa == 't' || aa == 'T')
                {
                    _getch();
                }

                break;
            }
        }
    }
}

void Teleword(char array2[15][15], int array5[15][15], int &teleword_scatter) // Teleword printing and teleword scatter
{
    cout << "Teleword: ";
    int p = -1;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (array5[i][j] == -1)
            {
                cout << array2[i][j];
                if (p != i)
                {
                    teleword_scatter++;
                }

                p = i;
            }
        }
    }

    cout << endl;
}

void Heaviest_Check(int arr1[], int arr2[], int &row1, int &col1) // returning heaviest row and column
{
    int max1 = 0, max2 = 0;
    max1 = arr1[0];
    row1 = 1;
    max2 = arr2[0];
    col1 = 1;

    for (int i = 1; i < 15; i++)
    {
        if (arr1[i] > max1)
        {
            max1 = arr1[i];
            row1 = i;
        }

        if (arr2[i] > max2)
        {
            max2 = arr2[i];
            col1 = i;
        }
    }
}