#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;
void encryption(int k)
{
    ifstream fin("../lab2/input.txt");
    ofstream fout("../lab2/output.txt");
    int cod, len;
    char h;
    char *s = new char[256];
    char q[80];

    do			//построчно
    {
        fout<<endl;
        fin>>s;
        len=strlen(s);

            for(int w=0;w<len;w++)
            {
                h=s[w];
                cod=(int)h;
                cod=cod+k;
                s[w]=char(cod);
                fout<<s[w];
            }
    } while (fin.getline(q, 80));
    fout.close();
    fin.close();
}
void decryption(int k)
{
    ifstream fin2("../lab2/output.txt");
    int cod, len;
    char h;
    char *s = new char[256];
    char q[80];
    do			//построчно
    {
        cout<<endl;
        fin2>>s;
        len=strlen(s);
        for(int w=0;w<len;w++)
        {
            h=s[w];
            cod=(int)h;
            cod=cod-k;
            s[w]=char(cod);
            cout<<s[w];
        }
    } while (fin2.getline(q, 80));
    fin2.close();
}
int main()
{
    int k; //key
    char c; //choice
    cout << "If encryption - enter e, if decryption - enter d: \n";
    cin >> c;
    cout << "Enter key: \n";
    if (c=='e')
    {
        cin >> k;
        encryption(k);
        cout << "If decryption - enter d, finish the program - z: \n";
        cin >>c;
        if(c=='d')
        {
            cout << "Enter key: \n";
            cin >> k;
            decryption(k);
        }

    }
    else
    {
        cin >> k;
        decryption(k);
    }
    return 0;
}

