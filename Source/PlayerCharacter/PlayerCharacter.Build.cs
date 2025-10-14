using UnrealBuildTool;

public class PlayerCharacter : ModuleRules
{
    public PlayerCharacter(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "UMG",
                "Slate"
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[]{});
    }
}