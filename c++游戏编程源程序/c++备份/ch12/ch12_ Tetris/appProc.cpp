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



  ����D���e



/*///////////////////////////////////////////
static const POINT app_TetrisBox[7][4] = 
{
	/*0
		��������
	*/{ { 0 , 1 }, { 1 , 1 } , { 2 , 1 } , { 3 , 1 } },
	/*1
		����
		  ����
	*/{ { 0 , 1 }, { 1 , 1 } , { 2 , 1 } , { 2 , 2 } },
	/*2
		  ����
		����
	*/{ { 0 , 2 }, { 1 , 2 } , { 1 , 1 } , { 2 , 1 } },
	/*3
		������
		    ��
	*/{ { 0 , 1 } ,{ 1 , 1 } , { 2 , 1 } , { 2 , 2 } },
	/*4
	        ��
		������
	*/{ { 0 , 2 } ,{ 1 , 2 } , { 2 , 2 } , { 2 , 1 } },
	/*5
		  ����
		  ����
	*/{ { 1 , 1 }, { 2 , 1 } , { 2 , 2 } , { 1 , 2 } },
	/*6
		  ��
		������
	*/{ { 2 , 1 }, { 1 , 2 } , { 2 , 2 } , { 3 , 2 } },

};


/*///////////////////////////////////////////

  �C����Ƶ��c

/*///////////////////////////////////////////
typedef struct _TETRIS_DATA
{
	BYTE  Data[10][20] ;//�����
	POINT NowBox[4] ;//�ثe���
	POINT NowPoint ;
	int   BoxNextIndex ;//�U�@�Ӥ��
	int   BoxNowIndex  ;//�ثe���

	int   TimeNextGrid ;
	int   TimeGridNow  ;

	int		sLV ;//���d
	int		sNLV ;//�U�@���n�������
	int		sScore ;//�o��
	int		sDel ;//�w�����
}TETRIS_DATA ;
TETRIS_DATA ts_DA ;

//�I��
d3dTexture ts_Back ;
//���
d3dTexture ts_Box[7] ;
//���D
d3dTexture ts_Title ;

/*///////////////////////////////////////////

  �C���i�椤

/*///////////////////////////////////////////

Tetris app_Tetris ;

void appTetrisRun()
{
	app_Proc = &app_Tetris ;
	//�w��l���
	ts_DA.sLV = 1 ;
	ts_DA.sNLV = 6 ;
//	app_Tetris.Updata();
}

//
//
//��l��
void Tetris::Updata()
{
	int i ;
	char ch[256] ;
	//�}�l
	memset( &ts_DA , 0 , sizeof( ts_DA ));
	//���J�I��
	ts_Back.Create( "�I��.tga" );
	//�s�J���
	for( i = 0 ; i < 7 ; i++ )
	{
		wsprintf( ch , "���%2.2d.bmp" , i );
		ts_Box[i].Create( ch );
	}
	//�Ĥ@�Ӥ�� 
	ts_DA.BoxNextIndex = rand()%7 ;
	GetBox();
	//�ɶ�
	ts_DA.TimeNextGrid = 560 ;
	//ø�s�Ҧ�
	d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAARG1 , D3DTA_TEXTURE );
	d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAARG2 , D3DTA_DIFFUSE );
	d3d_Device->SetTextureStageState( 0 , D3DTSS_COLORARG1 , D3DTA_TEXTURE );
	d3d_Device->SetTextureStageState( 0 , D3DTSS_COLORARG2 , D3DTA_DIFFUSE );

}

//
//
//�j��
void Tetris::Run()
{
	//���U
	BoxDown();
	//�첾
	Move();
	//����
	Rotation();
	//ø�s
	Render();
}
//
//
//ø�s
void Tetris::Render()
{
	//�e����
	RenderBack();
	//����
	d3d_Device->Present( NULL , NULL , NULL , NULL );
}

void Tetris::RenderBack()
{
	d3dTexture d3dRt ;
	//�M��
	d3dClear();
	//�}�lø�s
	d3d_Device->BeginScene();
		d3d_Device->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
		d3d_Device->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
		d3d_Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_SELECTARG2 );
		//�e�I��
		ts_Back.BltFast( 0 , 0 );
		//�e����
		d3dRt.BltFast( 220 , 40 , 420 , 440 , 0x8FFFFFFF );
		//��r��
		d3dRt.BltFast( 100 , 100 , 200 , 200 , 0X8F000000 );
		//�U�Ӥ����
		d3dRt.BltFast( 440 , 60 , 560 , 180 ,  0x4F000000 );
		//�e���
		DrawNowBox();

	d3d_Device->EndScene();

	//ø�s��r
	DrawText();

}
//�e��r
void Tetris::DrawText()
{
	int len ;
	char ch[256] ;

	//��r
	d3dHdc hdc ;
	SetBkMode( hdc , 1 );
	SetTextColor( hdc , RGB( 255 , 255 , 255 ));
	//�ثe����
	len = wsprintf( ch , "���ơG%d" , ts_DA.sScore );
	TextOut( hdc , 110 , 105 , ch , len );
	//�w�����
	len = wsprintf( ch , "��ơG%d" , ts_DA.sDel );
	TextOut( hdc , 110 , 125 , ch , len );
	//���d
	len = wsprintf( ch , "���d�G%d" , ts_DA.sLV );
	TextOut( hdc , 110 , 145 , ch , len );
}

