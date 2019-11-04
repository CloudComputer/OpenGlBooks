#define INITGUID
#define _WIN32_DCOM
#include <stdio.h>
#include <dplay8.h>

IDirectPlay8Server*                 g_pDPServer      = NULL;
IDirectPlay8Address*                g_pDeviceAddress = NULL;
IDirectPlay8Address*                g_pHostAddress   = NULL;

GUID g_guidApp = { 0x1ad4ca3b, 0xac68, 0x4d9b, { 0x95, 0x22, 0xbe, 0x59, 0xcd, 0x48, 0x52, 0x76 } };


HRESULT WINAPI DirectPlayMessageHandler(PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer);
BOOL    IsServiceProviderValid(const GUID* pGuidSP);
HRESULT InitDirectPlay();
HRESULT CreateDeviceAddress();
HRESULT HostSession();
HRESULT SendDirectPlayMessage();
void    CleanupDirectPlay();

#define SAFE_DELETE(p)          {if(p) {delete (p);     (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)    {if(p) {delete[] (p);   (p)=NULL;}}
#define SAFE_RELEASE(p)         {if(p) {(p)->Release(); (p)=NULL;}}

#define USER_EXIT       1
#define USER_SEND       2


int main(int argc, char* argv[], char* envp[])
{
    HRESULT                     hr;
    int                         iUserChoice;

    //��l��COM����
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // ��l��DirectPlay����
    if( FAILED( hr = InitDirectPlay() ) )
    {
        printf("��l��DirectPlay����:  0x%X\n", hr);
        goto LCleanup;
    }

    if( FAILED( hr = CreateDeviceAddress() ) )
    {
        printf("�إߦ�}����:  0x%X\n", hr);
        goto LCleanup;
    }

    if( FAILED( hr = HostSession() ) )
    {
        printf("�إߥ�������:  0x%X\n", hr);
        goto LCleanup;
    }

    // ��ܥ\���
    do
    {
        printf("�п�ܶ���.\n1.  ���}\n2.  �ǰe�T��\n");
        scanf("%d", &iUserChoice);

        if( iUserChoice == USER_SEND )
        {
            if( FAILED( hr = SendDirectPlayMessage() ) )
            {
                printf("�ǰe�T������:  0x%X\n", hr);
                goto LCleanup;
            }
        }
    } while (iUserChoice != USER_EXIT);

    
LCleanup:
    CleanupDirectPlay();

    // ����COM����
    CoUninitialize();

    return 0;
}


HRESULT InitDirectPlay()
{
    HRESULT     hr = S_OK;

    // �إ� IDirectPlay8Server ����
    if( FAILED( hr = CoCreateInstance(CLSID_DirectPlay8Server, NULL, 
                                    CLSCTX_INPROC_SERVER,
                                    IID_IDirectPlay8Server, 
                                    (LPVOID*) &g_pDPServer ) ) )
    {
        printf("Failed Creating the IDirectPlay8Peer Object:  0x%X\n", hr);
        goto LCleanup;
    }

    // ��l��DirectPlay
    if( FAILED( hr = g_pDPServer->Initialize(NULL, DirectPlayMessageHandler, 0 ) ) )
    {
        printf("Failed Initializing DirectPlay:  0x%X\n", hr);
        goto LCleanup;
    }
    
    // �إߥH TCP/IP ���q�T��w��Server��
    if( FALSE == IsServiceProviderValid(&CLSID_DP8SP_TCPIP ) )
    {
        hr = E_FAIL;
        printf("Failed validating CLSID_DP8SP_TCPIP");
        goto LCleanup;
    }

LCleanup:
    return hr;
}

BOOL IsServiceProviderValid(const GUID* pGuidSP)
{
    HRESULT                     hr;
    DPN_SERVICE_PROVIDER_INFO*  pdnSPInfo = NULL;
    DWORD                       dwItems = 0;
    DWORD                       dwSize = 0;

    hr = g_pDPServer->EnumServiceProviders(&CLSID_DP8SP_TCPIP, NULL, NULL, &dwSize, &dwItems, 0);

    if( hr != DPNERR_BUFFERTOOSMALL)
    {
        printf("�C�|��w����:  0x%x\n", hr);
        goto LCleanup;
    }

    pdnSPInfo = (DPN_SERVICE_PROVIDER_INFO*) new BYTE[dwSize];

    if( FAILED( hr = g_pDPServer->EnumServiceProviders(&CLSID_DP8SP_TCPIP, NULL, pdnSPInfo, &dwSize, &dwItems, 0 ) ) )
    {
        printf("�C�|��w����:  0x%x\n", hr);
        goto LCleanup;
    }

    if( dwItems == 0)
    {
        hr = E_FAIL;
    }

LCleanup:
    SAFE_DELETE_ARRAY(pdnSPInfo);
    if( SUCCEEDED(hr) )
        return TRUE;
    else
        return FALSE;
}

