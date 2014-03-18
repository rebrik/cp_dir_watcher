// Copyright Sergei Rebrik 2014
// Distributed under the Boost Software License, Version 1.0. 
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
// 
// Repository and documentation:
// https://github.com/rebrik/cp_dir_watcher
// 
// Revision History:

#include "file_watcher.h"

namespace cp
{
  //----------------------------------------------------------------------------
  file_watcher_t::file_watcher_t()
  {
    d_file_timeout_sec_ = 10.0;

    n_ev_created_ = 0;
    n_ev_opened = 0;
    n_ev_closed_write_ = 0;
    n_ev_closed_nowrite_ = 0;
    n_ev_deleted_ = 0;
    n_ev_moved_to_ = 0;
    n_ev_moved_from_ = 0;
    n_ev_modified_ = 0;
    n_ev_accessed_ = 0;
    n_ev_attrib_changed_ = 0;
    n_ev_timeout_ = 0;

    p_loop_ = 0;
    ev_w_file_timeout_.data = this;
  }

  //----------------------------------------------------------------------------
  file_watcher_t::~file_watcher_t()
  {
    file_watcher_close();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::file_watcher_init( ev_loop_t *loop )
  {
    p_loop_ = loop;

    ev_timer_init(&ev_w_file_timeout_, file_timeout_cb,
                  0.0, d_file_timeout_sec_);
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::file_watcher_close()
  {
    // if the watcher was initialized, close it
    if(p_loop_)
    {
      ev_timer_stop(p_loop_, &ev_w_file_timeout_);
      p_loop_ = 0;
    }
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::set_file_name( std::string file_name)
  {
    file_name_ = file_name;
  }
  
  //----------------------------------------------------------------------------
  std::string file_watcher_t::get_file_name()
  {
    return file_name_;
  }
  
  //----------------------------------------------------------------------------
  void file_watcher_t::set_file_timeout( double timeout)
  {
    d_file_timeout_sec_ = timeout;
  }
  
  //----------------------------------------------------------------------------
  double file_watcher_t::get_file_timeout()
  {
    return d_file_timeout_sec_;
  }
  
  //----------------------------------------------------------------------------
  void file_watcher_t::file_timeout_cb(
                             ev_loop_t *loop, ev_timer *w, int revents)
  {
    file_watcher_t * p_fw;

    p_fw = (file_watcher_t *)w->data;
    p_fw->on_file_timeout_cb();
  }


  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_created_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_created_++;
    on_file_created();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_opened_cb()
  {
    // means opened for either read or write or both
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_opened++;
    on_file_opened();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_closed_write_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_closed_write_++;
    on_file_closed_write();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_closed_nowrite_cb()
  { 
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_closed_nowrite_++;
    on_file_closed_nowrite();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_deleted_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_deleted_++;
    on_file_deleted();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_moved_to_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_moved_to_++;
    on_file_moved_to();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_moved_from_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_moved_from_++;
    on_file_moved_from();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_modified_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_modified_++;
    on_file_modified();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_accessed_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_accessed_++;
    on_file_accessed();
  }
 
  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_attrib_changed_cb()
  {
    ev_timer_again(p_loop_, &ev_w_file_timeout_);
    n_ev_attrib_changed_++;
    on_file_attrib_changed();
  }

  //----------------------------------------------------------------------------
  void file_watcher_t::on_file_timeout_cb()
  {
    // restart timeout (with possibly new value)
    ev_w_file_timeout_.repeat = d_file_timeout_sec_;
    ev_timer_again( p_loop_, &ev_w_file_timeout_);
    n_ev_timeout_++;
    on_file_timeout();
  }
  

} // namespace cp
