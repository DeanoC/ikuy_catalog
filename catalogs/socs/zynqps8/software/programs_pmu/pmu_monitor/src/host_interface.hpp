#pragma once

#include "zmodem.hpp"

struct HostInterface {
	enum class State : uint8_t {
		RECEIVING_COMMAND,
		PROCESSING_COMMAND,
		ZMODEM,
  } currentState;

	enum class DownloadTarget : uint8_t {
		A53,
		R5F,
		DATA
	} currentDownloadTarget;

	void Init();
	[[maybe_unused]] void Fini();
	void InputCallback();
	void CommandCallback();
	void EchoCmd(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int findCount);
	void PostDownload();
	void WhatCommand();
	void Read4BCmd(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int findCount);
	void Read16BCmd(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int findCount);

	bool DecodeAddress(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int const findCount);

	static const int CMD_BUF_SIZE = 256;
	uint8_t cmdBuffer[CMD_BUF_SIZE];
	uint32_t cmdBufferHead;
	uintptr_all_t downloadAddress;
  ZModem zModem;
	uintptr_all_t lastReadAddress;
	bool lastCommandWasR;

	void DownloadAt(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int const findCount);
	void SleepCpu(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int const findCount);
	void WakeUpCpu(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int const findCount);
	void BootCpu(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int const findCount);
	void Reset(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int const findCount);
	void HardReset(uint8_t const *cmdBuffer, unsigned int const *finds, unsigned int const findCount);
};
