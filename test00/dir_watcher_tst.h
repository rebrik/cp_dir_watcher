// Copyright Sergei Rebrik 2014
// Distributed under the Boost Software License, Version 1.0. 
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
// 
// Repository and documentation:
// https://github.com/rebrik/cp_dir_watcher
// 
// Revision History:

#ifndef DIR_WATCHER_TST_H
#define	DIR_WATCHER_TST_H

#include "dir_watcher.h"

namespace cp 
{

class dir_watcher_tst_t : public dir_watcher_t
{
  public:
    virtual void on_dir_moved();
    virtual void on_dir_deleted();
    virtual void on_dir_unmounted();
    virtual void on_dir_timeout();
};

}  // namespace cp



#endif	// DIR_WATCHER_TST_H 

