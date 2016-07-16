#pragma once
#include "base.h"

#ifdef __cplusplus
extern "C" {
#endif

	CK_RV Beidsdk_GetObjectValue(CK_FUNCTION_LIST_PTR pFunctions, CK_SESSION_HANDLE session_handle, CK_CHAR_PTR pName, CK_VOID_PTR *ppValue, CK_ULONG_PTR pvalueLen);
	void Beidsdk_PrintValue(CK_CHAR_PTR pName, CK_BYTE_PTR pValue, CK_ULONG valueLen);
	CK_ULONG beidsdk_GetData(void);

	void loadCard(CK_FUNCTION_LIST_PTR, CK_SESSION_HANDLE);
	void destroyReader();

	void cardPulled();

#ifdef __cplusplus
}
#endif
