#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string reverse(string s) {
    int j = s.length();
    for (int i = 0; i < j / 2; i++) {
        swap(s[i], s[j - i - 1]);
    }
    return s;
}

class Node {
public:
    string data;
    Node* next_sibling; // Pointer to the next sibling of a node
    Node* children; // Linked list to store the children of a node

    Node(string data) {
        this->data = data;
        this->next_sibling = nullptr;
        this->children = nullptr;
    }

    void add_child(Node* child) { // Adds a child to non-terminal nodes
        if (this->children == nullptr) {
            this->children = child;
        }
        else {
            Node* current = this->children;
            while (current->next_sibling != nullptr) {
                current = current->next_sibling;
            }
            current->next_sibling = child;
        }
    }
};

class ParserTree { // Tree class to construct the leftmost syntactical tree
private:
    Node* root;

public:
    ParserTree(Node* root) {
        this->root = root;
    }

    void add_child(Node* node, string data) { // Adds a child to non-terminal nodes
        if (node != nullptr) {
            Node* child = new Node(data);
            node->add_child(child);
        }
    }

    void print_tree(Node* node) { // Prints the leftmost syntactical tree in preorder        
        if (node == nullptr) {
            return;
        }
        cout << node->data << " ";
        Node* current = node->children;
        while (current != nullptr) {
            print_tree(current);
            current = current->next_sibling;
        }

    }

    Node* IsNewTerminal(Node* root) { // Finds the next non-terminal node that hasn't been analyzed
        string str = root->data;
        if (root == nullptr) {
            return nullptr;
        }
        if ((isupper(str[0])) && (root->children == nullptr)) {
            return root;
        }
        Node* current = root->children;
        while (current != nullptr) {
            Node* result = IsNewTerminal(current);
            if (result != nullptr) return result;
            current = current->next_sibling;
        }
        return nullptr;
    }
};

int main()
{
    string Grammar[11][3] = { {"G", "(M)", "("}, {"M", "YZ", "("}, {"Y", "G", "("}, {"Z", "e", ")"}, {"Z", "*M", "*"}, {"Z", "-M", "-"}, {"Z", "+M", "+"}, {"M", "YZ", "a"}, {"Y", "a", "a"}, {"M", "YZ", "b"}, {"Y", "b", "b"} };
    string expr;
    string stack = "G";
    Node* root = new Node("G");
    ParserTree Parser_Tree(root);
    bool flag = false;
    bool check = false;
    bool found;
    int i;
    cout << "Give an expression:\n";
    cin >> expr;
    while (!check) { // Checks if the given expression is terminal
        check = true;
        for (char& c : expr) {
            if ((c >= 65) && (c <= 90)) {
                check = false;
                cout << "Give a valid expression:\n";
                cin >> expr;
                break;
            }
        }
    }
    for (char& c : expr) { // Runs a pre-check on wether there are any terminal symbols not defined in the Grammar
        if ((c <= 39) || (c == 44) || (c >= 46 && c < 97) || (c > 98)) {
            expr = "";
            stack = "";
            break;
        }
    }
    while (!(expr.empty()) && !(stack.empty())) {
        char right = stack.back();
        char left = expr[0];
        if (!isupper(right)) { // If rightmost symbol of stack is terminal
            if ((right == left) && (expr.length() != 1) && (stack.length() != 1)) { // If current symbol of the stack and current symbol of the expression are the same, but neither of them is the last one in their respective strings
                stack.erase(stack.length() - 1, 1);
                expr.erase(0, 1);
            }
            else if ((right == left) && (expr.length() == 1)) { // If last symbol of the stack and last symbol of the expression are the same
                if (stack.length() == 1) {
                    stack.erase(stack.length() - 1, 1);
                    expr.erase(0, 1);
                    flag = true;
                }
                else {
                    expr = "";
                    stack = "";
                }
            }
        }
        else { // If rightmost symbol of stack is non-terminal
            found = false;
            i = 0;
            while ((!found) && (i < 11)) { // Seek appropriate production rule in the production table
                if ((Grammar[i][0][0] == right) && (Grammar[i][2][0] == left)) { // If there is an appropriate production rule in the Grammar
                    stack.erase(stack.length() - 1, 1);
                    string ch;
                    Node* input = new Node("");
                    input = Parser_Tree.IsNewTerminal(root);
                    for (char& c : Grammar[i][1]) {
                        ch = "";
                        ch += c;
                        Parser_Tree.add_child(input, ch);
                    }
                    if (Grammar[i][1][0] != 'e') {
                        stack.append(reverse(Grammar[i][1]));
                    }
                    found = true;
                }
                i++;
            }
            if (!found) { // If there is no appropriate production rule in the Grammar
                cout << "There are no production rules that match the given left and right parts within the grammar.\n ";
                break;
            }
        }
    }
    if (flag) {
        cout << "The expression has been successfully recognised.\n";
        cout << "The Leftmost Syntactical Tree of the given expression in Preorder is:\n";
        Parser_Tree.print_tree(root);
    }
    else {
        cout << "This expression can not be produced by the grammar.\n";
    }
}