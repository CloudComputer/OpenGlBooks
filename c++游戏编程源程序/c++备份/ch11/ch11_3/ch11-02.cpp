
#include "stdafx.h"
#include <dshow.h>

int main()
{
    IGraphBuilder *pGraph;
    IMediaControl *pMediaControl;
	IMediaEvent   *pEvent;

    CoInitialize(NULL);
    
    // �إ�Media����
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                        IID_IGraphBuilder, (void **)&pGraph);
    pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
  
    // Ū��"test.avi"�ɮ�
    pGraph->RenderFile(L"test.avi", NULL);

    // ø�s�ʵe
    pMediaControl->Run();

    // ���ݰʵe���񵲧�
    long evCode;
    pEvent->WaitForCompletion(INFINITE, &evCode);

    // �M������
	pEvent->Release();
    pMediaControl->Release();
    pGraph->Release();
	
    CoUninitialize();
	return 0;
}

