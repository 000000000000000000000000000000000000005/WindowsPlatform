// 010����Dllʵ�ֻ�ͼ��_��ֱ��.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "010����Dllʵ�ֻ�ͼ��_��ֱ��.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App

BEGIN_MESSAGE_MAP(CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App, CWinApp)
END_MESSAGE_MAP()


// CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App ����

CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App::CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App ����

CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App theApp;


// CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App ��ʼ��

BOOL CMy010����Dllʵ�ֻ�ͼ��_��ֱ��App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
