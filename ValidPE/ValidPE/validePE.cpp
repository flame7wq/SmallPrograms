//#include <afxwin.h>
#include <afxdlgs.h>
#define IMAGE_DOS_SIGNATURE		0x5A4D		// MZ
#define IMAGE_NT_SIGNATURE		0x004550	// PE00

class CMyApp :public CWinApp
{
	virtual BOOL InitInstance();
};

CMyApp theApp;
IMAGE_DOS_HEADER dosHeader;
IMAGE_NT_HEADERS32 ntHeader32;

BOOL CMyApp::InitInstance()
{
	CFileDialog dlg(TRUE);   //Constructors TRUE for FileOpen, FALSE for FileSaveAs
	//m_pMainWnd = &dlg;
	if (dlg.DoModal() != IDOK)
		return FALSE;

	BOOL bValid = FALSE;
	HANDLE hFile = CreateFile(dlg.GetPathName(), GENERIC_READ, 
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		MessageBox(NULL, "Invalid File £¡", "ValidPE", MB_OK);

	if (ReadFile(hFile, &dosHeader, sizeof(dosHeader), NULL, NULL))
		if (dosHeader.e_magic == IMAGE_DOS_SIGNATURE)
			if (SetFilePointer(hFile, dosHeader.e_lfanew, NULL, FILE_BEGIN))
				if (ReadFile(hFile, &ntHeader32, sizeof(ntHeader32), NULL, NULL))
					if (ntHeader32.Signature == IMAGE_NT_SIGNATURE)
						bValid = TRUE;

	if (bValid)
		MessageBox(NULL, "It's a valid PE file!", "ValidPE", MB_OK);
	else
		MessageBox(NULL, "It's an invalid PE file!", "ValidPE", MB_OK);
	return bValid;
}
