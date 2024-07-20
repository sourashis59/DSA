#include<bits/stdc++.h>

using namespace std;


/*
 * Supported operators: 
 *      binary: +, -, *, /
 *      unary: -
 * 
 * Precedence:
 *      unary -
 *      /, *
 *      +, -
 *      
 *      if operators with equal precedence are one after other:
 *      example: 1 - 2 + 3 
 *      parse tree should be: ((1 - 2) + 3), not (1 - (2 + 3))
 *      i.e., the left most operator should be operated in case of equal precedence 
 *      [similar for * and /]
 *       
 * Grammar: (right recursive, unambiguous)
 * ---------------------- 
 * E -> T - E 
 *      T + E
 *      T
 * 
 * T -> F * T
 *      F / T
 *      F
 * 
 * F -> -F
 *      (E)
 *      number
 * 
 * Problem with this:
 * -------------------
 *      for this example: 1 - 2 + 3
 *      The first production rule will match: E -> T - E
 *      which will generate parse tree: (1 - (...E: to be generated...))
 *      Which is wrong.
 *      
 * Solution grammar:
 *      We can modify the first grammar rule to fix this:
 *      E -> T {'+'|'-' T}   
 *      
 *      Similarly, 
 *      T -> F {'*'|'/' F}
 *      
 * 
 */
enum TokenType {
    NUMBER,
    ADD, 
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    OPENING_PARENTHESIS,
    CLOSING_PARENTHESIS
};


class Token {
public:
    static unordered_map<char, TokenType> char_to_type_map;
    
    TokenType type;
    string value;
    Token(TokenType type, const string &value): type(type), value(value) {}
};

unordered_map<char, TokenType> Token::char_to_type_map = {
    {'+', TokenType::ADD},
    {'-', TokenType::SUBTRACT},
    {'*', TokenType::MULTIPLY},
    {'/', TokenType::DIVIDE},
    {'(', TokenType::OPENING_PARENTHESIS},
    {')', TokenType::CLOSING_PARENTHESIS},
};



class Lexer {
public:
    //* parses the input stream and returns stream of tokens
    //* throws runttime_error if input is not valid
    static queue<Token> tokenize(const string &input) {
        //* init
        int pos = 0;
        
        queue<Token> q;
        while (pos < input.size()) {
            char curr = input[pos];
            if (isspace(curr)) {
                ++pos;
            } else if (isdigit(curr)) {
                q.push(Token(TokenType::NUMBER, readNumber(pos, input)));
            } else if (Token::char_to_type_map.count(curr)) {
                q.push(Token(Token::char_to_type_map[curr], string(1, curr)));
                ++pos;
            } else {
                throw runtime_error("invalid character in input!");
            }
        }
        return q;
    }

private:
    static string readNumber(int &pos, const string &input) {
        int start = pos;
        while (pos < input.size() && isdigit(input[pos])) ++pos;
        return input.substr(start, pos - start);
    }
};




//* Composite design pattern
//* abstract class (interface)
class Node {
public:
    virtual int evaluate() = 0;
    virtual string to_string() = 0;
};


class UnaryNegateNode: public Node {
    Node *node;
public:
    UnaryNegateNode(Node *node = nullptr): node(node) {}
    
    virtual int evaluate() {
        return - node->evaluate();
    }

    virtual string to_string() {
        string res = "(";
        res += "-";
        res += node->to_string();
        res += ")";
        return res;
    }
};

class AddNode: public Node {
    Node *left, *right;
public:
    AddNode(Node *left = nullptr, Node *right = nullptr): left(left), right(right) {}

    virtual int evaluate() {
        return left->evaluate() + right->evaluate();
    }
    
    virtual string to_string() {
        string res = "(";
        res += left->to_string();
        res += "+";
        res += right->to_string();
        res += ")";
        return res;
    }
};

class SubtractNode: public Node {
    Node *left, *right;
public:
    SubtractNode(Node *left = nullptr, Node *right = nullptr): left(left), right(right) {}

    virtual int evaluate() {
        return left->evaluate() - right->evaluate();
    }
    
    virtual string to_string() {
        string res = "(";
        res += left->to_string();
        res += "-";
        res += right->to_string();
        res += ")";
        return res;
    }
};

class MultiplyNode: public Node {
    Node *left, *right;
public:
    MultiplyNode(Node *left = nullptr, Node *right = nullptr): left(left), right(right) {}
    
