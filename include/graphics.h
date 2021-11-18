/*********************************************************
* EGE (Easy Graphics Engine)
* FileName      graphics.h
* HomePage1     http://misakamm.github.com/xege
* HomePage2     http://misakamm.bitbucket.org/index.htm
* teiba1        http://tieba.baidu.com/f?kw=ege
* teiba2        http://tieba.baidu.com/f?kw=ege%C4%EF
* Blog:         http://misakamm.com
* E-Mail:       mailto:misakamm[at gmail com]
*
* FileName: graphics.h
* �� VC ��ģ�� Borland BGI ��ͼ�⣬ʵ�ּ򵥵Ļ�ͼ֮�࣬��չ�˽ϸ��ӵĻ�ͼ����
*
* ������ʹ�ñ���ʱ����Ҫ����conio.hͷ�ļ�
* ��Щͷ�ļ���Ӧ���棬������ܻ�������
* ����getch��conio.h�ڵĸ��ǣ��ɰ����������������ע��
* ���蹲�棬��ʹ�ö��ļ��ֿ�������ģʽʹ�ã�
* ������һ��cppͬʱ�����������Էֿ�����
* ʹ�ñ��⣬������C++���룬��֧�ֵı�������
* VC6/VC2008/VC2010/VC2012/VC2013/MinGW3.4.5/MinGW4.7.1/MinGW4.8.1
*********************************************************/

/****************************************************************************
** ע�����
* �������Ҫ��ʾ����̨���ڣ����ڰ������ļ���ǰ���һ��define SHOW_CONSOLE
* �����Sleep���APIʱ�����ߵ���delay��ʵ�ʾ���ת��Ϊ����delay_ms����������API��ʹ��api_sleep
* ��delay_ms(0)�������ж���û�и��µı�Ҫ��������ε��������ĵ��ò��������֡�ʵ�Ӱ��
* �����delay_ms, delay_fps, getch, GetMouseMsg ʱ���������ݿ��ܻ���£���Щ�����൱��������delay_ms(0)��
*   �����ֻ��Ҫ���´��ڣ�������ȴ���������delay_ms(0),Sleep(0)����delay(0)
* �������ʹ��������ģʽ��ͼ���ǿ���ʹ��WindowFlush����delay(0)�������ܴ����0��delay
* �������ʹ��delay���������Լ�����ĳ���ռ�õ�CPU������һ��delay��û�е��õĻ�������ռ��һ��CPU��ʱ��
* ��setfillstyle�������Զ������ģʽδʵ�֣���һ��Ӧ���㹻
****************************************************************************/

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#ifndef __cplusplus
#error You must use C++ compiler, or you need filename with '.cpp' suffix
#endif

#include "ege.h"

//强制使用ege命令空间
// using namespace ege;

#endif
