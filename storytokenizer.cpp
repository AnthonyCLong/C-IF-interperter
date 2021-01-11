#include "storytokenizer.h"
#include <iostream>

using namespace std;

StoryTokenizer::StoryTokenizer(string str)
{
  string name;
  int namestart;
  int nameend;
   int start= str.find("<tw-passagedata");   
   int end = str.find("</tw-storydata>");
   str = str.substr(start,end-start);
   //cout<<str;

   while(str.find("<tw-passagedata")!=std::string::npos)
   {
      start= 0;
      namestart = str.find("name")+6;
      int nameend =str.find('"', namestart);
      name=str.substr(namestart,nameend-namestart);
      end = (str.find("<tw-passagedata",start+1));
      if (end==std::string::npos)
         {end=str.find_last_of(">");}
      passages.emplace_back(str.substr (start,end), name);
      str = str.substr(end);
   }
}
//------------------------------------------------------------------------------
bool StoryTokenizer::hasNextPassage()
{
   if(pcounter<passages.size())
      {return true;}
   else {return false;}
}
//------------------------------------------------------------------------------
int StoryTokenizer::getSize()
{
return passages.size();
}
//------------------------------------------------------------------------------
PassageToken StoryTokenizer::nextPassage()      
{
if (hasNextPassage())
   {return passages.at(pcounter++);} 
else return(PassageToken("",""));
}
//------------------------------------------------------------------------------
PassageToken::PassageToken(string str, string nm)
{
   passage = str;
   name = nm;
}
//------------------------------------------------------------------------------
string PassageToken::getText()
{
   return passage;  
}
//------------------------------------------------------------------------------
string PassageToken::getName()
{
   return name;  
}

//------------------------------------------------------------------------------
PassageTokenizer::PassageTokenizer(string str)
{
   type text = DEFAULT;
   string temp;
   int start = str.find(">");
   int end = str.find("</");
   if ((start == std::string::npos )&& (end == std::string::npos))
            {str = str.substr(1,str.length()-2);}
  else 
            { str = str.substr (start+1,end-(start+1));}
  char first;
  while(!str.empty())
  {
         temp = str;
         start = str.find_first_not_of('\n');
        if (start==std::string::npos)
         {break;}
     //else if (text == LINK)
       //{str =str;}
         else //if((text==SET)||(text==TEXT)||(text==LINK)||(text==DEFAULT))
               {str =str.substr(start);}
         
         first = str.at(0);
         if (first == '(')
               {
                        end = str.find(")");
                        if(str.find("set")==1)
                        {text= SET;}
                        else if(str.find("go-to")==1)
                        {text= GOTO;}
                        else if(str.find("else-if")==1) 
                        {text= ELSEIF;}
                        else if(str.find("if")==1) 
                        {text= IF;}
                        else if(str.find("else")==1) 
                        {text= ELSE;}     
                        
                        temp = str.substr (0,end+1);
                        str = str.substr (end+1);
               }        
                        
         else if(first == '['||str.find(" [[")==0)
               {
                        end = str.find_first_of(']');
                        if(((str.find("[[")==0)&&(str.find("[[[")!=0))||(str.find(" [[")==0))
                              {
                                       if(str.find(" [[")==0)
                                       {str = str.substr (1);}
                                       end = str.find("]]")+1;
                                       text= LINK;
                              }
                        else if(text == ELSE||text == IF||text == ELSEIF)
                              {
                                       end = str.find_first_of(']');             
                                       int n=0,tab =0;
               
                                       while(n!=end)
                                             {
                                                   if(str.at(n)=='[')
                                                         {tab++;}
                                                   n++;
                                             }
                                       tab--;
                                       while(tab!=0)
                                             {
                                                      end = str.find("]",end+1);
                                                      tab--;
                                             }
                 
                                       text= BLOCK;
                              }
                              temp = str.substr (0,end+1);
                              str = str.substr (end+1);      
               }
       
         else
               {
                              if (str.at(0)==' ' && text!=LINK&& str!=" ")
                              {str=str.substr(str.find_first_not_of(' '));}
                              text= TEXT;
                              end =str.find_first_of("[(");
                              if(end ==std::string::npos)
                                       {
                                             temp = str;
                                             str="";
                                       }
                              else
                                       { 
                                             temp = str.substr (0,end);
                                             str = str.substr (end);
                                       }

               }
     
         sections.push_back(SectionToken(temp,text));
  }
}      
//------------------------------------------------------------------------------
SectionToken PassageTokenizer::nextSection()
{
   if(hasNextSection())
         {return sections.at(scounter++);}
   else return SectionToken("",DEFAULT);
}
//------------------------------------------------------------------------------
bool PassageTokenizer::hasNextSection()
{
   if(scounter<sections.size())
         {return true;}
   else return false;
}
//------------------------------------------------------------------------------
SectionToken::SectionToken(string str, type det)
{
   section = str;
   text = det;
}
//------------------------------------------------------------------------------
string SectionToken::getText()
{
   return section;
}
//------------------------------------------------------------------------------
type SectionToken::getType()
{
   return text;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
