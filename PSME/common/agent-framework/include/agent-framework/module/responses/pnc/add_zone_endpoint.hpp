/*!
 * @copyright
 * Copyright (c) 2016-2017 Intel Corporation
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
 * @file responses/pnc/add_zone_endpoint.hpp
 * @brief Definition of pnc AddZoneEndpoint response
 * */

#pragma once



#include "agent-framework/module/model/attributes/oem.hpp"
#include "json-wrapper/json-wrapper.hpp"

#include <string>

namespace agent_framework {
namespace model {
namespace responses {

/*! AddZoneEndpoint response */
class AddZoneEndpoint {
public:
    /*!
     * @brief explicit AddZoneEndpoint response constructor
     */
    explicit AddZoneEndpoint(const std::string& task = std::string{}, const attribute::Oem& oem = attribute::Oem{});


    /*!
     * Set task UUID
     *
     * @param[in] task Task UUID
     * */
    void set_task(const std::string& task) {
        m_task = task;
    }


    /*!
     * Get task UUID
     *
     * @return Task UUID
     * */
    const std::string& get_task() const {
        return m_task;
    }


    /*!
     * @brief Transform response to Json
     * @return created Json value
     */
    json::Json to_json() const;


    /*!
     * @brief create AddZoneEndpoint from Json
     * @param[in] json the input argument
     * @return new AddZoneEndpoint
     */
    static AddZoneEndpoint from_json(const json::Json& json);


private:
    std::string m_task{};
    attribute::Oem m_oem{};
};

}
}
}
