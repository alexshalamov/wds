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


#include "driver.h"
#include "message.h"
#include "reply.h"

#include <cctype>
#include <sstream>

// can be merged to 1 lexer
// %define api.pure full
// %lex-param {yyscan_t scanner} {parser state}
// then, in lexer, we can return correct token based on the state

#include "gen/parser.h"
#include "gen/errorscanner.h"
#include "gen/headerscanner.h"
#include "gen/messagescanner.h"


int wfd_lex(YYSTYPE* yylval, void* scanner, std::unique_ptr<wds::rtsp::Message>& message) {
  return 0;
}

void wfd_error (void* scanner, std::unique_ptr<wds::rtsp::Message>& message, const char* error_message) {
}

namespace wds {
namespace rtsp {

Driver::~Driver() {
}


void Driver::Parse(const std::string& input, std::unique_ptr<Message>& message) {


  void* scanner;

  // we can remove all these ifs by providing state to lexers
  // e.g. wfd_lex_init(&scanner);
  // state = header, error, message
  // then in .l file we need to add #define YY_EXTRA_TYPE struct _state *
  //
  // then code would look like
  // wfd_lex_init(&scanner);
  // wfd_lex_set_extra(state, scanner);
  // in .l file we can check yyextra, if (yyextra == error) return error token.
  // *_scan_string(...) should be used to set input buffer for lexer

  if (!message) {
    header_lex_init(&scanner);
    wfd_parse(scanner, message);
    header_lex_destroy(scanner);
  } else if (message->is_reply()) {
    Reply* reply = static_cast<Reply*>(message.get());
    if (reply->response_code() == STATUS_SeeOther) {
      error_lex_init(&scanner);
      wfd_parse(scanner, message);
      error_lex_destroy(scanner);
    } else {
      message_lex_init(&scanner);
      //void message_set_extra (is_reply ,scanner );
      wfd_parse(scanner, message);
      message_lex_destroy(scanner);
    }
  }





}

} // namespace rtsp
} // namespace wds

