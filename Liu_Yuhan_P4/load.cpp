#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int load_DATA_SRC();
int load_LANGUAL();
int load_DATSRCLN();
int load_DERIV_CD();
int load_FD_GROUP();
int load_FOOD_DES();
int load_FOOTNOTE();
int load_LANGDESC();
int load_NUT_DATA();
int load_NUTR_DEF();
int load_SRC_CD();
int load_WEIGHT();
string modifyString (string str);

int main(int argc, char* argv[])
{
   load_FOOD_DES();
   load_DATA_SRC();
   load_LANGUAL();
   load_DATSRCLN();
   load_DERIV_CD();
   load_FD_GROUP();
   load_FOOTNOTE();
   load_LANGDESC();
   load_NUT_DATA();
   load_NUTR_DEF();
   load_SRC_CD();
   load_WEIGHT();

   return 0;
}



int load_WEIGHT(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE WEIGHT;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE WEIGHT("  \
         "NDB_No VARCHAR(5)," \
         "Seq VARCHAR(2),"\
         "Amount NUMERIC(5,3),"\
         "Msre_Desc VARCHAR(84),"\
         "Gm_Wgt NUMERIC(7,1),"\
         "Num_Data_Pts NUMERIC(3,0),"\
         "Std_Dev NUMERIC(7,3));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("WEIGHT.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO WEIGHT "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_SRC_CD(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE SRC_CD;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE SRC_CD("  \
         "Src_Cd VARCHAR(2)," \
         "SrcCd_Desc VARCHAR(60));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("SRC_CD.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO SRC_CD "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_NUTR_DEF(){
  sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE NUTR_DEF;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE NUTR_DEF("  \
         "Nutr_No VARCHAR(3)," \
         "Units VARCHAR(7),"\
         "Tagname VARCHAR(20),"\
         "NutrDesc VARCHAR(60),"\
         "Num_Dec VARCHAR(1),"\
         "SR_Order NUMERIC(6,0));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("NUTR_DEF.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO NUTR_DEF "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_NUT_DATA(){
  sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE NUT_DATA;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE NUT_DATA("  \
         "NDB_No VARCHAR(5)," \
         "Nutr_No VARCHAR(3),"\
         "Nutr_Val NUMERIC(10,3),"\
         "Num_Data_Pts NUMERIC(5,0),"\
         "Std_Error NUMERIC(8,3),"\
         "Src_Cd VARCHAR(2),"\
         "Deriv_Cd VARCHAR(4),"\
         "Ref_NDB_No VARCHAR(5),"\
         "Add_Nutr_Mark VARCHAR(1),"\
         "Num_Studies NUMERIC(2,0),"\
         "Min NUMERIC(10,3),"\
         "Max NUMERIC(10,3),"\
         "DF NUMERIC(4,0),"\
         "Low_EB NUMERIC(10,3),"\
         "Up_EB NUMERIC(10,3),"\
         "Stat_cmt VARCHAR(10),"\
         "AddMode_Data VARCHAR(10),"\
         "CC VARCHAR(1));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("NUT_DATA.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO NUT_DATA "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);
   return 0;
}

int load_LANGDESC(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE LANGDESC;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE LANGDESC("  \
         "Factor_Code VARCHAR(5)," \
         "Description VARCHAR(140));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("LANGDESC.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO LANGDESC "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_FOOTNOTE(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE FOOTNOTE;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE FOOTNOTE("  \
         "NDB_No VARCHAR(5)," \
         "Footnt_No VARCHAR(4),"\
         "Footnt_Typ VARCHAR(1),"\
         "Nutr_No VARCHAR(3),"\
         "Footnt_Txt VARCHAR(200));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("FOOTNOTE.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO FOOTNOTE "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_FOOD_DES(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE FOOD_DES;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE FOOD_DES("  \
         "NDB_No VARCHAR(5)," \
         "FdGrp_Cd VARCHAR(4),"\
         "Long_Desc VARCHAR(200),"\
         "Shrt_Desc VARCHAR(60),"\
         "ComName VARCHAR(100),"\
         "ManufacName VARCHAR(65),"\
         "Survey VARCHAR(1),"\
         "Ref_desc VARCHAR(135),"\
         "Refuse NUMERIC(2,0),"\
         "SciName VARCHAR(65),"\
         "N_Factor NUMERIC(4,2),"\
         "Pro_Factor NUMERIC(4,2),"\
         "Fat_Factor NUMERIC(4,2),"\
         "CHO_Factor NUMERIC(4,2));";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("FOOD_DES.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO FOOD_DES "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);
   return 0;
}

int load_FD_GROUP(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE FD_GROUP;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE FD_GROUP("  \
         "FdGrp_Cd VARCHAR(4)," \
         "FdGrp_Desc VARCHAR(60));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("FD_GROUP.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO FD_GROUP "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_DERIV_CD(){
    sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE DERIV_CD;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);


   /* Create SQL statement */
  sql = "CREATE TABLE DERIV_CD("  \
         "Deriv_Cd VARCHAR(4)," \
         "Deriv_Desc VARCHAR(120));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("DERIV_CD.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO DERIV_CD "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_DATSRCLN(){
    sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE DATSRCLN;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE DATSRCLN("  \
         "NDB_No VARCHAR(5)," \
         "Nutr_No VARCHAR(3)," \
         "DataSrc_ID VARCHAR(6));" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("DATSRCLN.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO DATSRCLN "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

int load_LANGUAL(){
  sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE LANGUAL;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);


   /* Create SQL statement */
  sql = "CREATE TABLE LANGUAL("  \
         "NDB_No INT," \
         "Factor_Code TEXT);" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("LANGUAL.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
   char str[1024];
   sqlite3_exec(db, "begin", callback, 0, &zErrMsg);
   while(in) {
    in.getline(str, 1024);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO LANGUAL VALUES ("+output +");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
    
   sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);
    in.close();
   sqlite3_close(db);
   return 0;
}
int load_DATA_SRC(){
    sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("nutrients.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }

   sql = "DROP TABLE DATA_SRC;";
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   /* Create SQL statement */
  sql = "CREATE TABLE DATA_SRC("  \
         "Data_Src_DD TEXT," \
         "Author TEXT," \
         "Title TEXT," \
         "Year INT," \
         "Journal TEXT," \
         "Vol_City TEXT," \
         "Issue_State INT," \
         "Start_Page INT," \
         "End_Page INT);" ;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   ifstream in("DATA_SRC.txt");
   if(!in) {
     cout << "Cannot open input file.\n";
     return 1;
   }
  sqlite3_exec(db, "begin", callback, 0, &zErrMsg);

   while(in) {
    string str;
    getline(in, str);  // delim defaults to '\n'
    string output = modifyString(str);
    if (output != ""){
      output = "INSERT INTO DATA_SRC "\
      "VALUES ("+ output;
      output = output + ");";
      const char * command = output.c_str();
      rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
      if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
      }
    }
   }
     sqlite3_exec(db, "COMMIT", callback, 0, &zErrMsg);

    in.close();
   
   sqlite3_close(db);

   return 0;
}

string modifyString (string str){  
  string output = str;
  output= output.substr(0,output.size()-1);
  for(int i = 0; i < output.size(); i++){
    if (output[i] == '\''){
      output.insert(i,"'");
      i++;
    }
  }
  for (int i = 0; i < output.size();i++){
    if (output[i] == '~'){
        output[i] = '\'';
    }
  }
  for (int i = 0; i < output.size();i++){
    if (output[i] == '\'' && output[i+1] == '\''){
        output.erase(i,2);
        i = i -1;
    }
  }
  for (int i = 0; i < output.size();i++){
    if (output[i] == '^' && output[i+1] == '^'){
      output.insert(i+1, "NULL");
    }
  }
  for (int i = 0; i < output.size(); i++){
    if (output[i] == '^'){
      output[i] = ',';
    }
  }
  if (output[output.size()-1] == ','){
    output = output + "NULL";
  }
  return output;
}