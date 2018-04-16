//For inputing with April Tags using a second window
#include "Input.h"
#include <iostream>

#ifdef __APPLE__
#define NEWTERMINAL "open -a Terminal -n "
#endif

#ifdef __unix__
#define NEWTERMINAL "gnome-terminal -e "
#endif

#ifdef __arm__
printf("Detected Raspberry Pi\n");
#define NEWTERMINAL "xterm -e "
#endif

#define SIZE 100

#include <bits/stdc++.h>

char oldwp[255];  //for checking if there is a new waypoint

using namespace std;

namespace AprilTags{
  double Input::getX(){
    return WPX;
  }
  double Input::getY(){
    return WPY;
  }

  void Input::inputParse(string str){
    //std::string str = "1.88,2.66,3,4,5";
    vect.clear();

    std::stringstream ss(str);

    double i;

    while (ss >> i)
    {
      vect.push_back(i);

      if (ss.peek() == ',')
      ss.ignore();
    }

    if (vect.size() == 2){
      cout <<
      "X: " << vect.at(0) << "  " <<
      "Y: " << vect.at(1) << endl;
      WPX = vect.at(0);
      WPY = vect.at(1);
    }

    else if (vect.size() == 1){
      cout << "TagID: " << vect.at(0) << endl;
    }

    else{
      cout << "INVALID INPUT." << endl;
    }
  }

  void Input::tail(int n)
  {
    int count = 0;  // To count '\n' characters

    // unsigned long long pos (stores upto 2^64 – 1
    // chars) assuming that long long int takes 8
    // bytes
    unsigned long long pos;
    char wp[2*SIZE];

    // Go to End of file
    if (fseek(fp, 0, SEEK_END))
    perror("fseek() failed");
    else
    {
      // pos will contain no. of chars in
      // input file.
      pos = ftell(fp);

      // search for '\n' characters
      while (pos)
      {
        // Move 'pos' away from end of file.
        if (!fseek(fp, --pos, SEEK_SET))
        {
          if (fgetc(fp) == '\n')

          // stop reading when n newlines
          // is found
          if (count++ == n)
          break;
        }
        else
        perror("fseek() failed");
      }

      // print last n lines
      while (fgets(wp, sizeof(wp), fp)){
        if (strcmp(wp,oldwp) != 0){
          //printf("NEW WP: %s", wp);
          inputParse(wp);
        }
        //check if there is new input
        for(int i = 0 ; i < sizeof(wp) ; i++)
        oldwp[i] = wp[i];
      }
    }
  }

  void Input::setup(FILE* FP, double COORDS[][2]){


   //for(int i; i<2.9; i++){
 	//memcpy(&COORDS[i][0], &coords[i][0], 32*sizeof(double));
    	//coords[i][0] = COORDS[i][0];

	//cout<<"TEST: "<< coords[i][0]<<endl;
   //}

	cout << "TESTESTEST" << coords[0][0] << endl;
	cout<<"TEST SIZE INTUP:   " << sizeof(COORDS)/sizeof(COORDS[0])<<endl;
//cout << "\nTEST COORDS MATRIX: " << COORDS[0][0] << COORDS[1][0] << COORDS[2][0] << COORDS[0][1] << COORDS[1][1] << COORDS[2][1]  << "\n";

    fp = FP;
    string command = "'./build/bin/StarTrackerInput' &";
    string term = NEWTERMINAL + command;
    system(term.c_str());
    //FILE* fp;
    char buffer[SIZE];
    // Open file in binary mode
    // wb+ mode for reading and writing simultaneously
    fp = fopen("input.txt", "wb+");
    if (fp == NULL)
    {
      printf("Error while opening file");
      exit(EXIT_FAILURE);
    }

  }
}
