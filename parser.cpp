//
//  parser.cpp
//  XHTML
//
//  Created by Alex Kustov on 26/03/2018.
//  Copyright © 2018 Alex Kustov. All rights reserved.
//

#include <fstream>
#include <string>
#include <iostream>
#include "parser.h"
#include "tokens.h"

#define PROBLEM_WITH_HTML   -1
#define PROBLEM_WITH_HEAD   -2
#define PROBLEM_WITH_TITLE  -3
#define ERROR_WITH_RANGE    -4
#define ERROR_WITH_B        -5
#define ERROR_WITH_I        -5
#define ERROR_WITH_H1       -6
#define ERROR_WITH_H2       -7
#define ERROR_WITH_P        -8
#define ERROR_WITH_UL       -9
#define ERROR_WITH_LI       -10
#define ERROR_WITH_OL       -11
#define ERROR_WITH_DL       -12
#define ERROR_WITH_DT       -13
#define ERROR_WITH_DD       -14
#define ERROR_WITH_TAG      -15

Parser::Parser()
{
    TOKEN = 0;
    index = 0;
    inputSize = 0;
    input = "";
    output = "";
    filePath = "";
    b = false;
    i = false;
    h1 = false;
    h2 = false;
    p = false;
    ul = false;
    li = false;
    ol = false;
    dl = false;
    dt = false;
    dd = false;
};

Parser::~Parser()
{
    outputFile.close();
};

void Parser::saveResult(std::string path)
{
    path += "result.txt";
    std::ofstream outputFile (path);
    outputFile << output;
};

void Parser::readFile(std::string msg)
{
    input = msg;
    inputSize = msg.size();
    parserHTML();
};

void Parser::scan()
{
    if(input.substr(index, 6) == "<head>")
    {
        index += 6;
        TOKEN = HEAD;
        return;
    };
    if(input.substr(index, 6) == "<html>")
    {
        index += 6;
        TOKEN = HTML;
        return;
    };
    if(input.substr(index, 7) == "<title>")
    {
        index += 7;
        TOKEN = TITLE;
        return;
    };
    if(input.substr(index, 6) == "<body>")
    {
        index += 6;
        TOKEN = BODY;
        return;
    };
    if(input.substr(index, 3) == "<b>")
    {
        index += 3;
        TOKEN = B;
        return;
    };
    if(input.substr(index, 3) == "<i>")
    {
        index += 3;
        TOKEN = I;
        return;
    };
    if(input.substr(index, 4) == "<h1>")
    {
        index += 4;
        TOKEN = H1;
        return;
    };
    if(input.substr(index, 4) == "<h2>")
    {
        index += 4;
        TOKEN = H2;
        return;
    };
    if(input.substr(index, 3) == "<p>")
    {
        index += 3;
        TOKEN = P;
        return;
    };
    if(input.substr(index, 6) == "<br />")
    {
        index += 6;
        TOKEN = BR;
        return;
    };
    if(input.substr(index, 4) == "<ul>")
    {
        index += 4;
        TOKEN = UL;
        return;
    };
    if(input.substr(index, 4) == "<li>")
    {
        index += 4;
        TOKEN = LI;
        return;
    };
    if(input.substr(index, 4) == "<ol>")
    {
        index += 4;
        TOKEN = OL;
        return;
    };
    if(input.substr(index, 4) == "<dl>")
    {
        index += 4;
        TOKEN = DL;
        return;
    };
    if(input.substr(index, 4) == "<dt>")
    {
        index += 4;
        TOKEN = DT;
        return;
    };
    if(input.substr(index, 4) == "<dd>")
    {
        index += 4;
        TOKEN = DD;
        return;
    };
    if(input.substr(index, 7) == "</head>")
    {
        index += 7;
        TOKEN = endHEAD;
        return;
    };
    if(input.substr(index, 7) == "</html>")
    {
        index += 7;
        TOKEN = endHTML;
        return;
    };
    if(input.substr(index, 8) == "</title>")
    {
        index += 8;
        TOKEN = endTITLE;
        return;
    };
    if(input.substr(index, 4) == "</b>")
    {
        index += 4;
        TOKEN = endB;
        return;
    };
    if(input.substr(index, 4) == "</i>")
    {
        index += 4;
        TOKEN = endI;
        return;
    };
    if(input.substr(index, 5) == "</h1>")
    {
        index += 5;
        TOKEN = endH1;
        return;
    };
    if(input.substr(index, 5) == "</h2>")
    {
        index += 5;
        TOKEN = endH2;
        return;
    };
    if(input.substr(index, 4) == "</p>")
    {
        index += 4;
        TOKEN = endP;
        return;
    };
    if(input.substr(index, 5) == "</ul>")
    {
        index += 5;
        TOKEN = endUL;
        return;
    };
    if(input.substr(index, 5) == "</li>")
    {
        index += 5;
        TOKEN = endLI;
        return;
    };
    if(input.substr(index, 5) == "</ol>")
    {
        index += 5;
        TOKEN = endOL;
        return;
    };
    if(input.substr(index, 5) == "</dl>")
    {
        index += 5;
        TOKEN = endDL;
        return;
    };
    if(input.substr(index, 5) == "</dt>")
    {
        index += 5;
        TOKEN = endDT;
        return;
    };
    if(input.substr(index, 5) == "</dd>")
    {
        index += 5;
        TOKEN = endDD;
        return;
    };
    if(input.substr(index, 7) == "</body>")
    {
        index += 7;
        TOKEN = endBODY;
        return;
    };
    if(input[index] == '<')
    {
        while(input[index] != '>') index++;
        index++;
    };
    TOKEN = -1;
    index++;
    return;
};

