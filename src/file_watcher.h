// Copyright Sergei Rebrik 2014
// Distributed under the Boost Software License, Version 1.0. 
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
// 
// Repository and documentation:
// https://github.com/rebrik/cp_dir_watcher
// 
// Revision History:

#ifndef FILE_WATCHER_H
#define	FILE_WATCHER_H

#include <string>
#include <ev.h>

namespace cp 
{

typedef struct ev_loop ev_loop_t;

class file_watcher_t
{
  friend class dir_watcher_t;

  public:

    file_watcher_t();

    virtual ~file_watcher_t();
    void file_watcher_init( ev_loop_t *loop );
    void file_watcher_close();
    void set_file_name( std::string file_name);
    std::string get_file_name();
    void set_file_timeout( double timeout);
    double get_file_timeout();

    virtual void on_file_created(){};
    virtual void on_file_opened(){};
    virtual void on_file_closed_write(){};
    virtual void on_file_closed_nowrite(){};
    virtual void on_file_deleted(){};
    virtual void on_file_moved_from(){};
    virtual void on_file_moved_to(){};
    virtual void on_file_modified(){};
    virtual void on_file_accessed(){};
    virtual void on_file_attrib_changed(){};

    virtual void on_file_timeout(){};


  protected:

    int n_ev_created_;
    int n_ev_opened;
    int n_ev_closed_write_;
    int n_ev_closed_nowrite_;
    int n_ev_deleted_;
    int n_ev_moved_to_;
    int n_ev_moved_from_;
    int n_ev_modified_;
    int n_ev_accessed_;
    int n_ev_attrib_changed_;
    int n_ev_timeout_;

  private:
    std::string file_name_;
    double d_file_timeout_sec_;
    ev_loop_t *p_loop_;
    ev_timer ev_w_file_timeout_;

    void on_file_created_cb();
    void on_file_opened_cb();
    void on_file_closed_write_cb();
    void on_file_closed_nowrite_cb();
    void on_file_deleted_cb();
    void on_file_moved_from_cb();
    void on_file_moved_to_cb();
    void on_file_modified_cb();
    void on_file_accessed_cb();
    void on_file_attrib_changed_cb();
    void on_file_timeout_cb();

    static void file_timeout_cb(ev_loop_t *loop, ev_timer *w, int revents);

};

}   // namespace CP
#endif	// FILE_WATCHER_H 
