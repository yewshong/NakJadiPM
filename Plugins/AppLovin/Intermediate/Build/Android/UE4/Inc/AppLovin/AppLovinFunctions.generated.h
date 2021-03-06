// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef APPLOVIN_AppLovinFunctions_generated_h
#error "AppLovinFunctions.generated.h already included, missing '#pragma once' in AppLovinFunctions.h"
#endif
#define APPLOVIN_AppLovinFunctions_generated_h

#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execAppLovinPreloadRewardedVideo) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAppLovinFunctions::AppLovinPreloadRewardedVideo(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAppLovinShowRewardedVideo) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAppLovinFunctions::AppLovinShowRewardedVideo(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAppLovinHasRewardedVideo) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAppLovinFunctions::AppLovinHasRewardedVideo(); \
		P_NATIVE_END; \
	}


#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAppLovinPreloadRewardedVideo) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAppLovinFunctions::AppLovinPreloadRewardedVideo(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAppLovinShowRewardedVideo) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAppLovinFunctions::AppLovinShowRewardedVideo(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAppLovinHasRewardedVideo) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAppLovinFunctions::AppLovinHasRewardedVideo(); \
		P_NATIVE_END; \
	}


#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUAppLovinFunctions(); \
	friend APPLOVIN_API class UClass* Z_Construct_UClass_UAppLovinFunctions(); \
	public: \
	DECLARE_CLASS(UAppLovinFunctions, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/AppLovin"), NO_API) \
	DECLARE_SERIALIZER(UAppLovinFunctions) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_INCLASS \
	private: \
	static void StaticRegisterNativesUAppLovinFunctions(); \
	friend APPLOVIN_API class UClass* Z_Construct_UClass_UAppLovinFunctions(); \
	public: \
	DECLARE_CLASS(UAppLovinFunctions, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/AppLovin"), NO_API) \
	DECLARE_SERIALIZER(UAppLovinFunctions) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAppLovinFunctions(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAppLovinFunctions) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAppLovinFunctions); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAppLovinFunctions); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAppLovinFunctions(UAppLovinFunctions&&); \
	NO_API UAppLovinFunctions(const UAppLovinFunctions&); \
public:


#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAppLovinFunctions(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAppLovinFunctions(UAppLovinFunctions&&); \
	NO_API UAppLovinFunctions(const UAppLovinFunctions&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAppLovinFunctions); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAppLovinFunctions); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAppLovinFunctions)


#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_PRIVATE_PROPERTY_OFFSET
#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_8_PROLOG
#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_PRIVATE_PROPERTY_OFFSET \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_RPC_WRAPPERS \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_INCLASS \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_PRIVATE_PROPERTY_OFFSET \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_INCLASS_NO_PURE_DECLS \
	NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID NakJadiPM_Plugins_AppLovin_Source_AppLovin_Classes_AppLovinFunctions_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