HRESULT WINAPI DirectPlayMessageHandler(PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer)
{
    HRESULT     hr = S_OK;

    switch (dwMessageId)
    {
    case DPN_MSGID_RECEIVE:
        {
            PDPNMSG_RECEIVE     pMsg;

            pMsg = (PDPNMSG_RECEIVE) pMsgBuffer;

            printf("\n�����쪺�T����:  %S\n", (WCHAR*)pMsg->pReceiveData);
            break;
        }
    }
    return hr;
}

HRESULT CreateDeviceAddress()
{
    HRESULT         hr = S_OK;

    // �إ� IDirectPlay8Address �˸m����}
    if( FAILED( hr = CoCreateInstance(CLSID_DirectPlay8Address, NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_IDirectPlay8Address,
                                    (LPVOID*) &g_pDeviceAddress ) ) )
    {
        printf("IDirectPlay8Address����إߥ���:  0x%X\n", hr);
        goto LCleanup;
    }
    
    // �]�w�˸m��}
    if( FAILED( hr = g_pDeviceAddress->SetSP(&CLSID_DP8SP_TCPIP ) ) )
    {
        printf("�]�w�˸m��}����:  0x%X\n", hr);
        goto LCleanup;
    }

LCleanup:
    return hr;
}

HRESULT HostSession()
{
    HRESULT                 hr = S_OK;
    DPN_APPLICATION_DESC    dpAppDesc;
    DPN_PLAYER_INFO         dpPlayerInfo;
    WCHAR                   wszSession[128];
    WCHAR                   wszName[] = L"Server";


    ZeroMemory(&dpPlayerInfo, sizeof(DPN_PLAYER_INFO));
    dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
    dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
    dpPlayerInfo.pwszName = wszName;
    dpPlayerInfo.pvData = NULL;
    dpPlayerInfo.dwDataSize = NULL;
    dpPlayerInfo.dwPlayerFlags = 0;

    if( FAILED( hr = g_pDPServer->SetServerInfo( &dpPlayerInfo, NULL, NULL, 
                                                 DPNSETSERVERINFO_SYNC ) ) )
    {
        printf("Failed Hosting:  0x%X\n", hr);
        goto LCleanup;
    }

    printf("\n�п�J�����W��.\n");
    wscanf(L"%ls", wszSession);

    ZeroMemory(&dpAppDesc, sizeof(DPN_APPLICATION_DESC));
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.dwFlags = DPNSESSION_CLIENT_SERVER;
    dpAppDesc.guidApplication = g_guidApp;
    dpAppDesc.pwszSessionName = wszSession;

    if( FAILED( hr = g_pDPServer->Host(&dpAppDesc,       
                                &g_pDeviceAddress, 1,    
                                NULL, NULL,              
                                NULL,                    
                                0 ) ) )                  
    {
        printf("�����W�٥���:  0x%X\n", hr);
        goto LCleanup;
    }
    else
    {
        printf("�������ݤ�...\n");
    }

LCleanup:
    return hr;
}

HRESULT SendDirectPlayMessage()
{
    HRESULT         hr = S_OK;
    DPN_BUFFER_DESC dpnBuffer;
    WCHAR           wszData[256];

    printf("\n��J�r��.\n");
    wscanf(L"%ls", wszData);

    dpnBuffer.pBufferData = (BYTE*) wszData;
    dpnBuffer.dwBufferSize = 2 * (wcslen(wszData) + 1);

    if( FAILED( hr = g_pDPServer->SendTo(DPNID_ALL_PLAYERS_GROUP,   
                                    &dpnBuffer,                     
                                    1,                              
                                    0,                              
                                    NULL,                           
                                    NULL,                           
                                    DPNSEND_SYNC |                  
                                    DPNSEND_NOLOOPBACK ) ) )        
    {
        printf("�e�X��ƥ���:  0x%x\n", hr);
    }
    return hr;
}




void CleanupDirectPlay()
{
    if( g_pDPServer)
        g_pDPServer->Close(0);

    SAFE_RELEASE(g_pDeviceAddress);
    SAFE_RELEASE(g_pHostAddress);
    SAFE_RELEASE(g_pDPServer);
}
