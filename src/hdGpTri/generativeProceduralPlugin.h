//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/imaging/hdGp/generativeProceduralPlugin.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdGpTriGenerativeProceduralPlugin
///
/// Registers a generative procedural plugin.
class HdGpTriGenerativeProceduralPlugin final
  : public HdGpGenerativeProceduralPlugin
{
public:
    virtual HdGpGenerativeProcedural* Construct(
        const SdfPath& proceduralPrimPath) override;
};

PXR_NAMESPACE_CLOSE_SCOPE
