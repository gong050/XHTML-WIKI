//
//  parser.h
//  XHTML
//
//  Created by Alex Kustov on 26/03/2018.
//  Copyright © 2018 Alex Kustov. All rights reserved.
//

#include <string>
#include <fstream>

class Parser
{
public:
    Parser();
    ~Parser();
    void readFile(std::string msg);
    void saveResult(std::string path);
    void parsFile();
    
private:
    void scan();
    void parserHTML();
    void parserHEAD();
    void parserBODY();
    void parserCONTENT();
    void parserTAG();
    void parserTITLE();
    void parserB();
    void parserI();
    void parserH1();
    void parserH2();
    void parserP();
    void parserBR();
    void parserUL();
    void parserLI();
    void parserOL();
    void parserDL();
    void parserDT();
    void parserDD();
    
protected:
    std::string input;
    std::string output;
    std::string filePath;
    std::ofstream outputFile;
    int index;
    int inputSize;
    int TOKEN;
    bool b, i, h1, h2, p, ul, li, ol, dl, dt, dd;
};
