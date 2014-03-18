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
#include "file_watcher_tst.h"

using namespace std;
using namespace cp;


//------------------------------------------------------------------------------
main (void)
{
  ev_loop_t *loop;
  loop = ev_default_loop (0); 
 
  dir_watcher_tst_t dir_w;
  dir_w.set_dir_name("./delme/"); // note the closing "/"
  dir_w.set_dir_timeout(60.0);
  
  // setup the list of watched files
  file_watcher_tst_t * file_w1 = new file_watcher_tst_t;
  file_w1->set_file_name("f1.txt");
  file_w1->set_file_timeout(10.0);
  dir_w.add_watched_file(file_w1);

  file_watcher_tst_t * file_w2 = new file_watcher_tst_t;
  file_w2->set_file_name("f2.txt");
  file_w2->set_file_timeout(10.0);
  dir_w.add_watched_file(file_w2);
  
  file_watcher_tst_t * file_w3 = new file_watcher_tst_t;
  file_w3->set_file_name("f3.txt");
  file_w3->set_file_timeout(10.0);
  dir_w.add_watched_file(file_w3);

  int i_err = dir_w.dir_watcher_init( loop );
  if(INOT_INIT_ERR == i_err)
  {
    cout << "Failed to initialize dir watcher!\n";
    cout << "inotify_init() failed\n";

    return INOT_INIT_ERR;
  }
  if(INOT_ADD_WATCH_ERR == i_err)
  {
    cout << "Failed to initialize dir watcher!\n";
    cout << "inotify_add_watch() failed\n";
    cout << "Check if the watched dir exists: " << dir_w.get_dir_name() << endl;
    return INOT_ADD_WATCH_ERR;
  }

  cout << "dir_watcher initialized\n";
  cout << "Watching dir: " << dir_w.get_dir_name()  << endl;

  ev_loop(loop, 0);  // main loop
  dir_w.dir_watcher_close();
  
  cout << "Done.\n";

  return 0;
}
