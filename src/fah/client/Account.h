/******************************************************************************\

                  This file is part of the Folding@home Client.

          The fah-client runs Folding@home protein folding simulations.
                    Copyright (c) 2001-2023, foldingathome.org
                               All rights reserved.

       This program is free software; you can redistribute it and/or modify
       it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 3 of the License, or
                       (at your option) any later version.

         This program is distributed in the hope that it will be useful,
          but WITHOUT ANY WARRANTY; without even the implied warranty of
          MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                   GNU General Public License for more details.

     You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
           51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

                  For information regarding this software email:
                                 Joseph Coffland
                          joseph@cauldrondevelopment.com

\******************************************************************************/

#pragma once

#include <cbang/event/Event.h>
#include <cbang/event/JSONWebsocket.h>
#include <cbang/util/Backoff.h>
#include <cbang/json/Value.h>


namespace FAH {
  namespace Client {
    class App;

    class Account : public cb::Event::JSONWebsocket {
      App &app;

      cb::SmartPointer<cb::Event::Event> updateEvent;
      cb::Backoff updateBackoff = cb::Backoff(60, 4 * 60 * 60);

    public:
      Account(App &app);

      void init();

      void setInfo(const cb::JSON::ValuePtr &account);
      void getInfo();

      void connect(const std::string &node);
      void link(const std::string &token);
      void update();

      // From cb::Event::JSONWebsocket
      void onOpen();
      void onMessage(const cb::JSON::ValuePtr &msg);
      void onPing(const std::string &payload);
      void onClose(cb::Event::WebsockStatus status, const std::string &msg);
    };
  }
}