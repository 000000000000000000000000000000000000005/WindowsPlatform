#include <windows.h>
#include <tchar.h>

#include <shlwapi.h>  
#pragma comment(lib,"shlwapi.lib")  


int main(int argc, char* argv[])
{
	//1.ȥ��·�����ķ�б�ܡ�\��
	TCHAR szFullPath[] = _T("C:\\Windows\\System32\\oobe\\zh-CN\\audit.exe.mui\\");
	PathRemoveBackslash(szFullPath);
	_tprintf(_T("PathRemoveBackslash %s\n"), szFullPath);

	//2.��·�������Ϸ�б�ܡ�\��
	PathAddBackslash(szFullPath);
	_tprintf(_T("PathAddBackslash %s\n"), szFullPath);
	PathRemoveBackslash(szFullPath); 

	//3. ɾ���ļ�����չ��
	PathRemoveExtension(szFullPath);
	_tprintf(_T("PathRemoveExtension %s\n"), szFullPath);

	//4. ���ļ�·�����������չ��
	PathAddExtension(szFullPath, _T("exe"));
	_tprintf(_T("PathAddExtension %s\n"), szFullPath);

	//5.�����ļ�·����չ��
	PathRenameExtension(szFullPath, _T(".mui"));
	_tprintf(_T("PathRenameExtension %s\n"), szFullPath);

	//6. ȥ���ļ������õ�Ŀ¼
	PathRemoveFileSpec(szFullPath);
	_tprintf(_T("PathRemoveFileSpec %s\n"), szFullPath);

	//7. ȥ��Ŀ¼�õ��ļ���
	TCHAR szFullPath2[] = _T("C:\\Windows\\System32\\oobe\\zh-CN\\audit.exe.mui");
	PathStripPath(szFullPath2);
	_tprintf(_T("PathStripPath %s\n"), szFullPath2);

	//8.ȥ��·�����ļ����֣��õ���Ŀ¼
	TCHAR szFullPath3[] = _T("C:\\Windows\\System32\\oobe\\zh-CN\\audit.exe.mui");
	PathStripToRoot(szFullPath3);
	_tprintf(_T("PathStripToRoot %s\n"), szFullPath3);

	//9. ��ȡ�ļ�����չ��
	TCHAR szFullPath4[] = _T("C:\\Windows\\System32\\oobe\\zh-CN\\audit.exe.mui");
	TCHAR* szExtension =PathFindExtension(szFullPath4);
	_tprintf(_T("PathFindExtension %s\n"), szExtension);

	return 0;
}