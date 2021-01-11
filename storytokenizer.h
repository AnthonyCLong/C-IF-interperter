#ifndef STORYTOKENIZER_H
#define STORYTOKENIZER_H
#include <vector>

#include <unordered_map>

using namespace std;

enum type{LINK, SET, GOTO, IF, ELSEIF, ELSE, BLOCK, TEXT, DEFAULT};

class PassageToken {
   public:
      PassageToken(string str, string name);
      string getText();
      string getName();
   private:
   string passage;
   string name;
};
//--------------------------------------------------------------
class StoryTokenizer {
   public:
      StoryTokenizer(string str);
      bool hasNextPassage();
      PassageToken nextPassage();  
      int getSize();
   private:
      vector <PassageToken> passages;
         int pcounter = 0;
};
//--------------------------------------------------------------
class  SectionToken {
   public:
      SectionToken(string str,type det);
      string getText();
       type getType();
   private:
      string section;
      type text;
};
//--------------------------------------------------------------
class PassageTokenizer {
   public:
      PassageTokenizer(string str);
      SectionToken nextSection();
      bool hasNextSection();
   private:
   vector <SectionToken> sections;
   int scounter = 0;

};

#endif