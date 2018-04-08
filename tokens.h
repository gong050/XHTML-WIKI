//
//  tokens.h
//  XHTML
//
//  Created by Alex Kustov on 26/03/2018.
//  Copyright © 2018 Alex Kustov. All rights reserved.
//

enum
{
    LDIV,
    RDIV,
    HEAD,           // Тег <head>       ->      none
    HTML,           // Тег <html>       ->      none
    TITLE,          // Тег <title>      ->      == Title ==
    BODY,           // Тег <body>       ->      none
    B,              // Тег <b>          ->      '''text'''
    I,              // Тег <i>          ->      ''text''
    H1,             // Тег <h1>         ->      === Subtitle ===
    H2,             // Тег <h2>         ->      ==== Sub-subtitle ====
    P,              // Тег <p>          ->      /n/n
    BR,             // Тег <br/>        ->      /n
    UL,             // Тег <ul>         ->      none
    LI,             // Тег <li>         ->      #listIteam
    OL,             // Тег <ol>         ->      none
    DL,             // Тег <dl>         ->      none
    DT,             // Тег <dt>         ->      ; Example
    DD,             // Тег <dd>         ->      : Examples text
    endHEAD,
    endHTML,
    endTITLE,
    endBODY,
    endB,
    endI,
    endH1,
    endH2,
    endP,
    endUL,
    endLI,
    endOL,
    endDL,
    endDT,
    endDD
};

