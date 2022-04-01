/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2020, Google Inc.
 *
 * rkisp1_ipa_serializer.h - Image Processing Algorithm data serializer for rkisp1
 *
 * This file is auto-generated. Do not edit.
 */

#pragma once

#include <tuple>
#include <vector>

#include <libcamera/ipa/rkisp1_ipa_interface.h>
#include <libcamera/ipa/core_ipa_serializer.h>

#include "libcamera/internal/control_serializer.h"
#include "libcamera/internal/ipa_data_serializer.h"

namespace libcamera {

LOG_DECLARE_CATEGORY(IPADataSerializer)

template<>
class IPADataSerializer<ipa::rkisp1::RkISP1Event>
{
public:
	static std::tuple<std::vector<uint8_t>, std::vector<SharedFD>>
	serialize(const ipa::rkisp1::RkISP1Event &data,
		  ControlSerializer *cs)
	{
		std::vector<uint8_t> retData;

		std::vector<uint8_t> op;
		std::tie(op, std::ignore) =
			IPADataSerializer<uint32_t>::serialize(data.op);
		retData.insert(retData.end(), op.begin(), op.end());

		std::vector<uint8_t> frame;
		std::tie(frame, std::ignore) =
			IPADataSerializer<uint32_t>::serialize(data.frame);
		retData.insert(retData.end(), frame.begin(), frame.end());

		std::vector<uint8_t> bufferId;
		std::tie(bufferId, std::ignore) =
			IPADataSerializer<uint32_t>::serialize(data.bufferId);
		retData.insert(retData.end(), bufferId.begin(), bufferId.end());

		if (data.controls.size() > 0) {
			std::vector<uint8_t> controls;
			std::tie(controls, std::ignore) =
				IPADataSerializer<ControlList>::serialize(data.controls, cs);
			appendPOD<uint32_t>(retData, controls.size());
			retData.insert(retData.end(), controls.begin(), controls.end());
		} else {
			appendPOD<uint32_t>(retData, 0);
		}

		if (data.sensorControls.size() > 0) {
			std::vector<uint8_t> sensorControls;
			std::tie(sensorControls, std::ignore) =
				IPADataSerializer<ControlList>::serialize(data.sensorControls, cs);
			appendPOD<uint32_t>(retData, sensorControls.size());
			retData.insert(retData.end(), sensorControls.begin(), sensorControls.end());
		} else {
			appendPOD<uint32_t>(retData, 0);
		}

		return {retData, {}};
	}

	static ipa::rkisp1::RkISP1Event
	deserialize(std::vector<uint8_t> &data,
		    ControlSerializer *cs)
	{
		return IPADataSerializer<ipa::rkisp1::RkISP1Event>::deserialize(data.cbegin(), data.cend(), cs);
	}


	static ipa::rkisp1::RkISP1Event
	deserialize(std::vector<uint8_t>::const_iterator dataBegin,
		    std::vector<uint8_t>::const_iterator dataEnd,
		    ControlSerializer *cs)
	{
		ipa::rkisp1::RkISP1Event ret;
		std::vector<uint8_t>::const_iterator m = dataBegin;

		size_t dataSize = std::distance(dataBegin, dataEnd);

		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "op"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		ret.op = static_cast<ipa::rkisp1::RkISP1Operations>(IPADataSerializer<uint32_t>::deserialize(m, m + 4));
		m += 4;
		dataSize -= 4;


		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "frame"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		ret.frame = IPADataSerializer<uint32_t>::deserialize(m, m + 4);
		m += 4;
		dataSize -= 4;


		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "bufferId"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		ret.bufferId = IPADataSerializer<uint32_t>::deserialize(m, m + 4);
		m += 4;
		dataSize -= 4;


		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "controlsSize"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		const size_t controlsSize = readPOD<uint32_t>(m, 0, dataEnd);
		m += 4;
		dataSize -= 4;
		if (dataSize < controlsSize) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "controls"
				<< ": not enough data, expected "
				<< (controlsSize) << ", got " << (dataSize);
			return ret;
		}
		if (controlsSize > 0)
			ret.controls =
				IPADataSerializer<ControlList>::deserialize(m, m + controlsSize, cs);
		m += controlsSize;
		dataSize -= controlsSize;


		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "sensorControlsSize"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		const size_t sensorControlsSize = readPOD<uint32_t>(m, 0, dataEnd);
		m += 4;
		dataSize -= 4;
		if (dataSize < sensorControlsSize) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "sensorControls"
				<< ": not enough data, expected "
				<< (sensorControlsSize) << ", got " << (dataSize);
			return ret;
		}
		if (sensorControlsSize > 0)
			ret.sensorControls =
				IPADataSerializer<ControlList>::deserialize(m, m + sensorControlsSize, cs);