    virtual int evaluate() {
        return left->evaluate() * right->evaluate();
    }

    virtual string to_string() {
        string res = "(";
        res += left->to_string();
        res += "*";
        res += right->to_string();
        res += ")";
        return res;
    }
};

class DivideNode: public Node {
    Node *left, *right;
public:
    DivideNode(Node *left = nullptr, Node *right = nullptr): left(left), right(right) {}

    virtual int evaluate() {
        return left->evaluate() / right->evaluate();
    }
    
    virtual string to_string() {
        string res = "(";
        res += left->to_string();
        res += "/";
        res += right->to_string();
        res += ")";
        return res;
    }
};

class NumberNode: public Node {
    string val;
public:
    NumberNode(const string &val): val(val) {}
    virtual int evaluate() {
        return stoi(val);
    }

    virtual string to_string() {
        // cout << "(";
        return val;
        // cout << ")";
    }
};



class Parser {
    class ParserHelper {
        const string *input;
        queue<Token> q;    
    public: 
        ParserHelper(const string &input): input(&input) {
            q = Lexer::tokenize(*this->input); 
        }

        Node *parse() {
            Node *parse_tree = parseE();
            if (!q.empty()) 
                throw runtime_error("Trailing characters!");
            
            return parse_tree;
        }

    private:
        Token peek() {
            return q.front();
        }
        
        bool match(TokenType type) {
            return (q.size() && q.front().type == type);
        }

        //* parse Expression
        Node *parseE() {
            Node *node = parseT();
            //* add and subtract operators have equal precedence
            //* if both are present left one should be evaluated first
            while (match(TokenType::ADD) || match(TokenType::SUBTRACT)) {
                TokenType oprtr = peek().type;
                q.pop(); //* consume
                Node *right_node = parseT();
                if (oprtr == TokenType::ADD) node = new AddNode(node, right_node);
                else node = new SubtractNode(node, right_node);
            }
            return node;
        }

        //* parse Term
        Node *parseT() {
            Node *node = parseF();
            //* multiply and divide operators have equal precedence
            //* if both are present left one should be evaluated first [that's why this while loop]
            while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
                TokenType oprtr = peek().type;
                q.pop(); //* consume
                Node *right_node = parseF();
                if (oprtr == TokenType::MULTIPLY) node = new MultiplyNode(node, right_node);
                else node = new DivideNode(node, right_node);
            }
            return node;
        }

        //* parse Factor
        Node *parseF() {
            if (match(TokenType::SUBTRACT)) {
                q.pop();
                return new UnaryNegateNode(parseF());
            }
            if (match(TokenType::NUMBER)) {
                Node* node = new NumberNode(peek().value);
                q.pop();
                return node;
            }
            if (match(TokenType::OPENING_PARENTHESIS)) {
                q.pop();
                Node *node = parseE();
                if (!match(TokenType::CLOSING_PARENTHESIS)) 
                    throw runtime_error("Missing closing parenthesis!");
                
                q.pop();
                return node;
            } 
            
            //* else 
            throw runtime_error("Invalid token!");
        }
    };

public:
    //* parses the input string and returns the root of the parse tree
    //* throws runtime_error if parsing is not successful
    static Node *parse(const string &input) {
        ParserHelper util(input);
        return util.parse();
    }
};

int main () {
    // string input = "1 + -1  / * 12";
    string input = "((1 +      3213) / 123 * 23 / 12 / 23 / 56 * (1 + (-2)))";
    string expected_output = "(((((((1+3213)/123)*23)/12)/23)/56)*(1+(-2)))";
    // string input = "1 - 2 + 3";
    // string input = "(1+(4+5+2)-3)+(6+8)";
    // Lexer lexer;
    // queue<Token> q = lexer.tokenize(input);

    // while (q.size()) {
    //     Token token = q.front();
    //     q.pop();

    //     cout << token.value /*<< ", " << token.type*/ << endl; 
    // }

    Node *parseTree = Parser::parse(input);

    string parse_tree_string = parseTree->to_string();
    cout << "\nparse tree: " << parse_tree_string;
    cout << "\nis it equal?: " << (parse_tree_string == expected_output);

    printf("\nRes= %d", parseTree->evaluate());
    printf("\n\n\n");
    return 0;
}