void Parser::parserHTML()
{
    scan();
    if(TOKEN != HTML)
    {
        std::cout << "Problem with <html>" << std::endl;
        exit(PROBLEM_WITH_HTML);
    };
    parserHEAD();
    scan();
    parserBODY();
    while(TOKEN != endHTML)
    {
        if(index == inputSize) exit(ERROR_WITH_RANGE);
        scan();
    }
    return;
};

void Parser::parserHEAD()
{
    while(TOKEN != HEAD)
    {
        if(index == inputSize) exit(ERROR_WITH_RANGE);
        scan();
    };
    
    if(TOKEN != HEAD)
    {
        std::cout << "Problem with <head>" << std::endl;
        exit(PROBLEM_WITH_HEAD);
    };

    while(TOKEN != TITLE)
    {
        if(index == inputSize) exit(ERROR_WITH_RANGE);
        scan();
    };
    
    if(TOKEN == TITLE)
    {
        parserTITLE();
    };
    while(TOKEN != endHEAD)
    {
        if(index == inputSize) exit(ERROR_WITH_RANGE);
        scan();
    }
    return;
};

void Parser::parserTITLE()
{
    output += "==";
    
    while(TOKEN != endTITLE)
    {
        if(index == inputSize) exit(ERROR_WITH_RANGE);
        scan();
        if(TOKEN != endTITLE) output += input[index - 1];
    };
    output += "==\n";
    return;
};

void Parser::parserBODY()
{
    while(TOKEN != BODY)
    {
        if(index == inputSize) exit(ERROR_WITH_RANGE);
        scan();
    };
    parserCONTENT();
    while(TOKEN != endBODY)
    {
        if(index == inputSize) exit(ERROR_WITH_RANGE);
        scan();
    }
    return;
};

void Parser::parserCONTENT()
{
    scan();
    parserTAG();
    return;
};

