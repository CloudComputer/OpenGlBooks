// appProc.cpp: implementation of the appProc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "canvasr.h"
#include "appProc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
appProc *app_Proc = NULL ;


void appProc::Run()
{

}

void appProc::Render()
{

}

/*///////////////////////////////////////////

  �C���ιϤ��ʵe

/*///////////////////////////////////////////
d3dCartoon app_Back ;//�I��
d3dCartoon app_Role[4] ;//����
d3dCartoon app_Prop[3] ;//��������
gameObj * app_Sort ;//�ƧǥΦ�C��

d3dTexture app_Shadow ;//�v�l

d3dTexture app_Title ;//���D
gameRole app_GamePlay ;//���a��T
gameRole app_GameProp[32] ;//��������

typedef struct _GAME_DATA
{
	//���ʸ�T
	int mWidth , mHeight ;
	int mScreenX , mScreenY ;
	//�U�@�ӱ������~�ɶ�
	int rTimeDown ;
	//�o��
	int		sTimeGame ;//�C���ɶ�
	int     sTimeGet  ;//���~���o�ɶ�
	int		sScore ;//�o��
	int		sNum ;//���o�ƶq
	//power
	int		sTimePower ;//�O�q�ɶ�
	int		sPowerNum ;//�ƶq
}GAME_DATA ;
GAME_DATA gm_Da ;
/*///////////////////////////////////////////

  �򩳪���ŧi

/*///////////////////////////////////////////

/*///////////////////////////////////////////

  �Ƨ�

/*///////////////////////////////////////////
void gameObj::AddSort()
{
	gameObj *sort ;
	gameObj *exit ;
	m_Exit = NULL ;
	m_Next = NULL ;
	//�Y�򩳨S������A�N�����[�J
	sort = app_Sort ;
	if( !sort )
	{
		app_Sort = this ;
		return ;
	}
	//Y�Y���̤p�A�[�J�Ĥ@��
	if( m_y <= sort->m_y )
	{
		m_Exit = sort ;
		sort->m_Next = this ;
		app_Sort = this ;
		return ;
	}
	//�}�l�̧ǧP�_Z
	while( sort )
	{
		if( m_y <= sort->m_y )
		{
			//�[�J�U�@��
			if( sort->m_Next )
				sort->m_Next->m_Exit = this ;
			m_Next = sort->m_Next ;
			//�[�J�W�@��
			sort->m_Next = this ;
			m_Exit = sort ;
			return ;
		}
		exit = sort ;
		sort = sort->m_Exit ;
	}
	//Y���̤j�ȡA�[�J��̫�@��
	exit->m_Exit = this ;
	m_Next = exit ;
}

void gameObj::SortDraw()
{

}

/*///////////////////////////////////////////

  �ƧǥΪ���

/*///////////////////////////////////////////
//��l��
void appSortInit()
{
	app_Sort = NULL ;
}
//ø�s
void appSortDraw()
{
	gameObj * sort ;
	sort = app_Sort ;
	while( sort )
	{
		sort->SortDraw();
		sort = sort->m_Exit ;
	}
}
/*///////////////////////////////////////////

  �������

/*///////////////////////////////////////////

//ø�s
void gameRole::Draw()
{
	int x , y ;

	//�p��U�@��
	m_GridTime -= di_DDD._time ;
	while( m_GridTime < 0 )
	{
		m_GridTime += m_GridNextTime ;
		m_Index ++ ;
		if( m_Index >= m_Cartoon->getNum())
			m_Index = 0 ;
	}
	//�e�v�l
	x = (int)m_x - gm_Da.mScreenX ;
	y = (int)m_y - gm_Da.mScreenY ;
	d3d_Device->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_ZERO );
	d3d_Device->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCCOLOR );
