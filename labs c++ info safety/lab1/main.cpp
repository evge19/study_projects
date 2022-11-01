#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
using namespace std;
void encryption(int k)
{
    ifstream fin("../lab1/input.txt");
    ofstream fout("../lab1/output.txt");
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
    ifstream fin2("../lab1/output.txt");

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
    ofstream fout("../lab1/input.txt");
    //fout.open("ttt.txt");
    int n; //число паролей
    int l;// длина
    cout << "Enter number of passwords: " << endl;
    cin >> n;
    cout << "Enter length " << endl;
    cin >> l;
    //fout << l;
    string m[36]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","0","1","2","3","4","5","6","7","8","9"};
    for(int v=0; v<n;v++)
    {
        fout << endl;
        for(int k=0;k<l;k++)
        {
            int q;
            q=rand()&35;
            fout <<m[q];
        }
    }
    fout.close();
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
