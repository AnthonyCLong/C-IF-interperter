#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "command.h"

class interpreter{
   public:
      interpreter( StoryTokenizer psg);
    static void setPasPos(string);
    static void addChoice(string);
    static void setVarBool(string,bool);
    static void incriment();
    static int getPasPos(string);
    static bool getVarBool(string);
    string setChoice();
    bool check_match(string);
    void clear();
    void runStory();

   private:
  vector<vector<command*>> command_passages;
   static unordered_map<string, int> passage_map;
  static unordered_map<string, bool> variable_map;
  static vector<string> link_choices;
  static int choice;
  static int section_index;
  string user_choice;
};

#endif