void Parser::parserTAG()
{
    while(TOKEN != endBODY)
    {
        while(TOKEN != LI && TOKEN != B && TOKEN != I && TOKEN != H1 && TOKEN != H2 && TOKEN != P && TOKEN != BR && TOKEN != UL && TOKEN != OL && TOKEN != DL && TOKEN != endB && TOKEN != endI && TOKEN != endH1 && TOKEN != endH2 && TOKEN != endP && TOKEN != endUL && TOKEN != endOL && TOKEN != endDL && TOKEN != endBODY && TOKEN != endLI)
        {
            if(index == inputSize) exit(ERROR_WITH_RANGE);
            output += input[index - 1];
            scan();
        };

        if(TOKEN == B)
        {
            b = true;
            parserB();
        };
        if(TOKEN == LI)
        {
            li = true;
            parserLI();
        };
        if(TOKEN == I)
        {
            i = true;
            parserI();
        };
        if(TOKEN == H1)
        {
            h1 = true;
            parserH1();
        };
        if(TOKEN == H2)
        {
            h2 = true;
            parserH2();
        };
        if(TOKEN == P)
        {
            p = true;
            parserP();
        };
        if(TOKEN == BR)
        {
            parserBR();
        };
        if(TOKEN == UL)
        {
            ul = true;
            parserUL();
        };
        if(TOKEN == OL)
        {
            ol = true;
            parserOL();
        };
        if(TOKEN == DL)
        {
            dl = true;
            parserDL();
        };
        if(TOKEN == endLI)
        {
            if(li == true) li = false; else exit(ERROR_WITH_LI);
            return;
        };
        if(TOKEN == endB)
        {
            if(b == true) b = false; else exit(ERROR_WITH_B);
            return;
        };
        if(TOKEN == endI)
        {
            if(i == true) i = false; else exit(ERROR_WITH_I);
            return;
        };
        if(TOKEN == endH1)
        {
            if(h1 == true) h1 = false; else exit(ERROR_WITH_H1);
            return;
        };
        if(TOKEN == endH2)
        {
            if(h2 == true) h2 = false; else exit(ERROR_WITH_H2);
            return;
        };
        if(TOKEN == endP)
        {
            if(p == true) p = false; else exit(ERROR_WITH_P);
            return;
        };
        if(TOKEN == endUL)
        {
            if(ul == true) ul = false; else exit(ERROR_WITH_UL);
            return;
        };
        if(TOKEN == endOL)
        {
            if(ol == true) ol = false; else exit(ERROR_WITH_OL);
            return;
        };
        if(TOKEN == endDL)
        {
            if(dl == true) dl = false; else exit(ERROR_WITH_DL);
            return;
        };
    };
    if(TOKEN == endBODY && !dl && !ol && !ul && !p && !h2 && !h1 && !i && !b) return; else exit(ERROR_WITH_TAG);
};

void Parser::parserB()
{
    output += "'''";
    scan();
    parserTAG();
    output += "'''";
    scan();
    return;
};

void Parser::parserI()
{
    output += "''";
    scan();
    parserTAG();
    output += "''";
    scan();
    return;
};

void Parser::parserH1()
{
    output += "===";
    scan();
    parserTAG();
    output += "===";
    scan();
    return;
};

void Parser::parserH2()
{
    output += "====";
    scan();
    parserTAG();
    output += "====";
    scan();
    return;
};

void Parser::parserP()
{
    output += "\n\n";
    scan();
    parserTAG();
    output += "\n\n";
    scan();
    return;
};

void Parser::parserBR()
{
    output += "\n";
    scan();
    return;
};

void Parser::parserUL()
{
    scan();
    parserTAG();
    scan();
    return;
};

void Parser::parserLI()
{
    output += "#";
    scan();
    parserTAG();
    scan();
    return;
};

void Parser::parserOL()
{
    scan();
    parserTAG();
    scan();
    return;
};

void Parser::parserDL()
{
    scan();
    parserTAG();
    scan();
    return;
};

void Parser::parserDT()
{
    output += "; ";
    scan();
    parserTAG();
    scan();
    return;
};

void Parser::parserDD()
{
    output += ": ";
    scan();
    parserTAG();
    scan();
    return;
};
