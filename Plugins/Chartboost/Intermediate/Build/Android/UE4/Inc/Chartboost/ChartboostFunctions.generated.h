// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CHARTBOOST_ChartboostFunctions_generated_h
#error "ChartboostFunctions.generated.h already included, missing '#pragma once' in ChartboostFunctions.h"
#endif
#define CHARTBOOST_ChartboostFunctions_generated_h

#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execChartboostCacheRewardedVideo) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Location); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UChartboostFunctions::ChartboostCacheRewardedVideo(Z_Param_Location); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execChartboostShowRewardedVideo) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Location); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UChartboostFunctions::ChartboostShowRewardedVideo(Z_Param_Location); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execChartboostHasRewardedVideo) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Location); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UChartboostFunctions::ChartboostHasRewardedVideo(Z_Param_Location); \
		P_NATIVE_END; \
	}


#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execChartboostCacheRewardedVideo) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Location); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UChartboostFunctions::ChartboostCacheRewardedVideo(Z_Param_Location); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execChartboostShowRewardedVideo) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Location); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UChartboostFunctions::ChartboostShowRewardedVideo(Z_Param_Location); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execChartboostHasRewardedVideo) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Location); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UChartboostFunctions::ChartboostHasRewardedVideo(Z_Param_Location); \
		P_NATIVE_END; \
	}


#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUChartboostFunctions(); \
	friend CHARTBOOST_API class UClass* Z_Construct_UClass_UChartboostFunctions(); \
	public: \
	DECLARE_CLASS(UChartboostFunctions, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Chartboost"), NO_API) \
	DECLARE_SERIALIZER(UChartboostFunctions) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_INCLASS \
	private: \
	static void StaticRegisterNativesUChartboostFunctions(); \
	friend CHARTBOOST_API class UClass* Z_Construct_UClass_UChartboostFunctions(); \
	public: \
	DECLARE_CLASS(UChartboostFunctions, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Chartboost"), NO_API) \
	DECLARE_SERIALIZER(UChartboostFunctions) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UChartboostFunctions(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UChartboostFunctions) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UChartboostFunctions); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UChartboostFunctions); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UChartboostFunctions(UChartboostFunctions&&); \
	NO_API UChartboostFunctions(const UChartboostFunctions&); \
public:


#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UChartboostFunctions(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UChartboostFunctions(UChartboostFunctions&&); \
	NO_API UChartboostFunctions(const UChartboostFunctions&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UChartboostFunctions); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UChartboostFunctions); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UChartboostFunctions)


#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_PRIVATE_PROPERTY_OFFSET
#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_7_PROLOG
#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_PRIVATE_PROPERTY_OFFSET \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_RPC_WRAPPERS \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_INCLASS \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_PRIVATE_PROPERTY_OFFSET \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_INCLASS_NO_PURE_DECLS \
	NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID NakJadiPM_Plugins_Chartboost_Source_Chartboost_Classes_ChartboostFunctions_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