//	d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_MODULATE );
	if( m_Alpha )
		app_Shadow.BltFast( x - 32 , y - 32 , x + 32 , y + 24 , D3DCOLOR_ARGB( m_Alpha , m_Alpha , m_Alpha , m_Alpha ));
	else
		app_Shadow.BltFast( x - 32 , y - 32 , x + 32 , y + 24 , -1 );
	//�[�J�ƧǦ�C
	x = x - m_Cartoon->m_Ox ;
	y = y - m_Cartoon->m_Oy - (int)m_top ;
	if(( x >= 640 )||( y >= 480 ))
		return ;
	if((( x + m_Cartoon->getWidth() ) < 0 )||(( y + m_Cartoon->getHeight()) < 0 ))
		return ;
	AddSort();
}

//�]�w��V�ΤU�@��ɶ�
void gameRole::SetCartoon( d3dCartoon * cartoon , int NextTime , int News )
{
	//�P�_�O�_���P��V
	if( News != -1 )
	if( m_News == News )return ;
	//��s��V���
	m_Cartoon = cartoon ;
	m_GridTime = m_GridNextTime = NextTime ;
	m_News = News ;
}
//�ƧǦ�Cø�s
void gameRole::SortDraw()
{
	int dx , dy ;
	d3dTexture *texture ;
	//�P�w�O�_���L����
	if( !m_Cartoon )return ;
	//�p��ø�s��m
	dx = (int)  m_x          - m_Cartoon->m_Ox - gm_Da.mScreenX  ;
	dy = (int)( m_y - m_top )- m_Cartoon->m_Oy - gm_Da.mScreenY ;
	//���o��ø�s����
	d3d_Device->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	d3d_Device->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
	d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_MODULATE );
	if( texture = m_Cartoon->getTexture( m_Index ))
		if( m_Alpha )
			texture->BltFast( dx , dy , dx + texture->getWinth() , dy + texture->getHeight() , D3DCOLOR_ARGB( m_Alpha , 255 , 255 , 255 ));
		else
			texture->BltFast( dx , dy );
}

/*///////////////////////////////////////////

  �C����Ƹ��J

/*///////////////////////////////////////////
BOOL appLoadGameData()
{
	int i ;

	//���J�I��
	app_Back.Create2D( "m%2.2d_%2.2d.bmp" , 0 );
	//���J�v�l
	app_Shadow.Create( "�v�l02.bmp" , 0 );
	//���J�������~
	app_Prop[0].Create1D( "�Q��%2.2d.bmp" , 0 , D3DCOLOR_ARGB( 255 , 0 , 255 , 0 ));
	app_Prop[1].Create1D( "�c�]%2.2d.bmp" , 0 , D3DCOLOR_ARGB( 255 , 0 , 255 , 0 ));
	app_Prop[2].Create1D( "�]��%2.2d.bmp" , 0 , D3DCOLOR_ARGB( 255 , 0 , 255 , 0 ));
	//�]�w�������~����I
	for( i = 0 ; i < 3 ; i++ )
	{ 
		app_Prop[i].m_Ox = 70 ;
		app_Prop[i].m_Oy = 100 ;
	}
	//���J����
	app_Role[0].Create1D( "�ڧN_01_%2.2d.bmp" , 0 , D3DCOLOR_ARGB( 255 , 0 , 255 , 0 ));
	app_Role[1].Create1D( "�ڧN_03_%2.2d.bmp" , 0 , D3DCOLOR_ARGB( 255 , 0 , 255 , 0 ) );
	app_Role[2].Create1D( "�ڧN_05_%2.2d.bmp" , 0 , D3DCOLOR_ARGB( 255 , 0 , 255 , 0 ) );
	app_Role[3].Create1D( "�ڧN_07_%2.2d.bmp" , 0 , D3DCOLOR_ARGB( 255 , 0 , 255 , 0 ) );
	//�]�w��������I
	for( i = 0 ; i < 4 ; i++ )
	{ 
		app_Role[i].m_Ox = 70 ;
		app_Role[i].m_Oy = 100 ;
	}
	//��l�Ĥ@�ӫ���
	app_GamePlay.SetCartoon( app_Role , 100 , 1 );
	app_GamePlay.m_x = 320.0f ;
	app_GamePlay.m_y = 240.0f ;
	//��L�]�w		
	d3d_Device->SetSamplerState( 0 , D3DSAMP_MAGFILTER , D3DTEXF_POINT );
	d3d_Device->SetSamplerState( 0 , D3DSAMP_MINFILTER , D3DTEXF_POINT );
	d3d_Device->SetRenderState( D3DRS_ZENABLE , false );
	return true ;
}
/*///////////////////////////////////////////



  �M�_�D���e



/*///////////////////////////////////////////
appTreasure app_Treasure ;
void appTreasureRun()
{
	app_Proc = &app_Treasure ;
}


