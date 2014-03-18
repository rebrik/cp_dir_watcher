// Copyright Sergei Rebrik 2014
// Distributed under the Boost Software License, Version 1.0. 
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
// 
// Repository and documentation:
// https://github.com/rebrik/cp_dir_watcher
// 
// Revision History:

#include "dir_watcher.h"

namespace cp
{

  //----------------------------------------------------------------------------
  dir_watcher_t::dir_watcher_t()
  {
    fd_inotify_ = -1;
    fd_iwatch_ = -1;
    p_loop_ = 0;
    n_ev_all_ = 0;
    n_ev_dir_timeout_ = 0;
    dir_name_ = ".";
    d_dir_timeout_sec_ = 60.0;
    ev_w_inotify_.data = this;
    ev_w_dir_timeout_.data = this;
  }

  //----------------------------------------------------------------------------
  dir_watcher_t::~dir_watcher_t()
  {
    dir_watcher_close();
  }
  
  //----------------------------------------------------------------------------
  // call it after all watched files in the dir were added
  int dir_watcher_t::dir_watcher_init(ev_loop_t *loop)
  {
    // init the dir watcher
    fd_inotify_ = inotify_init1(IN_NONBLOCK);
    if( fd_inotify_ < 0 )
    {
      return INOT_INIT_ERR;
    }
    int i_mask = IN_ALL_EVENTS;
    fd_iwatch_ = inotify_add_watch(fd_inotify_, dir_name_.c_str(), i_mask );
    if( fd_iwatch_ < 0 )
    {
      close(fd_inotify_);
      fd_inotify_ = -1;
      return INOT_ADD_WATCH_ERR;
    }

    p_loop_ = loop;
    // init libev io event showing that inotify device data are ready
    ev_io_init(&ev_w_inotify_, inotify_cb, fd_inotify_, EV_READ);
  //  ev_set_priority (&inotify_watcher, EV_MAXPRI);
    ev_io_start (p_loop_, &ev_w_inotify_);

    // init timeout
    ev_timer_init(&ev_w_dir_timeout_, dir_timeout_cb,
                  0.0, d_dir_timeout_sec_);
    ev_timer_again( p_loop_, &ev_w_dir_timeout_);

    // init all file watchers
    for( int i=0; i< watched_files_.size(); i++)
    {
      watched_files_[i]->file_watcher_init(p_loop_);
    }

    return 0;
  }
  
  //----------------------------------------------------------------------------
  // call it after all watched files in the dir were added
  void dir_watcher_t::dir_watcher_close()
  {
    // if the watcher was initialized, close it
    if( p_loop_)
    {
      // init all file watchers
      for( int i=0; i< watched_files_.size(); i++)
      {
        watched_files_[i]->file_watcher_close();
      }
      ev_timer_stop(p_loop_, &ev_w_dir_timeout_);
      ev_io_stop(p_loop_, &ev_w_inotify_);
      p_loop_ = 0;
    }
    if( fd_inotify_ > 0 )
    {
      inotify_rm_watch(fd_inotify_, fd_iwatch_);
      close(fd_inotify_);
      fd_inotify_ = -1;
    }
  }
  

  //----------------------------------------------------------------------------
  void dir_watcher_t::set_dir_name( std::string dir_name)
  {
    dir_name_ = dir_name;
  }
  
  //----------------------------------------------------------------------------
  std::string dir_watcher_t::get_dir_name()
  {
    return dir_name_;
  }
  
  //----------------------------------------------------------------------------
  void dir_watcher_t::set_dir_timeout( double timeout)
  {
    d_dir_timeout_sec_ = timeout;
  }
  
 //----------------------------------------------------------------------------
  double dir_watcher_t::get_dir_timeout()
  {
    return d_dir_timeout_sec_;
  }
  
  //----------------------------------------------------------------------------
  void dir_watcher_t::exit_ev_loop()
  {
    if( p_loop_)
    {
      ev_unloop(p_loop_, EVUNLOOP_ONE);
    }
  }
  
  //----------------------------------------------------------------------------
  void dir_watcher_t::restart_dir_timeout()
  {
    // restart timeout (with possibly new value)
    if( p_loop_)
    {
      ev_w_dir_timeout_.repeat = d_dir_timeout_sec_;
      ev_timer_again( p_loop_, &ev_w_dir_timeout_);
    }
  }
  
  //----------------------------------------------------------------------------
  void dir_watcher_t::add_watched_file( file_watcher_t * file)
  {
    watched_files_.push_back(file);
  }

