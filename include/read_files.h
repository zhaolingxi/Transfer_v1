#pragma once


#ifdef READFILE_EXPORT
#define READFILES __declspec(dllexport)
#else
#define READFILES __declspec(dllimport)
#endif

#include<string>
typedef bool (*FileStdCall)(const char* _FilePath);//_对文件的回调函数指针类型
typedef bool (*DirStdCall)(const char* _Directory);//_对文件夹的回调函数指针类型


class file_action
{
	virtual void ergodicDirAndFile(char* _BeginPath = nullptr,
		DirStdCall _DirCall = nullptr,
		FileStdCall _FileCall = nullptr,
		bool _ifOnlyFirstDeep = false) {};
};

#ifdef __cplusplus
extern"C" {
#endif
	READFILES bool findAllFilesOnCurFolder(char* path, int& file_num);

	READFILES void dfsListFolderFiles(char* path);

	READFILES char* getCurrentDir();

	READFILES int copyFile(const char* source_file, const char* dest_file);

	READFILES std::string generateUUIDWithoutDelim();

	READFILES bool encrypFileEasy(const char* source_file, const char* dest_file,bool encode=true,bool del_origin_file=false);

	class read_files :public file_action
	{
	public:
		void ergodicDirAndFile(char* _BeginPath = nullptr,
			DirStdCall _DirCall = nullptr,
			FileStdCall _FileCall = nullptr,
			bool _ifOnlyFirstDeep = false);
	};

	READFILES read_files* getInstance();

#ifdef __cplusplus
}
#endif

