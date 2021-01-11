#include "interpreter.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//STATIC DECLARATIONS  
vector<string> interpreter::link_choices;
unordered_map<string, bool> interpreter::variable_map;
unordered_map<string, int>interpreter::passage_map;
int interpreter::section_index= 0;
int interpreter::choice;
int commandBlock::block_index=0;
int command::ifcounter = -1;//-1
bool command::foundElse = false;
bool commandBlock::blockBool =false;
bool command::inBlock =false;
bool command::lastIF =false;
type command::prev =DEFAULT;
//STATIC DECLARATIONS  
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
interpreter::interpreter(StoryTokenizer st)
  {
 command_passages.resize(st.getSize());
 int pass = 0;
 int i=0;
  while (st.hasNextPassage())
     {
               PassageToken ptok = st.nextPassage();
               passage_map.emplace(ptok.getName(),pass++);
               PassageTokenizer pt(ptok.getText());
               while (pt.hasNextSection())
                    {
                             SectionToken stok = pt.nextSection();
                             command* buf;
                             switch (stok.getType())
                             {
                                    case LINK:
                                                 buf= new commandLink(stok);
                                                  break;
                                    case SET:
                                                  buf= new commandSet(stok);
                                                  break;
                                    case GOTO:
                                                  buf= new commandGoto(stok);
                                                  break;
                                     case IF:
                                                  buf= new commandIf(stok);
                                                  break;
                                    case ELSEIF:
                                                   buf= new commandElseif(stok);
                                                  break;
                                    case ELSE:
                                                   buf= new commandElse(stok);
                                                   break;
                                    case BLOCK:
                                                  buf= new commandBlock(stok);
                                                  break;
                                    case TEXT:
                                                   buf= new commandText(stok);
                                                   break;
                                    default:
                                                  cout << "  Unknown token:  ";
                            }
                            command_passages[i].push_back(buf);
                   }
                   i++;                                   
  }
 

  /*(for (int i = 0; i<command_passages.size();i++)
  {
  for(int j = 0; j<command_passages[i].size();j++)
 cout<<command_passages[i][j]->getCS()<<endl;
 cout<<endl;
  }*/
  }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 int interpreter::getPasPos(string name)
 {
         return passage_map[name];
 }
 //------------------------------------------------------------------------------
bool interpreter::getVarBool(string var)
 {
         return variable_map[var];
 }
 //------------------------------------------------------------------------------
void interpreter::setVarBool(string v,bool b)
{
      unordered_map<string,bool>::const_iterator got = variable_map.find (v);
      if ( got == variable_map.end() )
               {variable_map.insert({v,b});}
        else
               {variable_map[v] = b;}
}
//------------------------------------------------------------------------------
string interpreter::setChoice()
{
cout<<endl<<endl<<"What would you like to do?"<<endl;
for (int i=0; i< link_choices.size(); i++)
            {cout<<i+1<<". "<<link_choices.at(i)<<endl;}
getline(cin,user_choice);
return user_choice;
}
//------------------------------------------------------------------------------
 void interpreter::addChoice(string newchoice)
{
   interpreter::link_choices.push_back(newchoice);
}
//------------------------------------------------------------------------------
bool interpreter::check_match(string user)
{
      for(int i = 0; i<interpreter::link_choices.size();i++)
             {  
                  if (user == interpreter::link_choices.at(i))
                     return true;
              }
      cout<<"ERROR: please select an option form the list.";
      return false;
}
//------------------------------------------------------------------------------
void interpreter::clear()
      {
        while (!interpreter::link_choices.empty())
        interpreter::link_choices.pop_back();
      }
//------------------------------------------------------------------------------
void interpreter::incriment()
   {
         section_index=section_index+1;
   }
//------------------------------------------------------------------------------
void interpreter::setPasPos(string gtstr)
      {
            choice = getPasPos(gtstr);
            section_index = -1;
      }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void interpreter::runStory()
{
string str;
for (section_index=0; section_index< command_passages[choice].size();section_index++)
      { command_passages[choice][section_index]->execute();}

while(!interpreter::link_choices.empty())
      {
            str = setChoice();
            while(!check_match(str))
                  {str = setChoice();}
           choice =getPasPos(str);
            clear();
            
            command::prev =DEFAULT;
            command::reset_ifcounter();
//cout<<endl<<endl<<str<<endl<<endl<<endl;
            for (section_index=0; section_index< command_passages[choice].size();section_index++)
                              {command_passages[choice][section_index]->execute();}

      }          

}
