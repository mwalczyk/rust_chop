/* Shared Use License: This file is owned by Derivative Inc. (Derivative) and
 * can only be used, and/or modified for use, in conjunction with 
 * Derivative's TouchDesigner software, and only if you are a licensee who has
 * accepted Derivative's TouchDesigner license or assignment agreement (which
 * also govern the use of this file).  You may share a modified version of this
 * file with another authorized licensee of Derivative's TouchDesigner software.
 * Otherwise, no redistribution or sharing of this file, with or without
 * modification, is permitted.
 */

#include "CHOP_CPlusPlusBase.h"

#include <Windows.h>
#include <iostream>
#include <tchar.h>

typedef void (*ExecuteRsFuncPtr)(float* chanData, size_t chanIndex, size_t chanSamples, uint32_t executeCount);

class RustCHOP : public CHOP_CPlusPlusBase
{
public:
	RustCHOP(const OP_NodeInfo* info);
	virtual ~RustCHOP();

	virtual void getGeneralInfo(CHOP_GeneralInfo* ) override;
	virtual bool getOutputInfo(CHOP_OutputInfo*) override;
	virtual const char*	getChannelName(int32_t index, void* reserved) override;
	virtual void execute(const CHOP_Output*, OP_Inputs*, void* reserved) override;
	virtual int32_t	getNumInfoCHOPChans() override;
	virtual void getInfoCHOPChan(int index, OP_InfoCHOPChan* chan) override;
	virtual bool getInfoDATSize(OP_InfoDATSize* infoSize) override;
	virtual void getInfoDATEntries(int32_t index, int32_t nEntries, OP_InfoDATEntries* entries) override;
	virtual void setupParameters(OP_ParameterManager* manager) override;
	virtual void pulsePressed(const char* name) override;

private:

	int32_t	executeCount;

	HINSTANCE rustDll;
	ExecuteRsFuncPtr executeRsEntryPoint;
};
