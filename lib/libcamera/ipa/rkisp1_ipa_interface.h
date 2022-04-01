/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2020, Google Inc.
 *
 * rkisp1_ipa_interface.h - Image Processing Algorithm interface for rkisp1
 *
 * This file is auto-generated. Do not edit.
 */

#pragma once

#include <libcamera/ipa/core_ipa_interface.h>
#include <libcamera/ipa/ipa_interface.h>

#include <map>
#include <vector>

namespace libcamera {

namespace ipa {

namespace rkisp1 {




enum class _RkISP1Cmd {
	Exit = 0,
	Init = 1,
	Start = 2,
	Stop = 3,
	Configure = 4,
	MapBuffers = 5,
	UnmapBuffers = 6,
	ProcessEvent = 7,
};

enum class _RkISP1EventCmd {
	QueueFrameAction = 1,
};


enum RkISP1Operations {
	ActionV4L2Set = 1,
	ActionParamFilled = 2,
	ActionMetadata = 3,
	EventSignalStatBuffer = 4,
	EventQueueRequest = 5,
};

struct RkISP1Event
{
public:
#ifndef __DOXYGEN__
	RkISP1Event()
		: op(static_cast<RkISP1Operations>(0)), frame(0), bufferId(0)
	{
	}

	RkISP1Event(const RkISP1Operations &_op, uint32_t _frame, uint32_t _bufferId, const ControlList &_controls, const ControlList &_sensorControls)
		: op(_op), frame(_frame), bufferId(_bufferId), controls(_controls), sensorControls(_sensorControls)
	{
	}
#endif


	RkISP1Operations op;
	uint32_t frame;
	uint32_t bufferId;
	ControlList controls;
	ControlList sensorControls;
};

struct RkISP1Action
{
public:
#ifndef __DOXYGEN__
	RkISP1Action()
		: op(static_cast<RkISP1Operations>(0))
	{
	}

	RkISP1Action(const RkISP1Operations &_op, const ControlList &_controls, const ControlList &_sensorControls)
		: op(_op), controls(_controls), sensorControls(_sensorControls)
	{
	}
#endif


	RkISP1Operations op;
	ControlList controls;
	ControlList sensorControls;
};

class IPARkISP1Interface : public IPAInterface
{
public:

	virtual int32_t init(
		const IPASettings &settings,
		const uint32_t hwRevision) = 0;

	virtual int32_t start() = 0;

	virtual void stop() = 0;

	virtual int32_t configure(
		const IPACameraSensorInfo &sensorInfo,
		const std::map<uint32_t, libcamera::IPAStream> &streamConfig,
		const std::map<uint32_t, libcamera::ControlInfoMap> &entityControls) = 0;

	virtual void mapBuffers(
		const std::vector<libcamera::IPABuffer> &buffers) = 0;

	virtual void unmapBuffers(
		const std::vector<uint32_t> &ids) = 0;

	virtual void processEvent(
		const RkISP1Event &ev) = 0;

	Signal<uint32_t, const RkISP1Action &> queueFrameAction;
};

} /* namespace rkisp1 */

} /* namespace ipa */

} /* namespace libcamera */