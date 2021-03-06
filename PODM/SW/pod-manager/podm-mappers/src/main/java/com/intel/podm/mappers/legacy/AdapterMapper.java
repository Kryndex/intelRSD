/*
 * Copyright (c) 2016-2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.intel.podm.mappers.legacy;

import com.intel.podm.business.entities.redfish.Storage;
import com.intel.podm.client.resources.legacy.AdapterResource;
import com.intel.podm.mappers.EntityMapper;
import com.intel.podm.mappers.subresources.legacy.AdapterToStorageControllerMapper;

import javax.enterprise.context.Dependent;
import javax.inject.Inject;
import java.util.List;

import static java.util.Collections.singletonList;

@Dependent
public class AdapterMapper extends EntityMapper<AdapterResource, Storage> {
    @Inject
    private AdapterToStorageControllerMapper storageControllerMapper;

    protected AdapterMapper() {
        super(AdapterResource.class, Storage.class);
    }

    @Override
    protected void performNotAutomatedMapping(AdapterResource source, Storage target) {
        super.performNotAutomatedMapping(source, target);
        List<AdapterResource> resources = singletonList(source);
        storageControllerMapper.map(resources, target.getAdapters(), target::addAdapter);
    }
}