void appTreasure::Run()
{
	//�[�J���~
	AddObj();
	//��������
	Move();
	//���~���o
	GetProp();
	//ø�s
	Render();
	//����
	d3d_Device->Present( NULL , NULL , NULL , NULL );
}

void appTreasure::Render()
{
	d3dTexture d3dRt ;
	//�M��
	d3dClear();
	//�ƧǦ�C�M��
	appSortInit();
	//ø�s
	d3d_Device->BeginScene();
		d3d_Device->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
		d3d_Device->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
		d3d_Device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_SELECTARG2 );
		//�e�I��
		app_Back.Draw2D( gm_Da.mScreenX , gm_Da.mScreenY , 640 , 480 );
		//�e��T��
		d3dRt.BltFast( 15 , 15 , 200 , 125 , 0x8F000000 );
		//�e�����v�l�A�å[�J�ƧǦ�C
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_SELECTARG1 );
		app_GamePlay.Draw();
		//�e�������~
		DrawProp();
		//�e�ƧǦ�C
		appSortDraw();
	d3d_Device->EndScene();
	//����T��r
	DrawText();

}

void appTreasure::DrawText()
{
	d3dHdc hdc ;
	int j ;
	char ch[256] ;
	SetBkMode( hdc , 1 );
	SetTextColor( hdc , RGB( 255 , 255 , 255 ));
	//�Ѿl�ɶ�
	j = wsprintf( ch , "�ɶ��G%2.2d:%3.3d" , gm_Da.sTimeGame / 1000 , gm_Da.sTimeGame % 1000 );
	TextOut( hdc , 20 , 20 , ch , j );
	//�ثe����
	j = wsprintf( ch , "���ơG%d" , gm_Da.sScore );
	TextOut( hdc , 20 , 40 , ch , j );
	//���o���~
	j = wsprintf( ch , "�ƶq�G%d" , gm_Da.sNum );
	TextOut( hdc , 20 , 60 , ch , j );
	//�O�q��
	strcpy( ch , "�O�q" );
	for( j = 0 ; j < gm_Da.sPowerNum ; j++ )
		strcat( ch , "��" );
	TextOut( hdc , 20 , 80 , ch , strlen( ch ) );
	//�s��
	if( gm_Da.sTimeGet > 0 )
	{
		j = wsprintf( ch , "�s���G%2.2d:%3.3d" , gm_Da.sTimeGet / 1000 , gm_Da.sTimeGet % 1000 );
		TextOut( hdc , 20 , 100 , ch , j );
	}
}

