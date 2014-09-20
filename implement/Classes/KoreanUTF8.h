#ifndef __KOREAN_UTF8_H__
#define __KOREAN_UTF8_H__

#include "cocos2d.h"

USING_NS_CC;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

static const std::string UTF8(const std::string& string)
{
    int bufflen = MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, NULL, 0);
    WCHAR* widebuff = new WCHAR[bufflen + 1];
    memset(widebuff, 0, sizeof(WCHAR)* (bufflen + 1));
    MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, widebuff, bufflen);

    bufflen = WideCharToMultiByte(CP_UTF8, 0, widebuff, -1, NULL, 0, NULL, NULL);
    char* buff = new char[bufflen + 1];
    memset(buff, 0, sizeof(char)* (bufflen + 1));
    WideCharToMultiByte(CP_UTF8, 0, widebuff, -1, buff, bufflen, NULL, NULL);

    std::string strResult(buff);

    delete[] widebuff;
    delete[] buff;

    return strResult;
}

#define UTF8PCHAR(string)    UTF8(string).c_str()

#else

#define UTF8(string)    string
#define UTF8PCHAR(string)    string

#endif

#endif // __KOREAN_UTF8_H__

/*
작업2. 한글을 입력하는 cpp 파일에서 해당 헤더파일 include
#include "KoreanUTF8.h"
 
작업3. 한글 입력 시 UTF8() 또는 UTF8PCHAR() 로 감싸기
ex) auto label = LabelTTF::create(UTF8("Hello 홍길동"), "Arial", 24);
ex) log(UTF8PCHAR("테스트 한글 로그 출력"));
*/