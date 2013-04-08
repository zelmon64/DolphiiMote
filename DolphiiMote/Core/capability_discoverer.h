// Copyright 2013 Max Malmgren

// This file is part of DolphiiMote.

// DolphiiMote is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// DolphiiMote is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with DolphiiMote.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DOLPHIIMOTE_CAPABILITY_DISCOVERER_H
#define DOLPHIIMOTE_CAPABILITY_DISCOVERER_H

#include <map>
#include "wiimote.h"
#include "data_sender.h"
#include "wiimote_reader.h"

namespace dolphiimote
{
  class capability_discoverer : public wiimote_data_handler
  {
  public:
    
    capability_discoverer(std::map<int, wiimote> &wiimote_states, data_sender &sender, wiimote_reader &reader) : wiimote_states(wiimote_states), sender(sender), reader(reader)
    { }

    virtual void data_received(dolphiimote_callbacks &callbacks, int wiimote_number, checked_array<const u8> data);

    void determine_capabilities(int wiimote_number);
    void send_status_request(int wiimote_number);
    void enable(int wiimote_number, wiimote_capabilities::type capabilities_to_enable);
    

  private:
    void update_extension_type_from_id(int wiimote_number);
    void handle_extension_id_message(int wiimote_number, checked_array<const u8> data, dolphiimote_callbacks callbacks);
    void handle_motionplus_id_message(int wiimote_number, checked_array<const u8> data, dolphiimote_callbacks callbacks);
    void init_and_identify_extension_controller(int wiimote_number);
    void send_extension_id_read_message(int wiimote_number);
    void dispatch_capabilities_changed(int wiimote, dolphiimote_callbacks callbacks);
    void handle_motion_plus_and_extension_enabling(int wiimote_number, wiimote_capabilities::type capabilities_to_enable);

    void enable_only_extension(int wiimote);

    std::map<int, wiimote> &wiimote_states;
    data_sender &sender;
    wiimote_reader &reader;
  };
}
#endif DOLPHIIMOTE_CAPABILITY_DISCOVERER_H