void appTreasure::Move()
{
	float speed ;

	//�C���ɶ��g�L
	gm_Da.sTimeGame -= di_DDD._time ;
	gm_Da.sTimeGet  -= di_DDD._time ;
	gm_Da.sTimePower -= di_DDD._time ;
	//�P�w�C���O�_����
	if( gm_Da.sTimeGame <= 0 )
	{
		appTreasureGameoverRun();
		return ;
	}
	//�ϥΥ[�t
	if( di_DDD.Bn[0] )
	if( gm_Da.sTimePower <= 0 )
	if( gm_Da.sPowerNum > 0 )
	{
		gm_Da.sPowerNum -- ;
		gm_Da.sTimePower = 5000 ;
	}
	//�������ʳt��
	if( gm_Da.sTimePower > 0 )
		speed = ((float)di_DDD._time )* 0.40f ;
	else
		speed = ((float)di_DDD._time )* 0.20f ;
	//�������ʤ�V
	switch( di_DDD.News4ing )
	{
	case 1 ://�U
		app_GamePlay.m_y += speed ; 
		app_GamePlay.SetCartoon( &app_Role[0] , 100 , 1 );
		break ;
	case 5 ://�W
		app_GamePlay.m_y -= speed ; 
		app_GamePlay.SetCartoon( &app_Role[2] , 100 , 5 );
		break ;
	case 3 ://�k
		app_GamePlay.m_x += speed ; 
		app_GamePlay.SetCartoon( &app_Role[1] , 100 , 3 );
		break ;
	case 7 ://��
		app_GamePlay.m_x -= speed ; 
		app_GamePlay.SetCartoon( &app_Role[3] , 100 , 7 );
		break ;
	}
	//���ʭץ�
	if( app_GamePlay.m_x < 0 )
		app_GamePlay.m_x = 0 ;
	else if( app_GamePlay.m_x > app_Back.getWidth() )
		 app_GamePlay.m_x = (float)app_Back.getWidth() ;
	if( app_GamePlay.m_y < 0 )
		app_GamePlay.m_y = 0 ;
	else if( app_GamePlay.m_y > app_Back.getHeight() )
		 app_GamePlay.m_y = (float)app_Back.getHeight() ;
	//���b�ץ�
	gm_Da.mScreenX = (int)app_GamePlay.m_x - 320 ;
	gm_Da.mScreenY = (int)app_GamePlay.m_y - 240 ;
	if( gm_Da.mScreenX < 0 )
		gm_Da.mScreenX = 0 ;
	else if( gm_Da.mScreenX > gm_Da.mWidth )
		 gm_Da.mScreenX = gm_Da.mWidth ;
	if( gm_Da.mScreenY < 0 )
		gm_Da.mScreenY = 0 ;
	else if( gm_Da.mScreenY > gm_Da.mHeight )
		 gm_Da.mScreenY = gm_Da.mHeight ;

}

void appTreasure::AddObj()
{
	int i ;
	//�����p�ɾ�
	gm_Da.rTimeDown -= di_DDD._time ;
	if( gm_Da.rTimeDown > 0 )return ;
	gm_Da.rTimeDown += 1000 ;
	//�N�����[�J����
	for( i = 0 ; i < 32 ; i++ )
		if( !app_GameProp[i].m_Cartoon )
		{
			app_GameProp[i].SetCartoon( &app_Prop[rand()%3] , 100 , -1 );
			app_GameProp[i].m_x = (float)( rand()% ( app_Back.getWidth()  - 200 ) + 100 );
			app_GameProp[i].m_y = (float)( rand()% ( app_Back.getHeight() - 200 ) + 100 );
			app_GameProp[i].m_top = 480.0f ;
			app_GameProp[i].m_Alpha = 0 ;
			return ;
		}
}

void appTreasure::DrawProp()
{
	int i ;
	float speed = ((float)di_DDD._time )* 0.30f ;
	for( i = 0 ; i < 32 ; i++ )
		if( app_GameProp[i].m_Cartoon )
		{
			if( app_GameProp[i].m_top > speed )
				app_GameProp[i].m_top -= speed ;
			else app_GameProp[i].m_top = 0.0f ;
			app_GameProp[i].Draw();
		}
}

