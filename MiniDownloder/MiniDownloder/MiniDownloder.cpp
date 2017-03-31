// MiniDownloder.cpp
//
#include "Defines.h"
#include "DownloadManager.h"
#include "DownloadTask.h"
#include "TaskGroup.h"

#include <string>

#ifdef _MSC_VER
#include <windows.h>
#endif

int main()
{
	std::string url = "http://sw.bos.baidu.com/sw-search-sp/software/fdc0a25416cd7/ue_chinese_23.20.0.43.exe";

	int index = url.rfind('/');
	std::string file1 = url.substr(index + 1, url.length() - index);

	libdlmgr::DownloadManager::GetSingleton().Init("F:\\MiniDownloder\\cache");

	libdlmgr::TaskPtr task = libdlmgr::DownloadManager::GetSingleton().CreateDownLoadTask(url);
	task->SetDownloadPercentCallBack([](double percent)
	{
		printf("percent %lf%%\n", percent);
	});
	libdlmgr::DownloadManager::GetSingleton().AddDownLoadTask(task);

	while (true)
	{
		libdlmgr::DownloadManager::GetSingleton().Update();
#ifdef _MSC_VER
		Sleep(10);
#else
		usleep(100 * 1000);
#endif
	}

	libdlmgr::DownloadManager::GetSingleton().DeInit();

    return 0;
}

