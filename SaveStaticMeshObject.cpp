#include "SaveStaticMeshObject.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "StaticMeshAttributes.h"
#include "UObject/SavePackage.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"



bool USaveStaticMeshObject::SaveStaticMeshToDisk(UStaticMesh* StaticMesh, const FString& FileName)
{

    if (!StaticMesh) { return false; }
 
    // Prepare the package and file name
    FString PackageName = FString::Printf(TEXT("/Game/Test/%s"), *FileName);
    UPackage* Package = CreatePackage(*PackageName);
 
    if (!Package) {
        UE_LOG(LogTemp, Error, TEXT("Failed to create package: %s"), *PackageName);
        return false;
    }
 

    // Rename the static mesh to be part of the package
    StaticMesh->Rename(*StaticMesh->GetName(), Package);
    StaticMesh->MarkPackageDirty();
 
 
    // Determine the file path
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
    UE_LOG(LogTemp, Log, TEXT("Saving package to: %s"), *PackageFileName);
 
    // Set up save package arguments
    FSavePackageArgs SaveArgs;
    SaveArgs.TopLevelFlags = EObjectFlags::RF_Public | RF_Standalone;
    SaveArgs.Error = GError;
    SaveArgs.SaveFlags = SAVE_NoError | SAVE_KeepGUID; 
 
    // Save the package
    bool bSaved = UPackage::SavePackage(
        Package,
        StaticMesh,
        *PackageFileName,
        SaveArgs
    );
 
 
 
    if (bSaved)
    {
        // Notify the Asset Registry of the new asset
        FAssetRegistryModule::AssetCreated(StaticMesh);
 
        // Refresh the content browser
        if (GEditor)
        {
            // Access the content browser singleton
            FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
            IContentBrowserSingleton& ContentBrowser = ContentBrowserModule.Get();
 
            // Sync the content browser to the newly created assets
            TArray<UObject*> AssetsToSync;
            AssetsToSync.Add(StaticMesh);
            ContentBrowser.SyncBrowserToAssets(AssetsToSync);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save package: %s"), *PackageFileName);
    }
 
    return bSaved;
 
/*  
    //simplified code

    FString PackageName = FString::Printf(TEXT("/Game/YourMeshFolder/%s"), *FileName);
    UPackage* Package = CreatePackage(*PackageName);
    
    Package->FullyLoad();
    StaticMesh->Rename(*StaticMesh->GetName(), Package);
    FAssetRegistryModule::AssetCreated(StaticMesh);
    StaticMesh->MarkPackageDirty();
    
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
    bool bSaved = UPackage::SavePackage(Package, StaticMesh, EObjectFlags::RF_Public | RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);
 
 
    return bSaved;
*/



}
