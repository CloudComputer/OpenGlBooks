//========================================================
/**
*  @file      Music.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  DirectMusic������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#include "stdafx.h"
#include "music.h"


IDirectMusicPerformance* CMusic::g_pPerf=NULL;
IDirectMusicLoader*	CMusic::g_pLoader=NULL;
bool CMusic::bMusic=false;
bool CMusic::bExist=false;
bool CMusic::bPlay=false;
CMusic* CMusic::m_pMusic=NULL;

CMusic::CMusic():g_pMIDISeg(NULL)
{
	m_pMusic=this;
}

CMusic::~CMusic()
{
	if( bExist )
	{
		if (g_pMIDISeg)
		{
			g_pPerf->Stop(g_pMIDISeg, NULL, 0, 0);
			_RELEASE(g_pMIDISeg);
		}
	}
	bExist=false;
	bMusic=false;
}


/**\brief
 * �������ӿ�
 */
IDirectMusicPerformance* CMusic::CreatePerformance(void)
{
    IDirectMusicPerformance* pPerf;
 
    if (FAILED(CoCreateInstance(
            CLSID_DirectMusicPerformance,
            NULL,
            CLSCTX_INPROC, 
            IID_IDirectMusicPerformance,
            (void**)&pPerf
        )))
    {
        pPerf = NULL;
    }
    return pPerf;
}


/**\brief
 * ����LOADER
 */
IDirectMusicLoader* CMusic::CreateLoader(void)
{
    IDirectMusicLoader* pLoader;
 
    if (FAILED(CoCreateInstance(
            CLSID_DirectMusicLoader,
            NULL,
            CLSCTX_INPROC, 
            IID_IDirectMusicLoader,
            (void**)&pLoader
        )))
    {
        pLoader = NULL;
    }
    return pLoader;
}


/**\brief
 * ����һ������
 */
IDirectMusicSegment* CMusic::LoadMIDISegment(IDirectMusicLoader* pLoader, WCHAR *wszMidiFileName )
{
	if( !bMusic )return NULL;		//û������

	//����ļ��Ƿ����
	FILE *fp;
	char* str = Char(wszMidiFileName);
	fp=fopen(str , "rb");
	_DELETE( str );
	if( fp==NULL )
	{
		ShowMessage("Midi file %s not found!",Char(wszMidiFileName));
		return NULL;
	}
	fclose(fp);

    DMUS_OBJECTDESC ObjDesc; 
    IDirectMusicSegment* pSegment = NULL;

    ObjDesc.guidClass = CLSID_DirectMusicSegment;
    ObjDesc.dwSize = sizeof(DMUS_OBJECTDESC);
    wcscpy(ObjDesc.wszFileName, wszMidiFileName );
    ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;
 
    pLoader->GetObject(&ObjDesc,
            IID_IDirectMusicSegment, (void**) &pSegment);		//�õ�object
 
    pSegment->SetParam(GUID_StandardMIDIFile,
            -1, 0, 0, (void*)g_pPerf);							//�����ֶӵ�����
 
    pSegment->SetParam(GUID_Download, -1, 0, 0, (void*)g_pPerf);//�����Զ�����
 
    return pSegment;
}


/**\brief
 * ��ʼ��
 */
BOOL CMusic::InitMusic()
{	
	if(bExist)return true;		//���������

    if (SUCCEEDED(CoInitialize(NULL)))		//��ʼ��COM
    {
		if( !bExist )						//�����岻����
		{
			bExist=true;					
			g_pPerf = CreatePerformance();	//�������ӿ�
			if (g_pPerf == NULL)
			{
				MessageBox(NULL,"CreatePerformance\n��ʼ��DirectMusic���̳���\
					�������Ƿ���ȷ�İ�װ��DirectX 7.0���ϰ汾������������������\
					ռ�������������㽫�޷������������֡�","ERROR",MB_OK);
				bMusic=false;
				return false;
			}	

			if (FAILED(g_pPerf->Init(NULL, NULL, NULL)))
			{
				MessageBox(NULL,"Init\nDirectMusic ��ʼ�������밲װDirectX 7.0��\
					�ϰ汾������������������ռ�������������㽫�޷������������֡�",
					"ERROR",MB_OK);
				bMusic=false;
				return false;
			}	
		
			if (FAILED(g_pPerf->AddPort(NULL)))		//���һ��port
			{	
				MessageBox(NULL,"AddPort\nDirectMusic ��ʼ�������밲װDirectX 7.0��\
					�ϰ汾������������������ռ�������������㽫�޷������������֡�",
					"ERROR",MB_OK);
				bMusic=false;
				return false;
			}

			g_pLoader = CreateLoader();				//����һ��loader
			if (g_pLoader == NULL)
			{
				MessageBox(NULL,"CreatLoader\nDirectMusic ��ʼ������\
					�밲װDirectX 7.0���ϰ汾������������������ռ�������������㽫�޷�\
					�����������֡�","ERROR",MB_OK);
				bMusic=false;
				return false;
			}
		}
		bMusic=true;
		return true;
	}
	bMusic=false;
	return false;
}


/**\brief
 * ����
 */
BOOL CMusic::LoadMusic(WCHAR *filename)
{
	if( !bMusic )return true;		//û������

	wcscpy( MusicFile, filename );		
	if (g_pLoader)
	{
		_RELEASE(g_pMIDISeg);

		g_pMIDISeg = LoadMIDISegment(g_pLoader,filename);	//����һ����
		return true;
	}
	return false;
}

/**\brief
 * ����
 */
BOOL CMusic::Play(int start)
{
	if( !bMusic )return true;

	IDirectMusicSegmentState* g_pSegState;		//��ǰ��״̬
	if (g_pMIDISeg)
	{
		//����һ���Σ�������״̬
		g_pPerf->PlaySegment(g_pMIDISeg, DMUS_SEGF_REFTIME , start, &g_pSegState);	
	}
	bPlay=true;
	return true;
}


/**\brief
 * �Ƿ����ڲ���
 */
BOOL CMusic::IsPlay()
{
	if( !bMusic )return true;	//û������

	if (g_pMIDISeg)
	{
		if( (g_pPerf->IsPlaying(g_pMIDISeg,NULL))==S_OK )
			return true;
	}
	return false;
}


/**\brief
 * ֹͣ����
 */
BOOL CMusic::Stop()
{
	if( !bMusic )return true;

	if (g_pMIDISeg)
	{
		if( (g_pPerf->Stop(g_pMIDISeg, NULL, 0, 0))==S_OK )
		{
			bPlay=false;
			return true;
		}
	}
	return false;
}


/**\brief
 * ��ͣ����
 */
BOOL CMusic::Pause()
{
	if( !bMusic )return true;

	if (g_pMIDISeg)
	{
		g_pPerf->GetTime(NULL, &PauseTime);		//���ŵ���ʲôλ��

		if( (g_pPerf->Stop(g_pMIDISeg, NULL, 0, 0))==S_OK )	//ֹͣ
		{
			bPlay=false;
			return true;
		}
		return false;
	}
	return false;
}


/**\brief
 * ��ͣ��������������
 */
BOOL CMusic::Resume()
{
	if( !bMusic ) return true;

	if (g_pMIDISeg)
	{
		g_pMIDISeg->SetStartPoint(PauseTime);	//��ʼ��λ��
		IDirectMusicSegmentState* g_pSegState;	//����
		g_pPerf->PlaySegment(g_pMIDISeg,DMUS_SEGF_REFTIME,0,&g_pSegState);
		g_pMIDISeg->SetStartPoint(0);					
		bPlay=true;
		return true;
	}
	return false;
}