//�e���
void Tetris::DrawBox(int gx, int gy , int index )
{
	int x , y ;

	if(( index >= 0 )&&( index < 7 ))
	{
		x = gx * 20 + 220 ;
		y = gy * 20 +  40 ;

		ts_Box[index].BltFast( x , y  );
	}
}

void Tetris::GetBox()
{
	int i ;
	//�w�������I��l��m
	ts_DA.NowPoint.x = 3 ;
	ts_DA.NowPoint.y = -3 ;
	//�w�|�Ӥ����m
	ts_DA.BoxNowIndex = ts_DA.BoxNextIndex ;
	for( i = 0 ; i < 4 ; i++ )
	{
		ts_DA.NowBox[i].x = app_TetrisBox[ ts_DA.BoxNowIndex ][i].x ;
		ts_DA.NowBox[i].y = app_TetrisBox[ ts_DA.BoxNowIndex ][i].y ;
	}
	//�U�@�Ӥ��
	ts_DA.BoxNextIndex = rand()%7;
	//�ɶ���l��
	ts_DA.TimeGridNow = ts_DA.TimeNextGrid ;
}

void Tetris::DrawNowBox()
{
	int i , j ;
	int gx , gy ;
	BYTE index ;
	//�e���ؤ��
	for( i = 0 ; i < 10 ; i++ )
	for( j = 0 ; j < 20 ; j++ )
		if( index = ts_DA.Data[i][j] )
			DrawBox( i , j , index - 1 );
	//�e�ثe���
	for( i = 0 ; i < 4 ; i++ )
	{
		gx = ts_DA.NowBox[i].x + ts_DA.NowPoint.x ;
		gy = ts_DA.NowBox[i].y + ts_DA.NowPoint.y ;
		if( IsInRect( gx , gy ))
			DrawBox(  gx , gy , ts_DA.BoxNowIndex );
	}
	//�e�U�@�Ӥ��
	for( i = 0 ; i < 4 ; i++ )
		DrawBox(  app_TetrisBox[ts_DA.BoxNextIndex][i].x + 12 , app_TetrisBox[ts_DA.BoxNextIndex][i].y + 2 , ts_DA.BoxNextIndex );

}

void Tetris::BoxDown()
{
	int i ;
	int gx , gy ;
	//���U�ɶ�
	if( di_DDD.News4ing == 1 )
		ts_DA.TimeGridNow -= ( di_DDD._time * 5 );
	else
		ts_DA.TimeGridNow -= ( di_DDD._time  );
	//���U���\
	while( ts_DA.TimeGridNow < 0 )
	{
		ts_DA.TimeGridNow += ts_DA.TimeNextGrid ;
		if( IsDown( ts_DA.NowPoint.x , ts_DA.NowPoint.y + 1 ))
			ts_DA.NowPoint.y ++ ;
		else
		{
			//���U�Ӫ�����Y���i�J��l���A�N��C������
			for( i = 0 ; i < 4 ; i++ )
				if( !IsInRect( ts_DA.NowBox[i].x + ts_DA.NowPoint.x , ts_DA.NowBox[i].y + ts_DA.NowPoint.y ))
				{
					appTetrisGameOverRun();
					return ;
				}

			//��ƨ��w�İ�
			for( i = 0 ; i < 4 ; i++ )
			{
				gx = ts_DA.NowBox[i].x + ts_DA.NowPoint.x ;
				gy = ts_DA.NowBox[i].y + ts_DA.NowPoint.y ;
				ts_DA.Data[gx][gy] = ts_DA.BoxNowIndex + 1 ;
			}
			//�P�_�O�_�i����
			ListDelIs();
			//���U�@�Ӥ��
			GetBox();
			//����
			return ;
		}
	}
}

BOOL Tetris::IsDown( int nx , int ny )
{
	int i ;
	int gx , gy ;
	//
	for( i = 0 ; i < 4 ; i++ )
	{
		gx = ts_DA.NowBox[i].x + nx ;
		gy = ts_DA.NowBox[i].y + ny ;
		//�O�_�쩳
		if( gy >= 20 )
			return false ;
		//�O�_�b��l��
		if( gy >= 0 )
		if( !IsInRect( gx , gy ))
			return false ;
		//�U���O�_�����
		else if( ts_DA.Data[gx][gy] )
			return false ;
	}
	//
	return true ;

}

BOOL Tetris::IsInRect(int gx, int gy)
{
	if(( gx >= 0 )&&( gx < 10 ))
		if(( gy >= 0 )&&( gy < 20 ))
			return true ;
	return false ;

}
//����
void Tetris::Move()
{
	if( di_DDD.News4 == 3 )//��
	{
		if( IsDown( ts_DA.NowPoint.x + 1 , ts_DA.NowPoint.y ))
			ts_DA.NowPoint.x ++ ;
	}else if( di_DDD.News4 == 7 )//��
	{
		if( IsDown( ts_DA.NowPoint.x - 1 , ts_DA.NowPoint.y ))
			ts_DA.NowPoint.x -- ;
	}

}

