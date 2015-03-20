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
		CCLog( "�����ݿ�ʧ�ܣ�������:%d \n" , result, );  
	else  
		CCLog("�ɹ��ش������ݿ�");   
}

void DataController::TestDefault()
{


	if ( CCUserDefault::sharedUserDefault()->getBoolForKey( "flag", false))
	{
		//������
		std::string str = CCUserDefault::sharedUserDefault()->getStringForKey( "str", "null");   //ȡ��string
		ttf->setString( str.c_str());    //���ַ����ı�����Ϊstr
	} 
	else
	{
		//û������
		CCUserDefault::sharedUserDefault()->setStringForKey( "str", "now, hava data");   //д���ַ���
		CCUserDefault::sharedUserDefault()->setBoolForKey( "flag", true);        //д��bool
		CCUserDefault::sharedUserDefault()->flush();     //�����ݴ���xml����, ��������ò�ƿ��Բ���Ҳ����
	}
}

void DataController::TestSQLCreation()
{

	//����������IDΪ���������Զ�����  
	result=sqlite3_exec( pDB, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) ) " , NULL, NULL, &errMsg );  
	if( result != SQLITE_OK )  
		CCLog( "������ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg );  

	//��������  
	sqlstr=" insert into MyTable_1( name ) values ( '����' ) ";  
	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );  
	if(result != SQLITE_OK )  
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg );  

	//��������  
	sqlstr=" insert into MyTable_1( name ) values ( '��«��' ) ";  
	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );  
	if(result != SQLITE_OK )  
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg );  

	//��������  
	sqlstr=" insert into MyTable_1( name ) values ( '������' ) ";  
	result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );   
	if(result != SQLITE_OK )   
		CCLog( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, errMsg ); 
}


	//��ѯ
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
