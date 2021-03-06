/*!
 * @brief iSCSI MDR entry point v1.0.
 *
 * @copyright Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @header{Files}
 * @file iscsi_mdr_10_entry_point.hpp
 */

#pragma once

#include "iscsi/iscsi_mdr_entry_point.hpp"

namespace iscsi {

namespace structs {

struct ISCSI_MDR_VERSION;

}  // namespace structs

namespace parser {

/*!
 * @brief iSCSI MDR entry point.
 *
 * Some features are not implemented, because they do not make sense for
 * the iSCSI MDR layout.
 */
class IscsiMdr10EntryPoint final: public IscsiMdrEntryPoint {
public:
    /*!
     * @brief Create Entry point structure pointer
     * @param buf pointer to the bytes to be parsed
     * @param buf_size number of bytes to be parsed
     */
    IscsiMdr10EntryPoint(const std::uint8_t* buf, const size_t buf_size);

    /*! Copy constructor */
    IscsiMdr10EntryPoint(const IscsiMdr10EntryPoint&) = default;

    /*! Move constructor */
    IscsiMdr10EntryPoint(IscsiMdr10EntryPoint&&) = default;

    /*! Assignment operator */
    IscsiMdr10EntryPoint& operator=(const IscsiMdr10EntryPoint&) = default;

    /*! Move assignment operator */
    IscsiMdr10EntryPoint& operator=(IscsiMdr10EntryPoint&&) = default;

    /*! Destructor */
    ~IscsiMdr10EntryPoint() = default;

    /*!
     * @brief Get struct table address
     * @return return offset of start of struct table within the MDR region
     */
    std::uint64_t get_struct_table_address() const override;

    /*!
     * @brief Get iSCSI MDR major version
     * @return numerical value of the iSCSI MDR major version
     */
    std::uint8_t get_major_version() const override;

    /*!
     * @brief Get iSCSI MDR minor version
     * @return numerical value of the iSCSI MDR minor version
     */
    std::uint8_t get_minor_version() const override;

    /*!
     * @brief Not implemented, this method always throws.
     *
     * @return None.
     */
    [[ noreturn ]]
    std::string get_anchor_string() const override;

    /*!
     * @brief Not implemented, this method always throws.
     *
     * @return None.
     */
    [[ noreturn ]]
    std::uint8_t get_revision() const override;

private:

    const structs::ISCSI_MDR_VERSION* m_version;

    static constexpr int SUPPORTED_MAJOR = 1;
    static constexpr int SUPPORTED_MINOR = 0;
};

}  // namespace parser

}  // namespace iscsi