		return ret;
	}

	static ipa::rkisp1::RkISP1Event
	deserialize(std::vector<uint8_t> &data,
		    [[maybe_unused]] std::vector<SharedFD> &fds,
		    ControlSerializer *cs = nullptr)
	{
		return IPADataSerializer<ipa::rkisp1::RkISP1Event>::deserialize(data.cbegin(), data.cend(), cs);
	}

	static ipa::rkisp1::RkISP1Event
	deserialize(std::vector<uint8_t>::const_iterator dataBegin,
		    std::vector<uint8_t>::const_iterator dataEnd,
		    [[maybe_unused]] std::vector<SharedFD>::const_iterator fdsBegin,
		    [[maybe_unused]] std::vector<SharedFD>::const_iterator fdsEnd,
		    ControlSerializer *cs = nullptr)
	{
		return IPADataSerializer<ipa::rkisp1::RkISP1Event>::deserialize(dataBegin, dataEnd, cs);
	}
};

template<>
class IPADataSerializer<ipa::rkisp1::RkISP1Action>
{
public:
	static std::tuple<std::vector<uint8_t>, std::vector<SharedFD>>
	serialize(const ipa::rkisp1::RkISP1Action &data,
		  ControlSerializer *cs)
	{
		std::vector<uint8_t> retData;

		std::vector<uint8_t> op;
		std::tie(op, std::ignore) =
			IPADataSerializer<uint32_t>::serialize(data.op);
		retData.insert(retData.end(), op.begin(), op.end());

		if (data.controls.size() > 0) {
			std::vector<uint8_t> controls;
			std::tie(controls, std::ignore) =
				IPADataSerializer<ControlList>::serialize(data.controls, cs);
			appendPOD<uint32_t>(retData, controls.size());
			retData.insert(retData.end(), controls.begin(), controls.end());
		} else {
			appendPOD<uint32_t>(retData, 0);
		}

		if (data.sensorControls.size() > 0) {
			std::vector<uint8_t> sensorControls;
			std::tie(sensorControls, std::ignore) =
				IPADataSerializer<ControlList>::serialize(data.sensorControls, cs);
			appendPOD<uint32_t>(retData, sensorControls.size());
			retData.insert(retData.end(), sensorControls.begin(), sensorControls.end());
		} else {
			appendPOD<uint32_t>(retData, 0);
		}

		return {retData, {}};
	}

	static ipa::rkisp1::RkISP1Action
	deserialize(std::vector<uint8_t> &data,
		    ControlSerializer *cs)
	{
		return IPADataSerializer<ipa::rkisp1::RkISP1Action>::deserialize(data.cbegin(), data.cend(), cs);
	}


	static ipa::rkisp1::RkISP1Action
	deserialize(std::vector<uint8_t>::const_iterator dataBegin,
		    std::vector<uint8_t>::const_iterator dataEnd,
		    ControlSerializer *cs)
	{
		ipa::rkisp1::RkISP1Action ret;
		std::vector<uint8_t>::const_iterator m = dataBegin;

		size_t dataSize = std::distance(dataBegin, dataEnd);

		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "op"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		ret.op = static_cast<ipa::rkisp1::RkISP1Operations>(IPADataSerializer<uint32_t>::deserialize(m, m + 4));
		m += 4;
		dataSize -= 4;


		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "controlsSize"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		const size_t controlsSize = readPOD<uint32_t>(m, 0, dataEnd);
		m += 4;
		dataSize -= 4;
		if (dataSize < controlsSize) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "controls"
				<< ": not enough data, expected "
				<< (controlsSize) << ", got " << (dataSize);
			return ret;
		}
		if (controlsSize > 0)
			ret.controls =
				IPADataSerializer<ControlList>::deserialize(m, m + controlsSize, cs);
		m += controlsSize;
		dataSize -= controlsSize;


		if (dataSize < 4) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "sensorControlsSize"
				<< ": not enough data, expected "
				<< (4) << ", got " << (dataSize);
			return ret;
		}
		const size_t sensorControlsSize = readPOD<uint32_t>(m, 0, dataEnd);
		m += 4;
		dataSize -= 4;
		if (dataSize < sensorControlsSize) {
			LOG(IPADataSerializer, Error)
				<< "Failed to deserialize " << "sensorControls"
				<< ": not enough data, expected "
				<< (sensorControlsSize) << ", got " << (dataSize);
			return ret;
		}
		if (sensorControlsSize > 0)
			ret.sensorControls =
				IPADataSerializer<ControlList>::deserialize(m, m + sensorControlsSize, cs);

		return ret;
	}

	static ipa::rkisp1::RkISP1Action
	deserialize(std::vector<uint8_t> &data,
		    [[maybe_unused]] std::vector<SharedFD> &fds,
		    ControlSerializer *cs = nullptr)
	{
		return IPADataSerializer<ipa::rkisp1::RkISP1Action>::deserialize(data.cbegin(), data.cend(), cs);
	}

	static ipa::rkisp1::RkISP1Action
	deserialize(std::vector<uint8_t>::const_iterator dataBegin,
		    std::vector<uint8_t>::const_iterator dataEnd,
		    [[maybe_unused]] std::vector<SharedFD>::const_iterator fdsBegin,
		    [[maybe_unused]] std::vector<SharedFD>::const_iterator fdsEnd,
		    ControlSerializer *cs = nullptr)
	{
		return IPADataSerializer<ipa::rkisp1::RkISP1Action>::deserialize(dataBegin, dataEnd, cs);
	}
};


} /* namespace libcamera */