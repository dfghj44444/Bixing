#include "DataController.h"
#include "cocos2d.h"
#include "sqlite3/include/sqlite3.h"
USING_NS_CC;

int callback(void* ,int nCount,char** pValue,char** pName)
{
	string s;
	for(int i=0;i<nCount;i++)
	{
		s+=pName[i];
		s+=":";
		s+=pValue[i];
		s+="\n";
	}
	cout<<s<<endl;
	return 0;
}

DataController::DataController(void)
{
}


DataController::~DataController(void)
{
}

void DataController::Test()
{	 
	sqlite3* pDB;
	std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("test.db");  

	auto result = sqlite3_open(filename.c_str(), &pDB);  
	CCLog(filename.c_str());  
	if( result != SQLITE_OK )  
		CCLog( "打开数据库失败，错误码:%d \n" , result, );  
	else  
		CCLog("成功地打开了数据库");   
}

void DataController::TestDefault()
{
	if ( CCUserDefault::sharedUserDefault()->getBoolForKey( "flag", false))
	{
		//有数据
		std::string str = CCUserDefault::sharedUserDefault()->getStringForKey( "str", "null");   //取出string	
		CCLog("存储文件已存在");
	} 
	else
	{
		//没有数据
		CCUserDefault::sharedUserDefault()->setStringForKey( "str", "now, hava data");   //写入字符串
		CCUserDefault::sharedUserDefault()->setBoolForKey( "flag", true);        //写入bool
		CCUserDefault::sharedUserDefault()->flush();     //将数据存入xml里面, 不过现在貌似可以不加也可以
		CCLog("存储文件不存在,头次开始加载游戏");
	}
}

void DataController::TestSQLCreation()
{
	char errMsg = "Unknown";
	sqlite3* pDB;
	std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("test.db");  
	auto result = sqlite3_open(filename.c_str(), &pDB); 
	//创建表，设置ID为主键，且自动增加  
	auto result=sqlite3_exec( pDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) ) " , NULL, NULL, &errMsg );  
	if( result != SQLITE_OK )  
		CCLog( "创建表失败，错误码:%d ，错误原因:%s\n" , result, errMsg );  

	//插入数据
	std::string sqlstr=" insert into MyTable_1( name ) values ( '克塞' ) ";  
	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );  
	if(result != SQLITE_OK )  
		CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );  

	//插入数据  
	sqlstr=" insert into MyTable_1( name ) values ( '葫芦娃' ) ";  
	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );  
	if(result != SQLITE_OK )  
		CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );  

	//插入数据  
	sqlstr=" insert into MyTable_1( name ) values ( '擎天柱' ) ";  
	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );   
	if(result != SQLITE_OK )   
		CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg ); 
}

void DataController::TestSQLQuery()
{
	sqlite3* db=nullptr;
	char *zErrMsg = nullptr;
	int rc;
	//查询
	rc = sqlite3_open("test.db3", &db);  
	if (rc == SQLITE_OK)  
	{  
		rc = sqlite3_exec(db,  
			"CREATE TABLE test (id INTEGER NOT NULL, text VARCHAR(100))"  
			, callback, 0, &zErrMsg);  
		if (rc != SQLITE_OK) fprintf(stderr, "SQL error: %s\n", zErrMsg);  
		rc = sqlite3_exec(db,  
			"INSERT INTO test VALUES (1, 'text1')"  
			, callback, 0, &zErrMsg);  
		if (rc != SQLITE_OK) fprintf(stderr, "SQL error: %s\n", zErrMsg);  
		rc = sqlite3_exec(db,  
			"SELECT * FROM test"  
			, callback, 0, &zErrMsg);  
		if (rc != SQLITE_OK) fprintf(stderr, "SQL error: %s\n", zErrMsg);  
		sqlite3_close(db);  
	}
	else
	{  
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);  
	}  
}


void Data::TestFile(){
	//获取FileUtiles对象
	FileUtils *fileUtile=FileUtils::getInstance();
	//显示showView.png图片的全路径
	std::string path=fileUtile->fullPathForFilename("showView.png");
	//进入Documents目录下
	std::string pathToSave=fileUtile->getWritablePath();
	//添加到finder文件夹
	pathToSave +="finder";
	CCLOG("pathToSave=%s",pathToSave.c_str());

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *pDir = NULL;
	//打开该路径
	pDir = opendir (pathToSave.c_str());
	if (! pDir)
	{
		//创建该路径
		mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}
#else
	if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(pathToSave.c_str(), 0);
	}
#endif
}