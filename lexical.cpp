/*
 * lexical.cpp
 *
 */

#include <cctype>
#include <map>
using std::map;

#include "list_tokens.h"

static map<TokenType,string> tokenPrint = {
    { IF, "IF" },
    { SET, "SET" },
    { PRINT, "PRINT" },
    { LOOP, "LOOP" },
    { BEGIN, "BEGIN" },
    { END, "END" },
    
    { ID, "ID" },
    
    { ICONST, "ICONST" },
    { SCONST, "SCONST" },
    
    { PLUS, "PLUS" },
    { MINUS, "MINUS" },
    { STAR, "STAR" },
    { SLASH, "SLASH" },
    { LPAREN, "LPAREN" },
    { RPAREN, "RPAREN" },
    
    { SC, "SC" },
    { NL, "NL" },
    
    { ERR, "ERR" },
    
    { DONE, "DONE" },
};


ostream& operator<<(ostream& out, const Token& tok) {
    TokenType tt = tok.GetTokenType();
    out << tokenPrint[ tt ];
    if( tt == ID || tt == ICONST || tt == SCONST || tt == ERR ) {
        out << "(" << tok.GetLexeme() << ")";
    }
    return out;
}


static map<string,TokenType> kwmap = {
    { "if", IF },
    { "set", SET },
    { "print", PRINT },
    { "loop", LOOP },
    { "begin", BEGIN },
    { "end", END },
};

Token
id_or_kw(const string& lexeme, int linenum)
{
    TokenType tt = ID;
    
    auto kIt = kwmap.find(lexeme);
    if( kIt != kwmap.end() )
        tt = kIt->second;
    
    return Token(tt, lexeme, linenum);
}

Token
getNextToken(istream& in, int& linenum)
{
    enum LexState { BEGIN, INID, INSTRING, ININT, INCOMMENT } lexstate = BEGIN;
    string lexeme;
    char ch;
    bool sawEscape;
    
    while(in.get(ch)) {
        
        switch( lexstate ) {
            case BEGIN:
                if( ch == '\n' ) {
                    return Token(NL, "\n", linenum++);
                }
                
                if( isspace(ch) )
                    continue;
                
                lexeme = ch;
                
                if( isalpha(ch) ) {
                    lexstate = INID;
                }
                else if( ch == '"' ) {
                    lexstate = INSTRING;
                    sawEscape = false;
                }
                else if( isdigit(ch) ) {
                    lexstate = ININT;
                }
                else if( ch == '#' ) {
                    lexstate = INCOMMENT;
                }
                else {
                    TokenType tt = ERR;
                    switch( ch ) {
                        case '+':
                            tt = PLUS;
                            break;
                        case '-':
                            tt = MINUS;
                            break;
                        case '*':
                            tt = STAR;
                            break;
                        case '/':
                            tt = SLASH;
                            break;
                        case '(':
                            tt = LPAREN;
                            break;
                        case ')':
                            tt = RPAREN;
                            break;
                        case ';':
                            tt = SC;
                            break;
                    }
                    
                    return Token(tt, lexeme, linenum);
                }
                break;
                
            case INID:
                if( isalpha(ch) || isdigit(ch) ) {
                    lexeme += ch;
                }
                else {
                    in.putback(ch);
                    return id_or_kw(lexeme, linenum);
                }
                break;
                
            case INSTRING:
                if( sawEscape ) {
                    // last character was an escape, what's this one??
                    sawEscape = false;
                    if( ch == 'n' ) ch = '\n';
                    // otherwise... it's unchanged
                    lexeme += ch;
                    break;
                }
                
                if( ch == '\\' ) {
                    sawEscape = true;
                    break;
                }
                
                lexeme += ch;
                if( ch == '\n' ) {
                    return Token(ERR, lexeme, linenum);
                }
                if( ch == '"' ) {
                    lexeme = lexeme.substr(1, lexeme.length()-2);
                    return Token(SCONST, lexeme, linenum);
                }
                break;
                
            case ININT:
                if( isdigit(ch) ) {
                    lexeme += ch;
                }
                else if( isalpha(ch) ) {
                    lexeme += ch;
                    return Token(ERR, lexeme, linenum);
                }
                else {
                    in.putback(ch);
                    return Token(ICONST, lexeme, linenum);
                }
                break;
                
            case INCOMMENT:
                if( ch == '\n' ) {
                    in.putback(ch);
                    lexstate = BEGIN;
                }
                break;
        }
        
    }
    
    if( in.eof() )
        return Token(DONE, "", linenum);
    return Token(ERR, "some strange I/O error", linenum);
}

