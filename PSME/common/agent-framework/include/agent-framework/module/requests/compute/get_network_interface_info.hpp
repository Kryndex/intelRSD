/*!
 * @copyright
 * Copyright (c) 2015-2017 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * @file requests/compute/get_network_interface_info.hpp
 * @brief Compute GetProcessorInfo request
 * */

#pragma once
#include "agent-framework/module/constants/compute.hpp"
#include "agent-framework/module/constants/command.hpp"
#include "agent-framework/validators/procedure_validator.hpp"

#include <string>

namespace agent_framework {
namespace model {
namespace requests {

/*! GetNetworkInterfaceInfo request */
class GetNetworkInterfaceInfo {
public:
    explicit GetNetworkInterfaceInfo(const std::string& interface);

    static std::string get_command() {
        return literals::Command::GET_NETWORK_INTERFACE_INFO;
    }

    /*!
     * @brief Get interface number
     * @return Interface number
     * */
    std::string get_uuid() const {
        return m_interface;
    }

    /*!
     * @brief Transform request to Json
     *
     * @return created Json value
     */
    json::Json to_json() const;

    /*!
     * @brief create GetNetworkInterfaceInfo from Json
     *
     * @param[in] json the input argument
     *
     * @return new GetNetworkInterfaceInfo
     */
    static GetNetworkInterfaceInfo from_json(const json::Json& json);

    /*!
     * @brief Returns procedure scheme
     * @return Procedure scheme
     */
    static const jsonrpc::ProcedureValidator& get_procedure() {
        static const jsonrpc::ProcedureValidator procedure{
                get_command(),
                jsonrpc::PARAMS_BY_NAME,
                jsonrpc::JSON_OBJECT,
                literals::NetworkInterface::INTERFACE, jsonrpc::JSON_STRING,
                nullptr
        };
        return procedure;
    }
private:
    std::string m_interface{};
};

}
}
}
