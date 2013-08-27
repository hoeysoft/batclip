#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

static const int kCmdBufSize = 1024;

HWND GetConsoleHwnd();

void CheckError(BOOL error_condition, const char* msg) {
  if (error_condition) {
    fprintf(stderr, "%s\n", msg);
    system("pause");
    exit(1);
  }   
}

int main(int argc, char* argv[]) {
  CheckError(argc != 2, "Pass batchfile that reads clipboard.");

  HWND hwnd = GetConsoleHwnd();
  CheckError(hwnd == NULL, "Pass batchfile that reads clipboard.");

  BOOL is_opened = OpenClipboard(hwnd);
  CheckError(is_opened == FALSE, "Can not open clipboard.\n");

  HGLOBAL hmem = GetClipboardData(CF_TEXT);
  CheckError(hmem == NULL, "Keep text in clipboard.");

  TCHAR *cliptext = (TCHAR*)GlobalLock(hmem);
  CheckError(cliptext == NULL, "Can not lock clipboard.");
  
  // Make console command;
  char cmd[kCmdBufSize];
  int ret = sprintf(cmd, "cmd /c \"%s\" %s", argv[1], cliptext);
  CheckError(ret < 0, "Text is Too long");

  // Run!!!
  system(cmd);

  GlobalUnlock(hmem);
  CloseClipboard();
  
  return 0;
}

