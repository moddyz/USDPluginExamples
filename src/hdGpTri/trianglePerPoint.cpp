#include "trianglePerPoint.h"
#include "debugCodes.h"

#include <pxr/imaging/hd/primvarsSchema.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(_tokens,
                         ((primvars, "primvars"))((sourceMeshPath,
                                                   "sourceMeshPath")));

static VtArray<SdfPath>
_GetSourceMeshPaths(const HdSceneIndexPrim& procPrim)
{
    // Get the primvars
    HdDataSourceBaseHandle primvarsDataSrcBase =
        procPrim.dataSource->Get(_tokens->primvars);
    HdContainerDataSourceHandle primvarsDataSrc =
        HdContainerDataSource::Cast(primvarsDataSrcBase);
    HdPrimvarsSchema primvarsSchema(primvarsDataSrc);
    TF_VERIFY(primvarsSchema);

    // Get the sourceMeshPath primvar
    HdPrimvarSchema sourceMeshPathSchema =
        primvarsSchema.GetPrimvar(_tokens->sourceMeshPath);
    TF_VERIFY(sourceMeshPathSchema);

    // Query the source mesh paths.
    HdSampledDataSourceHandle sourceMeshPathDataSrc =
        sourceMeshPathSchema.GetPrimvarValue();
    VtValue value = sourceMeshPathDataSrc->GetValue(0);
    VtArray<SdfPath> sourceMeshPaths = value.Get<VtArray<SdfPath>>();
    return sourceMeshPaths;
}

HdGpTrianglePerPointGenerativeProcedural::
    HdGpTrianglePerPointGenerativeProcedural(const SdfPath& proceduralPrimPath)
  : HdGpGenerativeProcedural(proceduralPrimPath)
{
    TF_DEBUG(HDGPTRI).Msg("Constructing TrianglePerPoint procedural for %s\n",
                          proceduralPrimPath.GetText());
}

HdGpGenerativeProcedural::DependencyMap
HdGpTrianglePerPointGenerativeProcedural::UpdateDependencies(
    const HdSceneIndexBaseRefPtr& inputScene)
{
    HdGpGenerativeProcedural::DependencyMap dependencies;

    // Get the prim associated with this procedural from our scene index.
    HdSceneIndexPrim procPrim = inputScene->GetPrim(_GetProceduralPrimPath());
    TF_DEBUG(HDGPTRI).Msg("Got proc prim type %s\n",
                          procPrim.primType.GetText());

    VtArray<SdfPath> sourceMeshPaths = _GetSourceMeshPaths(procPrim);
    for (const SdfPath& sourceMeshPath : sourceMeshPaths) {
        TF_DEBUG(HDGPTRI).Msg("Got sourceMeshPath: %s\n",
                              sourceMeshPath.GetText());
        HdSceneIndexPrim sourceMeshPrim = inputScene->GetPrim(sourceMeshPath);
        HdDebugPrintDataSource(sourceMeshPrim.dataSource);

        // Get the primvars schema for the mesh.
        HdDataSourceBaseHandle primvarsDataSrcBase =
            procPrim.dataSource->Get(_tokens->primvars);
        HdContainerDataSourceHandle primvarsDataSrc =
            HdContainerDataSource::Cast(primvarsDataSrcBase);
        HdPrimvarsSchema primvarsSchema(primvarsDataSrc);
        HdDataSourceLocator pointsLocator = primvarsSchema.GetPointsLocator();

        // Insert dependency of mesh prim -> points data source locator.
        dependencies.insert(std::pair<SdfPath, HdDataSourceLocatorSet>(
            sourceMeshPath, HdDataSourceLocatorSet{ pointsLocator }));
    }

    return dependencies;
}

HdGpGenerativeProcedural::ChildPrimTypeMap
HdGpTrianglePerPointGenerativeProcedural::Update(
    const HdSceneIndexBaseRefPtr& inputScene,
    const ChildPrimTypeMap& previousResult,
    const DependencyMap& dirtiedDependencies,
    HdSceneIndexObserver::DirtiedPrimEntries* outputDirtiedPrims)
{
    TF_DEBUG(HDGPTRI).Msg("HdGpTrianglePerPointGenerativeProcedural::Update\n");

    ChildPrimTypeMap result;
    return result;
}

HdSceneIndexPrim
HdGpTrianglePerPointGenerativeProcedural::GetChildPrim(
    const HdSceneIndexBaseRefPtr& inputScene,
    const SdfPath& childPrimPath)
{
    TF_DEBUG(HDGPTRI).Msg(
        "HdGpTrianglePerPointGenerativeProcedural::GetChildPrim\n");
}

PXR_NAMESPACE_CLOSE_SCOPE
