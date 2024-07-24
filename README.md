This  was my attempt to create a blueprint function library that should allow to save a static mesh object to disk from Blueprint. 
I say it 'was' my attempt as I no longer follow this as it is not working. 

This code creates an .uasset file, but that file is not recognized by the Unreal Engine content browser.


Installation:

* add a new cpp class that inherits from BlueprintFunctionLibrary with the name 'SaveStaticMeshObject'
* copy the code of the both files to yor header and cpp file accordingly
*add the public dependency modules as shown in the build.cs file


Usage:

* create an actor Blueprint and add a static mesh component and set a mesh to it
* in eventgraph, on BeginPlay or any custom event, get the mesh object out of the static mesh component
* look foor node 'SaveStaticMeshToDisk' take the static mesh opject as an input and give a file name
* paste the actor BP into the level and either run or simulate the level





