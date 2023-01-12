#include <iostream>
#include <cstring>  
#include <random> 
#include <regex>
using namespace std;

random_device rd;
uniform_int_distribution<int> dist1(0,1);
uniform_int_distribution<int> dist2(0,2);

//Replaces the non-terminal characters (based on the hierarchy of the grammar) with the best terminal characters of each rule(eg G->v M->ε)
void TerminalRemove(string &str){ 
    regex r1("Z");
    regex r2("K");
    regex r3("G");
    regex r4("M");

    str = regex_replace(str, r1, "(K)");
    str = regex_replace(str, r2, "GM");
    str = regex_replace(str, r3, "v");
    str = regex_replace(str, r4, "");
}

void GenString(string &str)
{   
    bool flag = false;
    static int i = 0;
    int pos,r;
    string s1,s2,s3,temp=str;
    char c;
    
    for (auto &ch : str) {
        if(ch == 'Z' || ch == 'K' || ch == 'G' || ch == 'M'){
            pos = str.find(ch);
            c = ch; //character replaced later used in printf
            s1 = str.substr(0,pos);
            s2 = str.substr(pos+1,str.length());
            switch (ch)
            {
            case 'Z':
                s3 = "(K)";
                break;
            case 'K':
                s3 = "GM";
                break;
            case 'G':
                r = dist1(rd);
                s3 = (r==0) ? "v" : "Z"; //coinflip if 0 get value v else get value Z
                break;
            case 'M':
                r = dist2(rd);
                if(r==0){
                    s3 = "-K";
                }else if(r==1){
                    s3 = "+K";
                }else{
                    s3 = "";
                }
            default:
                break;
            }
            str = s1+s3+s2;
            i++;
            break; //replace the first character determined by the grammar left-to-right
        }
        
    }
    printf("%s -> %s , replaced %c col.%i with '%s' \n",temp.c_str(),str.c_str(),c,pos,s3.c_str());

    if(str.find('Z')==-1 && str.find('K')==-1 && str.find('G')==-1 && str.find('M')==-1) 
        flag = true; //If no special characters are left stop

    if(i<=15){
        if(!flag){
            GenString(str);
        }
    }else{
        cout << "There are still non-terminal characters replacing...\n";
        TerminalRemove(str); //If non-terminal chars are left replace them with terminal ones
    }
}


int main()
{
    string str = "Z"; //root
    GenString(str);
    cout << "\nFinal string is: " << str;
}