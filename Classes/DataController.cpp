#include "DataController.h"
#include "cocos2d.h"
#include "sqlite3/include/sqlite3.h"
USING_NS_CC;


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
		ttf->setString( str.c_str());    //将字符串的标题设为str
	} 
	else
	{
		//没有数据
		CCUserDefault::sharedUserDefault()->setStringForKey( "str", "now, hava data");   //写入字符串
		CCUserDefault::sharedUserDefault()->setBoolForKey( "flag", true);        //写入bool
		CCUserDefault::sharedUserDefault()->flush();     //将数据存入xml里面, 不过现在貌似可以不加也可以
	}
}

void DataController::TestSQLCreation()
{

	//创建表，设置ID为主键，且自动增加  
	result=sqlite3_exec( pDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) ) " , NULL, NULL, &errMsg );  
	if( result != SQLITE_OK )  
		CCLog( "创建表失败，错误码:%d ，错误原因:%s\n" , result, errMsg );  

	//插入数据  
	sqlstr=" insert into MyTable_1( name ) values ( '克塞' ) ";  
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
	} else {  
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));  
		sqlite3_close(db);  
		return 1;  
	}  

}
