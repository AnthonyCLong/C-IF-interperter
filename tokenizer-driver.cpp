#include <fstream>
#include "interpreter.h"

using namespace std;

int main()
{
 ifstream inFS;
  inFS.open("if.html");
  //int argc, char* argv[]
  //argv[argc-1]
  //"if.html"
  //"test-example.html"
   if (!inFS.is_open()) {
      cout << "Could not open file test-example.html" << endl;
      return 1; 
      }
 string line, story;
getline(inFS, line);
  
  while (inFS && line != "</html>")
        {
          story += line + '\n';
          getline(inFS, line);
        }
StoryTokenizer st(story);
interpreter interp(st);

interp.runStory();
  return 0;
}
