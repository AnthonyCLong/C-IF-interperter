#ifndef _COMMAND_H
#define _COMMAND_H

#include "storytokenizer.h"
#include <iostream>

class command
{
friend class interpreter;
public:
command (SectionToken text){command_string=text.getText(); command_type=text.getType();}
virtual void execute() = 0;
static void reset_ifcounter(){ifcounter=0;}

protected:
string command_string;
type command_type;
static int ifcounter;
static bool foundElse;
static bool inBlock;
static bool lastIF;
static type prev;
};
//--------------------------------------------------------------
class commandText: public command
{
using command::command;

public:
virtual void execute() override;
};
//--------------------------------------------------------------
class commandBlock: public command
{
public:
commandBlock(SectionToken text);
static void block_incriment(){commandBlock::block_index++;}
static bool getBlockBool(){return blockBool; }
static void setBlockBool(bool t){blockBool =t; }
virtual void execute() override;

private:
vector<command*> block_passages;
 static int block_index;
 bool ifcheck = false;
 static bool blockBool;
};
//--------------------------------------------------------------
class commandIf: public command
{
using command::command;
public:
virtual void execute() override;
};
//--------------------------------------------------------------
class commandElseif: public commandIf
{
using commandIf::commandIf;
public:
virtual void execute() override;
};
//--------------------------------------------------------------
class commandElse: public commandElseif
{
using commandElseif::commandElseif;
public:
virtual void execute() override;
};
//--------------------------------------------------------------
class commandGoto: public command
{
using command::command;
public:
virtual void execute() override;
};
//--------------------------------------------------------------
class commandSet: public command
{
using command::command;
public:
virtual void execute() override;
};
//--------------------------------------------------------------
class commandLink: public command
{
using command::command;
public:
virtual void execute() override;
private:
static vector<string> user_opts;
};

#endif