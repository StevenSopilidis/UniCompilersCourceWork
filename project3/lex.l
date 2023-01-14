%{
#include "stdbool.h"
#include "string.h"

// checks if name of points for shape are correct
// @param points: name of points
// @param n: number of points
bool checkPoints(char* points,int n) {
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++) {
            if(points[i] == points[j])
                return false;
        }
    }
    return true;
}

// method that verifies user input
// @param input: input that we want to verify
// @param message: message printed if verification was successful
// @param error_message: message printed if verification failed
void verifyInput(char* input, char* message, char* error_message) {
    bool valid = checkPoints(input, strlen(input));
    if(valid)
        printf("%s", message);
    else
        printf("%s", error_message);
}

%}
%option noyywrap 
POINT [a-z]|[A-Z]
%%


"OCTAGON "{POINT}{POINT}{POINT}{POINT}{POINT}{POINT}{POINT}{POINT} {
    char* points = yytext + 8;
    verifyInput(points, "Valid octagon entered", "Octagon must be determined by 8 different points");
}


"HEPTAGON"{POINT}{POINT}{POINT}{POINT}{POINT}{POINT}{POINT} {
    char* points = yytext + 9;
    verifyInput(points, "Valid heptagon entered", "Heptagon must be determined by 7 different points");
}

"HEXAGON "{POINT}{POINT}{POINT}{POINT}{POINT}{POINT} {
    char* points = yytext + 8;
    verifyInput(points, "Valid hexagon entered", "Hexagon must be determined by 6 different points");
}

"PENTAGON "{POINT}{POINT}{POINT}{POINT}{POINT} {
    char* points = yytext + 9;
    verifyInput(points, "Valid pentagon entered", "Pentagon must be determined by 5 different points");
}
"SQUARE "{POINT}{POINT}{POINT}{POINT} {
    char* points = yytext + 7;
    verifyInput(points, "Valid square entered", "Square must be determined by 4 different points");
}
"TRIANGLE "{POINT}{POINT}{POINT} {
    char* points = yytext + 9;
    verifyInput(points, "Valid Triangle entered", "Triangle must be determined by 3 different points");
}
"LINE "{POINT}{POINT} {
    char* points = yytext + 5;
    verifyInput(points, "Valid Line entered", "Line must be determined by 2 different points");
}
"POINT "{POINT} {
    printf("Valid point entered");
}

.+ printf("%s", "Not recognized");

%%
int main(int argc, char* argv[]) {
    yylex();
}