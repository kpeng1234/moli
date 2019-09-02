#pragma once
#include "CTSPlugInterFace.h"
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/daily_file_sink.h"

#define LOG_MODEL_STR "maitianPT"

class localTS
{
public:
	localTS();
	~localTS();
	BOOL static registerTS();
	void initTSDLL();
	void static intLogModel();
	void static releaseLogModel();
	void getGameInformatio();
private:
	CTSPlugInterFace ts;
	std::shared_ptr<spdlog::logger> logger = NULL;
	void test(int);

};

