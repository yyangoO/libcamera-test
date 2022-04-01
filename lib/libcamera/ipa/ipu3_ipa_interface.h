/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2020, Google Inc.
 *
 * ipu3_ipa_interface.h - Image Processing Algorithm interface for ipu3
 *
 * This file is auto-generated. Do not edit.
 */

#pragma once

#include <libcamera/ipa/core_ipa_interface.h>
#include <libcamera/ipa/ipa_interface.h>


#include <vector>

namespace libcamera {

namespace ipa {

namespace ipu3 {




enum class _IPU3Cmd {
	Exit = 0,
	Init = 1,
	Start = 2,
	Stop = 3,
	Configure = 4,
	MapBuffers = 5,
	UnmapBuffers = 6,
	ProcessEvent = 7,
};

enum class _IPU3EventCmd {
	QueueFrameAction = 1,
};


enum IPU3Operations {
	ActionSetSensorControls = 1,
	ActionParamFilled = 2,
	ActionMetadataReady = 3,
	EventProcessControls = 4,
	EventStatReady = 5,
	EventFillParams = 6,
};

struct IPU3Event
{
public:
#ifndef __DOXYGEN__
	IPU3Event()
		: op(static_cast<IPU3Operations>(0)), frame(0), frameTimestamp(0), bufferId(0)
	{
	}

	IPU3Event(const IPU3Operations &_op, uint32_t _frame, int64_t _frameTimestamp, uint32_t _bufferId, const ControlList &_controls, const ControlList &_sensorControls, const ControlList &_lensControls)
		: op(_op), frame(_frame), frameTimestamp(_frameTimestamp), bufferId(_bufferId), controls(_controls), sensorControls(_sensorControls), lensControls(_lensControls)
	{
	}
#endif


	IPU3Operations op;
	uint32_t frame;
	int64_t frameTimestamp;
	uint32_t bufferId;
	ControlList controls;
	ControlList sensorControls;
	ControlList lensControls;
};

struct IPU3Action
{
public:
#ifndef __DOXYGEN__
	IPU3Action()
		: op(static_cast<IPU3Operations>(0))
	{
	}

	IPU3Action(const IPU3Operations &_op, const ControlList &_controls, const ControlList &_sensorControls, const ControlList &_lensControls)
		: op(_op), controls(_controls), sensorControls(_sensorControls), lensControls(_lensControls)
	{
	}
#endif


	IPU3Operations op;
	ControlList controls;
	ControlList sensorControls;
	ControlList lensControls;
};

struct IPAConfigInfo
{
public:
#ifndef __DOXYGEN__
	IPAConfigInfo()
	{
	}

	IPAConfigInfo(const IPACameraSensorInfo &_sensorInfo, const ControlInfoMap &_sensorControls, const ControlInfoMap &_lensControls, const Size &_bdsOutputSize, const Size &_iif)
		: sensorInfo(_sensorInfo), sensorControls(_sensorControls), lensControls(_lensControls), bdsOutputSize(_bdsOutputSize), iif(_iif)
	{
	}
#endif


	IPACameraSensorInfo sensorInfo;
	ControlInfoMap sensorControls;
	ControlInfoMap lensControls;
	Size bdsOutputSize;
	Size iif;
};

class IPAIPU3Interface : public IPAInterface
{
public:

	virtual int32_t init(
		const IPASettings &settings,
		const IPACameraSensorInfo &sensorInfo,
		const ControlInfoMap &sensorControls,
		ControlInfoMap *ipaControls) = 0;

	virtual int32_t start() = 0;

	virtual void stop() = 0;

	virtual int32_t configure(
		const IPAConfigInfo &configInfo,
		ControlInfoMap *ipaControls) = 0;

	virtual void mapBuffers(
		const std::vector<libcamera::IPABuffer> &buffers) = 0;

	virtual void unmapBuffers(
		const std::vector<uint32_t> &ids) = 0;

	virtual void processEvent(
		const IPU3Event &ev) = 0;

	Signal<uint32_t, const IPU3Action &> queueFrameAction;
};

} /* namespace ipu3 */

} /* namespace ipa */

} /* namespace libcamera */