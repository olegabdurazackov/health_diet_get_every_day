#ifndef __TERM_EXAMPLE__
#define __TERM_EXAMPLE__

#include <stdio.h>
#include <iostream>


#define ESC "\033"

#define home() std::cout<<"\e[H"; // printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()    printf(ESC "[2J") //lear the screen, move to (1,1)
#define clear() std::cout<<"\e[2J";//   printf(ESC "[2J") //lear the screen, move to (1,1)
#define gotoxy(x,y)   printf(ESC "[%d;%dH", y, x);
#define move(x,y) std::cout<<"\e["<<y<<x<<"H";// printf(ESC "[%d;%dH", y, x);
#define visible_cursor() printf(ESC "[?251");
//Set Display Attribute Mode  <ESC>[{attr1};...;{attrn}m
#define resetcolor() std::cout<<"\e[0m"; //printf(ESC "[0m")
#define set_display_atrib(color) std::cout<<"\e["<<color<<"m" // printf(ESC "[%dm",color)
#define set_display_atrib_(color) std::cout<<"\e["<<color<<"m" // printf(ESC "[%dm",color)
#define set_atrib(color)  printf(ESC "[%dm",color)


//Format text
#define RESET     0
#define BOLD      1
#define BRIGH     2
#define UNDERSCORE 4
#define OFF_UNDERSCORE 24
#define UNDERSCORE_OFF 24
#define BLINK     5
#define OFF_BLINK 25
#define BLINK_OFF 25
#define REVERSE   7
#define OFF_REVERSE 27
#define REVERSE_OFF 27
#define HIDDEN    6

//Foreground Colours (text)
#define F_BLACK   30
#define F_RED     31
#define F_GREEN   32
#define F_YELLOW  33
#define F_BLUE    34
#define F_MAGENTA 35
#define F_CYAN    36
#define F_WHITE   37
#define F_DEFAULT_UNDERLINE 38
#define F_DEFAULT 39

//Background Colours
#define B_BLACK   40
#define B_RED     41
#define B_GREEN   42
#define B_YELLOW  44
#define B_BLUE    44
#define B_MAGENTA 45
#define B_CYAN    46
#define B_WHITE   47
#define B_DEFAULT 49

#endif
/*__TERM_EXAMPLE__*/
