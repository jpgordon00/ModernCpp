#ifndef CMDLINE_CMDLINE_
#define CMDLINE_CMDLINE_

#include <vector>
#include <string>

// one symbol for label and one for value
#define FORMAT_SYMBOL_LABEL "%l"
#define FORMAT_SYMBOL_VALUE "%v"

// these are just defaults, each cmd type
// accepts multiple formats per type
#define FORMAT_NO_VALUE_DEF "-%l"
#define FORMAT_SINGLE_VALUE_DEF_0 "-%l=%v"
#define FORMAT_SINGLE_VALUE_DEF_1 "-%l%v"

// maximum occurences of each cmd when parsed, where the
// 'maxOccurences' value in each new instance of cmd will be set.
// assume 1 occurence by default
#define CMD_DEF_OCCURENCES_MAX 1

namespace cmdline {

class cmdLine {
 public:
  // disable copy constructor and assign op
  cmdLine(const cmdLine&) = delete;
  cmdLine& operator=(const cmdLine&) = delete;
}

// handle singleton in local namespace instead of
// class for code reduction
static std::shared_ptr<cmdLine>
cmdLine::getInstance();

// allowable types of commands:
// 'NO_VALUE' represents a command that expects to
// recieve only a single command with a label and no associated values.
// 'SINGLE_VALUE' represents a command that expects to
// recieve only a single command and an associated value.
// 'AMBIGUOUS_VALUE' represents a command that expects to
// recieve only a single command with a label and either
// no value or a single value.
// 'UNLABELED' represents a command that does not expect to recieve a label.
enum cmdType {
  NO_VALUE = 0,
  SINGLE_VALUE = 1,
  AMBIGUOUS_VALUE = 2,
  UNLABELED = 3;
}

enum valueType {
  STRING
}

// allow nested invokation of commands via a function
// naned 'action'
// no base implementation, instead implement in cmd
// invoked only if no parse exceptions
class invokable {
  virtual void action(cmd& parent) = 0;
}

// define instances of this class for each readable command
class cmd {
 public:
  // copy constructor shoul
  cmd(const cmd&);

  // turn on polymorphism by generating
  // a v-table
  virtual ~cmd();

 private:
  // list of allowable strings where each represents
  // a valid label that, when matched, will result
  // in this instance invoking the action func
  vector<string> labelAliases;

  // true if this command and any of its aliases should only be
  // counted once, invoking a parse error if multiples encountered
  bool unique;

  // string description of this command
  // intend a default if not provided
  std::string description;

  // type of command should never change
  const cmdType type;

  // maximum num of occurences for this command
  // to not trigger a parsing exp
  // where 0 implies any amount of occurances
  const int maxOccurances;

  // true if this command should exist atleast once
  // when parsed to avoid a parsing excep
  const bool neccesary;

}

// input is cmd object refs and command line arguments
// output is modified cmd objects with return values and
// CONDITIONS FOR PROPER PARSING:
// strict ordering, uniqueness, occurances, neccessaryness
// without strict ordering use linear search for first fitting cmd

// for strict ordering allow list of cmd refs

// allow for additional validation functions via lambdas and nesting
// once succefully parsed, nested cmds and lambdas should

class parser {
}
};

#endif