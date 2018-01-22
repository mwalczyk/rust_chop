/* Shared Use License: This file is owned by Derivative Inc. (Derivative) and
 * can only be used, and/or modified for use, in conjunction with 
 * Derivative's TouchDesigner software, and only if you are a licensee who has
 * accepted Derivative's TouchDesigner license or assignment agreement (which
 * also govern the use of this file).  You may share a modified version of this
 * file with another authorized licensee of Derivative's TouchDesigner software.
 * Otherwise, no redistribution or sharing of this file, with or without
 * modification, is permitted.
 */

#include "RustCHOP.h"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <assert.h>

extern "C"
{
	DLLEXPORT
	int32_t GetCHOPAPIVersion(void)
	{
		return CHOP_CPLUSPLUS_API_VERSION;
	}

	DLLEXPORT
	CHOP_CPlusPlusBase* CreateCHOPInstance(const OP_NodeInfo* info)
	{
		return new RustCHOP(info);
	}

	DLLEXPORT
	void DestroyCHOPInstance(CHOP_CPlusPlusBase* instance)
	{
		delete (RustCHOP*)instance;
	}
};

// Functions that will be defined in Rust
extern "C"
{
	void execute_rs(float* chanData, size_t chanIndex, size_t chanSamples, uint32_t executeCount);
}

RustCHOP::RustCHOP(const OP_NodeInfo* info) 
{
	executeCount = 0;
}

RustCHOP::~RustCHOP()
{
}

void RustCHOP::getGeneralInfo(CHOP_GeneralInfo* ginfo)
{
	ginfo->cookEveryFrameIfAsked = true;
	ginfo->timeslice = false;
}

bool RustCHOP::getOutputInfo(CHOP_OutputInfo* info)
{
	info->numChannels = 1;
	info->numSamples = 100;
	info->startIndex = 0;
	return true;
}

const char* RustCHOP::getChannelName(int32_t index, void* reserved)
{
	return "chan_rust";
}

void RustCHOP::execute(const CHOP_Output* output, OP_Inputs* inputs, void* reserved)
{
	executeCount++;

	if (inputs->getNumInputs() > 0)
	{
		// TODO: for now, we ignore any CHOP inputs 
	}
	else 
	{
		// For now, pass each channel (in sequence) to the Rust .lib
		for (int i = 0; i < output->numChannels; ++i)
		{
			execute_rs(output->channels[i], i, output->numSamples, executeCount);
		}
	}
}

int32_t RustCHOP::getNumInfoCHOPChans()
{
	return 0;
}

void RustCHOP::getInfoCHOPChan(int32_t index, OP_InfoCHOPChan* chan)
{
}

bool RustCHOP::getInfoDATSize(OP_InfoDATSize* infoSize)
{
	infoSize->rows = 0;
	infoSize->cols = 0;
	return true;
}

void RustCHOP::getInfoDATEntries(int32_t index, int32_t nEntries, OP_InfoDATEntries* entries)
{
}

void RustCHOP::setupParameters(OP_ParameterManager* manager)
{
}

void RustCHOP::pulsePressed(const char* name)
{
}

