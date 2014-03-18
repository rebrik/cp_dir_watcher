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
#include <sstream>

#include "file_watcher_tst.h"

using namespace std;

namespace cp
{
  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_created()
  {
    cout << get_file_name() << ": on_file_created()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_opened()
  {
    cout << get_file_name() << ": on_file_opened()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_closed_write()
  {
    cout << get_file_name() << ": on_file_closed_write()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_closed_nowrite()
  { 
    cout << get_file_name() << ": on_file_closed_nowrite()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_deleted()
  {
    cout << get_file_name() << ": on_file_deleted()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_moved_to()
  {
    cout << get_file_name() << ": on_file_moved_to()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_moved_from()
  {
    cout << get_file_name() << ": on_file_moved_from()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_modified()
  {
    cout << get_file_name() << ": on_file_modified()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_accessed()
  {
    cout << get_file_name() << ": on_file_accessed()\n";
  }
 
  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_file_attrib_changed()
  {
    cout << get_file_name() << ": on_file_attrib_changed()\n";
  }

  //----------------------------------------------------------------------------
  void file_watcher_tst_t::on_timeout()
  {
    cout << get_file_name() << ": on_timeout()" << endl;
  }
  
  //----------------------------------------------------------------------------
  string file_watcher_tst_t::get_ev_counts_str()
  {
    ostringstream sout;
    sout.str() = "";

    sout << "N events for file: " << get_file_name() << endl
    << "Created: " <<n_ev_created_ << "  Opened: " << n_ev_opened
    << "  Closed write: " << n_ev_closed_write_ << endl
    << "Moved to: " << n_ev_moved_to_ << "  Moved from: " << n_ev_moved_from_
    << "  Deleted: " << n_ev_deleted_ << endl
    << "Modified: " << n_ev_modified_ << "  Accessed: " << n_ev_accessed_ << endl
    << "Attrib. changed: " << n_ev_attrib_changed_
    << "  Timeout: " << n_ev_timeout_ << endl;
    
    return sout.str();
  }
  
  
}