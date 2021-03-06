/*!
 * @header{License}
 * @copyright Copyright (c) 2017 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @header{Filesystem}
 * @file rmm/command/get_port_vlan_info.cpp
 */

#include "agent-framework/module/common_components.hpp"
#include "agent-framework/module/network_components.hpp"
#include "agent-framework/command/registry.hpp"
#include "agent-framework/command/rmm_commands.hpp"

using namespace agent_framework::command;
using namespace agent_framework::module;
using namespace agent_framework::model;

REGISTER_COMMAND(GetPortVlanInfo,
    [] (const GetPortVlanInfo::Request& request, GetPortVlanInfo::Response& response) {
        response = get_manager<EthernetSwitchPortVlan>().get_entry(request.get_uuid());
    }
);
