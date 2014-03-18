// Copyright Sergei Rebrik 2014
// Distributed under the Boost Software License, Version 1.0. 
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
// 
// Repository and documentation:
// https://github.com/rebrik/cp_dir_watcher
// 
// Revision History:

#ifndef DIR_WATCHER_H
#define	DIR_WATCHER_H

#include <sys/inotify.h>
#include <string>
#include <sstream>
#include <vector>

#include "file_watcher.h"

#define INOTIFY_BUF_LEN 0x8000  // 32KB

typedef struct inotify_event inotify_event_t;

namespace cp 
{

enum dir_watcher_err_t {INOT_INIT_ERR = 1, INOT_ADD_WATCH_ERR = 2};  
  
class dir_watcher_t
{
  public:

    dir_watcher_t();
    virtual ~dir_watcher_t();
    int dir_watcher_init( ev_loop_t *loop );
    void dir_watcher_close();
    
    void set_dir_name( std::string dir_name);
    std::string get_dir_name();
    void set_dir_timeout( double timeout);
    double get_dir_timeout();
    void add_watched_file( file_watcher_t * file);
    void exit_ev_loop();
    void restart_dir_timeout();
   
    virtual void on_dir_moved(){};
    virtual void on_dir_deleted(){};
    virtual void on_dir_unmounted(){};
    virtual void on_dir_timeout(){};

  protected:
    int n_ev_all_;
    int n_ev_dir_timeout_;

  private:
    ev_loop_t * p_loop_;
    std::string dir_name_;
    double d_dir_timeout_sec_;
    std::vector<file_watcher_t *> watched_files_;
    char inotify_buf_[INOTIFY_BUF_LEN];
    int fd_inotify_;
    int fd_iwatch_;
    ev_io  ev_w_inotify_;
    ev_timer ev_w_dir_timeout_;

    static void inotify_cb(ev_loop_t *loop, ev_io *w, int revents);
    static void dir_timeout_cb(ev_loop_t *loop, ev_timer *w, int revents);

    void dispach_dir_ev(ev_loop_t *loop, ev_io *w, int revents);

    file_watcher_t * match_fname(std::string fname);
};

}  // namespace cp
#endif	// DIR_WATCHER_H
