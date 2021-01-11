#include "interpreter.h"

void commandText::execute() 
{
      
int quot = command_string.find("&quot");
while (quot!=std::string::npos)
      {
            command_string.replace(quot,6,"\"");
            quot = command_string.find("&quot");
      }      
if(((prev==ELSE||prev==IF )&&(inBlock==false))||(prev==BLOCK))
{cout<<endl;}
if(prev==IF&&lastIF==false)
{cout<<endl;}

cout<<command_string;
if (lastIF==true&&inBlock==true&&prev==BLOCK)
{cout<<endl;}
prev =TEXT;

}
//------------------------------------------------------------------------------
commandBlock::commandBlock(SectionToken text):command(text)
{
   PassageTokenizer Bl (command_string);
   while(Bl.hasNextSection())
   {
      SectionToken bsec = Bl.nextSection();
                                //cout<<bsec.getText();
                             command* bbuf;
                             switch (bsec.getType())
                             {
                                    case LINK:
                                                 bbuf= new commandLink(bsec);
                                                  break;
                                    case SET:
                                                  bbuf= new commandSet(bsec);
                                                  break;
                                    case GOTO:
                                                  bbuf= new commandGoto(bsec);
                                                  break;
                                     case IF:
                                                  bbuf= new commandIf(bsec);
                                                  break;
                                    case ELSEIF:
                                                   bbuf= new commandElseif(bsec);
                                                  break;
                                    case ELSE:
                                                   bbuf= new commandElse(bsec);
                                                   break;
                                    case BLOCK:
                                                  bbuf= new commandBlock(bsec);
                                                  break;
                                    case TEXT:
                                                   bbuf= new commandText(bsec);
                                                   break;
                                    default:
                                                  cout << "  Unknown token:  ";
                            }
                           block_passages.push_back(bbuf);
                   }
                   //cout<<endl;
   }
//------------------------------------------------------------------------------
void commandBlock::execute()  
{
inBlock=true;
block_incriment();
      
if(prev==IF)
{lastIF=true;}
else lastIF=false;

int blockhold = block_index;
bool tempBool = blockBool;
bool inBlockhold = inBlock;
bool tempelse = foundElse;
bool hold_lastIF =lastIF;
int index_hold = ifcounter;
blockBool =true;


for (block_index=0; block_index< block_passages.size();block_index++)
                  {block_passages[block_index]->execute();
                  inBlock =true;}  
if(prev!=GOTO)
{block_index = blockhold;}
commandBlock::blockBool = tempBool;
foundElse = tempelse;
inBlock = inBlockhold;
ifcounter = index_hold;
lastIF = hold_lastIF;
ifcounter--;
      
      
      prev =BLOCK;
      inBlock =false;
}
//------------------------------------------------------------------------------
void commandIf::execute()  
{      
    lastIF=true;  
         
if(command::ifcounter == -1)
     {command::ifcounter =0; }
       
else if ((command::ifcounter == 1)&& (foundElse == false)&&(commandBlock::getBlockBool() == false))
           {command::ifcounter =0;
           lastIF=false;
           }
         
      foundElse = false;
      ifcounter++;
      
      int i=0, j=0,t=0,r=0;
      bool given;
      string buf = command_string;
      i = (command_string.find_first_of("$")+1) ;
      buf = command_string.substr(i);
      j = (buf.find_first_of(32)) ;
      buf = buf.substr(0,j);
      
      t = command_string.find_last_of ('t');
      r =command_string.find_last_of ('r');
      if (r-t != 1 || t == std::string::npos)
               {given =false;}
      else given = true; 
      
     if(given != interpreter::getVarBool(buf))
            { 
                  lastIF=false; 
                  if(command::ifcounter>1)
                        {
                              commandBlock::block_incriment();
                        }
                  else
                     {interpreter::incriment();}
             }  
             else if((prev==BLOCK&&inBlock==false&&lastIF==true)||(prev==LINK&&inBlock==false))
             {cout<<endl;}
             
        
        
        prev =IF;     
}
//------------------------------------------------------------------------------
void commandElseif::execute() 
{      
     if ((command::ifcounter == 1)&& (foundElse == false)&&(commandBlock::getBlockBool() == false))
           {command::ifcounter =0; }
           
      foundElse = false;
      command::ifcounter++;
      
      int i=0, j=0,t=0,r=0;
      bool given;
      string buf = command_string;
      i = (command_string.find_first_of("$")+1) ;
      buf = command_string.substr(i);
      j = (buf.find_first_of(32)) ;
      buf = buf.substr(0,j);
      
      t = command_string.find_last_of ('t');
      r =command_string.find_last_of ('r');
      if (r-t != 1 || t == std::string::npos)
               {given =false;}
      else given = true; 
      
     if(given != interpreter::getVarBool(buf))
            { 
                  if(command::ifcounter>1)
                        {
                              commandBlock::block_incriment();
                        }
                  else
                     {interpreter::incriment();}
             }  
             
             
             prev =ELSEIF;
}
//------------------------------------------------------------------------------
void commandElse::execute()  
{   
command::foundElse =true;
if(command::ifcounter==0)
      {interpreter::incriment();}
else if (commandBlock::getBlockBool() ==true)
                        {
                        commandBlock::block_incriment();
                        }
         commandBlock::setBlockBool(false);
         
         
         prev =ELSE;
}
//------------------------------------------------------------------------------
void commandGoto::execute() 
{
      string buf = command_string;
      int i = (command_string.find("&quot;")+6) ;
      buf = command_string.substr(i);
      i = (command_string.find("&quot;"));
      buf = buf.substr(0,i);
       interpreter::setPasPos(buf);  
       
       prev =GOTO;
}
//------------------------------------------------------------------------------
void commandSet::execute()  
{
      int i=0, j=0, t=0, r=0; 
      bool temp;
      string buf = command_string;
      i = (command_string.find_first_of("$")+1) ;
      buf = command_string.substr(i);
      j = (buf.find_first_of(32)) ;
      buf = buf.substr(0,j);
      t = command_string.find_last_of ('t');
      r =command_string.find_last_of ('r');
      if (r-t != 1 || t == std::string::npos)
            {temp =false;}
      else {temp = true;} 
            
      interpreter::setVarBool(buf,temp);
     
     
      prev =SET;
}
//------------------------------------------------------------------------------
void commandLink::execute()  
{
   
      
      string buffer = command_string;
      int gt;
      gt = buffer.find("-&gt");
      if (gt!=std::string::npos)
            {buffer = buffer.substr(gt+1);}
      else
            {buffer = buffer.substr(2,buffer.size()-4); }
                           
       if(prev==LINK||prev==BLOCK||(prev==IF&&lastIF==false))
      {cout<<endl;}
      cout<<buffer;
      interpreter::addChoice(buffer);
      
      
      prev =LINK;      
}
//------------------------------------------------------------------------------