void appTreasure::GetProp()
{
	int i ;
	int x , y ;
	int Score ;
	float len ;

	for( i = 0 ; i < 32 ; i++ )
		if( app_GameProp[i].m_Cartoon )
		if( app_GameProp[i].m_top <= 0.0f )
		if( app_GameProp[i].m_Alpha )
		{
			app_GameProp[i].m_Alpha -= di_DDD._time ;
			if( app_GameProp[i].m_Alpha <= 0 )
				app_GameProp[i].m_Cartoon = NULL ;
		}else
		{
			//����̯x��
			x = abs((int)( app_GamePlay.m_x - app_GameProp[i].m_x ));
			y = abs((int)( app_GamePlay.m_y - app_GameProp[i].m_y ));
			len = sqrtf((float)( x * x + y * y ));
			if( len < 32.0f )
			{
				//�z���ȯ���
				app_GameProp[i].m_Alpha = 255 ;
				//�����
				if( gm_Da.sTimeGet > 0 )
					Score = gm_Da.sTimeGet / 500 + 1 ;
				else Score = 1 ;
				gm_Da.sScore += ( Score * Score * 100 ) ;
				gm_Da.sNum ++ ;
				gm_Da.sTimeGet = 2000 ;

			}

		}

}

/*///////////////////////////////////////////

  �ǳƶ}�l

/*///////////////////////////////////////////
appTreasureStart app_TreasureStart ;
void appTreasureStartRun()
{
	app_Proc = &app_TreasureStart ;
	app_Title.Create( "������.tga" , 0 );
}

void appTreasureStart::Run()
{
	int i ;
	//�}�l����
	if( di_DDD.Bn[0] )
	{
		//��l�Ĥ@�ӫ���
		app_GamePlay.SetCartoon( app_Role , 100 , 1 );
		app_GamePlay.m_x = 320.0f ;
		app_GamePlay.m_y = 240.0f ;
		//�C����ƪ�l��
		memset( &gm_Da , 0 , sizeof( gm_Da ));
		gm_Da.sTimeGame = 60000 ;//�C���ɶ�
		gm_Da.sPowerNum = 3 ;//�O�q
		//�����i���ʽd��
		gm_Da.mWidth = app_Back.getWidth() - 640 ;
		gm_Da.mHeight = app_Back.getHeight()-480 ;
		//�N�ثe���~�M��
		for( i = 0 ; i < 32 ; i++ )
			app_GameProp[i].m_Cartoon = NULL ;
		//�C���}�l
		appTreasureRun();
		return ;
	}
	//ø�s
	Render();
}


void appTreasureStart::Render()
{
	d3dTexture text ;
	//ø�s
	app_Treasure.Render();
	//�e���D
	d3d_Device->BeginScene();
		//���t����
		text.BltFast( 0 , 0 , 640 , 480 , 0x80000000 );
		//�e���D
		app_Title.BltFast( 0 , 0 );
	d3d_Device->EndScene();
	//����
	d3d_Device->Present( NULL , NULL , NULL , NULL );
}

/*///////////////////////////////////////////

  �C������

/*///////////////////////////////////////////
appTreasureGameover app_TreasureGameover ;
void appTreasureGameoverRun()
{
	app_Proc = &app_TreasureGameover ;
	//���J���D
	app_Title.Create( "gameover.tga" , 0 );
	//�ɶ��W�s
	gm_Da.sTimeGet = gm_Da.sTimeGame = 0 ;
}

void appTreasureGameover::Run()
{
	//�}�l����
	if( di_DDD.Bn[0] )
	{
		//�^�C���D�e��
		appTreasureStartRun();
		return ;
	}
	//ø�s
	Render();
}

void appTreasureGameover::Render()
{
	d3dTexture text ;
	//ø�s����
	app_Treasure.Render();
	//�e��L���~
	d3d_Device->BeginScene();
		//���t����
		text.BltFast( 0 , 0 , 640 , 480 , 0x80000000 );
		//�e���D
		app_Title.BltFast( 0 , 0 );
	d3d_Device->EndScene();
	//����
	d3d_Device->Present( NULL , NULL , NULL , NULL );
}