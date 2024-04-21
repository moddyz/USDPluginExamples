//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/imaging/hdGp/generativeProcedural.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdGpTrianglePerPointGenerativeProcedural
///
/// Represents a procedural that creates a Triangle per mesh point.
class HdGpTrianglePerPointGenerativeProcedural final
  : public HdGpGenerativeProcedural
{
public:
    HdGpTrianglePerPointGenerativeProcedural(const SdfPath& proceduralPrimPath);
    virtual ~HdGpTrianglePerPointGenerativeProcedural() = default;

    virtual DependencyMap UpdateDependencies(
        const HdSceneIndexBaseRefPtr& inputScene) override;

    virtual ChildPrimTypeMap Update(
        const HdSceneIndexBaseRefPtr& inputScene,
        const ChildPrimTypeMap& previousResult,
        const DependencyMap& dirtiedDependencies,
        HdSceneIndexObserver::DirtiedPrimEntries* outputDirtiedPrims) override;

    virtual HdSceneIndexPrim GetChildPrim(
        const HdSceneIndexBaseRefPtr& inputScene,
        const SdfPath& childPrimPath) override;
};

PXR_NAMESPACE_CLOSE_SCOPE