  //----------------------------------------------------------------------------
  // It's a static function called by C 
  // Class pointer is stored in w->data
  void dir_watcher_t::inotify_cb( ev_loop_t *loop, ev_io *w, int revents)
  {
    dir_watcher_t * p_dw = (dir_watcher_t *)w->data;
    p_dw->dispach_dir_ev( loop, w, revents);
  }

  //----------------------------------------------------------------------------
  void dir_watcher_t::dir_timeout_cb(
                             ev_loop_t *loop, ev_timer *w, int revents)
  {
    dir_watcher_t * p_dw;

    p_dw = (dir_watcher_t *)w->data;
    p_dw->n_ev_dir_timeout_++;
    p_dw->on_dir_timeout();
  }

  //----------------------------------------------------------------------------
  void dir_watcher_t::dispach_dir_ev(ev_loop_t *loop, ev_io *w, int revents)
  {
    // ostringstream sout;

    // Normally revents == 1 , i.e.: "ev_io detected read will not block"

    // TODO: here we assume that the buffer is big enough to hold all
    // inotify events which arrived between the reads
    int n_read = read(fd_inotify_, inotify_buf_, INOTIFY_BUF_LEN);

    inotify_event_t * p_ie;
    int i_next_ie = 0;
    while( i_next_ie < n_read) // while we have inotify events in the buffer
    {
      p_ie=(inotify_event_t *)(inotify_buf_ + i_next_ie);
      // if len>0 event happened to something in the dir
      // IN_ISDIR bit corresponds to a subdir, not a file
      if(p_ie->len && !(p_ie->mask & IN_ISDIR)) 
      {
        std::string fname = p_ie->name;
        file_watcher_t * fw = match_fname(fname);
        if( fw ) 
        {
          if(p_ie->mask & IN_CREATE)        fw->on_file_created_cb();
          if(p_ie->mask & IN_CLOSE_WRITE)   fw->on_file_closed_write_cb();
          if(p_ie->mask & IN_CLOSE_NOWRITE) fw->on_file_closed_nowrite_cb();
          if(p_ie->mask & IN_DELETE)        fw->on_file_deleted_cb();
          if(p_ie->mask & IN_MOVED_FROM)    fw->on_file_moved_from_cb();
          if(p_ie->mask & IN_MOVED_TO)      fw->on_file_moved_to_cb();
          if(p_ie->mask & IN_MODIFY)        fw->on_file_modified_cb();
          if(p_ie->mask & IN_ATTRIB)        fw->on_file_attrib_changed_cb();
          if(p_ie->mask & IN_OPEN)          fw->on_file_opened_cb();
          if(p_ie->mask & IN_ACCESS)        fw->on_file_accessed_cb();
        }
      }
      else  // watched dir-related events
      {
        if(p_ie->mask & IN_DELETE_SELF) on_dir_deleted();
        if(p_ie->mask & IN_MOVE_SELF)   on_dir_moved();
        if(p_ie->mask & IN_UNMOUNT)     on_dir_unmounted();

/*
        sout << "---> Dir:  " << dir_name_;
        if(p_ie->mask & IN_ACCESS)      sout << " IN_ACCESS";
        if(p_ie->mask & IN_MODIFY)      sout << " IN_MODIFY";
        if(p_ie->mask & IN_ATTRIB)      sout << " IN_ATTRIB";
        if(p_ie->mask & IN_CLOSE_WRITE) sout << " IN_CLOSE_WRITE";
        if(p_ie->mask & IN_OPEN)        sout << " IN_OPEN";
        if(p_ie->mask & IN_MOVED_FROM)  sout << " IN_MOVED_FROM";
        if(p_ie->mask & IN_MOVED_TO)    sout << " IN_MOVED_TO";
        if(p_ie->mask & IN_CREATE)      sout << " IN_CREATE";
        if(p_ie->mask & IN_DELETE)      sout << " IN_DELETE";
        sout << endl;
        cout << sout.str();
*/
      }
      n_ev_all_++;
      i_next_ie += sizeof(inotify_event_t) + p_ie->len;
    }
    
    // update timer to new (if changed) timeout value, reset the timer
    ev_w_dir_timeout_.repeat = d_dir_timeout_sec_;
    ev_timer_again( p_loop_, &ev_w_dir_timeout_);
  }
  
  //----------------------------------------------------------------------------
  file_watcher_t * dir_watcher_t::match_fname(std::string fname)
  {
    for( int i=0; i< watched_files_.size(); i++)
    {
      if( watched_files_[i]->file_name_ == fname) return watched_files_[i];
    }
    return 0;  // not found
  }
  
} // namespace cp