#include <iostream>
#include <cstring>  
using namespace std;
  
void GenString(string &str)
{
    bool flag = false;
    static int i = 0;
    int r,pos;
    string s1,s2,s3,temp=str;
    char c;
    
    for (auto &ch : str) {
        if(ch == 'Z' || ch == 'K' || ch == 'G' || ch == 'M'){
            pos = str.find(ch);
            c = ch;
            s1 = str.substr(0,str.find(ch));
            s2 = str.substr(str.find(ch)+1,str.length());
            switch (ch)
            {
            case 'Z':
                s3 = "(K)";
                break;
            case 'K':
                s3 = "GM";
                break;
            case 'G':
                r = rand() % 2;
                s3 = (r==0) ? "v" : "Z"; //coinflip if 0 get value v else get value Z
                break;
            case 'M':
                r = rand() % 3;
                if(r==0){
                    s3 = "-K";
                }else if(r==1){
                    s3 = "+K";
                }else{
                    s3 = " ";
                }
            default:
                break;
            }
            str = s1+s3+s2;
            i++;
            break; //replace the first character determined by the grammar left-to-right
        }
        
    }
    printf("%s -> %s , replaced %c ln.%i with %s \n",temp.c_str(),str.c_str(),c,pos,s3.c_str());

    if(str.find('Z')==0 || str.find('K')==0 || str.find('G')==0 || str.find('M')==0) 
        flag = true;

    if(i<=20 && !flag) 
        GenString(str);
}


int main()
{
    string str = "Z"; //root
    srand(0); //get new random numbers each time the program runs

    GenString(str);
    cout << "Final string is: " << str;
}