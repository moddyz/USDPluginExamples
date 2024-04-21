//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "generativeProceduralPlugin.h"
#include "trianglePerPoint.h"
#include "debugCodes.h"

#include <pxr/imaging/hdGp/generativeProceduralPluginRegistry.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    TF_DEBUG(HDGPTRI).Msg("Registering HdGpTriGenerativeProceduralPlugin");

    HdGpGenerativeProceduralPluginRegistry::Define<
        HdGpTriGenerativeProceduralPlugin>();
}

HdGpGenerativeProcedural*
HdGpTriGenerativeProceduralPlugin::Construct(const SdfPath& proceduralPrimPath)
{
    return new HdGpTrianglePerPointGenerativeProcedural(proceduralPrimPath);
}

PXR_NAMESPACE_CLOSE_SCOPE
