/*
 * This file is part of Wireless Display Software for Linux OS
 *
 * Copyright (C) 2014 Intel Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */


#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>
#include <memory>

#include "message.h"
#include "payload.h"


int wfd_lex(YYSTYPE* yylval, void* scanner, std::unique_ptr<wds::rtsp::Message>& message);

void wfd_error (void* scanner, std::unique_ptr<wds::rtsp::Message>& message, const char* error_message);

namespace wds {
namespace rtsp {

class Driver {
 public:
  Driver() = default;
  ~Driver();

  void Parse(const std::string& input, std::unique_ptr<Message>& message /*out*/);

 private:
};

}  // namespace rtsp
}  // namespace wds

#endif  // DRIVER_H_
