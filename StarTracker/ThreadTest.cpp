// C++ program to implement tail
////used from https://www.geeksforgeeks.org/implement-your-own-tail-read-last-n-lines-of-a-huge-file/

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

#include <bits/stdc++.h>
using namespace std;

#define SIZE 100

// Utility function to sleep for n seconds
void sleep(unsigned int n)
{
  clock_t goal = n * 1000 + clock();
  while (goal > clock());
}

char oldwp[255];  //for checking if there is a new waypoint

void inputParse(string str){
  //std::string str = "1.88,2.66,3,4,5";

      std::vector<double> vect;

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
      }

      else if (vect.size() == 1){
        cout << "TagID: " << vect.at(0) << endl;
      }

      else{
        cout << "INVALID INPUT." << endl;
      }

      //for (i=0; i< vect.size(); i++)
          //std::cout << vect.at(i)<<std::endl;
}

// function to read last n lines from the file
// at any point without reading the entire file
void tail(FILE* in, int n)
{
  int count = 0;  // To count '\n' characters

  // unsigned long long pos (stores upto 2^64 – 1
  // chars) assuming that long long int takes 8
  // bytes
  unsigned long long pos;
  char wp[2*SIZE];

  // Go to End of file
  if (fseek(in, 0, SEEK_END))
  perror("fseek() failed");
  else
  {
    // pos will contain no. of chars in
    // input file.
    pos = ftell(in);

    // search for '\n' characters
    while (pos)
    {
      // Move 'pos' away from end of file.
      if (!fseek(in, --pos, SEEK_SET))
      {
        if (fgetc(in) == '\n')

        // stop reading when n newlines
        // is found
        if (count++ == n)
        break;
      }
      else
      perror("fseek() failed");
    }

    // print last n lines
    while (fgets(wp, sizeof(wp), in)){
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

// Creates a file and prints and calls tail() for
// 10 different values of n (from 1 to 10)
int main()
{
  string command = "'./build/bin/StarTrackerInput' &";
  string term = NEWTERMINAL + command;
  system(term.c_str());

//------------------------------------------------------------

//-------------------------------------------------------------

  FILE* fp;
  char buffer[SIZE];
  // Open file in binary mode
  // wb+ mode for reading and writing simultaneously
  fp = fopen("input.txt", "wb+");
  if (fp == NULL)
  {
    printf("Error while opening file");
    exit(EXIT_FAILURE);
  }

  // Dynamically add lines to input file
  // and call tail() each time
  while (true)
  {
    // flush the input stream before calling tail
    fflush(fp);

    // read last index lines from the file
    tail(fp, 1);

    // sleep for a bit
    //sleep(200);
  }
  /* close the file before ending program */
  fclose(fp);

  return 0;
}