//����
void Tetris::Rotation()
{
	//�ഫ�x�}
	static const POINT ro[4][4] = 
	{
		{{ 3 , 0 } , { 2 , 0 } , { 1 , 0 } , { 0 , 0 }},
		{{ 3 , 1 } , { 2 , 1 } , { 1 , 1 } , { 0 , 1 }},
		{{ 3 , 2 } , { 2 , 2 } , { 1 , 2 } , { 0 , 2 }},
		{{ 3 , 3 } , { 2 , 3 } , { 1 , 3 } , { 0 , 3 }},
	};

	int i ;
	int gx , gy ;
	POINT po[4] ;
	//�p�G�S���U�Ĥ@��A�N��n������
	if( !di_DDD.Bn[0] )
		return ;
	//���ഫ���m
	for( i = 0 ; i < 4 ; i++ )
	{
		po[i].x = ro[ ts_DA.NowBox[i].x ][ ts_DA.NowBox[i].y].x ;
		po[i].y = ro[ ts_DA.NowBox[i].x ][ ts_DA.NowBox[i].y].y ;
		//�P�w�O�_�b�x�����A�p�G���b�x��������
		gx = po[i].x + ts_DA.NowPoint.x ;
		gy = po[i].y + ts_DA.NowPoint.y ;
		if( !IsInRect( gx , gy ))
			return ;
		//�P�w�O�_������A�p�G���������
		else if( ts_DA.Data[gx][gy] )
			return ;
	}
	//���ন�\�A�]�s�����
	memcpy( ts_DA.NowBox , po , sizeof( po ));

}

//�������
void Tetris::ListDelIs()
{
	//����
	static const int Score[] = 	{ 0 ,100 , 300 , 1000 , 4000 };

	int i , j , k , num ;
	int list[20] ;
	//�P�_��O�_���������
	num = 0 ;
	memset( list , 0 , sizeof( list ));
	for( j = 19 ; j >= 0 ; j-- )
		for( i = 0 ; i < 10 ; i++ )
			if( ts_DA.Data[i][j] )
				list[j] ++ ;
	//�P�_�񺡦�
	for( j = 0 ; j < 20 ; j++ )
		if( list[j] == 10 )
		{
			//���h�Ӧ�
			for( i = 0 ; i < 10 ; i++ )
				ts_DA.Data[i][j] = 0 ;
			//���h��[�@
			num ++ ;
		}

	if( num == 0 )
		return ;
	//������U
	for( i = j = 19 ;( j >= 0 ); j-- )
	{
		//���U
		for( ; i >= 0 ; i-- )
			if( list[i] != 10 )
			{
				//�p�G��̤��P��A�N�W���U
				if( i != j )
					for( k = 0 ; k < 10 ; k++ )
					{
						ts_DA.Data[k][j] = ts_DA.Data[k][i] ;
						ts_DA.Data[k][i] = 0 ;
					}
				//��ƤW��
				i-- ;
				break ;
			}
	}
	//�O������
	ts_DA.sScore += Score[num] ;
	ts_DA.sDel += num ;
	ts_DA.sNLV -= num ;
	if( ts_DA.sNLV <= 0 )
	{
		ts_DA.sNLV = 6 ;
		ts_DA.sLV ++ ;
		if( ts_DA.sLV < 10 )
			ts_DA.TimeNextGrid = 60 + ( 10 - ts_DA.sLV )* 50 ;
	}
}

/*///////////////////////////////////////////



  �ǳƶ}�l



/*///////////////////////////////////////////
TetrisIs app_TetrisIs ;
void appTetrisIsRun()
{
	app_Tetris.Updata();
	app_Proc = &app_TetrisIs ;
	ts_Title.Create( "�Xù�����.tga" );
}

void TetrisIs::Run()
{
	if( di_DDD.Bn[0] )
		appTetrisRun();

	Render();
}

void TetrisIs::Render()
{
	//�e�I��
	app_Tetris.RenderBack();
	//�e��r
	d3d_Device->BeginScene();
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_SELECTARG1 );
		ts_Title.BltFast( 0 , 0 );
	d3d_Device->EndScene();
	//����
	d3d_Device->Present( NULL , NULL , NULL , NULL );
}

/*///////////////////////////////////////////



  �C������



/*///////////////////////////////////////////
TetrisGameOver app_TSGameOver ;
void appTetrisGameOverRun()
{
	app_Proc = &app_TSGameOver ;
	ts_Title.Create( "gameover.tga" );
}

void TetrisGameOver::Run()
{
	if( di_DDD.Bn[0] )
		appTetrisIsRun();
	//ø�s
	Render();
}

void TetrisGameOver::Render()
{
	//�e�I��
	app_Tetris.RenderBack();
	//�e��r
	d3d_Device->BeginScene();
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_SELECTARG1 );
		ts_Title.BltFast( 0 , 0 );
	d3d_Device->EndScene();

	//����
	d3d_Device->Present( NULL , NULL , NULL , NULL );

}
