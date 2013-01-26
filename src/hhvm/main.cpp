/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "runtime/base/program_functions.h"
#include "hhvm/process_init.h"
#include "runtime/vm/embedded_repo.h"

int main(int argc, char** argv) {
  HPHP::register_process_init();
  std::string repo = HPHP::get_embedded_repo();
  if (repo.empty()) {
    return HPHP::execute_program(argc, argv);
  }
  std::vector<char*> args;
  args.insert(args.begin(), argv, argv + argc);
  args.push_back("-vRepo.Authoritative=true");
  args.push_back("-vRepo.Local.Mode=r-");
  repo = "-vRepo.Local.Path=" + repo;
  args.push_back(const_cast<char*>(repo.c_str()));
  return HPHP::execute_program(args.size(), &args[0]);
}
