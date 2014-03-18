// Copyright Sergei Rebrik 2014
// Distributed under the Boost Software License, Version 1.0. 
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
// 
// Repository and documentation:
// https://github.com/rebrik/cp_dir_watcher
// 
// Revision History:

#include <iostream>

#include "dir_watcher_tst.h"

using namespace std;
namespace cp
{

  //----------------------------------------------------------------------------
  void dir_watcher_tst_t::on_dir_deleted()
  {
    // dir watcher is invalid after the dir was deleted
    cout << get_dir_name() << ": on_dir_deleted()\n";
    // exit the loop to stop the program
    exit_ev_loop();
  }

  //----------------------------------------------------------------------------
  void dir_watcher_tst_t::on_dir_moved()
  {
    // dir watcher is invalid after the dir was moved
    cout << get_dir_name() << ": on_dir_moved()\n";
    // exit the loop to stop the program
    exit_ev_loop();
  }

  //----------------------------------------------------------------------------
  void dir_watcher_tst_t::on_dir_unmounted()
  {
    // SR note: has not been tested
    // dir watcher is invalid after the dir was unmounted
    cout << get_dir_name() << ": on_dir_unmounted()\n";
    // exit the loop to stop the program
    exit_ev_loop();
  }

  //----------------------------------------------------------------------------
  void dir_watcher_tst_t::on_dir_timeout()
  {
    cout << get_dir_name() << ": on_timeout()\n";
   
    // restart timeout (with possibly new value)
    restart_dir_timeout();    
    // exit the loop to stop the program
    exit_ev_loop(); 
  }
  
} // namespace cp