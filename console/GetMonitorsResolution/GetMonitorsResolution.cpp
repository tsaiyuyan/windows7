// GetMonitorsResolution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "wtypes.h"
#include <iostream>
using namespace std;



BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor,
                              HDC      hdcMonitor,
                              LPRECT   lprcMonitor,
                              LPARAM   dwData)
{
	MONITORINFOEX info;
    info.cbSize = sizeof(info);
    if (GetMonitorInfo(hMonitor, &info))
    {
		if(info.dwFlags == MONITORINFOF_PRIMARY)
			std::cout <<"main :" << endl;

		auto x = std::abs(info.rcMonitor.left - info.rcMonitor.right);
		auto y = std::abs(info.rcMonitor.top  - info.rcMonitor.bottom);
        std::cout << "Monitor x: "<< x
                  <<" y: "        << y
                  << std::endl;

		if(x !=1920 || y!=1080)
		{
			DEVMODE dm;
			memset(&dm, 0, sizeof (dm));	
			dm.dmSize = sizeof (dm);

			BOOL bResult = EnumDisplaySettings(info.szDevice,ENUM_CURRENT_SETTINGS, &dm);
			if (bResult)
			{			
				dm.dmPelsWidth = 1920;
				dm.dmPelsHeight = 1080;
				dm.dmFields =DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
				DWORD dwFlags =  ( CDS_GLOBAL | CDS_UPDATEREGISTRY | CDS_RESET);
	
				auto status = ChangeDisplaySettingsEx(info.szDevice,&dm,NULL, NULL, NULL);		
				if ( status == DISP_CHANGE_SUCCESSFUL ){
					
				}			
			}else
			{
				auto err = GetLastError();
			
			}
		}

    }
    return TRUE;  // continue enumerating
}

int main()
{
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);

    return 0;
}