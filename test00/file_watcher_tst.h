// Copyright Sergei Rebrik 2014
// Distributed under the Boost Software License, Version 1.0. 
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
// 
// Repository and documentation:
// https://github.com/rebrik/cp_dir_watcher
// 
// Revision History:

#ifndef FILE_WATCHER_TST_H
#define	FILE_WATCHER_TST_H

#include "file_watcher.h"

namespace cp {
  
class file_watcher_tst_t : public file_watcher_t 
{

  public:
    virtual void on_file_created();
    virtual void on_file_opened();
    virtual void on_file_closed_write();
    virtual void on_file_closed_nowrite();
    virtual void on_file_deleted();
    virtual void on_file_moved_from();
    virtual void on_file_moved_to();
    virtual void on_file_modified();
    virtual void on_file_accessed();
    virtual void on_file_attrib_changed();

    virtual void on_timeout();

    std::string get_ev_counts_str();

};
  
} // namespace cp


#endif	// FILE_WATCHER_TST_H 

