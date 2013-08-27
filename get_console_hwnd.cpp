#include <Windows.h>
static const int kTitleBufSize = 1024;

HWND GetConsoleHwnd() {

  HWND hwndFound;
  TCHAR pszNewWindowTitle[kTitleBufSize];
  TCHAR pszOldWindowTitle[kTitleBufSize];

  GetConsoleTitle(pszOldWindowTitle, kTitleBufSize);

  // Format a "unique" NewWindowTitle.
  wsprintf(pszNewWindowTitle,TEXT("%d/%d"),
              GetTickCount(),
              GetCurrentProcessId());

  SetConsoleTitle(pszNewWindowTitle);

  // Ensure window title has been updated.
  Sleep(40);

  hwndFound=FindWindow(NULL, pszNewWindowTitle);

  // Restore original window title.
  SetConsoleTitle(pszOldWindowTitle);

  return hwndFound;
}