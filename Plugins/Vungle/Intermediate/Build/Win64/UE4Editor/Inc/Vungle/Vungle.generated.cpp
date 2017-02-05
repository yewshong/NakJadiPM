// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Boilerplate C++ definitions for a single module.
	This is automatically generated by UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "Private/VunglePrivatePCH.h"
#include "GeneratedCppIncludes.h"
#include "Vungle.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1Vungle() {}
	void UVungleFunctions::StaticRegisterNativesUVungleFunctions()
	{
		FNativeFunctionRegistrar::RegisterFunction(UVungleFunctions::StaticClass(), "VungleHasRewardedVideo",(Native)&UVungleFunctions::execVungleHasRewardedVideo);
		FNativeFunctionRegistrar::RegisterFunction(UVungleFunctions::StaticClass(), "VungleShowRewardedVideo",(Native)&UVungleFunctions::execVungleShowRewardedVideo);
	}
	IMPLEMENT_CLASS(UVungleFunctions, 1907983676);
	void UVungleComponent::StaticRegisterNativesUVungleComponent()
	{
	}
	IMPLEMENT_CLASS(UVungleComponent, 340423349);
	void UVungleSettings::StaticRegisterNativesUVungleSettings()
	{
	}
	IMPLEMENT_CLASS(UVungleSettings, 3920178441);
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	COREUOBJECT_API class UClass* Z_Construct_UClass_UObject();
	ENGINE_API class UClass* Z_Construct_UClass_UActorComponent();

	VUNGLE_API class UFunction* Z_Construct_UFunction_UVungleFunctions_VungleHasRewardedVideo();
	VUNGLE_API class UFunction* Z_Construct_UFunction_UVungleFunctions_VungleShowRewardedVideo();
	VUNGLE_API class UClass* Z_Construct_UClass_UVungleFunctions_NoRegister();
	VUNGLE_API class UClass* Z_Construct_UClass_UVungleFunctions();
	VUNGLE_API class UFunction* Z_Construct_UDelegateFunction_UVungleComponent_VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature();
	VUNGLE_API class UFunction* Z_Construct_UDelegateFunction_UVungleComponent_VungleAdPlayableChangedDynDelegate__DelegateSignature();
	VUNGLE_API class UClass* Z_Construct_UClass_UVungleComponent_NoRegister();
	VUNGLE_API class UClass* Z_Construct_UClass_UVungleComponent();
	VUNGLE_API class UClass* Z_Construct_UClass_UVungleSettings_NoRegister();
	VUNGLE_API class UClass* Z_Construct_UClass_UVungleSettings();
	VUNGLE_API class UPackage* Z_Construct_UPackage__Script_Vungle();
	UFunction* Z_Construct_UFunction_UVungleFunctions_VungleHasRewardedVideo()
	{
		struct VungleFunctions_eventVungleHasRewardedVideo_Parms
		{
			bool ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UVungleFunctions();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("VungleHasRewardedVideo"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x14022401, 65535, sizeof(VungleFunctions_eventVungleHasRewardedVideo_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(ReturnValue, VungleFunctions_eventVungleHasRewardedVideo_Parms, bool);
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(ReturnValue, VungleFunctions_eventVungleHasRewardedVideo_Parms), 0x0010000000000580, CPP_BOOL_PROPERTY_BITMASK(ReturnValue, VungleFunctions_eventVungleHasRewardedVideo_Parms), sizeof(bool), true);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Vungle|Rewarded Video"));
			MetaData->SetValue(ReturnFunction, TEXT("Keywords"), TEXT("vungle ad advertising video"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/VungleFunctions.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Check if Vungle has a rewarded Video"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UVungleFunctions_VungleShowRewardedVideo()
	{
		UObject* Outer=Z_Construct_UClass_UVungleFunctions();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("VungleShowRewardedVideo"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Vungle|Rewarded Video"));
			MetaData->SetValue(ReturnFunction, TEXT("Keywords"), TEXT("vungle ad advertising video"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/VungleFunctions.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("Vungle show a rewarded Video"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UVungleFunctions_NoRegister()
	{
		return UVungleFunctions::StaticClass();
	}
	UClass* Z_Construct_UClass_UVungleFunctions()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_Vungle();
			OuterClass = UVungleFunctions::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20000080;

				OuterClass->LinkChild(Z_Construct_UFunction_UVungleFunctions_VungleHasRewardedVideo());
				OuterClass->LinkChild(Z_Construct_UFunction_UVungleFunctions_VungleShowRewardedVideo());

				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UVungleFunctions_VungleHasRewardedVideo(), "VungleHasRewardedVideo"); // 3475037721
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UVungleFunctions_VungleShowRewardedVideo(), "VungleShowRewardedVideo"); // 2437152051
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("VungleFunctions.h"));
				MetaData->SetValue(OuterClass, TEXT("IsBlueprintBase"), TEXT("false"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/VungleFunctions.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UVungleFunctions(Z_Construct_UClass_UVungleFunctions, &UVungleFunctions::StaticClass, TEXT("UVungleFunctions"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVungleFunctions);
	UFunction* Z_Construct_UDelegateFunction_UVungleComponent_VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature()
	{
		struct VungleComponent_eventVungleDidCompleteRewardedVideoDynDelegate_Parms
		{
			bool wasSuccessfulView;
		};
		UObject* Outer=Z_Construct_UClass_UVungleComponent();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(VungleComponent_eventVungleDidCompleteRewardedVideoDynDelegate_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(wasSuccessfulView, VungleComponent_eventVungleDidCompleteRewardedVideoDynDelegate_Parms, bool);
			UProperty* NewProp_wasSuccessfulView = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("wasSuccessfulView"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(wasSuccessfulView, VungleComponent_eventVungleDidCompleteRewardedVideoDynDelegate_Parms), 0x0010000000000080, CPP_BOOL_PROPERTY_BITMASK(wasSuccessfulView, VungleComponent_eventVungleDidCompleteRewardedVideoDynDelegate_Parms), sizeof(bool), true);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/VungleComponent.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_UVungleComponent_VungleAdPlayableChangedDynDelegate__DelegateSignature()
	{
		struct VungleComponent_eventVungleAdPlayableChangedDynDelegate_Parms
		{
			bool isAdPlayable;
		};
		UObject* Outer=Z_Construct_UClass_UVungleComponent();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("VungleAdPlayableChangedDynDelegate__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(VungleComponent_eventVungleAdPlayableChangedDynDelegate_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(isAdPlayable, VungleComponent_eventVungleAdPlayableChangedDynDelegate_Parms, bool);
			UProperty* NewProp_isAdPlayable = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("isAdPlayable"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(isAdPlayable, VungleComponent_eventVungleAdPlayableChangedDynDelegate_Parms), 0x0010000000000080, CPP_BOOL_PROPERTY_BITMASK(isAdPlayable, VungleComponent_eventVungleAdPlayableChangedDynDelegate_Parms), sizeof(bool), true);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/VungleComponent.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UVungleComponent_NoRegister()
	{
		return UVungleComponent::StaticClass();
	}
	UClass* Z_Construct_UClass_UVungleComponent()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UActorComponent();
			Z_Construct_UPackage__Script_Vungle();
			OuterClass = UVungleComponent::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20A00080;

				OuterClass->LinkChild(Z_Construct_UDelegateFunction_UVungleComponent_VungleAdPlayableChangedDynDelegate__DelegateSignature());
				OuterClass->LinkChild(Z_Construct_UDelegateFunction_UVungleComponent_VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_DidVungleCompleteRewardedVideo = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("DidVungleCompleteRewardedVideo"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(DidVungleCompleteRewardedVideo, UVungleComponent), 0x0010000010080000, Z_Construct_UDelegateFunction_UVungleComponent_VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature());
				UProperty* NewProp_DidVungleAdPlayableChanged = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("DidVungleAdPlayableChanged"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(DidVungleAdPlayableChanged, UVungleComponent), 0x0010000010080000, Z_Construct_UDelegateFunction_UVungleComponent_VungleAdPlayableChangedDynDelegate__DelegateSignature());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UDelegateFunction_UVungleComponent_VungleAdPlayableChangedDynDelegate__DelegateSignature(), "VungleAdPlayableChangedDynDelegate__DelegateSignature"); // 3127444065
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UDelegateFunction_UVungleComponent_VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature(), "VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature"); // 689847225
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintSpawnableComponent"), TEXT(""));
				MetaData->SetValue(OuterClass, TEXT("ClassGroupNames"), TEXT("Advertising"));
				MetaData->SetValue(OuterClass, TEXT("HideCategories"), TEXT("Activation Components|Activation Collision"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("VungleComponent.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/VungleComponent.h"));
				MetaData->SetValue(NewProp_DidVungleCompleteRewardedVideo, TEXT("ModuleRelativePath"), TEXT("Classes/VungleComponent.h"));
				MetaData->SetValue(NewProp_DidVungleAdPlayableChanged, TEXT("ModuleRelativePath"), TEXT("Classes/VungleComponent.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UVungleComponent(Z_Construct_UClass_UVungleComponent, &UVungleComponent::StaticClass, TEXT("UVungleComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVungleComponent);
	UClass* Z_Construct_UClass_UVungleSettings_NoRegister()
	{
		return UVungleSettings::StaticClass();
	}
	UClass* Z_Construct_UClass_UVungleSettings()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_Vungle();
			OuterClass = UVungleSettings::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20000086;


PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_ZoneId = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("ZoneId"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(ZoneId, UVungleSettings), 0x0010000000004001);
				UProperty* NewProp_AppId = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("AppId"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(AppId, UVungleSettings), 0x0010000000004001);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->ClassConfigName = FName(TEXT("Engine"));
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("VungleSettings.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/VungleSettings.h"));
				MetaData->SetValue(OuterClass, TEXT("ObjectInitializerConstructorDeclared"), TEXT(""));
				MetaData->SetValue(NewProp_ZoneId, TEXT("Category"), TEXT("App"));
				MetaData->SetValue(NewProp_ZoneId, TEXT("DisplayName"), TEXT("Zone Id"));
				MetaData->SetValue(NewProp_ZoneId, TEXT("ModuleRelativePath"), TEXT("Classes/VungleSettings.h"));
				MetaData->SetValue(NewProp_AppId, TEXT("Category"), TEXT("App"));
				MetaData->SetValue(NewProp_AppId, TEXT("DisplayName"), TEXT("App Id"));
				MetaData->SetValue(NewProp_AppId, TEXT("ModuleRelativePath"), TEXT("Classes/VungleSettings.h"));
				MetaData->SetValue(NewProp_AppId, TEXT("ToolTip"), TEXT("SDK Ids"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UVungleSettings(Z_Construct_UClass_UVungleSettings, &UVungleSettings::StaticClass, TEXT("UVungleSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVungleSettings);
	UPackage* Z_Construct_UPackage__Script_Vungle()
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/Vungle")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0xCE6A833B;
			Guid.B = 0x9009A1E2;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

			Z_Construct_UDelegateFunction_UVungleComponent_VungleAdPlayableChangedDynDelegate__DelegateSignature();
			Z_Construct_UDelegateFunction_UVungleComponent_VungleDidCompleteRewardedVideoDynDelegate__DelegateSignature();
		}
		return ReturnPackage;
	}
#endif

PRAGMA_ENABLE_DEPRECATION_WARNINGS