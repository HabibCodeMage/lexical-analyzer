// lexical analyzer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<thread>
#include<vector>
#include<map>
#include <utility>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;
const int buffersize = 4096;
long int offset = 0L;
int variablesloc = 201;
map<int, vector<string>> symboltable;
string maketrime(string id)
{
    int i = 0;
    string tobereturn;
    for (; i < id.length() and i < 10; ++i)
    {
        tobereturn += id[i];
    }
    for (; i < id.length(); ++i)
    {
        tobereturn += toupper (id[i]);
    }
    return tobereturn;
}
pair<int,int> installID(string id)
{
    if (symboltable[121].at(0) == id)
        return make_pair(false,121);
    else if (symboltable[122].at(0) == id)
        return make_pair(false, 122);
    else if (symboltable[123].at(0) == id)
        return make_pair(false, 123);
    else if (symboltable[124].at(0) == id)
        return make_pair(false, 124);
    else if (symboltable[125].at(0) == id)
        return make_pair(false, 125);
    else if (symboltable[126].at(0) == id)
        return make_pair(false, 126);
    else if (symboltable[127].at(0) == id)
        return make_pair(false, 127);
    else if (symboltable[128].at(0) == id)
        return make_pair(false, 128);
    else if (symboltable[129].at(0) == id)
        return make_pair(false, 129);
    else if (symboltable[130].at(0) == id)
        return make_pair(false, 130);
    else if (symboltable[131].at(0) == id)
        return make_pair(false, 131);
    else if (symboltable[132].at(0) == id)
        return make_pair(false, 132);
    else if (symboltable[133].at(0) == id)
        return make_pair(false, 133);
    else if (symboltable[134].at(0) == id)
        return make_pair(false, 134);
    else if (symboltable[135].at(0) == id)
        return make_pair(false, 135);
    else if (symboltable[136].at(0) == id)
        return make_pair(false, 136);
    else if (symboltable[137].at(0) == id)
        return make_pair(false, 137);
    else if (symboltable[138].at(0) == id)
        return make_pair(false, 138);
    else if (symboltable[139].at(0) == id)
        return make_pair(false, 139);
    else if (symboltable[140].at(0) == id)
        return make_pair(false, 140);
    else if (symboltable[141].at(0) == id)
        return make_pair(false, 141);
    else if (symboltable[142].at(0) == id)
        return make_pair(false, 142);
    else if (symboltable[120].at(0) == id)
        return make_pair(false, 120);
    else if (symboltable[200].at(0) == id)
        return make_pair(false, 200);
    else
    {
        if (id.length() > 25)
        {

            id = id.substr(0, 25);
        }
        string trimmed = maketrime(id);
        for (int x = 201; x < variablesloc; ++x)
        {
           
            if ( trimmed==maketrime(symboltable[x].at(0)))
            {
                return make_pair(true, x);
            }
        }
        symboltable[variablesloc] = {id};
        return  make_pair(true,variablesloc++);
    }

}
void readbuffer(fstream& filhandle, char *);
struct token {
    string lexeme;
    string name;
    string attribute;
    int row;
    string column;
};
int column = 1;
int row = 1;
int numofcharacters=0;
vector<token> lexemes;
int main()
{
    symboltable[121] = { "AND" };
    symboltable[122] = { "ARRAY" };
    symboltable[123] = { "BEGIN" };
    symboltable[124] = { "DIV" };
    symboltable[125] = { "DO" };
    symboltable[126] = { "ELSE" };
    symboltable[127] = { "END" };
    symboltable[128] = { "FUNCTION" };
    symboltable[129] = { "IF" };
    symboltable[130] = { "INTEGER" };
    symboltable[131] = {"MOD"};
    symboltable[132] = { "NOT" };
    symboltable[133] = { "OF" };
    symboltable[134] = { "OR" };
    symboltable[135] = { "PROCEDURE" };
    symboltable[136] = { "PROGRAM" };
    symboltable[137] = { "REAL" };
    symboltable[138] = { "READLN" };
    symboltable[139] = { "THEN" };
    symboltable[140] =  {"VAR" };
    symboltable[141] = {"WHILE" };
    symboltable[142] = {"WRITELN" };
    symboltable[120] = {"EOF" };
    symboltable[200] ={ "ERROR" };


    fstream handle;
    handle.open("program.txt", ios::in);
    char* firstbuffer = new char[buffersize];
    char* secondbuffer = new char[buffersize];

    if (handle)
    {
        thread first(readbuffer,std::ref(handle) ,std::ref(firstbuffer));
        first.join();
        char* forward = &firstbuffer[0];
        bool isfirstbuffer = true;
        bool issecondbuffer = false;
        
        while (forward)
        {
            if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
            {

                thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                second.join();
                issecondbuffer = true;
                isfirstbuffer = false;
                forward = &secondbuffer[0];
            }
            else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
            {
                thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                first.join();
                issecondbuffer = false;
                isfirstbuffer = true;
                forward = &firstbuffer[0];
            }
            else if(*forward=='=')
            {
                token object;
                object.lexeme = "=";
                object.name = "relop";
                object.attribute = "EQ";
                object.row = row;
                object.column =std::to_string( column);
                lexemes.push_back(object);
            }
            else if (*forward=='<')
            {
                string startcolumn = std::to_string(column);
                forward += 1;
                column += 1;
                if (forward == &firstbuffer[buffersize-1])
                {
                    thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                    second.join();
                    forward = &secondbuffer[0];
                }
                if (forward == &secondbuffer[buffersize-1])
                {
                    thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                    first.join();
                    forward = &firstbuffer[0];
                }
                if (*forward == '=')
                {
                    token object;
                    object.lexeme = "<=";
                    object.name = "relop";
                    object.attribute = "LE";
                    object.row = row;
                    object.column = startcolumn+"-"+std::to_string(column);
                    lexemes.push_back(object);
                }
                else if (*forward == '>')
                {
                    token object;
                    object.lexeme = "<>";
                    object.name = "relop";
                    object.attribute = "NE";
                    object.row = row;
                    object.column = startcolumn + "-" + std::to_string(column);
                    lexemes.push_back(object);
                }
                else
                {
                    token object;
                    object.lexeme = "<";
                    object.name = "relop";
                    object.attribute =  "LT";
                    object.row = row;
                    column -= 1;
                    object.column = startcolumn;
                    lexemes.push_back(object);
                    forward -=1 ;

                }
            }
            else if (*forward == '>')
            {
                string startcolumn = std::to_string(column);
                forward += 1;
                column+=1;
                if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                {

                    thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                    second.join();
                    issecondbuffer = true;
                    isfirstbuffer = false;
                    forward = &secondbuffer[0];
                }
                else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                {
                    thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                    first.join();
                    issecondbuffer = false;
                    isfirstbuffer = true;
                    forward = &firstbuffer[0];
                }

                if (*forward == '=')
                {
                    token object;
                    object.lexeme = ">=";
                    object.name = "relop";
                    object.attribute = "GE";
                    object.row = row;
                    object.column = startcolumn + "-" + std::to_string(column);
                    lexemes.push_back(object);
                }
                else
                {
                    token object;
                    object.name = "relop";
                    object.lexeme = ">";
                    object.attribute =  "GT";
                    object.row = row;
                    column -= 1;
                    object.column = startcolumn;
                    lexemes.push_back(object);
                    forward -=1;
                }
            }
            else if (*forward=='+')
            {
                token object;
                object.lexeme = "+";
                object.name = "addop";
                object.attribute =  "+";
                object.row = row;
                object.column = std::to_string( column);
                lexemes.push_back(object);
            }
            else if (*forward == '-')
            {
                token object;
                object.lexeme = "-";
                object.name = "addop";
                object.attribute =  "-";
                object.row = row;
                object.column = std::to_string(column);
                lexemes.push_back(object);
            }
            else if (*forward == '*')
            {
                token object;
                object.lexeme = "*";
                object.name = "mulop";
                object.attribute =  "*";
                object.row = row;
                object.column = std::to_string(column);
                lexemes.push_back(object);
            }
            else if (*forward == '/')
            {
                token object;
                object.lexeme = "/";
                object.name = "mulop";
                object.attribute =  "/";
                object.row = row;
                object.column = std::to_string(column);
                lexemes.push_back(object);
            }
            else if (*forward == ':')
            {
            string startcolumn = std::to_string(column);
            forward += 1;
            column += 1;
            if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
            {

                thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                second.join();
                issecondbuffer = true;
                isfirstbuffer = false;
                forward = &secondbuffer[0];
            }
            else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
            {
                thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                first.join();
                issecondbuffer = false;
                isfirstbuffer = true;
                forward = &firstbuffer[0];
            }

                  if (*forward=='=')
                  {
                      token object;
                      object.lexeme = ":=";
                      object.name = "assignop";
                      object.row = row;
                      object.column = startcolumn + "-" + std::to_string(column);
                      lexemes.push_back(object);
                  }
                  else
                  {
                      token object;
                      object.name = "COLON";
                      column -= 1;
                      object.lexeme = ":";
                      object.row = row;
                      object.column = std::to_string(column);
                      lexemes.push_back(object);
                      forward -=1;

                  }
             
            }
            else if (*forward==';')
            {
                    token object;
                    object.lexeme = ";";
                    object.name = "SEMICOL";
                    object.row = row;
                    object.column = std::to_string(column);
                    lexemes.push_back(object);
            

            }
            else if (*forward == ',')
            {
                 token object;
                 object.lexeme = ",";
                 object.name = "COMMA";
                 object.row = row;
                 object.column = std::to_string(column);
                  lexemes.push_back(object);


            }
            else if (*forward == '.')
            {
            token object;
            object.lexeme = ".";
            object.name = "DOT";
            object.row = row;
            object.column = std::to_string(column);
            lexemes.push_back(object);


            }
            else if (*forward == '(')
            {
            token object;
            object.lexeme = "(";
            object.name = "LB";
            object.row = row;
            object.column = std::to_string(column);
            lexemes.push_back(object);


            }
            else if (*forward == ')')
            {
            token object;
            object.lexeme = ")";
            object.name = "RB";
            object.row = row;
            object.column = std::to_string(column);
            lexemes.push_back(object);


            }
            else if (*forward == '[')
            {
            token object;
            object.lexeme = "[";
            object.name = "LP";
            object.row = row;
            object.column = std::to_string(column);
            lexemes.push_back(object);


            }
            else if (*forward == ']')
            {
            token object;
            object.lexeme = "]";
            object.name = "RP";
            object.row = row;
            object.column = std::to_string(column);
            lexemes.push_back(object);


            }
            else if (*forward == '{')
            {
            for(;*forward!='}' || *forward=='\0'; ++forward)
                {
                if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                {

                    thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                    second.join();
                    issecondbuffer = true;
                    isfirstbuffer = false;
                    forward = &secondbuffer[0];
                }
                else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                {
                    thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                    first.join();
                    issecondbuffer = false;
                    isfirstbuffer = true;
                    forward = &firstbuffer[0];
                }
                else if (*forward=='\0')
                {
                    break;
                }
                else if (*forward!='\0')
                {
                    column += 1;
                }

            }

            }
            
            else if (*forward == '$')
            {

            token object;
            object.lexeme = "$";
            object.name = "DOLLAR";
            object.row = row;
            object.column = std::to_string(column);
            lexemes.push_back(object);
            }
            else if (isalpha(*forward))
            {
            string columnbegan = std::to_string(column);
            char* lexemebegan = forward;
            forward += 1;
            column += 1;
                for (; isalnum(*forward) || *forward=='\0'; ++forward)
                {

                    if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                    {

                        thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                        second.join();
                        issecondbuffer = true;
                        isfirstbuffer = false;
                        forward = &secondbuffer[0];
                    }
                    else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer)+1 == buffersize  )
                    {
                        thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                        first.join();
                        issecondbuffer = false;
                        isfirstbuffer = true;
                        forward = &firstbuffer[0];
                    }
                    else if (*forward=='\0')
                    {
                        break;
                    }
                    else if (*forward != '\0')
                    {
                        column += 1;
                    }

                }

                string id;
                while (lexemebegan!=forward)
                {
                    //forward=='\0' and strlen(forward)==buffersize-2 and isfirstbuffer
                    if (*lexemebegan == '\0' and issecondbuffer )
                    {
                        
                        lexemebegan = &secondbuffer[0];
                    }
                    if (*lexemebegan == '\0' and isfirstbuffer)
                    {
                        lexemebegan = &firstbuffer[0];
                    }

                    id += *lexemebegan;
                    lexemebegan += 1;
                }
                forward -= 1;
                column -= 1;
                pair<bool,int> loc = installID(id);
                if (loc.first)
                {

                    token object;
                    object.lexeme = id;
                    object.name = "id";
                    object.attribute = std::to_string(loc.second);
                    object.row = row;
                    object.column = columnbegan+"-"+std::to_string(column);
                    lexemes.push_back(object);

                }
                else
                {
                    token object;
                    object.lexeme = id;
                    object.name = "RESERVEWORD";
                    object.attribute = id;
                    object.row = row;
                    object.column = columnbegan + "-" + std::to_string(column);
                    lexemes.push_back(object);
                }
            }

            else if(isspace(static_cast<unsigned char>(*forward)))
            {
                for (; isspace(static_cast<unsigned char>(*forward)); ++forward)
                {
                    if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                    {

                        thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                        second.join();
                        issecondbuffer = true;
                        isfirstbuffer = false;
                        forward = &secondbuffer[0];
                    }
                    else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                    {
                        thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                        first.join();
                        issecondbuffer = false;
                        isfirstbuffer = true;
                        forward = &firstbuffer[0];
                    }
                    else if (*forward == '\n')
                    {
                        row += 1;
                        column = 1;
                    }
                    else if (*forward=='\0')
                    {
                        break;
                    }
                    else if (*forward!='\0')
                    {
                        column += 1;
                    }

                }
                forward -= 1;
                column -= 1;
            }
            else if (isdigit(*forward))
            {
                char* lexemebegan = forward;
                string columnbegain = std::to_string(column);
                for (; isdigit(*forward) || *forward=='\0'; ++forward)
                {
                    if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                    {

                        thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                        second.join();
                        issecondbuffer = true;
                        isfirstbuffer = false;
                        forward = &secondbuffer[0];
                    }
                    else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                    {
                        thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                        first.join();
                        issecondbuffer = false;
                        isfirstbuffer = true;
                        forward = &firstbuffer[0];
                    }
                    else if (*forward=='\0')
                    {
                        break;
                    }
                    else if (*forward!='\0')
                    {
                        column += 1;
                    }


                }
                if (!(isdigit(*forward)) and *forward!='.' and *forward !='E')
                {
                    string num;
                    while (lexemebegan != forward)
                    {
                        if (*lexemebegan == '\0' and issecondbuffer)
                        {

                            lexemebegan = &secondbuffer[0];
                        }
                        if (*lexemebegan == '\0' and isfirstbuffer)
                        {
                            lexemebegan = &firstbuffer[0];
                        }
                        num += *lexemebegan;
                        lexemebegan += 1;
                    }
                    column -= 1;
                    token object;
                    object.lexeme = num;
                    object.name = "int";
                    object.attribute =num;
                    object.row = row;
                    object.column = columnbegain+'-'+std::to_string(column);
                    lexemes.push_back(object);
                    forward-= 1;
                }
                else if (*forward == '.')
                {
                    forward += 1;
                    column += 1;
                    if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                    {

                        thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                        second.join();
                        issecondbuffer = true;
                        isfirstbuffer = false;
                        forward = &secondbuffer[0];
                    }
                    else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                    {
                        thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                        first.join();
                        issecondbuffer = false;
                        isfirstbuffer = true;
                        forward = &firstbuffer[0];
                    }

                    if (isdigit(*forward))
                    {
                        for (; isdigit(*forward) || *forward=='\0'; ++forward)
                        {
                            if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                            {

                                thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                                second.join();
                                issecondbuffer = true;
                                isfirstbuffer = false;
                                forward = &secondbuffer[0];
                            }
                            else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                            {
                                thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                                first.join();
                                issecondbuffer = false;
                                isfirstbuffer = true;
                                forward = &firstbuffer[0];
                            }
                            else if (*forward=='\0')
                            {
                                break;
                            }
                            else if (*forward!='\0')
                            {
                                column += 1;
                            }


                        }
                        if (!(isdigit(*forward)) and *forward!='E')
                        {
                            string num;
                            while (lexemebegan != forward)
                            {
                                if (*lexemebegan == '\0' and issecondbuffer)
                                {

                                    lexemebegan = &secondbuffer[0];
                                }
                                if (*lexemebegan == '\0' and isfirstbuffer)
                                {
                                    lexemebegan = &firstbuffer[0];
                                }
                                num += *lexemebegan;
                                lexemebegan += 1;
                            }
                            token object;
                            object.lexeme = num;
                            object.name = "float";
                            object.attribute = num;
                            object.row = row;
                            object.column = columnbegain+"-" + std::to_string(column);
                            lexemes.push_back(object);
                            forward -= 1;

                        }
                        else if (*forward=='E')
                        {
                            forward += 1;
                            column += 1;
                            if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                            {

                                thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                                second.join();
                                issecondbuffer = true;
                                isfirstbuffer = false;
                                forward = &secondbuffer[0];
                            }
                            else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                            {
                                thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                                first.join();
                                issecondbuffer = false;
                                isfirstbuffer = true;
                                forward = &firstbuffer[0];
                            }

                            if (*forward == '+' || *forward == '-')
                            {
                                forward += 1;
                                column += 1;
                                if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                                {

                                    thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                                    second.join();
                                    issecondbuffer = true;
                                    isfirstbuffer = false;
                                    forward = &secondbuffer[0];
                                }
                                else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                                {
                                    thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                                    first.join();
                                    issecondbuffer = false;
                                    isfirstbuffer = true;
                                    forward = &firstbuffer[0];
                                }

                                if (isdigit(*forward))
                                {
                                    for (; isdigit(*forward) || *forward=='\0'; ++forward)
                                    {
                                        if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                                        {

                                            thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                                            second.join();
                                            issecondbuffer = true;
                                            isfirstbuffer = false;
                                            forward = &secondbuffer[0];
                                        }
                                        else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                                        {
                                            thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                                            first.join();
                                            issecondbuffer = false;
                                            isfirstbuffer = true;
                                            forward = &firstbuffer[0];
                                        }
                                        else if (*forward == '\0')
                                        {
                                            break;
                                        }
                                        else if (*forward != '\0')
                                        {
                                            column += 1;
                                        }


                                    }
                                    string num;
                                    while (lexemebegan!=forward)
                                    {
                                        if (*lexemebegan == '\0' and issecondbuffer)
                                        {

                                            lexemebegan = &secondbuffer[0];
                                        }
                                        if (*lexemebegan == '\0' and isfirstbuffer)
                                        {
                                            lexemebegan = &firstbuffer[0];
                                        }                   num += *lexemebegan;
                                        lexemebegan += 1;
                                    }
                                    column -= 1;
                                    forward -= 1;
                                    token object;
                                    object.lexeme = num;
                                    object.name = "sci";
                                    object.attribute = num;
                                    object.row = row;
                                    object.column = columnbegain+std::to_string(column);
                                    lexemes.push_back(object);

                                    
                                }
                            }
                            else if (isdigit(*forward))
                            {
                                forward += 1;
                                column += 1;
                                for (; isdigit(*forward) || *forward=='\0'; ++forward)
                                {
                                    if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                                    {

                                        thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                                        second.join();
                                        issecondbuffer = true;
                                        isfirstbuffer = false;
                                        forward = &secondbuffer[0];
                                    }
                                    else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                                    {
                                        thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                                        first.join();
                                        issecondbuffer = false;
                                        isfirstbuffer = true;
                                        forward = &firstbuffer[0];
                                    }
                                    else if (*forward == '\0')
                                    {
                                        break;
                                    }
                                    else if (*forward != '\0')
                                    {
                                        column += 1;
                                    }



                                }
                                string num;
                                while (lexemebegan != forward)
                                {
                                    if (*lexemebegan == '\0' and issecondbuffer)
                                    {

                                        lexemebegan = &secondbuffer[0];
                                    }
                                    if (*lexemebegan == '\0' and isfirstbuffer)
                                    {
                                        lexemebegan = &firstbuffer[0];
                                    }
                                    num += *lexemebegan;
                                    lexemebegan += 1;
                                }
                                forward -= 1;
                                column -= 1;
                                token object;
                                object.lexeme = num;
                                object.name = "sci";
                                object.attribute = num;
                                object.row = row;
                                object.column = columnbegain+'-'+std::to_string(column);
                                lexemes.push_back(object);


                            }
                        }
                    }
                }
                else if (*forward == 'E')
                {
                    forward += 1;
                    column += 1;
                    if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                    {

                        thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                        second.join();
                        issecondbuffer = true;
                        isfirstbuffer = false;
                        forward = &secondbuffer[0];
                    }
                    else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                    {
                        thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                        first.join();
                        issecondbuffer = false;
                        isfirstbuffer = true;
                        forward = &firstbuffer[0];
                    }

                    if (*forward == '+' || *forward == '-')
                    {
                        forward += 1;
                        if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                        {

                            thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                            second.join();
                            issecondbuffer = true;
                            isfirstbuffer = false;
                            forward = &secondbuffer[0];
                        }
                        else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                        {
                            thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                            first.join();
                            issecondbuffer = false;
                            isfirstbuffer = true;
                            forward = &firstbuffer[0];
                        }

                        if (isdigit(*forward))
                        {
                            for (; isdigit(*forward) || *forward=='\0'; ++forward)
                            {
                                if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                                {

                                    thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                                    second.join();
                                    issecondbuffer = true;
                                    isfirstbuffer = false;
                                    forward = &secondbuffer[0];
                                }
                                else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                                {
                                    thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                                    first.join();
                                    issecondbuffer = false;
                                    isfirstbuffer = true;
                                    forward = &firstbuffer[0];
                                }
                                else if (*forward == '\0')
                                {
                                    break;
                                }
                                else if (*forward != '\0')
                                {
                                    column += 1;
                                }

                            }
                            string num;
                            while (lexemebegan != forward)
                            {
                                if (*lexemebegan == '\0' and issecondbuffer)
                                {

                                    lexemebegan = &secondbuffer[0];
                                }
                                if (*lexemebegan == '\0' and isfirstbuffer)
                                {
                                    lexemebegan = &firstbuffer[0];
                                }
                                num += *lexemebegan;
                                lexemebegan += 1;
                            }
                            forward -= 1;
                            column -= 1;
                            token object;

                            object.lexeme = num;
                            object.name = "sci";
                            object.attribute = num;
                            object.row = row;
                            object.column = columnbegain+'-' +std::to_string(column) ;
                            lexemes.push_back(object);


                        }
                    }
                    else if (isdigit(*forward))
                    {
                        forward += 1;
                        column += 1;

                        for (; isdigit(*forward) || *forward=='\0'; ++forward)
                        {
                            if (*forward == '\0' and isfirstbuffer and strlen(firstbuffer) + 1 == buffersize)
                            {

                                thread second(readbuffer, std::ref(handle), std::ref(secondbuffer));
                                second.join();
                                issecondbuffer = true;
                                isfirstbuffer = false;
                                forward = &secondbuffer[0];
                            }
                            else if (*forward == '\0' and issecondbuffer and strlen(secondbuffer) + 1 == buffersize)
                            {
                                thread first(readbuffer, std::ref(handle), std::ref(firstbuffer));
                                first.join();
                                issecondbuffer = false;
                                isfirstbuffer = true;
                                forward = &firstbuffer[0];
                            }
                            else if (*forward == '\0')
                            {
                                break;
                            }
                            else if (*forward != '\0')
                            {
                                column += 1;
                            }


                        }
                        string num;
                        while (lexemebegan != forward)
                        {
                            if (*lexemebegan == '\0' and issecondbuffer)
                            {

                                lexemebegan = &secondbuffer[0];
                            }
                            if (*lexemebegan == '\0' and isfirstbuffer)
                            {
                                lexemebegan = &firstbuffer[0];
                            }
                            num += *lexemebegan;
                            lexemebegan += 1;
                        }
                        forward -= 1;
                        column -= 1;
                        token object;
                        object.lexeme = num;
                        object.name = "sci";
                        object.attribute = num;
                        object.row = row;
                        object.column = columnbegain+'-'+std::to_string(column);
                        lexemes.push_back(object);


                    }

                }

            }
            else
            {
                break;
            }

            forward += 1;
            column += 1;

        }



    } 
    else
    {

        cerr << "File not Exist";
    }
    int tokenno = 1;
    int nofreservedwords=0, nofidentifiers=0, nofoperators=0, noffloat=0, nofcolon=0,
        nofsemicolon=0, noflb=0, nofrb=0, nofdot=0, nofsci=0, nofint=0;
    std::cout << left << setw(20) << "Token no" << left << setw(20) << "Line no" << left << setw(20) << "Column no" << left << setw(30) <<"Lexeme"  << left << setw(20) <<"Token"<<endl;

    for (auto it : lexemes)
    {
        std::cout << left << setw(20) << tokenno
            << left << setw(20) << it.row
            << left << setw(20) << it.column
            << left << setw(30) << it.lexeme;
        if (it.attribute.empty())
        {
            std::cout << "<" + it.name+">" << endl;
        }
        else
        {
            std::cout  << "<" + it.name + "," << it.attribute + ">" << endl;
        }
        if (it.name == "RESERVEWORD")
            nofreservedwords += 1;
        else if (it.name == "relop" || it.name == "addop" || it.name == "mulop" || it.name == "assignop")
            nofoperators += 1;
        else if (it.name == "float")
            noffloat += 1;
        else if (it.name == "int")
            nofint += 1;
        else if (it.name == "sci")
            nofsci += 1;
        else if (it.name == "id")
            nofidentifiers += 1;
        else if (it.name == "COLON")
            nofcolon += 1;
        else if (it.name == "SEMICOL")
            nofsemicolon += 1;
        else if (it.name == "LB")
            noflb += 1;
        else if (it.name == "RB")
            nofrb += 1;
        else if (it.name == "DOT")
            nofdot += 1;

        tokenno += 1;

    }
    cout << "NO OF RESERVEWORD=" << nofreservedwords << endl
        << "NO OF IDENTIFIERS=" << nofidentifiers << endl
        << "NO OF SEMICOLON=" << nofsemicolon << endl
        << "NO OF SEMICOLON=" << nofcolon << endl
        << "NO OF DOT=" << nofdot << endl
        << "NO OF Left paraenthesis=" << noflb << endl
        << "NO OF Right Paranthesis=" << nofreservedwords << endl
        << "NO OF int=" << nofint << endl
        << "NO OF float=" << noffloat << endl
        << "NO OF Scientific num=" << nofsci << endl;
}

void readbuffer(fstream& filhandle, char* buffer)
{

    int i=1;
    filhandle.get(buffer[0]);
    while (filhandle && i < (buffersize-1))
    {
        filhandle.get(buffer[i]);
        i += 1;
    }

    buffer[i-1] = '\0';
    numofcharacters += strlen(buffer);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
