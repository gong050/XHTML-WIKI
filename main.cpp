    //
//  main.cpp
//  XHTML
//
//  Created by Alex Kustov on 26/03/2018.
//  Copyright © 2018 Alex Kustov. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"
#define ERROR_WITH_FILE -1

int main(int argc, const char * argv[]) {
    Parser pars;
    std::string path;
    std::ifstream file;
    std::string inputMsg;

    std::cout << "Write file path : " << std::endl;
    std::cin >> path;
    
    file.open(path);
    getline(file, inputMsg, '\0');
    file.close();

    pars.readFile(inputMsg);
    
    std::cout << "Where to save the file?" << std::endl;
    std::cin >> path;
    
    pars.saveResult(path);
}
